//---------------------------------------------------------------------------

#ifndef FPRO336H
#define FPRO336H
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
class TTPRO336 : public TFChild
{
__published:	// IDE-managed Components
    TScrollBar *ScrollBarV;
    TScrollBar *ScrollBarH;
    TWPEdit *EditVendor;
    TCheckBox *CheckBoxMale;
    TCheckBox *CheckBoxFemale;
    TWPEdit *Edit1;
    TWPEdit *Edit2;
    TWPEdit *Edit9;
    TWPEdit *Edit8;
    TWPEdit *Edit7;
    TWPEdit *Edit3;
    TWPEdit *Edit4;
    TWPEdit *Edit5;
    TWPEdit *Edit6;
    TWPEdit *EditPermit;
    TWPEdit *EditFrom;
    TWPEdit *EditTo;
    TWPEdit *EditDate;
    TWPEdit *EditA1;
    TWPEdit *EditA2;
    TWPEdit *EditA3;
    TWPEdit *EditA4;
    TWPEdit *EditA5;
    TWPEdit *EditA6;
    TWPEdit *EditA7;
    TWPEdit *EditA8;
    TWPEdit *EditA9;
    TWPEdit *EditA10;
    TWPEdit *EditB1;
    TWPEdit *EditB2;
    TWPEdit *EditB3;
    TWPEdit *EditB4;
    TWPEdit *EditB5;
    TWPEdit *EditB6;
    TWPEdit *EditB7;
    TWPEdit *EditB8;
    TWPEdit *EditB9;
    TWPEdit *EditB10;
    TWPEdit *EditC1;
    TWPEdit *EditC2;
    TWPEdit *EditC3;
    TWPEdit *EditC4;
    TWPEdit *EditC5;
    TWPEdit *EditC6;
    TWPEdit *EditD1;
    TWPEdit *EditD2;
    TWPEdit *EditD3;
    TWPEdit *EditD4;
    TWPEdit *EditD5;
    TWPEdit *EditD6;
    TWPEdit *EditE1;
    TWPEdit *EditE2;
    TWPEdit *EditE3;
    TWPEdit *EditE4;
    TWPEdit *EditE5;
    TWPEdit *EditE6;
    TWPEdit *EditE7;
    TWPEdit *EditE8;
    TWPEdit *EditE9;
    TWPEdit *EditE10;
    TWPEdit *EditEM;
    TWPEdit *EditF10;
    TWPEdit *EditF9;
    TWPEdit *EditF8;
    TWPEdit *EditF7;
    TWPEdit *EditF6;
    TWPEdit *EditF5;
    TWPEdit *EditF4;
    TWPEdit *EditF3;
    TWPEdit *EditF2;
    TWPEdit *EditF1;
    TWPEdit *EditG1;
    TWPEdit *EditG2;
    TWPEdit *EditG3;
    TWPEdit *EditG4;
    TWPEdit *EditG5;
    TWPEdit *EditG6;
    TWPEdit *EditG7;
    void __fastcall CheckBoxMaleClick(TObject *Sender);
    void __fastcall CheckBoxFemaleClick(TObject *Sender);
private:	// User declarations
    TDateTime virtual getDate(void); // get from DT put on Form
    void virtual putDate(void); // get from From and put to DT
    void Init(void);
public:		// User declarations
    __fastcall TTPRO336(TComponent* Owner);
};
//---------------------------------------------------------------------------
// extern PACKAGE TFormApp *FormApp;
//---------------------------------------------------------------------------
#endif
