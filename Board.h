#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

struct Move{
  State team;
  int x;
  int y;

  Move() {}
  Move(State t, int xin, int yin) : team(t), x(xin), y(yin) {}
  string toString(){
    stringstream ss;
    ss << (char)(x+97) << (char)(y+49) << "\n";
    return ss.str();
  }
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
    bool makeMove(Move m);



    friend ostream& operator<<(ostream& out, const Board b);
    string toString() const;
};


#endif
