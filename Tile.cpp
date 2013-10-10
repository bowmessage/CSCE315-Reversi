#include "Tile.h"

Tile::Tile(){}

Tile::Tile(State s){
  state = s;
}


void Tile::turnWhite(){
  state = WHITE;
}

void Tile::turnBlack(){
  state = BLACK;
}

bool Tile::isWhite(){
  return state == WHITE;
}

bool Tile::isBlack(){
  return state == BLACK;
}

bool Tile::isEmpty(){
  return state == EMPTY;
}
