#include "SocketUDP.h"

int main(int argc, char **argv)
{
    SocketUDP socket;
    if ( !strcmp(argv[1], "client")) {
        socket.sendUDP("xxx");
        return 0;
    }
    socket.init();
    return 0;
}