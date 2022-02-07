/****************************getline************/
//通过getline获取每一行的内容并打印
// getline = malloc + realloc
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
    while (1) {
        if (getline(&linptr, &line_size, fp) < 0) {
            break;
        } else {
            printf("content [%s]\n", linptr);
            printf("size [%ld]\n", line_size);
        }
    }
    fclose(fp);
    exit(0);
}