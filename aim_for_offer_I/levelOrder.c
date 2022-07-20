/**
 * @file levelOrder.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-18
剑指 Offer 32 - I. 从上到下打印二叉树
从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

 

例如:
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回：

[3,9,20,15,7]
 

提示：

节点总数 <= 1000
 * @copyright Copyright (c) 2022
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };
 

#define MAX (1000)

int* levelOrder(struct TreeNode* root, int* returnSize){
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    struct TreeNode* queue[MAX] = {NULL};
    int front = 0;
    int rear = 0;
    int* ret = (int*)malloc(1000 * sizeof(int));
    *returnSize = 0;
    queue[rear % MAX] = root;
    ++rear;
    struct TreeNode* cur = NULL;
    while (front != rear) {
        cur = queue[front];
        front = (front + 1) % MAX;
        ret[(*returnSize)] = cur->val;
        ++(*returnSize);
        if (cur->left) {
            queue[rear] = cur->left;
            rear = (rear + 1) % MAX;
        }
        if (cur->right) {
            queue[rear] = cur->right;
            rear = (rear + 1) % MAX;
        }
    }
    return ret;
}

struct TreeNode* insertNode(struct TreeNode* root, struct TreeNode* node) {
    if (!root) {
        return node;
    }
    if (node->val > root->val) {
        root->right = insertNode(root->right, node);
    } else {
        root->left = insertNode(root->left, node);
    }
    return root;
}

struct TreeNode* makeTree(int size) {
    struct TreeNode* root = NULL;
    while (size) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = rand();
        node->left = NULL;
        node->right = NULL;
        root = insertNode(root, node);
        --size;
    }
    return root;
}

// 中序遍历
void traverseMid(struct TreeNode* root) {
    if (!root) {
        return;
    }
    traverseMid(root->left);
    printf("%d ", root->val);
    traverseMid(root->right);
}


void releaseTree(struct TreeNode* root) {
    if (!root->left && !root->right) {
        free(root);
        return;
    }
    if (root->left) {
        releaseTree(root->left);
    }
    if (root->right) {
        releaseTree(root->right);
    }
    free(root);
    return;
}


int main(void) {
    struct TreeNode* root = makeTree(10);
    traverseMid(root);
    printf("\n");
    int len = 0;
    int* ret = levelOrder(root, &len);
    int i = 0;
    for (i = 0; i < len; ++i) {
        printf("%d ", ret[i]);
    }
    printf("\n");
    free(ret);
    releaseTree(root);
    return 0;
}