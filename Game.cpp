#include "Parser.h"
#include "Game.h"

Game::Game(){
  turnNum = 0;
  shouldDisplayBoard = false;
}

void Game::startGame(){
  server = Server();
  server.startServer();
  cout << "Welcome to Reversi.\n";
  cout << "The game server has started. Waiting for connections...\n";
  startRound();
}

void Game::startRound(){
  server.acceptConnection();
  cout << "Connection received! Game starting.\n";

  board = Board();

  server.sendString("WELCOME\n");


  p1 = Player(WHITE, false);
  p2 = Player(BLACK, true);

  turnNum = 0;
  shouldDisplayBoard = false;

  while(board.hasValidMoves()){
    doTurn();
  }

  endGame();
}

void Game::endGame(){
  server.sendString(";The game is over.\n");
  
  int numWhite = board.numTilesOfState(WHITE);
  int numBlack = board.numTilesOfState(BLACK);
  if(numWhite > numBlack){
    server.sendString(";WHITE won the game.\n");
  }
  else if(numWhite < numBlack){
    server.sendString(";BLACK won the game.\n");
  }
  else{
    server.sendString(";The game resulted in a tie.\n");
  }

  server.sendString(";Goodbye.\n");
  server.endConnection();
}

bool Game::getInput(){
  //This function returns true when it is ready for a new move to be made.
  //It returns false when a setting is made or a non move input is received.
  
  bool hasParsed = false;
  do{
    string in = server.readString();
    hasParsed = parser.parse(*this, in);
    if(!hasParsed){
      server.sendString("ILLEGAL\n");
    }
    else{
      server.sendString("OK\n");
    }
  }while(!hasParsed);
  
  if(parser.justChangedMove){
    parser.justChangedMove = false;
    return true;
  }
  return false;
}

void Game::doTurn(){
  if(shouldDisplayBoard){
    server.sendString(board.toString());
  }
  while(!getInput()){}
  board.makeMove(p1.getMove(board));
  Move m = p2.getMove(board);
  if(board.makeMove(m)){
    server.sendString(m.toString());
  }
  else{
    server.sendString(";P2 Passes");
  }

  turnNum++;
}

void Game::undoLastTurn(){
  if(turnNum >= 1){
    turnNum--;
    board.undoLastMove();
    board.undoLastMove();
  }
}
