#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "people.h"
#include "link_list_p.h"
#include "md5.h"


static list_p gp;    //全局变量，存放工人信息


//判断用户是否存在
int check_user_name(const char* user_name)
{
    FILE* fp = fopen(USER_INFO_FILE, "rb");

    if(NULL == fp)
    {
        fprintf(stderr, "error");
    }

    peoples ui;

    int exist_flag = 0;

    while (fread(&ui, sizeof(ui), 1, fp) == 1)
    {
        if(strcmp(ui.p_name, user_name) == 0)
        {
            exist_flag = 1;
            break;
        }
    }

    fclose(fp);

    return !exist_flag; //有重复返回0
}



//人员信息初始化
void peopels_init(void)
{
    gp = creat_p();

    // 将人员信息数据文件中的数据都读取到链表中来

    peoples p;

    FILE* fp = fopen(USER_INFO_FILE, "rb");
    if(NULL == fp) return;

	while(fread(&p, sizeof(p), 1, fp) == 1)
	{
		push_back_p(gp, (void*)&p);
	}

	fclose(fp);
}



//人员信息添加
void peopels_add(void)
{
    peoples p;
    char c;     //用于判断是否继续循环
    char passwd[10];    //用于加密的密码

    while (1)
    {
        printf("请按以下信息依次输入人员信息:\n");

        while (1)
        {
            printf("请输入工人姓名:  ");
            fscanf(stdin, "%s", p.p_name);

            if(check_user_name(p.p_name)) break;

            printf("\n用户已存在,请重新输入！\n");
        }
        
        
        printf("请输入工人性别:  ");
        fscanf(stdin, "%s", p.p_sex);
        printf("请输入工人密码:(6位,注意保护自己的密码)  ");
        fscanf(stdin, "%s", passwd);
        md5_string(passwd, p.passwd);
        printf("请输入工人编号:(8位)  ");
        fscanf(stdin, "%s", p.p_num);
        printf("请输入工人身份证号:(18位合法)  ");
        fscanf(stdin, "%s", p.p_id);
        printf("请输入工人电话号码:(11位合法)  ");
        fscanf(stdin, "%s", p.p_phone);
        printf("请输入工人地址 :");
        fscanf(stdin, "%s", p.p_where);
        
        
        p.is_delete = '1';

        push_back_p(gp, (void*)&p);     //尾插，不加（void*）会报警告

        printf("\n录入信息成功!\n");

        FILE* fp = fopen(USER_INFO_FILE, "ab");
        if(NULL == fp) return;
	    fwrite(&p, sizeof(p), 1, fp);
	    fclose(fp);

        printf("\n是否需要继续输入工人信息:(Y/N)  ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    

        if(c == 'n' || c == 'N') break;
    }
}



//人员信息的删除
void peoples_del(void)
{
    char del_str[37];
    int flag;
    char c;
    peoples* del_p;

    while (1)
    {
        system("clear");
        printf("请输入你需要删除的工人信息(支持通过工号/身份证号/姓名删除):  ");
        scanf("%s", del_str);

        flag = remove_p(gp, del_str, cmp_str_p);

        if(-1 != flag)
        {
            del_p = find_data_p(gp, flag);
            FILE* fp = fopen(USER_INFO_FILE, "r+");
            if(NULL == fp)
            {
                fprintf(stderr ,"error");
            }
            fseek(fp, flag * sizeof(peoples), SEEK_SET);
            fwrite(del_p, sizeof(peoples), 1, fp);
            fclose(fp);
            printf("\n删除成功!\n");
        }
        else
        {
            printf("\n未找到该工人信息,删除失败, 国咩纳塞 ovo\n");
        }
        printf("\n是否需要继续输入工人信息:(Y/N) ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    

        if(c == 'n' || c == 'N') break;
    }
    
}



//商品信息的修改
void peoples_change()
{
    char change_str[46];  //存放修改的信息
    char c;               //判断循环
    peoples* change_g;      //暂存商品文件指针

    while (1)
    {
        printf("请输入您要修改工人的信息(工号/姓名):  \n");
        scanf("%s", change_str);

        if(-1 != find_pos_p(gp, change_str, cmp_str_p))
        {
            int flag = find_pos_p(gp, change_str, cmp_str_p);       //找到要修改工人信息的位置
            change_g = (peoples*)find_data_p(gp, flag);
            printf("已为您找到该工人的信息，(如下): \n");
            printf("\n姓名: %s\n性别: %s\n工号: %s\n电话号码: %s\n身份证号:%s\n住址: %s\n", change_g -> p_name, change_g -> p_sex, change_g -> p_num, change_g -> p_phone, change_g -> p_id,change_g -> p_where);

            //开始修改商品，使用循环套起来可以多次修改一个数据，防止误操作
            while (1)
            {
                printf("\n是否开始修改(Y/N)\n");
                while ((c = getchar()) != '\n' && c != EOF);
                c = getchar();
                if(c == 'N' || c == 'n') break;

                system("clear");
                printf("请输入工人姓名:");
                fscanf(stdin, "%s", change_g -> p_name);
                printf("请输入工人性别:");
                fscanf(stdin, "%s", change_g -> p_sex);
                printf("请输入工号:");
                fscanf(stdin, "%s", change_g -> p_num);
                printf("请输入电话号码:");
                fscanf(stdin, "%s", change_g -> p_phone);
                printf("请输入身份证号:");
                fscanf(stdin, "%s", change_g -> p_id);
                printf("请输入住址:");
                fscanf(stdin, "%s", change_g -> p_where);

                printf("\n是否需要再次修改本工人信息:(Y/N) ");

                // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
                while((c = getchar()) != '\n'  && c != EOF);        //EOF文件结束标志
                c = getchar();    

                if(c == 'y' || c == 'Y') 
                {
                    system("clear");
                    continue;
                }
                else break;
            }

            change_p(gp, (void*)change_g, flag);

            //打开目标文件
            FILE* fp = fopen(USER_INFO_FILE, "r+");
            if(NULL == fp)
            {
                perror("error");
            }
            fseek(fp, flag * sizeof(peoples), SEEK_SET);
            fwrite(change_g, sizeof(peoples), 1, fp);
            fclose(fp);
        }
        else
        {
            printf("未找到该工人信息，修改失败!\n");
        }
        printf("\n是否需要继续修改工人信息:(Y/N) ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    
        if(c == 'n' || c == 'N') break;
    }
 }



//工人信息的查找
void peopels_find()
{
    int num;
    char c;
    char peoples_str[51];

    while (1)
    {
        printf("\n---> 请选择查找模式(序号): \n");
        printf("---> 1.全部查找\n");
        printf("---> 2.姓名查找\n");
        printf("---> 3.工号查找\n");
        printf("---> 4.电话号码查找\n");
        printf("---> 5.性别查找\n");
        printf("---> 6.身份证号查找\n");
        printf("---> 0.退出查找\n");
        printf(">: ");
        scanf("%d", &num);
    
        switch (num)
        {
            case 1:
                    system("clear");
                    showall_peoples(gp);
                break;
            
            case 2:
                    system("clear");
                    printf("请输入您要查询的工人姓名:");
                    scanf("%s", peoples_str);
                    output_p(gp, peoples_str, cmp_str_p);
                break;

            case 3:
                    system("clear");
                    printf("请输入您要查询的工人工号:");
                    scanf("%s", peoples_str);
                    output_p(gp, peoples_str, cmp_str_p);

                break;

            case 4:
                    system("clear");
                    printf("请输入您要查询某个工人的电话号码:");
                    scanf("%s", peoples_str);
                    output_p(gp, peoples_str, cmp_str_p);
                break;

            case 5:
                    system("clear");
                    printf("请输入您需要查询的工人性别:");
                    scanf("%s", peoples_str);
                    output_p(gp, peoples_str, cmp_str_p);
                break;

            case 6:     
                    system("clear");
                    printf("请输入您需要查询的身份证号(支持模糊查询):");
                    scanf("%s", peoples_str);
                    output_p(gp, peoples_str, cmp_str_p);
                break;
        }
        if(0 == num) break;

        printf("\n是否需要继续查找工人信息:(Y/N) ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    
        if(c == 'n' || c == 'N') break;
    } 
 }
    







