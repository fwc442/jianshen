#所有文件及标注


*main.c 主函数,主界面。调用了管理员登陆系统,用户登录系统,打卡系统,以及文件IO的读写操作


//
userInfo.c 用户链表结构体声明以及插删操作,其中遍历因为头文件相互包含的冲突问题而移动到了admin_ui.c中

userInfo.c userInfo.h,九组高艳婷
//


//
yxl_daka.c 打卡系统
yxl__user_use.c 用户登录系统,用于查询卡信息,修改手机号与与冻结卡号操作
其中由于时间函数的bug,导致剩余天数显示与实际不符

yxl_daka.c yxl_user_use.c yxl.h 九组杨旭龙
//


//
rest.c rest.h 时间函数，用于计算时间卡的剩余时长，以及充值(天数)的函数 打印开卡时间和结束时间的函数

但因为这个模块没法通过最基本的检验,全是报错,所以让ai代替原作者进行了全面重构,不过即使是这样,里面的计算剩余天数函数依旧是有bug导致没法显示正常时间

rest.c rest.h 九组张春
//


//
admin_ui.c 管理员系统的ui界面
admin_biz.c 管理员系统的业务函数入口,如各类修改与查看,增删
admin_list 管理员系统的链表

原作者写的可以运行,但是把所有代码都写在了一个admin.c里面,可读性和可修改性差,所以让ai重构写成了三个文件分开,并加以完善

admin_ui.c admin_biz.c admin_list.c admin.h 九组 孙竞富
//

//
IO.c 文件IO,用于文件的读写操作,在main程序开启时(while循环之外)先进行read读取,在主系统0建退出之前进行写入操作
IO.h
user_data.txt 用户数据,格式第一行用户数量(链表len,下面同理),后续存数字数据
admin_data.txt 管理原账户数据

用了ai来写结构和修bug
IO.c IO.h 杨旭龙
//


用户链表结构体
typedef struct llist_data

   int id;(卡号)
   int call;（手机号）
   int type;(开卡类型 1次数卡 2时间卡)
   int* start_time;(开卡时间)  
   int* end_time;（过期时间）
这个地方的int* 是败笔,原本打算写char start_time[20]以存储,但因为最后讨论使用了int* 导致所有有关时间的部分都写错了,都需要让ai来进行修复*
   int cnt;(剩余次数)
llist_data;

typedef struct llist_node

   struct llist_data *data;
   struct llist_node *next;
llist_node;

typedef struct llist_head

    int len;
    llist_node *head;
llist_head;
