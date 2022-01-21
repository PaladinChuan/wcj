#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_
#include <stdio.h>
#include "list.h"

//航班内容结构体
typedef struct flight
{
	char number[18]; //航班号
	char staddress[18];//起点站
	char arraddress[18];//终点站
	int DATE[3];   //班期
	char TYPE[8];	//机型
	int stime;		//起飞时间
	int atime;      //到达时间
	int value;		//票价
}fly_t,*pfly_t;

//内核链表结构体
typedef struct kernel
{
	fly_t data;
	struct list_head list;
}kernel_t,*pkernel_t;

//初始化
extern void airplane_init(pkernel_t *p);
//创建节点
extern pkernel_t  create_node(fly_t d);
//头插
extern void airplane_insert_behind(pkernel_t p,fly_t d);
//尾插
extern void airplane_insert_front(pkernel_t p,fly_t d);
//遍历
extern void airplane_display(pkernel_t p);
//航班系统提示头
extern void airplane_start(void);

//航班内容输入
extern fly_t airplane_scanf_new(void);

//排序
extern void airplane_sort(pkernel_t p,fly_t d);

//航班内容删除
extern void airplane_scanf_del(pkernel_t p);
//删
//*num表示要删除的航班号
extern void airplane_del(pkernel_t p,char *num);

//打印单个信息
extern void airplane_print(pkernel_t node);

//航班内容输入
extern fly_t airplane_scanf(void);


//查
extern int airplane_search(pkernel_t p,char *num);

//改
extern int airplane_updata(pkernel_t p);

//航班内容查询
extern void airplane_scanf_search(pkernel_t p);


//排序
extern void  airplane_resort(pkernel_t p);

#endif 