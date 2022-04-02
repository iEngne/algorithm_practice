#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**
 * 给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

 

进阶：

尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？
 

示例 1:

输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]
示例 2:

输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释: 
向右旋转 1 步: [99,-1,-100,3]
向右旋转 2 步: [3,99,-1,-100]
 

提示：

1 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1
0 <= k <= 105

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x2skh7/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
void rotate(int* nums, int numsSize, int k){
    int i,j;
    for (i = 0; i < k; i++)
    {
        for (j = numsSize - 1; j > 0;j--)
        {
            nums[j] = nums[j-1]^nums[j];
            nums[j-1] = nums[j]^nums[j-1];
            nums[j] = nums[j]^nums[j-1];
        }
    }
}

void rotate2(int* nums, int numsSize, int k){
    int * p = (int*)malloc(sizeof(int)*numsSize);
    int i = 0;
    int index = 0;
    for (i = 0; i < numsSize; i++)
    {
        index = (i + k)%numsSize;
        p[index] = nums[i];
    }
    for (i = 0; i < numsSize; i++)
    {
        nums[i] = p[i];
    }
    free(p);
}



int main(void)
{
    int nums[] = {1,2,3,4,5,6,7,8,9};
    rotate(nums, sizeof(nums)/sizeof(int), 3);
    int i = 0;
    for (i = 0;i < sizeof(nums)/sizeof(int); i++)
    {
        printf("%d,", nums[i]);
    }
    printf("\n");
    return 0;
}