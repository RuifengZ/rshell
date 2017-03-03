#include "Parse.h"

Base* Parse::getCmd(){
    return cmds.at(cmdIndex);
}

void Parse::parseCmd(string toParse){
    cmdIndex = -1;
    cmds.clear();
    tokens.clear();
    char str[1024];
    for(unsigned a=0;a<=toParse.size();a++)
    {
        str[a]=toParse[a];
    }
    char *copy = strdup(str);
    char *res = strtok( str, ";&|()");
    
    while (res) {
        string cmdName = strdup(res);
        if(cmdName != " ")
            tokens.push_back(cmdName);
        if(copy[res-str+strlen(res)] == ';')
            tokens.push_back(";");
        else
            if(copy[res-str+strlen(res)] == '|')
                tokens.push_back("|");
            else
                if(copy[res-str+strlen(res)] == '&')
                    tokens.push_back("&");
                else
                    if(copy[res-str+strlen(res)] == '(')
                        tokens.push_back("(");
                    else
                        if(copy[res-str+strlen(res)] == ')')
                            tokens.push_back(")");
                        else
                            break;
                
        //cout << "ADDED: " << cmdName << " and " << copy[res-str+strlen(res)] << endl;
        
        // string cmdName = strdup(res);
        // if(cmds.empty())
        // {
        //     if(cmdName.substr(0,4) == "test" || cmdName.substr(0,1) == "[")
        //         cmds.push_back(new Test(cmdName));
        //     else
        //         cmds.push_back(new Command(cmdName));
        //     cmdIndex++;
        //     cout << "EMPTY" << endl;
        // }
        // else
        // {
        //     if(next == ';')
        //     {
        //         if(cmdName.substr(0,4) == "test" || cmdName.substr(0,1) == "[")
        //             cmds.push_back(new Semicolon(getCmd(), new Test(cmdName)));
        //         else
        //             cmds.push_back(new Semicolon(getCmd(), new Command(cmdName)));
        //         cmdIndex++;
        //         cout << "SEMICOLON" << endl;
        //     }
        //     else 
        //     {
        //         if (next == '|')
        //         {
        //             if(cmdName.substr(0,4) == "test" || cmdName.substr(0,1) == "[")
        //                 cmds.push_back(new Or(getCmd(), new Test(cmdName)));
        //             else
        //                 cmds.push_back(new Or(getCmd(), new Command(cmdName)));
        //             cmdIndex++;
        //             cout << "OR" << endl;
        //         }
        //         else
        //         {
        //             if (next == '&')
        //             {
        //                 if(cmdName.substr(0,4) == "test" || cmdName.substr(0,1) == "[")
        //                     cmds.push_back(new And(getCmd(), new Test(cmdName)));
        //                 else
        //                     cmds.push_back(new And(getCmd(), new Command(cmdName)));
        //                 cmdIndex++;
        //                 cout << "AND" << endl;
        //             }
        //         }
        //     }

        // }
        // if(copy[res-str+strlen(res)] == ';')
        //     next = ';';
        // else
        //     if(copy[res-str+strlen(res)] == '|')
        //         next = '|';
        //     else
        //         if(copy[res-str+strlen(res)] == '&')
        //             next = '&';
        //         else
        //             next = '0';
        
        //cmds.push_back(new Command(cmdName, copy[res-str+strlen(res)]));
        res = strtok( NULL, ";&|()");
    }
    free(copy);
    
    queue<string> outQueue;
    stack<string> opStack;
    for(unsigned z=0; z<tokens.size(); ++z)
    {
        //cout << z <<":" << tokens.at(z) << " " << endl;
        if(tokens.at(z).size() > 1)
        {
            outQueue.push(tokens.at(z));
        }
        if(tokens.at(z)==")")
        {
            while(opStack.top() != "(")
            {
                outQueue.push(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
        else
        {
            if(tokens.at(z).size() == 1 && tokens.at(z)!=" ")
            {
                opStack.push(tokens.at(z));
            }
        }
    }
    while(!opStack.empty())
    {
        outQueue.push(opStack.top());
        opStack.pop();
    }
    
    // while(!outQueue.empty())
    // {
    //     cout << "queue: " << outQueue.front() << endl;
    //     outQueue.pop();
    // }
    
    stack<string> values;
    while(!outQueue.empty())
    {   
        string token = outQueue.front();
        outQueue.pop();
        if(token.size()>1)
            values.push(token);
        else
        {
            if(token.size() == 1)
            {
                if(cmds.empty())
                {
                    string cmdName2 = values.top();
                    values.pop();
                    string cmdName1 = values.top();
                    values.pop();
                    if(token == ";")
                    {
                        if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                            cmds.push_back(new Semicolon(new Test(cmdName1), new Test(cmdName2)));
                        else
                            if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                cmds.push_back(new Semicolon(new Test(cmdName1), new Command(cmdName2)));
                            else
                                if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                    cmds.push_back(new Semicolon(new Command(cmdName1), new Test(cmdName2)));
                                else
                                    cmds.push_back(new Semicolon(new Command(cmdName1), new Command(cmdName2)));
                        cmdIndex++;
                    }
                    else 
                    {
                        if (token == "|")
                        {
                            if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                                cmds.push_back(new Or(new Test(cmdName1), new Test(cmdName2)));
                            else
                                if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                    cmds.push_back(new Or(new Test(cmdName1), new Command(cmdName2)));
                                else
                                    if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                        cmds.push_back(new Or(new Command(cmdName1), new Test(cmdName2)));
                                    else
                                        cmds.push_back(new Or(new Command(cmdName1), new Command(cmdName2)));           
                            cmdIndex++;
                        }
                        else
                        {
                            if (token == "&")
                            {
                                if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                                    cmds.push_back(new And(new Test(cmdName1), new Test(cmdName2)));
                                else
                                    if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                        cmds.push_back(new And(new Test(cmdName1), new Command(cmdName2)));
                                    else
                                        if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                            cmds.push_back(new And(new Command(cmdName1), new Test(cmdName2)));
                                        else
                                            cmds.push_back(new And(new Command(cmdName1), new Command(cmdName2)));
                                cmdIndex++;
                            }
                        }
                    }
                }
                else
                { 
                    string cmdName2 = values.top();
                    values.pop();
                    if(token == ";")
                    {
                        if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                            cmds.push_back(new Semicolon(getCmd(), new Test(cmdName2)));
                        else
                            cmds.push_back(new Semicolon(getCmd(), new Command(cmdName2)));
                        cmdIndex++;
                    }
                    else 
                    {
                        if (token == "|")
                        {
                            if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                cmds.push_back(new Or(getCmd(), new Test(cmdName2)));
                            else
                                cmds.push_back(new Or(getCmd(), new Command(cmdName2)));
                            cmdIndex++;
                        }
                        else
                        {
                            if (token == "&")
                            {
                                if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                    cmds.push_back(new And(getCmd(), new Test(cmdName2)));
                                else
                                    cmds.push_back(new And(getCmd(), new Command(cmdName2)));
                                cmdIndex++;
                            }
                        }
                    }
                }
            }
        }
        if(outQueue.empty() && values.size() == 1)
        {
            if(values.top().find("test") != string::npos || values.top().find("[") !=  string::npos)
                cmds.push_back(new Test(values.top()));
            else
                cmds.push_back(new Command(values.top()));
            cmdIndex++;
            break;
        }
    }
    cmds.at(cmdIndex)->execute();
}