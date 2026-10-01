/*
题目描述
实现一个简化版菜单导航系统，仅支持菜单导航功能，具体要求如下：

菜单结构：
主菜单（Main Menu）包含 3 个子菜单：
LED Control
Image
PID
LED Control 菜单包含 2 个选项：
LED On
LED Off
Image 菜单包含 1 个选项：
Show Image
PID 菜单包含 3 个选项：
Set KP
Set KI
Set KD

操作控制：
'W'：指针上移（循环，如顶部项上移会到最底部）
'S'：指针下移（循环，如底部项下移会到最顶部）
'A'：进入选中的子菜单（若当前为最底层菜单项，按 A 无实质操作，仅刷新显示）
'D'：返回上一级菜单（主菜单按 D 无实质操作，仅刷新显示）
'0'：退出程序

显示要求：
程序启动后立即显示主菜单初始状态
每次操作后更新并显示菜单状态
固定显示 "[normal mode]"
菜单标题格式："=== 菜单名称 ==="
菜单项中，选中项前显示 "->"，未选中项前显示 " "（三个空格）

初始状态：主菜单（Main Menu），指针指向第一个选项 "LED Control"。

输入格式
每次输入一个字符，有效输入为 'W'、'S'、'A'、'D'、'0'

输出格式
正常显示：
第一行："[normal mode]"
第二行：菜单标题，格式为 "=== 菜单名称 ==="
后续行：菜单项，选中项前显示 "->"，未选中项前显示 " "
特殊输出：
输入无效字符时，输出 "Invalid input"，此时不会更新菜单
退出程序时，输出 "Program exited"

样例
输入数据 1
A S S D S S A D S S A D 0
输出数据 1

[normal mode]
=== Main Menu ===
-> LED Control
   Image
   PID
[normal mode]
=== LED Control ===
-> LED On
   LED Off
[normal mode]
=== LED Control ===
   LED On
-> LED Off
[normal mode]
=== LED Control ===
-> LED On
   LED Off
[normal mode]
=== Main Menu ===
-> LED Control
   Image
   PID
[normal mode]
=== Main Menu ===
   LED Control
-> Image
   PID
[normal mode]
=== Main Menu ===
   LED Control
   Image
-> PID
[normal mode]
=== PID ===
-> Set KP
   Set KI
   Set KD
[normal mode]
=== Main Menu ===
   LED Control
   Image
-> PID
[normal mode]
=== Main Menu ===
-> LED Control
   Image
   PID
[normal mode]
=== Main Menu ===
   LED Control
-> Image
   PID
[normal mode]
=== Image ===
-> Show Image
[normal mode]
=== Main Menu ===
   LED Control
-> Image
   PID
Program exited
*/

#include <stdio.h>
#include <string.h>

const char* mainMenu[] = {"LED Control", "Image", "PID"};
const char* ledMenu[] = {"LED On", "LED Off"};
const char* imageMenu[] = {"Show Image"};
const char* pidMenu[] = {"Set KP", "Set KI", "Set KD"};
int level = 0;
int parentIdx = 0;
int cursor = 0;
void display() {
    printf("[normal mode]\n");
    if (level == 0) {
        printf("=== Main Menu ===\n");
        for (int i = 0; i < 3; i++) {
            if (i == cursor) printf("-> %s\n", mainMenu[i]);
            else printf("   %s\n", mainMenu[i]);
        }
    } else {
        if (parentIdx == 0) {
            printf("=== LED Control ===\n");
            for (int i = 0; i < 2; i++) {
                if (i == cursor) printf("-> %s\n", ledMenu[i]);
                else printf("   %s\n", ledMenu[i]);
            }
        } else if (parentIdx == 1) {
            printf("=== Image ===\n");
            for (int i = 0; i < 1; i++) {
                if (i == cursor) printf("-> %s\n", imageMenu[i]);
                else printf("   %s\n", imageMenu[i]);
            }
        } else {
            printf("=== PID ===\n");
            for (int i = 0; i < 3; i++) {
                if (i == cursor) printf("-> %s\n", pidMenu[i]);
                else printf("   %s\n", pidMenu[i]);
            }
        }
    }
}
int main() {
    char input[10];
    
    display();
    
    while (1) {
        scanf("%s", input);
        
        if (strcmp(input, "0") == 0) {
            printf("Program exited\n");
            break;
        }
        if (strcmp(input, "W") != 0 && strcmp(input, "S") != 0 && 
            strcmp(input, "A") != 0 && strcmp(input, "D") != 0) {
            printf("Invalid input\n");
            continue;
        }
        if (strcmp(input, "W") == 0) {
            if (level == 0) {
                cursor = (cursor - 1 + 3) % 3;
            } else {
                if (parentIdx == 0) cursor = (cursor - 1 + 2) % 2;
                else if (parentIdx == 1) cursor = 0;
                else cursor = (cursor - 1 + 3) % 3;
            }
        } else if (strcmp(input, "S") == 0) {
            if (level == 0) {
                cursor = (cursor + 1) % 3;
            } else {
                if (parentIdx == 0) cursor = (cursor + 1) % 2;
                else if (parentIdx == 1) cursor = 0;
                else cursor = (cursor + 1) % 3;
            }
        } else if (strcmp(input, "A") == 0) {
            if (level == 0) {
                parentIdx = cursor;
                level = 1;
                cursor = 0;
            }
        } else if (strcmp(input, "D") == 0) {
            if (level == 1) {
                level = 0;
                cursor = parentIdx;
            }
        }
        
        display();
    }
    return 0;
}
