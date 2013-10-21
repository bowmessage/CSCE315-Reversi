#include "Parser.h"
#include "Game.h"

Parser::Parser(){
  justChangedMove = false;
}

bool Parser::parse(Game& g, string t){
  game = &g;

  curIndex = 0;
  tokens = tokenizer.tokenize(t);



  if(tokens.size() == 0) return false;

  return command() || move(); //All comments removed from vectors.
}

bool Parser::command(){
  if(literal("EXIT")){
    game->server.sendString(";Goodbye.\n");
    game->server.endConnection();
    game->startRound();
    return true;
  }
  else if(literal("DISPLAY")){
    game->shouldDisplayBoard = !game->shouldDisplayBoard;
    if(game->shouldDisplayBoard){
      game->server.sendString(game->board.toString());
    }
    return true;
  }
  else if(difficulty()){
    //TODO implement
    return true;
  }
  else if(literal("UNDO")){
    game->undoLastTurn();
    game->server.sendString(game->board.toString());
    return true;
  }
  savePos();
  if(literal("HUMAN-AI") && next() &&
      server() && next() &&
      port() && next() &&
      difficulty() && next() &&
      difficulty()){
    return true;
  }
  restorePos();
  if(literal("AI-AI") && next() &&
      server() && next() &&
      port() && next() &&
      difficulty() && next() &&
      difficulty()){
    return true;
  }
  restorePos(); return false;
}

bool Parser::difficulty(){
  string curValue = cur().value;
  return curValue == "EASY" ||
    curValue == "MEDIUM" ||
    curValue == "HARD";
}

bool Parser::server(){
  //TODO implement
  return true;
}

bool Parser::port(){
  //TODO implement
  return true;
}



bool Parser::literal(string s){
  return cur().value == s;
}

bool Parser::move(){
  char c, r;
  savePos();
  if((c = column()) != 0 && next() &&
      (r = row()) != 0){
    Move m = Move(game->p1.team, (c-97), (r-49));
    int* offset = game->board.checkForLineFrom(m.team, m.x, m.y);
    if(offset != NULL){
      m.dirX = offset[0];
      m.dirY = offset[1];
      if(game->board.isValid(m)) {
        game->p1.moveToMake = m;
        delete[] offset;
        justChangedMove = true;
        return true;
      }
    }
    delete[] offset;
    return false;
  }
  restorePos();
  //Check if move is two characters right next to each other
  //as opposed to two tokens.
  string curStr = cur().value;
  if(curStr.size() == 2){
    c = curStr.at(0);
    r = curStr.at(1);
    if( (c >= 65) && (c <= 72) && (r >= 49) && (r <= 56)){
      Move m = Move(game->p1.team, (c-65), (r-49));
      int* offset = game->board.checkForLineFrom(m.team, m.x, m.y);
      if(offset != NULL){
        m.dirX = offset[0];
        m.dirY = offset[1];
        if(game->board.isValid(m)) {
          game->p1.moveToMake = m;
          delete[] offset;
          justChangedMove = true;
          return true;
        }
      }
      delete[] offset;
      return false;
    }
  }
  restorePos();
  return false;
}

char Parser::column(){
  string c = cur().value;
  if(c.size() != 1) return 0;
  char ch = c.at(0);
  if(ch >= 65 && ch <= 72){
    return ch;
  }
  else return 0;
}

char Parser::row(){
  string c = cur().value;
  if(c.size() != 1) return 0;
  char ch = c.at(0);
  if(ch >= 49 && ch <= 56){
    return ch;
  }
  else return 0;
}


void Parser::savePos(){
  saveIndex = curIndex;
}

void Parser::restorePos(){
  curIndex = saveIndex;
}

bool Parser::next(){
  curIndex++;
  return curIndex < tokens.size();
}
bool Parser::advance(int n){
  curIndex += n;
  return curIndex < tokens.size();
}

Token Parser::cur(){
  return tokenAt(curIndex);
}

Token Parser::tokenAt(int i){
  if(i < tokens.size()){
    return tokens[i];
  }
  else return Token("");
}
