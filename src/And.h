#ifndef __AND_H__
#define __AND_H__

#include "Connector.h"

class And: public Connector {
    public:
    And(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
    And() : Connector() {};
    
    //execute logic for bash And
    bool execute(int input, int output){
        if(lcmd->execute(0,1))
        {
           if(rcmd->execute(0,1))
           {
               return true;
           }
           else 
           {
               return false;
           }
        }
        else
        {
            return false;
        }
    };
};

#endif