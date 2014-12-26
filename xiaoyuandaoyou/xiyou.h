
#include <stdio.h>
#include <stdlib.h>

//西邮简介
void xiyou()
{
    char jianjie[1000];
    FILE *fp;
    if((fp = fopen("xiyoujianjie", "rt")) == NULL){
        printf("\033[31m抱歉，不能打开西邮简介的文件！\033[0m\n");
        exit -1;
    }
    while((fgets(jianjie, 1000, fp)) != NULL)
        printf("\033[33m%s\n\n\n", jianjie);
    fclose(fp);
    printf("\t\t\t\t\t\033[33m     按任意键继续......\033[0m");
    getchar();
}


