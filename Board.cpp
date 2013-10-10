#include "Board.h"

Board::Board(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      tiles[i][j] = Tile(EMPTY);
    }
  }
  tiles[3][3] = Tile(WHITE);
  tiles[3][4] = Tile(BLACK);
  tiles[4][3] = Tile(BLACK);
  tiles[4][4] = Tile(WHITE);
}

Board::~Board(){
}




void Board::setState(State s, int x, int y){
  tiles[y][x].setState(s);
}

State Board::getState(int x, int y){
  return tiles[y][x].getState();
}

vector<Tile> Board::validMoves(State s){
  vector<Tile> ret;
  return ret;
}





ostream& operator<<(ostream& out, const Board b){
  int numBlack = 0, numWhite = 0;

  out << "Current Board:\n";
  out << "  _ _ _ _ _ _ _ _ \n";
  for(int i = 0; i < 8; i++){
    out << (i+1);
    //out << (char)(97+i);
    for(int j = 0; j < 8; j++){
      out << "|";
      switch(b.tiles[i][j].state){
        case WHITE:
          numWhite++;
          out << "O";
          break;
        case BLACK:
          numBlack++;
          out << "@";
          break;
        case EMPTY:
          out << "_";
          break;
      }
    }
    out << "|\n";
  }
  out << "  a b c d e f g h\n";
  out << "\n";
  out << "White: " << numWhite << "\n";
  out << "Black: " << numBlack << "\n";
  out << "\n\n";
  return out;
}
