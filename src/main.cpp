#include "Parse.h"
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main()
{
    string fullCommands;
    Parse* parser = new Parse();
    
    while(fullCommands != "exit")
    {
        char *userName = getlogin();           
        if(!userName) {
            perror("getlogin() error");       
        }

        char hostName[1000];
        gethostname(hostName, sizeof hostName);

        cout << userName << "@" <<  hostName << "$ ";
        
        fullCommands = "";
        getline(cin, fullCommands);
        
        if(fullCommands == "exit")
            exit(0);
        
        parser->parseCmd(fullCommands);
    }

    return 0;
}