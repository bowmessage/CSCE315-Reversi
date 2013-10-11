#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

struct Move{
  int x;
  int y;
  State team;
};

class Board{
  public:
    Board();
    ~Board();

    Tile tiles[8][8];
    vector<Move> moves;

    void setState(State s, int x, int y);
    State getState(int x, int y);

    vector<Move> validMoves (State s);
    bool hasValidMoves();



    friend ostream& operator<<(ostream& out, const Board b);
    string toString() const;
};


#endif
