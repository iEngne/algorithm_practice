/**
回文链表
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

 

示例 1：


输入：head = [1,2,2,1]
输出：true
示例 2：


输入：head = [1,2]
输出：false
 

提示：

链表中节点数目在范围[1, 105] 内
0 <= Node.val <= 9
 

进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

相关标签
栈
递归
链表
双指针

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnv1oc/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


bool isPalindrome(struct ListNode* head){
    struct ListNode* p = head;
    struct ListNode* newHead = NULL;
    int n = 1;
    for (;p->next;){
        p = p->next;
        ++n;
    }
    int i = 0;
    for (; i < n/2; ++i){
        p = head;
        head = head->next;
        p->next = newHead;
        newHead = p;
    }
    if (n % 2 == 1){
        head = head->next;
    }
    for (;head;){
        if (head->val != newHead->val){
            return false;
        }
        head = head->next;
        newHead = newHead->next;
    }
    return true;
}
