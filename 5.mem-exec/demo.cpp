// zero_length_array.c
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <malloc.h>


#define MAX_LENGTH      1024
#define CURR_LENGTH      512

//  0长度数组
struct zero_buffer
{
    int     len;
    char    data[0];

}__attribute((packed));


int main(void)
{
    struct zero_buffer  *zbuffer = NULL;

    // =====================
    // 0长度数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test1:%ld\n",sizeof(struct zero_buffer));   //sizeof(struct zero_buffer) = sizeof(int)
    ///  开辟
    if ((zbuffer = (struct zero_buffer *)malloc(sizeof(struct zero_buffer) + sizeof(char) * CURR_LENGTH)) != NULL)
    {
        zbuffer->len = CURR_LENGTH;
        memcpy(zbuffer->data, "Hello World", CURR_LENGTH);
        printf("the length of zbuffer:%ld\n",malloc_usable_size(zbuffer)); //查看分配的内存的大小


        printf("%d, %s\n", zbuffer->len, zbuffer->data);
    }
    ///  销毁
    free(zbuffer);
    zbuffer = NULL;



    return EXIT_SUCCESS;
}