#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_list_p.h"
#include "people.h"

//创建链表
list_p creat_p(void)
{
    node_p* p = (node_p*)malloc(sizeof(node_p));

    if (NULL == p)
    {
        perror("malloc");
        return NULL;
    }

    p -> next = NULL;

    list_p l = NULL;

    l = (list_p)malloc(sizeof(*l));

    if(NULL == l)
    {
        perror("malloc");
        return NULL;
    }

    l -> head  = l -> tail = p;
    l -> size = 0;

    return l;
}



//销毁
void destory_p(list_p l)
{
    node_p* p = NULL;
    while(l -> head)
    {
        p = (node_p*)l -> head -> next;
        free(l -> head);
        l -> head = p;
    }
    free(l);    //释放链表信息结构体
}



//清空
void clear_p(list_p l)     
{
    node_p* p = (node_p*)l -> head -> next;
    
    node_p* k = NULL; //中间节点

    l -> head -> next = NULL;   //头节点指向空，保存下来

    while (p -> next)
    {
        k = (node_p*)p -> next;
        free(p);
        p = k;
    }
    l -> tail = l -> head;
    l -> size  = 0;
}



//头插
void push_front_p(list_p l , elem_type* data)
{
    //创建一个新节点
    node_p* p = (node_p*)malloc(sizeof(node_p));

    if(NULL == p)
    {
        perror("malloc");
        return ;
    }

    p -> data = *data;

    // 将新节点插入到链表中，原来的第一个节点变为该节点的后继，该节点成为第一个节点
    p -> next = l -> head -> next;
    l -> head -> next = (struct node *)p;       //不强转会报警告，下面有很多同类型的错误

    if(l -> size == 0) l -> tail = p;

    l -> size++; 
}



//尾插
void push_back_p(list_p l , elem_type* data)
{
    //创建一个新节点
    node_p* p = (node_p*)malloc(sizeof(node_p));

    if(NULL == p)
    {
        perror("malloc");
        return ;
    }

    p -> data = *data;


    // 将新节点插入到链表中，它将成为尾节点，而原来的尾节点的后继为该节点
    p -> next = NULL;
    l -> tail -> next = (struct node *)p;
    l -> tail = p;  //更新链表的尾指针，使其指向新插入的节点p
    l -> size++;
}



//删除某个节点,(假删，仅找到节点位置但不真正删除，只是让其不显示)
int remove_p(list_p l, void* data, int (*cmp)(void*, void*))
{
    node_p* p = (node_p*)l -> head -> next;
    int flag = 0;
     
    //寻找节点数据域数据
    while (NULL != p)
    {
        if(cmp(&(p -> data), data) != 0 && p -> data.is_delete != '0')      //假删
        {
            p -> data.is_delete = '0';
            break;
        }
        p = (node_p*)p -> next;
        flag++;
    }
    if(flag != -1 && p != NULL) return flag;    

    else return -1;     //未找到该节点返回-1
}



//修改某个节点（pos从0开始）
void change_p(list_p l, elem_type* data, int pos)
{
    node_p* p = (node_p*)l -> head -> next;

    for(int i = 0; i < pos; i++)    p = (node_p*)p -> next;

    p -> data = *data;
}



//查找某个节点的位置，(返回值为具体值，返回值可以用于文件中fseek)
int find_pos_p(list_p l, void* data, int(*cmp)(void*, void*))
{
    node_p* p = (node_p*)l -> head -> next;
    int flag = 0;

    while(NULL != p)
    {
        if(cmp(&(p -> data), data) != 0 && p -> data.is_delete != '0')
            break;
        p = (node_p*)p -> next;
        flag++;
    }
    if(flag != -1 && p != NULL) return flag;    

    else return -1;     //未找到该节点返回-1
}



//查找某个节点，返回值为节点数据(用于写入文件)
elem_type* find_data_p(list_p l, int num)
{
    node_p* p = (node_p*)l -> head -> next;

    for(int i = 0; i < num; i++)
    {
        p = (node_p*)p -> next;
    }

    if(NULL != p) return &(p -> data);
    return NULL;
}


