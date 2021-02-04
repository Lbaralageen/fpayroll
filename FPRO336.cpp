//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "Tprofile.h"

#include "FPRO336.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TMidi"
#pragma resource "*.dfm"


//---------------------------------------------------------------------------
__fastcall TTPRO336::TTPRO336(TComponent* Owner)
    : TFChild(Owner)
{
    SetForm(this, ScrollBarV, ScrollBarH);
}
//---------------------------------------------------------------------------
void TTPRO336::Init(void)
{
    if( person.ID <= 0 )
    {
        ShowMessage("You have to assign current person");
        Refresh(NULL);
        return;
    }
/*
    EditName->Text = person.FirstName;
    EditMiddle->Text = person.MiddleName;
    EditFamily->Text = person.LastName;

    EditStreet->Text = person.Street;
    EditMailCity->Text = person.City;
    EditMailProvince->Text = person.Province;
    EditPostal->Text = person.Index;

    WORD year, month, day;
    DecodeDate(person.Birth, year, month, day);
    EditDay->Text = day;
    EditMonth->Text = month;
    EditYear->Text = year;

    if( person.Sex )
    {
        CheckBoxMale->Checked = true;
        CheckBoxFemale->Checked = false;
    }else
    {
        CheckBoxFemale->Checked = true;
        CheckBoxMale->Checked = false;
    }
*/    
}
//---------------------------------------------------------------------------
TDateTime TTPRO336::getDate(void) // get from DT put on Form
{
    try
    {
       EditDate->Text = FormatDateTime("MM/dd/yyyy", DT);
    }
    catch(...){ShowMessage("Cannot Convert Date of Document!");}
    return Now();
}
//---------------------------------------------------------------------------
void TTPRO336::putDate(void) // get from From and put to DT
{
    try
    {
      DT =  StrToDate(EditDate->Text.Trim());
    }
    catch(...){ShowMessage("Cannot Convert Date of Document!");}
}
//---------------------------------------------------------------------------
void __fastcall TTPRO336::CheckBoxMaleClick(TObject *Sender)
{
    if( CheckBoxMale->Checked )
        CheckBoxFemale->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TTPRO336::CheckBoxFemaleClick(TObject *Sender)
{
    if( CheckBoxFemale->Checked )
        CheckBoxMale->Checked = false;
}
//---------------------------------------------------------------------------

