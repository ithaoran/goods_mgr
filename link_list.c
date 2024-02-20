#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_list.h"
#include "goods.h"

//创建链表
list creat_l(void)
{
    node* p = (node*)malloc(sizeof(node));

    if (NULL == p)
    {
        perror("malloc");
        return NULL;
    }

    p -> next = NULL;

    list l = NULL;

    l = (list)malloc(sizeof(*l));

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
void destory_l(list l)
{
    node* p = NULL;
    while(l -> head)
    {
        p = l -> head -> next;
        free(l -> head);
        l -> head = p;
    }
    free(l);    //释放链表信息结构体
}



//清空
void clear_l(list l)     
{
    node* p = l -> head -> next;
    
    node* k = NULL; //中间节点

    l -> head -> next = NULL;   //头节点指向空，保存下来

    while (p -> next)
    {
        k = p -> next;
        free(p);
        p = k;
    }
    l -> tail = l -> head;
    l -> size  = 0;
}



//头插
void push_front_l(list l , elem_type* data)
{
    //创建一个新节点
    node* p = (node*)malloc(sizeof(node));

    if(NULL == p)
    {
        perror("malloc");
        return ;
    }

    p -> data = *data;

    // 将新节点插入到链表中，原来的第一个节点变为该节点的后继，该节点成为第一个节点
    p -> next = l -> head -> next;
    l -> head -> next = p;

    if(l -> size == 0) l -> tail = p;

    l -> size++; 
}



//尾插
void push_back_l(list l , elem_type* data)
{
    //创建一个新节点
    node* p = (node*)malloc(sizeof(node));

    if(NULL == p)
    {
        perror("malloc");
        return ;
    }

    p -> data = *data;


    // 将新节点插入到链表中，它将成为尾节点，而原来的尾节点的后继为该节点
    p -> next = NULL;
    l -> tail -> next = p;
    l -> tail = p;  //更新链表的尾指针，使其指向新插入的节点p
    l -> size++;
}



//删除某个节点,(假删，仅找到节点位置但不真正删除，只是让其不显示)
int remove_l(list l, void* data, int (*cmp)(void*, void*))
{
    node* p = l -> head -> next;
    int flag = 0;
     
    //寻找节点数据域数据
    while (NULL != p)
    {
        if(cmp(&(p -> data), data) != 0 && p -> data.is_delete != '0')      //假删
        {
            p -> data.is_delete = '0';
            break;
        }
        p = p -> next;
        flag++;
    }
    if(flag != -1 && p != NULL) return flag;    

    else return -1;     //未找到该节点返回-1
}



//修改某个节点（pos从0开始）
void change_l(list l, elem_type* data, int pos)
{
    node* p = l -> head -> next;

    for(int i = 0; i < pos; i++)    p = p -> next;

    p -> data = *data;
}



//查找某个节点的位置，(返回值为具体值，返回值可以用于文件中fseek)
int find_pos(list l, void* data, int(*cmp)(void*, void*))
{
    node* p = l -> head -> next;
    int flag = 0;

    while(NULL != p)
    {
        if(cmp(&(p -> data), data) != 0 && p -> data.is_delete != '0')
            break;
        p = p -> next;
        flag++;
    }
    if(flag != -1 && p != NULL) return flag;    

    else return -1;     //未找到该节点返回-1
}



//查找某个节点，返回值为节点数据(用于写入文件)
elem_type* find_data(list l, int num)
{
    node* p = l -> head -> next;

    for(int i = 0; i < num; i++)
    {
        p = p -> next;
    }

    if(NULL != p) return &(p -> data);
    return NULL;
}


//判空
int empty_l(list l)
{
    return !(l -> size);  //链表非为空返回0
}



//求长度
int size_l(list l)
{
    return l -> size;
}



//随机访问某个数据元素
elem_type* at(list l, int pos)
{
    node* p = l -> head -> next;

    while(pos--) p = p -> next;

    return &(p -> data);
}



//展示链表所有商品数据信息
void showall_goods(list l)
{
    node* p = l -> head -> next;

    while (NULL != p)
    {
        if(p -> data.is_delete == '1')
        {
            printf("\n\n商品名: %s\n商品类型: %s\n商品ID: %s\n商品价格: %.2f\n商品进货数量: %d\n商品现存数量:%d\n生产商:%s\n入库时间:%s商品折扣:%d\n",p -> data.name, p -> data.goodstype, p -> data.id, p -> data.price, p -> data.input_num, p -> data.inventory, p -> data.factory, p -> data.time, p -> data.discont);
        }

        p = p -> next;
    }
    
}



//查找并输出商品结构体数据
void output_l(list l, void* data, int(*cmp)(void*, void*))
{
    node* p = l -> head -> next;
    int flag = 0;

    while(NULL != p)
    {
        if(cmp(&(p -> data), data) == 1)
        {
            printf("\n商品名:%s \n商品类型:%s \n商品ID:%s \n商品价格:%.2f \n商品进货数量:%d \n商品库存:%d \n生产商:%s \n入库时间:%s \n",p -> data.name, p -> data.goodstype, p -> data.id, p -> data.price, p -> data.input_num, p -> data.inventory, p -> data.factory, p -> data.time);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 2)
        {
            printf("\n商品名:%s \n商品类型:%s \n商品ID:%s \n商品价格:%.2f \n商品进货数量:%d \n商品库存:%d \n生产商:%s \n入库时间:%s \n",p -> data.name, p -> data.goodstype, p -> data.id, p -> data.price, p -> data.input_num, p -> data.inventory, p -> data.factory, p -> data.time);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 3)
        {
            printf("\n商品名:%s \n商品类型:%s \n商品ID:%s \n商品价格:%.2f \n商品进货数量:%d \n商品库存:%d \n生产商:%s \n入库时间:%s \n",p -> data.name, p -> data.goodstype, p -> data.id, p -> data.price, p -> data.input_num, p -> data.inventory, p -> data.factory, p -> data.time);
            flag++;        
        }
        else if(cmp(&(p -> data), data) == 4)
        {
            printf("\n商品名:%s \n商品类型:%s \n商品ID:%s \n商品价格:%.2f \n商品进货数量:%d \n商品库存:%d \n生产商:%s \n入库时间:%s \n",p -> data.name, p -> data.goodstype, p -> data.id, p -> data.price, p -> data.input_num, p -> data.inventory, p -> data.factory, p -> data.time);
            flag++;        
        }

        p = p -> next;
    }

    if(0 == flag) printf("\n未找到任何商品信息,是不是输入错误呢 ovo\n");
    else printf("\n未您找到%d件商品 ovo\n", flag);
}



//整数比较函数，不同的返回值代表不同的意义
int cmp_int(void* data, void* data1)
{
    goods* p = (goods*)data;        //data是空类型指针，所以要强转，不然编译报错
    int* i = (int*)data1;

    // if(i[0] <= p -> inventory && i[1] >= p -> inventory) return 1;      //用于比较商品库存信息
    if(*i == p -> inventory ) return 1;

    return 0;
}



//浮点数比较函数，不同的返回值代表不同的意义
int cmp_float(void* data, void* data1)
{
    goods* p = (goods*)data;        //data是空类型指针，所以要强转，不然编译报错
    float* f = (float*)data1;

    // if(f[0] <= p -> price  && f[1] >= p -> price) return 1;     //用于比较商品价格信息
    if(*f == p -> price ) return 1;

    return 0;
}



//字符串比较函数，不同的返回值代表不同的意义
int cmp_str(void* data, void* data1)
{
    goods* p = (goods*)data;        //data是空类型指针，所以要强转，不然编译报错
    char* s = (char*)data1;

    if(0 == strcmp(p -> goodstype, s)) return 1;        //商品类型
    // else if(0 == strcmp(p -> name, s)) return 2;     //商品名
    else if(strstr(p -> name, s)) return 2;             //商品名
    else if(0 == strcmp(p -> factory, s)) return 3;     //厂家
    else if(0 == strcmp(p -> id, s)) return 4;          //商品id

    else return 0;
}