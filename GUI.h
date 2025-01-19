//---------------------------------------------------------------------------

#ifndef GUIH
#define GUIH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class ToForm : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *oGrid;
    TLabel *oTempNum;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *oTempDen;
    TTimer *oTimer;
    TLabel *oBPMLabelC;
    TLabel *oBPMLabelU;
    TLabel *oBPMLabelD;
    TSpeedButton *oOnOff;
    TImage *Image1;
    TTimer *oTimer2;
    TLabel *oFromToSecs;
    TSpeedButton *oTap;
    void __fastcall oTimerTimer(TObject *Sender);
    void __fastcall oGridMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall oBPMLabelCMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall oBPMLabelDMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oBPMLabelUMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oTimer2Timer(TObject *Sender);
    void __fastcall oOnOffMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall oTapMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall oTempNumMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
    __fastcall ToForm(TComponent* Owner);

    void __fastcall SetupBPMsLabels();
};
//---------------------------------------------------------------------------
extern PACKAGE ToForm *oForm;
//---------------------------------------------------------------------------
#endif
