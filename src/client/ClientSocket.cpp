#include "ClientSocket.h"

#define ENUM_TO_STR(ENUM) std::string(#ENUM)

bool ClientSocket::TryLogin(int &socketFd, std::string userName)
{    
    Connecter(socketFd);
    std::string msg = "login, " + userName;
    size_t nrBytes = send(socketFd, msg.c_str(), msg.length(), 0);

    if (nrBytes != msg.length())
    {
        std::cout << "not everything is sent (" << nrBytes << "/" << msg.length() << " bytes sent)\n";
    }
    const int BufferSize = 100;
    char buffer[BufferSize];
    int incBytes = read(socketFd, buffer, BufferSize - 1);
    if (incBytes >= 0)
    {
        buffer[incBytes] = '\0';
        std::cout << "received " << incBytes << " bytes: " << buffer << std::endl;
    }

    if (strcmp(buffer, "ACK"))
    {
        Disconnect(socketFd);
        return true;
    }
    Disconnect(socketFd);
    return false;

}

void ClientSocket::Connecter (int &socketFd)
{
    socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketFd == -1)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PortNumber);

    int result = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);
    if (result != 1)
    {
        perror("could not convert ip address to network address structure");
        exit(EXIT_FAILURE);
    }
    else
    {
        result = connect(socketFd, (struct sockaddr*)&sa, sizeof sa);
        std::cout << result;
        if (result < 0)
        {
            perror("connect failed");
            close(socketFd);
            exit(EXIT_FAILURE);
        }
    }
}

void ClientSocket::Disconnect (int &socketFd)
{
    if (shutdown(socketFd, SHUT_RDWR) < 0)
    {
        perror("shutdown failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    close(socketFd);
}

void ClientSocket::Messenger (int &socketFd, std::string cmd, std::string userName)
{
    Connecter(socketFd);
    std::string message;
    bool exit = false;
    std::cout << "HDD DISK\n";
    //while(!exit)
    //{
        /*
        if (cmd == add || cmd == rm || cmd == get)
        {
            std::getline(std::cin, message);
            std::cout << "your  was: " << message << std::endl;
            Connecter(socketFd); 
            if(message == "exit")
            {
                exit = true;
            }
            message =  + ", " + userName + ", " + message;
        }
        else
        {
            message = ENUM_TO_STR(cmd) + ", " + userName;
        }
        */
        //std::getline(std::cin, message);
        message = cmd + "," + userName;
        std::cout << message;
        size_t nrBytes = send(socketFd, message.c_str(), message.length(), 0);

        if (nrBytes != message.length())
        {
            std::cout << "not everything is sent (" << nrBytes << "/" << message.length() << " bytes sent)\n";
        }

        const int BufferSize = 100;
        char buffer[BufferSize];

        int incBytes = read(socketFd, buffer, BufferSize - 1);
        if (incBytes >= 0)
        {
            //handle readed items
            buffer[incBytes] = '\0';
            std::cout << "received " << incBytes << " bytes: " << buffer << std::endl;
        }
        
        Disconnect(socketFd);
    //}  
}



