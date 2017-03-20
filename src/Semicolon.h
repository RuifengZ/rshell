#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__
#include "Connector.h"

class Semicolon: public Connector {
    public:
        Semicolon(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Semicolon() : Connector() {};
        bool execute(int input, int output){
            lcmd->execute(0,1);
            if(rcmd->execute(0,1)) {
                return true;
            }
            else {
                return false;
            }
        };
};
#endif