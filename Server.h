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
    int otherAiConnectID;
    char readBuf[1024];
    char otherAiReadBuf[1024];

    void startServer(int portNum);

    void acceptConnection();
    void endConnection();
    void connectTo(string IP, int portNum);

    void sendString(string s);
    string readString();

    void sendStringToOtherAi(string s);
    string readStringFromOtherAi();
};

#endif
