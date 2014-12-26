
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void password()
{
    int i, count = 0;
    char ZhangHao[9] = "000", zhanghao[9];
    char MiMa[8] = "000", mima[8];

    while(count < 3){
        printf("\033[2J\033[15;5H");
        printf("\t\t\t\t\033[33;42m  帐号  \033[0;0m  ");
        scanf("%s", zhanghao);
        printf("\n\n");
        printf("\t\t\t\t\033[33;42m  密码  \033[0;0m  ");
        system("stty -echo");
        scanf("%s", mima);
        system("stty echo");
        count++;
        if(strcmp(MiMa, mima) != 0 || strcmp(ZhangHao, zhanghao) != 0){
	    	if(count == 3){
            	printf("\n\n\n\t\t\t\t\033[31m输入次数超限！！！\033[0m\n");
            	exit(-1);
            }
            printf("\n\n\n\t\t\t\t\033[31m帐号或密码错误，按enter重新输入！！！\033[0m");
        }else {
            printf("\n\n\n\t\t\t\t\033[31m恭喜，按enter键继续......\033[0m\n");
            break;
        }
      getchar();
      getchar();
    }
}
