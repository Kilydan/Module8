#include "ServerSocket.h"



int main(void)
{
    ServerSocket* serverSocket = new ServerSocket();
    serverSocket->StartUp();
    serverSocket->Reading();
    
    
}
