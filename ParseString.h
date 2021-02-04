//---------------------------------------------------------------------------
#ifndef ParseStringH
#define ParseStringH
#include <deque>
using namespace std;

class TParseString
{
 private:
  String _Delimiters;
 protected:
 public:
  int Parse_Words(String line, deque<String> &word_list, bool erase=true);
  __property String Delimiters = {read = _Delimiters, write = _Delimiters};
  TParseString(void){}
};

//---------------------------------------------------------------------------
#endif

