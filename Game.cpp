#include "Parser.h"
#include "Game.h"

Game::Game(){
  turnNum = 0;
  shouldDisplayBoard = false;
  isInSetup = true;
  isHumanAiGame = true;
}

Game::Game(int p){
  turnNum = 0;
  shouldDisplayBoard = false;
  isInSetup = true;
  isHumanAiGame = true;

  server = Server();
  server.startServer(p);
}

void Game::startGame(){
  cout << "Welcome to Reversi.\n";
  cout << "The game server has started. Waiting for connections...\n";

  server.acceptConnection();

  turnNum = 0;
  shouldDisplayBoard = false;
  isInSetup = true;
  p1 = Player();
  p2 = Player();

  server.sendString("WELCOME\n");

  while(isInSetup){
    getInput();
  }

  doTurn(false);
  beginTurnLoop();


}

void Game::createPlayers(bool isHumanAiRound){
  if(isHumanAiRound){
    p1 = Player(WHITE, false);
    p2 = Player(BLACK, true);
  }
  else{
    p1 = Player(WHITE, true);
    p2 = Player(BLACK, false);
  }
}

void Game::startRound(){
  board = Board();
  turnNum = 0;
  isInSetup = false;
}

void Game::beginTurnLoop(){
  while(board.hasValidMoves()){
    doTurn(true);
  }
  endGame();
}

void Game::sendStr(string s){
  //sleep(1);
    cout << ";sending: " << s;
  if(isHumanAiGame)
    server.sendString(s);
  else{
    server.sendStringToOtherAi(s);
    server.readStringFromOtherAi();
  }
}


void Game::endGame(){
  sendStr(";The game is over.\n");
  
  int numWhite = board.numTilesOfState(WHITE);
  int numBlack = board.numTilesOfState(BLACK);
  if(numWhite > numBlack){
    sendStr(";WHITE won the game.\n");
  }
  else if(numWhite < numBlack){
    sendStr(";BLACK won the game.\n");
  }
  else{
    sendStr(";The game resulted in a tie.\n");
  }

  sendStr(";Goodbye.\n");
  server.endConnection();
  startGame();
}

bool Game::getInput(){
  //This function returns true when it is ready for a new move to be made.
  //It returns false when a setting is made or a non move input is received.
  
  bool hasParsed = false;
  do{
    string in;
    if(isHumanAiGame)
      in = server.readString();
    else in = server.readStringFromOtherAi();
    cout << ";received: " << in << "\n";
    hasParsed = parser.parse(*this, in);
    if(isHumanAiGame){
      if(!hasParsed){
        sendStr("ILLEGAL\n");
      }
      else{
        sendStr("OK\n");
      }
    }
  }while(!hasParsed);
  
  if(parser.justChangedMove){
    parser.justChangedMove = false;
    return true;
  }
  return false;
}

void Game::doTurn(bool shouldGetInput){
  cout << "starting do turn, should getinput: " << shouldGetInput << "\n";
  cout << "thijnks of board as: " << board.toString() << "\n";
  if(isHumanAiGame && shouldGetInput){
    cout << "about to get input in human ai mode\n";
    while(!getInput()){}
    cout << "got input in human ai mode\n";
  }
  if(isHumanAiGame){
    board.makeMove(p1.getMove(board));
    Move m = p2.getMove(board);
    if(board.makeMove(m)){
      sendStr(m.toString());
    }
    else{
      sendStr(";P2 Passes\n");
    }
  }
  else{
    Move m = p1.getMove(board);
    if(board.makeMove(m)){
      sendStr(m.toString());
    }
    else{
      sendStr(";P1 Passes\n");
    }
    if(shouldGetInput){
      while(!getInput()){}
    }
    board.makeMove(p2.getMove(board));
  }

  if(shouldDisplayBoard){
    sendStr(board.toString());
  }

  turnNum++;
}

bool Game::undoLastTurn(){
  if(turnNum >= 1){
    turnNum--;
    board.undoLastMove();
    board.undoLastMove();
    return true;
  }
  else return false;
}
