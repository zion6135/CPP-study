// 8.4 fork
//使用Demo
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    printf("Begin %d\n", getpid());
    
    pid_t tmp = fork();
    if(tmp < 0) { // fail
        perror("fail");
        exit(1);
    }
    if (tmp == 0) { //child
        printf("child is working %d\n", getpid());
    }
    else {  //parent
        // sleep(2);
        printf("parent is working %d\n", getpid());
    }
    printf("End %d\n", getpid());
    exit(0);
}
#endif
// 质数计算求取，通过fork来计算一次:说明fork有时候并不能提高程序速度
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define LEFT 30000000
#define RIGHT 30000200

int main() {
    int mark, j;
    for (int i = LEFT; i <= RIGHT; i++) {
        pid_t pid = fork();  // 父-->子-->孙-->。。。共200次
        if (pid < 0) {
            perror("error");
            exit(1);
        }
        if (pid == 0) {
            mark = 1;
            for (j = 2; j < i / 2; j++) {
                if (i % j == 0) {
                    mark = 0;
                    break;
                }
            }
            if (mark) {
                printf("%d is a primer\n", i);
            }
            exit(0);  //必须退出子进程--否则程序会fork 200次
        }
    }
    exit(0);
}
#endif

// 8.6 wait和waitpid
//进程的消亡以及释放资源
// 解释为什么这样输出：
// zion6135@zion6135:~/lbw/gitNote/chap8$ 30000083 is a primer
// 30000149 is a primer
// 30000109 is a primer
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define LEFT 30000000
#define RIGHT 30000200

int main() {
    int mark, j;
    for (int i = LEFT; i <= RIGHT; i++) {
        pid_t pid = fork();  // 父-->子-->孙-->。。。共200次
        if (pid < 0) {
            perror("error");
            exit(1);
        }
        if (pid == 0) {
            mark = 1;
            for (j = 2; j < i / 2; j++) {
                if (i % j == 0) {
                    mark = 0;
                    break;
                }
            }
            if (mark) {
                printf("%d is a primer\n", i);
            }
            exit(0);  //必须退出子进程--否则程序会fork 200次
        }
    }
    // 等子进程结束，主线程为其收尸
    for (int i = LEFT; i <= RIGHT; i++) {
        wait(NULL);  //阻塞等待每个子进程exit(0); 退出
    };

    exit(0);
}
#endif

// 8.10
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    puts("begin\n");
    int err = execl("/bin/date", "date", "+%s", NULL);
    perror("execl");

    puts("end\n");
    exit(0);
}
#endif
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    puts("begin\n");
    fflush(NULL);  //避免重定向不能保存begin的日志

    pid_t pid = fork();  // 父子进程
    if (pid < 0) {
        perror("fork()");
        exit(1);
    }
    if (pid == 0) {
        execl("/bin/date", "date", "+%s", NULL);  // 子进程从date文件的main开始执行
        perror("execl()");
        exit(1);
    }
    wait(NULL);  //为子进程收尸

    puts("end\n");
    exit(0);
}
#endif
// shell的简单外部命令实现：
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELINITS " \t\n"  // 三种分割符：空格，tab,换行

struct cmd_st {
    glob_t globres;
};

static void promt() {
    printf("mysh-0.1$");
}

static void prase(const char *buffer, struct cmd_st *cmd) {
    //解析一行的输入: 比如 ls -a -l /etc    /aaa/bbbb

    char *tok;

    int i = 0;  //第一次不用APPEND, 第二次在APEEND
    while (1) {
        tok = strsep(&buffer, DELINITS);
        if (tok == NULL) {
            break;
        }
        if (tok[0] == '\0')  //多个空格
            continue;
        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &cmd->globres);
        i = 1;
    }
}
int main() {
    puts("begin\n");

    while (1) {
        promt();  //打印提示符
        char *linebuffer = NULL;
        size_t line_size = 0;
        struct cmd_st cmd;

        //拿到每一行的输入
        if (getline(&linebuffer, &line_size, stdin) < 0) {
            break;
        }
        prase(linebuffer, &cmd);  //解析命令
        if (0) {
            //内部命令
        } else {
            //外部命令
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork()");
                exit(1);
            }
            if (pid == 0) {
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            } else {
                wait(NULL);
            }
        }
    }
    // pid_t pid = fork();  // 父子进程
    // if (pid < 0) {
    //     perror("fork()");
    //     exit(1);
    // }
    // if (pid == 0) {
    //     //  argv[0]相当于名字的作用
    //     //                  argv[0]  argv[1]
    //     execl("/bin/sleep", "sleep", "100", NULL);  // 子进程从date文件的main开始执行
    //     perror("execl()");
    //     exit(1);
    // }
    // wait(NULL);  //为子进程收尸

    puts("end\n");
    exit(0);
}