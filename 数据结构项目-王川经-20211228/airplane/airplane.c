#include "../include/airplane.h"
#include <stdlib.h>
#include <string.h>
//初始化
void airplane_init(pkernel_t *p)
{
	*p=(pkernel_t)malloc(sizeof(kernel_t));
	if(*p==NULL)
	{
		perror("航班系统初始化失败\n");
		return ;
	}
	
	INIT_LIST_HEAD(&(*p)->list);
}

//创建节点
pkernel_t  create_node(fly_t d)
{
	pkernel_t p=(pkernel_t)malloc(sizeof(kernel_t));
	if(p==NULL)
	{
		perror("创建新航班信息失败\n");
		return NULL;
	}	
	
	p->data = d;
	INIT_LIST_HEAD(&p->list);
	return p;
}

//头插
void airplane_insert_behind(pkernel_t p,fly_t d)
{
	pkernel_t node = create_node(d);
	if(node == NULL)
		return ;
	
	//插入后面
	list_add(&node->list, &p->list);
}

//尾插
void airplane_insert_front(pkernel_t p,fly_t d)
{
	pkernel_t node = create_node(d);
	if(node == NULL)
		return ;
	
	//插入后面
	list_add_tail(&node->list, &p->list);
}


//排序
void airplane_sort(pkernel_t p,fly_t d)
{
	
	//创建一个临时节点
	struct list_head *pos;
	//创建一个临时变量node
	pkernel_t node=p;
	
	list_for_each(pos, &p->list)
	{
			node = list_entry(pos, typeof(*p), list);
			//刚输入的起飞日期如果小于存储中的某个值得话，那么就尾插
			if(node->data.DATE[0]>d.DATE[0])
			{
				airplane_insert_front(node,d);
				return;
			}
			else if(node->data.DATE[0]==d.DATE[0])
			{
				if(node->data.DATE[1]>d.DATE[1])
				{
					airplane_insert_front(node,d);
					return;
				}
				else if(node->data.DATE[1]==d.DATE[1])
				{
					if(node->data.DATE[2]>d.DATE[2])
					{
						airplane_insert_front(node,d);
						return;
					}
					else if(node->data.DATE[2]==d.DATE[2])
					{
						if(node->data.stime>d.stime)
						{
							airplane_insert_front(node,d);
							return;
						}
					}
				}
			}
			else ;
	}
	//如果都不成立，那么插入最后一个Node后面
	airplane_insert_behind(node,d);
	
}



//删
//*num表示要删除的航班号
void airplane_del(pkernel_t p,char *num)
{
	//创建一个临时节点
	struct list_head *pos=(&p->list)->next,*temp;
	//创建一个临时变量node
	pkernel_t node;
	while(pos!=&p->list)
	{
		temp = pos->next;
		node=list_entry(pos, typeof(*p), list);
		if(!strcmp(node->data.number,num))
		{
			list_del(pos);
			printf("删除成功，删除的航班信息如下：\n");
			//打印单个信息
			airplane_print(node);	
			free(node);
		
		}
		pos=temp;
		
	}
	
}




//改
int airplane_updata(pkernel_t p)
{
	char number[18];
	printf("请输入要修改的航班号:");
	scanf("%s",number);
	printf("正在搜索是否有该航班号\n");
	int flag=0;
	//创建一个临时节点
	struct list_head *pos=(&p->list)->next,*temp;
	//创建一个临时变量node
	pkernel_t node;
	while(pos!=&p->list)
	{
		temp = pos->next;
		node=list_entry(pos, typeof(*p), list);
		if(!strcmp(node->data.number,number))
		{
			printf("搜索成功，搜索的航班信息如下：\n");
			//打印单个信息
			airplane_print(node);
			printf("请确认是否修改该航班信息(0不修改，非0修改):");
			int sure;
			scanf("%d",&sure);
			if(sure)
			{
				fly_t new_data;
				pkernel_t new_node;
				new_data = airplane_scanf();
				new_node = create_node(new_data);
				if(new_node == NULL)
					return -1;
				list_replace_init(&node->list,&new_node->list);
				free(node);
				printf("修改成功！\n");
			}
			flag++;
		}
		pos=temp;	
	}	
	if(flag==0)
	{
		printf("搜索失败，没有搜索到该航班信息！\n");
		return -1;
	}
	else
		return 0;	
	
	
}


