/**
 * @file HJ91.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-27
HJ91 走方格的方案数
题目
题解(176)
讨论(362)
排行
面经 new
简单  通过率：50.11%  时间限制：1秒  空间限制：32M
知识点
动态规划
基础数学
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
请计算n*m的棋盘格子（n为横向的格子数，m为竖向的格子数）从棋盘左上角出发沿着边缘线从左上角走到右下角，总共有多少种走法，要求不能走回头路，即：只能往右和往下走，不能往左和往上走。

注：沿棋盘格之间的边缘线行走

数据范围： 1 \le n,m \le 8 \ 1≤n,m≤8 


输入描述：
输入两个正整数n和m，用空格隔开。(1≤n,m≤8)

输出描述：
输出一行结果

示例1
输入：
2 2
复制
输出：
6
复制
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>


int getPathNums(int row, int col) {
    int dp[9][9] = {0};
    int i, j;
    dp[0][0] = 1;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            if (i - 1 >= 0 && j - 1 >= 0) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            } else if (i - 1 >= 0) {
                dp[i][j] = dp[i - 1][j];
            } else if (j - 1 >= 0) {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }
    return dp[row - 1][col - 1];
}


int main(void) {
    int i, j;
    scanf("%d %d", &i, &j);
    printf("%d\n", getPathNums(i + 1, j + 1));
    return 0;
}