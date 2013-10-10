#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"

using namespace std;

class Player{
  public:
    Player();
    Player(State t);

    State team;

};



#endif
