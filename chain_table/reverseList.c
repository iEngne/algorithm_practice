

/**
反转链表
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 

示例 1：


输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例 2：


输入：head = [1,2]
输出：[2,1]
示例 3：

输入：head = []
输出：[]
 

提示：

链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000
 

进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnnhm6/
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

struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* reverseList(struct ListNode* head){
    struct ListNode* p = NULL;
    struct ListNode* q = NULL;
    for (;head;){
        q = head->next;
        head->next = p;
        p = head;
        head = q;
    }
    return p;
}

struct ListNode* reverseList_1(struct ListNode* head){
    struct ListNode * p = NULL;
    struct ListNode* newHead = NULL;
    for (;head;){
        p = head;
        head = head->next;
        p->next = newHead;
        newHead = p;
    }
    return newHead;
}