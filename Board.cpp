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

vector<Position> Board::positionsFlippedByMove(Move m){
  vector<Position> ret;
  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){
      vector<Position> posAtOffset = positionsInLineFromOffset(m.team, m.x, m.y, i, j);
      if(posAtOffset.size() > 0){
        for(int k = 0; k < posAtOffset.size(); k++){
          ret.push_back(posAtOffset[k]);
        }
      }
    }
  }
  return ret;
}

vector<Move> Board::validMoves(State s){
  vector<Move> ret;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(getState(j,i) == EMPTY){
        int* offset;
        if((offset = checkForLineFrom(s,j,i)) != NULL){
          Move m = Move(s,j,i);
          m.dirX = offset[0];
          m.dirY = offset[1];
          ret.push_back(m);
        }
        delete[] offset;
      }
    }
  }
  return ret;
}

int* Board::checkForLineFrom(State s, int x, int y){
  State opp = opposite(s);
  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){
      if(x+i < 0 || x+i > 7 || y+j < 0 || y+j > 7) continue;
      if(getState(x+i, y+j) == opp && checkForLineFromOffset(s,x,y,i,j)){
        int* ret = new int[2];
        ret[0] = i;
        ret[1] = j;
        return ret;
      }
    }
  }
  return NULL;
}

bool Board::checkForLineFromOffset(State s, int x, int y, int i, int j){
  //i and j are x and y offsets respectively.
  
  if(i == 0 && j == 0){
    //No line if offset is 0..
    return false;
  }
  int xn = x+i; int yn = y+j;
  if(xn < 0 || yn < 0 || xn > 7 || yn > 7) return false;

  State opp = opposite(s);
  State cur = getState(xn, yn);

  if(cur == EMPTY) return false;
  if(cur == opp) return checkForLineFromOffset(s,xn,yn,i,j);//follow this line
  if(cur == s) return true;
}

vector<Position> Board::positionsInLineFromOffset(State s, int x, int y, int i, int j){
  vector<Position> blankRet;//Make this just in case we don't actually have a line here.
  vector<Position> ret;
  if(i == 0 && j == 0){
    //if offset is 0, no line here.
    return ret;
  }

  int xn = x+i; int yn = y+j;
  State opp = opposite(s);
  State cur = getState(xn, yn);
  while(cur == opp){
    ret.push_back(Position(xn,yn));
    xn += i; yn += j;
    if(xn < 0 || yn < 0 || xn > 7 || yn > 7) return blankRet;
    cur = getState(xn, yn);
  }

  if(cur == s){
    //success, this is a line.
    return ret;
  }
  else{
    //cur must equal EMPTY, no line here.
    return blankRet;
  }
}


bool Board::hasValidMoves(){
  return hasValidMoves(WHITE) && hasValidMoves(BLACK);
}

bool Board::hasValidMoves(State s){
  return validMoves(s).size() > 0;
}

bool Board::makeMove(Move m){
  if(isValid(m)){
    setState(m.team, m.x, m.y);

    vector<Position> positionsFlipped = positionsFlippedByMove(m);
    m.resultingTilesFlipped = positionsFlipped;
    for(int i = 0; i < positionsFlipped.size(); i++){
      setState(m.team, positionsFlipped[i].x, positionsFlipped[i].y);
    }

    /*int curX = m.x + m.dirX;
    int curY = m.y + m.dirY;
    while(getState(curX, curY) == opposite(m.team)){

      setState(m.team, curX, curY);
      m.resultingTilesFlipped.push_back(Position(curX, curY));

      curX += m.dirX;
      curY += m.dirY;
    }*/
    moves.push_back(m);
    return true;
  }
  else return false;
}

bool Board::isValid(Move m){
  return getState(m.x, m.y) == EMPTY &&
    checkForLineFromOffset(m.team, m.x, m.y, m.dirX, m.dirY);
}

State Board::opposite(State s){
  if(s == EMPTY) return EMPTY;
  return (s==WHITE)?BLACK:WHITE;
}

int Board::numTilesOfState(State s){
  int ret = 0;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(getState(i,j) == s) ret++;
    }
  }
  return ret;
}


ostream& operator<<(ostream& out, const Board b){
  out << b.toString();
  return out;
}

string Board::toString() const{
  stringstream ss;
  int numBlack = 0, numWhite = 0;

  ss << ";Current Board:\n";
  ss << ";  _ _ _ _ _ _ _ _ \n";
  for(int i = 0; i < 8; i++){
    ss << ";" << (i+1);
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
  ss << ";  a b c d e f g h\n";
  ss << ";\n";
  ss << ";White: " << numWhite << "\n";
  ss << ";Black: " << numBlack << "\n";
  ss << ";\n;\n";
  return ss.str();
}
