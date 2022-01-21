#include "net.h"
#include "print.h"
struct data	cli_data;
int main(int argc,char *argv[])
{
    int srv_fd;
    struct sockaddr_in sin;
    char buf[SIZE];
    int ret;
	

	//绑定服务器
    if(argc!=2){
	fprintf(stderr,"Usage :%s <ip>\n",argv[0]);
	exit(1);
    }

    //1,创建套接字
    srv_fd = socket(AF_INET,SOCK_STREAM,0);
    if(srv_fd <0){
	perror("socket");
	exit(1);
    }

    //初始化本地地址
    bzero(&sin,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    //sin.sin_addr.s_addr = inet_addr("192.168.30.5");
    sin.sin_addr.s_addr = inet_addr(argv[1]);

    
    //2,发送连接请求
    if(connect(srv_fd,(struct sockaddr*)&sin,sizeof(sin)) < 0){
	perror("accept");
	exit(1);
    }

    //3,与服务器通信
   
   
    printf("/---------QQNQ聊天客户端---------/\n");
    printf(RED"===========================\n"NONE);

		//一、选项登陆 注册 找回 退出
		
	int login_flag = 0;
	while(1){
		int cmd_i;
		printf("1、登录\n");
		printf("2、注册\n");
		printf("3、找回\n");
		printf("4、退出\n");
		printf("请输入命令\n");
		scanf("%d",&cmd_i);
		switch(cmd_i){
			case 1:			//登录
				//登陆
				//1、登陆CMD命令
				//2、输入账号密码
				//3、等待返回 返回成功，跳出while
				//4、失败，就提示，然后继续循环
				printf("请输入登录账号:\n");
				scanf("%s",cli_data.qq_num);
				printf("请输入登录密码:\n");
				scanf("%s",cli_data.qq_passwd);		
				cli_data.cmd = 1;	//登陆
				bzero(buf,sizeof(buf));
				json_lock(buf,&cli_data);
				
				if(write(srv_fd,buf,strlen(buf)) < 0){
							perror("write");
							exit(1);
				}			
				
				if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
					perror("read");
					exit(1);
				}
				
				json_unlock(buf,&cli_data);	//JSON解包
				if(cli_data.cmd == 2 && cli_data.group_flag == 1)
				{
					//
					login_flag = 1;	
					printf("登录成功！\n");
					printf("欢迎使用QQNQ客户端\n");
				}
				else
				{
					printf("登录失败！\n");
					
				}
					
				
			break;
			
			case 2:			//注册
				//注册
				//1、注册CMD命令
				//2、输入昵称 性别 密码 密保问题 密保答案
				//3、等待返回	
				cli_data.cmd = 3;	//注册
				printf("请输入注册名称:\n");
				scanf("%s",cli_data.qq_name);
				printf("请输入注册性别（0为女 1为男）:\n");
				scanf("%d",&cli_data.qq_sex);	
				printf("请输入注册密码：\n");
				scanf("%s",cli_data.qq_passwd);
				printf("密保问题1：你的理想是什么？\n");
				printf("密保问题2：你的小学叫什么？\n");
				printf("密保问题3：你的家乡叫什么？\n");
				printf("请输入你要选择的密保问题（1或2或3）");
				scanf("%d",&cli_data.qq_safe_q);
				printf("请输入你的密保问题答案");
				scanf("%s",cli_data.qq_safe_a);

				printf("正在注册账户中，请稍后.....\n");
				
				bzero(buf,sizeof(buf));
				json_lock(buf,&cli_data);
				
				if(write(srv_fd,buf,strlen(buf)) < 0){
							perror("write");
							exit(1);
				}			
				
				if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
					perror("read");
					exit(1);
				}
				
				json_unlock(buf,&cli_data);	//JSON解包
				if(cli_data.cmd == 4 && cli_data.group_flag == 1)
				{
					//
					printf("注册成功！\n");
					printf("您注册的账号为%s,请牢记你的账号\n",cli_data.qq_num);
				}
				else
				{
					printf("注册失败！\n");
					
				}				

					
			break;
			
			case 3:			//找回
				//找回密码
				//1、找回CMD命令
				//2、输入账号、密保答案 输入新密码
				//3、等待返回		
				cli_data.cmd = 5;	//找回
				printf("请输入找回账号:\n");
				scanf("%s",cli_data.qq_num);
				printf("密保问题1：你的理想是什么？\n");
				printf("密保问题2：你的小学叫什么？\n");
				printf("密保问题3：你的家乡叫什么？\n");
				printf("请输入你要选择的密保问题（1或2或3）");
				scanf("%d",&cli_data.qq_safe_q);
				printf("请输入你的密保问题答案");
				scanf("%s",cli_data.qq_safe_a);
				printf("请输入新密码：\n");
				scanf("%s",cli_data.qq_passwd);
				
				printf("正在找回账户中，请稍后.....\n");
				
				bzero(buf,sizeof(buf));
				json_lock(buf,&cli_data);
				
				if(write(srv_fd,buf,strlen(buf)) < 0){
							perror("write");
							exit(1);
				}			
				
				if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
					perror("read");
					exit(1);
				}
				
				json_unlock(buf,&cli_data);	//JSON解包
				if(cli_data.cmd == 6 && cli_data.group_flag == 1)
				{
					//
					printf("找回成功！\n");
					printf("密码重新设置成功，请牢记你的密码\n");
				}
				else
				{
					printf("找回失败，您填入的信息有误！\n");
					
				}				
			break;
			
			case 4:			//退出
				goto end;
			break;
			
			
		}

	

		

		


	
		
		sleep(1);
		//根据登陆 注册 找回的选项执行函数
		if(login_flag == 1)
			break;
		
	}
	
	printf("登陆成功\n");

    while(1){
		int cmd = 0;
#if 1
		//二、选择单聊、加好友、群聊、加群等等
		 //选择单聊，群聊等功能
		//加好友
		//1、加好友CMD命令
		//2、输入你要加的好友号
		//3、打包发送
		//4、等待返回 
		
		
		//查看好友列表
		//1、查看好友列表CMD命令
		//2、打包发送
		//3、等待返回
		
		//单聊
		//1、单聊CMD命令
		//2、输入好友号码
		//3、输入你要发送信息
		//4、等待返回
		//5、成功（好友在线）的话，开一个线程，接收好友消息 
		//6、是否退出聊天，不退出的话，你那么要循环执行3
		
		
		//选择建群
		printf("4、查看群列表\n");
		printf("3、向群发送信息\n");
		printf("2、添加群聊\n");
		printf("1、创建群聊\n");
		printf("0、退出客服端\n");
		printf("请选择命令：\n");
		scanf("%d",&cmd);
		
		if(cmd == 1)
		{
			printf("请输入你想要创建群聊的名称：\n");
			scanf("%s",cli_data.group_name);
			printf("正在创建中，请稍等.....\n");
			cli_data.cmd = 30;			//创建群聊命令
			bzero(buf,sizeof(buf));		//清零
			
			json_lock(buf,&cli_data);	//JSON分包
			if(write(srv_fd,buf,strlen(buf)) < 0){	//发送
						perror("write");
						exit(1);
			}
			bzero(buf,sizeof(buf));
			if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
				perror("read");
				exit(1);
			}
			json_unlock(buf,&cli_data);	//JSON解包
			if(cli_data.cmd == 31 && cli_data.group_flag == 1)
			{
				//
				printf("建群成功！\n");
				printf("群号为：%s,群名称为:%s\n",cli_data.group_num,cli_data.group_name);
				
			}
					
		}
		//选择寻找并加群
		else if(cmd == 2)
		{
			printf("请输入你想要加入群聊的号码：\n");
			scanf("%s",cli_data.group_num);
			printf("正在查找中，请稍等.....\n");
			cli_data.cmd = 32;			//通过号码加群
			bzero(buf,sizeof(buf));		//清零
			
			json_lock(buf,&cli_data);	//JSON分包
			if(write(srv_fd,buf,strlen(buf)) < 0){	//发送
						perror("write");
						exit(1);
			}
			bzero(buf,sizeof(buf));
			if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
				perror("read");
				exit(1);
			}			
			json_unlock(buf,&cli_data);	//JSON解包
			if(cli_data.cmd == 34 )
			{
				if(cli_data.group_flag == 1)
				{
					printf("进群成功！\n");
					printf("群号为：%s,群名称为:%s\n",cli_data.group_num,cli_data.group_name);
				}
				else
				{
					printf("搜索群失败\n");
				}
				
			}
		}
		else if(cmd == 3)
		{
				printf("请输入你想要进入群聊的号码：\n");			
				scanf("%s",cli_data.group_num);
				printf("请输入你要发送的群聊信息\n");
				scanf("%s",cli_data.group_message);
				printf("正在发送中，请稍等.....\n");
				cli_data.cmd = 35;			//向群发送信息
				bzero(buf,sizeof(buf));		//清零
			
				json_lock(buf,&cli_data);	//JSON分包
				if(write(srv_fd,buf,strlen(buf)) < 0){	//发送
							perror("write");
							exit(1);
				}
				bzero(buf,sizeof(buf));
				if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
					perror("read");
					exit(1);
				}			
				json_unlock(buf,&cli_data);	//JSON解包			
				if(cli_data.cmd == 36 )
				{
								if(cli_data.group_flag == 1)
								{
									printf("发送成功\n");
								}
								else
								{
									printf("发送失败，你没有该群\n");
								}
								
				}
				
			
		}
		else if(cmd == 4)
		{
				printf("正在打开群列表：\n");
				
				
			
			
		}
		else if(cmd == 0)
			break;
		

		
		
		
		
		
		//选择进入群聊室
		
#else
		
		//测试程序：发送和接收
		
		bzero(buf,sizeof(buf));
		printf("请输入你要发送的数据：\n");
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		if(write(srv_fd,buf,strlen(buf)) < 0){
				    perror("write");
					exit(1);
		}		
			if(!strncmp(buf,"over",4)){
			printf(RED"===========================\n"NONE);
			break;
			}		
		bzero(buf,sizeof(buf));
		if((ret = read(srv_fd,buf,sizeof(buf))) < 0){
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

		
#endif	//测试程序结束

    }
end:
    //4,断开连接
    close(srv_fd);

    return 0;
}
