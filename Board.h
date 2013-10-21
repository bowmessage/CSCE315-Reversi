#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

struct Position{
  int x;
  int y;

  Position(int xin, int yin) : x(xin), y(yin) {}
};

struct Move{
  State team;
  int x;
  int y;

  int dirX;
  int dirY;

  vector<Position> resultingTilesFlipped;

  Move() {
    resultingTilesFlipped = vector<Position>();
  }
  Move(State t, int xin, int yin) : team(t), x(xin), y(yin) {
    resultingTilesFlipped = vector<Position>();
  }
  string toString(){
    stringstream ss;
    ss << (char)(x+97) << (char)(y+49) << "\n";
    return ss.str();
  }
};

class Board{
  public:
    Board();
    Board(const Board& b);
    ~Board();

    Tile tiles[8][8];
    vector<Move> moves;

    void setState(State s, int x, int y);
    State getState(int x, int y);

    vector<Position> positionsFlippedByMove(Move m);
    vector<Move> validMoves (State s);
    bool hasValidMoves();
    bool makeMove(Move m);

    vector<Position> positionsInLineFromOffset(State s, int x, int y, int i, int j);
    int* checkForLineFrom(State s, int x, int y);
    bool checkForLineFromOffset(State s, int x, int y, int i, int j);

    int numTilesOfState(State s);
    bool hasValidMoves(State s);
    bool isValid(Move m);

    void undoLastMove();

    State opposite(State s);
    friend ostream& operator<<(ostream& out, const Board b);
    string toString() const;
};


#endif
