//---------------------------------------------------------------------------

#ifndef F11076H
#define F11076H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "WPDefs.hpp"
#include "WPPrint.hpp"
#include "WPRich.hpp"
#include "WpWinCtr.hpp"

#include "TMidi.h"
//---------------------------------------------------------------------------

class TT11076 : public TFChild
{
__published:	// IDE-managed Components
    TWPEdit *EditMYear;
    TWPEdit *EditStreet;
    TWPEdit *EditRoom;
    TWPEdit *EditCity;
    TWPEdit *EditProvince;
    TWPEdit *EditPostal;
    TWPEdit *EditNameBirth;
    TWPEdit *EditBirthDay;
    TWPEdit *EditBirthMonth;
    TWPEdit *EditBirthYear;
    TWPEdit *EditBirthPlace;
    TWPEdit *EditBirthSex;
    TWPEdit *EditBirthFather;
    TWPEdit *EditBirthMother;
    TWPEdit *EditBirthOtherName;
    TWPEdit *EditBirth1;
    TWPEdit *EditBirth2;
    TWPEdit *EditBirth3;
    TWPEdit *EditMName;
    TWPEdit *EditMBride;
    TWPEdit *EditMOther;
    TWPEdit *EditMDay;
    TWPEdit *EditMMonth;
    TWPEdit *EditMPlace;
    TWPEdit *EditM1;
    TWPEdit *EditM2;
    TWPEdit *EditM3;
    TWPEdit *EditDeathName;
    TWPEdit *EditDeathDay;
    TWPEdit *EditDeathMonth;
    TWPEdit *EditDeathYear;
    TWPEdit *EditDeathSex;
    TWPEdit *EditDeathAge;
    TWPEdit *EditDeathPlace;
    TWPEdit *EditDeathHusband;
    TWPEdit *EditDeathFather;
    TWPEdit *EditDeathMother;
    TWPEdit *EditDeath1;
    TWPEdit *EditDeath2;
    TWPEdit *EditFeeName;
    TWPEdit *EditFeeCard;
    TWPEdit *EditFeeDate;
    TWPEdit *EditWhy;
    TWPEdit *EditWhat;
    TWPEdit *EditDay;
    TWPEdit *EditMonth;
    TWPEdit *EditYear;
    TWPEdit *EditCodeHome;
    TWPEdit *EditWorkPhone;
    TWPEdit *EditTotal;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TWPEdit *EditPhoneHome;
    TWPEdit *EditCodeWork;
    TWPEdit *EditName;
    void __fastcall CheckBox1Click(TObject *Sender);
public:		// User declarations
    void virtual PostLoad(void);
    bool virtual BeforeSave(void);
    void virtual PostSave(void);
    
    TDateTime virtual getDate(void); // get from DT put on Form
    void virtual putDate(void); // get from From and put to DT
    void Init(void);
    __fastcall TT11076(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
