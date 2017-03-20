#ifndef __PIPE_H__
#define __PIPE_H__

#include <fstream> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Connector.h"


class Pipe: public Connector{
    public:
        Pipe(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Pipe() : Connector() {};
        
        bool execute(int input, int output){
            int fds[2];
        
            if(pipe(fds) == -1) {
                perror("pipe");
                return false;
            }
        
        
            if(!lcmd->execute(input,fds[1])) {
                return false;
            }
        
            close(fds[1]);
        
            if(!rcmd->execute(fds[0],output)) {
                return false;
            }
            close(fds[0]);
            return true;
        };
};

#endif