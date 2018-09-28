/*************************************************************************
	> File Name: priority_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年9月28日 星期三 11时06分22秒
 ************************************************************************/
//优先队列
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct pri_queue{
    int *data;
    int size, cnt;
}pri_queue;

pri_queue* init(int n){
    pri_queue *q = (pri_queue *)malloc(sizeof(pri_queue));
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(pri_queue* q) {
    return q->cnt == 0;
}

int push(pri_queue* q, int value) {
    if(q->cnt == q->size) return 0;
    q->data[++q->cnt] = value;
    int ind = q->cnt;
    while(ind > 1) {
        if (q->data[ind] < q->data[ind >> 1]) break;
        swap(q->data[ind], q->data[ind >> 1]);
        ind = ind >> 1;
    }
    return 1;
}
int pop(pri_queue* q) {
    q->data[1] = q->data[q->cnt--];
    int ind = 1;
    while((ind << 1) <= q->cnt) {
        int temp = ind;
        if(q->data[temp] < q->data[ind << 1]) temp = ind << 1;
        if((ind << 1 | 1) <= q->cnt && q->data[temp] < q->data[ind << 1 | 1]) temp = ind << 1 | 1;
        if (temp == ind) break;
        swap(q->data[temp], q->data[ind]);
        ind  = temp;
    }
    return 1;
}

int top(pri_queue* q) {
    if (empty(q)) return 0;
    return q->data[1];
}

void clear(pri_queue* q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void output(pri_queue* q) {
    printf("Queue = [");
    for (int i = 1; i <= q->cnt; i++) {
        printf(" %d", q->data[i]);
        i == q->cnt || printf(",");
    }
    printf(" ]\n");
}

int main() {
    #define MAX_N 20
    srand(time(0));
    pri_queue *q = init(MAX_N);
    for (int i = 0; i < MAX_N; i++) {
        int op = rand() % 4, value = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2:
                printf("insert %d to pri_queue\n", value);
                push(q, value);
                break;
            case 3:
                printf("pop %d from pri_queue\n", top(q));
                pop(q);
                break;
        }
        output(q);
    }


}
