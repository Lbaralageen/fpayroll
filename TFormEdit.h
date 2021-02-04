//---------------------------------------------------------------------------

#ifndef TFormEditH
#define TFormEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Buttons.hpp>

#include <Menus.hpp>

#include "TMain.h"

//---------------------------------------------------------------------------
class TFormEdit : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TButton *ButtonOK;
    TButton *ButtonCancel;
    TPanel *Panel3;
    TPanel *Panel4;
    TEdit *EditName;
    TLabel *Label1;
    void __fastcall ButtonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int __fastcall Execute(String name);

    __fastcall TFormEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
