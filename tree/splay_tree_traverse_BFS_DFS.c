/**
 * @file splay_tree_traverse_BFS_DFS.c
 * @author your name (you@domain.com)
 * @brief 实现伸展树,实现队列和栈用于广度优先遍历和深度优先遍历
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct BinTreeNode
{
    int val;
    int count; /**< 相同元素计数 */
    struct BinTreeNode* left;
    struct BinTreeNode* right;
} BinTreeNode;


/*********************************************************
 * 使用链表实现stack用于深度优先搜索
 ********************************************************/
typedef struct ListNode
{
    BinTreeNode* bin_tree_node;
    struct ListNode *next;
} ListNode;

typedef struct ListNode* Stack;

int is_empty(Stack stack)
{
    return stack == NULL;
}


int push_stack(Stack* stack, BinTreeNode* tree_node)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->next = NULL;
    node->bin_tree_node = tree_node;
    if (!node)
    {
        printf("out of memory\n");
        return -1;
    }
    if (!*stack)
    {
        *stack = node;
        return 0;
    }
    node->next = *stack;
    *stack = node;
    return 0;
}

BinTreeNode* pop_stack(Stack* stack)
{
    if (*stack)
    {
        ListNode* backup = *stack;
        BinTreeNode* ret = (*stack)->bin_tree_node;
        *stack = (*stack)->next;
        free(backup);
        return ret;
    }
    else
    {
        return NULL;
    }
}

void make_stack_empty(Stack* stack)
{
    while (stack)
    {
        ListNode* backup;
        backup = *stack;
        *stack = (*stack)->next;
        free(backup);
    }
}

BinTreeNode* get_top_elem(Stack stack)
{
    if (stack)
    {
        return stack->bin_tree_node;
    }
}


/****************************
 * 实现队列用于广度优先算法
 ***************************/
typedef struct Queue
{
    ListNode* front;
    ListNode* rear;
} Queue;


