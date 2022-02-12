// 二.系统的数据文件和信息

// 1  /etc/passwd  6.2
// 通过getpwuid()查询/etc/passwd内容

// ./main 0 输出 "root"
#include <stdio.h>
#include <stdlib.h>
#if 0
#include <pwd.h>
#include <sys/types.h>
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage..\n");
        exit(1);
    }
    struct passwd *passwdline = getpwuid(atoi(argv[1]));
    puts(passwdline->pw_name);
    exit(0);
}
#endif
// 2  /etc/group  6.4
// 3  /etc/shadow  6.3
// 模拟电脑登陆界面用户和密码的选择

// 编译： g++ main.c -lcrpt
// sudo ./ a.out lbw  -----lbw是用户名 ,sudo 是需要访问/etc/shadow否则无权限
// Password-----输入账户密码
// 打印结果
#if 0

#include <crypt.h>
#include <shadow.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *input_pass;
    struct spwd *shadowlinw;
    if (argc < 2) {
        fprintf(stderr, "Usage..\n");
        exit(1);
    }
    //输入的密码
    input_pass = getpass("PassWord:");
    fprintf(stdout, " %s\n", input_pass);

    // 得到登陆的用户名
    shadowlinw = getspnam(argv[1]);
    fprintf(stdout, " %s\n", shadowlinw->sp_pwdp);  //打印加密口令 --- 可与/etc/shadow的用户argv[1]的内容比对

    // 加密后的口令 crypted_pass = crypt（ 密码 ， 加密口令）
    char *crypted_pass = crypt(input_pass, shadowlinw->sp_pwdp);

    //比对不同的Password用同一个加密口令（hadowlinw->sp_pwdp）
    if (strcmp(shadowlinw->sp_pwdp, crypted_pass) == 0)
        puts("ok!");  //密码正确
    else
        puts("fail");  //密码错误
}
#endif
// 4  时间戳  6.10
