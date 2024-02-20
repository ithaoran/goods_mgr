#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "link_list.h"
#include "goods.h"

static list gs;    //静态全局变量，存放商品信息，且避免错乱

//商品信息初始化
void goods_init(void)
{
   gs = creat_l();

   // 将商品信息数据文件中的数据都读取到链表中来

   goods g;

   FILE* fp = fopen(GOODS_INFO_FILE, "rb");
    if(NULL == fp) return;

	while(fread(&g, sizeof(g), 1, fp) == 1)
	{
		push_back_l(gs, &g);
	}

	fclose(fp);
}

//商品信息的添加 
void goods_add(void)  
{
    goods g;
    char c;     //用于判断是否继续循环

    while (1)
    {
        printf("\n请按以下信息依次输入商品信息:\n");
        printf("请输入商品分区:(商品类型)  ");
        fscanf(stdin, "%s", g.goodstype);
        printf("请输入商品号:(69条型码,长度应为13位)  ");
        fscanf(stdin, "%s", g.id);
        printf("请输入商品名称:(合法即可)  ");
        fscanf(stdin, "%s", g.name);
        printf("请输入商品价格:(保留两位小数)  ");
        fscanf(stdin, "%f", &g.price);
        printf("请输入商品折扣:(数字1-10表示,10表示没有折扣)  ");
        fscanf(stdin, "%d", &g.discont);
        printf("请输入商品进货数量:");
        fscanf(stdin, "%d", &g.input_num);
        g.inventory = g.input_num;
        printf("请输入进货厂家:");
        fscanf(stdin, "%s", g.factory);

        time_t rawtime;
        struct tm* info;
        char buff[80];

        time(&rawtime);

        info = localtime(&rawtime);
        strcpy(g.time, asctime(info));
        // g.time = asctime(info);

        g.is_delete = '1';
        printf("\n loading ......\n");

        push_back_l(gs, (void*)&g);     //尾插，不加（void*）会报警告
        printf("\n录入信息成功!\n");

        FILE* fp = fopen(GOODS_INFO_FILE, "ab");
        if(NULL == fp) return;
	    fwrite(&g, sizeof(g), 1, fp);
	    fclose(fp);

        printf("\n是否需要继续输入商品信息:(Y/N) ");

         // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    

        if(c == 'n' || c == 'N') break;
    }
}



