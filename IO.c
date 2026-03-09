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

    fprintf(data, "%d\n", user->len);  // 只写数字，不写中文

    llist_node *p = user->head;
    while (p != NULL) {
        llist_data *d = p->data;
        if (d == NULL) { p = p->next; continue; }

        fprintf(data, "%ld %d %d ", d->call, d->type, d->cnt);

        if (d->type == 2 && d->start_time && d->end_time) {
            fprintf(data, "%d %d\n", *d->start_time, *d->end_time);
        } else {
            fprintf(data, "0 0\n");
        }
        p = p->next;
    }

    fclose(data);
}




llist_data *read_one_data(FILE *fp) {
    if (!fp) return NULL;

    llist_data *data = malloc(sizeof(llist_data));
    long call;
    int type, cnt, st, et;

    if (fscanf(fp, "%ld %d %d %d %d", &call, &type, &cnt, &st, &et) != 5) {
        free(data);
        return NULL;
    }

    data->call = call;
    data->type = type;
    data->cnt = cnt;

    if (type == 2) {
        data->start_time = malloc(sizeof(int));
        data->end_time = malloc(sizeof(int));
        *data->start_time = st;
        *data->end_time = et;
    } else {
        data->start_time = NULL;
        data->end_time = NULL;
    }

    return data;
}




void read_user(llist_head *head) {
    FILE *fp = fopen("user_data.txt", "r");
    if (!fp) return;

    int len = 0;
    fscanf(fp, "%d", &len);

    for (int i = 0; i < len; i++) {
        llist_data *data = read_one_data(fp);
        if (data) gyt_insert_user(head, data);
    }

    fclose(fp);
}


void write_admin(admin_head *admin) {
    if (admin == NULL) return;

    FILE *data = fopen("admin_data.txt", "w");
    if (data == NULL) {
        perror("打开文件失败");
        return;
    }

    fprintf(data, "%d\n", admin->len);  // 只写数字

    admin_node *p = admin->head;
    while (p != NULL) {
        admin_data *d = p->data;
        if (d == NULL) { p = p->next; continue; }
        fprintf(data, "%s %s\n", d->username, d->password);
        p = p->next;
    }

    fclose(data);
}


void read_admin(admin_head *admin) {
    FILE *fp = fopen("admin_data.txt", "r");
    if (!fp) return;

    int len = 0;
    fscanf(fp, "%d", &len);

    for (int i = 0; i < len; i++) {
        char username[20] = {0};
        char password[20] = {0};
        fscanf(fp, "%s %s", username, password);
        sjf_register_admin(admin, username, password);
    }

    fclose(fp);
}
