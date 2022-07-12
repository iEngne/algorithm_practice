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
#include <stdlib.h>
#include <time.h>


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


int median3(int* nums, int left, int right)
{
    int center = ((left & right) + (left | right)) >> 1;
    if (nums[left] > nums[center]) {
        swap(&nums[left], &nums[center]);
    }
    if (nums[left] > nums[right]) {
        swap(&nums[left], &nums[right]);
    }
    if (nums[center] > nums[right]) {
        swap(&nums[center], &nums[right]);
    }
    // 把pivot数交换到最后一个位置 */
    swap(&nums[center], &nums[right - 1]);
    return nums[right - 1];
}


void q_sort(int* nums, int left, int right)
{
    int pivot = median3(nums, left, right);
    int i = left;
    int j = right - 1;
    while (i < j) {
        while (nums[++i] < pivot);
        while (nums[--j] > pivot);
        if (i < j)
        {
            swap(&nums[i], &nums[j]);
        }
    }
    /* 把pivot交换回i的位置 */
    swap(&nums[i], &nums[right - 1]);
    /* 至少有两个元素再排序 */
    if (i - 1 - left >= 1) {
        q_sort(nums, left, i - 1);
    }
    if (right - i - 1 >= 1) {
        q_sort(nums, i + 1, right);
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
    int i = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned int)(tv.tv_usec));
    int *arr = (int*)malloc(20 * sizeof(int));
    for (i = 0; i < 20; ++i) {
        arr[i] = rand() % 100000;
    }
    quick_sort(arr, 20);
    for (i = 0; i < 20; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
