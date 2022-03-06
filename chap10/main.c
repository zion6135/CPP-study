
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
#if 0
int main() {
    alarm(5);  // 默认杀死进程
    // alarm(2);  //超过一个alarm()，程序会在设定的alarm() 最后最早的alarm被杀死

    while (1) {
    }
    exit(0);
}
#endif
#include <time.h>

#if 0
// 5s的定时程序：用time()函数
int main() {
    time_t end;
    int64_t count = 0;

    end = time(NULL) + 5;

    while (time(NULL) <= end) {
        count++;
    }
    printf("%lld\n", count);
}
// time ./a.out 可以看到time调用的时间是不准的
// lbw@HP-ZHAN-66-Pro-15-G3:~/lbw/gitNote/chap10$ time ./a.out
// 1761106842

// real    0m5.770s
// user    0m5.769s
// sys     0m0.000s
#endif

#if 0
// 5s的定时程序：用alarm() + signal()

// 同一个程序用gcc main.c -O1优化编译，如果不加volatile，会让程序进入死循环
// 而volatile的用处就体现出来了：让编译器对这个变量不在进行编译优化，这个时候在用gcc main.c -O1优化编译也不会出问题
volatile int loop = 1;

void alarm_handler(int s) {
    loop = 0;
}

int main() {
    alarm(5);
    signal(SIGALRM, alarm_handler);
    int count = 0;
    while (loop) {
        count++;
    }
    printf("%lld\n", count);

    exit(0);
}
//打印结果如下 ：可以看到时间精度很高
// lbw@HP-ZHAN-66-Pro-15-G3:~/lbw/gitNote/chap10$ time ./a.out
// 2474397847

// real    0m5.002s
// user    0m5.000s
// sys     0m0.000s
// lbw@HP-ZHAN-66-Pro-15-G3:~/lbw/gitNote/chap10$
#endif

#if 0
//漏桶： 流控：控制打印速度 alarm + signal
volatile int loop = 0;

void alarm_handler(int s) {
    alarm(1);
    loop = 1;
}

int main(int argc, char **argv) {
    signal(SIGALRM, alarm_handler);
    alarm(1);

    while (1) {
        while (!loop)
            pause();
        loop = 0;
        printf("hello,hello\n");
    }
}
#endif

#if 0
//令牌桶：有权限一秒打印一次hello,
//如果程序被阻塞了3s，分配给程序的资源：3s打印3次hello，那么解除阻塞之后，程序就会拥有打印3次hello的权限，于时可以打印3次。
// 相比于漏桶，不会白白浪费可使用资源。
volatile int token = 0;
#define MAX 100
void alarm_handler(int s) {
    alarm(1);
    token++;  //增加令牌
    if (token > MAX) {
        token = MAX;
    }
}

int main(int argc, char **argv) {
    signal(SIGALRM, alarm_handler);
    alarm(1);

    while (1) {
        while (token <= 0)
            pause();
        token--;  //消耗令牌
        // 模拟操作
        printf("hello\n");
    }
}
#endif

// 10.11信号集  10.12信号屏蔽字
void int_handler(void) {
    fprintf(stdout, "1\n");
}
int main() {
    sigset_t set, set_old2, set_old;

    signal(SIGINT, int_handler);
    // 清0
    sigemptyset(&set);
    // 将信号SIGINT加入信号集
    sigaddset(&set, SIGINT);
    // 保存之前状态
    sigprocmask(SIG_UNBLOCK, &set, &set_old);
    {
        for (int i = 0; i < 5; i++) {
            //对信号集set的信号阻塞SIG_BLOCK，之后不在响应信号集set的信号
            sigprocmask(SIG_BLOCK, &set, &set_old2);
            {  //因为包含SIGINT的信号集set被阻塞，所以不响应SIGINT--即ctrl+c不调用int_handler
                for (int i = 0; i < 5; i++) {
                    write(1, "*", 1);
                    sleep(1);
                }
                write(1, "\n", 1);
            }
            //对信号集set的信号解除阻塞SIG_UNBLOCK,恢复对set的响应
            sigprocmask(SIG_UNBLOCK, &set_old2, NULL);
        }
    }
    //恢复之前的状态
    sigprocmask(SIG_SETMASK, &set_old, NULL);
}

//在打印5行*****期间是不会响应SIGINT的，只会在打印结束时候调用一次int_handler