#include "AI.h"

AI::AI(){
  team = EMPTY;
  difficulty = EASY;
}

AI::AI(State t){
  team = t;
  difficulty = EASY;
}


Move AI::getMove(Board b){
  Node* parent = new Node(b);
  switch(difficulty){
    case EASY:
      parent->fillChildrenToDepth(team, 2);
      break;
    case MEDIUM:
      parent->fillChildrenToDepth(team, 3);
      break;
    case HARD:
      parent->fillChildrenToDepth(team, 4);
      break;
  }
  Move ret = parent->getMoveFromChildren(team);
  delete parent;
  return ret;
}
