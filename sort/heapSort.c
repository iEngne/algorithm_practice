/**
 * @file heapSort.c
 * @author your name (you@domain.com)
 * @brief 堆排序，也是一种选择排序
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h."



void swap(int* a, int* b)
{
    if (a != b){
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/**
 * @brief max堆，下滤
 * 
 * @param nums 
 * @param start 
 * @param end 
 */
void maxPercDown(int* nums, int dad, int end)
{
    int child = 0;
    int tmp = nums[dad];
    for (;dad * 2 + 1 <= end; dad = child)
    {
        child = dad * 2 + 1;
        /* 找到左右子元素中的最大值 */
        if (child != end && nums[child + 1] > nums[child])
        {
            ++child;
        }
        if (nums[child] > tmp)
        {
            nums[dad] = nums[child];
        }
        else
        {
            break;
        }
    }
    nums[dad] = tmp;
}

void heapSrot(int* nums, int size)
{
    /* 从最后一个父元素开始 */
    int dad = size/2 - 1;
    /* 第一步，将数组转换成max堆 */
    for (; dad >= 0; --dad)
    {
        maxPercDown(nums, dad, size - 1);
    }
    /* 第二步，排序元素 */
    for (; size >= 1; --size)
    {
        swap(&nums[0], &nums[size - 1]);
        maxPercDown(nums, 0, size - 2);
    }
}


int main(void)
{
    int array[] = {9,10,8,7,1,3,5,4,6,2};
    heapSrot(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}