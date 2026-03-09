#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "admin.h"
#include "rest.h"  

//遍历
void gyt_show_all(llist_head* user){
    llist_node* p=user->head->next;
    while(p!=NULL){
        printf("====================\n");
        printf("卡号：%ld\n",p->data->id);
        printf("手机号：%ld\n",p->data->call);
        printf("卡类型：");
        int r=p->data->type;
        if(r==1){
            printf("次数卡，剩余次数：%d\n",p->data->cnt);
        }else{
			printf("时间卡，");
			print_start_time(p);
			print_end_time(p);
        }
        printf("====================\n");
        p=p->next;
    }
}

// 管理员链表
static admin_head *g_admin_list = NULL;

// 时间转换工具：给时间卡赋值用,rest.c来的
static time_t ymd2timestamp(int year, int month, int day) {
    struct tm tm_time = {0};
    tm_time.tm_year = year - 1900;  // tm_year: 从1900开始
    tm_time.tm_mon = month - 1;     // tm_mon: 0-11
    tm_time.tm_mday = day;          // tm_mday: 1-31
    return mktime(&tm_time);
}

// 管理员系统ui
static void admin_op_menu(llist_head *user_list) {
    int choice;
    long id, phone;
    int type, cnt, days;
    int year, month, day;
    llist_node *found = NULL;
    llist_data *new_data = NULL;
    char username[20], password[20];

    while (1) {
		getchar();
		getchar();
		system("clear");
        printf("\n======== 管理员操作菜单 ========\n");
        printf("1. 查看所有用户\n");
        printf("2. 新增账户\n");
        printf("3. 充值账户\n");
        printf("4. 删除账户\n");
        printf("5. 注册新管理员\n");
        printf("6. 退出登录\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        getchar();  // 吸收换行符，防止输入异常

        switch (choice) {
            case 1:
                // 调用外部用户链表遍历函数（原作者逻辑）
                gyt_show_all(user_list);
                break;

            case 2:
                printf("===== 新增用户账户 =====\n");
                printf("请输入卡号：");
                scanf("%ld", &id);
                // 检查卡号是否已存在（原作者逻辑）
                if (gyt_search_user_by_cardId(user_list, id) != NULL) {
                    printf("新增失败：卡号%ld已存在！\n", id);
                    break;
                }
                printf("请输入手机号：");
                scanf("%ld", &phone);
                printf("请选择卡类型（1-次数卡，2-时间卡）：");
                scanf("%d", &type);
                if (type != 1 && type != 2) {
                    printf("新增失败：卡类型只能是1或2！\n");
                    break;
                }

                // 分配用户数据内存
                new_data = (llist_data*)malloc(sizeof(llist_data));
                if (new_data == NULL) {
                    perror("新增用户：malloc fail");
                    printf("新增失败！\n");
                    break;
                }
                // 基础信息赋值
                new_data->id = id;
                new_data->call = phone;
                new_data->type = type;

                if (type == 1) {  // 次数卡
                    printf("请输入初始剩余次数：");
                    scanf("%d", &cnt);
                    new_data->cnt = cnt;
                    new_data->start_time = NULL;
                    new_data->end_time = NULL;
                } else {  // 时间卡：赋值时间戳（和rest.c统一）
                    printf("请输入开卡时间（年 月 日）：");
                    scanf("%d %d %d", &year, &month, &day);
                    new_data->start_time = (int*)malloc(sizeof(int));
                    *new_data->start_time = ymd2timestamp(year, month, day);

                    printf("请输入过期时间（年 月 日）：");
                    scanf("%d %d %d", &year, &month, &day);
                    new_data->end_time = (int*)malloc(sizeof(int));
                    *new_data->end_time = ymd2timestamp(year, month, day);
                    new_data->cnt = 0;
                }
                // 调用外部用户链表插入函数（原作者逻辑）
                if (gyt_insert_user(user_list, new_data) == 0) {
                    printf("新增用户%ld成功！\n", id);
                } else {
                    printf("新增用户%ld失败！\n", id);
                    // 失败释放内存，防止泄漏
                    free(new_data->start_time);
                    free(new_data->end_time);
                    free(new_data);
                }
                break;

            case 3:
                printf("===== 账户充值 =====\n");
                printf("请输入要充值的卡号：");
                scanf("%ld", &id);
                found = gyt_search_user_by_cardId(user_list, id);
                if (found == NULL) {
                    printf("充值失败：未找到卡号%ld的用户！\n", id);
                    break;
                }
                // 次数卡充值（原作者逻辑，保留）
                if (found->data->type == 1) {
                    printf("请输入充值次数：");
                    scanf("%d", &cnt);
                    if (cnt <= 0) {
                        printf("充值失败：充值次数必须大于0！\n");
                        break;
                    }
                    found->data->cnt += cnt;
                    printf("充值成功！卡号%ld当前剩余次数：%d\n", id, found->data->cnt);
                } else {  // 时间卡充值：调用rest.c的recharge_time_card（修复原BUG）
                    printf("请输入充值天数：");
                    scanf("%d", &days);
                    int ret = recharge_time_card(found->data, days);
                    if (ret == 1) {
                        printf("充值成功！卡号%ld已延长%d天有效期！\n", id, days);
                        // 可选：打印充值后的过期时间
                        print_end_time(found);
                    } else if (ret == REST_ERR_DAYS) {
                        printf("充值失败：充值天数必须大于0！\n");
                    } else if (ret == REST_ERR_NULL) {
                        printf("充值失败：用户时间戳未初始化！\n");
                    } else {
                        printf("充值失败！错误码：%d\n", ret);
                    }
                }
                break;

            case 4:
                printf("===== 删除用户账户 =====\n");
                printf("请输入要删除的卡号：");
                scanf("%ld", &id);
                // 调用外部用户链表删除函数（原作者逻辑）
                if (gyt_delete_user(user_list, id) == 0) {
                    printf("删除成功：卡号%ld已删除！\n", id);
                } else {
                    printf("删除失败：未找到卡号%ld或删除失败！\n", id);
                }
                break;

            case 5:
                printf("===== 注册新管理员 =====\n");
                printf("请输入新管理员用户名：");
                scanf("%s", username);
                printf("请输入新管理员密码：");
                scanf("%s", password);
                if (sjf_register_admin(g_admin_list, username, password) == 0) {
                    printf("新管理员%s注册成功！\n", username);
                } else {
                    printf("新管理员注册失败！\n");
                }
                break;

            case 6:
                printf("已退出管理员操作，返回登录界面！\n");
                return;  // 退出内层菜单，替代原goto，更规范

            default:
                printf("输入错误：请选择1-6的有效选项！\n");
                break;
        }
    }
}

// 管理员系统入口（原作者sjf_admin_system，重构后）
void sjf_admin_system(llist_head *user_list,admin_head *admin_list) {
    if (user_list == NULL) {
        printf("管理员系统启动失败：用户链表为空！\n");
        return;
    }
    // 创建管理员链表
    g_admin_list = admin_list;
		/*sjf_create_admin_list();
    if (g_admin_list == NULL) {
        printf("管理员系统启动失败：创建管理员链表失败！\n");
        return;
    }
	*/
    // 初始化默认管理员（方便测试，原作者逻辑保留）
    sjf_register_admin(g_admin_list, "admin", "123456");
    printf("管理员系统启动成功！默认管理员：admin / 123456\n");

    char username[20], password[20];
    int outer_choice;
    // 外层登录/注册/退出菜单
    while (1) {
		getchar();
		getchar();
		system("clear");
        printf("\n===== 管理员系统 =====\n");
        printf("1. 管理员登录\n");
        printf("2. 注册新管理员\n");
        printf("3. 退出管理员系统\n");
        printf("请选择：");
        scanf("%d", &outer_choice);
        getchar();  // 吸收换行符

        switch (outer_choice) {
            case 1:
                printf("\n===== 管理员登录 =====\n");
                printf("请输入用户名：");
                scanf("%s", username);
                printf("请输入密码：");
                scanf("%s", password);
                // 调用登录业务接口
                if (sjf_login_admin(g_admin_list, username, password) == 0) {
                    printf("欢迎%s！登录成功！\n", username);
                    admin_op_menu(user_list);  // 进入操作菜单
                } else {
                    printf("登录失败：用户名或密码错误！错误码：%d\n", ADMIN_ERR_LOGIN);
                }
                break;

            case 2:
                printf("\n===== 注册新管理员 =====\n");
                printf("请输入用户名：");
                scanf("%s", username);
                printf("请输入密码：");
                scanf("%s", password);
                if (sjf_register_admin(g_admin_list, username, password) == 0) {
                    printf("注册成功！请使用新账号登录！\n");
                } else {
                    printf("注册失败！错误码：%d\n", ADMIN_ERR_MALLOC);
                }
                break;

            case 3:
                // 销毁管理员链表，释放内存
                //sjf_destroy_admin_list(g_admin_list);别特么销毁了
                printf("已退出管理员系统，感谢使用！\n");
                return;

            default:
                printf("输入错误：请选择1-3的有效选项！\n");
                break;
        }
    }
}
