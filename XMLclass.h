//---------------------------------------------------------------------------

#ifndef XMLclassH
#define XMLclassH

#include <assert.h>
#include <dir.h>
#include <vector>
#include <map>

#include "XmlObjModel.hpp"
#include "XmlParser.hpp"
#include "Xml_Def.h"
//---------------------------------------------------------------------------
using namespace std;

class TXelm;

typedef vector<TXelm *> vecxml;
typedef map<long, TXelm *> mapxml;
typedef vector<String>  vecstr;
typedef vector<float>  vecflt;

class TXobj;

class TXelm : public TXmlElement
{
private:
  String getAttrDefaultTag(void){ return getAttr(ATTR_TAG_Default); }
  String getAttrTypeTag(void){ return getAttr(ATTR_TAG_Type); }
  String getAttrNameTag(void){ return getAttr(ATTR_TAG_Name); }
  void setAttrNameTag(String val){ SetAttribute(ATTR_TAG_Name, val); }
  String getAttrSNameTag(void){ return getAttr(ATTR_TAG_Short_Name); }
  void setAttrSNameTag(String val){ SetAttribute(ATTR_TAG_Short_Name, val); }
  String getAttrSIDTag(void){ return getAttr(ATTR_TAG_SID); }
  void setAttrSIDTag(String val){ SetAttribute(ATTR_TAG_SID, val); }
  String getAttrIDTag(void){ return getAttr(ATTR_TAG_ID); }
  void setAttrIDTag(String val){ SetAttribute(ATTR_TAG_ID, val); }
  String getAttrSQLTag(void){ return getAttr(ATTR_TAG_SQL); }
  void setAttrSQLTag(String val){ SetAttribute(ATTR_TAG_SQL, val); }
  TXelm * __fastcall rootDoc(void){ return (TXelm *)OwnerDocument->DocumentElement; }
public :
  String  getAttr(String arg);
  void  setAttr(String arg, String value){SetAttribute(arg, value);}
//  String operator [] (String name) { return getAttr(name);}
  TXelm *AddChild(String teg);
  TXelm *AddChild(TXelm *nodeChild);
  void Delete(TXelm *node);
  void Delete(String item); // delete all nodes 'item' from current node
  TXelm *Node(String Anode);
  TXelm *TreeFindID(String id);
  TXelm *TreeFindName(String AttrName);
  TXelm *FindName(String AttrName);
  TXelm *FindSName(String AttrName);
  TXelm *FindName(String item, String AttrName);
  vecxml Select(String nodeName);
  map<long, String> SelectIDName(String nodeName);
  map<String, long> SelectNameID(String nodeName);
  vecxml Select(String nodeParent, String nodeChildren);
  TXelm * Select0(String nodeName);
  TXelm *ParentND(void){return (TXelm *)ParentNode;}
//	__property String Attr = {read=getAttr, write=setAttr, nodefault};
	__property TXelm *Parent = {read=ParentND, nodefault};
	__property String atName = {read=getAttrNameTag, write=setAttrNameTag, nodefault};
	__property String atSName = {read=getAttrSNameTag, write=setAttrSNameTag, nodefault};
	__property String atSID = {read=getAttrSIDTag, write=setAttrSIDTag, nodefault};
	__property String atID = {read=getAttrIDTag, write=setAttrIDTag, nodefault};
	__property String atSQL = {read=getAttrSQLTag, write=setAttrSQLTag, nodefault};
	__property String atType = {read=getAttrTypeTag, nodefault};
	__property String atDefault = {read=getAttrDefaultTag, nodefault};

	__property TXelm * root = {read=rootDoc, nodefault};

  __fastcall TXelm() : TXmlElement() {};
  __fastcall virtual ~TXelm(void){}
};


class TXobj : public TXmlObjModel
{
private:
  bool CreateFile(String fName);
  TXelm * __fastcall rootDoc(void){ return (TXelm *)Document->DocumentElement; }
  String __fastcall getFilePath(void){return ExtractFilePath(File);}
  String __fastcall getFile(void){return _file;}
  String _file; // full path to the real file
  TXelm * __fastcall getProject(void){return Select(NODE_TAG_Project);}
public :
  TXelm * __fastcall Select(String nodeName);
  __property TXelm *Project = {read=getProject, nodefault};
	__property String File = {read=getFile, nodefault};
	__property String Path = {read=getFilePath, nodefault};
  __property TXelm * root = {read=rootDoc, nodefault};
  __fastcall void Save(){SaveToFile(File);}
  __fastcall TXobj(String FileName);
  __fastcall virtual ~TXobj(void){Save();}
};
// cloning from one XML object to other
extern TXelm *Clone(TXelm *child, TXelm *toParent);
extern long CRC(long crcstart, vecxml array);
extern long CRC(long crcstart, vecstr array);
extern long CRC(String _crc);
extern float vecmin(vecflt);
extern float vecmax(vecflt);
extern vecstr getListFile(String mask);

//---------------------------------------------------------------------------
#endif

