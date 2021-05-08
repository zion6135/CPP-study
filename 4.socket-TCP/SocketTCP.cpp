

#include "SocketTCP.h"

#define MAX_MSG_SIZE 1024
#define DEFAULT_PORT 1010
#define DEFAULT_IP "192.168.1.12"

struct body {
    uint32_t length;
    char buffer[1024];
}__attribute((packed)); //不考虑字节对齐body_t;
struct body recv_buffer;


int SocketTCP::init()
{
    printf("%d:%s", __LINE__, __FUNCTION__);
    thread udp(&SocketTCP::socketThread, this);
    udp.detach();
    printf("tcp init end");
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
}

void SocketTCP::startProcMsg_send() //发送消息子线程
{
    printf("%d:%s", __LINE__, __FUNCTION__);

    thread t([this]() {
        while (true) {
            sem_wait(&sem_send);
            printf("Start process msg");
            deque<HavpMsg_send*> dequeMsgs;
            mutex_send.lock();
            dequeMsgs.swap(dequeMsgs_send);
            mutex_send.unlock();
            for (auto it = dequeMsgs.begin(); it != dequeMsgs.end(); it++) {
                printf("sockt send:type:%d, module:%d, data:%s, length:%d", (*it)->type, (*it)->module, (*it)->data.c_str(), (*it)->data.length());
                if (1 == socketSend_prepare((*it)->type, (*it)->module, ref((*it)->data))) {
                    recv_buffer.length = strlen(data_send);
                    memcpy(recv_buffer.buffer , data_send, strlen(data_send));
                    send(connect_fd, &recv_buffer, strlen(data_send) + 4, 0);
                    memset(&recv_buffer,0,strlen(data_send) + 4); 
                }
                delete *it;
            }
            printf("End process msg");
        }
    });
    t.detach();
}

void SocketTCP::startProcMsg_recv() // 接收消息子线程
{
    printf("%d:%s", __LINE__, __FUNCTION__);

    thread t([this]() {
        while (true) {
            sem_wait(&sem_recv);
            printf("Start process msg");

            deque<Msg_myself*> dequeMsgs;
            mutex_recv.lock();
            dequeMsgs.swap(dequeMsgs_recv);
            mutex_recv.unlock();

            for (auto it = dequeMsgs.begin(); it != dequeMsgs.end(); it++) {
                /********处理收到的消息 ************/
                free(*it);
            }
            printf("End process msg");
        }
    });
    t.detach();
}


int SocketTCP::socketThread()
{
    printf("%d:%s", __LINE__, __FUNCTION__);
    struct sockaddr_in addr ;
    char buff[MAX_MSG_SIZE];
    int ret;
    socklen_t length = sizeof(addr);
    
    // startProcMsg_recv();  消息队列--参考socket-udp
    // startProcMsg_send();
    
    initSocket();

    //开始监听是否有客户端连接
    if (listen(socket_fd, 1) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    printf("======waiting for client's request======\n");


    for (;;) {
        //阻塞直到有客户端连接，不然多浪费CPU资源。
        printf("accept...");
        if ((connect_fd = accept(socket_fd, (struct sockaddr*)(&addr), &length  )) == -1) {
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
            continue;
        }
        for (;;) {
            static bool flag_processed = false;
            memset(&recv_buffer,0,sizeof(recv_buffer));
            int recv_size = recv(connect_fd,&recv_buffer,1028,0);
            // 数据接收错误
            if (recv_size <= 0) {
                printf("recv failed. [%s]", strerror(errno));
                sleep(0.5);
                close(connect_fd);
                break;
            }
            // int recv_size = read(connect_fd,&recv_buffer,1028);
            printf("recv_size %d",recv_size);
            length = htonl(recv_buffer.length);
            printf("recv_buffer.length %d",length);
            printf("recv_buffer.buffer %s",recv_buffer.buffer);

            int unrecv_len = length + 4 - recv_size;

            // 接收数据粘包
            size_t len = 0;
            int offst = length;
            struct body* buffer_tmp = (body *)malloc(sizeof( body));
            while (unrecv_len < 0) {
                printf("unrecv_len %d",unrecv_len);

                memset(buffer_tmp,0,sizeof(body));
                printf("offst == %d", offst);
                memcpy(&buffer_tmp->length,&recv_buffer.buffer[offst],4);
                buffer_tmp->length  = htonl(buffer_tmp->length);

                if (buffer_tmp->length > 1024) {
                    printf("error length");
                    break;
                }
                printf("len == %d", buffer_tmp->length);
                memcpy(buffer_tmp->buffer,&recv_buffer.buffer[offst+4],buffer_tmp->length);

                unrecv_len = unrecv_len + buffer_tmp->length + 4;
                offst = offst + buffer_tmp->length + 4;

                /************处理数据buffer_tmp*************/
                flag_processed = true;
             }
             free(buffer_tmp);
             buffer_tmp = nullptr;

            // 接收数据分包
            printf("unrecv_len %d",unrecv_len);
            int offset = recv_size - 4;
            while (unrecv_len > 0) {
                printf("recv_buffer_retain %s",recv_buffer.buffer);
                recv_size += recv(connect_fd,&recv_buffer.buffer[offset],unrecv_len,0);
                printf("recv_buffer_retain %d",recv_size);
                printf("recv_buffer_retain %s",recv_buffer.buffer);
                unrecv_len = length + 4 - recv_size;
                printf("recv_buffer_retain %d",unrecv_len);
            }
            if (flag_processed == true) {
                flag_processed = false;
                continue;
            }
            /************处理数据recv_buffer*************/
            printf("over");
        }
    }
    close(connect_fd);
    close(socket_fd);
    return 0;
}
