#ifndef MYTIME_H__
#define MYTIME_H__

typedef void (*Func)(char *tmp);

int Init(Func func, char *arg, int time);
void Destory(int pos);

#endif