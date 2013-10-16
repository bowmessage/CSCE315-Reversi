#include "Board.h"

struct Node{
	Node *right;
	Node *left;
	Move possible_move;

	Node(Move move){
		right = NULL;
		left = NULL;
		possible_move = move;
	}
	
	void addRight(Node r){
		right = r;
	}
	
	void addLeft(Node l){
		left = l;
	}
	
	void removeLeft(){ left = NULL; }
	
	void removeRight(){ right = NULL; }

}

class AI{
  public:
	Node move_tree;
	
	AI();
	~AI();
	
	updateMoveTree(Board gameboard);
	
}
