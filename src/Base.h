#ifndef __BASE_H__
#define __BASE_H__

using namespace std;

class Base {
    public:
    //base class for abstract use
    std::string name;    
    virtual bool execute(int input, int output) = 0;
    virtual void setLine(string ucmd) = 0;
};

#endif