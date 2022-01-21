#include "net.h"



//寻找str相同的名称下的是否相同的data字符串
int search_same_str(sqlite3* db,char *sql,char *str,char *data)
{
    char * errmsg;
    //查询数据库的stu表中所有信息
    char **retp;
    int nrow,ncolumn;
	long temp;

    if(sqlite3_get_table(db,sql,&retp,&nrow,&ncolumn,&errmsg) != SQLITE_OK){
	printf("error:%s\n",errmsg);
	exit(1);
    }
	printf("ncolumn=%d,nrow =%d\n",ncolumn,nrow);
	//如果没有数据，直接返回0
	if(ncolumn == 0 && nrow == 0)
		return 0;
    //扫描是否有匹配的
    int i,j;

	for(i = 0; i < ncolumn;i++)
	{
		printf("%s\n",retp[i]);			//打印操作内容，方便调试
		//是否有匹配的头
		if(!strcmp(retp[i],str))
			break;
	}
	if(i != ncolumn)	//没有超出范围
		for(j = 1;j < nrow+1;j++)
		{
			printf("%s\n",retp[j*ncolumn + i]);  //打印操作内容，方便调试
			//是否有相同的数据
			if(!strcmp(retp[j*ncolumn + i],data))
				return -1;
		}
	else				//没有检测到相同的头
		return 1;
	
	return 0;
}


//寻找str相同的名称下的是否相同的data字符串
int search_same_str_change_name(sqlite3* db,char *sql,char *str,char *data,char *name)
{
    char * errmsg;
    //查询数据库的stu表中所有信息
    char **retp;
    int nrow,ncolumn;
	long temp;

    if(sqlite3_get_table(db,sql,&retp,&nrow,&ncolumn,&errmsg) != SQLITE_OK){
	printf("error:%s\n",errmsg);
	exit(1);
    }
	printf("ncolumn=%d,nrow =%d\n",ncolumn,nrow);
	//如果没有数据，直接返回0
	if(ncolumn == 0 && nrow == 0)
		return 0;
    //扫描是否有匹配的
    int i,j;

	for(i = 0; i < ncolumn;i++)
	{
		printf("%s\n",retp[i]);			//打印操作内容，方便调试
		//是否有匹配的头
		if(!strcmp(retp[i],str))
			break;
	}
	if(i != ncolumn)	//没有超出范围
		for(j = 1;j < nrow+1;j++)
		{
			printf("%s\n",retp[j*ncolumn + i]);  //打印操作内容，方便调试
			//是否有相同的数据
			if(!strcmp(retp[j*ncolumn + i],data))
			{
				strcpy(name,retp[j*ncolumn + i+1]);
				return -1;
			}
		}
	else				//没有检测到相同的头
		return 1;
	
	return 0;
}

//数据库增加、删除、修改、创建
//cmd=1为增加 cmd=2为删除 cmd=3为修改 cmd=4为创建
void sql3_add(sqlite3* db,char *name,char *str,int cmd)
{
    char * errmsg;
	if(cmd == 1)
	{
		//增加数据库
		char sql_operate[100]={0};
		strcpy(sql_operate,"insert into ");
		strcat(sql_operate,name);
		strcat(sql_operate," values");
		strcat(sql_operate,str);
		
		printf("%s\n",sql_operate);
		if(sqlite3_exec(db,sql_operate,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("error:%s\n",errmsg);
		exit(1);
		}		
	}
	
	
	if(cmd == 3)
	{
		//修改命令
		char sql_operate[100]={0};
		strcpy(sql_operate,"update ");
		strcat(sql_operate,name);
		strcat(sql_operate," set ");
		strcat(sql_operate,str);
		
		printf("%s\n",sql_operate);
		if(sqlite3_exec(db,sql_operate,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("error:%s\n",errmsg);
		exit(1);
		}			
	}
	
	if(cmd == 4)
	{
		//创建数据库
		char sql_operate[200]={0};
		//create table stu(sno int,name char(10), age int, score float);
		strcpy(sql_operate,"create table  if not exists ");
		strcat(sql_operate,name);
		strcat(sql_operate,str);
		
		printf("%s\n",sql_operate);
		if(sqlite3_exec(db,sql_operate,NULL,NULL,&errmsg) != SQLITE_OK){
			
			printf("error:%s\n",errmsg);
			exit(1);
		}			
	}
	
}