//商品信息的删除
void goods_del(void)
{
    char del_str[37];       //存放删除需要的信息
    int flag;           
    char c;                 //判断循环
    goods* del_g;

    while (1)
    {
        system("clear");
        printf("请输入你需要删除的商品信息(仅支持通过ID/商品名删除):  ");
        scanf("%s", del_str);

        flag = remove_l(gs, del_str, cmp_str);

        if(-1 != flag)
        {
            del_g = find_data(gs, flag);
            FILE* fp = fopen(GOODS_INFO_FILE, "r+");
            if(NULL == fp)
            {
                fprintf(stderr ,"error");
            }
            fseek(fp, flag * sizeof(goods), SEEK_SET);
            fwrite(del_g, sizeof(goods), 1, fp);
            fclose(fp);
            printf("\n删除成功!\n");
        }
        else
        {
            printf("\n未找到该商品,删除失败, 国咩纳塞 ovo\n");
        }
        printf("\n是否需要继续输入要删除的商品信息:(Y/N) ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    

        if(c == 'n' || c == 'N') break;
    }
    
}



//商品信息的修改
void goods_change()
{
    char change_str[46];  //存放修改的信息
    char c;               //判断循环
    goods* change_g;      //暂存商品文件指针

    while (1)
    {
        printf("\n请输入您要修改商品的信息(ID/商品名):  ");
        scanf("%s", change_str);

        if(-1 != find_pos(gs, change_str, cmp_str))
        {
            int flag = find_pos(gs, change_str, cmp_str);       //找到要修改商品的位置
            change_g = (goods*)find_data(gs, flag);
            printf("已为您找到该商品的信息如下: \n");
            printf("\n商品名: %s\n商品类型: %s\n商品ID: %s\n商品价格: %.2f\n商品进货数量: %d\n商品现存数量:%d\n生产商:%s\n入库时间:%s\n商品折扣:%d", change_g -> name, change_g -> goodstype, change_g -> id, change_g -> price, change_g -> input_num,change_g -> inventory, change_g -> factory, change_g -> time, change_g -> discont);

            //开始修改商品，使用循环套起来可以多次修改一个数据，防止误操作
            while (1)
            {
                printf("\n是否开始修改(Y/N)\n");
                while ((c = getchar()) != '\n' && c != EOF) ;
                c = getchar();
                if(c == 'N' || c == 'n') break;

                system("clear");
                printf("请输入商品(合法即可):");
                fscanf(stdin, "%s", change_g -> name);
                printf("请输入商品分区(商品类型):");
                fscanf(stdin, "%s", change_g -> goodstype);
                printf("请输入商品ID(69条型码,长度应为13位):");
                fscanf(stdin, "%s", change_g -> id);
                printf("请输入商品价格(合理即可):");
                fscanf(stdin, "%f", &(change_g -> price));
                printf("请输入商品进货数量(0-9 阿拉伯数字):");
                fscanf(stdin, "%d", &(change_g -> input_num));
                printf("请输入商品折扣:(数字1-10表示,10表示没有折扣)  ");
                fscanf(stdin, "%d", &(change_g -> discont));
                change_g -> inventory = change_g -> input_num;
                printf("请输入进货厂家:");
                fscanf(stdin, "%s", change_g -> factory);

                printf("\n是否需要再次修改本商品信息:(Y/N) ");

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

            change_l(gs, change_g, flag);

            //打开目标文件
            FILE* fp = fopen(GOODS_INFO_FILE, "r+");
            if(NULL == fp)
            {
                perror("error");
            }
            fseek(fp, flag * sizeof(goods), SEEK_SET);
            fwrite(change_g, sizeof(goods), 1, fp);
            fclose(fp);
            printf("\n修改成功!");
        }

        else
        {
            printf("\n未找到该商品,修改失败!");
        }

        printf("\n是否需要继续修改商品信息:(Y/N) ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    
        if(c == 'n' || c == 'N') break;
    }
 }



 //商品信息的查找
 void goods_find()
 {
    int num;
    char c;
    float goods_price;
    char goods_str[21];
    
    while (1)
    {
        printf("\n---> 请选择查找模式(序号): \n");
        printf("---> 1.全部查找\n");
        printf("---> 2.商品id查找\n");
        printf("---> 3.商品分区查找\n");
        printf("---> 4.商品价格查找\n");
        printf("---> 5.生产商查找\n");
        printf("---> 6.商品名查找\n");
        printf("---> 0.退出查找\n");
        printf(">: ");
        scanf("%d", &num);
    
        switch (num)
        {
            case 1:
                    system("clear");
                    showall_goods(gs);
                break;
            
            case 2:
                    system("clear");
                    printf("请输入您要查询的商品id:");
                    scanf("%s", goods_str);
                    output_l(gs, goods_str, cmp_str);
                break;

            case 3:
                    system("clear");
                    printf("请输入您要查询的商品分区:");
                    scanf("%s", goods_str);
                    output_l(gs, goods_str, cmp_str);

                break;

            case 4:
                    system("clear");
                    printf("请输入您要查询某个价格的商品:");
                    scanf("%f", &(goods_price));
                    output_l(gs, &(goods_price), cmp_float);
                break;

            case 5:
                    system("clear");
                    printf("请输入您需要查询的生产商:");
                    scanf("%s", goods_str);
                    output_l(gs, goods_str, cmp_str);
                break;

            case 6:     
                    system("clear");
                    printf("请输入您需要查询的商品名(支持模糊查询):");
                    scanf("%s", goods_str);
                    output_l(gs, goods_str, cmp_str);
                break;
        }
        if(0 == num) break;

        printf("\n是否需要继续查询商品信息:(Y/N) ");

        // 清空标准输入缓冲区中的所有数据，否则会导致下次调用 scanf 立即失败返回。一直到读到‘\n’，虽然不满足循环条件，但是先读取再循环，也相当于清除了。
        while((c = getchar()) != '\n' && c != EOF);
        c = getchar();    
        if(c == 'n' || c == 'N') break;
    }    
 }
    


