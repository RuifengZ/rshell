#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <stdio.h>

#include "Base.h"
using namespace std;

class Test: public Base{
	public:
	    vector<string> flags;
        Test() {};
        Test(string ucmd);
        bool execute(int input, int output);
        void setLine(string newP);
};
#endif