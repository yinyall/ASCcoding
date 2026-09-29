/*
背景故事
开学周的前夜，ASC 实验室灯还亮着。电控组在调 PWM，硬件组在换电机轴承，运营组在排版招新海报。雪松学长端着保温杯巡场，忽然灵机一动： “今晚的工位占用要按比例来，电控：硬件：运营 = A : B : C。而且编号要体面——用 1~9 每个数恰好一次，分成三份，分别组成三位数当作三组当班编号。能列出所有合法编号的，明天不用来搬电源。” 于是大家把这件事交给了你。

任务说明
用数字 1,2,…,9 共 9 个数，各用且仅用一次，分成三组，分别组成三个三位数 X Y Z，并满足数值比例 X : Y : Z = A : B : C。 若存在解，输出全部满足条件的三连击；若无解，输出 No!!!。 视为存在同一整数倍数 k，使得 X = Ak, Y = Bk, Z = C*k； X, Y, Z 必须均为三位数（100999），且三者中 19 不重复、无遗漏； 三个工位分别可理解为：电控 = X、硬件 = Y、运营 = Z（没有“视觉”这组，别填错啦）； 输出时按每行第一个三位数 X 升序排列。

输入格式
一行三个整数：A B C，保证 A < B < C。

输出格式
若干行，每行三个三位数：X Y Z；按 X 升序。若无解，输出一行：No!!!

输入

1 2 3
输出

192 384 576
219 438 657
273 546 819
327 654 981*/ 
#include <stdio.h>

// 检查 x, y, z 三个三位数是否恰好用掉 1~9 各一次
int check(int x, int y, int z) {
    int used[10] = {0};
    int nums[3] = {x, y, z};
    for (int i = 0; i < 3; i++) {
        int n = nums[i];
        for (int j = 0; j < 3; j++) {
            int d = n % 10;
            n /= 10;
            if (d == 0) return 0;      // 不能有 0
            if (used[d]) return 0;     // 重复
            used[d] = 1;
        }
    }
    // 检查 1~9 是否都出现
    for (int d = 1; d <= 9; d++) {
        if (!used[d]) return 0;
    }
    return 1;
}

int main(void) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);

    // 计算 k 的范围
    int kmin = (100 + A - 1) / A;   // ceil(100/A)
    int kmax = 999 / C;             // floor(999/C)

    int found = 0;
    for (int k = kmin; k <= kmax; k++) {
        int X = A * k;
        int Y = B * k;
        int Z = C * k;
        // 确保都是三位数（k 范围已保证，但保险起见）
        if (X < 100 || X > 999) continue;
        if (Y < 100 || Y > 999) continue;
        if (Z < 100 || Z > 999) continue;

        if (check(X, Y, Z)) {
            printf("%d %d %d\n", X, Y, Z);
            found = 1;
        }
    }

    if (!found) {
        printf("No!!!\n");
    }

    return 0;
}
