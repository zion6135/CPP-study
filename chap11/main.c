
// 11.1 线程的概念:一个线程就是一个函数
// 一个进程就是一个容器：装的是LWIP（子线程）
// POSIX线程：一套标准，而不是实现 所以有pthread

//多线程和信号小范围内可以混用
// 解决异步事件：多线程和信号

// 11.3 线程标识
// pthread_e1ual()：每个线程也有ID，可以使用pthread_e1ual();来比对两个线程是否一致
// pthread_self()；  获取自身的线程号 ，类似getpid()

// 11.4 线程创建
// pthread_create()
// 线程的调度取决于调度器的策略
#if 0
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *fun(void *p) {
    puts("thread is working!");  //无打印，因为线程还没被调度, 主进程就结束了
    return NULL;
}
int main() {
    puts("Begin!");
    pthread_t tid;
    int err = pthread_create(&tid, NULL, fun, NULL);
    if (err) {
        fprintf(stderr, "pthread_create%s", strerror(err));
        exit(1);
    }
    puts("End");
    exit(0);
}
#endif
// 11.5 线程终止
// 线程终止的三种方式-----
// 1.线程从启动例程返回，返回值就是线程的退出码
// 2.线程可以被同一进程中的其他线程取消
// 3.线程调用pthread_exit()函数

// pthread_join()-----相当于wait()
#if 0
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void *tmp;

static void *fun(void *p) {
    puts("thread is working!");  //无打印，因为线程还没被调度, 主进程就结束了
    pthread_exit(NULL);          //实现对线程清理，并返回void*
    // return NULL;
}
int main() {
    puts("Begin!");
    int a = 10;
    int *b = &a;
    pthread_t tid;
    int err = pthread_create(&tid, NULL, fun, NULL);
    if (err) {
        fprintf(stderr, "pthread_create%s", strerror(err));
        exit(1);
    }
    // NULL：表示不关心tid对应线程的返回值
    // 阻塞等待tid对应的线程执行结束
    pthread_join(tid, NULL);
    puts("End");
    exit(0);
}
#endif

/* 线程的取消选项
1.pthread_cancel()
2.取消有两种状态：{
    允许:(1)异步cancel. (2)推迟cancel（默认）-->推迟到cancel点在取消
        cancel点：  (1)POSIX定义的cancel点，都是可能引发阻塞的系统调用
                   (2)相关函数:pthread_setcancelstate();  //是否允许cancel
                   (3)设置取消方式：pthread_setcanceltype();  //设置取消方式
                   (4)pthread_testcancel();  //什么都不做，就是一个取消点
    不允许:
}
3.线程分离： pthread_detach(),不关心线程的情况

*/

/*
栈的清理：pthread_cleanup_push()
pthread_cleanup_pop(int a);
1.必须成对出现
2.pthread_cleanup_push()相当于挂上钩子函数，thread_cleanup_pop(1)；代表出栈并调用，thread_cleanup_pop(0)；代表出栈并不调用
*/
#if 0
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void cleanup_func(void *p) {
    puts(p);
}

static void *func(void *p) {
    puts("thread is working!");  //无打印，因为线程还没被调度, 主进程就结束了
    pthread_cleanup_push(cleanup_func, "cleanup:1");
    pthread_cleanup_push(cleanup_func, "cleanup:2");
    pthread_cleanup_push(cleanup_func, "cleanup:3");

    pthread_cleanup_pop(1);  // 调用"cleanup:3"
    pthread_cleanup_pop(0);  // 不调用"cleanup:2"
    pthread_cleanup_pop(0);  // 不调用"cleanup:1"
    puts("push over");
    pthread_exit(NULL);  //实现对线程清理，并返回void*

    // return NULL;
}

int main() {
    puts("Begin!");

    pthread_t tid;
    int err = pthread_create(&tid, NULL, func, NULL);
    if (err) {
        fprintf(stderr, "pthread_create%s", strerror(err));
        exit(1);
    }

    pthread_join(tid, NULL);
    puts("End!");
    exit(0);
}
#endif

/*线程的小例子*/
