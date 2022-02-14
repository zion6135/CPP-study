// 7.3进程终止
#include <stdio.h>
#include <stdlib.h>
#if 0
void first(void) {
    printf("first\n");
}

void secod(void) {
    printf("secod\n");
}
void third(void) {
    printf("third\n");
}
int main() {
    atexit(first);
    atexit(secod);
    atexit(third);

    printf("main\n");
    exit(0);
}
#endif

// 7.5环境表
// 打印环境变量
#if 0
#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main() {
    for (int i = 0; environ[i] != NULL; i++) {
        puts(environ[i]);
    }
    exit(0);
}
#endif
#if 0
#include <stdio.h>
#include <stdlib.h>

int main() {
    puts(getenv("PATH"));  // 获取环境变量PATH
    // 如果环境变量不存在，创建。如果存在，覆盖/添加。
    // puts(setenv("PATH", "111", 0));
    exit(0);
}
#endif

// 7.6 C程序的存储空间分布 