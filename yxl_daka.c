#include <stdio.h>
#include <stdlib.h>
#include "yxl.h"

void yxl_daka(llist_node *cur)
{
	long card;
	llist_node *user;
	while(1)
	{
		card=0;
		system("clear");//刷屏
		printf("------------------------------\n");
		printf("-------欢迎来到打卡系统-------\n");
		printf("------------------------------\n");
		printf("\n\n");
		printf("            -请刷卡-          \n");
		scanf("%ld",&card);

		//找有没有
		{
			printf("您的卡号无效,刷卡失败,请联系管理员\n");
			getchar();
			getchar();
			continue;
		}
		else//找到了
		{
			if(user->data->type==1)
			{
				if(user->data->cnt>0)
				{
					user->data->cnt--;
					printf("欢迎您!用户@%ld，您的卡为次数卡,剩余次数为%d次\n\n",user->data->call,user->data->cnt);
					printf("您今日打卡成功,祝您今日愉快!\n\n");
					getchar();
					getchar();
				}
				else
				{
					printf("欢迎您!用户@%ld\n\n",user->data->call);
					printf("您的会员卡次数已用完,请联系管理员充值\n\n");
					getchar();
					getchar();
				}
			}
			else if(user->data->type=2)
			{
				int s_time;
				//进行时间运算
				{
					printf("欢迎您!用户@%ld，您的卡为时间卡,剩余时长为%d天\n\n",user->data->call,s_time);
					printf("您今日打卡成功,祝您今日愉快!\n\n");
					getchar();
					getchar();
				}
				else
				{
					printf("欢迎您!用户@%ld\n\n",user->data->call);
					printf("您的时间卡已过期,请联系管理员充值\n\n");
					getchar();
					getchar();
				}
			}
			else
			{
				printf("您的卡为未知卡,请联系管理员\n\n");
				getchar();
				getchar();
			}
		}
	}
}
