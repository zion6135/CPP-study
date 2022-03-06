#include "tbf.h"
// 模拟用户操作

#define CPS 10
#define BUFSIZE 10
#define BURST 100

static int cost = 0;
int main(int argc, char **argv) {
    tbf_t *tb = tbf_init(CPS, BURST);
    if (!tb) {
        fprintf(stderr, "result = tbf_init\n");
        exit(0);
    }

    while (1) {
        // 取BUFSIZE个token, 能要到size个
        int size = tbf_fetchtoken(tb, 5);
        fprintf(stdout, "get = %d\n", size);
        // 模拟消耗token
        {
            cost = 10;  // 消耗cost个token
            printf("hello\n");
        }

        //如果没用完，归还token
        if (size - cost > 0) {
            fprintf(stdout, "return = %d\n", size - cost);

            tbf_returnToken(tb, size - cost);
        }

        get_ToeknParms(tb);
    }

    tbf_destory(tb);
}