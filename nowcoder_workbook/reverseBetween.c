/*
描述
将一个节点数为 size 链表 m 位置到 n 位置之间的区间反转，要求时间复杂度 O(n)O(n)，空间复杂度 O(1)O(1)。
例如：
给出的链表为 1\to 2 \to 3 \to 4 \to 5 \to NULL1→2→3→4→5→NULL, m=2,n=4m=2,n=4,
返回 1\to 4\to 3\to 2\to 5\to NULL1→4→3→2→5→NULL.

数据范围： 链表长度 0 < size \le 10000<size≤1000，0 < m \le n \le size0<m≤n≤size，链表中每个节点的值满足 |val| \le 1000∣val∣≤1000
要求：时间复杂度 O(n)O(n) ，空间复杂度 O(n)O(n)
进阶：时间复杂度 O(n)O(n)，空间复杂度 O(1)O(1)
示例1
输入：
{1,2,3,4,5},2,4
复制
返回值：
{1,4,3,2,5}
复制
示例2
输入：
{5},1,1
复制
返回值：
{5}
*/
#include <stdio.h>
#include <stdlib.h>


struct ListNode {
int val;
struct ListNode *next;
};
/*
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */
/**
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 * 
 * @param head ListNode类 
 * @param m int整型 
 * @param n int整型 
 * @return ListNode类
 */
struct ListNode* reverseBetween(struct ListNode* head, int m, int n ) {
    // write code here
    struct ListNode* headS = head;
    struct ListNode* headE = head;
    struct ListNode* headSPre = NULL;
    struct ListNode* headEN = NULL;
    // 找到要反转的链表的头
    for (; m > 1; --m)
    {
        headSPre = headS;
        headS = headS->next;
    }
    // 找到要反转的链表的尾
    for (; n > 1; --n)
    {
        headE = headE->next;
    }
    headEN = headE->next;
    struct ListNode* SubHeadNew = headEN;
    struct ListNode* headTmp = NULL;
    int i = 0;
    while (headS != headEN)
    {
        headTmp = headS->next;
        headS->next = SubHeadNew;
        SubHeadNew = headS;
        headS = headTmp;
    }
    /* 如果headSPre非空说明要反转的子链表不是从第一个开始的，
    ** 反转后要接回去
    */
    if (headSPre)
    {
        headSPre->next = SubHeadNew;
    }
    else
    {
        head = SubHeadNew;
    }
    return head;
}


int main(void)
{
    int i = 0;
    struct ListNode* head = NULL;
    struct ListNode* headTmp = NULL;
    for (i = 5; i > 0; --i)
    {
        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = i;
        node->next = head;
        head = node;
    }
    headTmp = head;
    while (headTmp)
    {
        headTmp = headTmp->next;
    }
    struct ListNode* newHead = reverseBetween(head, 1, 5);
    head = newHead;

    while (head)
    {
        head = head->next;
    }
    while (newHead)
    {
        struct ListNode* tmp = newHead->next;
        free(newHead);
        newHead = tmp;
    }
    return 0;
}





