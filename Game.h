#ifndef GAME_H
#define GAME_H

#include "Parser.h"
#include "Board.h"
#include "Player.h"
#include "Server.h"

class Parser;

class Game{
  public:
    Game();

    void startGame();
    void startRound();
    void doTurn();
    bool getInput();
    void endGame();
    void undoLastTurn();

    int turnNum;
    bool shouldDisplayBoard;

    Server server;
    Board board;
    Parser parser;

    Player p1;
    Player p2;
};

#endif
