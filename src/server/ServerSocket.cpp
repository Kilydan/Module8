#include "../protocol.h"
#include "ServerSocket.h"
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/select.h>
#include <unistd.h>

static const int SelectTimeout = 2;
int listenFd, nrBytes;
const int BufferSize = 100;
char buffer[BufferSize];
int communicationFd;

ServerSocket::ServerSocket()
{

}
ServerSocket::~ServerSocket(){

}

std::string ServerSocket::HandleMessage(int nrBytes)
{ 
    buffer[nrBytes] = '\0';
    if(buffer == "ls")
    {
        std::cout << "message was ls";
        SendMessage(nrBytes, communicationFd);
    }
    std::cout << "message: " << buffer << std::endl;
    return std::string(buffer);
}
void ServerSocket::StartUp()
{
    listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenFd < 0)
    {       
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PortNumber);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        perror("bind failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenFd, 10) < 0)
    {
        perror("listen failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }
}
void ServerSocket::SendMessage(int nrBytes, int communicationFd)
{
    if (nrBytes > 0)
    {
        std::string respond = HandleMessage(nrBytes);
        size_t nrBytes = send(communicationFd, respond.c_str(), respond.length(), 0);    
        //error check to see if all bytes where send succesfully
        if (nrBytes != respond.length())
        {
            std::cout << "not everything is sent (" << nrBytes << "/" << respond.length() << " bytes sent)\n";
        }        
    }
}
void ServerSocket::Reading()
{
    while (true)
    {        
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(listenFd, &readFds);

        struct timeval timeout;
        timeout.tv_sec = SelectTimeout;
        timeout.tv_usec = 0;

        int nrSockets = select(FD_SETSIZE, &readFds, NULL, NULL, &timeout);

        if (nrSockets < 0) // error situation
        {
            perror("error from calling socket");
        }
        else if (nrSockets == 0) // timeout
        {
            std::cout << "still listening\n";
        }
        else // found activity, find out what kind
        {
            if (FD_ISSET(listenFd, &readFds))
            {
                communicationFd = accept(listenFd, NULL, NULL);
                if (communicationFd < 0)
                {
                    perror("accept failed");
                    close(listenFd);    
                    exit(EXIT_FAILURE);
                }
                //Reading from clients  
                nrBytes = read(communicationFd, buffer, BufferSize - 1);
                //send message back depening on the received message
                SendMessage(nrBytes, communicationFd);
                
                //connection error handling
                if (shutdown(communicationFd, SHUT_RDWR) < 0)
                {
                    perror("shutdown failed");
                    close(communicationFd);
                    close(listenFd);
                    exit(EXIT_FAILURE);
                }
                close(communicationFd);
            }
        }
    }
}