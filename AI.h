#ifndef AI_H
#define AI_H

#include "Board.h"

struct Node{

  vector<Node*> children;

	Move moveToGetHere;
  Board boardHere;
  int boardScoreHere;

  Node(){
  }
  Node(Board b){
    boardHere = b;
  }
	Node(Move move){
		moveToGetHere = move;
	}

  ~Node(){
    for(int i = 0; i < children.size(); i++){
      delete children[i];
    }
  }

  void fillChildrenToDepth(State team, int d){
    if(d < 0) return;
    vector<Move> moves = boardHere.validMoves(team);
    for(int i = 0; i < moves.size(); i++){
      Board newBoard = Board(boardHere);
      newBoard.makeMove(moves[i]);
      Node* c = new Node(newBoard);
      c->fillChildrenToDepth(newBoard.opposite(team), d-1);
      children.push_back(c);
    }

  }

};


class AI{
  public:

    State team;

    Node move_tree;
    
    AI();
    AI(State t);
    
    void updateMoveTree(Board b);
    int evaluateBoard(Board b);

    Move getMove(Board b);
	
};

#endif
