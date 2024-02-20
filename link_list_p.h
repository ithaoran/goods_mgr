#ifndef LINK_LIST_H_P
#define LINK_LIST_H_P

#include "people.h"

typedef peoples elem_type;

typedef struct node_p
{
    elem_type data;
    struct node* next; 
}node_p;

typedef struct list_p
{
    node_p* head;
    node_p* tail;
    int size;
    int cap;
}*list_p;



list_p creat_p(void);  //创建链表
void push_front_p(list_p l , elem_type* data);  //头插
void push_back_p(list_p l , elem_type* data);   //尾插
void destory_p(list_p l);   //销毁
void clear_p(list_p l);     //清空
int empty_p(list_p l);     //判空
int size_p(list_p l);     //求长度
elem_type* at_p(list_p l, int pos);     //随机访问某个数据元素
void change_p(list_p l, elem_type* data, int pos);     //修改某个节点（pos从0开始）
int remove_p(list_p l, void* data_f, int (*cmp)(void*, void*));   //删除某个节点
//查找某个节点，返回值为节点数据(用于写入文件)
elem_type* find_data_p(list_p l, int num);
//查找某个节点的位置，(返回值为具体值，返回值可以用于文件中fseek)
int find_pos_p(list_p l, void* data, int(*cmp)(void*, void*));
//展示链表所有商品数据信息
void showall_peoples(list_p l);
//查找并输出商品结构体数据
void output_p(list_p l, void* data, int(*cmp)(void*, void*));


//字符串比较函数，不同的返回值代表不同的意义
int cmp_str_p(void* data, void* data1);

#endif