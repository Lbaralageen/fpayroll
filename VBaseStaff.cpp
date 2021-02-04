//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <systdate.h>
#include "TMain.h"
#include "TFormDB.h"

//---------------------------------------------------------------------------
struct DataSQL
{
	unsigned short year;
	unsigned char month;
	unsigned char day;
};
struct tims
{
    union
    {
        DataSQL     Fdata;
        long Ldata;
    }val;
};
//------------------------------------------------------
long getFDate(TDateTime dta)
{
	unsigned short year, month, day;
	dta.DecodeDate(&year, &month, &day);
	long dts = getFDate(year, month, day);
	return dts;
}
//------------------------------------------------------
long getFDate(String dtstring)
{
    if( dtstring.Trim().IsEmpty() || dtstring == "0" )
        return 0L;
    TDateTime dta = StrToDate(dtstring);
	unsigned short year, month, day;
	dta.DecodeDate(&year, &month, &day);
	long dts = getFDate(year, month, day);
	return dts;
}
//------------------------------------------------------
long getFDate(unsigned short year, unsigned short month, unsigned short day)
{
	DataSQL val;
	val.day = day;
	val.month = month;
	val.year = year;

	tims vl;
	vl.val.Fdata = val;

	return vl.val.Ldata;
}
//------------------------------------------------------
TDateTime getFDate(long dta)
{
	try
	{
	  if( dta > 0 )
	  {
		tims vl;
		vl.val.Ldata = dta;
		DataSQL val = vl.val.Fdata;
		unsigned short month = (unsigned short)val.month;
		unsigned short day = (unsigned short)val.day;
        if( day == 0 || month == 0 || val.year == 0 )
    		return Now();
        else
    		return EncodeDate( val.year, month, day );
	  }else
		  return Now();
	}catch(...){return Now();}
}
//---------------------------------------------------------------------------
// remove files from directory
bool RemoveDirFiles(String _dirName, bool _removeDir)
{
	TSearchRec sr;
	String mask;
	String dirName = _dirName;

	if(dirName[dirName.Length()] != '\\')
		mask = dirName + String("\\*.*");
	else
		mask = dirName + String("*.*");

	if(dirName[dirName.Length()] != '\\')
		dirName += '\\';


	if( FindFirst(mask, faDirectory, sr) == 0)
		do {
			String fName = dirName + sr.Name;
			if( sr.Name != "." &&  sr.Name != "..")
				remove( fName.c_str() );
		} while ( FindNext(sr) == 0 );

	if(_removeDir)
		RemoveDir(_dirName);	// NOTE : _dirName (not dirName)

	return (true);
}
//---------------------------------------------------------------------------
long __fastcall TFormMain::NumOfTable(String TableName, String term)
{
    TADOQuery *qr = base->RemoteQuery;
    String sql = "SELECT COUNT(*) AS tempCount FROM "+ TableName + " " + term + ";";
    qr->Close();
    qr->SQL->Clear();
    qr->SQL->Add( sql.c_str() );
    qr->Open();
    return (long)qr->FieldByName("tempCount")->AsInteger;
}
//---------------------------------------------------------------------------
bool __fastcall Tbase::_Query(TADOQuery *qr, String Query)
{
   if( Query == NULL || Query.IsEmpty() )
       return false;
   try
   {
     qr->Close();
     qr->SQL->Clear();
     qr->SQL->Add( Query );
     qr->Open();
     qr->First();
   }
   catch(...){return false;}
   return true;
}
//---------------------------------------------------------------------------
long __fastcall Tbase::LQuery0(String Query, String field)
{
   long result = 0L;
   if( Query == NULL || Query.IsEmpty() )
       return result;
   _Query(RemoteQuery, Query);
   if( !RemoteQuery->Eof )
   {
      result = RemoteQuery->FieldByName(field)->AsInteger ;
   }
   RemoteQuery->Close();
   return result;
}
//---------------------------------------------------------------------------
String __fastcall Tbase::SQuery0(String Query, String field)
{
   String result = 0L;
   if( Query == NULL || Query.IsEmpty() )
       return result;
   _Query(RemoteQuery, Query);
   if( !RemoteQuery->Eof )
   {
      result = RemoteQuery->FieldByName(field)->AsString ;
   }
   RemoteQuery->Close();
   return result;
}
//---------------------------------------------------------------------------
double __fastcall Tbase::FQuery0(String Query, String field)
{
   double result = 0.0f;
   if( Query == NULL || Query.IsEmpty() )
       return result;
   _Query(RemoteQuery, Query);
   if( !RemoteQuery->Eof )
   {
      result = RemoteQuery->FieldByName(field)->AsFloat ;
   }
   RemoteQuery->Close();
   return result;
}
//---------------------------------------------------------------------------
vecstr __fastcall Tbase::SQuery(String Query, String field)
{
   vecstr result;
   if( Query == NULL || Query.IsEmpty() )
       return result;
//   GetFieldNames(const AnsiString TableName, Classes::TStrings* List);
   _Query(RemoteQuery, Query);
   for(; !RemoteQuery->Eof ; RemoteQuery->Next())
        result.push_back( RemoteQuery->FieldByName(field)->AsString );
   RemoteQuery->Close();
   return result;
}
//---------------------------------------------------------------------------
vecflt __fastcall Tbase::FQuery(String Query, String field)
{
   vecflt result;
   if( Query == NULL || Query.IsEmpty() )
       return result;
   _Query(RemoteQuery, Query);
   for(; !RemoteQuery->Eof ; RemoteQuery->Next())
        result.push_back( RemoteQuery->FieldByName(field)->AsFloat );
   RemoteQuery->Close();
   return result;
}
//---------------------------------------------------------------------------
long __fastcall Tbase::MaxNumber(TADOQuery *qr, String field, String table, String where)
{
   long maxnum = 0;
   try
   {
       where = where.IsEmpty() ? String("") : String(" WHERE " + where);
       String sql = "SELECT " + field + " FROM "+ table + where + ";";
       _Query(qr, sql);
       if( !qr->Eof )
       {
         sql = "SELECT Max(" + field + ") AS tempCount FROM "+ table + where + ";";
         _Query(qr, sql);
         maxnum = qr->FieldByName("tempCount")->AsInteger;
       }
       qr->Close();
   }
   catch(...){return 0L;}
   return maxnum;
}









