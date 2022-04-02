/**
打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

 

示例 1：

输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：

输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
 

提示：

1 <= nums.length <= 100
0 <= nums[i] <= 400
相关标签
数组
动态规划

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnq4km/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */


#include "stdlib.h"
#include "math.h"

// 状态转移方程：dp[i] = fmax(dp[i - 2] + nums[i], dp[i - 1])
int rob(int* nums, int numsSize){
    if (numsSize == 1){
        return nums[0];
    }else if (numsSize == 2){
        return fmax(nums[0], nums[1]);
    }
    int* dp = (int*)malloc(numsSize * sizeof(int));
    dp[0] = nums[0];
    dp[1] = fmax(nums[0], nums[1]);
    int i = 2;
    int max = dp[0];
    for (;i < numsSize; ++i){
        dp[i] = fmax(dp[i - 2] + nums[i], dp[i - 1]);
        max = fmax(dp[i],max);
    }
    free(dp);
    return max;
}