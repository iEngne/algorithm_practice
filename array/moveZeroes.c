/**
移动零
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。

 

示例 1:

输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]
示例 2:

输入: nums = [0]
输出: [0]
 

提示:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

进阶：你能尽量减少完成的操作次数吗？

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x2ba4i/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"
#include "stdlib.h"

void moveZeroes(int* nums, int numsSize){
    int i,j;
    for(i = 0; i < numsSize - 1; i++){
        for (j = i + 1; j < numsSize; j++){
            if (nums[i] == 0 && nums[j] != 0){
                nums[i] = nums[i]^nums[j];
                nums[j] = nums[i]^nums[j];
                nums[i] = nums[i]^nums[j];
                break;
            }
        }
    }
}

void moveZeroes_1(int* nums, int numsSize){
    int i = 0;
    int j = 0;
    // 找到0元素最先出现的地方
    while (j < numsSize){
        if (nums[j] == 0){
            i = j;
            break;
        }
        j++;
    }
    while(j < numsSize){
        if (nums[i] == 0 && nums[j] != 0){
            nums[i] = nums[i]^nums[j];
            nums[j] = nums[i]^nums[j];
            nums[i] = nums[i]^nums[j];
            i++;
            j++;
            continue;
        }
        j++;
    }
}


void moveZeroes_2(int* nums, int numsSize){
    int i = 0;
    int j = 1;
    if (numsSize == 1){
        return;
    }
    while(j < numsSize){
        if (nums[j] == 0){
            j++;
        }
        else {
            nums[i] = nums[j];
            j++;
            i++;
        }
    }
    while (i < numsSize){
        nums[i] = 0;
        i++;
    }
}


int nums[] = {0,1,0,3,12};
int main(void){
    int size = sizeof(nums)/sizeof(int);
    moveZeroes_2(nums, size);
    int i = 0;
    for(; i < size; i++){
        printf("%d\n", nums[i]);
    }
    return 0;
}