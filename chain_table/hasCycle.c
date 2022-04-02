/**
环形链表
给你一个链表的头节点 head ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。

如果链表中存在环 ，则返回 true 。 否则，返回 false 。

 

示例 1：



输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：



输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：



输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
 

提示：

链表中节点的数目范围是 [0, 104]
-105 <= Node.val <= 105
pos 为 -1 或者链表中的一个 有效索引 。
 

进阶：你能用 O(1)（即，常量）内存解决此问题吗？
相关标签
哈希表
链表
双指针
作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnwzei/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include "stdio.h"
#include "uthash/src/uthash.h"
#include "stdbool.h"

 struct ListNode {
     int val;
     struct ListNode *next;
 };

typedef struct HashTable {
    struct ListNode *p;
    UT_hash_handle hh;
} HashTable;


void deleteAll(HashTable* nodes){
    HashTable *cur, *tmp;

    HASH_ITER(hh, nodes, cur, tmp) {
        HASH_DEL(nodes, cur);  /* delete; users advances to next */
        free(cur);             /* optional- if you want to free  */
    }
}

bool hasCycle(struct ListNode *head) {
    HashTable* nodes = NULL;
    HashTable* node = NULL;
    for (;head;head = head->next){
        HASH_FIND(hh, nodes, &head, sizeof(head), node);
        if (!node){
            node = (HashTable*)malloc(sizeof(HashTable));
            node->p = head;
            HASH_ADD(hh, nodes, p, sizeof(node->p), node);
        }else{
            deleteAll(nodes);
            return true;
        }
    }
    deleteAll(nodes);
    return false;
}

bool hasCycle_1(struct ListNode *head) {
    if (!head){
        return false;
    }
    if (head == head->next){
        return true;
    }
    struct ListNode* tmp = head;
    head->next = head;
    head = tmp->next;
    return hasCycle_1(head);
}

// 递归逐个删除，并将删除元素的next指向自己
bool hasCycle_2(struct ListNode *head) {
    //如果head为空，或者他的next指向为空，直接返回false
    if (head == NULL || head->next == NULL)
        return false;
    //如果出现head.next = head表示有环
    if (head->next == head)
        return true;
    struct ListNode* nextNode = head->next;
    //当前节点的next指向他自己，相当于把它删除了
    head->next = head;
    //然后递归，查看下一个节点
    return hasCycle_2(nextNode);
}


struct ListNode* reverseList(struct ListNode* head) {
    //新链表
    struct ListNode* newHead = NULL;
    while (head != NULL) {
        //先保存访问的节点的下一个节点，保存起来
        //留着下一步访问的
        struct ListNode* temp = head->next;
        //每次访问的原链表节点都会成为新链表的头结点，
        //其实就是把新链表挂到访问的原链表节点的
        //后面就行了
        head->next = newHead;
        //更新新链表
        newHead = head;
        //重新赋值，继续访问
        head = temp;
    }
    //返回新链表
    return newHead;
}

bool hasCycle3(struct ListNode* head) {
    struct ListNode* rev = reverseList(head);
    if (head != NULL && head->next != NULL && rev == head) {
        return true;
    }
    return false;
}


int main(void){
    int i = 0;
    struct ListNode* head = NULL;
    struct ListNode* tmp = NULL;
    for (; i < 10; ++i){
         struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
         node->val = i;
         node->next = head;
         if (i == 4){
             tmp = node;
         }
         head = node;
    }
    struct ListNode* p = head;
    for (;p->next;){
        p = p->next;
    }
     p->next = tmp;
    printf("%d:\n",hasCycle_2(head));
    for(i = 0; i < 10; ++i){
        tmp = head->next;
        free(head);
        head = tmp;
    }
    return 0;
}