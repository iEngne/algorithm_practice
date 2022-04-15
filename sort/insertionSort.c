/**
 * @file insertionSort.c
 * @author your name (you@domain.com)
 * @brief 插入排序
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

void insertionSort(int* nums, int size)
{
    int i = 1;
    for (; i < size; ++i)
    {
        int key = nums[i];
        int j = i - 1;
        for (; j >= 0 && key < nums[j]; --j)
        {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = key;
    }
}

int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    insertionSort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}