//判空
int empty_p(list_p l)
{
    return !(l -> size);  //链表非为空返回0
}



//求长度
int size_p(list_p l)
{
    return l -> size;
}



//随机访问某个数据元素
elem_type* at_p(list_p l, int pos)
{
    node_p* p = (node_p*)l -> head -> next;

    while(pos--) p = (node_p*)p -> next;

    return &(p -> data);
}



//展示链表所有工人数据信息
void showall_peoples(list_p l)
{
    node_p* p = (struct node_p *)l -> head -> next;
    int flag = 0;

    while (NULL != p)
    {
        if(p -> data.is_delete == '1')
        {
            printf("\n\n姓名: %s\n性别: %s\n工号: %s\n身份证号: %s\n电话号码: %s\n住址:%s\n密码:%s\n",p -> data.p_name, p -> data.p_sex, p -> data.p_num, p -> data.p_id, p -> data.p_phone, p -> data.p_where, p-> data.passwd);
            flag++;
        }

        p = (node_p*)p -> next;
    }
    printf("\n\n我们有%d位店员噢!\n", flag);
    
}



//查找并输出商品结构体数据
void output_p(list_p l, void* data, int(*cmp)(void*, void*))
{
    node_p* p = (struct node_p *)l -> head -> next;
    int flag = 0;

    while(NULL != p)
    {
        if(cmp(&(p -> data), data) == 1)
        {
            printf("\n工人名:%s \n性别:%s \n工号:%s \n电话号码:%s \n身份证号:%s \n地址:%s \n",p -> data.p_name, p -> data.p_sex, p -> data.p_num, p -> data.p_phone, p -> data.p_id, p -> data.p_where);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 2)
        {
            printf("\n工人名:%s \n性别:%s \n工号:%s \n电话号码:%s \n身份证号:%s \n地址:%s \n",p -> data.p_name, p -> data.p_sex, p -> data.p_num, p -> data.p_phone, p -> data.p_id, p -> data.p_where);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 3)
        {
            printf("\n工人名:%s \n性别:%s \n工号:%s \n电话号码:%s \n身份证号:%s \n地址:%s \n",p -> data.p_name, p -> data.p_sex, p -> data.p_num, p -> data.p_phone, p -> data.p_id, p -> data.p_where);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 4)
        {
            printf("\n工人名:%s \n性别:%s \n工号:%s \n电话号码:%s \n身份证号:%s \n地址:%s \n",p -> data.p_name, p -> data.p_sex, p -> data.p_num, p -> data.p_phone, p -> data.p_id, p -> data.p_where);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 5)
        {
            printf("\n工人名:%s \n性别:%s \n工号:%s \n电话号码:%s \n身份证号:%s \n地址:%s \n",p -> data.p_name, p -> data.p_sex, p -> data.p_num, p -> data.p_phone, p -> data.p_id, p -> data.p_where);
            flag++;        
        }

        p = (struct node_p *)p -> next;
    }

    if(0 == flag) printf("\n未找到任何工人信息,是不是输入错误呢 ovo\n");
    else printf("\n未您找到%d名工人 ovo\n", flag);
}



//字符串比较函数，不同的返回值代表不同的意义
int cmp_str_p(void* data, void* data1)
{
    peoples* p = (peoples*)data;        //data是空类型指针，所以要强转，不然编译报错
    char* s = (char*)data1;

    if(0 == strcmp(p -> p_num, s)) return 1;        //工号
    else if(strstr(p -> p_id, s)) return 2;             //身份证号
    else if(0 == strcmp(p -> p_name, s)) return 3; //名字
    else if(0 == strcmp(p -> p_phone, s)) return 4;      //电话号码
    else if(0 == strcmp(p -> p_sex, s)) return 4;      //电话号码

    else return 0;
}