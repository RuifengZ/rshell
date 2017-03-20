#ifndef __REDIROO_H__
#define __REDIROO_H__

#include <fstream> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Connector.h"


class Rediroo: public Connector{
    public:
        Rediroo(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Rediroo() : Connector() {};
        
        bool execute(int input, int output){
            string ofilename = rcmd->name;
            int dupout = dup(1);
            close(1);
            int out = open(ofilename.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            dup(out);
            
            bool ret = lcmd->execute(0,1);
            
            close(1);
            dup(dupout);
            
            return ret;
        };
};

#endif