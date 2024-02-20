#include <stdio.h>
#include <stdlib.h>
#include "goods.h"
#include "goods_mgr.h"


void goods_op()
{
    goods_init();      //商品信息初始化
    int num;

    while (1)
    {
        system("clear");        //清空终端
        printf("\n*********************************************");
        printf("\n---- 欢迎来到商品信息管理系统! ovo ----");
        printf("\n---- 请选择您要使用的功能(序号)    ----");
        printf("\n----> 1.增加商品信息               ----");
        printf("\n----> 2.删除商品信息               ----");
        printf("\n----> 3.修改商品信息               ----");
        printf("\n----> 4.查看商品信息               ----");
        printf("\n----> 0.返回上一级菜单             ----");
        printf("\n*********************************************");
        printf("\n>:");
        scanf("%d", &num);

        switch (num)
        {
            case 1:
                system("clear");        //清空终端
                goods_add();
                break;

            case 2:
                system("clear");        //清空终端
                goods_del();
                break;

            case 3:
                system("clear");        //清空终端
                goods_change();
                break;

            case 4:
                system("clear");        //清空终端
                goods_find();
                break;

            }

            if(0 == num) break;
    }
    
}