#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "stdio.h"

#include "child/Child.h"
#include "father/father.h"

int main() {
    fatherImpl aa("222");
    father::create("111");

    ChildImpl bb("111");
    Child::create("111");

    printf("main\n");
    while (1) {
        sleep(100);
    }
}