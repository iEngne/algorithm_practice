/**
 * @file radix_sort.c
 * @author your name (you@domain.com)
 * @brief 基数排序是一种非比较型整数排序算法，
 * 其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。
 * 由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 待排序数的进制 */
#define BASE (10)


int find_max(int* arr, int size)
{
    int max = arr[0];
    int i;
    for (i = 1; i < size; ++i)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

void print(int* arr, int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void radix_sort(int* arr, int size)
{
    int* backup = arr;
    int* snd_arr = (int*)malloc(size * sizeof(int));
    int bucket[BASE] = {0};
    int i;
    int max = find_max(arr, size);
    int exp = 1;
    while (max / exp > 0)
    {
        for (i = 0; i < size; ++i)
        {
            ++bucket[(arr[i] / exp) % BASE];
        }
        for (i = 1; i < size; ++i)
        {
            bucket[i] += bucket[i - 1];
        }
        /* 计数排序，i从0开始还是size - 1开始无所谓，基数排序必须跟
        上一步中的个数累加顺序有关 */
        for (i = size - 1; i >= 0; --i)
        {
            snd_arr[--bucket[(arr[i] / exp) % BASE]] = arr[i];
        }
        // for (i = 0; i < size; ++i)
        // {
        //     snd_arr[--bucket[(arr[i] / exp) % BASE]] = arr[i];
        // }
        int * tmp;
        tmp = arr;
        arr = snd_arr;
        snd_arr = tmp;
        memset(bucket, 0 , BASE * sizeof(int));
        exp *= BASE;
        //print(arr, size);
    }
    if (backup != arr)
    {
        memcpy(arr, snd_arr, size * sizeof(int));
    }
}

int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    radix_sort(array, sizeof(array)/sizeof(int));
    int i = 0;
    for (; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}