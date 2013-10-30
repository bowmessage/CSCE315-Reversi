#ifndef AI_H
#define AI_H

#include "Board.h"
#include <stdlib.h>

enum Difficulty{
  EASY, MEDIUM, HARD
};

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
	Node(Board b, Move move){
    boardHere = b;
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
      Node* c = new Node(newBoard, moves[i]);
      c->fillChildrenToDepth(newBoard.opposite(team), d-1);
      children.push_back(c);
    }
  }

  Move getMoveFromChildren(State team){
    //Get max val of childrens' mins.
    int max = -1000000;
    Move ret;
    for(int i = 0; i < children.size(); i++){
      int cur = children[i]->getMinVal(team);
      if(cur > max){
        max = cur;
        ret = children[i]->moveToGetHere;
      }
    }
    return ret;
  }

  int getMinVal(State team){
    if(children.size() < 1){
      //No children
      return evaluateBoard(team, boardHere);
    }
    else{
      //Get min of childrens' maxes.
      int min = 1000000;
      for(int i = 0; i < children.size(); i++){
        int cur = children[i]->getMaxVal(team);
        min = cur < min ? cur : min;
      }
      return min;
    }
  }

  int getMaxVal(State team){
    if(children.size() < 1){
      //No children
      return evaluateBoard(team, boardHere);
    }
    else{
      //Get max of childrens' mins.
      int max = -1000000;
      for(int i = 0; i < children.size(); i++){
        int cur = children[i]->getMinVal(team);
        max = cur > max ? cur : max;
      }
      return max;
    }
  }

  int evaluateBoard(State team, Board b){
    int ret = 0;
    State opp = b.opposite(team);

    //More pieces = better
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

    //More available moves = better
    vector<Move> myPossibleMoves = b.validMoves(team);
    vector<Move> theirPossibleMoves = b.validMoves(opp);
    ret += (myPossibleMoves.size() - theirPossibleMoves.size());

    //More corners = way better!
    for(int i = 0; i < 8; i+=7){
      for(int j = 0; j < 8; j+=7){
        if(b.getState(i,j) == team){
          ret += 5;
        }
        else if(b.getState(i,j) == opp){
          ret -= 5;
        }
      }
    }


    return ret;
  }

};


class AI{
  public:

    State team;

    Node move_tree;

    Difficulty difficulty;
    
    AI();
    AI(State t);
    
    Move getMove(Board b);
	
};

#endif
