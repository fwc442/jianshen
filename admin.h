#ifndef __ADMIN_H__
#define __ADMIN_H__
#include "userInfo.h"

void gyt_show_all(llist_head* user); //遍历

// 管理员数据结构
typedef struct admin_data {
    char username[20];  // 管理员用户名
    char password[20];  // 管理员密码
} admin_data;

// 管理员链表节点
typedef struct admin_node {
    admin_data *data;
    struct admin_node *next;
} admin_node;

// 管理员链表头
typedef struct admin_head {
    int len;            // 链表节点数
    admin_node *head;   // 链表头节点（哨兵位）
} admin_head;

// 错误码定义（原作者规范）
#define ADMIN_ERR_MALLOC    -11  // 内存分配失败（创建/注册失败）
#define ADMIN_ERR_LOGIN     -12  // 登录失败（用户名/密码错误）


// 创建管理员哨兵位链表，返回链表头指针，失败返回NULL
admin_head* sjf_create_admin_list();
// 销毁管理员链表，释放所有节点和内存
void sjf_destroy_admin_list(admin_head *list);


// 新建管理员账户，成功返回0，失败返回-11
int sjf_register_admin(admin_head *list, char *username, char *password);
// 管理员登录验证，成功返回0，失败返回-12
int sjf_login_admin(admin_head *list, char *username, char *password);


// 任务三主调用函数：管理员系统入口，传参用户链表头指针
void sjf_admin_system(llist_head *user_list,admin_head *admin_list);

#endif
