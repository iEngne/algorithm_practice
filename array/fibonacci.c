/**
 * @file fibonacci.c
 * @author your name (you@domain.com)
 * @brief 求斐波那契数列，已知f(0) = 0, f(1) = 1, f(n) = f(n-1) + f(n-2),其中n >= 2
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"
#include "stdlib.h"

////////////递归法，时间复杂夫O(2^n)////////////
int fibo(int n){
    if (n == 0){
        return 0;
    }else if (n == 1){
        return 1;
    }else{
        return fibo(n-1)+fibo(n-2);
    }
}

///////////////带存储的递归，减少递归次数，空间换时间，时间复杂度O(n)////////////
int recurrence(int* memo, int n){
    if (n == 0){
        return 0;
    }else if (n == 1){
        return 1;
    }
    if (memo[n] != 0){
        return memo[n];
    }
    memo[n] = recurrence(memo, n-1) + recurrence(memo, n-2);
    return memo[n];
}

int fibo1(int n){
    int* memo = (int*)calloc(n+1, sizeof(int));
    int ret = recurrence(memo, n);
    free(memo);
    return ret;
}

//////////////////不使用递归，使用递推,时间复杂度O(n)/////////////////
int fibo2(int n){
    int* dp = (int*)calloc(n+1, sizeof(int));
    int i = 0;
    dp[0] = 0;
    dp[1] = 1;
    for (i = 2; i <= n; ++i){
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    int ret = dp[n];
    free(dp);
    return ret;
}
///////////////////在上面的基础上继续优化空间///////////////////////
int fibo3(int n){
    int pre = 1;
    int pre_pre = 0;
    int cur = 0;
    int i = 0;
    if (n == 0){
        return pre_pre;
    }else if (n == 1){
        return pre;
    }
    for (i = 2; i <= n; ++i){
        cur = pre + pre_pre;
        pre_pre = pre;
        pre = cur;
    }
    return cur;
}

int main(void){
    printf("%d\n", fibo3(8));
    return 0;
}