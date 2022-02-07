#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    printf("Before while(1)");
    fflush(stdout);
    while (1)
        ;
    printf("after while()");
    fflush(NULL);
    exit(0);
}

/************************5.11 snprintf scanf和printf******************/
// 1.重映像
// echo 1  和 echo 1 >> /tmp/out
// fprintf(stderr, ***);  或者fprintf(file_name, ***); 出错重映像到文件
// sprintf ---避免写溢出用 snprintf
#if 0
int main() {
    char buf[1024];
    int year = 2014, month = 5, day = 13;

    sprintf(buf, "%d-%d-%d", year, month, day);
    puts(buf);

    exit(0);
}
#endif
// snprintf

// atoi()  // 字符串到int

// 2. fscanf :从流那数据
// 和sscanf：从字符串拿数据

/************************5.10 fseek和ftell和rewind()******************/
// 3.操作文件位置指针
// fseek()传参为long--》说明大小范围为-2G～2G,而long ftell();说明大小范围为00-2G，
// 为了规避此问题：有了fseeko和ftello函数

// fseek(fp, 0, SEEK_SET);  //文件首
// fseek(fp, 0, SEEK_CUR);  //文件当前位置

//测试文件长度
#if 0
int main(int argc, char **argv) {
    FILE *fp;
    static int count = 0;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    printf("%d\n", ftell(fp));
    fclose(fp);
    exit(0);
}
#endif

// long参数 ： 0L

/******************fflush***********************/
// 无法打印： 因为stdout无法刷新，需要在printf末尾加上'\n'
#if 0
int main(int argc, char **argv) {
    printf("Before while(1)");
    while (1)
        ;
    printf("after while()");
    exit(0);
}
#endif

//或者用fflush来刷新
#if 0
int main(int argc, char **argv) {
    printf("Before while(1)");
    fflush(stdout);
    while (1)
        ;
    printf("after while()");
    fflush(NULL);
    exit(0);
}
#endif

// setvbuf()修改缓冲模式
//缓冲区：大多数情况是好处：合并系统调用
//行缓冲：换行的时候刷新 ， 满了刷新， 强制刷新(标准输出？？)
//全缓冲：满了刷新， 强制刷新(默认，只要不是终端设备)
//无缓冲：如stderr,需要立即输出的内容
