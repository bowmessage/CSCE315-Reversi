#include "Server.h"
#include "Game.h"
#include <iostream>

using namespace std;

int main(){
/*  Game g;
  //cout << g.board;
  g.startGame();
  while(1){
    g.doTurn();
  }*/

  Game g;
  g.startGame();

  Server s;
  s.startServer();
  cout << "Welcome to Reversi.\n";
  cout << "The game server has started. Waiting for connections...\n";
  s.acceptConnection();
  cout << "Connection received! Game starting.\n";
  s.sendString(g.board.toString());
  s.readString();
  s.endConnection();
}
