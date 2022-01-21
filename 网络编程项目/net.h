#ifndef __NET_H__
#define	__NET_H__
//头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#include </usr/local/include/json/json.h>
#include <stdbool.h>

#include <sqlite3.h>

//数据结构体 ----群聊
struct data{
	int cmd;							//命令 30为建群    31为建群后返回群号  32为号码加群    33为昵称加群  34为加群回复信息   35为发送群信息  36为发群信息返回

//
	char qq_name[20];						//昵称
	char qq_num[20];						//qq号
	char qq_passwd[20];						//qq密码
	int  qq_sex;							//qq性别
	int  qq_state;							//qq状态
	int  qq_safe_q;							//qq安全问题
	char qq_safe_a[20];						//qq安全答案
	
	char group_name[20];					//群名称
	char group_num[20];						//群号码
	char return_group_num_buf[10][10];		//群列表
	char group_message[100];				//群信息
	int  group_flag;						//群标志
};

#define CLIENT_MAC_SIZE 100
struct clientinfo{
    pthread_t tid;							//进程tid
    int cli_fd;								//客服端的fd
    struct sockaddr_in cli_addr;			//客户端地址
	unsigned long account_number;			//账号
	int usr_num;							//用户号码
};


#define MAX_LOG 8
#define PORT  5678
#define SIZE 1024


extern void json_lock(char *str,struct data *dt);
extern void json_unlock(char *str,struct data *dt);

extern int search_same_str(sqlite3* db,char *sql,char *str,char *data);
extern int search_same_str_change_name(sqlite3* db,char *sql,char *str,char *data,char *name);

extern void sql3_add(sqlite3* db,char *name,char *str,int cmd);


#endif



