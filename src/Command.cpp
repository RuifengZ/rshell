#include "Command.h"

Command::Command(string ucmd){
    
    //cout << "RECIEVED CMD: " << ucmd << "   RECIEVED CON: " << con << endl;
    string cmd_M, cmd_P;
    istringstream ss(ucmd);
    
    ss >> cmd_M;
    
    cmdLine[0] = strdup(cmd_M.c_str());
    
    int pos = 1;
    while(ss>>cmd_P)
    {
 
       // cout << "CMD" << pos<< ": " << cmd_P << endl;
        cmdLine[pos]=strdup(cmd_P.c_str());
       // cout << "RECORDED: " << cmdLine[pos]<< endl;
               ++pos;
    }
    
    
    // for(int a=0; a<pos; ++a)
    // {
    //     cout << "ACTUAL: " << a<< ": " << (cmdLine)[a] << endl;
    // }
    
    //cout << "TEST1: " << ucmd << "|||" << con <<endl;
}

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
    //cout << "TEST2: " << ucmd << "   " << con <<endl;
}

bool Command::execute()
{
    int pip[2];
    char instring[20];
    pipe(pip);
    pid_t pid = fork();
    if(pid == 0)
    {
        //cout << "child: " << pid << endl;
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

       // cout << "parent: " << pid << endl;
    }
    return strcmp(instring, "Fail");

}