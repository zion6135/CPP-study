#include "SocketTCP.h"

#define MAX_MSG_SIZE 1024
#define DEFAULT_PORT 7070
#define DEFAULT_IP "192.168.43.157" //ifconfig

struct body {
    uint32_t length;
    char buffer[1024];
};//__attribute((packed)); //不考虑字节对齐body_t;
struct body recv_buffer;


int SocketTCP::init(int a)
{
    switch (a) {
        case 0: {//server
            printf("%d:%s\n", __LINE__, __FUNCTION__);
            thread tcp(&SocketTCP::ServerThread, this);
            tcp.detach();
            printf("tcp server end\n");
            break;
        }
        
        case 1: { //client
            printf("%d:%s\n", __LINE__, __FUNCTION__);
            thread tcp(&SocketTCP::clientThread,this);
            tcp.detach();
            printf("tcp client end\n");
            break;
        }
    }
    return 0;
}

int SocketTCP::initSocket()
{
    struct sockaddr_in servaddr;
    //初始化Socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    //初始化
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(DEFAULT_IP);  // IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    servaddr.sin_port = htons(DEFAULT_PORT);  //设置的端口为DEFAULT_PORT

    //将本地地址绑定到所创建的套接字上
    int ret = ::bind(socket_fd, (struct sockaddr*)(&servaddr), sizeof(servaddr));
    if (ret < 0) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
}

int SocketTCP::sendMsg(const char* msg)
{
    if (send(connect_fd, msg, strlen(msg), 0) == -1)
        perror("send error");
    //close(connect_fd);
}
void SocketTCP::startProcMsg_send() //发送消息子线程
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);

    thread t([this]() {
        while (true) {
            sem_wait(&sem_send);
            printf("%d Start process msg\n", __LINE__);
            deque<data_t*> dequeMsgs;
            mutex_send.lock();
            dequeMsgs.swap(dequeMsgs_send);
            mutex_send.unlock();
            for (auto it = dequeMsgs.begin(); it != dequeMsgs.end(); it++) {
                printf("%d processing msg\n", __LINE__);

/************************发送数据*****************************************************************/
                delete *it;
            }
            printf("%d End process msg\n", __LINE__);
        }
    });
    t.detach();
}

void SocketTCP::startProcMsg_recv() // 接收消息子线程
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);

    thread t([this]() {
        while (true) {
            sem_wait(&sem_recv);
            printf("%d Start process msg\n",__LINE__);

            deque<data_t*> dequeMsgs;
            mutex_recv.lock();
            dequeMsgs.swap(dequeMsgs_recv);
            mutex_recv.unlock();

            for (auto it = dequeMsgs.begin(); it != dequeMsgs.end(); it++) {

                printf("over\n");
                free(*it);
            }
            printf("%d End process msg\n",__LINE__);
        }
    });
    t.detach();
}



long SocketTCP::readn( int fd,  void *buf, size_t count)
{
    size_t nleft= count;
    long nread;
    char *bufp = (char *)buf;

    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
                continue;
            return -1;
        } else if (nread == 0) { // 对方关闭或者已经读到eof
            return count - nleft;
        }
        bufp += nread;
        nleft -= nread;
    }
    return count;
}
int SocketTCP::clientThread()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
 
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(DEFAULT_PORT);
    addr.sin_addr.s_addr = inet_addr(DEFAULT_IP);
 
    int len = sizeof(addr);
    if (-1 == connect(fd, (struct sockaddr*)&addr, len)){
        printf("Connect to server fail\n");
        return 0;
    }
#if 0
    char szMsg[128];
    char datasend[256];
    while(scanf("%s", szMsg)){
        if (!strcmp(szMsg, "quit")){  break; }
        int len = strlen(szMsg);
        memcpy(datasend,&len,4);
        printf("length == %d",len);
        memcpy(datasend+4,szMsg,strlen(szMsg));
        send(fd, szMsg, len + 4,0);//向server发数据
    }

    close(fd);
    #elif 1
    char demo[9];
    int length = 5;
    memcpy(demo, &length, 4);
    memcpy(demo+4 , "alive", 5);
    send(fd, demo, 9, 0);
    memset(demo,0,9);
    close(fd);
    #endif
    printf("===over\n");
    return 0;
}


int SocketTCP::ServerThread()
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);
    struct sockaddr_in addr ;
    char buff[MAX_MSG_SIZE];
    int ret;
    socklen_t length = sizeof(addr);

    // startProcMsg_recv();
    // startProcMsg_send();

    initSocket();
    printf("======init success======\n");

    //开始监听是否有客户端连接
    if (listen(socket_fd, 2) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    printf("======waiting for client's request======\n");


    for (;;) {
        //阻塞直到有客户端连接，不然多浪费CPU资源。
        printf("accept...\n");
        if ((connect_fd = accept(socket_fd, (struct sockaddr*)(&addr), &length  )) == -1) {
            printf("accept socket error: %s(errno: %d)\n", strerror(errno), errno);
            continue;
        }
        printf("accept ok...\n");
        int n = -1;  //== 0代表读完本次数据，继续accept
        for (;;) {
            char head_buffer[4];
            int body_length = 0;
            n = readn(connect_fd,head_buffer,4);
            if (n == 0) {break;}

            memcpy(&body_length,head_buffer,4);
            // body_length = htonl(body_length);
            printf("body_length == %d\n",body_length);

            char* body_buffer = (char*) malloc (sizeof(char) * body_length + 1);
            printf("==malloc size = %ld\n",(sizeof(char) * body_length + 1));
            n = readn(connect_fd,body_buffer,body_length);
            if (n == 0) {break;}
            
            body_buffer[body_length] = '\0';
            printf("==body_buffer == %s\n",body_buffer);

            free(body_buffer);
            body_buffer = nullptr;
            printf("==over\n");
        }
        close(connect_fd);
    }
    close(socket_fd);
    return 0;
}
