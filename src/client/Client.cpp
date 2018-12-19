#include "ClientSocket.h"

bool connected = false;
int socketFd;
std::string UN = "";


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
    std::cout << ("\n\nLogged in\nPCtoHDDClient\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Logout\n");
    std::cout << ("(2) Get list of items\n");
	std::cout << ("(3) Get item\n");
	std::cout << ("(4) Remove Item\n");
	std::cout << ("(5) Add Item\n");
    std::cout << ("-----------------------\n");
    std::cout << ("(6) Exit\n\n");
    std::cout << ("Choice : ");
}


int main(void)
{
    bool quit = false;
	bool login = false;
	while (!quit)
	{
		if (!login)
		{
			char choice = '\0';
			loginMenu();
			std::cin >> choice;
			std::cin.ignore();

			switch(choice)
			{
				case '1':
					//login
					std::cout << "Username: ";
        			std::getline(std::cin, UN);
					login = ClientSocket::TryLogin(socketFd, UN);
					if(!login)
					{
						std::cout << "Wrong Username";
					}
					else
					{
						std::cout << "Login succesfull";
					}
					break;
				case '2':
					//exit
					quit = true;
					break;
				default:
					std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
					break;
			}
			
		}
		else
		{
			char choice = '\0';
			showMenu();
			std::cin >> choice;
			std::cin.ignore();

			switch(choice)
			{
			case '1' :
				// Logout
				login = false;
				break;
			case '2' :
				// get list
				ClientSocket::Messenger(socketFd, ls, UN);
				break;
			case '3' :
				// get item
				ClientSocket::Messenger(socketFd, get, UN);
				break;
			case '4' :
				// remove item
				ClientSocket::Messenger(socketFd, rm, UN);				
				break;
			case '5':
				//Add item
				ClientSocket::Messenger(socketFd, add, UN);
			case '6':
				//exit
				quit = true;
				login = false;
				break;
			default:
				std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
				break;
			}
		}
	}
    return 0;
}
