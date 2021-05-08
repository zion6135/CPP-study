#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "malloc.h"

struct point_buffer
{
    int     len;
    char    *data = nullptr;
}__attribute((packed));  //不用字节对齐

#define CURR_LENGTH 12
int main() {

    struct point_buffer* pbuffer;
    // =====================
    // 指针数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test3:%ld\n",sizeof(struct point_buffer));
    ///  开辟
    if ((pbuffer = (struct point_buffer *)malloc(sizeof(struct point_buffer))) != NULL)
    {
        pbuffer->len = CURR_LENGTH;
        if ((pbuffer->data = (char *)malloc(sizeof(char) * CURR_LENGTH)) != NULL)
        {
        memcpy(pbuffer->data, "Hello World", CURR_LENGTH);
        printf("the length of zbuffer:%ld\n",malloc_usable_size(pbuffer->data)); //查看分配的内存的大小
                                                                                 


        printf("%d, %s\n", pbuffer->len, pbuffer->data);
        }
    }

    /// 销毁
    free(pbuffer->data);
    free(pbuffer);
    pbuffer = NULL;
}
