#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "yxl.h"
#include "userInfo.h"
#include "rest.h"
#include "admin.h"
#include "IO.h"

int main()
{		llist_head *user;
		admin_head *admin;
		user=gyt_create();
		admin=sjf_create_admin_list();
		read_user(user);
		read_admin(admin);
	while(1)
	{
		int n=0;
		system("clear");
		printf("------------------------------\n");
		printf("----欢迎来到健身房管理系统----\n");
		printf("------------------------------\n");
		printf("1 进入管理员系统\n");
		printf("2 进入用户登录界面\n");
		printf("3 进入打卡系统\n");
		printf("0 退出系统\n");
		printf("------------------------------\n");
		printf("请输入您的操作:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
				sjf_admin_system(user,admin);
				continue;
			case 2:
				yxl_user_ui(user);
				continue;
			case 3:
				yxl_daka(user);
				continue;
			case 0:				
				write_user(user);
				write_admin(admin);
				sjf_destroy_admin_list(admin);
				destroy(user);
				return 0;
			default:
				printf("请重新输入:");
				continue;
		}				
	}
	return 0;
}
