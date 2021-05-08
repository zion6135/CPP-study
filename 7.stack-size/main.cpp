#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <exception>
#include "string.h"
rlimit my_rlimit;
 
int main() {

    /*----------------------------------- get stack rlimit ----------------------------------------*/
    // int ret = getrlimit(RLIMIT_STACK, &my_rlimit);
    // printf("stack rlimit: (%llu)  (%llu)\n", my_rlimit.rlim_cur, my_rlimit.rlim_max);
 
 try {


 }
 catch(std::exception& e){    //这里用来捕捉标准异常
    std::cout<<"standard library expection "<< e.what() << std::endl;
}
catch(...){
    std::cout<<"xxxxxxxxxxxxxx "<< std::endl;
}
    return 0;
}