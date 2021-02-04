//---------------------------------------------------------------------------

#ifndef StaffH
#define StaffH

extern WORD get_crc_16( WORD crc, char *buf, int size );
extern String replace(String src, char from, char to);
extern bool PathExists(String path);
extern String DelSymbol(String path, char chr);
extern void CopyPaths(String PathFrom, String PathTo, int iAttributes);
extern String DelLastSlash(String path);
extern String CreateNewDirIn(String path);

//---------------------------------------------------------------------------
#endif
