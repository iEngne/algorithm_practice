/**
 * 
 * @file prime_factorization.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-15
 * 
 * @copyright Copyright (c) 2022
描述
功能:输入一个正整数，按照从小到大的顺序输出它的所有质因子（重复的也要列举）（如180的质因子为2 2 3 3 5 ）


数据范围： 1 \le n \le 2 \times 10^{9} + 14 \1≤n≤2×10 
9
 +14 
输入描述：
输入一个整数

输出描述：
按照从小到大的顺序输出它的所有质数的因子，以空格隔开。

示例1
输入：
180
复制
输出：
2 2 3 3 5
 */

#include <stdio.h>



int main(void)
{
    int num = 0;
    scanf("%d", &num);
    int i = 2;
    /* 短除法 */
    for (; i <= num / i;  ++i)
    {
        // nums 能被i整除时，i一定时质数,为什么？
        /*
         如果此时i是合数，那么i肯定可以被比i小的质因数整除分解，i又是质数2开始递增的，
         那么在之前的循环中，能被小的质数分解的都已经被分解了，所以i不可能是合数。
        */
        while (num % i == 0)
        {
            num /= i;
            printf("%d ", i);
        }
    }
    if (num > 1)
    {
        printf("%d ", num);
    }
    return 0;    
}
