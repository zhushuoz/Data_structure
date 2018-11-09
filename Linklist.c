/*************************************************************************
	> File Name: Linklist.c
	> Author: 
	> Mail: 
	> Created Time: 2018年10月11日 星期四 20时23分21秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

//设置头结点的好处在于在对链表进行操作时不会改变头指针，头结点的next就是链表的第一个元素

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList {
    LinkNode head;//头结点 不存放数据 指向链表中的第一个元素
    int length;
}LinkList;

LinkNode *getNewNode(int value) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = value;
    p->next = NULL;
    return p;
}

LinkList *init() {
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));//头结点
    p->head.next = NULL;//开始头结点指向空
    p->length = 0;
    return p;
}


void insert(LinkList *l, int value, int ind){
    LinkNode *p = &(l->head);
    while(ind--) {
        p = p->next;
        if (p == NULL) return ;
    }
    LinkNode *new_node = getNewNode(value);
    new_node->next = p->next;
    p->next = new_node;
    l->length += 1;
    return ;
}

void erase(LinkList *l, int ind) {
   LinkNode *p = &(l->head);
    while(ind--) {
        p = p->next;
        if (p == NULL) return ;
    }
    if (p->next == NULL) return ;     
    LinkNode *q = p->next;
    p->next = p->next->next;
    free(q);
    l->length -= 1;
    return ;
}

void inserve(LinkList *l) {
    if (l->head.next == NULL) return ;
    LinkNode *p = l->head.next, *q;
    while (p->next) {
        q = p->next;
        p->next = q->next;
        q->next =l->head.next;
        l->head.next = q;
    }
}

void clear(LinkList *l) {
    if (l->head.next == NULL) return ;
    LinkNode *p = l->head.next, *q;
    while(p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(l);
    return ;
}

void output(LinkList *l) {
    printf("[%d]", l->length);
    LinkNode *p = l->head.next;
    while(p != NULL) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
    return ;
}


int main() {

    LinkList *l = init();
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() %4, value, ind;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                ind = rand() % (l->length + 1);
                value = rand() % 100;
                printf("insert(%d %d) to LinkList\n", value, ind);
                insert(l, value, ind);
                output(l);
            } break;
            case 3:{
                if (l->length == 0) break;
                ind = rand() % l->length;
                printf("erase(%d) from LinkList\n", ind);
                erase(l, ind);
                output(l);
            }break;
        }
    }
    inserve(l);
    output(l);
    clear(l);

    return 0;
}
