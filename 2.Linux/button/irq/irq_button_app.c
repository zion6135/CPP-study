/******************firstdrvtest.c*************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
 
int main()
{
	int fd;
	int i;
    unsigned char key_val;
    int cnt = 0;
	fd = open("/dev/button", 0);//可通过ls /dev/xyz命令查看

	if (fd < 0)
	{
		printf("can't open!\n");
	}
	printf("open!\n");
	while (1) {
	 	read(fd,&key_val,1);
        printf("key val = 0x%x\n",key_val);

	}
	return 0;
}
