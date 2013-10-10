#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game{
  public:

    Game();


    void startGame();
    int turnNum;
    bool isP1Turn;

    void doTurn();


    Board board;

    Player p1;
    Player p2;

};

#endif
