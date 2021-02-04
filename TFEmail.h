//---------------------------------------------------------------------------

#ifndef TFEmailH
#define TFEmailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WPDefs.hpp"
#include "WPPrint.hpp"
#include "WPRich.hpp"
#include "WpWinCtr.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFEmail : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel3;
    TPanel *Panel4;
    TButton *ButtonClose;
    TPanel *Panel5;
    TButton *ButtonSet;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TGroupBox *GroupBox1;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TRadioButton *RadioButton3;
    TEdit *EditAddress;
    TEdit *EditSubject;
    TLabel *Label3;
    TWPRichText *WPRichText1;
private:	// User declarations
public:		// User declarations
    int Execute(void);
    __fastcall TFEmail(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEmail *FEmail;
//---------------------------------------------------------------------------
#endif
