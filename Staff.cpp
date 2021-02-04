//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <dir.h>
#include <stdio.h>
#include "Staff.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
bool PathExists(String path)
{
  if( path == NULL || path.IsEmpty() )
    return false;
  bool result = false;
  TSearchRec sr;
  int iAttributes = faDirectory | faArchive;
  int idx = path.Length();
  if( path[idx] == '\\' )    // delete last limiter
    path = path.SetLength(--idx);
  for(;idx > 1; idx--)       // find last folder
    if( path[idx] == '\\' )
        break;
  String lastFolder = path.SubString(idx+1, path.Length());
  path = path.SetLength(idx) + "*.*";
  if (FindFirst(path, iAttributes, sr) == 0)
  {
    do
    {
      if((sr.Attr & iAttributes) == sr.Attr)
        if( sr.Name.AnsiCompareIC(lastFolder) == 0 )
         return true;
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
  return result;
}
//---------------------------------------------------------------------------
String replace(String src, char from, char to)
{
    for(int i = 1; i < src.Length(); i++ )
        if( src[i] == from )
            src[i] = to;
    return src;
}
//---------------------------------------------------------------------------
String DelSymbol(String path, char chr)
{
  int ps = path.Pos(chr);
  int ln = path.Length();
  if( ln < 3 )
    return path;
  if( ps > 0 )
  {
     if( ps == 1 )
        path = path.SubString(2, ln);
     else
     {
        String left  = path.SubString(1, ps-1);
        String right = path.SubString(ps+1, ln);
        path = left + right;
     }
  }
  return path;
}
//---------------------------------------------------------------------------
String DelLastSlash(String path)
{
  if( path[path.Length()] == '\\' )
    path = path.SetLength(path.Length()-1);
  return path;
}
//---------------------------------------------------------------------------
void CopyPaths(String PathFrom, String PathTo, int iAttributes)
{
  if( !PathExists(PathFrom) )
        return;
  if( PathTo[PathTo.Length()] != '\\' )
      PathTo[PathTo.Length()] = '\\';

  TSearchRec sr;
  PathFrom = DelLastSlash(PathFrom) + "\\";
  String files = PathFrom + "*.gif";
  if( !PathExists(PathTo) )
    mkdir(PathTo.c_str());
  if (FindFirst(files, iAttributes, sr) == 0)
  {
    do{
       CopyFile((PathFrom + sr.Name).c_str(), (PathTo + sr.Name).c_str(), true);
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
}
//---------------------------------------------------------------------------
String CreateNewDirIn(String path)
{
    path = DelLastSlash(path) + "\\";
    String result = path;
    char str[256];
    bool flag = true;
    WORD incrc = (int)Now();
    do
    {
      long crc = get_crc_16(incrc++, path.c_str(), path.Length() );
      sprintf(str, "%X", crc);
      result = path + str;
      if( PathExists(result) )
        continue;
      flag = !CreateDir(result);
    }while( flag );
    return result + "\\";
}
//---------------------------------------------------------------------------



