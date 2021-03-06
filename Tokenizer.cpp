#include "Tokenizer.h"

vector<Token> Tokenizer::tokenize(string s){
  vector<Token> ret;
  stringstream inStream;
  inStream << s;
  while(inStream.rdbuf()->in_avail()){
    string cur;
    inStream >> cur;
    if(cur.size() > 0 && cur.at(0) == ';') return ret;//If we've started a comment token, we're done.
    transform(cur.begin(), cur.end(), cur.begin(), ::toupper);

    //string cur_trim = ltrim(rtrim(cur));

    //if(cur_trim.size() > 0)
      ret.push_back(Token(cur));
  }
  return ret;
}
