//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GUIFromTo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
ToDLGFromTo *oDLGFromTo;

#define MIN_BPMS        10
#define MAX_BPMS        250

#define MIN_SECS        10
#define MAX_SECS        3600

int giSecs     = 10;
int giFromBPMs = 60;
int giToBPMs   = 120;
//---------------------------------------------------------------------------
__fastcall ToDLGFromTo::ToDLGFromTo(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::FormShow(TObject *Sender)
{
    SetupToBPMsLabels();
    SetupFromBPMsLabels();
    SetupSecsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oFromBPMLabelCMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giFromBPMs = giFromBPMs + 100;
    }
    else
    if (Button == mbRight)
    {
        giFromBPMs = giFromBPMs - 100;
    }

    if (giFromBPMs > MAX_BPMS) giFromBPMs = MAX_BPMS;
    if (giFromBPMs < MIN_BPMS) giFromBPMs = MIN_BPMS;

    SetupFromBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oFromBPMLabelDMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giFromBPMs = giFromBPMs + 10;
    }
    else
    if (Button == mbRight)
    {
        giFromBPMs = giFromBPMs - 10;
    }

    if (giFromBPMs > MAX_BPMS) giFromBPMs = MAX_BPMS;
    if (giFromBPMs < MIN_BPMS) giFromBPMs = MIN_BPMS;

    SetupFromBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oFromBPMLabelUMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giFromBPMs = giFromBPMs + 1;
    }
    else
    if (Button == mbRight)
    {
        giFromBPMs = giFromBPMs - 1;
    }

    if (giFromBPMs > MAX_BPMS) giFromBPMs = MAX_BPMS;
    if (giFromBPMs < MIN_BPMS) giFromBPMs = MIN_BPMS;

    SetupFromBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::SetupFromBPMsLabels()
{
    oFromBPMLabelU->Caption = IntToStr(giFromBPMs % 10);
    oFromBPMLabelD->Caption = IntToStr((giFromBPMs / 10) % 10);
    oFromBPMLabelC->Caption = IntToStr(giFromBPMs / 100);
    if (giFromBPMs < 100) oFromBPMLabelC->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oToBPMLabelCMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giToBPMs = giToBPMs + 100;
    }
    else
    if (Button == mbRight)
    {
        giToBPMs = giToBPMs - 100;
    }

    if (giToBPMs > MAX_BPMS) giToBPMs = MAX_BPMS;
    if (giToBPMs < MIN_BPMS) giToBPMs = MIN_BPMS;

    SetupToBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oToBPMLabelDMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giToBPMs = giToBPMs + 10;
    }
    else
    if (Button == mbRight)
    {
        giToBPMs = giToBPMs - 10;
    }

    if (giToBPMs > MAX_BPMS) giToBPMs = MAX_BPMS;
    if (giToBPMs < MIN_BPMS) giToBPMs = MIN_BPMS;

    SetupToBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oToBPMLabelUMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giToBPMs = giToBPMs + 1;
    }
    else
    if (Button == mbRight)
    {
        giToBPMs = giToBPMs - 1;
    }

    if (giToBPMs > MAX_BPMS) giToBPMs = MAX_BPMS;
    if (giToBPMs < MIN_BPMS) giToBPMs = MIN_BPMS;

    SetupToBPMsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::SetupToBPMsLabels()
{
    oToBPMLabelU->Caption = IntToStr(giToBPMs % 10);
    oToBPMLabelD->Caption = IntToStr((giToBPMs / 10) % 10);
    oToBPMLabelC->Caption = IntToStr(giToBPMs / 100);
    if (giToBPMs < 100) oToBPMLabelC->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oSecsLabelUMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giSecs = giSecs + 1;
    }
    else
    if (Button == mbRight)
    {
        giSecs = giSecs - 1;
    }

    if (giSecs > MAX_SECS) giSecs = MAX_SECS;
    if (giSecs < MIN_SECS) giSecs = MIN_SECS;

    SetupSecsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oSecsLabelDMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giSecs = giSecs + 10;
    }
    else
    if (Button == mbRight)
    {
        giSecs = giSecs - 10;
    }

    if (giSecs > MAX_SECS) giSecs = MAX_SECS;
    if (giSecs < MIN_SECS) giSecs = MIN_SECS;

    SetupSecsLabels();
}
//---------------------------------------------------------------------------

void __fastcall ToDLGFromTo::oSecsLabelCMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        giSecs = giSecs + 100;
    }
    else
    if (Button == mbRight)
    {
        giSecs = giSecs - 100;
    }

    if (giSecs > MAX_SECS) giSecs = MAX_SECS;
    if (giSecs < MIN_SECS) giSecs = MIN_SECS;

    SetupSecsLabels();
}
//---------------------------------------------------------------------------

void __fastcall ToDLGFromTo::oSecsLabelMMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       if (Button == mbLeft)
    {
        giSecs = giSecs + 1000;
    }
    else
    if (Button == mbRight)
    {
        giSecs = giSecs - 1000;
    }

    if (giSecs > MAX_SECS) giSecs = MAX_SECS;
    if (giSecs < MIN_SECS) giSecs = MIN_SECS;

    SetupSecsLabels();
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::SetupSecsLabels()
{
    oSecsLabelU->Caption = IntToStr(giSecs % 10);
    oSecsLabelD->Caption = IntToStr((giSecs / 10) % 10);
    oSecsLabelC->Caption = IntToStr((giSecs / 100) % 10);
    oSecsLabelM->Caption = IntToStr(giSecs / 1000);

    if (giSecs < 1000) oSecsLabelM->Caption = "";
    if (giSecs < 100)  oSecsLabelC->Caption = "";
}
//---------------------------------------------------------------------------
bool bGetFromToPars(int* _iFrom,int* _iTo,int* _iSecs)
{
    giFromBPMs = *_iFrom;
    giToBPMs   = *_iTo;
    giSecs     = *_iSecs;

    oDLGFromTo->ShowModal();
    if (oDLGFromTo->ModalResult == mrOk)
    {
        *_iFrom = giFromBPMs;
        *_iTo   = giToBPMs;
        *_iSecs = giSecs;
        return (true);
    }
    else
        return(false);
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oOkBtnClick(TObject *Sender)
{
    oDLGFromTo->ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall ToDLGFromTo::oCancelBtnClick(TObject *Sender)
{
    oDLGFromTo->ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

