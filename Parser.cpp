#include "Parser.h"

bool Parser::parse(Game& g, string t){
  vector<Token> tokens = tokenizer.tokenize(t);
  cout << tokens.size();
  for(int i = 0; i < tokens.size(); i++){
    cout << tokens[i].value;
  }

  //TODO implement
  return true;
}