//查
int airplane_search(pkernel_t p,char *num)
{
	
	int flag=0;
	//创建一个临时节点
	struct list_head *pos=(&p->list)->next,*temp;
	//创建一个临时变量node
	pkernel_t node;
	while(pos!=&p->list)
	{
		temp = pos->next;
		node=list_entry(pos, typeof(*p), list);
		if(!strcmp(node->data.number,num))
		{
			printf("查找成功，查找的航班信息如下：\n");
			//打印单个信息
			airplane_print(node);
			flag++;
		}
		pos=temp;	
	}	
	if(flag==0)
	{
		printf("查找失败，没有查找到该航班信息！\n");
		return -1;
	}
	else
		return 0;
	
}


//遍历
void airplane_display(pkernel_t p)
{
	pkernel_t node;
	struct list_head *pos;
	printf("以下是所有航班的信息：\n");
	list_for_each(pos, &p->list)
	{
		node = list_entry(pos,typeof(*p),list);
		//打印单个信息
		airplane_print(node);
	}
}

//航班系统提示头
void airplane_start(void)
{
	printf("-----------------------------\n");
	printf("------欢迎使用航班系统-------\n");
	printf("-----------------------------\n");
}

//航班内容输入
fly_t airplane_scanf_new(void)
{
	fly_t data;
	printf("--------------------\n");
	printf("正在创建新航班....\n");
	printf("--------------------\n");
	printf("新航班创建成功！\n");
	printf("--------------------\n");
	//航班内容输入
	data = airplane_scanf();
	return data;
}
//航班内容删除
void airplane_scanf_del(pkernel_t p)
{
	
	char number[18];
	printf("请输入要删除的航班号:");
	scanf("%s",number);
	//删
	//*num表示要删除的航班号
	airplane_del(p,number);

}

//航班内容查询
void airplane_scanf_search(pkernel_t p)
{
	
	char number[18];
	printf("请输入要查询的航班号:");
	scanf("%s",number);
	airplane_search(p,number);

}


//打印单个信息
void airplane_print(pkernel_t node)
{
		printf("*****************************\n");
		printf("航班号:%s\n",node->data.number);
		printf("起始站:%s\n",node->data.staddress);
		printf("终止站:%s\n",node->data.arraddress);
		printf("班期:%d年%d月%d日\n",node->data.DATE[0],node->data.DATE[1],node->data.DATE[2]);
		printf("机型:%s\n",node->data.TYPE);
		printf("起飞时间:%d:%d\n",node->data.stime/60,node->data.stime%60);
		printf("到达时间:%d:%d\n",node->data.atime/60,node->data.atime%60);
		printf("票价:%d元\n",node->data.value);
		printf("*****************************\n");
}

//航班内容输入
fly_t airplane_scanf(void)
{
	fly_t data;
	int hour,min;
	printf("请输入航班号(最多17位):");
	scanf("%s",data.number);
	printf("请输入起始站(最多17位):");
	scanf("%s",data.staddress);
	printf("请输入终点站(最多17位):");
	scanf("%s",data.arraddress);	
	printf("请输入班期(例如2021.12.28):");
	scanf("%d.%d.%d",&data.DATE[0],&data.DATE[1],&data.DATE[2]);
	printf("请输入机型(最多7位):");
	scanf("%s",data.TYPE);
	printf("请输入起飞时间(例如9:30):");
	scanf("%d:%d",&hour,&min);
	data.stime = hour*60+min;
	printf("请输入到达时间(例如9:30):");
	scanf("%d:%d",&hour,&min);
	data.atime = hour*60+min;
	printf("请输入票价(整数):");
	scanf("%d",&data.value);	
	return data;
}

//排序
void  airplane_resort(pkernel_t p)
{
	pkernel_t node;
	pkernel_t head_node;
	struct list_head *head=(&p->list);
	struct list_head *pp=(&p->list)->next;
	struct list_head *pos=(&p->list)->next;

	INIT_LIST_HEAD(head);
	
	while(pos!=head)
	{
		pp = pos->next;
		node = list_entry(pos, typeof(*p), list);
		while(head->next!=head)
		{
			head_node = list_entry(head->next, typeof(*p), list);
			
						//刚输入的起飞日期如果小于存储中的某个值得话，那么就头擦
			if(head_node->data.DATE[0]>node->data.DATE[0])
				break;
			else if(head_node->data.DATE[0]==node->data.DATE[0])
			{
				if(head_node->data.DATE[1]>node->data.DATE[1])
				{
					break;
				}
				else if(head_node->data.DATE[1]==node->data.DATE[1])
				{
					if(head_node->data.DATE[2]>node->data.DATE[2])
					{
						break;
					}
					else if(head_node->data.DATE[2]==node->data.DATE[2])
					{
						if(head_node->data.stime>node->data.stime)
						{
							break;
						}
					}
				}
			}
			
			
			head = head->next;
		}
		//头插
		list_add(&node->list,head);
		head=(&p->list);
		pos=pp;
	}
	printf("排序成功\n");
}

