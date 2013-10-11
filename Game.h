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
    void getInput();
    void endGame();

    int turnNum;
    bool isP1Turn;

    Server server;
    Board board;
    Parser parser;

    Player p1;
    Player p2;
};

#endif
