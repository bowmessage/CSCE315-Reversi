#define DEBUGOUTS 1

#include "Player.h"

Player::Player(){
  moveToMake.x = 0; moveToMake.y = 0; moveToMake.team = EMPTY;
  team = EMPTY;
  connectionSocketID = -1;
  isAI = false;
}

Player::Player(State t, bool iA){
  moveToMake.x = 0; moveToMake.y = 0; moveToMake.team = t;
  team = t;
  connectionSocketID = -1;
  isAI = iA;
}


int* Player::convertStrMoveToInts(string s){
  if(s.size() != 2){
    cout << "Please only use 2 characters to enter your move.\n";
    return NULL;
  }
  int* ret = new int[2];

  char col = s[0];
  char row = s[1];

  int colNum = (int)(col-97);
  int rowNum = (int)(row-49);

  if(DEBUGOUTS){
    cout << "colNum: " << colNum << ", rowNum: " << rowNum << "\n";
  }

  ret[0] = colNum;
  ret[1] = rowNum;

  return ret;
}

Move Player::getMove(Board& b){
  if(isAI){
    //TODO make AI pick random valid move
    return moveToMake;
  }
  else return moveToMake;
}
