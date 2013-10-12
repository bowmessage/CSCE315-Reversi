#include "Tokenizer.h"

vector<Token> Tokenizer::tokenize(string s){
  vector<Token> ret;
  stringstream inStream;
  inStream << s;
  while(inStream.rdbuf()->in_avail()){
    string cur;
    inStream >> cur;
    if(cur.size() > 0 && cur.at(0) == ';') return ret;//If we've started a comment token, we're done.
    ret.push_back(Token(cur));
  }
  return ret;
}
