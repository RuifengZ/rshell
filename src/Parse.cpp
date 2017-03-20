#include "Parse.h"

Base* Parse::getCmd(){
    return cmds.at(cmdIndex);
}

void Parse::parseCmd(string toParse){
    cmdIndex = -1;
    cmds.clear();
    stack<string> tokens;
    char str[1024];
    
    //  -----------------Parentheses space code---------------
    vector<unsigned> indices;
    string tempString = "";
    for (unsigned i=0;i<toParse.length();++i)
    {
        if (toParse.at(i) == '(' || toParse.at(i) == ')')
        {
            indices.push_back(i);
        }
    }
    
    for (unsigned i=0;i<toParse.length();++i)
    {
        for (unsigned j=0;j<indices.size();++j)
        {
            if (indices.at(j) == i)
            {
                tempString += " ";
            }
        }
        tempString += toParse.at(i);
    }
    toParse = tempString; 
    
    //----------------------------------------------------------
    
    for(unsigned a=0;a<=toParse.size();a++) // copy command toParse to a char array
    {
        str[a]=toParse[a];
    }
    //cout << str << endl;
    char *copy = strdup(str);
    char *res = strtok( str, ";&|()><"); //seperate str by limiters
    
    while (res) {
        string cmdName = strdup(res); //read command name
        if(cmdName != " ")
            tokens.push(cmdName);       //push to tokens for prefix conversion
        if(copy[res-str+strlen(res)] == ';')
            tokens.push(";");
        else
            if(copy[res-str+strlen(res)] == '|'){
                if(copy[res-str+strlen(res) + 1] == '|')
                    tokens.push("||");
                else
                    tokens.push("|");
            }
            else
                if(copy[res-str+strlen(res)] == '&')
                    tokens.push("&");
                else
                    if(copy[res-str+strlen(res)] == '>'){
                        if(copy[res-str+strlen(res) + 1] == '>')
                            tokens.push(">>");
                        else
                            tokens.push(">");
                    }
                    else
                        if(copy[res-str+strlen(res)] == '<')
                            tokens.push("<");
                        else
                            if(copy[res-str+strlen(res)] == '(')
                                tokens.push(")");
                            else
                                if(copy[res-str+strlen(res)] == ')')
                                    tokens.push("(");
                                else
                                    break;
        res = strtok( NULL, ";&|()><");
    }
    free(copy);
    
    // while(!tokens.empty())
    // {
    //     cout << "stack: " << tokens.top() << endl;
    //     tokens.pop();
    // }
    
    //convert the inputed commands to prefix notation 
    queue<string> outQueue;
    stack<string> opStack;
    while(!tokens.empty())
    {
        string read = tokens.top();
        tokens.pop();
        if(read.size() > 1 && read != ">>" && read != "||")
        {
            outQueue.push(read);
        }
        if(read==")")
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
            if((read.size() == 1 || read==">>" || read=="||") && read!=" " )
            {
                opStack.push(read);
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
    
    
    // evaluates prefix notation
    // uses the And, Semicolon, and Or classes as operators with two children
    stack<string> values;
    while(!outQueue.empty()) 
    {   
        string token = outQueue.front();
        outQueue.pop();
        if(token.size()>1 && token !=">>" && token !="||")   //check if operand
            values.push(token);
        else
        {
            if(token.size() == 1 || token == ">>" || token == "||")
            {
                if(cmds.empty()) //check if cmds is initialized
                {
                    string cmdName1 = values.top(); //read operands
                    values.pop();
                    string cmdName2 = values.top();
                    values.pop();
                    if(token == ";")
                    {
                        //extra test cases to determin if command is a test command
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
                        if (token == "||")
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
                            else
                            {
                                if (token == ">")
                                {
                                    if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                                        cmds.push_back(new Rediro(new Test(cmdName1), new Test(cmdName2)));
                                    else
                                        if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                            cmds.push_back(new Rediro(new Test(cmdName1), new Command(cmdName2)));
                                        else
                                            if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                                cmds.push_back(new Rediro(new Command(cmdName1), new Test(cmdName2)));
                                            else
                                                cmds.push_back(new Rediro(new Command(cmdName1), new Command(cmdName2)));
                                    cmdIndex++;
                                }
                                else
                                {
                                    if (token == "<")
                                    {
                                        if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                                            cmds.push_back(new Rediri(new Test(cmdName1), new Test(cmdName2)));
                                        else
                                            if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                                cmds.push_back(new Rediri(new Test(cmdName1), new Command(cmdName2)));
                                            else
                                                if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                                    cmds.push_back(new Rediri(new Command(cmdName1), new Test(cmdName2)));
                                                else
                                                    cmds.push_back(new Rediri(new Command(cmdName1), new Command(cmdName2)));
                                        cmdIndex++;
                                    }
                                    else
                                    {
                                        if (token == ">>")
                                        {
                                            if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                                                cmds.push_back(new Rediroo(new Test(cmdName1), new Test(cmdName2)));
                                            else
                                                if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                                    cmds.push_back(new Rediroo(new Test(cmdName1), new Command(cmdName2)));
                                                else
                                                    if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                                        cmds.push_back(new Rediroo(new Command(cmdName1), new Test(cmdName2)));
                                                    else
                                                        cmds.push_back(new Rediroo(new Command(cmdName1), new Command(cmdName2)));
                                            cmdIndex++;
                                        }
                                        else{
                                            if (token == "|")
                                            {
                                                if((cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos) && (cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos))
                                                    cmds.push_back(new Pipe(new Test(cmdName1), new Test(cmdName2)));
                                                else
                                                    if(cmdName1.find("test") != string::npos || cmdName1.find("[") != string::npos)
                                                        cmds.push_back(new Pipe(new Test(cmdName1), new Command(cmdName2)));
                                                    else
                                                        if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                                            cmds.push_back(new Pipe(new Command(cmdName1), new Test(cmdName2)));
                                                        else
                                                            cmds.push_back(new Pipe(new Command(cmdName1), new Command(cmdName2)));
                                                cmdIndex++;
                                            }
                                        }
                                    }
                                }
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
                        if (token == "||")
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
                            else
                            {
                                if (token == ">")
                                {
                                    if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                        cmds.push_back(new Rediro(getCmd(), new Test(cmdName2)));
                                    else
                                        cmds.push_back(new Rediro(getCmd(), new Command(cmdName2)));
                                    cmdIndex++;
                                }
                                else
                                {
                                  if (token == "<")
                                    {
                                        if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                            cmds.push_back(new Rediri(getCmd(), new Test(cmdName2)));
                                        else
                                            cmds.push_back(new Rediri(getCmd(), new Command(cmdName2)));
                                        cmdIndex++;
                                    }
                                    else
                                    {
                                      if (token == ">>")
                                        {
                                            if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                                cmds.push_back(new Rediroo(getCmd(), new Test(cmdName2)));
                                            else
                                                cmds.push_back(new Rediroo(getCmd(), new Command(cmdName2)));
                                            cmdIndex++;
                                        }
                                        else
                                        {
                                            if (token == "|")
                                            {
                                                if(cmdName2.find("test") != string::npos || cmdName2.find("[") != string::npos)
                                                    cmds.push_back(new Pipe(getCmd(), new Test(cmdName2)));
                                                else
                                                    cmds.push_back(new Pipe(getCmd(), new Command(cmdName2)));
                                                cmdIndex++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(outQueue.empty() && values.size() == 1) //check if only one command was entered
        {
            if(values.top().find("test") != string::npos || values.top().find("[") !=  string::npos)
                cmds.push_back(new Test(values.top()));
            else
                cmds.push_back(new Command(values.top()));
            cmdIndex++;
            break;
        }
    }
    // cout << "CMDINDEX: " << cmdIndex << endl;
    // cout << "CMDSIZE1: " << cmds.size() << endl;
    cmds.at(cmdIndex)->execute(0,1);
}