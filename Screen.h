//---------------------------------------------------------------------------

#ifndef ScreenH
#define ScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormScreen : public TForm
{
__published:	// IDE-managed Components
    TImage *Image;
    TButton *ButtonOK;
    void __fastcall ImageClick(TObject *Sender);
    void __fastcall ButtonOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormScreen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormScreen *FormScreen;
//---------------------------------------------------------------------------
#endif
