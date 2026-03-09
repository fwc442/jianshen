#include <stdio.h>
#include <stdlib.h>
#include "admin.h"

// 创建管理员哨兵位链表
admin_head* sjf_create_admin_list() {
    admin_head *list = (admin_head*)malloc(sizeof(admin_head));
    if (list == NULL) {
        perror("sjf_create_admin_list: malloc head fail");
        return NULL;
    }
    // 创建哨兵位头节点，不存储数据
    list->head = (admin_node*)malloc(sizeof(admin_node));
    if (list->head == NULL) {
        perror("sjf_create_admin_list: malloc sentinel fail");
        free(list);
        return NULL;
    }
    list->head->next = NULL;
    list->len = 0;
    return list;
}

// 销毁管理员链表（释放所有内存，防止内存泄漏）
void sjf_destroy_admin_list(admin_head *list) {
    if (list == NULL) return;
    admin_node *p = list->head->next;  // 跳过哨兵位
    admin_node *q = NULL;
    // 遍历释放节点数据和节点本身
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q->data);  // 释放admin_data
        free(q);        // 释放admin_node
    }
    free(list->head);   // 释放哨兵位
    free(list);         // 释放链表头
    list = NULL;
}
