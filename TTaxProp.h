//---------------------------------------------------------------------------

#ifndef TTaxPropH
#define TTaxPropH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TMidi.h"
//---------------------------------------------------------------------------
class TFTaxProp : public TFChild
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *Edit1;
    TLabel *Label2;
    TEdit *Edit2;
    TLabel *Label3;
    TEdit *Edit3;
    TLabel *Label4;
    TEdit *Edit4;
    TLabel *Label5;
    TEdit *Edit5;
private:	// User declarations
public:		// User declarations
    __fastcall TFTaxProp(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TFTaxProp *FTaxProp;
//---------------------------------------------------------------------------
#endif
