//main.cpp

#include <iostream>
#include <stdio.h>
#include "server/Server.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Server serverObj;
    serverObj.handleSocketWork();
    std::cout << "Hello, World! : %d\n"<<serverObj.getProtNumberForSocket();
    return 0;
}
