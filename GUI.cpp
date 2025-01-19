//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "inifiles.hpp"
#include "GUI.h"
#include "OMidiOut.h"
#include "GUIFromTo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define MAX_INSTRUMENTS 16
#define MAX_TICS        16

typedef struct{

    AnsiString      asName;
    unsigned char   ucChannel;
    unsigned char   ucInstrument;
    unsigned char   ucNote;
    unsigned char   ucVolume;

}TInstrumentInfo;

TInstrumentInfo goInstTab[MAX_INSTRUMENTS];
//---------------------------------------------------------------------------
bool gbPatternGrid[MAX_TICS][MAX_INSTRUMENTS];
int  giBPMs     = 120;
int  giTempoNum = 4;
int  giTempoDen = 4;
int  giMIDIDev  = 0;

#define MIN_BPMS    10
#define MAX_BPMS    250
//---------------------------------------------------------------------------
ToForm *oForm;

int   giSubBeat    = -1;
int   giAbsSubBeat = -1;
float gfAbsSubBeat = 0;

bool gbNoteOn[MAX_INSTRUMENTS];



int giFromBPMs = 60;
int giToBPMs   = 120;
int giSecs     = 120;


TObjetoMidiOut		oMIDIOut;
DWORD               gdwInitialTime;

DWORD               gdwLastTAPTime = -1;
float               gfAvgTAPBPMs   = 0.0f;
//---------------------------------------------------------------------------
void ReadConfig()
{
    TIniFile *ini   = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
    giMIDIDev       = ini->ReadInteger( "General", "MIDIDev", 0 );
    giBPMs          = ini->ReadInteger( "General", "BPMS", 120 );
    giTempoNum      = ini->ReadInteger( "General", "TempoNum", 4 );
    giTempoDen      = ini->ReadInteger( "General", "TempoDen", 4 );

    int r;
    for (r=0;r<MAX_INSTRUMENTS;r++)
    {
        AnsiString asRow;
        asRow = ini->ReadString("General","Row"+IntToStr(r),"0000000000000000");

        for (int c=0;c<MAX_TICS;c++)
        {
            char *str = asRow.c_str();
            gbPatternGrid[c][r] = (str[c] == '1');
        }
    }

    for (r=0;r<MAX_INSTRUMENTS;r++)
    {
        AnsiString asVar = "Inst"+IntToStr(r);
        goInstTab[r].asName         = ini->ReadString(asVar,"Name","");
        goInstTab[r].ucChannel      = ini->ReadInteger(asVar,"Channel",9);
        goInstTab[r].ucInstrument   = ini->ReadInteger(asVar,"Channel",0);
        goInstTab[r].ucNote         = ini->ReadInteger(asVar,"Note",32);
        goInstTab[r].ucVolume       = ini->ReadInteger(asVar,"Volume",127);
    }
}
//---------------------------------------------------------------------------
void WriteConfig()
{
    TIniFile *ini   = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
    ini->WriteInteger( "General", "MIDIDev",  giMIDIDev );
    ini->WriteInteger( "General", "BPMS", giBPMs );
    ini->WriteInteger( "General", "TempoNum", giTempoNum );
    ini->WriteInteger( "General", "TempoDen", giTempoDen );

    int r;
    for (r=0;r<MAX_INSTRUMENTS;r++)
    {
        AnsiString asRow = "";

        for (int c=0;c<MAX_TICS;c++)
        {
            if (gbPatternGrid[c][r])
                asRow+="1";
            else
                asRow+="0";
        }

        ini->WriteString("General","Row"+IntToStr(r),asRow);        
    }

    for (r=0;r<MAX_INSTRUMENTS;r++)
    {
        AnsiString asVar = "Inst"+IntToStr(r);
        ini->WriteString(asVar,"Name",goInstTab[r].asName);
        ini->WriteInteger(asVar,"Channel",goInstTab[r].ucChannel);
        ini->WriteInteger(asVar,"Channel",goInstTab[r].ucInstrument);
        ini->WriteInteger(asVar,"Note",goInstTab[r].ucNote);
        ini->WriteInteger(asVar,"Volume",goInstTab[r].ucVolume);
    }
}
//---------------------------------------------------------------------------
void __fastcall ToForm::FormCreate(TObject *Sender)
{
    // Read configuration
    ReadConfig();

    // Open MIDI Out port
	int iMIDIOutPort = giMIDIDev;

	// Open Output Port
	oMIDIOut.Open(NULL);
	if (oMIDIOut.Abierto)
	{
		oMIDIOut.EstablecerDispositivo(iMIDIOutPort);
		// printf("MIDI Output port %d %s\n",iMIDIOutPort,ObtenerNombreDispositivoMidiOut(iMIDIOutPort));
	}
	else
    {
//		printf("Unable to start MIDI Output port %d\n",
//			   "%s\n",iMIDIOutPort,ObtenerNombreDispositivoMidiOut(iMIDIOutPort));
//		return(-1);
	}

    SetupBPMsLabels();

    oTempNum->Caption  = IntToStr(giTempoNum);
    oTempNum->Caption  = IntToStr(giTempoDen);

    int r,c;

    // Fill instrument names
    oGrid->ColWidths[0] = 48;
    for (r=0;r<MAX_INSTRUMENTS;r++)
        oGrid->Cells[0][r+1] = goInstTab[r].asName;

    // Fill grid
    for (c=0;c<MAX_TICS;c++)
        for (r=0;r<MAX_INSTRUMENTS;r++)
            if (gbPatternGrid[c][r])
                oGrid->Cells[c+1][r+1] = char(7);
            else
                oGrid->Cells[c+1][r+1] = "";

    oFromToSecs->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall ToForm::FormDestroy(TObject *Sender)
{
    WriteConfig();
}
//---------------------------------------------------------------------------
__fastcall ToForm::ToForm(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------


void __fastcall ToForm::oTimerTimer(TObject *Sender)
{
    DWORD dwCurTicks  = GetTickCount();
    int iTicks        = dwCurTicks - gdwInitialTime;
    float fSecs       = (float)iTicks / 1000.0f;
    float fSBPSs      = (float)giBPMs * 4.0f / 60.0f;
    float fRelSubBeat = fSecs * fSBPSs;
    gfAbsSubBeat     += fRelSubBeat;
    giAbsSubBeat      =(int)gfAbsSubBeat;

    int   iRelSubBeat = giAbsSubBeat % (oGrid->ColCount - 1);

    if (iRelSubBeat != giSubBeat)
    {
        oGrid->Cells[giSubBeat+1][0] = "";

        giSubBeat = iRelSubBeat;
        oGrid->Cells[giSubBeat+1][0] = char(24);

        for (int r=0;r<oGrid->RowCount-1;r++)
        {
            if (gbPatternGrid[giSubBeat][r])
            {
                if (gbNoteOn[r])
                {
                    // Note Off
                    oMIDIOut.Comando(0x90 + goInstTab[r].ucChannel,goInstTab[r].ucNote,0);
                    gbNoteOn[r] = false;
                }

                oMIDIOut.Comando(0xC0 + goInstTab[r].ucChannel,goInstTab[r].ucInstrument,0);
                oMIDIOut.Comando(0x90 + goInstTab[r].ucChannel,goInstTab[r].ucNote,goInstTab[r].ucVolume);
                gbNoteOn[r] = true;
            }
        }

    }

    gdwInitialTime   = dwCurTicks;
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oOnOffMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giSubBeat    = -1;
        giAbsSubBeat = 0;
        gfAbsSubBeat = 0;

        gdwInitialTime  = GetTickCount();
        oTimer->Enabled = ! oTimer->Enabled;

        if (oTimer->Enabled == false)
        {
            for (int c=0;c<oGrid->ColCount;c++)
                oGrid->Cells[c][0] = "";

            oFromToSecs->Caption = "";
        }
    }
    else
    {
        ShowMessage("Cool Metronome: by David Márquez de la Cruz 2007 (c)");
    }
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oGridMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int iRow,iCol;
    oGrid->MouseToCell(X,Y,iCol,iRow);

    if ((iCol<1) || (iRow<1) || (iCol>16) || (iRow>16)) return;

    gbPatternGrid[iCol-1][iRow-1] = !gbPatternGrid[iCol-1][iRow-1];

    if (gbPatternGrid[iCol-1][iRow-1])
        oGrid->Cells[iCol][iRow] = char(7);
    else
        oGrid->Cells[iCol][iRow] = "";
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oBPMLabelCMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giBPMs = giBPMs + 100;
    }
    else
    if (Button == mbRight)
    {
        giBPMs = giBPMs - 100;
    }

    if (giBPMs > MAX_BPMS) giBPMs = MAX_BPMS;
    if (giBPMs < MIN_BPMS) giBPMs = MIN_BPMS;

    SetupBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oBPMLabelDMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giBPMs = giBPMs + 10;
    }
    else
    if (Button == mbRight)
    {
        giBPMs = giBPMs - 10;
    }

    if (giBPMs > MAX_BPMS) giBPMs = MAX_BPMS;
    if (giBPMs < MIN_BPMS) giBPMs = MIN_BPMS;

    SetupBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oBPMLabelUMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giBPMs = giBPMs + 1;
    }
    else
    if (Button == mbRight)
    {
        giBPMs = giBPMs - 1;
    }

    if (giBPMs > MAX_BPMS) giBPMs = MAX_BPMS;
    if (giBPMs < MIN_BPMS) giBPMs = MIN_BPMS;

    SetupBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oTimer2Timer(TObject *Sender)
{
    if (giFromBPMs < giToBPMs)
    {
        if (giBPMs < giToBPMs)
        {
            giBPMs++;
            SetupBPMsLabels();
        }
        else
        {
            oTimer2->Enabled = false;
            oFromToSecs->Caption = "";
        }
    }
    else
    {
        if (giBPMs > giToBPMs)
        {
            giBPMs--;
            SetupBPMsLabels();
        }
        else
        {
            oTimer2->Enabled = false;
            oFromToSecs->Caption = "";
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ToForm::SetupBPMsLabels()
{
    oBPMLabelU->Caption = IntToStr(giBPMs % 10);
    oBPMLabelD->Caption = IntToStr((giBPMs / 10) % 10);
    oBPMLabelC->Caption = IntToStr(giBPMs / 100);
    if (giBPMs < 100) oBPMLabelC->Caption = "";
}
//---------------------------------------------------------------------------

void __fastcall ToForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_SPACE)
    {
        TShiftState Shift;
        oOnOffMouseDown(Sender,mbLeft,Shift,0,0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ToForm::oTapMouseDown(TObject *Sender, TMouseButton Button,TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        DWORD dwCurTAPTime = GetTickCount();
        float fBPMs = 1.0f / ((float)(dwCurTAPTime - gdwLastTAPTime) / (60.0f*1000.0f));

        // Es la primera vez o ha pasado mucho tiempo desde el ultimo tap
        if ( (fBPMs < MIN_BPMS) || (fBPMs > (2*MAX_BPMS)) )
        {
            gfAvgTAPBPMs   = -1.0f;
        }
        else
        {
            if (gfAvgTAPBPMs == -1.0f)
            {
                gfAvgTAPBPMs = fBPMs;
            }
            else
            {
                gfAvgTAPBPMs = (gfAvgTAPBPMs + fBPMs) * 0.5f;
            }

            giBPMs = (int)gfAvgTAPBPMs;
            if (giBPMs > MAX_BPMS) giBPMs = MAX_BPMS;
            if (giBPMs < MIN_BPMS) giBPMs = MIN_BPMS;

            SetupBPMsLabels();
        }

        gdwLastTAPTime = dwCurTAPTime;
    }
    else
    {
        if ((Button == mbRight) && (! oTimer->Enabled))
        {
            if (bGetFromToPars(&giFromBPMs,&giToBPMs,&giSecs))
            {
                // Compute interval to change values
                oTimer2->Interval = (1000 * giSecs) / abs(giToBPMs - giFromBPMs);
                oTimer2->Enabled  = true;

                giBPMs            = giFromBPMs;
                SetupBPMsLabels();

                gdwInitialTime  = GetTickCount();
                oTimer->Enabled = true;

                oFromToSecs->Caption = IntToStr( giFromBPMs ) + "-" + IntToStr(giToBPMs) + " : " + IntToStr(giSecs);
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall ToForm::oTempNumMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    if (oGrid->ColCount == 17)
    {
        oTempNum->Caption = "3";
        oGrid->ColCount = 13;
    }
    else
    {
        oTempNum->Caption = "4";
        oGrid->ColCount = 17;
    }
}
//---------------------------------------------------------------------------


