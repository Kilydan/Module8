#include "ClientSocket.h"

bool connected = false;
int socketFd;


static void loginMenu( void )
{
    std::cout << ("\n\nLogin\nPCtoHDDClient\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Login\n");
    std::cout << ("(2) Exit\n\n");
    std::cout << ("Choice : ");
}

static void showMenu( void )
{
    std::cout << ("\n\nApplication\nPCtoHDDClient\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Logout\n");
    std::cout << ("(2) Get list of items\n");
	std::cout << ("(3) Get item\n");
	std::cout << ("(4) Remove Item\n");
    std::cout << ("-----------------------\n");
    std::cout << ("(5) Exit\n\n");
    std::cout << ("Choice : ");
}






int main(void)
{
    bool quit = false;
	bool login = false;
	while (!quit)
	{
		while (!login)
		{
			char choice = '\0';
			loginMenu();
			std::cin >> choice;
			std::cin.ignore();

			switch(choice)
			{
				case 1:
				//login
                login = ClientSocket::TryLogin(socketFd);
					break;
				case 2:
				//exit
                quit = true;
					break;
				default:
					std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
					break;
			}
		}

		while(login)
		{
			char choice = '\0';
			showMenu();
			std::cin >> choice;
			std::cin.ignore();

			switch(choice)
			{
			case '1' :
				// Logout
				ClientSocket::Connecter(socketFd);
				break;
			case '2' :
				// get list
				ClientSocket::Disconnect(socketFd);
				break;
			case '3' :
				// get item
				ClientSocket::Messenger(socketFd);
				break;
			case '4' :
				// remove item
				
				break;
			case '5':
				//logout
				quit = true;
				login = false;
				break;
			default:
				std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
				break;
			}
		}
	}

	ClientSocket::Disconnect(socketFd);
    return EXIT_SUCCESS;
}
