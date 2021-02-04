//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ImgList.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TButton *OKButton;
	TImage *ProgramIcon;
	TLabel *LabelProductName;
	TLabel *LabelCopyright;
	TLabel *LabelMail;
	TLabel *LabelWeb;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *LabelDate;
	TImageList *LogoImages;
	TTimer *LogoTimer;
	TGroupBox *GroupBox1;
	TLabel *LabelName1;
	TLabel *LabelCompany1;
	TLabel *LabelSN1;
	TLabel *LabelName;
	TLabel *LabelCompany;
	TLabel *LabelSN;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LabelWebClick(TObject *Sender);
	void __fastcall LabelMailClick(TObject *Sender);
	
private:
public:
	virtual __fastcall TAboutBox(TComponent *Owner);
	void UpdateInfo(void);
};
//----------------------------------------------------------------------------
extern TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif	
