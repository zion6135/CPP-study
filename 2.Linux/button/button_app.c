/******************firstdrvtest.c*************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
 
int main()
{
	int fd;
	int i;
     unsigned char key_val[4];
      int cnt;
	 fd = open("/dev/button", 0);//可通过ls /dev/xyz命令查看
	if (fd < 0)
	{
		printf("can't open!\n");
	}
	printf("open!\n");
	while (1) {
	 	read(fd,key_val,sizeof(key_val));
        for (i = 0; i < sizeof(key_val)/sizeof(key_val[0]); i++) {
            // 如果被按下的次数不为0，打印出来
            if (!key_val[i])
                printf("K%d has been pressed %d times!\n", i+1, cnt);
        }

	}
	return 0;
}
