#include "Server.h"

Server::Server(){
}

void Server::startServer(){
  struct sockaddr_in serverAddr;

  int socketID = socket(AF_INET, SOCK_STREAM, 0);

  memset(&serverAddr, 0, sizeof(struct sockaddr_in));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(44423);





  bind(socketID, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  listen(socketID, 5);

  for(;;){
    cout << "Before accept... \n";
    int connectID = accept(socketID, (sockaddr *) NULL, NULL);
    cout << "After accept... \n";
    write(connectID, "this is a test, this is only a test.\n", (size_t)15);
    shutdown(connectID, 2);
    close(connectID);
  }

  //socklen_t peer_addr_size = sizeof(struct sockaddr_in);
  //int cfd = accept(socketID, (struct sockaddr *) &peer_addr, &peer_addr_size);
}
