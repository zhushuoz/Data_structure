/*************************************************************************
	> File Name: Double_Array_Trie.c
	> Author: zhushuo
	> Mail: 
	> Created Time: 2018年10月10日 星期三 10时16分33秒
 ************************************************************************/
//双数组字典树
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 26
//字典树所用节点
typedef struct Node {
    int flag;
    struct Node *next[26];
}Node ;

//双数组存储字典树
typedef struct DATNode{
    //check 数组存节点的父亲节点的下标 用负数表示独立成词
    int base, check;
    int fail;
}DATNode;

void clear(Node *node){
    if(node == NULL) return ;
    for (int i = 0; i < 26; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
} 

/**********  字典树操作  ************/

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

int insert(Node *node, const char *str){
    Node *p = node;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        if(p->next[str[i] - 'a'] == NULL) {
            p->next[str[i] - 'a'] = getNewNode();
            cnt += 1;
        }
        p = p->next[str[i] - 'a'];
    }
    p->flag = 1;
    return cnt;
}
/*************  字典树操作 ************/

/************* 双数组字典树 ************/
//得到base值
int getBase(Node *node, DATNode *trie) {
    int base = 1, flag = 0;
    while(!flag) {
        flag = 1;
        base += 1;
        for(int i = 0; i < 26; i++) {
            if(node->next[i] == NULL) continue;
            if(trie[base + i].check == 0) continue;
            flag = 0;
            break;
        }
    }
    return base;
}

void output_da(DATNode *data, int n) {
    for (int i = 1; i <= n; i++) {
        if (i - 1 && i % 5 == 1) printf("\n");
        printf("(%2d %2d %3d)    ", i, data[i].base, data[i].check);
    }
    printf("\n");
    return ;
}

//建立双数组的字典树
void Transform(Node *node, DATNode *trie, int ind) {
    //printf("ind = %d\n", ind);
    if(node->flag) trie[ind].check = -trie[ind].check;
    trie[ind].base = getBase(node, trie);    
    for (int i = 0; i < 26; i++) {
        if(node->next[i] == NULL) continue;
        trie[trie[ind].base + i].check = ind;
    } 
    for (int i = 0; i < 26; i++) {
        if(node->next[i] == NULL) continue;
        Transform(node->next[i], trie, trie[ind].base + i);
    }
    return ;
}

int search(DATNode *trie, const char *str) {
    int p = 1;
    for(int i = 0; str[i]; i++) {
        int delta = str[i] - 'a';
        int check = abs(trie[trie[p].base + delta].check);
        if(check - p) return 0;
        p = trie[p].base + delta;
    }
    return trie[p].check < 0;
}
/************* 双数组字典树 ************/


/************* AC自动机 ************/

int has_child(DATNode *trie, int p, int i) {
    return (abs(trie[trie[p].base + i].check) == p);
}

void bulid_ac(DATNode *trie, int cnt) {
    int *queue = (int *)malloc(sizeof(int) * (cnt + 5));
    int head = 0, tail = 0;
    trie[1].fail = 0;
    queue[tail++] = 1;
    while(head < tail) {
        int now = queue[head++];
        printf("%d\n", now);
        for (int i  = 0; i < SIZE; i++) {
            //判断当前节点是否是now的子节点
            if(!has_child(trie, now, i)) continue;
            int p = trie[now].fail;
            while(p && !has_child(trie, p, i)) p = trie[p].fail;
            if(p == 0) p = 1;
            else p = trie[p].base + i;
            trie[trie[now].base + i].fail = p;
            queue[tail++] = trie[now].base + i;
        }
    }
    return ;
}

int match_count(DATNode *trie, const char *str) {
    int ret = 0;
    int p = 1, q;
    while(str[0]) {
        //while(p && p->childs[str[0] - 'a'] == NULL) p = p->fail;
        while(p && !has_child(trie, p, str[0] - 'a')) p = trie[p].fail;
        if(p == 0) p = 1;
        else p = trie[p].base + str[0] - 'a';
        q = p;
        while(q) ret += (trie[q].check < 0), q = trie[q].fail;
        //if(p == 0) p = 1;
        str++;
    }
    return ret;
}

/************* AC自动机 ************/
void output(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < 26; i++) {
        if(node->next[i] == NULL) continue;
        printf("%c", i + 'a');
        if(node->next[i]->flag == 1) printf("\n");
        output(node->next[i]);
    }
}

int main() {
    int n;
    char str[100];
    Node *root = getNewNode();
    scanf("%d", &n);
    while(n--) {
        scanf("%s", str);
        insert(root, str);
    }
    DATNode *trie = (DATNode *)calloc(sizeof(DATNode), 500);
    Transform(root, trie, 1);
    /*while(scanf("%s", str) != EOF) {
        printf("search %s is %d\n", str, search(trie, str));
    }*/
    scanf("%s", str);
    printf("start bulid_ac\n");
    bulid_ac(trie, 500);
    printf("finish bulid_ac\n");
    output_da(trie, 50);
    printf("\n");
    printf("%d\n", match_count(trie, str));

    return 0;
}
