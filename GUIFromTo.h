//---------------------------------------------------------------------------

#ifndef GUIFromToH
#define GUIFromToH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
bool bGetFromToPars(int* _iFrom,int* _iTo,int* _iSecs);

//---------------------------------------------------------------------------
class ToDLGFromTo : public TForm
{
__published:	// IDE-managed Components
    TLabel *oFromBPMLabelU;
    TLabel *oFromBPMLabelC;
    TLabel *oFromBPMLabelD;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *oToBPMLabelC;
    TLabel *oToBPMLabelD;
    TLabel *oToBPMLabelU;
    TLabel *oSecsLabelC;
    TLabel *oSecsLabelD;
    TLabel *oSecsLabelU;
    TLabel *oSecsLabelM;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TImage *Image1;
    TSpeedButton *oOkBtn;
    TSpeedButton *oCancelBtn;
    void __fastcall oFromBPMLabelCMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oFromBPMLabelDMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oFromBPMLabelUMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oToBPMLabelCMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oToBPMLabelDMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oToBPMLabelUMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oSecsLabelDMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oSecsLabelCMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oSecsLabelMMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall oSecsLabelUMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall oOkBtnClick(TObject *Sender);
    void __fastcall oCancelBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall ToDLGFromTo(TComponent* Owner);

    void __fastcall SetupToBPMsLabels();
    void __fastcall SetupFromBPMsLabels();
    void __fastcall SetupSecsLabels();
};
//---------------------------------------------------------------------------
extern PACKAGE ToDLGFromTo *oDLGFromTo;
//---------------------------------------------------------------------------
#endif
