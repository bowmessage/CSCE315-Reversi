#include "Server.h"
#include "Game.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
/*  Game g;
  //cout << g.board;
  g.startGame();
  while(1){
    g.doTurn();
  }*/    

  int p = -1;

  int opt = getopt(argc, argv, "p:");

  while(opt != -1){
    switch(opt){
      case 'p':
        p = atoi(optarg);
        break;
    }
    opt = getopt(argc, argv, "p:");
  }
  Game g;
  if(p == -1){
    g = Game(44423);
  }
  else{
    g = Game(p);
  }
  g.startGame();
}
