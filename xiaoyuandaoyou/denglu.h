
#include <stdio.h>

int denglu()
{
    int choice;
    printf("\033[2J\033[8;40H");
    printf("\t\t\033[42m                    \033[0m\n");
    printf("\t\t\t\t\t\t\033[42;33m   <1>管理员登陆    \033[0m\n");
    printf("\t\t\t\t\t\t\033[42m                    \033[0m\n\n");

    printf("\t\t\t\t\t\t\033[42m                    \033[0m\n");
    printf("\t\t\t\t\t\t\033[42;33m   <2>用户登陆      \033[0m\n");
    printf("\t\t\t\t\t\t\033[42m                    \033[0m\n\n");

    printf("\t\t\t\t\t\t\033[42m                    \033[0m\n");
    printf("\t\t\t\t\t\t\033[42;33m   <0>退出程序      \033[0m\n");
    printf("\t\t\t\t\t\t\033[42m                    \033[0m\n\n\n\n");

    printf("\t\t\t\t             请选择您的登陆模式：");
    scanf("%d", &choice);
    printf("\033[0m");
    
    return choice;
}
