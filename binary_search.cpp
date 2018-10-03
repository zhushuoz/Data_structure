/*************************************************************************
	> File Name: binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年10月03日 星期三 10时27分10秒
 ************************************************************************/

#include <stdio.h>
#define P(func) {\
    printf("%s = %d\n", #func, func);\
}

// 1 2 3 4 5 6 7 
int binary_search(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] > x) tail = mid - 1;
        else head = mid +  1;
    }
    return -1;
}

//11111111000000000
int binary_search2(int *num, int n) {
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}


int binary_search3(int *num, int n) {
    int head = 0, tail = n, mid ;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}

int main() {

    int n;
    int num[100];
    int arr1[10] = {1, 3, 5, 7, 9, 11, 13, 17, 19, 23};
    int arr2[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    int arr3[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    /*scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }*/
    //printf("%d\n", binary_search2(num, n));
    P(binary_search(arr1, 10, 11));
    P(binary_search2(arr2, 10));
    P(binary_search3(arr3, 10));
}
