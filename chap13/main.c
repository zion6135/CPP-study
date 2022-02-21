// 9.4 进程组
//前台进程组 （最多1个或没有）：接收终端的输入，输出 + 后台进程组：0 1 2重定向，不接受终端输入输出
//会话 session，标识sid，
//终端: setsid()

// 守护进程
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int daemonize() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork()");
        return -1;
    }
    if (pid > 0) {  // parent
        exit(0);
    }
    int fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        perror("open()");
        return -1;
    }

    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2) {
        close(fd);
    }
    setsid();  // child

    // 让守护进程在一定存在的目录
    chdir("/");
    // umask(0);
    return 0;
}
#define FNAME "/tmp/out"
int main() {
    if (daemonize()) {
        exit(1);
    }
    FILE *fp = fopen(FNAME, "w");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    for (int i = 0;; i++) {
        fflush(fp);
        fprintf(fp, "%d\n", i);
        sleep(1);
    }

    exit(0);
}
// 父进程执行结束，子进程后台运行
// lbw@lbw:~/lbw/gitNote/chap9$ g++ main.c -o mydaemon
// lbw@lbw:~/lbw/gitNote/chap9$ ./mydaemon
// lbw@lbw:~/lbw/gitNote/chap9$

// 查看子进程（守护进程）
// lbw@lbw:~/lbw/gitNote/chap9$
// lbw@lbw:~/lbw/gitNote/chap9$ps axj
// 96186 4160831 4160831 4160831 ? -1 Ss 1000 0 : 00. / mydaemon

//查看输出的日志
// lbw@lbw:~/lbw/gitNote/chap9$:tail -f /tmp/out
// 158
// 159
// 160
// 161
// 162
// 163
// 164
// 165

//杀死守护进程
// lbw@lbw:~/lbw/gitNote/chap9$kill -9 4160831