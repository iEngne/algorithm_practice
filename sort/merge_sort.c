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
#include <math.h>

/**
 * 归并排序分为迭代法和递归法
 * 迭代法的基本思想是，一开始假设一个元素一组，然后相邻的两组进行比大小合并
 * 这样两个短的就变成了一个比原来长的有序分组了，然后再相邻的两两合并
 * 示意图如下，假设要求递增排序
 * 10   9   8   7   6   5   4   3   2   1
 *  \   /   \   /   \   /   \   /   \   /
 * [9,10]   [7,8]   [5,6]   [3,4]   [1,2]
 *      \   /           \   /
 *    [7,8,9,10]      [3,4,5,6]     [1,2]
 *              \     /
 *         [3,4,5,6,7,8,9,10]       [1,2]
 *                           \     /
 *                    [1,2,3,4,5,6,7,8,9,10]
 * 
 * 递归法的基本思想是，通过递归调用，不断对数进行二分法分组，直到每个分组都
 * 只有一个元素，然后再合并，合并过程类似上述类似。
 */



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

/************************ 迭代法 *****************************/
void merge_sort_iter(int* nums, int size)
{
    int* tmp_nums = (int*)malloc(size * sizeof(int));
    // step 标识分组的长度，以1，2，4，8...方式增长
    int step = 1;
    int index = 0;
    // 第一层用于控制步长
    for (step = 1; step < size; step <<= 1)
    {
        // 第二层用于分组划分,span是合并后的分组大小
        int span = step + step;
        for (index = 0; index < size; index += span)
        {
            merge(nums, tmp_nums, index, fmin(index + step, size - 1), fmin(index + span - 1, size - 1));
        }
    }
    free(tmp_nums);
    return;
}


/************************ 递归法 *****************************/
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
    //merge_sort(array, sizeof(array)/sizeof(int));
    merge_sort_iter(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
