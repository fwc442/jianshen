#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

// 注册新管理员（业务逻辑：查重+插入链表）
int sjf_register_admin(admin_head *list, char *username, char *password) {
    // 入参合法性校验
    if (list == NULL || username == NULL || password == NULL 
        || strlen(username) == 0 || strlen(password) == 0) {
        return ADMIN_ERR_MALLOC;
    }
    // 查重：用户名不能重复（原代码未实现，补充核心逻辑）
    admin_node *p = list->head->next;
    while (p != NULL) {
        if (strcmp(p->data->username, username) == 0) {
            printf("注册失败：用户名%s已存在！\n", username);
            return ADMIN_ERR_MALLOC;
        }
        p = p->next;
    }
    // 分配节点和数据内存
    admin_node *new_node = (admin_node*)malloc(sizeof(admin_node));
    admin_data *new_data = (admin_data*)malloc(sizeof(admin_data));
    if (new_node == NULL || new_data == NULL) {
        perror("sjf_register_admin: malloc fail");
        free(new_node);  // 防止内存泄漏
        free(new_data);
        return ADMIN_ERR_MALLOC;
    }
    // 赋值并插入链表头部（头插法，原逻辑保留）
    strcpy(new_data->username, username);
    strcpy(new_data->password, password);
    new_node->data = new_data;
    new_node->next = list->head->next;
    list->head->next = new_node;
    list->len++;
    return 0;  // 注册成功
}

// 管理员登录（业务逻辑：遍历链表匹配用户名+密码）
int sjf_login_admin(admin_head *list, char *username, char *password) {
    // 入参合法性校验
    if (list == NULL || username == NULL || password == NULL) {
        return ADMIN_ERR_LOGIN;
    }
    // 遍历链表匹配
    admin_node *p = list->head->next;
    while (p != NULL) {
        if (strcmp(p->data->username, username) == 0 &&
            strcmp(p->data->password, password) == 0) {
            return 0;  // 登录成功
        }
        p = p->next;
    }
    return ADMIN_ERR_LOGIN;  // 用户名/密码错误
}
