#include "Test.h"

Test::Test(string ucmd){
    string cmd_P;
    bool bracket = false;
    if(ucmd.substr(0,1) == "[")
    {
        ucmd.erase(0,1);
        ucmd.erase(ucmd.size() - 1,1);
        bracket = true;
    }
    istringstream ss(ucmd);
    
    if(!bracket)
        ss >> name;
        
    
    while(ss>>cmd_P)
    {
        flags.push_back(cmd_P);
    }
    
}


void Test::setLine(string newP){
    string cmd_P;
    istringstream ss(newP);
    while(ss>>cmd_P)
    {
        flags.push_back(cmd_P);
    }
    
}

bool Test::execute(int input, int output){
    struct stat buf;
    string flag;
    string path;
    bool exists = false;

    if(flags.empty())
    {
        perror("test");
        return false;
    }
    if(flags.size() == 1) {
        flag = "-e";
        path = flags.back();
    }
    else {
        path = flags.back();
        flags.pop_back();
        flag = flags.back();
    }

    int statret = stat(path.c_str(),&buf);
    if (statret == 0) {
        exists = true;
    }

    if(statret == -1) {
        perror("stat");
        return false;
    }

    if(flag == "-e") {
        cout << "(true)" << endl;
        return exists;
    }
    else if(flag == "-d") {
        if(S_ISDIR(buf.st_mode)) {
            cout << "(true)" << endl;
            return true;
        }
        else {
            cout << "(false)" << endl;
            return false;
        }
    }
    else if(flag == "-f") {
         if(S_ISREG(buf.st_mode)) {
             cout << "(true)" << endl;
             return true;
         }
        else {
            cout << "(false)" << endl;
            return false;
        }
    }
    else {
        cout << "Error: In test flag " << flag << " is not valid."  << endl;
        return false;
    }
}