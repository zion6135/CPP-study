
#ifndef __SOCKETTCP_H__
#define __SOCKETTCP_H__

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
typedef struct {
    int a;
    char b[10];
}data_t;

class SocketTCP {
// receive
public:
    int init(int a);
    void startProcMsg_recv();
    int clientThread();

    long readn( int fd,  void *buf, size_t count);

private:
    int initSocket();
    int ServerThread();

    deque<data_t*> dequeMsgs_recv;
    mutex mutex_recv;
    sem_t sem_recv;
// send
private:
    int sendMsg(const char* msg);
    void startProcMsg_send();

    deque<data_t*> dequeMsgs_send;
    mutex mutex_send;
    sem_t sem_send;

    int socket_fd;
    int connect_fd;
};
#endif

