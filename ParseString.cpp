//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ParseString.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

int TParseString::Parse_Words(String line, deque<String> &word_list, bool erase)
{
  // parses line for words delimited with characters from _Delimiters string.
  // The result of parsing is stored in word_list.
  // Return:
  //    - word counts if _Delimiters is not empty
  //    - -1 otherwise
  if(erase)
    word_list.erase(word_list.begin(),word_list.end());
  if(_Delimiters.IsEmpty())
  {
    ShowMessage("Delimiter string is empty");
    return -1; // error
  }
  String last_char;
  while(line.Length()>0)
  {
    // delete all trailing delimiters
    while(line.IsDelimiter(_Delimiters, line.Length()))
      line.Delete(line.Length(),1);
    // find the last delimiter left
    int last_delim = line.LastDelimiter(_Delimiters);
    String word = line.SubString(last_delim + 1, line.Length() - last_delim);
    if(!word.IsEmpty())
      word_list.push_front(word);
    line.Delete(last_delim + 1, line.Length() - last_delim);
  }
  return word_list.size();
}
