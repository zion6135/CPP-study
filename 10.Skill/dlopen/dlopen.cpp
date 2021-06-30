// 通过dlopen加载库，并且调用库的方法变量
// g++ -rdynamic -g -o main dlopen.cpp test.h -ldl
// ./main


#include <iostream>
#include <dlfcn.h> 
#include "test.h"
using namespace std;

typedef int (*func_ptr) (int, int);
typedef void (test_destory)(test_class* p);
typedef void (test_func)(test_class* p);
typedef test_class* (test_create)();

int main ()
{
    char* error;
    void* handle = dlopen("./libcaculate.so", RTLD_LAZY);
    if (!handle) {
        printf("error1\n");
        return 0;
    }

    // 清除之前的错误
    dlerror();

// 调用普通函数
    func_ptr fun_so = func_ptr(dlsym(handle, "add")); // 找到so中的add函数
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    printf("add = %d\n", (*fun_so)(2, 7));

// 调用类方法
    test_create* create_class = (test_create*)(dlsym(handle, "create")); // 返回类指针
    test_class* tmp = (*create_class)();

    test_func* test_exec = (test_func*)(dlsym(handle, "test")); // 返回类指针
    (*test_exec)(tmp);

    test_destory* destory_class = (test_destory*)(dlsym(handle, "destroy"));
    (*destory_class)(tmp);
 
    //  关闭动态库
    dlclose(handle);
}