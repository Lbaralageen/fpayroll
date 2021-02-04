//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "XMLclass.h"

extern WORD get_crc_16( WORD crc, char *buf, int size );

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TXobj::TXobj(String FileName) : TXmlObjModel(NULL)
 {
      Document->FormattedOutput = true;
      Document->RemoveAll();
      if( !LoadDataSource(FileName.c_str()) )
      {
        CreateFile(FileName);
        LoadDataSource(FileName.c_str());
      }
      _file = FileName;
 }
//---------------------------------------------------------------------------
TXelm * __fastcall TXobj::Select(String nodeName){
    TXelm *result = root->Select0(nodeName);
    if( result == NULL )
        return root->AddChild(nodeName);
    return result;
}
//---------------------------------------------------------------------------
bool TXobj::CreateFile(String fName)
{
	FILE *f = fopen(fName.c_str(), "wt");
	if( f == NULL )
		return true; // break service

	fprintf(f, "\n<root>© 2001   TSW System Provider. \n</root>\n");
	fclose(f);

	return false;
}
//---------------------------------------------------------------------------
String TXelm::getAttr(String Arg)
{
   String arg;
   try{ arg = GetAttribute(Arg); }
   catch(...){arg = "";}
   return arg;
}
//---------------------------------------------------------------------------
TXelm *TXelm::AddChild(String teg)
{
   return (TXelm *)CreateChildElement(teg);
}
//---------------------------------------------------------------------------
TXelm *TXelm::AddChild(TXelm *nodeChild)
{
   ((TXmlNode *)this)->AppendChild(nodeChild);
   return nodeChild;
}
//---------------------------------------------------------------------------
TXelm *TXelm::FindName(String AttrName)
{
    TXelm *result = (TXelm *)NULL;
    if( !(TXmlNode *)this->HasChildNodes() )
    return result;
    TXmlNodeList *vars = GetChildNodesByNodeType(ELEMENT_NODE);
    assert(vars);
    for(int i = 0; i < vars->Length; i++)
    {
        TXelm *elm = (TXelm *)vars->Item(i);
        if( elm->atName == AttrName )
        {
            result = elm;
            break;
        }
    }
    delete vars;
    return result;
}
//---------------------------------------------------------------------------
TXelm *TXelm::TreeFindID(String id)
{
    TXelm *result = (TXelm *)NULL;
    if( !(TXmlNode *)this->HasChildNodes() )
    return result;
    TXmlNodeList *vars = GetChildNodesByNodeType(ELEMENT_NODE);
    assert(vars);
    for(int i = 0; i < vars->Length; i++)
    {
        TXelm *elm = (TXelm *)vars->Item(i);
        if( elm->atID == id )
        {
            result = elm;
            break;
        }
        result = elm->TreeFindName(id);
        if( result != NULL )
            break;
    }
    delete vars;
    return result;
}
//---------------------------------------------------------------------------
TXelm *TXelm::TreeFindName(String AttrName)
{
    TXelm *result = (TXelm *)NULL;
    if( !(TXmlNode *)this->HasChildNodes() )
    return result;
    TXmlNodeList *vars = GetChildNodesByNodeType(ELEMENT_NODE);
    assert(vars);
    for(int i = 0; i < vars->Length; i++)
    {
        TXelm *elm = (TXelm *)vars->Item(i);
        if( elm->atName == AttrName )
        {
            result = elm;
            break;
        }
        result = elm->TreeFindName(AttrName);
        if( result != NULL )
            break;
    }
    delete vars;
    return result;
}
//---------------------------------------------------------------------------
TXelm *TXelm::FindSName(String AttrSName)
{
    TXelm *result = (TXelm *)NULL;
    if( !(TXmlNode *)this->HasChildNodes() )
    return result;
    TXmlNodeList *vars = GetChildNodesByNodeType(ELEMENT_NODE);
    assert(vars);
    for(int i = 0; i < vars->Length; i++)
    {
        TXelm *elm = (TXelm *)vars->Item(i);
        if( elm->atSName == AttrSName )
        {
            result = elm;
            break;
        }
    }
    delete vars;
    return result;
}
//---------------------------------------------------------------------------
vecxml TXelm::Select(String nodeParent, String nodeChildren)
{
    return Select0(nodeParent)->Select(nodeChildren);
}
//---------------------------------------------------------------------------
long CRC(long crcstart, vecxml lst)
{
    WORD crc = crcstart + 29091969L;
    for(int i = 0; i < (int)lst.size(); i++)
        crc = get_crc_16(crc, lst[i]->atName.c_str(), lst[i]->atName.Length() );
    return crc;
}
//---------------------------------------------------------------------------
long CRC(String _crc)
{
    WORD crc = (WORD)(29091969L- (long)(int)Now());
    return (long)get_crc_16(crc, _crc.c_str(), _crc.Length() );
}
//---------------------------------------------------------------------------
long CRC(long crcstart, vecstr array)
{
    WORD crc = crcstart + 29091969L;
    for(int i = 0; i < (int)array.size(); i++)
        crc = get_crc_16(crc, array[i].c_str(), array[i].Length() );
    return crc;
}
//---------------------------------------------------------------------------
map<long, String> TXelm::SelectIDName(String nodeName)
{
    map<long, String> result;
    vecxml lst = Select(nodeName);
    for(int i = 0; i < (int)lst.size(); i++)
    {
        long id = lst[i]->atID.ToInt();
        result[id] = lst[i]->atName;
    }
    return result;
}
//---------------------------------------------------------------------------
map<String, long> TXelm::SelectNameID(String nodeName)
{
    map<String, long> result;
    vecxml lst = Select(nodeName);
    for(int i = 0; i < (int)lst.size(); i++)
    {
        long id = lst[i]->atID.ToInt();
        result[lst[i]->atName] = id;
    }
    return result;
}
//---------------------------------------------------------------------------
vecxml TXelm::Select(String nodeName)
{
    vecxml listNodes;
    if( nodeName.IsEmpty() )
        return listNodes;
    TXmlNodeList *vars = (TXmlNodeList *)SelectNodes( nodeName );
    if( vars == NULL )
        return listNodes;
    for(int i = 0; i < vars->Length; i++)
        listNodes.push_back( (TXelm *)vars->Item(i) ); 
    delete vars;
    return listNodes;
}
//---------------------------------------------------------------------------
TXelm * TXelm::Select0(String nodeName)
{
    TXmlNodeList *vars = (TXmlNodeList *)SelectNodes( nodeName );
    TXelm *result = NULL;
    if( vars->Length > 0 )
    {
        TXelm *elm = (TXelm *)vars->Item(0);
        result = elm;
    }else
        result = AddChild(nodeName);
    delete vars;
    return result;
}
//---------------------------------------------------------------------------
// delete current node from parent tree
void TXelm::Delete(TXelm *node)
{
    if( node != NULL )
    {
      node->RemoveAll();
      RemoveChild(node);
      node->Release();
    }
}
//---------------------------------------------------------------------------
// delete all children nodes 'item' from current node
void TXelm::Delete(String item)
{
    vecxml lst = Select(item);
    for(int i = 0; i < (int)lst.size(); i++ )
        Delete(lst[i]);
}
//---------------------------------------------------------------------------
// clone project template from dom to XML
TXelm *Clone(TXelm *child, TXelm *toParent) // return new item
{
	TXelm *elm = (TXelm *)child->CloneNode(true);  // create clone with children
	toParent->ForceOwnerDocument( elm );
	toParent->AppendChild( elm );
	elm->Release();
    return elm;
}
//---------------------------------------------------------------------------
vecstr getListFile(String mask)
{
  vecstr result;
  if( mask == NULL || mask.IsEmpty() )
    return result;
  TSearchRec sr;
  int iAttributes = faAnyFile | faArchive;
  if (FindFirst(mask, iAttributes, sr) == 0)
  {
    do
    {
      if((sr.Attr & iAttributes) == sr.Attr)
         result.push_back(sr.Name);
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
  return result;
}
//---------------------------------------------------------------------------
float vecmin(vecflt lst)
{
    float min = 1.0e32;
    for(int i = 0; i < (int)lst.size(); i++)
        if( min > lst[i] )
            min = lst[i];
    return min;
}
float vecmax(vecflt lst)
{
    float max = -1.0e32;
    for(int i = 0; i < (int)lst.size(); i++)
        if( max < lst[i] )
            max = lst[i];
    return max;
}
//---------------------------------------------------------------------------



