#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "peoples_mgr.h"
#include "goods_mgr.h"


void menu_op()
{
    int num;

    while (1)
    {
        system("clear");        //清空终端
        printf("\n*********************************************");
        printf("\n---- 欢迎进入管理员管理系统! ovo   ----");
        printf("\n---- 请选择您要使用的功能(序号)    ----");
        printf("\n----> 1.管理商品信息               ----");
        printf("\n----> 2.管理店员信息               ----");
        printf("\n----> 0.退出系统                   ----");
        printf("\n*********************************************");
        printf("\n>:");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            system("clear");        //清空终端
            goods_op();
            break;
        case 2:
            system("clear");        //清空终端
            peoples_op();
            break;
        }
        if(0 == num) break;
    }
}