//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "Tprofile.h"

#include "FGST34a.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TMidi"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TTGST34a::TTGST34a(TComponent* Owner)
    : TFChild(Owner)
{
    SetForm(this);

    // calculate field 105
    Edit103->OnExit =  Sum105Change;    Edit104->OnExit =  Sum105Change;
    Edit103A->OnExit = Sum105Change;    Edit104A->OnExit =  Sum105Change;
    // calculate field 108
    Edit106->OnExit =  Sum108Change;    Edit107->OnExit =  Sum108Change;
    Edit106A->OnExit = Sum108Change;    Edit107A->OnExit =  Sum108Change;

    // calculate field 112
    Edit110->OnExit =  Sum112Change;    Edit111->OnExit =  Sum112Change;
    Edit110A->OnExit = Sum112Change;    Edit111A->OnExit =  Sum112Change;

    // calculate field 205-405
    Edit205->OnExit =  Sum113Change;    Edit405->OnExit =  Sum113Change;
    Edit205A->OnExit = Sum113Change;    Edit405A->OnExit =  Sum113Change;

}
//---------------------------------------------------------------------------
void TTGST34a::Init(void)
{
    if( company.ID <= 0 )
        return;

    EditBN->Text = company.Federal;
    EditName->Text = company.IncName;

    if( EditDate->Text.IsEmpty() )
    {
      DT = Now();
      EditDate->Text = DT.FormatString("MM/dd/yyyy");
    }
}
//---------------------------------------------------------------------------
TDateTime TTGST34a::getDate(void) // get from DT put on Form
{
    try
    {
        EditDate->Text = DT.FormatString("MM/dd/yyyy");
    }
    catch(...){ShowMessage("Cannot Convert Date of Document!");}
    return Now();
}
//---------------------------------------------------------------------------
void TTGST34a::putDate(void) // get from From and put to DT
{
    try
    {
        DT =  StrToDate(EditDate->Text.Trim());
    }
    catch(...){ShowMessage("Cannot Convert Date of Document!");}
}
//---------------------------------------------------------------------------
void TTGST34a::Calc()
{
    Screen->Cursor = crHourGlass;
    try
    {
      Sum105Change(NULL);
      Sum108Change(NULL);
      Sum112Change(NULL);
      Sum113Change(NULL);

      SetEdit();
      try
      {
        WORD year, month, day;
        DT =  StrToDate(EditDate->Text.Trim());
        DecodeDate(DT, year, month, day);
        EditDay->Text = day;
        EditMonth->Text = month;
        EditYear->Text = year;
      }catch(...)
      {
        ShowMessage("Wrong Date!");
      }
    }catch(...){
        DT = Now();
        WPEditClick( EditDay );
    }
    Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum1145Change(TObject *Sender)
{
    float koef = Edit113CZ->Text.Pos("-") > 0 ? -1.0 : 0.0;

    double sum =  atof(Edit113C->Text.Trim().c_str());
    sum +=  atof(Edit113CA->Text.Trim().c_str()) / 100.0;

    if( koef > 0 )
    {
        Edit114->Text = (int)sum;
        Edit115->Text = "";
    }else
    {
        Edit115->Text = (int)sum;
        Edit115A->Text = (int)(100 * (sum - (float)(int)sum));
        Edit114->Text = "";
    }
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum113cChange(TObject *Sender)
{
    float koef = Edit113AZ->Text.Pos("-") > 0 ? -1.0 : 0.0;
    double sum =  koef * atof(Edit113A->Text.Trim().c_str());
    sum +=  koef * atof(Edit113AA->Text.Trim().c_str()) / 100.0;
    // 113A + 113B
    sum +=  atof(Edit113B->Text.Trim().c_str());
    sum +=  atof(Edit113BA->Text.Trim().c_str()) / 100.0;

    Edit113CZ->Text = sum < 0.0 ? "-" : " ";
    sum = fabs(sum);

    Edit113C->Text = (int)sum;
    Edit113CA->Text = (int)(100 * (sum - (float)(int)sum));

    Sum1145Change(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum113Change(TObject *Sender)
{
    double sum =  atof(Edit205->Text.Trim().c_str());
    sum +=  atof(Edit205A->Text.Trim().c_str()) / 100.0;
    sum +=  atof(Edit405->Text.Trim().c_str());
    sum +=  atof(Edit405A->Text.Trim().c_str()) / 100.0;
    Edit113B->Text = (int)sum;
    Edit113BA->Text = (int)(100 * (sum - (float)(int)sum));

    Sum113cChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum113aChange(TObject *Sender)
{
    double sum =  atof(Edit112->Text.Trim().c_str());
    sum +=  atof(Edit112A->Text.Trim().c_str()) / 100.0;
    // 112 - 109
    float koef = Edit109Z->Text.Pos("-") > 0 ? -1.0 : 0.0;
    sum -=  koef * atof(Edit109->Text.Trim().c_str());
    sum -=  koef * atof(Edit109A->Text.Trim().c_str()) / 100.0;

    Edit113AZ->Text = sum < 0.0 ? "-" : " ";
    sum = fabs(sum);

    Edit113A->Text = (int)sum;
    Edit113AA->Text = (int)(100 * (sum - (float)(int)sum));
    
    Sum113Change(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum112Change(TObject *Sender)
{
    double sum =  atof(Edit110->Text.Trim().c_str());
    sum +=  atof(Edit110A->Text.Trim().c_str()) / 100.0;
    sum +=  atof(Edit111->Text.Trim().c_str());
    sum +=  atof(Edit111A->Text.Trim().c_str()) / 100.0;
    Edit112->Text = (int)sum;
    Edit112A->Text = (int)(100 * (sum - (float)(int)sum));

    Sum113aChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum109Change(TObject *Sender)
{
    double sum =  atof(Edit108->Text.Trim().c_str());
    sum +=  atof(Edit108A->Text.Trim().c_str()) / 100.0;
    // 108 - 105
    sum -=  atof(Edit105->Text.Trim().c_str());
    sum -=  atof(Edit105A->Text.Trim().c_str()) / 100.0;

    if( sum < 0.0 ) // type negative or not
    {
        Edit109Z->Text =  "-";
        sum *= -1.0;
    }else
        Edit109Z->Text =  " ";

    Edit109->Text = (int)sum;
    Edit109A->Text = (int)(100 * (sum - (float)(int)sum));
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum108Change(TObject *Sender)
{
    double sum =  atof(Edit106->Text.Trim().c_str());
    sum +=  atof(Edit106A->Text.Trim().c_str()) / 100.0;
    sum +=  atof(Edit107->Text.Trim().c_str());
    sum +=  atof(Edit107A->Text.Trim().c_str()) / 100.0;
    Edit108->Text = (int)sum;
    Edit108A->Text = (int)(100 * (sum - (float)(int)sum));

    Sum109Change(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TTGST34a::Sum105Change(TObject *Sender)
{
    double sum =  atof(Edit103->Text.Trim().c_str());
    sum +=  atof(Edit103A->Text.Trim().c_str()) / 100.0;
    sum +=  atof(Edit104->Text.Trim().c_str());
    sum +=  atof(Edit104A->Text.Trim().c_str()) / 100.0;
    Edit105->Text = (int)sum;
    Edit105A->Text = (int)(100 * (sum - (float)(int)sum));

    Sum109Change(Sender);
}
//---------------------------------------------------------------------------
//   second page
//---------------------------------------------------------------------------
void __fastcall TTGST34a::SetEdit(void)
{
    vector<TComp>::iterator j_ptr, i_ptr;
    for(j_ptr = lstRect.begin(); j_ptr != lstRect.end(); j_ptr++)
    {
        TComp *val = &(*j_ptr);
        TWPEdit *editSender = val->edit;
        TXelm *elm = (TXelm *)editSender->Tag;
        try
        {
          {
            String number = editSender->Text.Trim();
            if( !number.IsEmpty() )
            {
                int j = number.Length();
                for(int i=10; j > 0 && i > 0 ; i--)
                {
                    String name = editSender->Name + "_" + String(i);
                    for(i_ptr = lstRect.begin(); i_ptr != lstRect.end(); i_ptr++)
                    {
                        TComp *val = &(*i_ptr);
                        if( val->edit->Name == name )
                        {
                            val->edit->Text = String(number[j--]);
                            break;
                        }
                    }
                }

            }
          }
        }catch(...){ }
	}
}
//---------------------------------------------------------------------------
bool TTGST34a::BeforeSave(void)
{
    ProcessMoney(); // to process all money fields
    return false;
}
//---------------------------------------------------------------------------
void TTGST34a::PostSave(void)
{
    UnProcessMoney(); // to unprocess all money fields
}
//---------------------------------------------------------------------------
// to process data from DB
void TTGST34a::PostLoad(void)
{
//    LoadProcessMoney();        
}
//---------------------------------------------------------------------------


