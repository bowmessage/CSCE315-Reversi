#include "Tokenizer.h"

vector<Token> Tokenizer::tokenize(string s){
  vector<Token> ret;
  stringstream inStream;
  inStream << s;
  while(inStream.rdbuf()->in_avail()){
    string cur;
    inStream >> cur;
    ret.push_back(Token(cur));
  }
  return ret;
}
