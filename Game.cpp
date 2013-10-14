#include "Parser.h"
#include "Game.h"

Game::Game(){
}

void Game::startGame(){
  server = Server();
  server.startServer();
  cout << "Welcome to Reversi.\n";
  cout << "The game server has started. Waiting for connections...\n";
  server.acceptConnection();
  cout << "Connection received! Game starting.\n";
  startRound();
  server.sendString(board.toString());
  server.readString();
}

void Game::startRound(){
  board = Board();

  server.sendString("WELCOME\n");


  p1 = Player(WHITE, false);
  p2 = Player(BLACK, true);

  turnNum = 0;

  while(board.hasValidMoves()){
    doTurn();
  }

  endGame();
}

void Game::endGame(){
  server.sendString(";The game is over.");
  
  int numWhite = board.numTilesOfState(WHITE);
  int numBlack = board.numTilesOfState(BLACK);
  if(numWhite > numBlack){
    server.sendString(";WHITE won the game.");
  }
  else if(numWhite < numBlack){
    server.sendString(";BLACK won the game.");
  }
  else{
    server.sendString(";The game resulted in a tie.");
  }

  server.sendString(";Goodbye.");
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
  server.sendString(board.toString());
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
