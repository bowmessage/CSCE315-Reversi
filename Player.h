#ifndef PLAYER_H
#define PLAYER_H

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

    bool isAI;
    int connectionSocketID;

    Move moveToMake;

    Move getMove(Board& b);
    int* convertStrMoveToInts(string s);


};



#endif
