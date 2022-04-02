/**
二叉树的层序遍历
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

 

示例 1：


输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
示例 2：

输入：root = [1]
输出：[[1]]
示例 3：

输入：root = []
输出：[]
 

提示：

树中节点数目在范围 [0, 2000] 内
-1000 <= Node.val <= 1000
相关标签
树
广度优先搜索
二叉树

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnldjj/
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


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
////////////////////////////////////////
typedef struct QueueNode {
    struct TreeNode*  node;
    struct QueueNode* next; 
}QueueNode;

typedef struct Queue{
    QueueNode* front;
    QueueNode* rear;
}Queue;

bool isEmpty(Queue* queue){
    return queue->front == NULL;
}

void append(Queue* queue, struct TreeNode* node){
    if (!node){
        return;
    }
    QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
    p->node = node;
    p->next = NULL;
    if (!queue->rear){
        queue->rear = p;
        queue->front = p;
    }else {
        queue->rear->next = p;
        queue->rear = p;
    }
}

struct QueueNode* serve(Queue* queue){
    if (isEmpty(queue)){
        return NULL;
    }
    QueueNode* tmp = queue->front;
    queue->front = queue->front->next;
    if (!queue->front){
        queue->rear = NULL;
    }
    return tmp;
}

int getSize(Queue* queue){
    if (isEmpty(queue)){
        return 0;
    }
    QueueNode* tmp = queue->front;
    int i = 0;
    for (;tmp;++i){
        tmp = tmp->next;
    };
    return i;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int **res = (int**)calloc(2000, sizeof(int*));
    int *resColSize = (int*)calloc(2000, sizeof(int));
    Queue queue = {0};
    append(&queue, root);
    int i = 0;
    int j = 0;
    for (;!isEmpty(&queue);){
        int size = getSize(&queue);
        //printf("size:%d\n", size);
        int* arr = (int*)malloc(size * sizeof(int));
        int i = 0;
        for (; i < size;++i){
            QueueNode* qNode = serve(&queue);
            arr[i] = qNode->node->val;
            //printf("arr[%d]:%d\n", i, arr[i]);
            if (qNode->node->left){
                //printf("qNode->node->left->val:%d\n", qNode->node->left->val);
                append(&queue, qNode->node->left);
            }
            if (qNode->node->right){
                //printf("qNode->node->right->val:%d\n", qNode->node->right->val);
                append(&queue, qNode->node->right);
            }
            free(qNode);
        }
        res[j] = arr;
        resColSize[j] = size;
        ++j;
    }
    *returnColumnSizes = resColSize;
    *returnSize = j;
    return res;
}