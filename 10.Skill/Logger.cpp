#include <iostream>
#include <string>
#include <fstream>
#include <cstdarg>
using namespace std;
 
void fun(const char *format, ...)
{
	va_list args;
	va_start(args, format); //通过确定的参数确定在栈中的参考位置
 
    // 根据传入的参数来依次的解析数据：
    // 由于形参是从右到左入栈。从上到下依次入栈。
    // 传入的5个参数"AAA", 1, "BBB", 2 ,"xxxx" 
    // 而栈从上到下依次增长。
	cout << va_arg(args, char *) << endl;  // AAA
	cout << va_arg(args, int) << endl;  // 1
	cout << va_arg(args, char *) << endl;  // BBB
	cout << va_arg(args, int) << endl;  // 2
 
	va_end(args);
}
 
int main()
{
	fun("xxxx", "AAA", 1, "BBB", 2);
	return 0;
}