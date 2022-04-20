/**
 * @file random.c
 * @author your name (you@domain.com)
 * @brief 实现一种生成随机数的方法，参考《数据结构与算法分析 c语言实现第二版》10.4 随机化算法部分
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"


#define A 48271L
#define M 2147483647L
#define Q (M / A)
#define R (M % A)

static unsigned int seed = 1;


double 
random(void)
{
    long tmp_seed;
    tmp_seed = A * (seed % Q) - R * (seed / Q);
    if (tmp_seed >= 0)
    {
        seed = tmp_seed;
    }
    else
    {
        seed = tmp_seed + M;
    }
    
    return (double) seed / M;
}


void initialize(unsigned long init_val)
{
    seed = init_val;
}


int main(void)
{
    int i = 100;
    do
    {
        printf("%lf ", random());
    } while (--i);
    return 0;
}
