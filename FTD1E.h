//---------------------------------------------------------------------------

#ifndef FTD1EH
#define FTD1EH
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
class TTD1E : public TFChild
{
__published:	// IDE-managed Components
    TScrollBar *ScrollBarV;
    TScrollBar *ScrollBarH;
    TWPEdit *EditLastName;
    TWPEdit *EditFirstName;
    TWPEdit *EditNumber;
    TWPEdit *EditAddress1;
    TWPEdit *EditAddress2;
    TWPEdit *EditPostBox;
    TWPEdit *EditCounty;
    TWPEdit *EditSIN;
    TWPEdit *EditBirth;
    TWPEdit *EditF1;
    TWPEdit *EditF2;
    TWPEdit *EditF3;
    TWPEdit *EditF4;
    TWPEdit *EditF5;
    TWPEdit *EditF6;
    TWPEdit *EditF7;
    TWPEdit *EditF8;
    TWPEdit *EditF9;
    TWPEdit *EditF10;
    TWPEdit *EditF11;
    TWPEdit *EditF12;
    TWPEdit *EditF13;
    TWPEdit *EditF14;
    TWPEdit *EditSUM;
    TWPEdit *EditBox;
    TWPEdit *EditAddTax;
    TWPEdit *EditDate;
    void __fastcall SumFChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    void Init(void);
    __fastcall TTD1E(TComponent* Owner);
};
//---------------------------------------------------------------------------
// extern PACKAGE TFormApp *FormApp;
//---------------------------------------------------------------------------
#endif
