// gcc -g -o demo demo.c -ldl
// ./demo
 
// 段错误 (核心已转储)
 
// ulimit -c unlimited // 设置 core 文件大小为无限制
// ./demo 生成 core 文件
// gdb ./demo core 调试段错误

#include <stdio.h>
void test()
{
    int *p = NULL;
    *p = 1;
}

int main()
{
    test();
    return 0;
}