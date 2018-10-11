/*************************************************************************
	> File Name: ac.c
	> Author: zhushuo
	> Mail: 
	> Created Time: 2019年10月11日 星期四 09时44分03秒
 ************************************************************************/
//线索化
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BEGIN_LETTER 'a'
#define MAX_SIZE 2000000


typedef struct Node {
    int flag;
    struct Node *next[BASE], *fail;
}Node;

typedef struct Queue {
    Node **data;
    int head, tail, size;
}Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue), 1);
    q->data = (Node **)malloc(sizeof(Node *) * n);
    q->head = q->tail = 0;
    return q;
}
void clear_queue(Queue *q) {
    if(q == NULL) return;
    free(q->data);
    free(q);
    return ;
}
Node *front(Queue *q) {
    return q->data[q->head];
}
int empty(Queue *q) {
    return q->head == q->tail;
}

void push(Queue *q, Node *node) {
    q->data[q->tail++] = node;
    return ;
}

void pop(Queue *q) {
    if(empty(q)) return ;
    q->head++;
}

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

int insert(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if(p->next[ind] == NULL) p->next[ind] = getNewNode(), ++cnt;
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}


void clear(Node *node) {
    if(node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

//层次遍历
void bulid_ac(Node *root, int n) {
    Node **queue = (Node **)malloc(sizeof(Node) * (MAX_SIZE + 5));
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *now = queue[head++];
        for (int i = 0; i < BASE; i++) {
            if (now->next[i] == NULL) {
                if (now != root) now->next[i] = now->fail->next[i];//线索化 查找
                continue;
            }
            Node *p = (now->fail ? now->fail->next[i] : root);
            if (p == NULL) p = root;//如果失败指针下没有当前i节点 则指向root
            now->next[i]->fail = p;
            queue[tail++] = now->next[i];
        }
    }
    free(queue);
    return ;
}

int match(Node *root, const char *str) {
    Node *p = root, *q;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        p = p->next[ind];
        q = p;
        /*while(p && p->next[ind] == NULL) p = p->fail;
        if(p == NULL) p = root;
        else p = p->next[ind];
        //cnt += (p->flag == 1);
        Node *q = p;
        */
        while(q) {
            cnt += q->flag, q = q->fail;
            //if(q->flag == 1) q->flag = 0;
        }
        if(p == NULL) p = root;
    }
    return cnt;
}

int main() {
    Node *root = getNewNode();
    int n, cnt = 0;
    char str[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        cnt += insert(root, str);
    }
    //bulid ac
    bulid_ac(root, cnt);
    scanf("%s", str);
    printf("%d\n", match(root, str));
    return 0;
}


