#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Token{
  Token(string s) : value(s) {};
  string value;
};

class Tokenizer{
  public:
    vector<Token> tokenize(string s);
};

#endif
