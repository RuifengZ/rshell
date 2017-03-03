#include "Command.h"

//constructer, Passes in string command using stringstream
//pushes the command and flags to char*[] cmdLine for execvp use
Command::Command(string ucmd){
    
    string cmd_M, cmd_P;
    istringstream ss(ucmd);
    
    ss >> cmd_M;
    
    cmdLine[0] = strdup(cmd_M.c_str());
    
    int pos = 1;
    while(ss>>cmd_P)
    {
        cmdLine[pos]=strdup(cmd_P.c_str());
       ++pos;
    }
}

//a set command to change the current command
//same as constuctor 
void Command::setLine(string ucmd){
    fill(cmdLine, cmdLine + 99, (char*)NULL);
    string cmd_M, cmd_P;
    istringstream ss(ucmd);
    
    ss >> cmd_M;
    
    cmdLine[0] = (char*)cmd_M.c_str();
    
    int pos = 1;
    while(ss>>cmd_P)
    {
        cmdLine[pos]=(char*)cmd_P.c_str();
        pos++;
    }
}

//forks and executes cmdLine with execvp
bool Command::execute()
{
    int pip[2];
    char instring[20];
    pipe(pip);
    pid_t pid = fork();
    if(pid == 0)
    {
        close(pip[0]); 
        if(execvp(cmdLine[0], cmdLine)==-1)
        {
            perror(cmdLine[0]);
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
    }
    return strcmp(instring, "Fail");
}