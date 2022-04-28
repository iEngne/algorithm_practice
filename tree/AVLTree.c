/**
 * @file searchTree.c
 * @author your name (you@domain.com)
 * @brief 实现一个高度自平衡的AVL树
 * @version 0.1
 * @date 2022-04-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"
#include "math.h"
#include <sys/time.h>

#ifndef _Search_Tree_H
#define _Search_Tree_H
struct TreeNode;
typedef struct TreeNode TreeNode;
typedef struct TreeNode* SearchTRee;
typedef struct TreeNode* Position;
#endif


typedef enum ERorateDir{
    ROTATE_L = 1,
    ROTATE_R,
}ERorateDir;


struct TreeNode {
    int elem;
    int count; /**< 一个节点相同元素计数 */
    int height; ///< 树的高度
    struct TreeNode* left;
    struct TreeNode* right;
};


void releaseSTree(TreeNode* t){
    if (!t){
        TreeNode* left = (t)->left;
        TreeNode* right = (t)->right;
        free(t);
        releaseSTree(left);
        releaseSTree(right);
    }
}


Position singleRotate(Position k, ERorateDir dir){
    Position k1;
    if (dir == ROTATE_L){
        k1 = k->left;
        k->left = k1->right;
        k1->right = k;
    }else if (dir == ROTATE_R){
        k1 = k->right;
        k->right = k1->left;
        k1->left = k;
    }
    k->height = fmax(k->left->height, k->right->height) + 1;
    k1->height = fmax(k1->left->height, k1->right->height) + 1;
    return k1;
}


Position doubleRotateWithLeft(Position k){
    k->left = singleRotate(k->left, ROTATE_R);
    return singleRotate(k, ROTATE_L);
}


Position doubleRotateWithRight(Position k){
    k->right = singleRotate(k->right, ROTATE_L);
    return singleRotate(k, ROTATE_R);
}

/**
 * @brief 
 * 
 * @param tree 
 * @param x 
 * @return TreeNode*，新树的root节点
 */
TreeNode* insert(TreeNode* tree, int x){
    if (!tree){
        TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
        if (!tree){
            perror("error");
            tree = NULL;
        }
        tree->elem = x;
        tree->count = 1;
        tree->height = 0;
        tree->left = NULL;
        tree->right = NULL;
    }else {
        if (x < tree->elem){
            tree->left = insert(tree->left, x);
            /* 插入之后判断是否需要调整平衡 */
            if (tree->left - tree->right == 2){
                /* L-L型 */
                if (x < tree->left->elem){
                    tree->left = singleRotate(tree->left, ROTATE_L);
                /* L-R型 */
                }else if (x > tree->left->elem){
                    tree->right = doubleRotateWithLeft(tree->right);
                }
            }
        }else if (x > tree->elem){
            tree->right = insert(tree->right, x);
            /* 插入之后判断是否需要调整平衡 */
            if (tree->right - tree->left == 2){
                /* R-R型 */
                if (x > tree->left->elem){
                    tree->right = singleRotate(tree->right, ROTATE_R);
                /* R-L型 */
                }else if (x < tree->left->elem){
                    tree->right = doubleRotateWithRight(tree->right);
                }
            }
        }else{
            ++ tree->count;
            return tree;
        }
    }
    tree->height = fmax(tree->left->height, tree->right->height) + 1;
    return tree;
}

TreeNode* find(TreeNode* tree, int x){
    if (!tree){
        return NULL;
    }
    if (x == tree->elem){
        return tree;
    }else if (x < tree->elem){
        return find(tree->left, x);
    }else {
        return find(tree->right, x);
    }
}

TreeNode* findMin(TreeNode* tree){
    if (!tree){
        return NULL;
    }
    if (!tree->left){
        return tree;
    }else {
        return findMin(tree->left);
    }
}

TreeNode* findMax(TreeNode* tree){
    if (!tree){
        return NULL;
    }
    if (!tree->right){
        return tree;
    }else {
        return findMax(tree->right);
    }
}

/**
 * @brief 
 * 
 * @param tree 
 * @param x 
 * @return TreeNode* ,新树的root节点
 */


TreeNode* 
delete(tree, x)
TreeNode* tree;int x;
{
    if (!tree)
    {
        return NULL;
    }
    if (x < tree->elem)
    {
        tree->left = delete(tree->left, x);
        if (tree->right->height - tree->left->height == 2)
        {
            Position tmpTree = tree->right;
            /* x是删除的元素,删除后O是最小不平衡子树的root
                O
              /   \
             x     o
                 /
                o
            */
            /* 双旋转 */
            if (tmpTree->left->height > tmpTree->right->height)
            {
                tree = doubleRotateWithRight(tree);
            }
            /* 
                O                       O   
              /   \                   /   \
             x     o         或者    x     o
                    \                    /  \
                     o                  o    o
            */
            /* 单旋转 */
            else
            {
                tree = singleRotate(tree, ROTATE_R);
            }
        }
    }
    else if (x > tree->elem)
    {
        tree->right = delete(tree->right, x);
        if (tree->left->height - tree->right->height == 2)
        {
            Position tmpTree = tree->left;
            /* x是删除的元素
                   O
                 /   \
                o     x
                 \
                  o
            */
            /* 双旋转 */
            if (tmpTree->right->height > tmpTree->left->height)
            {
                tree = doubleRotateWithLeft(tree);
            }
            else
            {
                tree = singleRotate(tree, ROTATE_L);
            }
        }
    }
    else 
    {
        /* 左右子树都存在 */
        if (tree->left && tree->right)
        {
            if (tree->count > 1)
            {
                --tree->count;
            }
            else
            {
                // 从高的子树中找到元素替换将要删除的节点位置，保证左右子树是平衡的
                if (tree->left->height > tree->right->height)
                {
                    TreeNode* tmp = findMax(tree->left);
                    tree->elem = tmp->elem;
                    tree->count -= tmp->count;
                    /* 删除移动了元素的节点 */
                    tree->left = delete(tree->left, tmp->elem);
                }
                else
                {
                    /* 在右子树中找到最小的值，也就是左子树是空的节点，将它移到将要删除的节点位置 */
                    TreeNode* tmp = findMin(tree->right);
                    tree->elem = tmp->elem;
                    tree->count -= tmp->count;
                    /* 删除移动了元素的节点 */
                    tree->right = delete(tree->right, tmp->elem);
                }
            }
        
        }
        /* 只存在一个子树,或者不存在子树 */
        else 
        {
            TreeNode* tmpNode = tree;
            if (!tree->left)
            {
                /* 如果两个子树都是空，将right给tree也没问题，因为right就是NULL */
                tree = tree->right;
            }
            else if (!tree->right)
            {
                tree = tree->left;
            }
            free(tmpNode);
        }
    }
    tree->height = fmax(tree->left->height, tree->right->height) + 1;
    return tree;
}