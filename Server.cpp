#include "Server.h"

Server::Server(){
  socketID = 0;
  connectID = 0;
}

void Server::startServer(int portNum){
  struct sockaddr_in serverAddr;

  socketID = socket(AF_INET, SOCK_STREAM, 0);

  memset(&serverAddr, 0, sizeof(struct sockaddr_in));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(portNum);

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

void Server::connectTo(string IP, int portNum){
  otherAiConnectID = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in remote;

  remote.sin_family = AF_INET;
  inet_aton(IP.c_str(), &remote.sin_addr);
  remote.sin_port = htons(portNum);

  int res = connect(otherAiConnectID, (struct sockaddr*)&remote, sizeof(remote)); 
}

void Server::sendString(string s){
  write(connectID, s.c_str(), s.size());
}

string Server::readString(){
  for(int i = 0; i < 1024; i++){
    readBuf[i] = NULL;
  }
  read(connectID, readBuf, 1024);
  return string(readBuf);
}

void Server::sendStringToOtherAi(string s){
  write(otherAiConnectID, s.c_str(), s.size());
}

string Server::readStringFromOtherAi(){
  for(int i = 0; i < 1024; i++){
    otherAiReadBuf[i] = NULL;
  }
  read(otherAiConnectID, otherAiReadBuf, 1024);
  return string(otherAiReadBuf);
}
