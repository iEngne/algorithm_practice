#include "stdio.h"
#include "stdlib.h"
/**
 * 只出现一次的数字
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

示例 1:

输入: [2,2,1]
输出: 1
示例 2:

输入: [4,1,2,1,2]
输出: 4

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x21ib6/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

int cmpfunc(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}

int singleNumber(int* nums, int numsSize){
    qsort(nums, numsSize,sizeof(int), cmpfunc);
    int i;
    // 比较下标是2x和2x+1的数
    for (i = 0; i+1 < numsSize; i+=2){
        if (nums[i] != nums[i+1]){
            return nums[i];
        }
    }
    // 如果能跑到这里说明前面都成对，最后一个是单独的数
    return nums[numsSize-1];
}

int singleNumber_1(int* nums, int numsSize){
    int xor = nums[0];
    int i;
    for (i = 1; i < numsSize; i++){
        xor ^= nums[i];
    }
    return xor;
}

int main(void){
    int nums[] = {9,9,3,3,2,1,6,7,2,4,4,1,5,5,6};
    printf("ret = %d\n", singleNumber_1(nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}