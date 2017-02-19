#ifndef _Command_
#define _Command_

#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>
using namespace std;

class Command
{
    private:
    char connector;
    public:
    char* cmdLine[99];
    Command() {};
    Command(string ucmd, char con);
    void setLine(string ucmd, char con);
    char getConnector();
};
#endif