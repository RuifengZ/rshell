#include "Execute.h"

void Execute::executeCmd(Command* cmd){
    if(skipNext)
    {
        skipNext = false;
        return;
    }
    
    int pip[2];
    char instring[20];
    string wwww = "000000";
    pipe(pip);
    pid = fork();
    if(pid == 0)
    {
        wwww = "WHOOO";
        //cout << "child: " << pid << endl;
         close(pip[0]); 
        if(execvp((cmd->cmdLine)[0], cmd->cmdLine)==-1)
        {
            perror((cmd->cmdLine)[0]);
            write(pip[1], "Fail", 7);
            exit(1);
        }
        exit(0);
        
    }
    if(pid > 0)
    {
        if(wait(0) == -1)
            perror("wait");
        close(pip[1]);
        read(pip[0], instring, 7);

       // cout << "parent: " << pid << endl;
    }
    
    cout << instring;
    
    if(strcmp(instring, "Fail") == 0 && (cmd->getConnector()) == '&')
    {
        //cout << "skip && " << endl;
        skipNext = true;
    }
    if(!(strcmp(instring, "Fail") == 0) && (cmd->getConnector()) == '|')
    {
        //cout << "skip|| " << endl;
        skipNext = true;
    }

}

void Execute::addCmd(Command* cmd){
    cmds.push_back(cmd);
}
void Execute::setCmds(Parse* p){
    cmds.clear();
    // for(int pos = 0; pos<99; ++pos)
    // {
    //     if((p->cmdList_P)[pos][0] == "")
    //         break;
    //     cmds.push_back( new Command((p->cmdList_P)[pos][0], (p->cmdList_P)[pos][1]));
    // }
    
    // for(unsigned pos=0; pos<cmds.size(); ++pos)
    // {
    //     cout << (cmds.at(pos)->cmdLine)[1] << endl;
    // }
}