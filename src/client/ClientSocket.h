#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "../protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <string>

enum Command
{
    add,
    rm,
    get,
    ls
};

class ClientSocket
{
    public:
        ClientSocket();

        static void Connecter(int &socketFd);
        static void Disconnect(int &socketFd);
        static bool TryLogin(int &socketFd, std::string userName);
        static void Messenger (int &socketFd, Command cmd, std::string userName);
};

#endif