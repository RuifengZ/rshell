#include "Command.h"

//constructer, Passes in string command using stringstream
//pushes the command and flags to char*[] cmdLine for execvp use
Command::Command(string ucmd){
    
    string cmd_M, cmd_P;
    istringstream ss(ucmd);
    
    ss >> cmd_M;
    name = cmd_M;
    
    cmdLine[0] = strdup(cmd_M.c_str());
    
    pos = 1;
    while(ss>>cmd_P)
    {
        cmdLine[pos]=strdup(cmd_P.c_str());
       ++pos;
    }
}

//a set command to change the current command
//same as constuctor 
void Command::setLine(string ucmd){
    string cmd_P;
    istringstream ss(ucmd);

    while(ss>>cmd_P)
    {
        cmdLine[pos]=strdup(cmd_P.c_str());
       ++pos;
    }
}

//forks and executes cmdLine with execvp
bool Command::execute(int input, int output)
{
    bool error = true;
    pid_t pid = fork();
    if(pid == 0)
    {
        if(dup2(input,0) == -1) {
            perror("dup2");
            return false;
        }
        if(dup2(output,1) == -1) {
            perror("dup2");
            return false;
        }
        if(execvp(cmdLine[0], cmdLine)==-1)
        {
            error = false;
            perror(cmdLine[0]);
            exit(1);
        }
        exit(0);
        
    }
    if(pid > 0)
    {
       int status;
       if(waitpid(pid,&status,0) == -1)
           perror("wait");
       if(WEXITSTATUS(status) != 0)
           error = false;
    }
    return error;
}