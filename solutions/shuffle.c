/**
 * @file shuffle.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
打乱数组
给你一个整数数组 nums ，设计算法来打乱一个没有重复元素的数组。打乱后，数组的所有排列应该是 等可能 的。

实现 Solution class:

Solution(int[] nums) 使用整数数组 nums 初始化对象
int[] reset() 重设数组到它的初始状态并返回
int[] shuffle() 返回数组随机打乱后的结果
 

示例 1：

输入
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
输出
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

解释
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。例如，返回 [3, 1, 2]
solution.reset();      // 重设数组到它的初始状态 [1, 2, 3] 。返回 [1, 2, 3]
solution.shuffle();    // 随机返回数组 [1, 2, 3] 打乱后的结果。例如，返回 [1, 3, 2]
 

提示：

1 <= nums.length <= 200
-106 <= nums[i] <= 106
nums 中的所有元素都是 唯一的
最多可以调用 5 * 104 次 reset 和 shuffle
相关标签
数组
数学
随机化

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xn6gq1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */


#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/time.h"
#include "string.h"

typedef struct {
    int* srcNum;
    int* shuffleNums;
    int size;
} Solution;


Solution* solutionCreate(int* nums, int numsSize) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->srcNum = (int*)malloc(numsSize * sizeof(int));
    obj->shuffleNums = (int*)malloc(numsSize * sizeof(int));
    obj->size = numsSize;
    memcpy(obj->srcNum, nums, numsSize * sizeof(int));
    return obj;
}

int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->size;
    return obj->srcNum;
}

int* solutionShuffle(Solution* obj, int* retSize) {
    int i = 0;
    int* backup = (int*)malloc(obj->size * sizeof(int));
    memcpy(backup, obj->srcNum, obj->size * sizeof(int));
    struct timeval tv;
    struct timezone tz;
    for (; i < obj->size; ++i){
        int index = 0;
        gettimeofday(&tv, &tz);
        srand((unsigned int)(tv.tv_usec));
        while (backup[index = rand()%obj->size] == 0x80000000);
        obj->shuffleNums[i] = backup[index];
        backup[index] = 0x80000000;
    }
    *retSize = obj->size;
    return obj->shuffleNums;
}

void solutionFree(Solution* obj) {
    free(obj->srcNum);
    free(obj->shuffleNums);
    free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(nums, numsSize);
 * int* param_1 = solutionReset(obj, retSize);
 
 * int* param_2 = solutionShuffle(obj, retSize);
 
 * solutionFree(obj);
*/


int main(void){
    int nums[]={3,4,5,1,2};
    int numsSize = sizeof(nums)/sizeof(int);
    Solution* obj = solutionCreate(nums, numsSize);
    int retSize = 0;
    int* param_1 = solutionReset(obj, &retSize);
    int i = 0;
    for (; i < numsSize; ++i){
        printf("%d\n", param_1[i]);
    }
    int* param_2 = solutionShuffle(obj, &retSize);
    i = 0;
    for (; i < numsSize; ++i){
        printf("sh:%d\n", param_2[i]);
    }
    solutionFree(obj);
    return 0;
}