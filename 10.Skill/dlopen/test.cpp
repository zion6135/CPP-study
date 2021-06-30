// g++ -fPIC -shared -g test.cpp -o libcaculate.so 生成so

#include "stdio.h"
#include "test.h"
int add(int a,int b)
{
    printf("this is result\n");
    return (a + b);
}

extern "C" test_class* create() {
    printf("this is class new\n");
    return new test_class();
}

extern "C" void test(test_class* p) {
    p->test();
}

extern "C" void destroy(test_class* p) {
    printf("this is class delete\n");
    delete p;
}

int main() {
    return 0;
}