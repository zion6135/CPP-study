#include <stdio.h>
#include <stdlib.h>
#include <cstring>
struct point_buffer
{
    int     len;
    char    *data = nullptr;
};
#define CURR_LENGTH 12
int main() {

    struct point_buffer* pbuffer;
    // =====================
    // 指针数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("%d\n",sizeof(int));
    printf("the length of struct test3:%d\n",sizeof(struct point_buffer));
    ///  开辟
    if ((pbuffer = (struct point_buffer *)malloc(sizeof(struct point_buffer))) != NULL)
    {
        pbuffer->len = CURR_LENGTH;
        if ((pbuffer->data = (char *)malloc(sizeof(char) * CURR_LENGTH)) != NULL)
        {
            memcpy(pbuffer->data, "Hello World", CURR_LENGTH);


            printf("%d, %s\n", pbuffer->len, pbuffer->data);
        }
    }

    /// 销毁
    free(pbuffer->data);
    free(pbuffer);
    pbuffer = NULL;
}
