/*************************************************************************
	> File Name: welcom.c
	> Author: 
	> Mail: 
	> Created Time: 2014年12月11日 星期四 15时54分34秒
 ************************************************************************/

#include <stdio.h>

//欢迎使用
void welcom()
{
    printf("\033[2J\033[10;1H");
    printf("\t\t\t\033[31m                      LL\n");
    printf("\t\t\t                      LL\n");
    printf("\t\t\tWW      WW  EEEEEEEE  LL          CCCCCCCC   OOOOOOOO  MMMMMMMMMM  EEEEEEEE\n");
    printf("\t\t\tWW      ww EE      EE LL         CC      CC OO      OO MM  MM  MM EE      EE\n");
    printf("\t\t\tWW      ww EEEEEEEEEE LL         CC         OO      OO MM  MM  MM EEEEEEEEEE\n");
    printf("\t\t\tWW  ww  ww EE         LL      LL CC         OO      OO MM  MM  MM EE        \n");
    printf("\t\t\tWWww  wwww EE      EE  LL    LL  CC      CC OO      OO MM  MM  MM EE      EE\n");
    printf("\t\t\t Ww    ww   EEEEEEEE     LLLL     CCCCCCCC   OOOOOOOO  MM  MM  MM  EEEEEEEE \n\n\n");
    printf("\t\t\t      \033[33m         **欢迎使用西安邮电大学校园导航系统**\n\033[0m");
}
