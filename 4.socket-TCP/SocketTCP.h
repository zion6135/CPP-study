
#ifndef __SOCKETUDP_H__
#define __SOCKETUDP_H__
#include <ctype.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <list>
#include <pthread.h>
#include <stdarg.h>  // va_list
#include <sys/slog.h>
#include <sys/slog2.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <map>
#include <deque>
#include <mutex>
#include <semaphore.h>

#include "cjson.h"
#include "HavpIPC.h"
#include "DevToParkModClient.h"
#include <deque>




class SocketUDP {
// receive
public:
    int init();
    void startProcMsg_recv();

private:
    int initSocket();
    int socketThread();
// send
private:
    int send(const char* msg);
    void startProcMsg_send();
};
#endif
