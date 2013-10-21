#include "AI.h"

AI::AI(){
  team = EMPTY;
}

AI::AI(State t){
  team = t;
}


int AI::evaluateBoard(Board b){
  int ret = 0;
  State opp = b.opposite(team);
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(b.getState(i,j) == team){
        ret++;
      }
      else if(b.getState(i,j) == opp){
        ret--;
      }
    }
  }
  return ret;
}

void AI::updateMoveTree(Board b){
}

Move AI::getMove(Board b){
  Node* parent = new Node(b);
  parent->fillChildrenToDepth(team, 4);
  delete parent;
  return Move();
}
