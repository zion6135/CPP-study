/********APUE chap3文件i/o**************/
// 3.2文件描述符file descriptor（本质：int数，数组下标）
// FILE： 文件位置pos, 文件唯一标识，fd, 使用计数
// 一个程序打开：会默认打开stdin, stdout, stderr三个流（fd = 0 1 2），所以默认第一个open/fopen操作返回的fd是3 ,不是0

// 3.3-3.8 文件i/o操作：open/close/read/write/lseek
// 文件io与标准io区别
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    putchar('a');      // 标准I/O
    write(1, "b", 1);  // 文件I/O

    putchar('a');
    write(1, "b", 1);

    putchar('a');
    write(1, "b", 1);

    exit(0);
}

// 输出结果：  bbbaaa

#endif
// 3.9 io效率问题
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void) {
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            perror("write error");

    if (n < 0)
        perror("read error");

    exit(0);
}
#endif

// 3.10 文件共享：删除文件第10行
#if 0
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage.. \n");
        exit(0);
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }
    char *linptr = NULL;
    size_t line_size = 0;
    int count = 0;
    while (1) {
        if (getline(&linptr, &line_size, fp) < 0) {
            break;
        } else {
            printf("content [%s]\n", linptr);
        }
        if (count++ ==)
    }
    fclose(fp);
    exit(0);
}
#endif
// 3.11 原子操作
// 3.12 程序中重定向 : dup,dup2
#if 0
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FNAME "/tmp/out"
int main() {
    int fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        perror("open()");
        exit(1);
    }
    // ==
    // close(1);
    // int dupfd = dup(fd);  // 复制fd，得到的dupfd是可用的最小fd 1

    // ==
    int dupfd = dup2(fd, 1);
    printf("hello %d %d", dupfd, fd);
    puts("hello");  // default 输出到stdout(fd == 1), 当close(1)后，输出到FNAME
    exit(0);
}
#endif
// 3.13 同步：sync, fsync,fdatasync

// 3.14 fcntl()
// 3.15 ioctl()
// 3.16 /dev/fd
