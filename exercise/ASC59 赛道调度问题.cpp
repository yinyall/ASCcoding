/*
背景
ASC智能车实验室在赛前训练周开放标准测试赛道供各队预约。同一时刻赛道只能被一个队使用。由于预约时间段存在重叠，管理员需要从中筛选出一批互不冲突的预约，使获批的队伍数量尽可能多。

问题描述
给出n个预约请求，每个请求包含一个开始时间begin_i与结束时间end_i（满足begin_i < end_i）。请你帮助管理员安排赛道的使用，使得能够获批的预约数量最大。

说明
时间为整数刻度，采用半开区间[begin_i, end_i)的不冲突规则；也就是说，当一个请求的开始时间等于另一个已安排请求的结束时间时，二者不冲突。

输入格式
第一行：一个整数n（1 ≤ n ≤ 1000），表示预约请求数量。 接下来n行：每行两个整数begin_i、end_i（满足0 ≤ begin_i <end_i≤ 32767）。

输出格式
输出一个整数：最多能获批的预约数量。

样例
输入数据 1
11
3 5
1 4
12 14
8 12
0 6
8 11
6 10
5 7
3 8
5 9
2 13
输出数据 1
4
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int begin;
    int end;
} Request;

int cmp(const void *a, const void *b) {
    Request *x = (Request *)a;
    Request *y = (Request *)b;
    if (x->end != y->end) return x->end - y->end;
    return x->begin - y->begin;
}

int main() {
    int n;
    scanf("%d", &n);

    Request req[1005];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &req[i].begin, &req[i].end);
    }


    qsort(req, n, sizeof(Request), cmp);

    int count = 0;
    int lastEnd = -1;

    for (int i = 0; i < n; i++) {
        if (req[i].begin >= lastEnd) {
            count++;
            lastEnd = req[i].end;
        }
    }

    printf("%d\n", count);
    return 0;
}
