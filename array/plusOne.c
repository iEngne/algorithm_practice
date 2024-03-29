/**
加一
给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

 

示例 1：

输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字 123。
示例 2：

输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。
示例 3：

输入：digits = [0]
输出：[1]
 

提示：

1 <= digits.length <= 100
0 <= digits[i] <= 9

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x2cv1c/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include"string.h"
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize){
    int i;
    int* ret = (int*)malloc(sizeof(int) * (digitsSize+1));
    if (!ret){
        return NULL;
    }
    for (i = digitsSize - 1; i >= 0; i--){
        if (digits[i] != 9){
            digits[i]++;
            *returnSize = digitsSize;
            memcpy(ret, digits, sizeof(int) * digitsSize);
            break;
        }
        else
        {
            digits[i] = 0;
        }
    }
    if (digits[0] == 0){
        memset(ret, 0, sizeof(int) * (digitsSize+1));
        ret[0] = 1;
        *returnSize = digitsSize+1;
    }
    return ret; 
}


int nums[] = {1,2,3};

int main(void){
    int size,i = 0;
    int* ret = plusOne(nums, sizeof(nums)/sizeof(int), &size);
    while (i < size && ret){
        printf("%d\n", ret[i]);
        i++;
    }
    free(ret);
    return 0;
}