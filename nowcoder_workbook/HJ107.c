/**
 * @file HJ107.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-29
HJ107 求解立方根
题目
题解(171)
讨论(451)
排行
面经new
中等  通过率：29.36%  时间限制：1秒  空间限制：32M
知识点
基础数学
二分
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
计算一个浮点数的立方根，不使用库函数。
保留一位小数。

数据范围：|val| \le 20 \∣val∣≤20 

输入描述：
待求解参数，为double类型（一个实数）

输出描述：
输出参数的立方根。保留一位小数。

示例1
输入：
19.9
复制
输出：
2.7
复制
示例2
输入：
2.7
复制
输出：
1.4
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

int main(void) {
    double num;
    scanf("%lf", &num);
    double left, right;
    left = 0.01;
    int negative = 0;
    // 负数转为正数，一个数开立方是同符号的，
    // 输出时加上负号就行
    if (num < 0) {
        num = -num; 
        negative = 1;
    }
    right = num;
    // 大于0 小于1的情况下，立方根会比原来的数大
    // 所以右边界设为1
    if (num < 1) {
        right = 1;
    }
    
    double pivot;
    pivot = left + (right - left) / 2;
    while (right - left >= 0.00001) {
        if (pivot * pivot * pivot < num) {
            left = pivot;
        } else {
            right = pivot;
        }
        pivot = left + (right - left) / 2;
    }
    if (negative) {
        printf("%.1lf\n", -left);
    } else {
        printf("%.1lf\n", left);
    }
    return 0;
}