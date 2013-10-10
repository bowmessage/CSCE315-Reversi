#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
#include <iostream>

using namespace std;

class Board{
  public:
    Board();
    ~Board();

    Tile tiles[8][8];

    void setState(State s, int x, int y);
    State getState(int x, int y);

    vector<Tile> validMoves (State s);



    friend ostream& operator<<(ostream& out, const Board b);
};


#endif
