#include "Server.h"

Server::Server(){
  socketID = 0;
  connectID = 0;
}

void Server::startServer(){
  struct sockaddr_in serverAddr;

  socketID = socket(AF_INET, SOCK_STREAM, 0);

  memset(&serverAddr, 0, sizeof(struct sockaddr_in));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(44423);

  bind(socketID, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  listen(socketID, 5);
}

void Server::acceptConnection(){
  connectID = accept(socketID, (sockaddr *) NULL, NULL);
}
void Server::endConnection(){
  shutdown(connectID, 2);
  close(connectID);
}

void Server::sendString(string s){
  write(connectID, s.c_str(), s.size());
}

string Server::readString(){
  read(connectID, readBuf, 1024);
  return string(readBuf);
}
