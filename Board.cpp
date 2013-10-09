#include "Board.h"

Board::Board(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      tiles[i][j] = Tile(BLANK);
    }
  }
  tiles[3][3] = Tile(WHITE);
  tiles[3][4] = Tile(BLACK);
  tiles[4][3] = Tile(BLACK);
  tiles[4][4] = Tile(WHITE);
}

Board::~Board(){
}

ostream& operator<<(ostream& out, const Board b){
  out << "Current Board:\n";
  out << "_________________\n";
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      out << "|";
      switch(b.tiles[i][j].state){
        case WHITE:
          out << "O";
          break;
        case BLACK:
          out << "@";
          break;
        case BLANK:
          out << " ";
          break;
      }
    }
    out << "|\n";
  }
  out << "_________________\n";
  return out;
}
