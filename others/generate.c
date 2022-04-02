/**
 * @file generate.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief 
杨辉三角
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。



 

示例 1:

输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
示例 2:

输入: numRows = 1
输出: [[1]]
 

提示:

1 <= numRows <= 30
相关标签
数组
动态规划

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xncfnv/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int** res = (int**)malloc(numRows * sizeof(int*));
    int* returnColSizes = (int*)malloc(numRows * sizeof(int));
    *returnSize = 0;
    if (numRows == 1){
        int* row1 = (int*)malloc(1 * sizeof(int));
        row1[0] = 1;
        res[0] = row1;
        *returnSize = 1;
        returnColSizes[0] = 1;
    }else if (numRows >= 2){
        int* row1 = (int*)malloc(1 * sizeof(int));
        int* row2 = (int*)malloc(2 * sizeof(int));
        row1[0] = 1
        row2[0] = 1;
        row2[1] = 1;
        res[0] = row1;
        res[1] = row2;
        *returnSize = 2;
        returnColSizes[0] = 1;
        returnColSizes[1] = 2;
    }
    int i;
    int* rowPre;
    for(i = 2; i < numRows; ++i){
        rowPre = res[i - 1];
        int* row = (int*)malloc((i+1) * sizeof(int));
        int j = 1;
        row[0] = 1;
        row[i] = 1;
        for (; j < i; ++j){
            row[j] = rowPre[j - 1] + rowPre[j];
        }
        returnColSizes[i] = i + 1;
        ++(*returnSize);
        res[i] = row;
    }
    *returnColumnSizes = returnColSizes;
    return res;
}