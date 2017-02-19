#include "Parse.h"

void Parse::parseCmd(string toParse){
    
    cmds.clear();
    char str[1024];
    for (unsigned a=0;a<=toParse.size();a++)
    {
        str[a]=toParse[a];
    }
    char *copy = strdup(str);
    char *res = strtok( str, ";&|#" );
    while (res) {
        if(copy[res-str+strlen(res)] == '#')
            break;
        cmds.push_back(new Command(strdup(res), copy[res-str+strlen(res)]));
        res = strtok( NULL, ";&|#" );
    }
    free(copy);
}