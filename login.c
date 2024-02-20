#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "md5.h"
#include "menu.h"
#include "people.h"
#include "privacy.h"
#include "goods_mgr.h"




// 登录验证
void login_auth(void)
{
    char uname[51], upass[51], upass_md5[33], upass_new[33], passwd_change1[10], passwd_change2[10];
    char passwd_begin[10] = "888888";
    int login_flag = 0;

    printf("-------------------------------\n");
    printf("   用户登陆界面\n\n");
    printf("请按提示依次输入用户名和密码\n");
    printf("-------------------------------\n");
    printf("用户名：");
    scanf("%s", uname);
    printf("密码：");
    disable();
    scanf("%s", upass);
    enable();
    md5_string(upass, upass_md5);

    FILE* fp = fopen(USER_INFO_FILE, "rb");

    peoples ui;
    int auth_flag = 0;

    while(fread(&ui, sizeof(ui), 1, fp) == 1)
    {
        if(strcmp(ui.p_name, uname) == 0 && strcmp(ui.passwd, upass_md5) == 0)
        {
            auth_flag = 1;
            break;
        }
    }

    fclose(fp);

    if(auth_flag)   
    {
        goods_op();
    }
        
    else if(strcmp("boss",uname) == 0 && strcmp("888888" ,passwd_begin) == 0) 
    {
        printf("\n第一次进入账户请更改密码!");
        printf("\n请输入您的密码:");
        disable();
        scanf("%s", passwd_change1);
        printf("\n请确认您的密码:");
        scanf("%s", passwd_change2);
        enable();
        
        if(strcmp("boss",uname) == 0 && strcmp(passwd_change1 ,passwd_change2) == 0)
        {
            menu_op();
        } 
    }
    
    else
    {
        printf("-------------------------------\n");
        printf("\n用户名或密码错误,登录失败!\n");
        exit(1);
    }
}