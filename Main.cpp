
#include "Game.h"
#include <iostream>

using namespace std;

int main(){
  Game g;
  //cout << g.board;
  g.startGame();
  while(1){
    g.doTurn();
  }
}
