#ifndef _Parse_
#define _Parse_

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>

#include "Command.h"
#include "Test.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"

using namespace std;

class Parse
{
    private:
        int cmdIndex;
    public:
        vector<Base*> cmds;
        vector<string> tokens;

        Parse() : cmdIndex(-1) {};
        void parseCmd(string toParse);
        Base* getCmd();
};
#endif





