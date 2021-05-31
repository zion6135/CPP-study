#include <stdio.h>    // for printf()  
#include <signal.h> 
#include <sys/time.h>
 #include <time.h>
#include <unistd.h>

#include <errno.h>

void sigFunc(int )
{
   static int iCnt = 0;
   printf("The %d Times: Hello world\n", iCnt++);
}
 
int main(void)
{
   struct itimerval tv;
   signal(SIGALRM, sigFunc);
   //how long to run the first time
   tv.it_value.tv_sec = 3;  // 秒
   tv.it_value.tv_usec = 0; // 微妙
   //after the first time, how long to run next time
   tv.it_interval.tv_sec = 1;
   tv.it_interval.tv_usec = 0;
 
   if (setitimer(ITIMER_REAL, &tv, NULL) != 0)
	printf("setitimer err %d\n", errno);
 
   while(1)
   {
	sleep(1);
   }
}