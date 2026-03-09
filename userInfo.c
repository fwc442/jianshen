#include <stdio.h>
#include <stdlib.h>
#include "userInfo.h"


//创建用户链表
llist_head* gyt_create(){
    llist_head* user=malloc(sizeof(llist_head));
    if(user==NULL){
        perror("malloc fail");
        return NULL;
    }
    user->head=malloc(sizeof(llist_node));
    user->len=0;
    return user;
}



//插入（头插法）0插入成功，-1插入失败
int gyt_insert_user(llist_head* user,llist_data *data){
    llist_node* n = malloc(sizeof(llist_node));
    if(n==NULL){
        perror("malloc fail");
        return -1;
    }
    n->data=data;
    n->next=user->head->next;
    user->head->next=n;

    user->len++;
    return 0;
}


/*
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
*/


//按照卡号查找用户
llist_node* gyt_search_user_by_cardId(llist_head* user,long cardId){
    llist_node* p=user->head->next;
    while(p!=NULL){
        if(p->data->id==cardId){
            return p;
        }
        p=p->next;
    }
    return NULL;
}



//按照手机号查找用户
llist_node* gyt_search_user_by_phone(llist_head* user,long phone){
    llist_node* p=user->head->next;
    while(p!=NULL){
        if(p->data->call==phone){
            return p;
        }
        p=p->next;
    }
    return NULL;
}



//删除用户(按卡号)，传参卡号，返回值成功与否，-1则删除失败，0删除成功 
int gyt_delete_user(llist_head* user,long cardId){
    llist_node* p=user->head;
    while(p->next!=NULL){
        if(p->next->data->id==cardId){
            llist_node* q=p->next;
            p->next=q->next;
            free(q);
            user->len--;
            return 0;
        }
        p=p->next;
    }
    return -1;
}



//销毁链表
void destroy(llist_head* user){
    //销毁节点
    llist_node* p=user->head->next;
    llist_node* q;
    while(p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }
    free(user->head);
    free(user);
}

llist_head *yxl_cs(void)
{
	llist_head* handler=NULL;
	handler=gyt_create();

	llist_data *one=malloc(sizeof(llist_data));
	llist_data *two=malloc(sizeof(llist_data));
	one->id=10000;
	one->call=10084;
	one->type=1;
	one->cnt=2;

	two->id=10001;
	two->call=10096;
	two->type=2;


	gyt_insert_user(handler,one);
	gyt_insert_user(handler,two);
	return handler;
}
