//---------------------------------------------------------------------------

#ifndef FNAS2120BH
#define FNAS2120BH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "XMLclass.h"
#include "WPDefs.hpp"
#include "WPPrint.hpp"
#include "WPRich.hpp"
#include "WpWinCtr.hpp"
#include "TMidi.h"
#include "TSMask.hpp"
//---------------------------------------------------------------------------
class TNAS2120B : public TFChild
{
__published:	// IDE-managed Components
    TWPEdit *EditName;
    TWPEdit *EditMiddle;
    TWPEdit *EditFamily;
    TWPEdit *EditDay;
    TWPEdit *EditMonth;
    TWPEdit *EditYear;
    TCheckBox *CheckBoxMale;
    TCheckBox *CheckBoxFemale;
    TCheckBox *CheckBoxTwin;
    TWPEdit *EditMother;
    TWPEdit *EditFather;
    TWPEdit *EditCity;
    TWPEdit *EditProvince;
    TWPEdit *EditCountry;
    TWPEdit *EditNameBirth;
    TWPEdit *EditNameOther;
    TCheckBox *CheckBoxSINYes;
    TCheckBox *CheckBoxSINNo;
    TWPEdit *Edit1;
    TWPEdit *Edit2;
    TWPEdit *Edit3;
    TWPEdit *Edit4;
    TWPEdit *Edit5;
    TWPEdit *Edit6;
    TWPEdit *Edit7;
    TWPEdit *Edit8;
    TWPEdit *Edit9;
    TCheckBox *CheckBoxCitizen;
    TCheckBox *CheckBoxIndian;
    TCheckBox *CheckBoxResident;
    TCheckBox *CheckBoxOtherStatus;
    TWPEdit *EditHomeCode;
    TWPEdit *EditHomePhone;
    TWPEdit *EditWorkCode;
    TWPEdit *EditWorkPhone;
    TWPEdit *EditStreet;
    TWPEdit *EditRoom;
    TWPEdit *EditMailCity;
    TWPEdit *EditMailProvince;
    TWPEdit *EditPostal;
    TWPEdit *EditDate;
    TCheckBox *CheckBoxFirst;
    TCheckBox *CheckBoxReplace;
    TCheckBox *CheckBoxName;
    TCheckBox *CheckBoxStatus;
    TCheckBox *CheckBoxOther;
    void __fastcall CheckBoxFirstClick(TObject *Sender);
    void __fastcall CheckBoxMaleClick(TObject *Sender);
    void __fastcall CheckBoxSINNoClick(TObject *Sender);
    void __fastcall CheckBoxCitizenClick(TObject *Sender);
private:	// User declarations
    void virtual PostLoad(void);
    bool virtual BeforeSave(void);
    void virtual PostSave(void);
    TDateTime virtual getDate(void); // get from DT put on Form
    void virtual putDate(void); // get from From and put to DT
    void Init(void);
public:		// User declarations
    __fastcall TNAS2120B(TComponent* Owner);
};
//---------------------------------------------------------------------------
// extern PACKAGE TFormApp *FormApp;
//---------------------------------------------------------------------------
#endif
