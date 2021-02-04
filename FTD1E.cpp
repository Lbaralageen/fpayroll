//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "Tprofile.h"

#include "FTD1E.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TMidi"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TTD1E::TTD1E(TComponent* Owner)
    : TFChild(Owner)
{
    SetForm(this, ScrollBarV, ScrollBarH);

    EditF1->OnExit = SumFChange;
    EditF2->OnExit = SumFChange;
    EditF3->OnExit = SumFChange;
    EditF4->OnExit = SumFChange;
    EditF5->OnExit = SumFChange;
    EditF6->OnExit = SumFChange;
    EditF7->OnExit = SumFChange;
    EditF8->OnExit = SumFChange;
    EditF9->OnExit = SumFChange;
    EditF10->OnExit = SumFChange;
    EditF11->OnExit = SumFChange;
    EditF12->OnExit = SumFChange;
    EditF13->OnExit = SumFChange;
    EditF14->OnExit = SumFChange;
}
//---------------------------------------------------------------------------
void TTD1E::Init(void)
{
    if( person.ID <= 0 )
    {
        ShowMessage("You have to assign current person");
        return;
    }
    EditLastName->Text = person.LastName;
    EditFirstName->Text = person.FirstName;

    EditAddress1->Text = person.Street;
    EditAddress2->Text = person.City + " " + person.Province;
    EditCounty->Text = person.County;
    EditPostBox->Text = person.Index;
    EditSIN->Text = person.getSIN();
    EditBirth->Text = person.Birth.FormatString("yyyy/MM/dd");
}
//---------------------------------------------------------------------------
void __fastcall TTD1E::SumFChange(TObject *Sender)
{
    double sum =  atof(EditF1->Text.Trim().c_str());
    sum +=  atof(EditF2->Text.Trim().c_str());
    sum +=  atof(EditF3->Text.Trim().c_str());
    sum +=  atof(EditF4->Text.Trim().c_str());
    sum +=  atof(EditF5->Text.Trim().c_str());
    sum +=  atof(EditF6->Text.Trim().c_str());
    sum +=  atof(EditF7->Text.Trim().c_str());
    sum +=  atof(EditF8->Text.Trim().c_str());
    sum +=  atof(EditF9->Text.Trim().c_str());
    sum +=  atof(EditF10->Text.Trim().c_str());
    sum +=  atof(EditF11->Text.Trim().c_str());
    sum +=  atof(EditF12->Text.Trim().c_str());
    sum +=  atof(EditF13->Text.Trim().c_str());
    sum +=  atof(EditF14->Text.Trim().c_str());
    EditSUM->Text = sum;
}
//---------------------------------------------------------------------------


