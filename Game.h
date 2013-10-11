#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Server.h"

class Game{
  public:
    Game();

    void startGame();
    void startRound();
    void doTurn();
    void endGame();

    int turnNum;
    bool isP1Turn;

    Server server;
    Board board;

    Player p1;
    Player p2;
};

#endif
