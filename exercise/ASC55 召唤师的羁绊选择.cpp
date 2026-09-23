/*
题目描述
在召唤师峡谷，不是所有英雄都能单打独斗。有些英雄只有在“羁绊”英雄也被选中时，才能上场。给定召唤空间容量 m 和 n 个英雄，每个英雄有体积 w、战斗力 v，部分英雄有“依赖关系”：如果英雄 A 依赖于英雄 B，只有选了英雄 B 才能选英雄 A。 请问，如何在不超过空间容量的前提下，选出最大战斗力？

输入格式
第一行输入整数 m 和 n（1≤m≤200，1≤n≤30）。 接下来 n 行，每行输入两个整数，表示第 i 个英雄的体积 w 和战斗力 v。 再输入一个整数 k，表示依赖关系对数。 接下来 k 行，每行输入两个整数 a b，表示“英雄 a 依赖于英雄 b”（下标从1开始）

输出格式
输出最大总战斗力。

样例
输入数据 1
10 3
2 5
4 11
6 13
1
3 2
输出数据 1
24
*/




#include <stdio.h>
#include <string.h>

#define MAX_M 205
#define MAX_N 35

int m, n;
int w[MAX_N], v[MAX_N];
int dep[MAX_N][MAX_N];
int arr[MAX_M];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }
    
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        dep[a][b] = 1;
    }
    
    memset(arr, 0, sizeof(arr));
    
    int need[MAX_N][MAX_N] = {0};
    for (int i = 1; i <= n; i++) {
        need[i][i] = 1;
        for (int j = 1; j <= n; j++) {
            if (dep[i][j]) {
                need[i][j] = 1;
                for (int l = 1; l <= n; l++) {
                    if (dep[j][l]) {
                        need[i][l] = 1;
                    }
                }
            }
        }
    }
    
    int total = 1;
    for (int i = 0; i < n; i++) total *= 2;
    
    for (int count = 0; count < total; count++) {
        int total_w = 0, total_v = 0;
        int valid = 1;
        
        for (int i = 0; i < n; i++) {
            if (count & (1 << i)) {
                int hero = i + 1;
                for (int j = 1; j <= n; j++) {
                    if (need[hero][j] && !(count & (1 << (j-1)))) {
                        valid = 0;
                        break;
                    }
                }
                if (!valid) break;
                total_w += w[hero];
                total_v += v[hero];
            }
        }
        
        if (valid && total_w <= m && total_v > arr[m]) {
            arr[m] = total_v;
        }
    }
    
    printf("%d\n", arr[m]);
    return 0;
}
