
// /proc/self/exe是一个符号链接，代表当前程序的绝对路径
// 用readlink读取/proc/self/exe可以获取当前程序的绝对路径
// 自动重启
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char buf[32] = {};
    char *exec_argv[] = { argv[0], buf, 0 };
    printf("argv[0] = %s\n", argv[0]);

    int count = argc > 1 ? atoi(argv[1]) : 0;

    printf("Running: %s %d\n", argv[0], count);
    snprintf(buf, sizeof(buf), "%d", count+1);
    printf("buf = %s\n", buf);

    sleep(5);

    char szDir[512] = {'0'};
    int cnt = readlink("/proc/self/exe",szDir,512);
    printf("path = %s\n", szDir); //当前程序的绝对路径

    execv("/proc/self/exe", exec_argv);//重启 参数为  argv[0] buf

    printf("path = %s\n", szDir);  // 并不能执行到此处

    return 0;
}