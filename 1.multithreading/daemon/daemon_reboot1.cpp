// 如何调用【linux】shell命令行命令并获取命令行的输出内容

#include <stdio.h>
#include <string.h>
 
void executeCMD(const char *cmd, char *result)
{
    char buf_ps[1024];
    char ps[1024]={0};
    FILE *ptr;
    strcpy(ps, cmd);
    if((ptr=popen(ps, "r"))!=NULL)
    {
        while(fgets(buf_ps, 1024, ptr)!=NULL)
        {
//	       可以通过这行来获取shell命令行中的每一行的输出
//	   	   printf("%s", buf_ps);
           strcat(result, buf_ps);
           if(strlen(result)>1024)
               break;
        }
        pclose(ptr);
        ptr = NULL;
    }
    else
    {
        printf("popen %s error\n", ps);
    }
}
 
int main()
{
        char result[1024]={0};
        executeCMD("ps", result);
//      这行是将每一行的输出拼接之后获取到了result字符串中了
        printf("%s", result);
        return 0;
}