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
		scanf("%d",&card);

		//找有没有
		{
			printf("您的卡号无效,刷卡失败,请联系管理员\n");
			getchar();
			getchar();
			continue;
		}
		else//找到了
		{
		}
	}
}
