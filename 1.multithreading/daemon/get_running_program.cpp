// 在/proc文件下去解析某个程序的运行状态，名字----
// 读/proc/597097/status文件的Name与 ./a.out test的test是否一致
//     execv("/proc/self/exe", exec_argv);  重启程序
// 编译：g++ get_running_program.cpp
// 执行：./a,out test
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
// get pid by program name

int main (int argc, char* argv[])
{
    DIR *pdir = NULL;
    struct dirent *pde = NULL;
    FILE *pf = NULL;
    char buff[128];
    char buff2[128];
    char *pstr = NULL;
    int pid, ppid;
    int n;
    int i;

    pdir = opendir("/proc");
    if (!pdir)
    {
        perror("open /proc fail.\n");
        return -1;
    }

    while ((pde = readdir(pdir))) // 遍历读出目录中的所有线程目录
    {
        if ((pde->d_name[0] < '0')
        || (pde->d_name[0] > '9'))
        {
            continue;
        }
        sprintf(buff, "/proc/%s/status", pde->d_name);
        printf("path = %s\n",buff);
        pf = fopen(buff, "r");
        if (pf)
        {
            n = fread(buff, 1, 127, pf);
            printf("buff = %s\n",buff);
            fclose(pf);
            buff[n] = 0;

            for (i = 0; i < n; i++)
            {
                if ('\n' == buff[i])
                {
                    buff[i] = 0;
                    break;
                }
            }
        printf("== (%s) ==\n", buff);
            n = i; 
            for (i = 0; i < n; i++)
            {
                if ((' ' == buff[i]) || ('\t' == buff[i]))
                {
                    break;
                }
            }

            for (; i < n; i++)
            {
                if ((' ' != buff[i]) && ('\t' != buff[i]))
                {
                    break;
                }
            }

        printf("NAME: (%s)\n", buff + i);

            if (0 == strcmp(buff + i, argv[1]))
            {
                printf("found %s, pid = %d\n", buff + i, atoi(pde->d_name));
                break;
            }
        }
    }

    closedir(pdir);
    return 0;
}