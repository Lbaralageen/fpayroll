//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "Tprofile.h"

#include "FNAS2120B.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TMidi"
#pragma resource "*.dfm"


//---------------------------------------------------------------------------
__fastcall TNAS2120B::TNAS2120B(TComponent* Owner)
    : TFChild(Owner)
{
    SetForm(this);
}
//---------------------------------------------------------------------------
void TNAS2120B::Init(void)
{
    if( person.ID <= 0 )
        return;

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

    String sin = person.getSIN();
    if( sin != "0" )
    {
        CheckBoxSINYes->Checked = true;
        for(int i=9; i > 0; i--)
        {
            if( i  > sin.Length() )
                continue;
            String name = "Edit" + String(i);
            TWPEdit *edit = dynamic_cast<TWPEdit *>(FindComponent(name));
            if( edit )
                edit->Text = sin[i];
        }
    }else
        CheckBoxSINNo->Checked = true;

    if( person.Sex )
    {
        CheckBoxMale->Checked = true;
        CheckBoxFemale->Checked = false;
    }else
    {
        CheckBoxFemale->Checked = true;
        CheckBoxMale->Checked = false;
    }
}
//---------------------------------------------------------------------------
bool TNAS2120B::BeforeSave(void)
{
	try
	{
	  // process SIN
		if( CheckBoxSINYes->Checked )
		{
		  bool flag = false;
		  String sin = "";
		  for(int i=1; i <= 9; i++)
		  {
			  String name = "Edit" + String(i);
              TWPEdit *edit = dynamic_cast<TWPEdit *>(FindComponent(name));
              if( !edit || edit->Text.IsEmpty() || !isdigit( edit->Text[1] ) )
              {
                flag = true; // error in SIN
                break;
              }else
                if( edit )
                    sin += edit->Text[1];
          }
          Edit1->MaxLength = 10;
          Edit1->Text = sin.Trim();
          if( flag )
          {
            ShowMessage("error in SIN number!");
            WPEditClick(Edit1);
            return true;
          }
        }else
            Edit1->Text = "0";

      // process Date
      Word Year = atoi(EditYear->Text.c_str());
      year1 = Year;
      Word Month  = atoi(EditMonth->Text.c_str());
      Word Day = atoi(EditDay->Text.c_str());
      if( Day == 0 || Month == 0 || Year == 0 )
      {
        unsigned short year, month, day;
        Now().DecodeDate( &year, &month, &day );
        EditYear->Text = year;
		EditDay->Text = year;
        EditMonth->Text = year;
        if( Day == 0 )
            EditDay->Text = day;
        if( Month == 0 )
            EditMonth->Text = month;
        if( Year == 0 )
            EditYear->Text = year;
        ShowMessage("Wrong Date!");
        WPEditClick(EditYear);
        return true;
      }else
	  {
		  TDateTime dts = EncodeDate(Year, Month, Day);
		  EditYear->Text = getFDate( dts );
      }
    }catch(...){
        ShowMessage("Wrong Date!");
        WPEditClick(EditYear);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void TNAS2120B::PostSave(void)
{
    EditYear->Text =  year1;
}
//---------------------------------------------------------------------------
// to process data from DB
void TNAS2120B::PostLoad(void)
{
    // fill SIN from DB
    String sin = Edit1->Text;
    if( sin != "0" )
    {
        Edit1->Text = "";
        CheckBoxSINYes->Checked = true;
        for(int i=9; i > 0; i--)
        {
            if( i  > sin.Length() )
                continue;
            String name = "Edit" + String(i);
            TWPEdit *edit = dynamic_cast<TWPEdit *>(FindComponent(name));
            if( edit )
                edit->Text = sin[i];
        }
    }else
    {
        CheckBoxSINNo->Checked = true;
        Edit1->Text = "";
    }

    // Fill date from DB
	long dt = atol(EditYear->Text.c_str());
	unsigned short year, month, day;
	getFDate(dt).DecodeDate( &year, &month, &day );
    EditYear->Text = year;
    EditDay->Text = day;
    EditMonth->Text = month;
}
//---------------------------------------------------------------------------
TDateTime TNAS2120B::getDate(void) // get from DT put on Form
{
    try
    {
       EditDate->Text = FormatDateTime("MM/dd/yyyy", DT);
    }
    catch(...){ShowMessage("Cannot Convert Date of Document!");}
    return Now();
}
//---------------------------------------------------------------------------
void TNAS2120B::putDate(void) // get from From and put to DT
{
    try
    {
      DT =  StrToDate(EditDate->Text.Trim());
    }
    catch(...){ShowMessage("Cannot Convert Date of Document!");}
}
//---------------------------------------------------------------------------
void __fastcall TNAS2120B::CheckBoxFirstClick(TObject *Sender)
{
    if( oldCh1 == (TCheckBox *)Sender )
        return;
    CheckBoxFirst->Checked  = false;
    CheckBoxReplace->Checked = false;
    CheckBoxName->Checked = false;
    CheckBoxStatus->Checked = false;
    CheckBoxOther->Checked = false;
    oldCh1 = (TCheckBox *)Sender;
    ((TCheckBox *)Sender)->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TNAS2120B::CheckBoxMaleClick(TObject *Sender)
{
    if( oldCh2 == (TCheckBox *)Sender )
        return;
    CheckBoxFemale->Checked = false;
    CheckBoxMale->Checked = false;
    oldCh2 = (TCheckBox *)Sender;
    ((TCheckBox *)Sender)->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TNAS2120B::CheckBoxSINNoClick(TObject *Sender)
{
    if( oldCh3 == (TCheckBox *)Sender )
        return;
     CheckBoxSINNo->Checked = false;
     CheckBoxSINYes->Checked = false;
    oldCh3 = (TCheckBox *)Sender;
    ((TCheckBox *)Sender)->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TNAS2120B::CheckBoxCitizenClick(TObject *Sender)
{
    if( oldCh4 == (TCheckBox *)Sender )
        return;
    {
        CheckBoxIndian->Checked = false;
        CheckBoxResident->Checked = false;
        CheckBoxOtherStatus->Checked = false;
        CheckBoxCitizen->Checked = false;
    }
    oldCh4 = (TCheckBox *)Sender;
    ((TCheckBox *)Sender)->Checked = true;
}
//---------------------------------------------------------------------------



