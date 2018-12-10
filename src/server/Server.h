#ifndef CONSOLE_H
#define CONSOLE_H

#include "iConsole.h"

class Console
{
public:
    Console(std::string consoleName, int position);
    ~Console();
    
    void TurnOn();
    void TurnOff();
    int GetPos();
    //Set name/pos are not needed, flaw in class diagram
    std::string GetName();

private:
    std::string consoleName;    
    int position;

};

#endif
