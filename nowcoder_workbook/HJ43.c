/**
 * @file HJ43.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-28
HJ43 迷宫问题
题目
题解(203)
讨论(412)
排行
面经new
中等  通过率：37.68%  时间限制：1秒  空间限制：32M
知识点
查找
dfs
广度优先搜索(BFS)
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
定义一个二维数组 N*M ，如 5 × 5 数组下所示：


int maze[5][5] = {
0, 1, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 1, 0,
};


它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的路线。入口点为[0,0],既第一格是可以走的路。


数据范围： 2 \le n,m \le 10 \2≤n,m≤10  ， 输入的内容只包含 0 \le val \le 1 \0≤val≤1 

输入描述：
输入两个整数，分别表示二维数组的行数，列数。再输入相应的数组，其中的1表示墙壁，0表示可以走的路。数据保证有唯一解,不考虑有多解的情况，即迷宫只有一条通道。

输出描述：
左上角到右下角的最短路径，格式如样例所示。

示例1
输入：
5 5
0 1 0 0 0
0 1 1 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
复制
输出：
(0,0)
(1,0)
(2,0)
(2,1)
(2,2)
(2,3)
(2,4)
(3,4)
(4,4)
复制
示例2
输入：
5 5
0 1 0 0 0
0 1 0 1 0
0 0 0 0 1
0 1 1 1 0
0 0 0 0 0
复制
输出：
(0,0)
(1,0)
(2,0)
(3,0)
(4,0)
(4,1)
(4,2)
(4,3)
(4,4)

复制
说明：
注意：不能斜着走！！     
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>


int main(void) {
    int m, n;
    int arr[10][10];
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &arr[i][j]);
        }
        getchar();
    }
    getchar();
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            printf("arr:%d \n", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}