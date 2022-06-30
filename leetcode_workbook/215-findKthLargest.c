/**
 * @file 215-findKthLargest.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-29
215. 数组中的第K个最大元素
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

 

示例 1:

输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
示例 2:

输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
 

提示：

1 <= k <= nums.length <= 104
-104 <= nums[i] <= 104
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>


void findMaxMin(int* nums, int numsSize, int* max, int* min) {
    *max = nums[0];
    *min = nums[0];
    int i = 0;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > *max) {
            *max = nums[i];
        }
        if (nums[i] < *min) {
            *min = nums[i];
        }
    }
    return;
}

// 思路类似于计数排序，将数值跟下标对应起来，然后从后往前找
int findKthLargest(int* nums, int numsSize, int k){
    int max, min;
    findMaxMin(nums, numsSize, &max, &min);
    int* buffer = (int*)calloc((max - min + 1), sizeof(int));
    
    int i = 0;
    for (i = 0; i < numsSize; ++i) {
        ++buffer[nums[i] - min];
    }

    for (i = max - min; i >= 0; --i) {
        while (buffer[i] > 0) {
            --buffer[i];
            --k;
            if (k == 0) {
                free(buffer);
                return i + min;
            }
        }
    }
    free(buffer);
    return 0;
}