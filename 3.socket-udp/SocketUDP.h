#ifndef _SocketUDP_H__
#define _SocketUDP_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <thread>


using namespace std;

#define MAX_MSG_SIZE 1024 * 1024 * 2  // 2M
#define SEVER_PORT 8080
#define CLIENT_PORT 8080
#define SEVER_IP "172.20.10.5"
#define CLIENT_IP "172.20.10.5"

class SocketUDP {
/*Server端*/
public:
    int init();
    int main_process();
    int Reveive_Process(const char* data, const int len);

private:
    int Server_Init();
    int Receive_Loop();

/*client*/
public:
    int sendUDP(const string msg);



};

#endif
