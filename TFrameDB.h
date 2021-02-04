//---------------------------------------------------------------------------


#ifndef TFrameDBH
#define TFrameDBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include "XMLclass.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrameDB : public TFrame
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TSpeedButton *ButtonStation;
    TLabel *LabelPathStation;
    TEdit *EditPath;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *EditUser;
    TEdit *EditPassword;
    TSpeedButton *Bip;
    TBitBtn *BtBConnect;
    TOpenDialog *OpenDialog;
    TBitBtn *BitBtnCheck;
    void __fastcall BtBConnectClick(TObject *Sender);
    void __fastcall ButtonStationClick(TObject *Sender);
    void __fastcall BitBtnCheckClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    bool CheckDB(TXobj *obj);
    bool __fastcall Execute(TWinControl *owner, TXobj *_obj);
    TXobj *obj;
    __fastcall TFrameDB(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TFrameDB *FrameDB;
//---------------------------------------------------------------------------
#endif
