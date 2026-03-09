#include <stdio.h>
#include <stdlib.h>
#include "IO.h"

void write_user(llist_head *user) {
    if (user == NULL) return;

    FILE *data = fopen("user_data.txt", "w");
    if (data == NULL) {
        perror("打开用户文件失败");
        return;
    }

    // 先写入用户数量
    fprintf(data, "用户数量:%d\n", user->len);

    llist_node *p = user->head;
    while (p != NULL && p->data != NULL) {
        llist_data *d = p->data;

        // 写入卡号、手机号、类型
        fprintf(data, "卡号:%ld 手机号:%ld 类型:%d ", d->call, d->call, d->type);

        if (d->type == 1) {
            // 次数卡：写入剩余次数
            fprintf(data, "剩余次数:%d\n", d->cnt);
        } else if (d->type == 2) {
            // 时间卡：写入开卡时间和到期时间（解引用指针）
            fprintf(data, "开卡时间:%d 到期时间:%d\n", 
                   *(d->start_time), *(d->end_time));
        }

        p = p->next;
    }

    fclose(data);
}    

llist_data *read_one_data(FILE *fp)
{
    if (!fp) return NULL;

    llist_data *data = (llist_data *)malloc(sizeof(llist_data));
    
    long card, phone;
    int type;
    // 读基础信息
    if (fscanf(fp, "卡号:%ld 手机号:%ld 类型:%d ", &card, &phone, &type) != 3) {
        free(data);
        return NULL;
    }

    data->call = card;
    data->type = type;

    if (type == 1) { // 次数卡
        int cnt;
        fscanf(fp, "剩余次数:%d\n", &cnt);
        data->cnt = cnt;
        data->start_time = NULL;
        data->end_time = NULL;
    }
    else { // 时间卡
        int st, et;
        fscanf(fp, "开卡时间:%d 到期时间:%d\n", &st, &et);
        
        // 给指针分配内存！存值！
        data->start_time = (int *)malloc(sizeof(int));
        data->end_time = (int *)malloc(sizeof(int));
        *data->start_time = st;
        *data->end_time = et;
    }

    return data;
}

// 你外面已经有 head 了！直接传进去！不用二级指针！
void read_user(llist_head *head)
{
    FILE *fp = fopen("user_data.txt", "r");
    if (!fp) {
        perror("文件不存在");
        return;
    }

    int len = 0;
    fscanf(fp, "用户数量:%d\n", &len);

    // 循环读 len 条，直接插入你的链表
    for (int i = 0; i < len; i++) {
        llist_data *data = read_one_data(fp);
        if (data) {
            gyt_insert_user(head, data); // 调用你现成的插入函数
        }
    }

    fclose(fp);
}

void write_admin(admin_head *admin)
{
	if(admin==NULL)return ;
	FILE *data = fopen("admin_data.txt","w");
	if(data==NULL)
	{
		perror("打开文件失败\n");
		return;
	}
	fprintf(data,"管理员数量:%d\n",admin->len);
	admin_node *p=admin->head;
	while(p!=NULL && p->data!=NULL)
	{
		admin_data *d=p->data;
		fprintf(data,"账号:%s 密码:%s\n",d->username,d->password);
		p=p->next;
	}
	fclose(data);
}

void read_admin(admin_head *admin)
{
	FILE *fp=fopen("admin_data.txt","r");
	if(!fp)
	{
		perror("读取管理员账户失败\n");
		return;
	}
	int len=0;
	fscanf(fp,"管理员数量:%d\n",&len);

	for(int i=0;i<len;i++)
	{
		char username[20];
		char password[20];
		fscanf(fp,"账号:%s 密码:%s",username,password);
		if((sjf_register_admin(admin,username,password))!=0)
		{
			perror("添加管理员账户失败");
			return ;
		}
				
	}
	fclose(fp);
}
