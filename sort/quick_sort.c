/**
 * @file quick_sort.c
 * @author your name (you@domain.com)
 * @brief 快速排序
 * @version 0.1
 * @date 2022-04-18
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

typedef struct Range
{
    int start;
    int end;
} Range;


int median3(int* nums, int left, int right)
{

}

/* 非递归的方式,在一次循环中，将可能的边界压栈 */
void quick_sort1(int* nums, int size)
{
    if (size <= 1)
    {
        return;
    }
    Range range[size];
    int p = 0;
    range[p].start = 0;
    range[p].end = size - 1;
    ++p;
    for (; p;)
    {
        Range r = range[--p];
        if (r.start >= r.end)
        {
            continue;
        }
        /* 去中间位置的数为枢纽数 */
        int pivot = nums[(r.start + r.end) / 2];
        int i = r.start;
        int j = r.end;
        /* 注意这里是小于等于 */
        for (; i <= j;)
        {
            for (; nums[i] < pivot;)
            {
                ++i;
            }
            for (; nums[j] > pivot;)
            {
                --j;
            }
            /* 注意这里是小于等于 */
            if (i <= j)
            {
                swap(&nums[i], &nums[j]);
                ++i;
                --j;
            }
        }

        if (r.start < j)
        {
            range[p].start = r.start;
            range[p].end = j;
            ++p;
        }
        if (i < r.end)
        {
            range[p].start = i;
            range[p].end = r.end;
            ++p;
        }
    }
}


void q_sort(int* nums, int left, int right)
{
    int pivot = (left + right) / 2;
    int i = left;
    int j = right;
    for (;i <= j;)
    {
        for (;nums[i] < nums[pivot];)
        {
            ++i;
        }
        for (; nums[j] > nums[pivot];)
        {
            --j;
        }
        if (i <= j)
        {
            swap(&nums[i], &nums[j]);
            ++i;
            --j;
        }
    }
    if (left < j)
    {
        q_sort(nums, left, j);
    }
    if (right > i)
    {
        q_sort(nums, i, right);
    }
}

/* 递归方式 */
void quick_sort(int *nums, int size)
{
    q_sort(nums, 0, size - 1);
    return;
}

int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    quick_sort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
