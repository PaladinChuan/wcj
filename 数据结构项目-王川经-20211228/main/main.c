#include "../include/airplane.h"

int main(void)
{
	pkernel_t p;		//建立一个航班系统
	fly_t d;
	airplane_init(&p);	//创建一个头
	airplane_start();
	int choose;
	while(1)			//插入操作
	{
		printf("系统有如下操作命令：\n");
		printf("\033[47;31m\033[5m(0添加航班信息)\n");
		printf("\033[47;33m(1删除航班信息)\n");
		printf("\033[47;34m(2查询航班信息)\n");
		printf("\033[47;32m(3修改航班信息)\n");
		printf("\033[47;35m(4查看所有航班)\n");
		printf("\033[47;30m(5航班信息排序)\n");
		printf("\033[47;31m(6退出航班系统)\n");
		printf("\033[40;37m\033[0m请输入命令：");
		scanf("%d",&choose);
		switch(choose)
		{
			case 0:							//添加航班信息
					//输入航班数据
					d = airplane_scanf_new();
					airplane_insert_behind(p,d);
					//按序插入
					//airplane_sort(p,d);
					//遍历
					airplane_display(p);
				break;
			case 1:							//删除航班信息
					airplane_scanf_del(p);
				break;
			case 2:							//查询航班信息
					airplane_scanf_search(p);
				break;
				
			case 3:							//替换航班信息
					airplane_updata(p);
				break;
				
			case 4:							//遍历航班信息
					//遍历
					airplane_display(p);					
				break;
			case 5:		
					airplane_resort(p);		//排序
				break;
			case 6:							//退出系统
				return 0;
				break;

		//头插
		//airplane_insert_behind(p,d);
		//尾插
		//airplane_insert_front(p,d);
		
		}
	}
	
	
	return 0;
}