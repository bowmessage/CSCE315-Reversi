#include "Server.h"
#include "Game.h"
#include <iostream>
#include "FL/Fl.H"
#include "FL/Fl_Double_Window.H"
#include "reversi.h"

using namespace std;

Game g;

void* GameThread(void* in){
  g.startGame();
  pthread_exit(NULL);
}

int main(int argc, char** argv){

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
  if(p == -1){
    g = Game(44423);
  }
  else{
    g = Game(p);
  }

  pthread_t gameThread;
  pthread_create(&gameThread,
      NULL,
      GameThread,
      NULL);

  ReversiUI r(&g);
  r.show(p);

  while(Fl::wait()){
    if(g.shouldUpdateUI){
      g.shouldUpdateUI = false;
      r.updateUI();
    }
  }

  //pthread_join(gameThread, NULL);

}
