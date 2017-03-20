#ifndef __REDIRI_H__
#define __REDIRI_H__

#include <fstream> 
#include <unistd.h>
#include "Connector.h"


class Rediri: public Connector {
    public:
        Rediri(Base* lcmd, Base* rcmd) : Connector(lcmd, rcmd) {};
        Rediri() : Connector() {};
        
        bool execute(int input, int output){
            string ifilename = rcmd->name;

            ifstream ifs;
            ifs.open(ifilename.c_str());
            if(!ifs.is_open())
                cout << "EEEEEEE" << endl;
            
            string newP;
            getline(ifs, newP);
            
            lcmd->setLine(newP);
                
            ifs.close();
            
            return lcmd->execute(0,1);
        };
};

#endif