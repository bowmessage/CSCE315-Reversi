#ifndef PARSER_H
#define PARSER_H

#include "Game.h"
#include <vector>

using namespace std;

struct Token{
};

class Parser{
  bool parse(Game& g, vector<Token> tokens);
};



#endif