void enqueue(Queue* queue, BinTreeNode* tree_node)
{
    if (!queue)
    {
        printf("error queue is NULL\n");
        return;
    }
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->bin_tree_node = tree_node;
    node->next = NULL;
    if (!queue->rear)
    {
        queue->rear = node;
        queue->front = queue->rear;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}

BinTreeNode* dequeue(Queue* queue)
{
    if (!queue)
    {
        printf("error: queue does not exist\n");
        return NULL;
    }
    if (!queue->front)
    {
        printf("error: queue is empty\n");
        return NULL;
    }
    else
    {
        ListNode* list_node = queue->front;
        BinTreeNode* tree_node = list_node->bin_tree_node;
        if (queue->front == queue->rear)
        {
            queue->front = queue->rear = NULL;
        }
        else
        {
            queue->front = queue->front->next;
        }
        free(list_node);
        return tree_node;
    }
}


/*******************************************
 *  实现伸展树 
 *******************************************/
typedef struct BinTreeNode* SplayTree;
typedef struct BinTreeNode* Position;


/**
 * @brief 插入操作就跟二叉搜索树插入一样，不做平衡操作
 * 
 * @param splay_tree 
 * @param x 
 * @return SplayTree 
 */
void insert(SplayTree* root, int x)
{
    BinTreeNode* node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (!node)
    {
        return;
    }
    node->val = x;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    if (!*root)
    {
        *root = node;
        return;
    }
    SplayTree pos = *root;
    while (1)
    {
        if (x < pos->val)
        {
            if (pos->left)
            {
                pos = pos->left;
            }
            else
            {
                pos->left = node;
                break;
            }
        }
        else if (x > pos->val)
        {
            if (pos->right)
            {
                pos = pos->right;
            }
            else
            {
                pos->right = node;
                break;
            }

        }
        else
        {
            if (pos->val == x)
            {
                ++pos->count;
                break;
            }
        }
    }
}


/**
 * @brief 二叉查找树的查找操作
 * 
 * @param root 
 * @param x 
 * @return Position 
 */
Position find_search_tree(SplayTree root, int x)
{
    if (!root)
    {
        printf("error:not found\n");
        return NULL;
    }
    if (x < root->val)
    {
        return find_search_tree(root->left, x);
    }
    else if (x > root->val)
    {
        return find_search_tree(root->right, x);
    }
    else
    {
        return root;
    }
}


Position find_max(SplayTree root)
{
    if (!root)
    {
        return root;
    }
    if (root->right)
    {
        return root;
    }
    else
    {
        return find_max(root->right);
    }
}


Position find_min(SplayTree root)
{
    if (!root)
    {
        return root;
    }
    if (!root->left)
    {
        return root;
    }
    else
    {
        return find_min(root->left);
    }
}

/**
 * @brief 删除元素，删除操作跟二叉查找树的删除一致
 * 为了保持删除元素后的树依然是查找树，需要将删除节点的左子树的最大值
 * 或者右子树中的最小值移动到删除的地方，移动有两种方案：
 * 1. 仅移动链表节点中的值
 * 2. 移动链表的节点
 * 这里使用第1种方案, 第2种有点麻烦
 * @param root 
 * @param x 
 * @return Position 
 */
Position delete(SplayTree root, int x)
{
    if (!root)
    {
        printf("error:not found\n");
        return root;
    }
    if (x < root->val)
    {
        root->left = delete(root->left, x);
    }
    else if (x > root->val)
    {
        root->right = delete(root->right, x);
    }
    else
    {
        if (root->left && root->right)
        {
            if (root->count >= 2)
            {
                --root->count;
            }
            else
            {
                Position tmp = find_min(root->right);
                root->val = tmp->val;
                root->count = tmp->count;
                root->right = delete(root->right, tmp->val);
            }
        }
        else
        {
            Position tmp = root;
            if (!root->left)
            {
                root = root->right;
            }
            else if (!root->right)
            {
                root = root->left;
            }
            free(tmp);
        }
    }
    return root;
}

/**
 * @brief 清空树，释放内存
 * 
 * @param root 
 * @return Position 
 */
Position delete_all(SplayTree root)
{
    if (root)
    {
        if (root->left)
        {
            root->left = delete_all(root->left);
        }
        if (root->right)
        {
            root->right =  delete_all(root->right);
        }
        if (!root->left && !root->right)
        {
            free(root);
            return NULL;
        }
    }
}


Position splay_left_left(Position g, Position p, Position cur)
{
    g->left = p->right;
    p->left = cur->right;
    p->right = g;
    cur->right = p;
    return cur;
}


Position splay_left_right(Position g, Position p, Position cur)
{
    /* cur跟p互换 */
    p->right = cur->left;
    cur->left = p;
    g->left = cur;
    /* cur跟g互换 */
    g->left = cur->right;
    cur->right = g;
    return cur;
}


Position splay_right_left(Position g, Position p, Position cur)
{
    /* cur跟p互换 */
    p->left = cur->right;
    cur->right = p;
    g->right = cur;
    /* cur跟g互换 */
    g->left = cur->left;
    cur->left = g;
    return cur;
}


Position splay_right_right(Position g, Position p, Position cur)
{
    g->right = p->left;
    p->right = cur->left;
    p->left = g;
    cur->left = p;
    return cur;
}

Position rotate_left(Position p, Position cur)
{
    p->left = cur->right;
    cur->right = p;
    return cur;
}

Position rotate_right(Position p, Position cur)
{
    p->right = cur->left;
    cur->left = p;
    return cur;
}

/**
 * @brief 伸展树的查找操作要求将找到的元素伸展到根节点
 * 
 * @param cur_pos 
 * @param x 
 * @return Position 
 */
Position find(SplayTree cur_pos, int x)
{
    if (!cur_pos)
    {
        return NULL;
    }
    Stack stack = NULL;
    while (1)
    {
        if (x < cur_pos->val)
        {
            if (cur_pos->left)
            {
                push_stack(&stack, cur_pos);
                cur_pos = cur_pos->left;
            }
            else
            {
                printf("error:not found\n");
                return NULL;
            }
        }
        else if (x > cur_pos->val)
        {
            if (cur_pos->right)
            {
                push_stack(&stack, cur_pos);
                cur_pos = cur_pos->right;
            }
            else
            {
                printf("error:not found\n");
                return NULL;
            }
        }
        else
        {
            printf("find it\n");
            Position p, q, r;
            p = pop_stack(&stack);
            q = pop_stack(&stack);
            r = pop_stack(&stack);
            /* 找到元素后通过伸展将元素放到根节点*/
            while (1)
            {
                /* 栈里没有元素，那么cur_pos就是根节点 */
                if (!p && !q && !r)
                {
                    break;
                }
                /* 说明当前cur_pos变量保存的节点的父节点是根节点,旋转一次就行 */
                if (p && !q && !r)
                {
                    if (p->left == cur_pos)
                    {
                        cur_pos = rotate_right(p, cur_pos);
                    }
                    else
                    {
                        cur_pos = rotate_left(p, cur_pos);
                    }
                    break;
                }
                /* zig-zig模式 */
                if (q->left == p && p->left == cur_pos)
                {
                    cur_pos = splay_left_left(q, p ,cur_pos);
                }
                else if (q->right == p && p->right == cur_pos)
                {
                    cur_pos = splay_right_right(q, p ,cur_pos);
                }
                /* zig-zag模式 */
                else if (q->left == p && p->right == cur_pos)
                {
                    cur_pos = splay_left_right(q, p ,cur_pos);
                }
                else if (q->right == p && p->left == cur_pos)
                {
                    cur_pos = splay_right_left(q, p, cur_pos);
                }

                if (!r)
                {
                    break;
                }
                if (r->left == q)
                {
                    r->left = cur_pos;
                }
                else
                {
                    r->right = cur_pos;
                }
                p = r;
                q = pop_stack(&stack);
                r = pop_stack(&stack);
            }
            return cur_pos;
        }
    }

}

/**
 * @brief 随机生成一棵二叉查找树
 * 
 * @param size 
 * @return SplayTree 
 */
SplayTree make_random_bin_tree(int size)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned int)(tv.tv_usec));
    SplayTree tree = NULL;
    printf("[random:]");
    while (size--)
    {
        int x = rand() % 100;
        printf("%d ", x);
        insert(&tree, x);
    }
    printf("\n");
    return tree;
}

