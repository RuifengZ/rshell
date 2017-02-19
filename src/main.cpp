#include "Execute.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main()
{
    


    string fullCommands;
    //Command* user_cmd = new Command();
    Execute* executer = new Execute();
    Parse* parser = new Parse();
    
    while(fullCommands != "exit")
    {
        // char *userName = getlogin();           
        // if(!userName) {
        //     perror("getlogin() error");       
        // }

        // char hostName[1000];
        // gethostname(hostName, sizeof hostName);

        // cout << userName << "@" <<  hostName << "$ ";
        cout << "$";
        fullCommands = "";
        getline(cin, fullCommands);
        
        if(fullCommands == "exit")
            exit(0);
        
        parser->parseCmd(fullCommands);
        // executer->setCmds(parser);
       
        for(unsigned pos=0; pos<parser->cmds.size(); ++pos)
        {
            executer->executeCmd(parser->cmds.at(pos));
        }
        
    }

    return 0;
}