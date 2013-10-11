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
  out << b.toString();
  return out;
}

string Board::toString() const{
  stringstream ss;
  int numBlack = 0, numWhite = 0;

  ss << "Current Board:\n";
  ss << "  _ _ _ _ _ _ _ _ \n";
  for(int i = 0; i < 8; i++){
    ss << (i+1);
    //ss << (char)(97+i);
    for(int j = 0; j < 8; j++){
      ss << "|";
      switch(tiles[i][j].state){
        case WHITE:
          numWhite++;
          ss << "@";
          break;
        case BLACK:
          numBlack++;
          ss << "O";
          break;
        case EMPTY:
          ss << "_";
          break;
      }
    }
    ss << "|\n";
  }
  ss << "  a b c d e f g h\n";
  ss << "\n";
  ss << "White: " << numWhite << "\n";
  ss << "Black: " << numBlack << "\n";
  ss << "\n\n";
  return ss.str();
}
