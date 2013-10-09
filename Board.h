#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <iostream>

using namespace std;

class Board{
  public:
    Board();
    ~Board();

    Tile tiles[8][8];
    friend ostream& operator<<(ostream& out, const Board b);
};


#endif
