#include "Game.h"

Game::Game(){
}

void Game::startGame(){
  server = Server();
  server.startServer();
  cout << "Welcome to Reversi.\n";
  cout << "The game server has started. Waiting for connections...\n";
  server.acceptConnection();
  cout << "Connection received! Game starting.\n";
  startRound();
  server.sendString(board.toString());
  server.readString();
}

void Game::startRound(){
  board = Board();

  server.sendString("WELCOME");


  p1 = Player(WHITE, false);
  p2 = Player(BLACK, true);

  isP1Turn = true;
  turnNum = 0;

  while(board.hasValidMoves()){
    doTurn();
  }
  endGame();
}

void Game::endGame(){
  server.endConnection();
}

void Game::doTurn(){
  server.sendString(board.toString());
  stringstream ss;
  ss << "Starting Player " << ((!isP1Turn)+1) << "'s turn.\n";
  server.sendString(ss.str());

  Move m;
  if(isP1Turn){
    m = p1.getMove(board);
    board.setState(m.team, m.x, m.y);
  }
  else{
    m = p2.getMove(board);
    board.setState(m.team, m.x, m.y);
  }

  isP1Turn = !isP1Turn;
  turnNum++;
}
