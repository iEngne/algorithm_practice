/**
对称二叉树
给你一个二叉树的根节点 root ， 检查它是否轴对称。

 

示例 1：


输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：


输入：root = [1,2,2,null,3,null,3]
输出：false
 

提示：

树中节点数目在范围 [1, 1000] 内
-100 <= Node.val <= 100
 

进阶：你可以运用递归和迭代两种方法解决这个问题吗？

相关标签
树
深度优先搜索
广度优先搜索
二叉树

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xn7ihv/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


bool isSymmetric_judge(struct TreeNode* left, struct TreeNode* right){
    if (!left && !right) return true;
    if (!left || !right || left->val != right->val) return false;
    return isSymmetric_judge(left->left, right->right) && isSymmetric_judge(right->left,left->right);
}

bool isSymmetric(struct TreeNode* root){
    if (!root) return true;
    return isSymmetric_judge(root->left, root->right);
}

/*------------------------------------------------*/

typedef struct OwnQueue {
    int head;
    int tail;
    int capacity;
    int count;
    struct TreeNode** queue;
} OwnQueue;

void pushQueue(OwnQueue* objq, struct TreeNode* elm){
    if (objq->count == 1000) return;
    objq->queue[objq->tail] = elm;
    ++objq->tail;
    ++objq->count;
    objq->tail = objq->tail % objq->capacity;
}

struct TreeNode* popQueue(OwnQueue* objq){
    if (objq->count <= 0) return NULL;
    --objq->count;
    return objq->queue[objq->head++];
}

OwnQueue* initQueue(){
    OwnQueue* objq = (OwnQueue*)calloc(1, sizeof(OwnQueue));
    objq->queue = (struct TreeNode**)calloc(1000, sizeof(struct TreeNode));
    objq->capacity = 1000;
    objq->head = 0;
    objq->tail = 0;
    objq->count = 0;
    return objq;
}

void delQueue(OwnQueue* objq){
    free(objq->queue);
    free(objq);
}

bool isSymmetric(struct TreeNode* root){
    struct TreeNode* p = root->left;
    struct TreeNode* q = root->right;
    OwnQueue* objq = initQueue();
    pushQueue(objq, p);
    pushQueue(objq, q);
    for (;objq->count > 0;){
        p = popQueue(objq);
        q = popQueue(objq);
        if (!q && !p) continue;
        if (!p || !q || p->val != q->val){
            delQueue(objq);
            return false;
        }

        pushQueue(objq, p->left);
        pushQueue(objq, q->right);

        pushQueue(objq, p->right);
        pushQueue(objq, q->left);
    }
    delQueue(objq);
    return true;
}