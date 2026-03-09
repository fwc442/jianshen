#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rest.h"

// ==============================
// 任务2-1：计算剩余天数
// ==============================
int get_rest_time(llist_data *user)
{
    if (user == NULL || user->end_time == NULL) {
        return REST_ERR_NULL;
    }

    if (user->type == 1) {
        return REST_ERR_TYPE;
    }

    time_t now = time(NULL);
    time_t end = *(user->end_time);
    int diff = end - now;
    int days = diff / (24 * 60 * 60);

    return days > 0 ? days : 0;
}

// ==============================
// 任务2-2：充值功能
// ==============================
int recharge_time_card(llist_data *user, int recharge_days)
{
    if (user == NULL || user->end_time == NULL) {
        return REST_ERR_NULL;
    }
    if (recharge_days <= 0) {
        return REST_ERR_DAYS;
    }
    if (user->type == 1) {
        return REST_ERR_TYPE;
    }

    time_t old_end = *(user->end_time);
    time_t new_end = old_end + (time_t)recharge_days * 24 * 60 * 60;
    *(user->end_time) = new_end;

    return 1;
}

// ==============================
// 打印开卡时间
// ==============================
void print_start_time(llist_node *user)
{
    if (!user || !user->data) {
        printf("用户节点为空\n");
        return;
    }

    llist_data *data = user->data;

    if (!data->start_time) {
        printf("开卡时间：未设置\n");
        return;
    }

    time_t t = *(data->start_time);
    struct tm *tt = localtime(&t);
    printf("开卡时间：%04d-%02d-%02d\n",
           tt->tm_year + 1900,
           tt->tm_mon + 1,
           tt->tm_mday);
}

// ==============================
// 打印过期时间
// ==============================
void print_end_time(llist_node *user)
{
    if (!user || !user->data) {
        printf("用户节点为空\n");
        return;
    }

    llist_data *data = user->data;

    if (!data->end_time) {
        printf("过期时间：未设置\n");
        return;
    }

    time_t t = *(data->end_time);
    struct tm *tt = localtime(&t);
    printf("过期时间：%04d-%02d-%02d\n",
           tt->tm_year + 1900,
           tt->tm_mon + 1,
           tt->tm_mday);
}

/*
// ==============================
// ======== MAIN 测试函数 ========
// 自动创建用户 → 测试所有功能
// ==============================
int main()
{
    printf("===== 开始测试 rest.c 所有函数 =====\n\n");

    // 1. 创建一个测试用户节点
    llist_node *user = (llist_node *)malloc(sizeof(llist_node));
    user->data = (llist_data *)malloc(sizeof(llist_data));
    user->next = NULL;

    // 2. 基础信息
    user->data->id = 10001;
    user->data->call = 13800138000;
    user->data->type = 2;    // 时间卡
    user->data->cnt = 0;

    // 3. 给 start_time 和 end_time 分配内存（int* 存时间戳）
    user->data->start_time = (int *)malloc(sizeof(int));
    user->data->end_time   = (int *)malloc(sizeof(int));

    // 4. 赋值：开卡时间 = 现在
    time_t now = time(NULL);
    *(user->data->start_time) = now;

    // 5. 赋值：过期时间 = 10天后
    *(user->data->end_time) = now + 10 * 24 * 60 * 60;

    // ================== 测试开始 ==================

    // 测试打印时间
    printf("【测试打印时间】\n");
    print_start_time(user);
    print_end_time(user);
    printf("\n");

    // 测试剩余天数
    printf("【测试剩余天数】\n");
    int rest = get_rest_time(user->data);
    printf("剩余天数：%d\n\n", rest);

    // 测试充值 15 天
    printf("【测试充值15天】\n");
    int ret = recharge_time_card(user->data, 15);
    if (ret == 1) {
        printf("充值成功！\n");
        print_end_time(user);

        int rest_new = get_rest_time(user->data);
        printf("充值后剩余天数：%d\n", rest_new);
    }

    printf("\n===== 所有函数测试完成！=====\n");

    // 释放内存
    free(user->data->start_time);
    free(user->data->end_time);
    free(user->data);
    free(user);

    return 0;
}
*/
