
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *fps;
    int ch;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <src_file>", argv[0]);
    }
    fps = fopen(argv[1], "r");  //需要fps存在 read only
    if (fps == NULL) {
        perror("popen()");
        exit(1);
    }

    int count = 0;
    while (fgetc(fps) != EOF) {
        count++;
    }
    printf("count = %d\n", count);
    fclose(fps);

    exit(0);
}

/**********************fgetc和fputc************************/
// 1.实现 cp srcfile destfile动作
// fgetc(); 成功返回unsigned char 转换成的 int ，失败返回EOF
// fputc();  writes the character c, cast to an unsigned char, to stream.
// ./mycpy /etc/services /tmp/out 然后diff /etc/services /tmp/out发现文件完全一样2
#if 0
int main(int argc, char **argv) {
    FILE *fps, *fpd;
    int ch;

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
    while (1) {
        ch = fgetc(fps);
        if (ch == EOF)
            break;
        fputc(ch, fpd);
    }
    fclose(fpd);
    fclose(fps);

    exit(0);
}
#endif

// 2.测试文件字符个数， 通过fgetc()实现，达到和ll命令一样的效果
#if 0
int main(int argc, char **argv) {
    FILE *fps;
    int ch;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <src_file>", argv[0]);
    }
    fps = fopen(argv[1], "r");  //需要fps存在 read only
    if (fps == NULL) {
        perror("popen()");
        exit(1);
    }

    int count = 0;
    while (fgetc(fps) != EOF) {
        count++;
    }
    printf("count = %d\n", count);
    fclose(fps);

    exit(0);
}
#endif
