#ifndef __USERINFO_H__
#define __USERINFO_H__


typedef struct llist_data
{	
   long id;//卡号
   long call;        //手机号
   int type;        // (开卡类型 1次数卡 2时间卡)
   int* start_time; //(开卡时间)
   int* end_time;   //（充值时间）
   int cnt;         //(剩余次数)
}llist_data;

typedef struct llist_node
{
   struct llist_data *data;
   struct llist_node *next;
}llist_node;

typedef struct llist_head 
{
    int len;
    llist_node *head;
}llist_head;



llist_head* gyt_create();   ////创建用户链表
int gyt_insert_user(llist_head* user,llist_data *data); //插入（头插法）0插入成功，-1插入失败
//void gyt_show_all(llist_head* user); //遍历  已经移动到了admin_ui.c
llist_node* gyt_search_user_by_cardId(llist_head* user,long cardId);
llist_node* gyt_search_user_by_phone(llist_head* user,long phone);
int gyt_delete_user(llist_head* user,long cardId);
void destroy(llist_head* user);

llist_head* yxl_cs(void);//用于测试的函数

#endif
