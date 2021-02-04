//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop



//---------------------------------------------------------------------------
USERES("PayRoll.res");
USEFORM("TMain.cpp", FormMain);
USEFORM("TMidi.cpp", FChild);
USEFORM("About.cpp", AboutBox);
USEUNIT("Staff.cpp");
USEUNIT("XMLclass.cpp");
USEFORM("TPayment.cpp", FPayment);
USEFORM("TTaxProp.cpp", FTaxProp);
USEFORM("TFNew.cpp", FormNew);
USEFORM("F11076.cpp", T11076);
USEUNIT("FormListCall.cpp");
USEFORM("TFrameDB.cpp", FrameDB); /* TFrame: File Type */
USEUNIT("ParseString.cpp");
USEFORM("TProfile.cpp", TSetupProfile);
USEFORM("TFOpen.cpp", FormOpen);
USEFORM("TEmpl.cpp", TEmploees);
USEFORM("TFormDB.cpp", base);
USEUNIT("VBaseStaff.cpp");
USEFORM("FGST34a.cpp", TGST34a);
USEFORM("TFormEdit.cpp", FormEdit);
USEUNIT("IPerson.cpp");
USERES("wmf.RES");
USEFORM("FNAS2120B.cpp", NAS2120B);
USEFORM("Screen.cpp", FormScreen);
USEUNIT("Fprint.cpp");
USEUNIT("FMidiDB.cpp");
USEUNIT("FMidProc.cpp");
USEUNIT("FMidiEvent.cpp");
USEFORM("TFEmail.cpp", FEmail);
//---------------------------------------------------------------------------
#include "TMain.h"

TXobj *dom = NULL;
TXobj *prj = NULL;
String GlobalPath;
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  ShortDateFormat = "MM/dd/yyyy";
  LongDateFormat = "MM/dd/yyyy";
  DateSeparator = '/';
  ShortTimeFormat = "hh:mm:ss";
  char *ptr = &DecimalSeparator; *ptr = '.';
  GlobalPath = ExtractFilePath(_argv[0]);

    try{
        dom = new TXobj(GlobalPath + "ibm.xml");
        prj = new TXobj(GlobalPath + "forms.xml");
    }
    catch (Exception &exception){ return 1; }

	Application->Initialize();
	Application->HelpFile = GlobalPath + "Iform.hlp";

         Application->Title = "IForms";
         Application->CreateForm(__classid(TFormMain), &FormMain);
         Application->CreateForm(__classid(TAboutBox), &AboutBox);
         Application->CreateForm(__classid(Tbase), &base);
         Application->CreateForm(__classid(TFormScreen), &FormScreen);
         Application->Run();

	return 0;
}
//---------------------------------------------------------------------------
