#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <iostream>

enum Command
{
    add,
    cd,
    rm,
    get,
    ls, 
    login
};

class ServerSocket
{
public:
    ServerSocket();
    ~ServerSocket();
    
    std::string HandleMessage(int nrBytes);
    void StartUp();
    void Reading();
    void SendMessage(int nrBytes, int communicationFd);


};

#endif
