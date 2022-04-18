/**
 * @file merge_sort.c
 * @author your name (you@domain.com)
 * @brief 归并排序
 * 采用分治法（Divide and Conquer）的一个非常典型的应用。
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"
#include "stdlib.h"


void merge(int* nums, int* tmp_nums, int left, int star_r, int right)
{
    int i, j, k;
    k = left;
    for (i = left, j = star_r; i <= star_r - 1 && j <= right;)
    {
        if (nums[i] <= nums[j])
        {
            tmp_nums[k] = nums[i];
            ++i;
            ++k;
        }
        else
        {
            tmp_nums[k] = nums[j];
            ++j;
            ++k;
        }
    }
    for (; j <= right; ++j, ++k)
    {
        tmp_nums[k] = nums[j];
    }
    for (; i <= star_r; ++i, ++k)
    {
        tmp_nums[k] = nums[i];
    }
    int size = right - left + 1;
    for (i = 0; i < size; ++i, ++left)
    {
        nums[left] = tmp_nums[left];
    }
}


void m_sort(int* nums, int* tmp_nums, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        m_sort(nums, tmp_nums, left, center);
        m_sort(nums, tmp_nums, center + 1, right);
        merge(nums, tmp_nums, left, center + 1, right);
    }
}


void merge_sort(int *nums, int size)
{
    int* tmp_nums = (int*)malloc(size * sizeof(int));
    if (!tmp_nums)
    {
        printf("out of memory\n");
        return;
    }
    m_sort(nums, tmp_nums, 0, size - 1);
    free(tmp_nums);
    return;
}


int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    merge_sort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
