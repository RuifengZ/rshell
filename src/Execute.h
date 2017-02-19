#ifndef _Execute_
#define _Execute_

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include "Command.h"
#include "Parse.h"
using namespace std;

class Execute
{
    private:
    pid_t pid;
    vector<Command*> cmds;
    bool skipNext;
    
    public:
    Execute():skipNext(false) {};
    // Execute(Command* ucmd) : cmd_E(ucmd) {};
    void executeCmd(Command* cmd);
    void addCmd(Command* cmd);
    void setCmds(Parse* p);
};
#endif