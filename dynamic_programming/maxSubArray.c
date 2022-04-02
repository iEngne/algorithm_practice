/**
最大子序和
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

 

示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
示例 2：

输入：nums = [1]
输出：1
示例 3：

输入：nums = [5,4,-1,7,8]
输出：23
 

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
 

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。

相关标签
数组
分治
动态规划

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xn3cg3/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
// 最后一个元素是nums[i]的连续子数组的最大和定义为dp[i]，
// 意味着子数组的第一个元素不一定从nums[0]开始,但最后一个必须是nums[i]
int maxSubArray(int* nums, int numsSize){
   int* dp = (int*)malloc(numsSize*sizeof(int));
   dp[0] = nums[0];
   int i = 1;
   int max = nums[0];
   for (; i < numsSize; ++i){
        dp[i] = fmax(dp[i - 1], 0) + nums[i];
        max = fmax(dp[i], max);
   }
   free(dp);
   return max;
}