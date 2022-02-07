
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    static int count = 0;
    while (1) {
        fp = fopen("tmp", "r");
        if (fp == NULL) {
            perror("fopen()");
            break;
        } else {
            count++;
        }
    }
    printf("opened  [%d]", count++);

    fclose(fp);
    exit(0);
}

/**********************5.5 fopen和fclose************************/
// 1.fopen权限
// r read only
// r+ read and write
// w 有则清空，无则创建
// w+
// a 写到文件末尾处
// a+ read在文件开头 write放在文件末尾
// r和r+需要保证文件存在

// 4.为什么需要fclose
// fopen返回值内存在哪里？ heap
// 所以必须要fclose---避免memory leak

// 5.fopen的上限
// 程序默认打开 stdin stdout stderr   所以程序最多打开的流 = 默认 - 3
// ulimit -a中的open files代表程序默认打开的流上限

// 2.编译
// gcc -E     预处理  生成main
// make main  生成a.out

// 3.erro输出

// fprintf + 查找宏
//报错：打开/usr/include/asm-generic/errno-base.h 可以看到是
//#define ENOENT           2      /* No such file or directory */
// fprintf(stderr, "fopen eroor %d\n", errno);

// perror
// perror("fopen()");  // 打印  fopen(): No such file or directory

// strerror
// fprintf(stderr, "fopen error %s\n", strerror(errno));

// 6.文件权限 0666 & ~umask
// terminal输入umask 为 0002
