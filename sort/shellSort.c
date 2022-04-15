/**
 * @file shellSort.c
 * @author your name (you@domain.com)
 * @brief 希尔排序，也称递减增量排序算法,是优化的插入排序
 * 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率；
 * 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位；
 * 1959 Donard L.Shell提出
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"
#include "math.h"

/** Hibbard提出1，3，7，15...，这样的2^k - 1序列用于增量排序效果
 * 比N = N / 2的效果好
 * Sedgewick提出1，5，19，41，109...,这样的项或者是9*4^i - 9*2^i + 1
 * 或者是4^i - 3*2^i + 1,比上面的Hibbard提出的效果好
 */



void shellSort(int* nums, int size)
{
    int increment = 0;
    for (increment = size >> 1; increment > 0; increment >>= 1)
    {
        /** 希尔排序的内部就是简单插入排序 */
        int i;
        for (i = increment; i < size; ++i)
        {
            int key = nums[i];
            int j = i - increment;
            for (; j >= 0 && nums[j] > key; j -= increment)
            {
                nums[j + increment] = nums[j];
            }
            nums[j + increment] = key;
        }
    }
}


int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    shellSort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}

