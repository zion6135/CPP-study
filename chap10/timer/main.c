#include <stdio.h>
#include <stdlib.h>
#include "mytime.h"

void Func1(char *tmp) {
    fprintf(stdout, "%s", tmp);
}

int main() {
    puts("begin!!");
    int fd = Init(Func1, "222", 2);
    if (fd < 0) {
        puts("error!!");
        exit(0);
    }
    int fd2 = Init(Func1, "555", 5);

    puts("end !!");

    static int a = 0;
    while (a <= 5) {
        write(1, ".", 1);
        sleep(1);
        a++;
    }
    Destory(fd);
    Destory(fd2);
    exit(0);
}