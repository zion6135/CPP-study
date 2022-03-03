
// 10.3 signal
// step1 :产生 段错误
#include <stdio.h>
#include <stdlib.h>
#if 0
int main(int argc, char **argv) {
    int *p = (int *)0;
    *p = 1;
}
#endif
// 2. ulimit -c 10240   让core 文件最大10M+ 可以产生core文件

// 信号会打断阻塞的系统调用:为了防止出现调用open()---》signal过来了打断open()--->需要在open 失败检查加上错误检查
// EINTR代表被打断的系统调用中断
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#if 0
int main(int argc, char **argv) {
    int sfd;
    do {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0) {
            // error check:
            if (errno != EINTR) {
                perror("open()");
                exit(1);
            }
        }
    } while (sfd < 0);

    close(sfd);
}
#endif
// 10.4 不可靠的信号
// 实际测试：每个信号的响应都有同样的信号行为
#include <signal.h>
#if 0
void int_handler(int a) {
    write(1, "7", 1);
}
int main() {
    int i;
    signal(
        SIGINT,
        int_handler);  //函数的调用是内核布置的。
                       //信号的不可靠指的是信号的行为不可靠：当收到SIGINT，然后内核调用int_handler函数，当内核第二次收到同样的信号，第二次的调用会恢复为默认调用

    for (int i = 0; i < 10; i++) {
        write(1, "*", 1);
        sleep(1);
    }
}
#endif
// 10.6 函数alarm
// 5s后杀死进程
int main() {
    alarm(5);  // 默认杀死进程
    // alarm(2);  //超过一个alarm()，程序会在设定的alarm() 最后最早的alarm被杀死

    while (1) {
    }
    exit(0);
}
