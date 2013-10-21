#ifndef SERVER_H
#define SERVER_H

#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"

#include <cstring>
#include <unistd.h>
#include <iostream>
#include <cerrno>

using namespace std;

class Server{
  public:

    Server();

    int socketID;
    int connectID;
    char readBuf[1024];

    void startServer();

    void acceptConnection();
    void endConnection();
    void connectTo();

    void sendString(string s);
    string readString();
};

#endif
