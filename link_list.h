#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "goods.h"

typedef goods elem_type;

typedef struct node
{
    elem_type data;
    struct node* next; 
}node;

typedef struct list
{
    node* head;
    node* tail;
    int size;
    int cap;
}*list;



list creat_l(void);  //创建链表
void push_front_l(list l , elem_type* data);  //头插
void push_back_l(list l , elem_type* data);   //尾插
void destory_l(list l);   //销毁
void clear_l(list l);     //清空
int empty_l(list l);     //判空
int size_l(list l);     //求长度
elem_type* at(list l, int pos);     //随机访问某个数据元素
void change_l(list l, elem_type* data, int pos);     //修改某个节点（pos从0开始）
int remove_l(list l, void* data_f, int (*cmp)(void*, void*));   //删除某个节点
//查找某个节点，返回值为节点数据(用于写入文件)
elem_type* find_data(list l, int num);
//查找某个节点的位置，(返回值为具体值，返回值可以用于文件中fseek)
int find_pos(list l, void* data, int(*cmp)(void*, void*));
//展示链表所有商品数据信息
void showall_goods(list l);
//查找并输出商品结构体数据
void output_l(list l, void* data, int(*cmp)(void*, void*));


//整数比较函数，不同的返回值代表不同的意义
int cmp_int(void* data, void* data1);
//浮点数比较函数，不同的返回值代表不同的意义
int cmp_float(void* data, void* data1);
//字符串比较函数，不同的返回值代表不同的意义
int cmp_str(void* data, void* data1);

#endif