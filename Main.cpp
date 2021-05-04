#include "System.h"

int main()
{
    string line;
    getline(cin,line);
    System start(line);

    while(line!="exit"){
        start.callFunctions();
        getline(cin,line);
        start = System(line);
    }
    return 0;
}