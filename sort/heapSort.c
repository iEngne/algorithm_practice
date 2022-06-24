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

#include "stdio.h"



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
    /* 从最后一个父元素开始
       因为数组从0开始，所以对于一个下标为x的节点来说
       如果左右子节点存在，那么左子节点的下标是2x+1,右子节点是2x+2,
       所以，最后一个元素的下标是size-1,因此size - 1 == 2x+1 或者2x + 2;
       所以x = size / 2 - 1;
     */
    int dad = size/2 - 1;
    /* 第一步，将数组转换成max堆
       max堆中的数并没有排序好，因为只符合父节点比子节点大，
       但左右子节点的大小情况未知
     */
    for (; dad >= 0; --dad)
    {
        maxPercDown(nums, dad, size - 1);
    }
    /* 第二步，排序元素 */
    for (; size >= 1; --size)
    {
        /* 通过不断交换第一个元素和最后一个未排序的元素
           将当前最大的未排序元素放到最后，相当于从后往前排 */
        swap(&nums[0], &nums[size - 1]);
        maxPercDown(nums, 0, size - 2);
    }
}


int main(void)
{
    int array[] = {9,10,8,7,1,3,5,4,6,2,4, 13,12,10};
    heapSrot(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}