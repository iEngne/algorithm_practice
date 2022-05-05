/**
 * @file AVLTree.c
 * @author your name (you@domain.com)
 * @brief 实现AVL树
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



int height(Position root)
{
    if (!root)
    {
        printf("Line:%d, error:node does not exist\n", __LINE__);
        return -1;
    }
    if (root->left && root->right)
    {
        return fmax(root->left->height, root->right->height) + 1;
    }
    else if (root->left && !root->right)
    {
        return root->left->height + 1;
    }
    else if (!root->left && root->right)
    {
        return root->right->height + 1;
    }
    else
    {
        return 0;
    }
}


int height_lr_diff(Position root)
{
    if (root->right && root->left)
    {
        return root->left->height > root->left->height? \
               root->left->height - root->right->height: \
               root->right->height - root->left->height;
    }
    else if (root->left && !root->right)
    {
        return root->left->height + 1;
    }
    else if (!root->left && root->right)
    {
        return root->right->height + 1;
    }
    else
    {
        return 0;
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
    k->height = height(k);
    k1->height = height(k1);
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
 * @brief 插入操作，插入后做平衡调整
 * 
 * @param tree 
 * @param x 
 * @return TreeNode*，新树的root节点
 */
TreeNode* insert(TreeNode* tree, int x){
    if (!tree){
        tree = (TreeNode*)malloc(sizeof(TreeNode));
        if (!tree){
            printf("error:out of memory\n");
            return NULL;
        }
        tree->elem = x;
        tree->count = 1;
        tree->height = 0;
        tree->left = NULL;
        tree->right = NULL;
    }else {
        int diff_height;
        if (x < tree->elem){
            tree->left = insert(tree->left, x);
            diff_height = height_lr_diff(tree);
            /* 插入之后判断是否需要调整平衡 */
            if (diff_height == 2){
                /* L-L型 */
                if (x < tree->left->elem){
                    tree = singleRotate(tree, ROTATE_L);
                /* L-R型 */
                }else if (x > tree->left->elem){
                    tree = doubleRotateWithLeft(tree);
                }
            }
        }else if (x > tree->elem){
            tree->right = insert(tree->right, x);
            diff_height = height_lr_diff(tree);
            /* 插入之后判断是否需要调整平衡 */
            if (diff_height == 2){
                /* R-R型 */
                if (x > tree->right->elem){
                    tree = singleRotate(tree, ROTATE_R);
                /* R-L型 */
                }else if (x < tree->right->elem){
                    tree = doubleRotateWithRight(tree);
                }
            }
        }else{
            ++ tree->count;
            return tree;
        }
    }
    tree->height = height(tree);
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
 * @brief AVL树的删除，删除后需要做调整平衡
 * 
 * @param tree 
 * @param x 
 * @return TreeNode* ,新树的root节点
 */
TreeNode* 
delete(root, x)
TreeNode* root;int x;
{
    if (!root)
    {
        printf("Lline:%d, error: node does not exist\n", __LINE__);
        return NULL;
    }
    int height_diff;
    if (x < root->elem)
    {
        root->left = delete(root->left, x);
        height_diff = height_lr_diff(root);
        /* 1.如果被删除的元素不是叶子节点，是去高的子树中去找的替代的叶子节点，
        然后删除叶子节点。
        2.如果本来要删除的就是叶子节点，那跟上面的后半部分动作一致。
        所以只有叶子节点被删除之后才会需要调整 */
        if (height_diff == 2)
        {
            /* x是删除的元素,删除后O是最小不平衡子树的root
                O
              /   \
             x     o
                  /
                 o
            */
            /* 这种情况必须用双旋转，单旋转不能改变深度 */
            if (!root->right->right)
            {
                root = doubleRotateWithRight(root);
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
                root = singleRotate(root, ROTATE_R);
            }
        }
    }
    else if (x > root->elem)
    {
        root->right = delete(root->right, x);
        height_diff = height_lr_diff(root);
        if (height_diff == 2)
        {
            /* x是删除的元素,删除后O是最小不平衡子树的root
                   O
                 /   \
                o     x
                 \
                  o
            */
            /* 这种情况必须用双旋转，单旋转不能改变深度 */
            if (!root->left->left)
            {
                root = doubleRotateWithLeft(root);
            }
            /*       O                  O
                   /   \              /   \
                  o     x   或者     o     x
                /   \               /
               o     o             o
           */
            else
            {
                root = singleRotate(root, ROTATE_L);
            }
        }
    }
    else 
    {
        /* 左右子树都存在 */
        if (root->left && root->right)
        {
            if (root->count > 1)
            {
                --root->count;
            }
            else
            {
                // 从高的子树中找到元素替换将要删除的节点位置，保证左右子树是平衡的
                if (root->left->height > root->right->height)
                {
                    /* 在左子树中找到最大的值，也就是左子树是空的节点，将它移到将要删除的节点位置 */
                    TreeNode* tmp = findMax(root->left);
                    root->elem = tmp->elem;
                    root->count -= tmp->count;
                    /* 删除移动了元素的节点 */
                    root->left = delete(root->left, tmp->elem);
                }
                else
                {
                    /* 在右子树中找到最小的值，也就是左子树是空的节点，将它移到将要删除的节点位置 */
                    TreeNode* tmp = findMin(root->right);
                    root->elem = tmp->elem;
                    root->count -= tmp->count;
                    /* 删除移动了元素的节点 */
                    root->right = delete(root->right, tmp->elem);
                }
            }
        
        }
        /* 只存在一个子树,或者不存在子树 */
        else 
        {
            TreeNode* tmpNode = root;
            if (!root->left)
            {
                /* 如果两个子树都是空，将right给root也没问题，因为right就是NULL */
                root = root->right;
            }
            else if (!root->right)
            {
                root = root->left;
            }
            free(tmpNode);
        }
    }
    if (root)
    {
        root->height = height(root);
    }
    return root;
}


/**
 * @brief 前序遍历
 * 
 * @param root 
 * @param level 
 */
void pre_order_traverse(SearchTRee root, int level)
{
    if (root)
    {
        printf("%d-%d ", level, root->elem);
        pre_order_traverse(root->left, level + 1);
        pre_order_traverse(root->right, level + 1);
    }
}


int main(void)
{
    int arr[] = {32,50,2,84,69,98,73,62,20,9};
    SearchTRee root = NULL;
    int i;
    for (i = 0; i < sizeof(arr)/sizeof(int); ++i)
    {
        root = insert(root, arr[i]);
        pre_order_traverse(root, 0);
        printf("\n");
    }
    pre_order_traverse(root, 0);
    printf("\n");

    root = delete(root, 50);
    pre_order_traverse(root, 0);
    printf("\n");

    root = delete(root, 32);
    pre_order_traverse(root, 0);
    printf("\n");

    root = delete(root, 62);
    pre_order_traverse(root, 0);
    printf("\n");

    releaseSTree(root);
    return 0;
}