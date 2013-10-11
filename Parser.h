#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>

#include "Tokenizer.h"

using namespace std;

class Game;

class Parser{
  public:

    Tokenizer tokenizer;

    bool parse(Game& g, string tokens);
};



#endif
