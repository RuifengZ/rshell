#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "Base.h"
#include <cstdlib>
using namespace std;

class Connector: public Base {
    protected:
        Base* lcmd; //left command of the connector
        Base* rcmd; //right command of the connector

    public:
        Connector(Base* cmd1, Base* cmd2) : lcmd(cmd1), rcmd(cmd2) {};
        Connector() : lcmd(NULL), rcmd(NULL) {};
        virtual bool execute(int input, int output) = 0;
        void setLine(string newP) {};
};
#endif