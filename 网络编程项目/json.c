#include "net.h"
//JSON封包
void json_lock(char *str,struct data *dt)
{

    //定义一个结构体变量同时初始化
	
	/*数据结构体 ----群聊
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

	*/
	int i;
    struct json_object *data =NULL;   //指向一个数据的指针
    struct json_object *json_cmd,*json_qq_name,*json_qq_num;
    struct json_object *json_qq_passwd,*json_qq_state,*json_group_name;
	struct json_object *json_group_num,*json_group_message,*json_group_flag;
	
	struct json_object *json_qq_safe_q, *json_qq_safe_a,*json_qq_sex;
	

    //1.创建json普通对象
    data = json_object_new_object();

    //2.将基本类型转换为json对应类型
	json_cmd 			=		json_object_new_int(dt->cmd);
	json_qq_name 		= 		json_object_new_string(dt->qq_name);
	json_qq_num 		=		json_object_new_string(dt->qq_num);
	json_qq_passwd		=		json_object_new_string(dt->qq_passwd);
	json_qq_sex 		=		json_object_new_int(dt->qq_sex);
	json_qq_state 		=		json_object_new_int(dt->qq_state);
	json_qq_safe_q 		=		json_object_new_int(dt->qq_safe_q);
	json_qq_safe_a 		=		json_object_new_string(dt->qq_safe_a);
	
	json_group_name 	= 		json_object_new_string(dt->group_name);
	json_group_num 		=		json_object_new_string(dt->group_num);
	json_group_message 	= 		json_object_new_string(dt->group_message);
	json_group_flag 	=		json_object_new_int(dt->group_flag);

    //3.将json对应类型添加到json普通对象中
	
    json_object_object_add(data,"cmd",json_cmd);
    json_object_object_add(data,"qq_name",json_qq_name);
    json_object_object_add(data,"qq_num",json_qq_num);
    json_object_object_add(data,"qq_passwd",json_qq_passwd);
	json_object_object_add(data,"qq_sex",json_qq_sex);
    json_object_object_add(data,"qq_state",json_qq_state);	
//	
	json_object_object_add(data,"qq_safe_q",json_qq_safe_q);
	json_object_object_add(data,"qq_safe_a",json_qq_safe_a);
//	
	json_object_object_add(data,"group_name",json_group_name);
	json_object_object_add(data,"group_num",json_group_num);
	json_object_object_add(data,"group_message",json_group_message);
	json_object_object_add(data,"group_flag",json_group_flag);

    const char *string =NULL;
    string = json_object_to_json_string(data);

	

    strncpy(str,string,strlen(string));
    printf("string =  %s\n",string);


    //8.销毁json对象
    json_object_put(data);

    json_object_put(json_cmd);
    json_object_put(json_qq_name);
    json_object_put(json_qq_num);
	json_object_put(json_qq_passwd);
	json_object_put(json_qq_sex);
	json_object_put(json_qq_state);
	json_object_put(json_qq_safe_q);
	json_object_put(json_qq_safe_a);
    json_object_put(json_group_name);
    json_object_put(json_group_num);
	json_object_put(json_group_message);
	json_object_put(json_group_flag);
}
//JSON解包
void json_unlock(char *str,struct data *dt)
{

	/*数据结构体 ----群聊
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

	*/
    printf("json字符串:\n %s\n",str);
    printf("***********************************************\n");

    struct json_object *data =NULL;   //指向一个数据的指针
    struct json_object *json_cmd,*json_qq_name,*json_qq_num;
    struct json_object *json_qq_passwd,*json_qq_state,*json_group_name;
	struct json_object *json_group_num,*json_group_message,*json_group_flag;

	struct json_object *json_qq_safe_q,*json_qq_safe_a,*json_qq_sex;

    //1.获取json普通对象
    data = json_tokener_parse(str);

    //2.通过key解析json对象
    json_cmd = json_object_object_get(data,"cmd");
    json_qq_name = json_object_object_get(data,"qq_name");
    json_qq_num = json_object_object_get(data,"qq_num");
	json_qq_passwd = json_object_object_get(data,"qq_passwd");
	json_qq_sex = json_object_object_get(data,"qq_sex");
	json_qq_state = json_object_object_get(data,"qq_state");
	json_qq_safe_q = json_object_object_get(data,"qq_safe_q");
	json_qq_safe_a = json_object_object_get(data,"qq_safe_a");
	json_group_name = json_object_object_get(data,"group_name");	
	json_group_num = json_object_object_get(data,"group_num");	
	json_group_message = json_object_object_get(data,"group_message");	
	json_group_flag = json_object_object_get(data,"group_flag");		

    //3.将json数据对象转换为基本类型
    dt->cmd = json_object_get_int(json_cmd);
	
    char *name=NULL;
    name= json_object_get_string(json_qq_name);
    strcpy(dt->qq_name,name);
	name = NULL;
    name= json_object_get_string(json_qq_num);
    strcpy(dt->qq_num,name);	
	name = NULL;
    name= json_object_get_string(json_qq_passwd);
    strcpy(dt->qq_passwd,name);	
	
    dt->qq_sex = json_object_get_int(json_qq_sex);	
    dt->qq_state = json_object_get_int(json_qq_state);	
	dt->qq_safe_q = json_object_get_int(json_qq_safe_q);	
	
	name = NULL;
    name= json_object_get_string(json_qq_safe_a);
    strcpy(dt->qq_safe_a,name);
	name = NULL;
    name= json_object_get_string(json_group_name);
    strcpy(dt->group_name,name);
	name = NULL;
    name= json_object_get_string(json_group_num);
    strcpy(dt->group_num,name);	
	name = NULL;
    name= json_object_get_string(json_group_message);
    strcpy(dt->group_message,name);	
	
    dt->group_flag = json_object_get_int(json_group_flag);	
	

    printf("解析成功的基本类型数据:\n");
    printf("cmd=%d qq_name=%s qq_num=%s qq_passwd=%s qq_state=%d  qq_safe_q=%d group_name=%s group_num=%s group_message=%s group_flag=%d\n",\
				dt->cmd,dt->qq_name,dt->qq_num,dt->qq_passwd,dt->qq_state,dt->qq_safe_q,dt->group_name,dt->group_num,dt->group_message,dt->group_flag);


}

