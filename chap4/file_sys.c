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
#if 0
// 通过lseek创建5G大小的文件tmp，同过stat tmp查看的内容，对应struct stat的变量
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char **argv) {
    int fd;

    if (argc < 2) {
        fprintf(stderr, "Usage..\n");
        exit(1);
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        exit(1);
    }
    // 必须用LL, 否则会当作int来使用，会达不到5G的大小
    lseek(fd, 5LL * 1024LL * 1024LL - 1LL, SEEK_SET);

    write(fd, "", 1);
    close(fd);
    exit(0);
}
#endif

//查看文件类型
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argv, char **argc) {
    struct stat tmp;

    stat(argc[1], &tmp);

    if (S_ISREG(tmp.st_mode)) {  // 返回ture,代表是常规文件
        fprintf(stdout, "is regular file\n");
    }

    exit(0);
}
#endif
// 2.文件访问权限 ls -l  4.7
// 对应stat的st_mode（bitmap）-----及ll 最前面的内容

// 3.umask  4.8
// 4.文件权限更改/管理 chmod,  4.9
// 5.粘住位 4.10
// 6.文件系统: FAT/UFS  4.12
// 7.硬链接，符号链接 4.17
// 8.utime  4.19
// 9.目录创建，销毁 4.21
// 10.更改当前工作路径 4.23
// 11.分析/读取目录内容 4.22

#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#if 0

// int glob(const char *pattern, int flags, int (*errfunc)(const char *epath, int eerrno), glob_t *pglob);
// void globfree(glob_t *pglob);

int errfunc_(const char *epath, int eerrno) {
    puts(epath);
    fprintf(stderr, "Error msg: %d\n", strerror(eerrno));
    return 0;
}
#define PATH "/etc/a*.conf"
int main() {
    glob_t globres;
    int err = glob(PATH, 0, errfunc_, &globres);
    if (err) {
        printf("Error code = %d\n", err);
        exit(1);
    }
    for (int i = 0; i < globres.gl_pathc; i++) {  // 匹配epath的列表
        puts(globres.gl_pathv[i]);
    }

    globfree(&globres);
    exit(0);
}
#endif
//实现命令du(查看当前位置的所有的文件)的功能
//达到 du ./ 和 ./file_sys ./结果一致
#define PATHSIZE 1024

static int path_noloop(const char *path) {
    // 在字符串中 ，找某个字符
    char *pos;
    pos = strrchr(path, '/');
    if (pos == NULL) {
        exit(1);
    }

    if (strcmp(pos + 1, ".") == 0 || strcmp(pos + 1, "..") == 0) {
        return 0;
    }
    return 1;
}

static int64_t mydu(const char *path) {
    struct stat statres;

    if (lstat(path, &statres) < 0)  // 链接查看
    {
        perror("lstat\n");
        exit(1);
    }
    if (!S_ISDIR(statres.st_mode)) {
        // path 为非目录文件
        return statres.st_blocks;  // 与du file_name结果一致
    } else {
        // path 是目录文件
        char nextpath[PATHSIZE];
        glob_t globresout;

        strncpy(nextpath, path, PATHSIZE);
        strncat(nextpath, "/*", PATHSIZE);

        if (0 < glob(nextpath, 0, NULL, &globresout)) {
            // globfree(&globresout);
        }
        {  // .指向自己 ..指向上一级目录
            // 隐藏文件---会造成递归卡死
            strncpy(nextpath, path, PATHSIZE);
            strncat(nextpath, "/.", PATHSIZE);

            if (0 < glob(nextpath, GLOB_APPEND, NULL, &globresout)) {
                // globfree(&globresout);
            }
        }
        // 找到目录下所有文件
        int sum = 0;
        for (int i = 0; i < globresout.gl_pathc; i++) {
            if (path_noloop(globresout.gl_pathv[i]))
                sum += mydu(globresout.gl_pathv[i]);
        }
        sum += statres.st_blocks;
        return sum;
    }
}

int main(int argc, char **argv) {
    // 分目录文件（递归）和文件
    if (argc < 2) {
        fprintf(stderr, "Usage..\n");
        exit(1);
    }

    printf("%lld", mydu(argv[1]) / 2);  // 一个block为512B,所以需要* 0.5K， 最后结果单位为KB
    exit(0);
}
// 二.系统的数据文件和信息

// 三.进程环境