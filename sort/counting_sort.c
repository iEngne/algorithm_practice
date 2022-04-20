/**
 * @file counting_sort.c
 * @author your name (you@domain.com)
 * @brief 计数排序，作为一种线性时间复杂度的排序，
 * 计数排序要求输入的数据必须是有确定范围的整数，并且数据最好集中在一定的范围内，
 * 如果有个数特别大或者特别小，内存浪费会比较大。
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int find_max_min(int* arr, int size, int* p_max, int* p_min)
{
    if (size <= 0)
    {
        return -1;
    }
    *p_max = arr[0];
    *p_min = arr[0];
    int i;
    for (i = 1; i < size; ++i)
    {
        if (arr[i] > *p_max)
        {
            *p_max = arr[i];
        }
        if (arr[i] < *p_min)
        {
            *p_min = arr[i];
        }
    }
    return 0;
}

void counting_sort(int* arr, int size)
{
    int max, min;
    int ret = find_max_min(arr, size, &max, &min);
    if (ret < 0)
    {
        printf("find max or min error\n");
        return;
    }
    int* sorted_arr = (int*)malloc(size * sizeof(int)+20);
    if (!sorted_arr)
    {
        printf("out of memory\n");
        return;
    }
    int* count_arr = (int*)calloc(max - min + 1, sizeof(int));
    if (!count_arr)
    {
        printf("out of memory\n");
        free(sorted_arr);
        return;
    }
    int i;
    /* 这一步类似于哈希,将数的有序性转化为数组小标的有序性 */
    for (i = 0; i < size; ++i)
    {
        ++count_arr[arr[i] - min];
    }
    /****************下面两个for循环时关键点*****************/
    for (i = 1; i < max - min + 1; ++i)
    {
        count_arr[i] += count_arr[i - 1];
    }
    for (i = size - 1; i >= 0; --i)
    {
        sorted_arr[--count_arr[arr[i] - min]] = arr[i];
    }
    /*******************************************************/
    for (i = 0; i < size; ++i)
    {
        printf("%d, ", sorted_arr[i]);
    }
    memcpy(arr, sorted_arr, size * sizeof(int));
    printf("\n");
    free(count_arr);
    free(sorted_arr);
    return;
}


int main(void)
{
    int array[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    counting_sort(array, sizeof(array)/sizeof(int));
    int i;
    for (i = 0; i < sizeof(array)/sizeof(int); ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}