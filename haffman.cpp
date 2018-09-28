/*************************************************************************
	> File Name: haffman.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年9月28日 星期日 10时01分46秒
 ************************************************************************/

 //哈夫曼树
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
}Node;

Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if(root == NULL) return ;
    clear(root->rchild);
    clear(root->rchild);
    free(root);
    return ;
}

void swap_node(Node *p, Node *q) {
    Node temp = *p;
    *p = *q;
    *q = temp;
    return ;
}


Node *bulid_haffman(Node **arr, int n) {
    Node INIT_NODE = {0, INT32_MAX, NULL, NULL};
    for (int i = 0; i < n - 1; i++) {
        Node *first = &INIT_NODE, *second = &INIT_NODE;
        for (int j = 0; j < n - i; j++) {
            if (arr[j]->freq < first->freq) {
                second = first;
                first = arr[j];
            }else if(arr[j]->freq < second->freq){
                second = arr[j];
            }
        }
        Node *temp = getNewNode(0, first->freq + second->freq);
        temp->lchild = first;
        temp->rchild = second;
        swap_node(arr[n - i - 1], first);
        swap_node(arr[n - i - 2], second);

        arr[n -i - 2] = temp;        
        for (int k = 0; k <= n - i - 2; k++) {
            printf("i = %d :%d\n", k, arr[k]->freq);
        } 
        printf("\n");
    }
    return arr[0];
}

void extract_code(Node *node, char (*code)[20], int k, char *buff){
    printf("riit = %d\n", node->lchild->freq);
    buff[k] = 0;
    if(node->key) {
        strcpy(code[node->key], buff);
        printf("k = %s\n", code[node->key]);
        return ;
    } 
    buff[k] = '0';
    extract_code(node->lchild, code, k + 1, buff);
    buff[k] = '1';
    extract_code(node->lchild, code, k + 1, buff);
    return ;
}


void in_output(Node *root){
    if (root == NULL) return ;
    printf("%d\n", root->freq);
    in_output(root->lchild);
    in_output(root->rchild);
    return ;
}


int main() {
    int n;
    char buff[100];
    scanf("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        char key[10];
        int freq;
        scanf("%s%d", key, &freq);
        arr[i] = getNewNode(key[0], freq);
    }

    Node *root = bulid_haffman(arr, n);
    //in_output(root);
    char code[256][20] = {0};
    extract_code(root, code, 0, buff);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf("%c : %s\n", i, code[i]);
    }
    return 0;
}
