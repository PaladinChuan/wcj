#include "net.h"
#include "print.h"
struct clientinfo cli_info[CLIENT_MAC_SIZE];
struct data	cli_data[CLIENT_MAC_SIZE];

void * cli_group(void* arg);

sqlite3 *db;						//数据库
int usr_num = 0 ;						//有多少个用户连接了

//服务器初始化
int net_init(void) 
{
	struct sockaddr_in sin;
	int srv_fd;
	//1、创建套接字
	srv_fd = socket(AF_INET,SOCK_STREAM,0);
    if(srv_fd <0){
	perror("socket");
	exit(1);
    }
	
    int on = 1;
    setsockopt(srv_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));	

	//初始化本地地址
    bzero(&sin,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = INADDR_ANY;  //让系统自动识别有效的网卡IP	
	
	//2、绑定
    if(bind(srv_fd,(struct sockaddr *)&sin,sizeof(sin)) < 0){
	perror("bind");
	exit(1);
    }	
	
	//3、监听
    if(listen(srv_fd,MAX_LOG) < 0){
	perror("listen");
	exit(1);
    }	
	
	//5、返回ID
	return srv_fd;
	
}



int main(void)
{
	int srv_fd;							//服务器文件描述符
	int conn_fd;						//客户端文件描述符
	struct clientinfo cli;				//客户端的临时连接信息
	struct sockaddr_in cli_addr;		//客户端的临时连接地址
	char *ip;							//客户端的IP地址
	int i;								//变量
	pthread_t tid;						//线程tid

	char sql3_param_buf[200];			//数据库参数缓存
	char sql3_cmd_buf[100];				//数据库命令缓存

	srand((long)time(NULL));			//随机数生成初始化

	//网络初始化
	srv_fd = net_init();
	
	//初始化客户信息
    bzero(cli_info,sizeof(cli_info));

    //打开数据库文件
    if(sqlite3_open("friend.db",&db) != SQLITE_OK){     //打开数据库
	perror("sqlite3_open");
	exit(1);
    }
	
	
	//先将QQ列表里面的QQ号的文件描述符全部改为999
	//先注册qq列表 账号qq_num、密码qq_passwd、昵称qq_name、性别qq_sex、密保问题qq_safe_q、密保答案qq_safe_a 在线文件描述符user_fd
	bzero(sql3_param_buf,sizeof(sql3_param_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
	sprintf(sql3_param_buf,"(qq_num char(20),qq_passwd char(20),qq_name char(20),qq_sex int,qq_safe_q int,qq_safe_a char(20),user_fd int)");	//转成字符串存入
					
	bzero(sql3_cmd_buf,sizeof(sql3_cmd_buf));		//table名称
	sprintf(sql3_cmd_buf,"qq_list");				//转成字符串存入
	sql3_add(db,sql3_cmd_buf,sql3_param_buf,4);			//创建table表			
	
	//然后将所有的QQ号的文件描述符改为999
	bzero(sql3_cmd_buf,sizeof(sql3_cmd_buf));
	sprintf(sql3_cmd_buf,"user_fd=999 where user_fd!=999");  //
	printf("%s\n",sql3_cmd_buf);					//打印：为了测试，可注释掉
	sql3_add(db,"qq_list",sql3_cmd_buf,3);		//往数据库里面的qq号列表的用户标识符修改为当前的用户标识符		


	while(1){
		printf("等待客户端连接中....\n");
		//4、接收连接请求  地址传回来  客户端文件描述符传回来
		socklen_t len = sizeof(cli_addr);
		conn_fd = accept(srv_fd,(struct sockaddr*)&cli_addr,&len);
		if(conn_fd < 0){
			perror("accept");
			exit(1);
		}
	//保存客户端信息
	cli.cli_fd = conn_fd;
	cli.cli_addr = cli_addr;
	cli.usr_num = usr_num++;
		
	//打印客户端IP
	ip = inet_ntoa(cli_addr.sin_addr);
	printf("%s上线了\n",ip);
			
	//创建线程进行登陆、注册和找回
	
	
	
	//创建线程进行加人、单聊
	
	
	
	
	//创建线程进行创建群、拉人、或者群聊
	if(pthread_create(&tid,NULL,cli_group,&cli)){
	    perror("pthread_create");
	    exit(1);
	}	
	pthread_detach(tid);	
	
			
	}
	
    //6,断开连接
    close(srv_fd);
	
	return 0;
}

//
void *cli_group(void* arg)
{
    struct clientinfo *cli_pinfo = (struct clientinfo*)arg;
    int conn_fd;
    int ret;	
	char buf[SIZE];
	int conn_num;			//连接第几个用户
	long temp_num;
	char temp_group_num[100];
	char temp_group_name[100];
	char sql3_buf[200];					//临时字符串（用于生成sql字符串命令）
    
	conn_fd = cli_pinfo->cli_fd;
	conn_num = cli_pinfo->usr_num;
#if 1	
	while(1)
	{
	//解析JSON
	//调用JSON解包内容
		bzero(buf,sizeof(buf));
		if((ret = read(conn_fd,buf,sizeof(buf))) < 0){
			perror("read");
			exit(1);
		}else if(!ret)
			;
		else{
		if(!strncmp(buf,"over",4)){
			printf(RED"===========================\n"NONE);
			;
		}
		json_unlock(buf,&cli_data[conn_num]);
		//printf(BLUE"%s\n"NONE,buf);
					
					
		printf(RED"----------------------------\n"NONE);
		}

	
	//解析判断 0  登陆
		//第一步，获取账号密码 与数据库比对
		//strcat  
		//exec callback get_table
		//strcpy 
		//sprintf
		
	if(cli_data[conn_num].cmd == 1)	//登录
	{
		int ret;
		char temp_passwd_buf[20];
		//正在验证账号密码
		printf("正在验证账号密码...\n");
		bzero(temp_passwd_buf,sizeof(temp_passwd_buf));
		ret = search_same_str_change_name(db,"select * from  qq_list","qq_num",cli_data[conn_num].qq_num,temp_passwd_buf);	
		if(ret == -1)
		{
			//说明找到QQ号了
			if(!strcmp(temp_passwd_buf,cli_data[conn_num].qq_passwd))
			{
				//成功匹配到了密码 //这时候需要把用户标识符修改为当前的用户标识符
				bzero(sql3_buf,sizeof(sql3_buf));
				sprintf(sql3_buf,"user_fd='%d' where qq_num='%s'",conn_fd,cli_data[conn_num].qq_num);  //
				printf("%s\n",sql3_buf);					//打印：为了测试，可注释掉
				sql3_add(db,"qq_list",sql3_buf,3);		//往数据库里面的qq号列表的用户标识符修改为当前的用户标识符				
				
				//返回成功
				cli_data[conn_num].cmd = 2;				//qq登录返回命令
				cli_data[conn_num].group_flag = 1;		//qq登陆成功标志
				
				bzero(buf,sizeof(buf));
				json_lock(buf,&cli_data[conn_num]);		//打包
				//发回给用户	
				if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
				}	
			}
			else 
			{
				//返回失败
				cli_data[conn_num].cmd = 2;				//qq登录返回命令
				cli_data[conn_num].group_flag = 0;		//qq登陆失败标志
				
				bzero(buf,sizeof(buf));
				json_lock(buf,&cli_data[conn_num]);		//打包
				//发回给用户	
				if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
				}					
				
			}
			
		}
		else 
		{
				//返回失败
				cli_data[conn_num].cmd = 2;				//qq登录返回命令
				cli_data[conn_num].group_flag = 0;		//qq登陆失败标志
				
				bzero(buf,sizeof(buf));
				json_lock(buf,&cli_data[conn_num]);		//打包
				//发回给用户	
				if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
				}				
			
		}
		
	}
		//第二步  返回比对结果，成功就将数据库的用户标识符设置为当前用户标识符 失败就不动
		
		
		//解析判断 注册
		//第一步、生成随机数的账号，判断数据库的QQ列表是否有相同的随机数，没有就注册数据库，有就重新生成随机数的账号
		//srand((long)time(NULL));			//随机数生成初始化
		//temp_num = (long)rand();
		//strcat 
		//exec callback get_table
		//strcpy 
		//第二步、注册数据库，账号qq_num、密码qq_passwd、昵称qq_name、性别qq_sex、密保问题qq_safe_q、密保答案qq_safe_a 在线文件描述符user_fd
		//exec callback get_table
		if(cli_data[conn_num].cmd == 3)	//注册
		{	
			//正在注册新账号中
			printf("正在注册新账号中...\n");
			while(1)
			{
				int ret =0;
				temp_num = (long)rand();
				bzero(temp_group_num,sizeof(temp_group_num));
				printf("QQ号为%ld\n",temp_num);
				sprintf(temp_group_num,"%ld",temp_num);
				printf("%s\n",temp_group_num);
				//读取数据库文件
				ret = search_same_str(db,"select * from  qq_list","qq_num",temp_group_num);
				if(ret == 0)
				{
					printf("%s\n",temp_group_num);
					
					strcpy(cli_data[conn_num].qq_num,temp_group_num);//将qq号输入
					
					
					//将QQ列表的数据库里面增加QQ(qq_num char(20),qq_passwd char(20),qq_name char(20),qq_sex int,qq_safe_q int,qq_safe_a char(20),user_fd int)					
					bzero(sql3_buf,sizeof(sql3_buf));
					sprintf(sql3_buf,"('%s','%s','%s','%d','%d','%s','%d')",cli_data[conn_num].qq_num,\
																			cli_data[conn_num].qq_passwd,\
																			cli_data[conn_num].qq_name,\
																			cli_data[conn_num].qq_sex,\
																			cli_data[conn_num].qq_safe_q,\
																			cli_data[conn_num].qq_safe_a,\
																			999);  //
					printf("%s\n",sql3_buf);					//打印：为了测试，可注释掉
					sql3_add(db,"qq_list",sql3_buf,1);		//往数据库里面的群聊列表组添加群聊号和名称
					

					//创建用户的好友列表
					bzero(sql3_buf,sizeof(sql3_buf));  				//
					sprintf(sql3_buf,"(qq_num char(20),qq_name char(20))");	//转成字符串存入
					
					bzero(temp_group_name,sizeof(temp_group_name));		//table名称
					sprintf(temp_group_name,"qf_%s",cli_data[conn_num].qq_num);	//转成字符串存入
					sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表	
									
					//创建用户的群聊列表
					bzero(sql3_buf,sizeof(sql3_buf));  				//
					sprintf(sql3_buf,"(group_num char(20),group_name char(20))");	//转成字符串存入
					
					bzero(temp_group_name,sizeof(temp_group_name));		//table名称
					sprintf(temp_group_name,"qg_%s",cli_data[conn_num].qq_num);	//转成字符串存入
					sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表				
					
					
					//然后将群号返回给用户
					cli_data[conn_num].cmd = 4;			//qq号建立返回命令
					cli_data[conn_num].group_flag = 1;		//qq号建立成功标志
					bzero(buf,sizeof(buf));
					json_lock(buf,&cli_data[conn_num]);		//打包
					 //发回给用户	
					if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
					}	
					printf("@@@@@@@@@@@@@@@@\n");
					break;	
				}
				if(ret == -1)
					printf("有相同的qq号，正在重新生成。\n");
				sleep(1);
			}
			
			printf("成功创建\n");		
		
		}
		//解析判断 找回密码
		//第一步、从数据库找到账号，然后匹配密保答案
		//strcat 
		//exec callback get_table
		//strcpy 
		//第二步、成功修改新密码、失败就不动，返回信息
		//strcat 
		//exec callback get_table
		//strcpy 
		
		if(cli_data[conn_num].cmd == 5)
		{		
				//正在找回密码中...
				printf("正在找回密码中.....\n");
		
		}

		
		
		

		

	//解析判断  加好友
	//1、判断命令
	//2、拿到QQ号，然后再数据库QQ_LIST查找是否有该QQ号
	//3、有的话，那么在自身的QQ号列表（qf_123）下加入该QQ号,并且在对方的QQ号列表也加入请求人的号码
	///////////////////////4、还得创建一个单聊空间
	//5、返回
	
	
	
	
	//解析判断 查看好友列表
	//1、提取数据库好友列表
	//2、返回

	
	//解析判断 单聊
	//1、判断该好友QQ号是否在该QQ号的数据库好友列表
	//2、查看是否在线，返回数据，同时要给好友发消息
	//////////////3、如果不在线，数据存入单聊空间
	
	
	//解析判断1、创建群聊
			//第一步：生成随机数
			//第二步：寻找是否有同样的随机数，如果有，那么再次生成随机数
			//第三步：生成数据库内容
					//3.1 创建一个数据库的群聊空间
					//3.2 在用户账号的列表下面加入群聊号
					//3.3 创建一个群聊列表并将该群聊号码和名称加入，方便查询
					
			//第四步：返回创建群聊成功信息，并返回群聊号码和群聊名称
	if(cli_data[conn_num].cmd == 30)
	{
			printf("正在生成群号\n");
			while(1)
			{
				int ret =0;
				temp_num = (long)rand();
				bzero(temp_group_num,sizeof(temp_group_num));
				printf("群号为%ld\n",temp_num);
				sprintf(temp_group_num,"%ld",temp_num);
				printf("%s\n",temp_group_num);
				//读取数据库文件
				ret = search_same_str(db,"select * from  group_list","group_num",temp_group_num);
				if(ret == 0)
				{
					printf("%s\n",temp_group_num);
					
					strcpy(cli_data[conn_num].group_num,temp_group_num);//将群号输入
					
					
					//建立群聊列表并增加
					bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
					sprintf(sql3_buf,"(group_num char(20),group_name char(20))");	//转成字符串存入
					
					bzero(temp_group_name,sizeof(temp_group_name));		//table名称
					sprintf(temp_group_name,"group_list");				//转成字符串存入
					sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表					
					
					
					bzero(sql3_buf,sizeof(sql3_buf));
					sprintf(sql3_buf,"('%s','%s')",cli_data[conn_num].group_num,cli_data[conn_num].group_name);  //
					printf("%s\n",sql3_buf);					//打印：为了测试，可注释掉
					sql3_add(db,"group_list",sql3_buf,1);		//往数据库里面的群聊列表组添加群聊号和名称
					
					//建立群内聊天数据库和群成员数据库
					//建立群成员数据库
					bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
					sprintf(sql3_buf,"(qq_num char(20),power int)");	//转成字符串存入
					
					bzero(temp_group_name,sizeof(temp_group_name));		//table名称
					sprintf(temp_group_name,"gn_%s",cli_data[conn_num].group_num);	//转成字符串存入
					sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表
					
					bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
					sprintf(sql3_buf,"('%s','%d')",cli_data[conn_num].qq_num,0);		//转成字符串存入					
					
					sql3_add(db,temp_group_name,sql3_buf,1);			//往刚创建的表里面添加群主
					//在数据库里面的添加群聊空间
					bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
					sprintf(sql3_buf,"(qq_num char(10),message char(100))");	//转成字符串存入
					
					bzero(temp_group_name,sizeof(temp_group_name));		//table名称
					sprintf(temp_group_name,"gs_%s",cli_data[conn_num].group_num);	//转成字符串存入
					sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表
									
					//在用户列表下面增加群聊列表
					bzero(sql3_buf,sizeof(sql3_buf));  				//
					sprintf(sql3_buf,"(group_num char(20),group_name char(20))");	//转成字符串存入
					
					bzero(temp_group_name,sizeof(temp_group_name));		//table名称
					sprintf(temp_group_name,"qg_%s",cli_data[conn_num].qq_num);	//转成字符串存入
					sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表

					
					bzero(sql3_buf,sizeof(sql3_buf));  				//
					sprintf(sql3_buf,"('%s','%s')",cli_data[conn_num].group_num,cli_data[conn_num].group_name);		//转成字符串存入					
					
					sql3_add(db,temp_group_name,sql3_buf,1);			//往刚创建的表里面添加群主				
					
					
					//然后将群号返回给用户
					cli_data[conn_num].cmd = 31;			//群聊返回命令
					cli_data[conn_num].group_flag = 1;		//群聊建立成功标志
					strcpy(cli_data[conn_num].group_num,temp_group_num);//将群号输入
					bzero(buf,sizeof(buf));
					json_lock(buf,&cli_data[conn_num]);		//打包
					 //发回给用户	
					if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
					}	
					printf("@@@@@@@@@@@@@@@@\n");
					break;	
				}
				if(ret == -1)
					printf("有相同的群聊，正在重新生成。\n");
				sleep(1);
			}
			
			printf("成功创建\n");
	}

			
	//解析判断2、加入群聊
			//第一步：寻找数据库的该用户下是否有该同样的群聊
			
			//第二步：寻找数据库的群聊列表里面是否有该数据
			
			//第三步：若通过数字查找，直接返回正确错误，若通过昵称查找，确定是否有多个，有多个话，返回多个数据，请求其选择或取消
	if(cli_data[conn_num].cmd == 32)
	{
		int ret;
		printf("正在寻找群号\n");
		//读取数据库文件
		ret = search_same_str_change_name(db,"select * from  group_list","group_num",cli_data[conn_num].group_num,cli_data[conn_num].group_name);		
		if(ret == -1)
		{
			//说明找到群号了
			//群里增加该QQ号
			bzero(temp_group_name,sizeof(temp_group_name));		//table名称
			sprintf(temp_group_name,"gn_%s",cli_data[conn_num].group_num);	//转成字符串存入
			
			bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
			sprintf(sql3_buf,"('%s','%d')",cli_data[conn_num].qq_num,2);		//转成字符串存入					
					
			sql3_add(db,temp_group_name,sql3_buf,1);			//往刚创建的表里面添加群员		
			
			
			//在用户列表下面增加群聊列表
			bzero(sql3_buf,sizeof(sql3_buf));  				// 在用户的群列表增加用户的群
			sprintf(sql3_buf,"(group_num char(20),group_name char(20))");	//转成字符串存入
					
			bzero(temp_group_name,sizeof(temp_group_name));		//table名称
			sprintf(temp_group_name,"qg_%s",cli_data[conn_num].qq_num);	//转成字符串存入
			sql3_add(db,temp_group_name,sql3_buf,4);			//创建table表

					
			bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
			sprintf(sql3_buf,"('%s','%s')",cli_data[conn_num].group_num,cli_data[conn_num].group_name);		//转成字符串存入					
					
			sql3_add(db,temp_group_name,sql3_buf,1);			//往刚创建的表里面添加群主	
			
			
			//成功返回
			cli_data[conn_num].cmd = 34;			//群聊返回命令
			cli_data[conn_num].group_flag = 1;		//群聊建立成功标志
			bzero(buf,sizeof(buf));
			json_lock(buf,&cli_data[conn_num]);		//打包
			 //发回给用户	
			if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
			}	
		}
		else
		{
			cli_data[conn_num].cmd = 34;			//群聊返回命令
			cli_data[conn_num].group_flag = 0;		//群聊进入失败标志
			bzero(buf,sizeof(buf));
			json_lock(buf,&cli_data[conn_num]);		//打包
			 //发回给用户	
			if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
			}				
		}
	}		
	
	//解析判断3、进行群聊
			//第一步：建立一个群聊信息数据库，并将里面的群聊信息发送给该用户
			
			//第二步：接收群聊信息，并将群聊信息加载到群聊信息数据库
	if(cli_data[conn_num].cmd == 35)
	{
		//正在进入群聊
		printf("正在寻找是否有该群\n");
		//读取数据库文件
		bzero(temp_group_name,sizeof(temp_group_name));		//table名称
		sprintf(temp_group_name,"select * from qg_%s",cli_data[conn_num].qq_num);	//转成字符串存入
		ret = search_same_str_change_name(db,temp_group_name,"group_num",cli_data[conn_num].group_num,cli_data[conn_num].group_name);		
		if(ret == -1)
		{
			//找到群聊了
			printf("已找到用户下面的群聊\n");
			
			//向群聊空间发送自己的群聊信息
			bzero(temp_group_name,sizeof(temp_group_name));		//table名称
			sprintf(temp_group_name,"gs_%s",cli_data[conn_num].group_num);	//转成字符串存入
			
			bzero(sql3_buf,sizeof(sql3_buf));  				//群参数（qq_num,power） //power权限为0为群主 1为管理员 2为群员
			sprintf(sql3_buf,"('%s','%s')",cli_data[conn_num].qq_num,cli_data[conn_num].group_message);		//转成字符串存入			
			
			sql3_add(db,temp_group_name,sql3_buf,1); //往群聊表里添加群聊信息	
	
			
			//将群内消息返回
			
			
			//群播，对所有群用户进行群播
			//先找到所有群用户，然后找到注册的列表中该用户的状态，如果上线，直接发送数据。
			
			
			
			//成功返回
			cli_data[conn_num].cmd = 36;			//群聊返回命令
			cli_data[conn_num].group_flag = 1;		//群聊建立成功标志
			bzero(buf,sizeof(buf));
			json_lock(buf,&cli_data[conn_num]);		//打包
			 //发回给用户	
			if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
			}				
		}
		else
		{
			cli_data[conn_num].cmd = 36;			//群聊返回命令
			cli_data[conn_num].group_flag = 0;		//群聊进入失败标志
			bzero(buf,sizeof(buf));
			json_lock(buf,&cli_data[conn_num]);		//打包
			 //发回给用户	
			if(write(conn_fd,buf,strlen(buf)) < 0){
						perror("write");
						exit(1);
			}				
		}
		
	}		
			
			
	}
#else
	//测试程序
	while(1)
	{
		bzero(buf,sizeof(buf));
		if((ret = read(conn_fd,buf,sizeof(buf))) < 0){
			perror("read");
			exit(1);
		}else if(!ret)
			break;
		else{
			if(!strncmp(buf,"over",4)){
			printf(RED"===========================\n"NONE);
			break;
			}
			printf(BLUE"%s\n"NONE,buf);
			printf(RED"----------------------------\n"NONE);
		}

        //发送文件名给服务器	
		if(write(conn_fd,buf,strlen(buf)) < 0){
			perror("write");
			exit(1);
		}		
		
		
	}
	
#endif

    pthread_exit(0);
}
