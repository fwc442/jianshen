#include <stdio.h>
#include <stdlib.h>
#include "yxl.h"

void yxl_user_ui(llist_head *handler)
{
while(1)
{
	system("clear");
	long call=0;
	llist_node *user_init;
	printf("------------------------------\n");
	printf("-----欢迎来到用户登录系统-----\n");
	printf("------------------------------\n");
	printf("\n\n");
	printf("**输入0退出系统");
	printf("\n\n");
	printf("**请输入您的预留手机号:");
	scanf("%ld",&call);

	if(call==0)
		return;
	else
	{
		user_init=gyt_search_user_by_phone(handler,call);
		if(user_init!=NULL)
		{
			yxl_user_ui_main(user_init);
			continue;
		}
		else
		{
			printf("没有此用户,请确认后重新输入\n");
			getchar();getchar();continue;
		}
	}
}}

void yxl_user_ui_main(llist_node *user)
{
	while(1){
	system("clear");
	int mode;//卡模式
	int s_time;//剩余时间
	int n;//操作
	mode=user->data->type;
	printf("------------------------------\n");
	printf("-------欢迎来到用户系统-------\n");
	printf("------------------------------\n");
	printf("\n\n");
	printf("您的卡号:%ld\n",user->data->id);
	printf("您的预留手机号:%ld\n",user->data->call);
	print_start_time(user);
	switch(mode)
	{
		case 1:
			printf("您的卡类型:次数卡\n");
			printf("剩余次数:%d\n",user->data->cnt);
			break;
		case 2:
			printf("您的卡类型:时间卡\n");
			s_time=get_rest_time(user->data);
			s_time=10;
			printf("剩余过期时间:%d天\n",s_time);
			break;
		default:	
		printf("您的卡出现未知错误,请确认后退出并联系管理员\n");
		getchar();getchar();return;
	}

	printf("\n\n");
	printf("请输入您的操作:\n");
	printf("1 修改手机号\n");
	printf("2 冻结卡号(卡遗失)\n");
	printf("0 退出系统\n");
	printf("充值请联系管理员\n");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			long new_call;
			printf("请输入新的手机号:\n");
			scanf("%ld",&new_call);
			user->data->call=new_call;
			if(user->data->call==new_call)
				printf("修改成功!请确认后退出\n");
			else
				printf("修改失败!请确认后退出并联系管理员\n");
			getchar();getchar();continue;
		case 2:
			char a;
			printf("请确认是否冻结卡号:Y/N\n");
			getchar();
			scanf("%c",&a);
			if(a=='Y')
			{
				user->data->id=-1;
				if(user->data->id!=-1)
					printf("冻结失败!请确认后退出并联系管理员!\n");
				else
					printf("已冻结,请确认后退出\n");
			}
			else
				printf("已取消\n");
			getchar();getchar();continue;
		case 0:
			return;
		default:
			printf("请输入正确的操作数字!\n");
			getchar();getchar();continue;
	}
}}


