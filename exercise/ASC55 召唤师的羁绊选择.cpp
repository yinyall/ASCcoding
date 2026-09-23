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

#define MAXN 35
#define MAXM 205

int w[MAXN], v[MAXN];          // 体积、战力；0 号是虚拟根
int dp[MAXN][MAXM];            // dp[u][j]：以 u 为根的子树，容量 j 的最大战力
int temp[MAXM];
int n, m;

// 邻接表
int head[MAXN], nxt[MAXN], to[MAXN], ecnt = 0;

void addEdge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void dfs(int u) {
    // 初始化：只选 u 自己
    for (int j = w[u]; j <= m; j++) dp[u][j] = v[u];

    // 合并每个子节点
    for (int e = head[u]; e; e = nxt[e]) {
        int son = to[e];
        dfs(son);
        memcpy(temp, dp[u], sizeof(dp[u]));   // 备份旧状态
        for (int j = m; j >= w[u]; j--)
            for (int k = 0; k <= j - w[u]; k++)
                if (dp[son][k] + temp[j - k] > dp[u][j])
                    dp[u][j] = dp[son][k] + temp[j - k];
    }
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &w[i], &v[i]);

    int k, indeg[MAXN] = {0};
    scanf("%d", &k);
    while (k--) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(b, a);      // b 是父，a 是子
        indeg[a]++;
    }

    // 虚拟根 0，连接所有无依赖的英雄
    w[0] = v[0] = 0;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) addEdge(0, i);

    dfs(0);
    printf("%d\n", dp[0][m]);
    return 0;
}
