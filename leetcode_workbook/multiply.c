/**
 * @file 面试题 08.05. 递归乘法.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-29
面试题 08.05. 递归乘法
递归乘法。 写一个递归函数，不使用 * 运算符， 实现两个正整数的相乘。可以使用加号、减号、位移，但要吝啬一些。

示例1:

 输入：A = 1, B = 10
 输出：10
示例2:

 输入：A = 3, B = 4
 输出：12
提示:

保证乘法范围不会溢出
 * @copyright Copyright (c) 2022
 * 
 */

void multiplyR(int* res, int a, int b) {
    if (a & 1) {
        *res += b;
    }
    a >>= 1;
    if (!a) {
        return;
    }
    b <<= 1;
    multiplyR(res, a, b);
}

int multiplyR1(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return multiplyR1(a, b - 1) + a;
}

int multiply(int A, int B){
    int res = 0;
    // multiplyR(&res, A, B);
    if (A > B) {
        res = multiplyR1(A, B);
    } else {
        res = multiplyR1(B, A);  
    }
    return res;
}