#ifndef __OR_H__
#define __OR_H__

#include "Connector.h"

class Or: public Connector {
    public:
        Or(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Or() : Connector() {};
        bool execute(int input, int output){
            if(!lcmd->execute(0,1)) {
                if(rcmd->execute(0,1)) {
                    return true;
                }
                else {
                    return false;
                }
            }
            return true;            
        };
};

#endif