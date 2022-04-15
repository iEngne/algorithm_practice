/**
 * @file heap.c
 * @author your name (you@domain.com)
 * @brief 二叉堆
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"

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
        printf("out of memory\n")
        return NULL;
    }
    h->capacity = maxSize;
    h->size = 0;
    h->heap = (int*)malloc(maxSize * sizeof(int) + 1); /**< 加1是因为数组从下标1开始，空间要多一个 */
    if (!h->heap)
    {
        printf("out of memory\n")
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
    for (; h->heap[i >> 1] > x; i >>= 1)
    {
        h->heap[i] = h->heap[i >> 1];
    }
    h->heap[i] = x;
}


/**
 * @brief 删除最小元素，下滤
 * 
 * @param h 
 * @param x 
 */
int deleteMin(HeapStruct* h , int x)
{
    int i = 1;
    int min = h->heap[1];
    int child;
    int lastOne = h->heap[h->size];
    for (; child <= h->size;)
    {
        child = i * 2;
        if (h->heap[child + 1] < h->heap[child])
        {
            ++child;
        }
        /* 删除的时候，一定会有一个位置空出来，
           使用子元素和最后一个元素三者间最小的元素去填充
        */
        if (lastOne > h-heap[child])
        {
            h->heap[i] = h->heap[child];
        }
        else
        {
            break;
        }
        i = child;
    }
    h->heap[i] = lastOne;
    return min;
}