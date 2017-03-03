#ifndef _Command_
#define _Command_

#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Base.h"
using namespace std;

class Command : public Base
{
    public:
    char* cmdLine[99];
    Command() {};
    Command(string ucmd);
    void setLine(string ucmd);
    bool execute();
};
#endif