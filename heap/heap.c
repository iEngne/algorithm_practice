/**
 * @file heap.c
 * @author your name (you@domain.com)
 * @brief 二叉堆，二叉堆一般使用使用数组实现，在逻辑结构上又具有二叉树的特征，
 * 数组下标一般从1开始，这样对于任意的下标为i的非叶子节点，它的左子节点下标是2i,右子节点是2i+1。
 * 如果数组下标从0开始，这样对于任意的下标为i的非叶子节点，它的左子节点下标是2i+1,右子节点是2i+2。
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"
#include "stdlib.h"

typedef struct HeapStruct
{
    int capacity;
    int size;
    int* heap;
} HeapStruct;


HeapStruct* initialize(int maxSize)
{
    HeapStruct* h = (HeapStruct*)malloc(sizeof(HeapStruct));
    if (!h)
    {
        printf("out of memory\n");
        return NULL;
    }
    h->capacity = maxSize;
    h->size = 0;
    h->heap = (int*)malloc((maxSize + 1) * sizeof(int)); /**< 加1是因为数组从下标1开始，空间要多一个 */
    if (!h->heap)
    {
        printf("out of memory\n");
        free(h);
        return NULL;
    }
    return h;
}

void deinitialize(HeapStruct* h)
{
    if (h)
    {
        if (h->heap)
        {
            free(h->heap);
        }
        free(h);
    }
}


/**
 * @brief 在堆中插入数据，使用上滤percolate up
 *
 * @param h 
 * @param x 
 */
void insert(HeapStruct* h, int x)
{
    if (h->size == h->capacity)
    {
        return;
    }
    int i = ++h->size;
    for (; (i >> 1) >= 1 && h->heap[i >> 1] > x; i >>= 1)
    {
        h->heap[i] = h->heap[i >> 1];
    }
    h->heap[i] = x;
}


/**
 * @brief 删除最小元素，下滤
 * 上滤或者下滤过程类似于插入排序
 * @param h 
 * @param x 
 */
int deleteMin(HeapStruct* h)
{
    if (h->size == 0)
    {
        printf("no element\n");
        return 0;
    }
    int i;
    int min = h->heap[1];
    int child;
    int lastOne = h->heap[h->size];
    for (i = 1; i * 2 <= h->size;i = child)
    {
        child = i * 2;
        /* 找到左右child中的最小者 */
        if (child < h->size && h->heap[child + 1] < h->heap[child])
        {
            ++child;
        }
        /* 删除的时候，一定会有一个位置空出来，
           使用左右子元素和最后一个元素三者间最小的元素去填充
        */
        if (lastOne > h->heap[child])
        {
            h->heap[i] = h->heap[child];
        }
        else
        {
            break;
        }
    }
    h->heap[i] = lastOne;
    --h->size;
    return min;
}


int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    HeapStruct* h = initialize(sizeof(array)/sizeof(int));
    int i = 0;
    for (i = 0; i < sizeof(array)/sizeof(int); ++i)
    {
        insert(h, array[i]);
    }
    for (i = 0; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d,", h->heap[i]);
    }
    printf("\n");
    while (h->size > 0)
    {
        printf("%d ", deleteMin(h));
    }
    printf("\n");
    deinitialize(h);
    return 0;
}