
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 1024
int main(int argc, char **argv) {
    FILE *fps, *fpd;
    char buff[BUFFERSIZE];

    if (argc < 3) {
        fprintf(stderr, "usage: %s <src_file> <dest_file>", argv[0]);
    }

    fps = fopen(argv[1], "r");  //需要fps存在
    if (fps == NULL) {
        perror("fps error");
        exit(1);
    }
    fpd = fopen(argv[2], "w");
    if (fpd == NULL) {
        fclose(fps);
        perror("fpd error");
        exit(1);
    }
    size_t n;
    while ((n = fread(buff, 1, BUFFERSIZE, fps)) > 0) {
        fwrite(buff, 1, n, fpd);
    }
    fclose(fpd);
    fclose(fps);

    exit(0);
}
/***********fgets()和fputs()*******************/
// 1.注意fgets()
// gets(char* s) 是不安全的，因为仅传入一个地址,所以引入fgets函数
// fgets()需要注意 读到size-1 ： 比如
char buf[5];
fgets(buf, 5, stream);

// 那么读取 abcdef 为 a b c d \0 然后下次从e开始读
// 那么读取 ab 那么为 a b \0

//那么读abcd 需要读几次呢？
// a b c d \0 然后下一次读 \n \0 ...故要两次

// 2.fgets和fputs实现文件拷贝
#if 0
#define BUFFERSIZE 1024
int main(int argc, char **argv) {
    FILE *fps, *fpd;
    char buff[BUFFERSIZE];

    if (argc < 3) {
        fprintf(stderr, "usage: %s <src_file> <dest_file>", argv[0]);
    }

    fps = fopen(argv[1], "r");  //需要fps存在
    if (fps == NULL) {
        perror("fps error");
        exit(1);
    }
    fpd = fopen(argv[2], "w");
    if (fpd == NULL) {
        fclose(fps);
        perror("fpd error");
        exit(1);
    }
    while (NULL != fgets(buff, BUFFERSIZE, fps)) {
        fputs(buff, fpd);
    }
    fclose(fpd);
    fclose(fps);

    exit(0);
}
#endif

// 3. fread()和 fwrite()
//从stream读nmemb个大小为size的数据到ptr,返回值为读取成功的对象个数
// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

// fread(buf, 1, 10, fp);
// fread(buf, 10, 1, fp); 若对象只有5个字节大小，则返回值为 0，所以为了保险使用fread(buf, 1, 10, fp);

//写nmemb个大小为size的的数据ptr到stream
// size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

//注意字节数应该使用返回值
