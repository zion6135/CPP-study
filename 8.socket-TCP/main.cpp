#include "SocketTCP.h"
#include <string>
int main(int argc, char **argv)
{
    SocketTCP socket;
    if ( !strcmp(argv[1], "client")) {
        socket.init(1);  //server 
    } else {
        socket.init(0);  //server 
    }
    while(1);
    return 0;
}