/**
 * @brief 深度优先遍历(后序遍历)
 * 
 * @param root 
 */
void traverse_DFS(SplayTree root)
{
    Stack stack = NULL;
    int ret = push_stack(&stack, root);
    if (ret < 0)
    {
        printf("push_stack error\n");
        return;
    }
    while (!is_empty(stack))
    {
        BinTreeNode* ret = pop_stack(&stack);
        if (!ret)
        {
            printf("error:ret is NULL\n");
        }
        printf("%d ", ret->val);
        if (ret->right)
        {
            push_stack(&stack, ret->right);
        }
        if (ret->left)
        {
            push_stack(&stack, ret->left);
        }
    }

}


int is_empty_queue(Queue* queue)
{
    return queue->front == queue->rear && queue->front == NULL;
}


/**
 * @brief 广度优先遍历(层序遍历)
 * 
 * @param root 
 */
void traverse_BFS(SplayTree root)
{
    Queue queue = {0};
    enqueue(&queue, root);
    int level = 0;
    while (!is_empty_queue(&queue))
    {
        BinTreeNode* node = dequeue(&queue);
        printf("%d ", node->val);
        if (node->left)
        {
            enqueue(&queue, node->left);
        }
        if (node->right)
        {
            enqueue(&queue, node->right);
        }
    }
}

/**
 * @brief 前序遍历
 * 
 * @param root 
 * @param level 
 */
void pre_order_traverse(SplayTree root, int level)
{
    if (root)
    {
        printf("%d-%d ", level, root->val);
        pre_order_traverse(root->left, level + 1);
        pre_order_traverse(root->right, level + 1);
    }
}

/**
 * @brief 中序遍历
 * 
 * @param root 
 * @param level 
 */
void in_order_traverse(SplayTree root, int level)
{
    if (root)
    {
        in_order_traverse(root->left, level + 1);
        printf("%d-%d ", level, root->val);
        in_order_traverse(root->right, level + 1);
    }

}


/**
 * @brief 后序遍历
 * 
 * @param root 
 * @param level 
 */
void post_order_traverse(SplayTree root, int level)
{
    if (root)
    {
        post_order_traverse(root->left, level + 1);
        post_order_traverse(root->right, level + 1);
        printf("%d-%d-%p ", level, root->val, root);
    }
}


int main(void)
{
    //SplayTree root = make_random_bin_tree(10);
    int arr[] = {32,50,2,84,69,98,73,62,20,9};
    int i = 0;
    SplayTree root = NULL;
    for (i = 0; i < sizeof(arr)/sizeof(int); ++i)
    {
        insert(&root, arr[i]);
    }
    root = find(root, 73);
    printf("--%p--\n", find_search_tree(root, 62));
    delete(root, 50);
    printf("---------------------\n");
    pre_order_traverse(root, 0);
    printf("\n");
    in_order_traverse(root, 0);
    printf("\n");
    post_order_traverse(root, 0);
    printf("\n");
    traverse_DFS(root);
    printf("\n");
    traverse_BFS(root);
    delete_all(root);
    return 0;
}