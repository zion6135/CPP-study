#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define _File_Save_ 0 
 
#define DEBUG_LOG(...) debug_log("DEBUG", __TIME__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#if _File_Save_
void debug_log(
			const char *logLevel,
			const char *time,
			const char *file,
            const char *func,    
            const int   iLine,
            const char *format ,...)  // __VA_ARGS__会把传入的参数以逗号隔开并且匹配到const char *format ,...
{
		#include <stdarg.h>
 
		static char output[1024]={0};
        va_list arg_list;
        va_start(arg_list,format);
        vsnprintf(output,sizeof(output),format, arg_list);
        printf("[%s][%s][%s][%s][%d]:%s\n",time, logLevel, file, func, iLine, output);
        va_end(arg_list);
}

#else

void debug_log(
			const char *logLevel,
			const char *time,
			const char *file,
            const char *func,    
            const int   iLine,
            const char *format ,...)
{
		#include <stdarg.h>
 
		static char output[1024]={0};
        va_list arg_list;
        va_start(arg_list,format);
        vsnprintf(output,sizeof(output),format, arg_list);
 
		FILE *file_descrip = fopen("/home/ts-ly/CPP-study/10.Skill/log.txt", "a+"); // 通过pwd来确认文件位置
        fprintf(file_descrip, "[%s][%s][%s][%s][%d]:%s\n",time, logLevel, file, func, iLine, output);
		fclose(file_descrip);
 
		va_end(arg_list);

}
#endif
int main()
{
	DEBUG_LOG("%s, ranking NO.%d", "You are so smart", 1); // 模仿printf的写法
 
	return 0;
}