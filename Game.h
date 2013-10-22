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
    Game(int p);

    void startGame();
    void createPlayers(bool isHumanAiRound);
    void startRound();
    void beginTurnLoop();
    void doTurn(bool shouldGetInput);
    bool getInput();
    void endGame();
    bool undoLastTurn();
    void sendStr(string s);

    int turnNum;
    bool shouldDisplayBoard;
    bool isInSetup;
    bool isHumanAiGame;

    Server server;
    Board board;
    Parser parser;

    Player p1;
    Player p2;
};

#endif
