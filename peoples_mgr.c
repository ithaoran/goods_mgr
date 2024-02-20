#include <stdio.h>
#include <stdlib.h>
#include "people.h"
#include "peoples_mgr.h"

void peoples_op()
{
    peopels_init();    //工人信息初始化
    int num;

    while (1)
    {
        system("clear");        //清空终端
        printf("\n*********************************************");
        printf("\n---- 欢迎来到商品信息管理系统! ovo ----");
        printf("\n---- 请选择您要使用的功能(序号)    ----");
        printf("\n----> 1.增加店员信息               ----");
        printf("\n----> 2.删除店员信息               ----");
        printf("\n----> 3.修改店员信息               ----");
        printf("\n----> 4.查看店员信息               ----");
        printf("\n----> 0.返回上一级菜单             ----");
        printf("\n*********************************************");
        printf("\n>:");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            system("clear");        //清空终端
            peopels_add();
            break;

        case 2:
            system("clear");        //清空终端
            peoples_del();
            break;

        case 3:
            system("clear");        //清空终端
            peoples_change();
            break;
        
        case 4:
            system("clear");        //清空终端
            peopels_find();
            break;

        }
        
        if(0 == num) break;
    }
    

}