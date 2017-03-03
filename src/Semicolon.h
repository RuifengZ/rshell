#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__
#include "Connector.h"

class Semicolon: public Connector {
    public:
        Semicolon(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Semicolon() : Connector() {};
    virtual bool execute(){
        lcmd->execute();
        if(rcmd->execute()) {
            return true;
        }
        else {
            return false;
       }
    };
};
#endif