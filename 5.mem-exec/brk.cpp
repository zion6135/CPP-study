#include <unistd.h>
#include <iostream>
#include <time.h>
// 0.brk传入的参数比当前已分配的指针地址高，则分配内存。。
//      传入的参数比当前已分配的指针地址低，则释放内存。。
// 1.brk性能很差--会产生内存碎片
// 2.内存碎片：没有办法释放已经申请的内存---->为了解决这个问题：libc的接口malloc

int main() {
    void* p =sbrk(0); //指向当前堆的起始位置

    clock_t count = clock();

    for (unsigned int i = 0; i < 0x5fffff; i++) {
        int* p1 = (int*) p;
        int ret = brk(p1+1024); // malloc 4K
        p1[256] = 1024;
        ret = brk(p);   // free 4K
    }

    std::cout << "interval = " << clock() - count << "ticks" << std::endl;
}
