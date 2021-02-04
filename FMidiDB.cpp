
//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"

#include "TMidi.h"

//---------------------------------------------------------------------------

String TFChild::readMoney(TXelm *record, String val)
{
    assert( record );
    String result;
    try
    {
      if( record->atType == ATTR_TAG_MONEY )
      {
          double vl = atof( val.c_str() );
          long whole = (long)vl;
          double drop =  vl - (double)whole;
          if( whole == 0L )
              result = "";
          else
              result = whole;
          int dp = ceil(1000.0 * drop);
          dp /= 10;
          if( dp == 0 )
              NextEdit(record)->Text = "";
          else
          {
              if( dp < 10 )
                  NextEdit(record)->Text = String("0") + dp;
              else
                  NextEdit(record)->Text = dp;
          }
      }
   }catch(...){}
   return result;
}

//---------------------------------------------------------------------------
void __fastcall TFChild::LoadFromDB(long _id)
{

      Clear();
      TADOQuery *qr = base->RemoteQuery;
      try
      {
        TXelm *elm = node;
        if( node->Parent->NodeName ==  NODE_TAG_Group )
            elm = node->Parent;
         String SQLcommand = "SELECT * FROM " + elm->atSName + " WHERE ID="+String(_id)+";";
         base->_Query(qr, SQLcommand);
         vecxml lst = node->Select(NODE_TAG_Field);
         if( !qr->Eof )
         {
              long ID = qr->FieldByName("ID")->AsInteger;
              NameRecord = qr->FieldByName("Short_Name")->AsString;
              long _date = qr->FieldByName("DT")->AsInteger;
              if( _date > 0L )
                  DT = getFDate(_date);

              for(int j = 0; j < (int)lst.size(); j++)
                 for(int i = 0; i < (int)lstRect.size(); i++)
                 {
                    try
                    {
                      if( lst[j]->atName == lstRect[i].getName() )
                      {
                          String FieldName = lst[j]->atName.Trim();
                          if( lst[j]->getAttr(ATTR_TAG_Database) == ATTR_TAG_No )
                              continue;
                          String val = qr->FieldByName(FieldName)->AsString.Trim();
                          if( lstRect[i].edit )
                          {

                                if( lst[j]->atType == ATTR_TAG_PHONE || lst[j]->atType == ATTR_TAG_MONEY )
                                {
                                  if( val == "0" )
                                      val = "";
                                  if( lst[j]->atType == ATTR_TAG_MONEY )
                                        val = readMoney(lst[j], val);
                                }else if( lst[j]->atType == ATTR_TAG_DATE )
                                {
                                  long dts = atol(val.c_str());
                                  if( dts > 0L )
                                      val = getFDate( dts ).FormatString("MM/dd/yyyy");
                                  else
                                      val = "";
                                }

                                lstRect[i].edit->Text = val;
                          }else if( lstRect[i].box )
                              lstRect[i].box->Checked = val == "True"?true:false;
                          break;
                      }
                     }catch(...){}
                 }
         }
      }
      catch(...){
          Clear();
          NameRecord = "";
      }
     qr->Close();

     getDate(); // get from DT put on Form
     PostLoad();
}
//---------------------------------------------------------------------------
void TFChild::Save(void)
{
    putDate(); // get from From and put to DT
    if( NameRecord.IsEmpty() )
        SaveAs();
    else
	{
	  TrashForm(NameRecord, true); // make copy of document is first
	  try
	  {
		  InsertForm(NameRecord);
          DeleteForm(NameRecord, true); // delete copy of document
	  }catch(...)
	  {
		  TrashForm(NameRecord, false);
	  }
	}
}
//---------------------------------------------------------------------------
void TFChild::DeleteForm(String NameForm, bool Flag)
{
	  try
	  {
		TXelm *elm = node;
		if( node->Parent->NodeName ==  NODE_TAG_Group )
			elm = node->Parent;

         String SQLcommand = "DELETE FROM " + elm->atSName + " WHERE Short_Name='" + NameForm + "' AND Flag=" + String(Flag?"Yes":"No") + ";";
         base->RunSQL( SQLcommand );
      }
      catch(...){}
}
//---------------------------------------------------------------------------
// true - restore, false - hide
void TFChild::TrashForm(String NameForm, bool Flag)
{
	  try
	  {
		TXelm *elm = node;
		if( node->Parent->NodeName ==  NODE_TAG_Group )
			elm = node->Parent;

		 String SQLcommand = "UPDATE " + elm->atSName + " SET Flag = Yes WHERE Short_Name='" + NameForm + "';";
		 base->RunSQL( SQLcommand );
	  }
	  catch(...){}
}
//---------------------------------------------------------------------------
void TFChild::InsertForm(String NameForm)
{
      try
      {
        if( BeforeSave() )
            return;
        
        TXelm *elm = node;
        if( node->Parent->NodeName ==  NODE_TAG_Group )
            elm = node->Parent;

         String ID = base->MaxID(elm->atSName) + 1L;
		 String SQLcommand = "INSERT INTO " + elm->atSName + " (ID, Flag, Short_Name, DT ";

		vecxml lstGroup = elm->Select(NODE_TAG_Item);
		for(int k = 0; k <= lstGroup.size(); k++)
		{
			if( k == lstGroup.size() && lstGroup.size() > 0 )
				break;
			TXelm *elm = node;
			if( lstGroup.size() > 0 )
				elm = lstGroup[k];
			vecxml lst = elm->Select(NODE_TAG_Field);
			for(int i = 0; i < (int)lst.size(); i++)
			{
			   if( lst[i]->getAttr(ATTR_TAG_Database) == ATTR_TAG_No )
					continue;
			   SQLcommand += ", " + lst[i]->atName;
			}
		}
		 SQLcommand += ") VALUES (" + ID  + ", No, '" + NameForm + "', " + String(getFDate(DT));

		for(int k = 0; k <= lstGroup.size(); k++)
		{
			if( k == lstGroup.size() && lstGroup.size() > 0 )
				break;
			TXelm *elm = node;
			if( lstGroup.size() > 0 )
				elm = lstGroup[k];

			 vecxml lst = elm->Select(NODE_TAG_Field);
			 for(int j = 0; j < (int)lst.size(); j++)
             {
                 if( lst[j]->getAttr(ATTR_TAG_Database) == ATTR_TAG_No )
                    continue;
                 for(int i = 0; i < (int)lstRect.size(); i++)
                 {
                    String val;
                    if( lstRect[i].edit )
                        val = lstRect[i].edit->Text.Trim();
                    else if( lstRect[i].box )
                        val = lstRect[i].box->Checked ? 1 : 0;

                    if( lst[j]->atName == lstRect[i].getName() )
                    {
                      if( val.IsEmpty() )
                          val = " ";

                      if( lstRect[i].edit )
                      {
                          TXelm *elm = lstRect[i].elm;
                          assert(elm);
                          String SQL = elm->getAttr(ATTR_TAG_SQL);
                          if( !SQL.IsEmpty() )
                          {
							  if( elm->atType == ATTR_TAG_PHONE && SQL != ATTR_TAG_INT )
                                SQLcommand += ", '" + val + "'";
                              else
                              {
                                if( elm->atType == ATTR_TAG_PHONE || elm->atType == ATTR_TAG_INT || elm->atType == ATTR_TAG_MONEY || elm->atType == ATTR_TAG_DATE )
                                  if( val.Trim().IsEmpty() )
                                      val = 0;
                                  else
                                  {
                                    if( elm->atType == ATTR_TAG_DATE )
                                    {
                                        SQLcommand += ", " + String(getFDate(val));
                                        break;
                                    }
                                  }
                                SQLcommand += ", " + val;
                              }
                          }else
                          {
                            if( elm->atType == ATTR_TAG_DATE )
                                SQLcommand += ", " + String(getFDate(val));
                            else
                            {
                              if( elm->getAttr(ATTR_TAG_Length) == String(1) )
                              {
                                  val = val.Trim();
                                  val = val.IsEmpty() ? 0 : 1;
                                  SQLcommand += ", " + val;

                              }else
                                  SQLcommand += ", '" + val + "'";
                            }
                          }
                      }else if( lstRect[i].box )
                      {
                              SQLcommand += ", " + val;
                      }
                      break;
                    }
                 }
             }
         }
         SQLcommand += ") ;";

         FILE *f = fopen("a.txt", "a");
         fputs(SQLcommand.c_str(), f);
         fclose(f);
         base->RunSQL( SQLcommand );

         PostSave();
      }
      catch(...){}
}
//---------------------------------------------------------------------------

