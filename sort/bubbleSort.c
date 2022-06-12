/**
 * @file bubble.c
 * @author your name (you@domain.com)
 * @brief 冒泡排序
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"


void swap(int* x, int* y)
{
    if (x != y)
    {
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
    }
}

void bubble_sort(int* nums, int size)
{
    int i,j;
    /* 外层循环控制有边界 */
    for (i = size - 1; i >=1; --i)
    {
        for (j = 0; j < i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(&nums[j], &nums[j+1]);
            }
        }
    }
}

int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    bubbleSort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}