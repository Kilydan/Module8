#include "Console.h"

Console::Console(std::string name, int pos)
{
    position = pos;
    consoleName = name;
}

void Console::TurnOn()
{

}

void Console::TurnOff()
{

}

int Console::GetPos()
{
    return position;
}
std::string Console::GetName()
{
    return consoleName;
}