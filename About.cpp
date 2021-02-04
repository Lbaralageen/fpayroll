//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//--------------------------------------------- ------------------------
#ifndef _INC_SHELLAPI
#include <shellapi.h>
#endif
//---------------------------------------------------------------------------
#include "About.h"
//#include "VersionKey.hpp"
//#include "UnsatIni.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
	LogoTimer->Enabled = true;
	LabelDate->Caption = String(__DATE__);
	LabelProductName->Caption = "IFORMS"; //UNSATINI::RES_PRODUCT_NAME();
	LabelCopyright->Caption = "2001 TSW"; //UNSATINI::RES_LEGAL_COPYRIGHT();
}
/*
//---------------------------------------------------------------------------
void __fastcall TAboutBox::LogoTimerTimer(TObject *Sender)
{
	static int index = 0;

	int w = LogoImages->Width;
	int h = LogoImages->Height;
	int logoCount = LogoImages->Count;
	Graphics::TBitmap * Image = new Graphics::TBitmap;

	if( index == logoCount )
		index = 0;

	LogoImages->GetBitmap(index, Image);
//	ImageLogo->Picture->Assign( Image );
	index++;

	HDC DC1 = GetDC(Panel1->Handle);
	HDC DC2 = CreateCompatibleDC(0);	SelectObject(DC2, Image->Handle);
	BitBlt(DC1, ProgramIcon->Left, ProgramIcon->Top, w, h, DC2, 0, 0, SRCCOPY);
	ReleaseDC(Panel1->Handle, DC1);
	DeleteDC(DC2);

	delete Image;

}
*/
//---------------------------------------------------------------------------
void __fastcall TAboutBox::LabelWebClick(TObject *Sender)
{
	int result = (int)ShellExecute(0, "open", "http://www.ecomcanada.net",
		"", "", SW_SHOWNORMAL);

	if( result <= 32 )
		ShowMessage("Unable to start web browser.");
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::LabelMailClick(TObject *Sender)
{
	int result = (int)ShellExecute(0, "open", "mailto:tsw@ecomcanada.net",
		"", "", SW_SHOWNORMAL);

	if( result <= 32 )
		ShowMessage("Unable to start mail client.");
}
//---------------------------------------------------------------------------
void TAboutBox::UpdateInfo(void)
{
//	TForm * mf = Application->MainForm;
}
//---------------------------------------------------------------------------
