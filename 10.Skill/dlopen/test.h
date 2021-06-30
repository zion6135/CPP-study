// g++ -fPIC -shared test.cpp -o libcaculate.so 生成so

#include "stdio.h"
#ifdef __cplusplus
extern "C"
{
#endif
int add(int a,int b);

class test_class {
public:
    static int test() {
        printf("this is 5\n");
        return 5;
    }
};


#ifdef __cplusplus
}
#endif
