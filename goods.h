#ifndef GOODS_H
#define GOODS_H

#define GOODS_INFO_FILE "./goods_info.dat"

typedef struct 
{
    char id[20];         //商品ID
    char name[37];      //商品名
    char is_delete;     //商品现存状态（1表示存在，0表示被删除）
    char goodstype[20]; //商品类型
    char factory[46];   //厂家
    char time[50];      //商品进货时间
//char类型的数据放在一起定义，节省内存空间

    float price;        //商品价格
    
    int input_num;      //商品进货数量
    int inventory;        //商品库存
    int discont;        //商品折扣
}goods;


void goods_init(void);     //商品信息初始化
void goods_add(void);       //商品信息的添加 
void goods_del(void);       //商品信息的删除
void goods_change(void);    //商品信息的修改
void goods_find(void);      //商品信息的查找

#endif