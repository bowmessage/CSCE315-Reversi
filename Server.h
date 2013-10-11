#ifndef SERVER_H
#define SERVER_H

#include "arpa/inet.h"
#include "sys/types.h"
#include "sys/socket.h"

#include <cstring>
#include <unistd.h>
#include <iostream>

using namespace std;

class Server{
  public:

    Server();

    void startServer();

};


#endif
