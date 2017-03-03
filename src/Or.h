#ifndef __OR_H__
#define __OR_H__

#include "Connector.h"

class Or: public Connector {
    public:
        Or(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Or() : Connector() {};
        bool execute(){
            if(!lcmd->execute()) {
                if(rcmd->execute()) {
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