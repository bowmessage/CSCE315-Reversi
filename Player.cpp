//#define DEBUGOUTS 1

#include "Player.h"

Player::Player(){
  team = EMPTY;
  isAI = false;
}

Player::Player(State t){
  team = t;
  isAI = false;
}

int* Player::getMove(){
  int* moveInts = NULL;
  string moveString;

  do{
    cout << "Enter your move: ";
    cin >> moveString;
    moveInts = convertStrMoveToInts(moveString);
  }while(moveInts == NULL);

  return moveInts;
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

  if(true){//DEBUGOUTS){
    cout << "colNum: " << colNum << ", rowNum: " << rowNum << "\n";
  }

  ret[0] = colNum;
  ret[1] = rowNum;

  return ret;
}
