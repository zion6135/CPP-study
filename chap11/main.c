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

// 11.6 线程同步

/*线程竞争的小例子
 千万不要在多线程用sleep()
*/
#if 0
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT - LEFT + 1)

static void *thr_prime(void *p) {
    int i, j, mark;
    i = *(int *)p;
    mark = 1;
    for (j = 2; j < i / 2; j++) {
        if (i % j == 0) {
            mark = 0;
            break;
        }
    }

    if (mark) {
        printf("%d is primer\n", i);
    }

    pthread_exit(p);
}

int main() {
    // 创建THRNUM个线程
    int i, mark, j;
    pthread_t tid[THRNUM];
    int *mt;
    void *ptr;
    for (i = LEFT; i <= RIGHT; i++) {
        mt = (int *)malloc(sizeof(int));
        *mt = i;
        int err = pthread_create(tid + i - LEFT, NULL, thr_prime, mt);
        if (err) {
            fprintf(stderr, "pthread create error %s", strerror(err));
        }
    }
    for (i = LEFT; i <= RIGHT; i++) {
        pthread_join(tid[i - LEFT], &ptr);
        free(ptr);
    }
    exit(0);
}

#endif

#if 0
// 竞争故障
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define THRNUM 20
#define FNAME "/tmp/out"
#define LINESIZE 1024

static void *thr_add(void *p) {
    FILE *fp;

    char linebuf[LINESIZE];
    fp = fopen(FNAME, "r+");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }
    fgets(linebuf, LINESIZE, fp);
    fseek(fp, 0, SEEK_SET);  //更新到文件首

    fprintf(fp, "%d\n", atoi(linebuf) + 1);

    fclose(fp);

    pthread_exit(NULL);
}

int main() {
    pthread_t tid[THRNUM];
    int i;
    for (i = 0; i < THRNUM; i++) {
        int err = pthread_create(tid + i, NULL, thr_add, NULL);  // 20个线程同时打开线程
        if (err) {
            fprintf(stderr, "pthread_create(): %s\n", strerror(err));
            exit(1);
        }
    }
    exit(0);
}
#endif
/* 11.6.1 互斥量
1.本质上是一把锁，比如一个房间20个人进去会有问题，我希望一个人一个人进去，一个人枪到了锁（互斥量），进入房间，用完了之后出来，把锁释放。
2.当A线程加锁了，B线程试图再次加锁，程序就会阻塞，直到A线程解锁。
3.互斥量通过休眠使进程阻塞
动态初始化：
  创建：pthread_mutex_init()
  销毁:pthread_destory()
  上锁:pthread_mutex_lock()  /  pthread_mutex_trylock() // 避免阻塞线程，根据返回值判定是否上锁成功
  解锁:pthread_mutex_unlock()

静态初始化：
  pthrad_mutex tmp = PTHREAD_MUTEX_INITIALIZER

*/


/*11.6.2 避免死锁
1：对同一个线程用互斥量加锁两次，那么这个线程就会死锁
2：当使用两个互斥量a,b，(1)线程A使用互斥量a--->(2)线程B使用互斥量b---->(3)线程A使用互斥量b(线程A死锁)--->(4)线程B使用互斥量a(线程B死锁) 
     这种情况，只要保证:(3)之前互斥量b使用前是unlock()的状态    或者使用try_lock()避免阻塞
*/

/*11.6.3 函数pthread_mutex_timelock()
在上锁的时候，如果阻塞，有阻塞的等待时间。避免产生线程一直被阻塞在某个地方
*/

/*11.6.4 读写锁
1.读写锁有三种状态：读模式加锁， 写模式加锁，不加锁。
    线程A执行写加锁--->B线程执行写加锁会阻塞，直到线程A解锁
    线程A执行读加锁--->B线程执行读加锁不会阻塞---但是线程A或线程B执行写加锁会被阻塞，直到读加锁解锁。

2.读写锁适用于：需要读操作次数远大于写操作的情况
3.读写锁也叫shared-exclusive lock, 当读模式锁住了，可以说成是共享模式锁住。当写模式锁住的时候，可以说以互斥模式 锁住
4.读写锁使用之前必须要初始化（调用pthread_rwlock_init()函数 )
5. 锁定读的锁：pthread_rwlock_rdlock()
    锁定写的锁：pthread_rwlock_wrlock()
    读/写的解锁：pthread_rwlock_unlock()
6.同理有pthread_rwlock_try_lock()避免阻塞
*/

/* 11.6.5 带超时的读写锁
pthread_rwlock_timedwrlock();   
*/

/* 11.6.6 条件变量
0.引入的原因：条件变量的引入，使多个线程以一种无竞争的方式等待条件的改变。

1.条件变量必须初始化与销毁： pthread_cond_init() / pthread_cond_destroy()
B线程等待，A线程发出信号，B线程解除阻塞
2.B线程等待条件变量为真： pthread_cond_wait() / pthread_cond_timedwait() 超时
3.A线程广播条件变量状态：
pthread_cond_signal() 激活等待的线程，等待的线程按照入队顺序激活一个。
pthread_cond_broadcast()：激活所有的等待线程
4.条件变量的使用总是和一个互斥锁结合在一起？？？？
虚假唤醒

*/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
void* thread_A(void* a) {
    pthread_detach(pthread_self());
    printf("thread_A E\n");

    pthread_mutex_lock(&mtx);
    while(1) {
        printf("22222\n");
        pthread_cond_wait(&cond,&mtx);
        printf("33333\n");
        break;
    }
    pthread_mutex_unlock(&mtx);
    return NULL;
}

void* thread_B(void* a) {
    pthread_detach(pthread_self());
        printf("thread_B E\n");


    static int b = 1;
    while (b != 0){

            pthread_cond_signal(&cond); //注意：可能这个地方跑过了，但thread_B没到wait的地方，需要注意先后的问题
            printf("11111[%d]\n",b);
            b++;
            sleep(1);
            if (b == 20) {
                break;
            }

        }
    return NULL;
}

int main()
{
    pthread_t thread1,thread2;
    pthread_cond_t frt;

    pthread_create(&thread1, NULL, thread_A, NULL);
    printf("thread_main E\n");

    pthread_create(&thread2, NULL, thread_B, NULL);

    while(1) {
            printf("[%s]\n","main");

        sleep(5);
    }
}
/* 11.6.7 自旋锁
0.通过死循环使程序一直查询锁是否可用
1.初始化：pthread_spin_init();
2.pthread_spin_destroy();
*/