/**
 * @file HJ61.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-27
HJ61 放苹果
题目
题解(146)
讨论(253)
排行
面经new
简单  通过率：50.10%  时间限制：1秒  空间限制：32M
知识点
递归
动态规划
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
把m个同样的苹果放在n个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？
注意：如果有7个苹果和3个盘子，（5，1，1）和（1，5，1）被视为是同一种分法。

数据范围：0 \le m \le 10 \0≤m≤10 ，1 \le n \le 10 \1≤n≤10 。

输入描述：
输入两个int整数

输出描述：
输出结果，int型

示例1
输入：
7 3
复制
输出：
8
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>

/**
设f(m,n) 为m个苹果，n个盘子的放法数目，则先对n作讨论，
1.当n>m：必定有n-m个盘子永远空着，去掉它们对摆放苹果方法数目不产生影响。即if(n>m) f(m,n) = f(m,m)　　
2.当n<=m：不同的放法可以分成两类：
    1).有至少一个盘子空着，即相当于f(m,n) = f(m,n-1);
    2).所有盘子都有苹果，相当于可以从每个盘子中拿掉一个苹果，不影响不同放法的数目，即f(m,n) = f(m-n,n).
而总的放苹果的放法数目等于两者的和，即 f(m,n) =f(m,n-1)+f(m-n,n)
递归出口条件说明：
当n=1时，所有苹果都必须放在一个盘子里，所以返回１；
当没有苹果可放时，定义为１种放法；
递归的两条路，第一条n会逐渐减少，终会到达出口n==1;
第二条m会逐渐减少，因为n>m时，我们会return f(m,m)　所以终会到达出口m==0．
*/

// 递归法
int getCount(int apples, int dishes) {
    if (apples == 0 || dishes == 1) {
        return 1;
    } else if (apples < dishes) {
        return getCount(apples, apples);
    /* apples >= dished */
    } else {
        return getCount(apples, dishes - 1) + getCount(apples - dishes, dishes);
    }
}

// 动态规划迭代
int getCount1(int apples, int dishes) {
    int dp[11][11] = {0};
    int i, j; // i:苹果数量，j:盘子数量
    for (i = 0; i <= apples; ++i) {
        for (j = 0; j <= apples; ++j) {
            if (i == 0 || j == 1) {
                dp[i][j] = 1;
            } else if (i < j) {
                dp[i][j] = dp[i][i];
            } else if (i >= j) {
                dp[i][j] = dp[i][j - 1] + dp[i - j][j];
            }
        }
    }
    return dp[apples][dishes];
}

int main(void) {
    int m, n;
    scanf("%d %d", &m, &n);
    printf("%d\n", getCount1(m, n));
    return 0;
}