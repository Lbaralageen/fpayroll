//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "TFormDB.h"

#include "Tprofile.h"


dataPerson person;
dataCompany company;

//---------------------------------------------------------------------------
String dataPerson::FullName(void)
{
    return FirstName + " " + MiddleName + " " + LastName;
}
//---------------------------------------------------------------------------
String dataPerson::getSIN()
{
   char str[20];
   return String(ltoa(SIN, str, 10));
}
//---------------------------------------------------------------------------
void dataCompany::SaveToDB()
{
    String StartPeriod =  getFDate(Start);
    if( ID > 0 ) // we have to update person
    {
        try
        {
           String SQLcommand = String("UPDATE Company SET ") +
           "Name = '" + IncName + "', " +
           "Trade = '" + TradeName + "', " +
           "Certificate = '" + CertName + "', " +
           "Stateman = '" + Position + "', " +
           "Saleman = '" + SaleName + "', " +
           "Phone = '" + Phone + "', " +
           "FirstName = '" + FirstName + "', " +
           "LastName = '" + LastName + "', " +
           "PhonePerson = '" + PhonePerson + "', " +
           "StreetMail = '" + Mail_Street + "', " +
           "CityMail = '" + Mail_City + "', " +
           "ProvinceMail = '" + Mail_Province + "', " +
           "CountyMail = '" + Mail_County + "', " +
           "IndexMail = '" + Mail_Index + "', " +
           "PhoneMail = '" + Mail_Telephone + "', " +
           "FaxMail = '" + Mail_Fax + "', " +
           "StreetBus = '" + Bus_Street + "', " +
           "CityBus = '" + Bus_City + "', " +
           "ProvinceBus = '" + Bus_Province + "', " +
           "CountyBus = '" + Bus_County + "', " +
           "IndexBus = '" + Bus_Index + "', " +
           "PhoneBus = '" + Bus_Telephone + "', " +
           "FaxBus = '" + Bus_Fax + "', " +
           "Federal = '" + Federal + "', " +
           "Provincial = '" + Provincial + "', " +
           "Payroll = " + String(Payroll) + ", " +
           "GST = " + String(GST) + ", " +
           "PST = " + String(PST) + ", " +
           "Health = " + String(HealthTax) + ", " +
           "Cfty = " + String(HealthSfty) + ", " +
           "StartPeriod = " + StartPeriod + ", " +
           "IndexPeriod = " + String(select) +
           " WHERE ID = " + String(ID) + ";";
           base->RunSQL( SQLcommand );
        }
        catch(...){}
     }else
     {   // otherwise add new record
        try
        {
           String ID = base->MaxID(ATTR_TAG_Person) + 1L;
           String SQLcommand = "INSERT INTO " + String(ATTR_TAG_Company) + " (";
           vecxml lst = dom->Select(NODE_TAG_Database)->FindName(ATTR_TAG_Remote)->FindName(ATTR_TAG_Company)->Select(NODE_TAG_Field);
           for(int i = 0; i < (int)lst.size(); i++)
             SQLcommand += lst[i]->atSName + ", ";
           SQLcommand[ SQLcommand.Length() - 1 ] = ')';
           SQLcommand += " VALUES (" +
           ID + ", '" +
           IncName + "', '" +
           TradeName + "', '" +
           CertName + "', '" +
           Position + "', '" +
           SaleName + "', '" +
           Phone + "', '" +
           FirstName + "', '" +
           LastName + "', '" +
           PhonePerson + "', '" +
           Mail_Street + "', '" +
           Mail_City + "', '" +
           Mail_Province + "', '" +
           Mail_County + "', '" +
           Mail_Index + "', '" +
           Mail_Telephone + "', '" +
           Mail_Fax + "', '" +
           Bus_Street + "', '" +
           Bus_City + "', '" +
           Bus_Province + "', '" +
           Bus_County + "', '" +
           Bus_Index + "', '" +
           Bus_Telephone + "', '" +
           Bus_Fax + "', '" +
           Federal + "', '" +
           Provincial + "', " +
           String(Payroll) + ", " +
           String(GST) + ", " +
           String(PST) + ", " +
           String(HealthTax) + ", " +
           String(HealthSfty) + ", " +
           StartPeriod + ", " +
           String(select) + ") ;";

           base->RunSQL( SQLcommand );
        }
        catch(...){}
     }
}
//---------------------------------------------------------------------------
void dataPerson::SaveToDB()
{
    WORD year, month, day;
    DecodeDate(Birth, year, month, day);

    if( ID > 0 ) // we have to update person
    {
        try
        {
           String SQLcommand = String("UPDATE Person SET ") +
           "ID = " + String(ID) + ", " +
           "Name = '" + FirstName + "', " +
           "Middle = '" + MiddleName + "', " +
           "Last_Name = '" + LastName + "', " +
           "SIN = " + getSIN() + ", " +
           "Sex = " + String(Sex?1:0) + ", " +
           "BirthDay = " + String(day) + ", " +
           "BirthMonth = " + String(month) + ", " +
           "BirthYear = " + String(year) + ", " +
           "Street = '" + Street + "', " +
           "City = '" + City + "', " +
           "Province = '" + Province + "', " +
           "County = '" + County + "', " +
           "Post_Box = '" + Index + "', " +
           "Phone_Home = '" + PhoneHome + "', " +
           "Fax = '" + Fax + "', " +
           "Phone_Work = '" + PhoneWork + "' " +
           "WHERE ID = " + String(ID) + ";";
           base->RunSQL( SQLcommand );
        }
        catch(...){}
     }else
     {   // otherwise add new record
        try
        {
           String ID = base->MaxID(ATTR_TAG_Person) + 1L;
            char str[20];
           String sin = ltoa(SIN, str, 10);
           String SQLcommand = "INSERT INTO " + String(ATTR_TAG_Person) +
           " (ID, Name, Middle, Last_Name, SIN, Sex, BirthDay, BirthMonth,  BirthYear, Street, City, Province, County, Post_Box, Phone_Home, Fax, Phone_Work ) VALUES (" +
           ID + ", '" +
           FirstName  + "', '" +
           MiddleName  + "', '" +
           LastName  + "', '" +
           sin  + "', " +
           String(Sex?1:0)  + ", " +
           String(day)  + ", " +
           String(month)  + ", " +
           String(year)  + ", '" +
           Street  + "', '" +
           City  + "', '" +
           Province  + "', '" +
           County  + "', '" +
           Index  + "', '" +
           PhoneHome  + "', '" +
           Fax  + "', '" +
           PhoneWork  + "');";

           base->RunSQL( SQLcommand );
        }
        catch(...){}
     }
}
//---------------------------------------------------------------------------
String dataCompany::CheckData()
{
    String result;
    if( IncName.IsEmpty() )
        return "Incorporation Name is empty!";

    if( TradeName.IsEmpty() ) TradeName = " ";
    if( CertName.IsEmpty() ) CertName = " ";
    if( Position.IsEmpty() ) Position = " ";
    if( SaleName.IsEmpty() ) SaleName = " ";
    if( Phone.IsEmpty() ) Phone = " ";
    if( FirstName.IsEmpty() ) FirstName = " ";
    if( LastName.IsEmpty() ) LastName = " ";
    if( PhonePerson.IsEmpty() ) PhonePerson = " ";

    if( Mail_Street.IsEmpty() ) Mail_Street = " ";
    if( Mail_Province.IsEmpty() ) Mail_Province = " ";
    if( Mail_County.IsEmpty() ) Mail_County = " ";
    if( Mail_City.IsEmpty() ) Mail_City = " ";
    if( Mail_Index.IsEmpty() ) Mail_Index = " ";
    if( Mail_Telephone.IsEmpty() ) Mail_Telephone = " ";
    if( Mail_Fax.IsEmpty() ) Mail_Fax = " ";

    if( Bus_Street.IsEmpty() ) Bus_Street = " ";
    if( Bus_Province.IsEmpty() ) Bus_Province = " ";
    if( Bus_County.IsEmpty() ) Bus_County = " ";
    if( Bus_City.IsEmpty() ) Bus_City = " ";
    if( Bus_Index.IsEmpty() ) Bus_Index = " ";
    if( Bus_Telephone.IsEmpty() ) Bus_Telephone = " ";
    if( Bus_Fax.IsEmpty() ) Bus_Fax = " ";

    if( Federal.IsEmpty() ) Federal = " ";
    if( Provincial.IsEmpty() ) Provincial = " ";
    return result;
}
//---------------------------------------------------------------------------
String dataPerson::CheckData()
{
    String result;

    if( FirstName.IsEmpty() )
        return "First name is empty!";
    if( !CheckSIN(SIN) )
        return "SIN is wrong!";

    // address
    if( Street.IsEmpty() )
        Street = " ";
    if( Province.IsEmpty() )
        Province = " ";
    if( County.IsEmpty() )
        County = " ";
    if( City.IsEmpty() )
        City = " ";
    if( Index.IsEmpty() )
        Index = " ";
    if( Fax.IsEmpty() )
        Fax = " ";
    if( PhoneHome.IsEmpty() )
        PhoneHome = " ";
    if( PhoneWork.IsEmpty() )
        PhoneWork = " ";
    return result;
}
//---------------------------------------------------------------------------
void dataCompany::Clear(void)
{
    ID = -1;
    TradeName = " ";
    CertName = " ";
    Position = " ";
    SaleName = " ";
    Phone = " ";
    Mail_Street = " ";
    Mail_Province = " ";
    Mail_County = " ";
    Mail_City = " ";
    Mail_Index = " ";
    Mail_Telephone = " ";
    Mail_Fax = " ";
    Bus_Street = " ";
    Bus_Province = " ";
    Bus_County = " ";
    Bus_City = " ";
    Bus_Index = " ";
    Federal = " ";
    Provincial = " ";
    Start = Now();
    select = 0;
}
//---------------------------------------------------------------------------
void dataPerson::Clear(void)
{
    ID = -1;
    FirstName = " ";
    LastName = " ";
    MiddleName = " ";
    SIN = 0L;
    // address
    Street = " ";
    Province = " ";
    County = " ";
    City = " ";
    Index = " ";
    Fax = " ";
    PhoneHome = " ";
    PhoneWork = " ";
    Birth = Now();
}
//---------------------------------------------------------------------------


