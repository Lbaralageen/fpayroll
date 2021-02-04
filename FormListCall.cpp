//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "TMain.h"

#include "FGST34A.h"
#include "FTD1E.h"
#include "FNAS2120B.h"
#include "F11076.h"
#include "FPRO336.h"


//---------------------------------------------------------------------------
void __fastcall TFormMain::CallForm(TXelm *page, long _id, String _caption)
{
    CloseMenu->Enabled = true;
    CloseAll->Enabled = true;
    ClearMenu->Enabled = true;
    InitializeMenu->Enabled = true;
    PrintMenu->Enabled = true;
    PrintAll->Enabled = true;

      BitBtnClear->Enabled = true;
      BitBtnInit->Enabled = true;
      ButtonPrint->Enabled = true;


    assert(page);
    String ID = page->getAttr(ATTR_TAG_ID);
    if( ID.IsEmpty() )
    {
        ShowMessage("This Form doesn't have ID!");
        return;
    }
    TFChild *ptr = NULL;
    if( !CheckForm(ID) )
    {
        switch(ID.ToInt())
        {
            case FR_GST34A :
            {
                TTGST34a *fptr = new TTGST34a(this);
                fptr->Execute(page, _id);
                ptr = (TFChild *)fptr;
            } break;
            case FR_11076 :
            {
                TT11076 *fptr = new TT11076(this);
                fptr->Execute(page, _id);
                ptr = (TFChild *)fptr;
            } break;
/*
            case FR_TD1E :
            {
                TTD1E *fptr = new TTD1E(this);
                fptr->Execute(page, _id);
                ptr = (TFChild *)fptr;
            } break;
*/            
            case FR_NAS2120B :
            {
                TNAS2120B *fptr = new TNAS2120B(this);
                fptr->Execute(page, _id);
                ptr = (TFChild *)fptr;
            } break;
/*
            case FR_PRO336 :
            {
                TTPRO336 *fptr = new TTPRO336(this);
                fptr->Execute(page, _id);
                ptr = (TFChild *)fptr;
            } break;
*/
        }
        ptr->Caption = _caption;
        RegisterForm(ID, ptr);
    }else
    {
        TFChild *ptr = getForm(ID);
        ptr->SetFocus();
        ptr->WindowState = wsNormal;
    }
}
//---------------------------------------------------------------------------
static int f_counter = 0;
void TFormMain::RegisterForm(String obj, TFChild *form)
{
    String _obj;
    if( obj.IsEmpty() )
        _obj = form->Caption;
    else
        _obj = obj;
    if( !CheckForm(_obj) )
    {
        if( !obj.IsEmpty() )
        {
          f_counter++; // increase number register of forms
          _obj = String(f_counter) + "_" + obj;
        }
        ListForms[_obj] = form;

        TMenuItem *Item = NewItem(form->Caption, 0, false, true, OpenWindowsMenu, 0, "Win_" + _obj);
        Item->Tag = (long)form;
        WindowMenu->Add( Item );
    }
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
