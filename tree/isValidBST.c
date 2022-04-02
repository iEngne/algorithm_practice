/**
验证二叉搜索树
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
 

示例 1：


输入：root = [2,1,3]
输出：true
示例 2：


输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。
 

提示：

树中节点数目范围在[1, 104] 内
-231 <= Node.val <= 231 - 1

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xn08xg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"
#include "stdbool.h"
#include "limits.h"
#include "stdlib.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isValidBST_1(struct TreeNode* root, int max, int min){
    if (!root) return true;
    if (root->val >= max || root->val <= min) return false;
    return isValidBST_1(root->left,root->val, min) && isValidBST_1(root->right, max, root->val);
}


bool isValidBST(struct TreeNode* root){
    return isValidBST_1(root, INT_MAX,INT_MIN);
}

