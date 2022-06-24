/**
 * @file HJ35.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-23
HJ35 蛇形矩阵
题目
题解(323)
讨论(642)
排行
面经new
简单  通过率：47.50%  时间限制：1秒  空间限制：32M
知识点
数组
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形。

例如，当输入5时，应该输出的三角形为：

1 3 6 10 15

2 5 9 14

4 8 13

7 12

11


输入描述：
输入正整数N（N不大于100）

输出描述：
输出一个N行的蛇形矩阵。

示例1
输入：
4
复制
输出：
1 3 6 10
2 5 9
4 8
7
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N = 0;
    scanf("%d", &N);
    int i = 0;
    int j = 0;
    int k = 0;
    int* space = (int*)malloc(N * N * sizeof(int));
    int** arr = (int**)malloc(N * sizeof(int*));
    for (i = 0; i < N; ++i)
    {
        arr[i] = space + i * N;
    }
    int num = (1 + N) * N / 2;
    int n = 0;
    i = 0;
    for (n = 1; n <= num; ++n, --i, ++j)
    {
        if (i < 0)
        {
            i = k + 1;
            j = 0;
            ++k;
        }
        arr[i][j] = n;
    }
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            if (arr[i][j] != 0)
            {
                printf("%d ", arr[i][j]);
            }
        }
        printf("\n");
    }
    free(space);
    free(arr);
    return 0;
}