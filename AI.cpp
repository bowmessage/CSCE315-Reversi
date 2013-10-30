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
  vector<Move> possibleMoves = b.validMoves(team);
  int randIndex = rand() % possibleMoves.size();
  switch(difficulty){
    case EASY:
      return possibleMoves[randIndex];
      break;
    case MEDIUM:
      parent->fillChildrenToDepth(team, 2);
      break;
    case HARD:
      parent->fillChildrenToDepth(team, 4);
      break;
  }
  Move ret = parent->getMoveFromChildren(team);
  delete parent;
  return ret;
}
