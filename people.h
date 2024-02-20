#ifndef PEOPLE_H
#define PEOPLE_H

#define USER_INFO_FILE "./user_info.dat"


typedef struct people 
{
    char passwd[100];     //密码
    char p_num[9];       //工号
    char p_name[21];    //姓名
    char p_sex[5];      //性别
    char p_phone[12];   //电话号码
    char p_id[20];      //身份证号码
    char p_where[61];   //地址
    char is_delete;     //商品现存状态（1表示存在，0表示被删除）

}peoples;

void peopels_init(void);        //人员信息初始化
void peopels_add(void);         //人员增加
void peoples_del(void);       //人员信息的删除
void peoples_change(void);        //人员信息的修改
void peopels_find(void);        //人员信息的查找
//判断用户是否存在
int check_user_name(const char* user_name);



#endif