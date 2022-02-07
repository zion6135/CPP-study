// 4 6 7
//<<深入理解计算机系统>>

// 文件系统：
// 类ls的实现

// 4
// 一.目录和文件
// 1.获取文件属性 4.2
// stat/fstat/lstat
// stat 命令： stat [file_name] //是通过stat()函数封装出来的
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
static off_t flen(const char *fname) {
    struct stat statres;

    if (stat(fname, &statres) < 0) {
        perror("stat()");
        exit(1);
    }
    return statres.st_size;  // st_size为off_t
}
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    off_t len = flen(argv[1]);

    fprintf(stdout, "len = [%ld]", len);  // 与ll 或者 stat argv[1]结果一样
    exit(0);
}
#endif
// 2.文件访问权限 ls -l  4.7

// 3.umask  4.8
// 4.文件权限更改/管理 chmod,  4.9
// 5.粘住位 4.10
// 6.文件系统: FAT/UFS  4.12
// 7.硬链接，符号链接 4.17
// 8.utime  4.19
// 9.目录创建，销毁 4.21
// 10.更改当前工作路径 4.23
// 11.分析/读取目录内容 4.22

// 二.系统的数据文件和信息

// 三.进程环境