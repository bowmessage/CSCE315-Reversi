#include "AI.h"

AI::AI(){
  team = EMPTY;
}

AI::AI(State t){
  team = t;
}


Move AI::getMove(Board b){
  Node* parent = new Node(b);
  parent->fillChildrenToDepth(team, 4);
  Move ret = parent->getMoveFromChildren(team);
  delete parent;
  return ret;
}
