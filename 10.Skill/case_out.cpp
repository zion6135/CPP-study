
#include "iostream"


int main()
{
    int flag = 1;
    switch (flag)
    {
        case 1:
        case 2:
            if (flag == 1) {
                printf("000\n");
            } else {
                printf("222\n"); 

            }
            break;
    }

    return 0;
}