#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;

class Game;

struct Token{
  string value;
};

class Parser{
  public:
    bool parse(Game& g, string tokens);
};



#endif
