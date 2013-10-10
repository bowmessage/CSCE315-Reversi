#include "Tile.h"

Tile::Tile(){}

Tile::Tile(State s){
  state = s;
}


Tile::turnWhite(){
  state = Tile.WHITE;
}

Tile::turnBlack(){
  state = Tile.BLACK;
}

Tile::isWhite(){
  if(state == Tile.WHITE) return true;
  else return false;
}

Tile::isBlack(){
  if(state == Tile.BLACK) return true;
  else return false;
}

Tile::isEmpty(){
  if(state == Tile.BLANK) return true;
  else return false;
}
