#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <iostream>

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
