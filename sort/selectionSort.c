/**
 * @file selection.c
 * @author your name (you@domain.com)
 * @brief 选择排序
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"

/**
 * 从序列中选择一个最大(或者最小)的，放到对应位置,
 * 由于从一个序列中选择最大或者最小的方式有多种，
 * 所以有多种选择排序,堆排序也可以看作时选择排序
 */


void swap(int* a, int* b)
{
    if (a != b){
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/** 简单选择排序 */
void selectionSort(int* nums, int size)
{
    int i = 0;
    for (; i < size - 1; ++i)
    {
        int minIndex = i;
        int j = 0;
        for (j = i + 1; j < size; ++j)
        {
            if (nums[j] < nums[minIndex]){
                minIndex = j;
            }
        }
        if (i != minIndex)
        {
            swap(&nums[minIndex], &nums[i]);
        }
    }
}


int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    selectionSort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}