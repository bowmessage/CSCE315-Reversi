#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Player{
  public:
    Player();
    Player(State t);

    State team;
    bool isAI;

    int* getMove();
    int* convertStrMoveToInts(string s);


};



#endif
