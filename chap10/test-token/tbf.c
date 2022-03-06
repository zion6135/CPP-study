// 令牌桶
#include <signal.h>
#include <string.h>

#include "tbf.h"

struct tbf {
    int cps;    // 流量 cost per second
    int burst;  // 上限个数
    int token;  // 令牌个数
    int pos;    // 处于job数组哪个位置
};

#define MAX 10
struct tbf *job[MAX];  //多个对象使用同tb的接口
void (*alarm_handler_save)(int);
static int useFlag = 0;

static int get_free_pos(void) {
    for (int i = 0; i < MAX; i++) {
        if (job[i] == NULL)
            return i;
    }
    return -1;
}

static int min(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void alrm_handler(int a) {
    alarm(1);  //为下一次定时

    // 每秒增加每个对象的流量
    for (int i = 0; i < MAX; i++) {
        if (job[i] != NULL) {
            // 更新每秒的流量
            job[i]->token += job[i]->cps;
            // 达到上限，更新token为最大个数值
            if (job[i]->token > job[i]->burst) {
                job[i]->token = job[i]->burst;
            }
            printf("i=[%d] token = [%d]\n", i, job[i]->token);
        }
    }
}

static void module_unload() {
    signal(SIGALRM, alarm_handler_save);  //恢复到之前的配置
    alarm(0);                             // 关闭alarm
    for (int i = 0; i < MAX; i++) {
        free(job[i]);
    }
}

static void module_load() {
    alarm_handler_save = signal(SIGALRM, alrm_handler);  //注册信号
    alarm(1);                                            // 闹钟

    atexit(module_unload);  //程序异常退出：
}
// start
tbf_t *tbf_init(int cps, int burst) {
    struct tbf *tmp;

    if (!useFlag) {
        module_load();
        useFlag = 1;
    }
    int pos = get_free_pos();
    if (pos < 0) {
        return NULL;
    }

    tmp = malloc(sizeof(tmp));
    if (tmp == NULL) {
        return NULL;
    }

    tmp->token = 0;
    tmp->cps = cps;
    tmp->burst = burst;
    tmp->pos = pos;

    job[pos] = tmp;
    return tmp;
}

//取token
//
int tbf_fetchtoken(tbf_t *xx, int size) {
    if (size <= 0) {
        return -1;
    }

    struct tbf *me = xx;
    while (me->token <= 0) {
        pause();
    }

    int n = min(me->token, size);
    me->token -= n;

    return n;
}

int tbf_returnToken(tbf_t *xx, int size) {
    struct tbf *me = xx;
    if (size <= 0) {
        return -1;
    }

    me->token += size;
    if (me->token > me->burst)
        me->token = me->burst;
    return size;
}
int get_ToeknParms(tbf_t *tmp) {
    struct tbf *me = tmp;
    fprintf(stdout, "===================\n");
    fprintf(stdout, "token = %d\n", me->token);
    fprintf(stdout, "burst = %d\n", me->burst);
    fprintf(stdout, "cps = %d\n", me->cps);
    fprintf(stdout, "pos = %d\n", me->pos);
    fprintf(stdout, "===================\n");
}

void tbf_destory(tbf_t *xx) {
    struct tbf *tmp = xx;
    job[tmp->pos] = NULL;
    free(xx);
}