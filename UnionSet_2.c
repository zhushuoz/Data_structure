/*************************************************************************
	> File Name: UnionSet.c
	> Author: zhushuo
	> Mail: 
	> Created Time: 2018年10月18日 星期四 19时50分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct UnionSet {
    int *father;
    int *size;
    int n;
}UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)calloc(sizeof(UnionSet), 1);
    u->father = (int *)malloc(sizeof(int) * n);
    u->size = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->father[i] = i;
        u->size[i] = 1;
    }
    u->n = n;
    return u;
}

void clear(UnionSet *u) {
    if(u == NULL) return ;
    free(u->father);
    free(u);
    return ;
}

int find(UnionSet *u, int x) {
    if(u->father[x] != x) return find(u, u->father[x]);
    return x;
}

int merge(UnionSet *u, int a, int b) {
    int fa = find(u, a), fb = find(u, b);
    if(fa == fb) return 0;
    if(u->size[fa] < u->size[fb]) {
        fa ^= fb, fb ^= fa, fa ^= fb;
    }
    u->father[fb] = fa;
    u->size[fb] += u->size[fa];
    return 1;
}

void output(UnionSet *u) {
    for (int i = 0; i < u->n; i++) {
        printf("(%d, %d)\t");

        if(i + 1 < u->n && i + 1 % 5 == 0) printf("\n");
    }
    printf("\n\n");
}



int main() {
    srand(time(0));
    int op, a, n, b;
    #define MAX_OP 20 
    #define MAX_N 10
    UnionSet *u = init(MAX_N);
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        a = rand() % MAX_N;
        b = rand() % MAX_N;
        switch(op) {
            case 0:{
                printf("find %d <-> %d = %d\n",a, b, find(u, a) == find(u, b));
            } break;
            default:{
                
            }
        }
    }

    return 0;
}

