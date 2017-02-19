#include "Command.h"

Command::Command(string ucmd, char con){
    connector = con;
    
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

void Command::setLine(string ucmd, char con){
    
    connector = con;
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

char Command::getConnector()
{
    return connector;
}