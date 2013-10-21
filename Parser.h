#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "arpa/inet.h"

#include "Tokenizer.h"
#include "Board.h"

using namespace std;

class Game;

class Parser{
  public:

    Parser();

    Tokenizer tokenizer;

    Game* game;

    vector<Token> tokens;
    int curIndex;
    int saveIndex;

    bool parse(Game& g, string tokens);
    bool justChangedMove;

    bool command();
    bool literal(string s);
    bool difficulty();
    bool server();
    bool port();
    bool team();

    bool move();
    char column();
    char row();




    void savePos();
    void restorePos();
    bool next();
    bool advance(int n);
    Token cur();
    Token tokenAt(int i);
};

#endif
