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

void Game::getInput(){
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
}

void Game::doTurn(){
  server.sendString(board.toString());
  getInput();
  board.makeMove(p1.getMove(board));
  Move m = p2.getMove(board);
  if(board.makeMove(m)){
    server.sendString(m.toString());
  }
  else{
    server.sendString(";P2 Passes");
  }

  turnNum++;

  //server.sendString(";Starting Player 1's turn.\n");
  //server.sendString(";Player 1 moves on: "
  //server.sendString(";Starting Player 2's turn.\n");
}
