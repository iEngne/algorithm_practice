/**
将有序数组转换为二叉搜索树
给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。

高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

 

示例 1：


输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：

示例 2：


输入：nums = [1,3]
输出：[3,1]
解释：[1,null,3] 和 [3,1] 都是高度平衡二叉搜索树。
 

提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 按 严格递增 顺序排列
相关标签
树
二叉搜索树
数组
分治
二叉树

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xninbt/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
////////////////////////////////////////////

struct TreeNode* sortedArrayToBST_impl(int* nums, int i, int j){
    if (j < i){
        return NULL;
    }
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    int middle = (j - i + 1)/2 + i; 
    node->val = nums[middle];
    node->left = sortedArrayToBST_impl(nums, i, middle - 1);
    node->right = sortedArrayToBST_impl(nums, middle + 1, j);
    return node;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return sortedArrayToBST_impl(nums, 0, numsSize - 1);
}