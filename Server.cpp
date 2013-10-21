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
  cout << "got connect\n";
}
void Server::endConnection(){
  shutdown(connectID, 2);
  close(connectID);
}

void Server::connectTo(string IP, int portNum){
  int connectingSocketID = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in remote;

  remote.sin_family = AF_INET;
  inet_aton(IP.c_str(), &remote.sin_addr);
  remote.sin_port = htons(portNum);

  int res = connect(connectingSocketID, (struct sockaddr*)&remote, sizeof(remote)); 
  cout << "tried to connect, res: " << res << "\n";
  cout << "errno: " << errno << "\n";
}

void Server::sendString(string s){
  write(connectID, s.c_str(), s.size());
}

string Server::readString(){
  read(connectID, readBuf, 1024);
  cout << "recv: " << string(readBuf) << "\n";
  return string(readBuf);
}
