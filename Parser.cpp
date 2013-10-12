#include "Parser.h"
#include "Game.h"

bool Parser::parse(Game& g, string t){
  game = &g;

  curIndex = 0;
  tokens = tokenizer.tokenize(t);

  cout << tokens.size();
  for(int i = 0; i < tokens.size(); i++){
    cout << tokens[i].value;
  }

  //TODO implement
  if(tokens.size() == 0) return false;

  return command() || move(); //All comments removed from vectors.
}

bool Parser::command(){
  if(literal("EXIT")){
    return true;
  }
  else if(literal("DISPLAY")){
    return true;
  }
  else if(difficulty()){
    return true;
  }
  else if(literal("UNDO")){
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
    game->p1.moveToMake = Move(game->p1.team, (c-97), (r-49));
    return true;
  }
  else {
    restorePos();
    return false;
  }
}

char Parser::column(){
  string c = cur().value;
  if(c.size() != 1) return 0;
  char ch = c.at(0);
  if(ch >= 97 && ch <= 104){
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
