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


void swap(int* a, int* b)
{
    if (a != b){
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

void bubbleSort(int* nums, int size)
{
    /* 外循环用于控制内循环的边界 */
    int i = 0;
    for (; i < size - 1; ++i)
    {
        int j = 0;
        for (; j < size - 1 - i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(&num[j], &num[j + 1]);
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