#ifndef __AND_H__
#define __AND_H__

#include "Connector.h"

class And: public Connector {
    public:
    //constructors
    And(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
    And() : Connector() {};
    bool execute(){
        if(lcmd->execute())
        {
           if(rcmd->execute())
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