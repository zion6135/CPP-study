#include <iostream>
#include <time.h>

class CTestClass
{
    char m_chrBuf[4096];
};

void test1() {
    for (unsigned int i = 0; i < 0x5fffff; i++) {
        CTestClass *p = new CTestClass;
        delete p;
    }
}

void test2() {
    for (unsigned int i = 0; i < 0x5fffff; i++) {
        CTestClass *p = (CTestClass *)malloc(sizeof(CTestClass));
        free(p);
    }
}

int main() {

    clock_t count = clock();
    
    test1();
    
    test2();


    std::cout << "interval = " << clock() - count << "ticks" << std::endl;
}
