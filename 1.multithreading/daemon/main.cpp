
#include <iostream>
#include <signal.h> 
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <errno.h>
using namespace std;


int main() {
    while (1) {
        printf("this is me\n");
        sleep(1);
    }
}