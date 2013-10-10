#include "Tile.h"

Tile::Tile(){}

Tile::Tile(State s){
  state = s;
}

void Tile::setState(State s){
  state = s;
}

State Tile::getState(){
  return state;
}
