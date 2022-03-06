#ifndef _TBF_H__
#define _TBF_H__

#include <stdio.h>
#include <stdlib.h>

typedef void tbf_t;

#define TBF_MAX 1024

tbf_t *tbf_init(int cps, int burst);
int tbf_fetchtoken(tbf_t *xx, int size);
int tbf_returnToken(tbf_t *xx, int size);
void tbf_destory(tbf_t *xx);

int get_ToeknParms(tbf_t *tmp);
#endif