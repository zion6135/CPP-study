#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include "mytime.h"
#define MAX 10

struct Timer_t {
    int time;
    Func f;
    char *arg;
    int pos;
};
struct Timer_t *Timer_list[MAX];

static int firstIn = 0;

typedef void (*sighandler_t)(int);
sighandler_t sig_save;

void alrm_handler(int a) {
    for (int i = 0; i < MAX; i++) {
        if (Timer_list[i] != NULL) {
            Timer_list[i]->time--;
            if (Timer_list[i]->time == 0) {
                Timer_list[i]->f(Timer_list[i]->arg);
            }
        }
    }
    alarm(1);
}

int Init(Func func, char *arg, int time) {
    int pos = -1;
    for (int i = 0; i < MAX; i++) {
        if (Timer_list[i] == NULL) {
            pos = i;
        }
    }
    if (pos < 0) {
        return -ENOSPC;
    }

    Timer_list[pos] = malloc(sizeof(struct Timer_t));
    if (!Timer_list[pos]) {
        return -ENOMEM;
    }

    if (!func || !arg || (time == 0)) {
        return -EINVAL;
    }
    Timer_list[pos]->f = func;
    Timer_list[pos]->arg = arg;
    Timer_list[pos]->time = time;
    // Timer_list[pos]->pos = pos;

    if (!firstIn) {
        sig_save = signal(SIGALRM, alrm_handler);
        alarm(1);
        firstIn = 1;
    }
    return pos;
}

void Destory(int pos) {
    signal(SIGALRM, sig_save);
    alarm(0);

    free(Timer_list[pos]);
    Timer_list[pos] = NULL;
}