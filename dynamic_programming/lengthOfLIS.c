/**
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

示例 1：

输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
示例 2：

输入：nums = [0,1,0,3,2,3]
输出：4
 * 
 */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"


// 子序列在数组中的位置可以不连续
int lengthOfLIS(int* nums, int numsSize){
    int* dp = (int*)calloc(numsSize, sizeof(int));

    int max = 1;
    int i = 1;
    int j = 0;
    for(;i < numsSize; ++i){
        dp[i] = 1;
        for(j = 0;j < i; ++j){
            if (nums[j] < nums[i]){
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
        max = fmax(max, dp[i]);
    }
    free(dp);
    return max;
}

int main(void){
    int nums[] = {10,9,2,5,3,7,101,18,7};
    printf("%d\n", lengthOfLIS(nums, sizeof(nums)/sizeof(int)));
    return 0;
}