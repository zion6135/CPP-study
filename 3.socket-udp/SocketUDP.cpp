#include "SocketUDP.h"
    struct sockaddr src_addr;
    socklen_t addrlen = sizeof(struct sockaddr);

//用于监听client的消息
int SocketUDP::Server_Init()
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);
    int fd = -1;
    int ret = 0;
    struct sockaddr_in addrSer;
    socklen_t addrlen = sizeof(struct sockaddr);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        printf("socket failed [  %s  ]\n", strerror(errno));
        return -1;
    }

    addrSer.sin_family = AF_INET;
    addrSer.sin_addr.s_addr = inet_addr(SEVER_IP);
    addrSer.sin_port = htons(SEVER_PORT);
    ret = bind(fd, (struct sockaddr*)(&addrSer), addrlen); //监听程序所运行系统（Server_IP）的端口（SEVER_PORT）
    if (ret < 0) {
        printf("bind failed [%s]\n", strerror(errno));
        close(fd);
        return -1;
    }
    printf("init success\n");
    return fd;
}

int SocketUDP::Receive_Loop()
{
    char msg_buf[MAX_MSG_SIZE];
    while(1) {
        int recv_fd = Server_Init();
        if (recv_fd < 0) {
            static unsigned char cnt = 0;
            sleep(1);
            printf("get_recv_socket failed, retrying %c\n", cnt++);
            continue;
        }

        while (1) { //循环一直接受来自当前电脑的端口消息
            int recv_size;
            printf("Waiting to get message\n");
            recv_size = recvfrom(recv_fd, msg_buf, MAX_MSG_SIZE, 0, &src_addr, &addrlen);
            if (recv_size < 0) {
                printf("reply recv failed. [%s]\n", strerror(errno));
                sleep(1);
                continue;
            }
            printf("Receive Data:%s, size:%d\n", msg_buf, recv_size);
            
            // 处理收到的数据
            data_t* tmp;
            memcpy(tmp, msg_buf, recv_size); //拷贝收到的这种结构体到tmp
            Reveive_Process(tmp, recv_size);

        }
    }
}

int SocketUDP::Reveive_Process( data_t* data, const int len)
{
    //如果收到的消息过多，处理逻辑代码过多，可能会出现掉帧，于是需要 信号量+消息容器的机制来处理
    m_mutex.lock();
    data_m.push_back(data);
    m_mutex.unlock();
    sem_post(&m_sem);
    return 0;
}

int SocketUDP::main_process()
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);

    Receive_Loop();  //用于接收数据

    return 0;
}

int SocketUDP::sendUDP(const string msg)
{
    int send_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (send_fd < 0) {
        printf("fd: %d error\n ", send_fd);
    }

    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(CLIENT_PORT);
    addrSer.sin_addr.s_addr = inet_addr(CLIENT_IP);
    char out_buf[] = "helloworld";
    int ret = sendto(send_fd, out_buf, sizeof(out_buf), 0, (struct sockaddr*)&(addrSer),
                 sizeof(struct sockaddr));
    printf("Send ret:%d\n", ret);
    close(send_fd);
    return 0;
}

void SocketUDP::startProcMsg()
{
    printf("%d:%s", __LINE__, __FUNCTION__);

    thread t([this]() {
        while (true) {
            sem_wait(&m_sem);  //阻塞直到    sem_post(&m_sem);
            vector<data_t*> tmp_map;
            m_mutex.lock();
            data_m.swap(tmp_map);
            m_mutex.unlock();
            for (auto it = data_m.begin(); it != data_m.end(); it++) {
                //printf("message == %d\n", *it);
            }
            // LOG("End process msg");
        }
    });
    t.detach();
}

int SocketUDP::init()
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);
    thread udp(&SocketUDP::main_process, this);
    udp.detach();
    printf("udp init end\n");
   
    startProcMsg();//xxxxx

    while(1){
        ;
    }
    return 0;
}
