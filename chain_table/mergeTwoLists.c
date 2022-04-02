/**
合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

 

示例 1：


输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：

输入：l1 = [], l2 = []
输出：[]
示例 3：

输入：l1 = [], l2 = [0]
输出：[0]
 

提示：

两个链表的节点数目范围是 [0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按 非递减顺序 排列
相关标签
递归
链表

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnnbp2/
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

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    if (!list1) return list2;
    if (!list2) return list1;
    struct ListNode* head = NULL;
    if (list1->val < list2->val){
        head = list1;
        list1 = list1->next;
    }
    else{
        head = list2;
        list2 = list2->next;
    }
    struct ListNode* tail = head;
    for (;list1&&list2;){
        if (list1->val <= list2->val){
            tail->next = list1;
            tail = tail->next;
            list1 = list1->next;
        }else {
            tail->next = list2;
            tail = tail->next;
            list2 = list2->next;
        }
    }
    if (list1){
        tail->next = list1;
    }else if (list2){
        tail->next = list2;
    }
    return head;
}