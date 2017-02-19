#ifndef _Parse_
#define _Parse_

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "Command.h"

using namespace std;

class Parse
{
    public:
    string cmdList_P [99][2];
    vector<Command*> cmds;
    Parse() {};
    void parseCmd(string toParse);
};
#endif





