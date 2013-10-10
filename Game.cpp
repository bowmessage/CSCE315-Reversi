#include "Game.h"

Game::Game(){
}

void Game::startGame(){
  board = Board();
  p1 = Player(WHITE);
  p2 = Player(BLACK);


  isP1Turn = true;
  turnNum = 0;
}

void Game::doTurn(){
  cout << board;
  cout << "Starting Player " << ((!isP1Turn)+1) << "'s turn.\n";

  int* xyMove;
  if(isP1Turn){
    xyMove = p1.getMove();
    board.setState(p1.team, xyMove[0], xyMove[1]);
  }
  else{
    xyMove = p2.getMove();
    board.setState(p2.team, xyMove[0], xyMove[1]);
  }
  delete[] xyMove;

  isP1Turn = !isP1Turn;
  turnNum++;
}
