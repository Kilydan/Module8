#include "../protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

//bool connected = false;
int socketFd;

static void showMenu( void )
{
    std::cout << ("\n\nMessenger\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Connect to server\n");
    std::cout << ("(2) Disconnect to server\n");
    std::cout << ("(3) Send message\n");
    std::cout << ("-----------------------\n");
    std::cout << ("(4) Exit\n\n");
    std::cout << ("Choice : ");
}

static void Connecter ( int &socketFd )
{
	/*
	if(connected)
	{
		std::cout << "already connected";
	}
	else
	{
	*/	
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
	        //connected = true;
	        std::cout << result;
	        if (result < 0)
	        {
	            perror("connect failed");
	            close(socketFd);
	            exit(EXIT_FAILURE);
	        }
	    }
	//}
}

static void Disconnect ( int &socketFd )
{
    if (shutdown(socketFd, SHUT_RDWR) < 0)
    {
        perror("shutdown failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    close(socketFd);
    //connected = false;
}

static void Messager ( int &socketFd )
{
	/*
	if(!connected)
	{
		std::cout << "No connection, going back to the menu!";
	}
	else
	{
*/
		std::string message;
		bool exit = false;
		std::cout << "Welcome to the messager, type exit to leave \n";
		while(!exit)
		{
			std::cout << "Message: ";
			std::getline(std::cin, message);
			std::cout << "your message was: " << message << std::endl;
			Connecter( socketFd );	
			if(message == "exit")
			{
				exit = true;
			}
			else
			{
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
					buffer[incBytes] = '\0';
			        std::cout << "received " << incBytes << " bytes: " << buffer << std::endl;
				}
			}
			Disconnect(socketFd);
		}
	//}
	
}

int main(void)
{

    bool quit = false;
    while(!quit)
    {
		char choice = '\0';
        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch(choice)
        {
    	case '1' :
            // Connect to Server
    		Connecter( socketFd );
            break;
    	case '2' :
            // Disconnect from server
    		Disconnect( socketFd );
            break;
    	case '3' :
            // Send message
            Messager( socketFd );
            break;
    	case '4' :
            // Exit
    		quit = true;
            break;
        default:
            std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
            break;
        }
    }

    close(socketFd);
    return EXIT_SUCCESS;
}