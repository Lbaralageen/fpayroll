//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFormEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TFormEdit::TFormEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int __fastcall TFormEdit::Execute(String name)
{
    EditName->Text = name;
    EditName->Focused();
    return ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormEdit::ButtonOKClick(TObject *Sender)
{
    if( EditName->Text.IsEmpty() || EditName->Text.Length() < 2 )
    {
        ShowMessage("Please type name!");
        EditName->Focused();
        return;
    }
}
//---------------------------------------------------------------------------



