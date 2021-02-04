//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "Tprofile.h"

#include "F11076.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TMidi"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TT11076::TT11076(TComponent* Owner)
    : TFChild(Owner)
{
    SetForm(this);
}
//---------------------------------------------------------------------------
void TT11076::Init(void)
{
    if( person.ID <= 0 )
        return;
    // initialize mailing fields
    EditName->Text = person.FullName();
    EditStreet->Text = person.Street;
    EditCity->Text = person.City;
    EditProvince->Text = person.Province;
    EditPostal->Text = person.Index;

    if( EditDay->Text.IsEmpty() )
    {
      WORD year, month, day;
      DT = Now();
      DecodeDate(DT, year, month, day);
      EditDay->Text = day;
      EditMonth->Text = month;
      EditYear->Text = year;
    }
}
//---------------------------------------------------------------------------
TDateTime TT11076::getDate(void) // get from DT put on Form
{
    try
    {
      WORD year, month, day;
      DecodeDate(DT, year, month, day);
      EditDay->Text = day;
      EditMonth->Text = month;
      EditYear->Text = year;
    }
    catch(...){
        ShowMessage("Cannot Convert Date of Document!");
        EditYear->Focused();
    }
}
//---------------------------------------------------------------------------
void TT11076::putDate(void) // get from From and put to DT
{
    try
    {
      WORD year, month, day;
	  day = atoi(EditDay->Text.Trim().c_str());
	  month = atoi(EditMonth->Text.Trim().c_str());
	  year = atoi(EditYear->Text.Trim().c_str());
	  if( year == 0 && month != 0 && day == 0 )
		  DT = EncodeDate(year, month, day);
	  else
	  	 DT = Now();
    }
	catch(...)
	{
		ShowMessage("Cannot Convert Date of Document!");
		EditYear->Focused();
	}
}
//---------------------------------------------------------------------------
void __fastcall TT11076::CheckBox1Click(TObject *Sender)
{
	if( oldCh1 == (TCheckBox *)Sender )
		return;
	{
		CheckBox1->Checked = false;
		CheckBox2->Checked = false;
		CheckBox3->Checked = false;
	}
	oldCh1 = (TCheckBox *)Sender;
	((TCheckBox *)Sender)->Checked = true;
}
//---------------------------------------------------------------------------
bool TT11076::BeforeSave(void)
{
    if( ProcessData( year1, EditBirthYear, EditBirthMonth, EditBirthDay, true ) )
        return true;
    if( ProcessData( year2, EditMYear, EditMMonth, EditMDay, true ) )
        return true;
    if( ProcessData( year3, EditDeathYear, EditDeathMonth, EditDeathDay, true ) )
        return true;
    return false;
}
//---------------------------------------------------------------------------
void TT11076::PostSave(void)
{
    EditBirthYear->Text =  year1 ? String(year1) : String("");
    EditMYear->Text =  year2 ? String(year2) : String("");
    EditDeathYear->Text =  year3 ? String(year3) : String("");
}
//---------------------------------------------------------------------------
// to process data from DB
void TT11076::PostLoad(void)
{
	if( atol(EditBirthYear->Text.c_str()) == 0 )
		EditBirthYear->Text  = "";
	else
		UnProcessData( EditBirthYear, EditBirthMonth, EditBirthDay, true );
	if( atol(EditMYear->Text.c_str()) == 0 )
		EditMYear->Text  = "";
	else
		UnProcessData( EditMYear, EditMMonth, EditMDay, true );
	if( atol(EditDeathYear->Text.c_str()) == 0 )
		EditDeathYear->Text  = "";
	else
		UnProcessData( EditDeathYear, EditDeathMonth, EditDeathDay, true );
}
//---------------------------------------------------------------------------

