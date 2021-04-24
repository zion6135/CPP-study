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
#include <pthread.h>

#include <deque>
#include <map>
#include <deque>
#include <mutex>
#include <semaphore.h>
#include <vector>
using namespace std;

#define MAX_MSG_SIZE 1024  // 2M
#define SEVER_PORT 8080
#define CLIENT_PORT 8080
#define SEVER_IP "172.17.0.1"
#define CLIENT_IP "127.0.0.1"
//172.16.0.89
//172.17.0.1
typedef struct {
    int a;
    char b[10];
}data_t;

class SocketUDP {
/*Server端*/
public:
    int init();
    int main_process();
    int Reveive_Process( data_t* data, const int len);

private:
    int Server_Init();
    int Receive_Loop();

/*client*/
public:
    int sendUDP(const string msg);


/*message queue*/
public:
    void startProcMsg();

private:
    vector<data_t*> data_m;  //消息队列
    mutex m_mutex;  //锁
    sem_t m_sem;  //信号量
};

#endif
