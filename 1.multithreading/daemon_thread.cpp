// 创建一个守护线程：每次收到sigalrm信号，执行touchfile()函数
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

// ps aux即可查看正在运行的线程  ---即可kill 
// 此代码执行后，可脱离父进程（终端）的限制
#define _file_name_prefix_ "%s/log/mydaemon.%s"  // 定义文件格式

void touchfile(int num) {
    char *HomeDir = getenv("HOME");
    //printf("%s\n",HomeDir);
    const time_t demo = time(NULL);
    //printf("%s\n",ctime(&demo));

    char str_Filename[250] = {0};
    sprintf(str_Filename,_file_name_prefix_,HomeDir,ctime(&demo));
    printf("%s\n",str_Filename);
    int fd = open(str_Filename,O_RDWR|O_CREAT, 0666); //设置文件的可执行权限
    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    close(fd);
}

int main() {
    //创建子进程，父进程退出，独立于终端
    pid_t pid = fork(); //父进程复制出一个和当前进程一样的子进程
    if(pid > 0) {
        printf("son\n");    
        //exit(1); // 如果exit结束执行的话，那么子进程会成为孤儿进程，并被init收养。
    } else if(pid == 0) {
        printf("dady\n"); 
    } 
    pid_t pid1 = setsid();
    if (-1 == pid1) {
        printf("this is process leader\n");  //当前线程是会话（session）的领头进程
        exit(1);  // 如果exit结束执行的话，那么子进程会成为孤儿进程，并被init收养。
    } else {
        printf("this is son %d\n",pid1); // 子进程重新获得了一个新的会话(session)id，那么此时父进程死了也不会影响到子进程。。。
                                         // 那么此时起子线程的任务就可以作为守护进程
    }
    //设置掩码
    //umask(0);
    //切换目录
    //chdir(getenv("home"));  // 切换到home目录
    //关闭文件描述符
    //执行核心逻辑
    struct itimerval my_it = {
        {6, 1},  // 每次的任务之间间隔60s+1us
        {1, 2}   // 设置定时器setitimer后1s+2us开始执行任务
        };
    setitimer(ITIMER_REAL, &my_it, NULL);  //ITIMER_REAL--系统真实时间，发出sigalrm信号
    
    struct  sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);  // 将参数信号集初始化并清空.--这里感觉就是把sa_flags清0
    act.sa_handler = touchfile; // 收到信号执行的函数

    sigaction(SIGALRM,&act,NULL);
    while(1) {
        
        sleep(1);

    }
}
