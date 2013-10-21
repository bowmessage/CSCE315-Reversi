#ifndef PLAYER_H
#define PLAYER_H

#include "AI.h"
#include "Board.h"
#include "Tile.h"
#include <string>
#include <iostream>
#include <cstdlib>


using namespace std;

class Player{
  public:
    Player();
    Player(State t, bool iA);

    State team;

    AI ai;
    bool isAI;
    int connectionSocketID;

    Move moveToMake;

    Move getMove(Board& b);
    //int* convertStrMoveToInts(string s);


};



#endif
