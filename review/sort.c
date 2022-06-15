#include <stdio.h>
#include <stdlib.h>


void swap(int* x, int* y)
{
    if (x != y)
    {
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
    }
}

void bubble_sort(int* nums, int size)
{
    int i,j;
    /* 外层循环控制右边界 */
    for (i = size - 1; i >=1; --i)
    {
        for (j = 0; j < i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(&nums[j], &nums[j+1]);
            }
        }
    }
}

/* 假设从大到小排 */
void selection_sort(int* nums, int size)
{
    int i, j;
    int max_index;
    /* 注意这里i < size - 1 */
    for (i = 0; i < size - 1; ++i)
    {
        max_index = i;
        for (j = i + 1; j < size; ++j)
        {
            if (nums[j] > nums[max_index])
            {
                max_index = j;
            }
        }
        swap(&nums[i], &nums[max_index]);
    }
}

/* 假设从大到小排列 */
void insertion_sort(int* nums, int size)
{
    int i, j;
    for (i = 1; i < size; ++i)
    {
        int tmp = nums[i];
        for (j = i - 1; j >= 0 && tmp > nums[j]; --j)
        {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = tmp;
    }
}

void shell_sort(int* nums, int size)
{
    int incr = 0;
    int i,j;
    for (incr = size >> 1; incr > 0; incr >>= 1)
    {
        for (i = incr; i < size ; ++i)
        {
            int tmp = nums[i];
            for (j = i - incr; j >=0 && nums[j] > tmp; j-=incr)
            {
                nums[j+incr] = nums[j];
            }
            nums[j + incr] = tmp;
        }
    }
}



int main(void)
{
    int nums[] = {3,4,1,2,5,7,8,6,5,9,10,5};
    selection_sort(nums, sizeof(nums)/sizeof(int));
    int i;
    for (i = 0; i < sizeof(nums)/sizeof(int); ++i)
    {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    return 0;
}