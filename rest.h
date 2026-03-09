#ifndef __REST_H__
#define __REST_H__

#include "userInfo.h"


#define REST_ERR_NULL       -11
#define REST_ERR_TYPE       -12
#define REST_ERR_DAYS       -13

// 2获取剩余天数
int get_rest_time(llist_data *user);

// 任务2充值天数
int recharge_time_card(llist_data *user, int recharge_days);

// 打印开卡时间
void print_start_time(llist_node *user);

// 打印过期时间
void print_end_time(llist_node *user);

#endif
