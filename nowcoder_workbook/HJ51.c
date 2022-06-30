/**
 * @file HJ51.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-28
点击提交题解，有机会获得牛币或京东卡

HJ51 输出单向链表中倒数第k个结点
题目
题解(182)
讨论(352)
排行
面经new
简单  通过率：29.26%  时间限制：1秒  空间限制：32M
知识点
链表
双指针
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
输入一个单向链表，输出该链表中倒数第k个结点，链表的倒数第1个结点为链表的尾指针。

链表结点定义如下：
struct ListNode
{
    int m_nKey;
    ListNode* m_pNext;
};
正常返回倒数第k个结点指针，异常返回空指针.
要求：
(1)正序构建链表;
(2)构建后要忘记链表长度。
数据范围：链表长度满足 1 \le n \le 1000 \1≤n≤1000  ， k \le n \k≤n  ，链表中数据满足 0 \le val \le 10000 \0≤val≤10000 

本题有多组样例输入。


输入描述：
输入说明
1 输入链表结点个数
2 输入链表的值
3 输入k的值

输出描述：
输出一个整数

示例1
输入：
8
1 2 3 4 5 6 7 8
4
复制
输出：
5
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct ListNode {
    int m_nkey;
    struct ListNode* m_pNext;
} ListNode;


ListNode* makeList(ListNode* head, int val) {
    if (!head) {
        head = (ListNode*)malloc(sizeof(ListNode));
        head->m_pNext = NULL;
        head->m_nkey = val;
    } else {
        ListNode* cur = head;
        while(cur->m_pNext) {
            cur = cur->m_pNext;
        }
        cur->m_pNext = malloc(sizeof(ListNode));
        cur->m_pNext->m_pNext = NULL;
        cur->m_pNext->m_nkey = val;
    }
    return head;
}

ListNode* findKElem(ListNode* head, int k, int* count) {
    if (!head) {
        *count = 0;
        return NULL;
    } else {
        ListNode* cur = findKElem(head->m_pNext, k, count);
        *count += 1;
        if (*count == k) {
            return head;
        }
        return cur;
    }  
}


void fflushStdin(void) {
    scanf("%*[^\n]");
    scanf("%*c"); 
}

void releaseList(ListNode* head) {
    ListNode* cur = NULL;
    while (head) {
        cur = head;
        head = head->m_pNext;
        free(cur);
    }
}

void findKthNode(void) {
    int n, k;
    int vals[1002];
    scanf("%d", &n);
    fflushStdin();
    int i = 0;
    for (i = 0; i < n; ++i) {
        scanf("%d", &vals[i]);
    }
    fflushStdin();
    scanf("%d", &k);
    fflushStdin();
    int count = 0;
    ListNode* head = NULL;
    for (i = 0; i < n; ++i) {
            head = makeList(head, vals[i]); 
    }
    ListNode* kElem = findKElem(head, k, &count);
    if (kElem) {
        printf("--%d\n", kElem->m_nkey);
    }
    releaseList(head);
}


typedef struct Group {
    int n;
    int vals[1000];
    int k;
} Group;


void getKthElem(Group* group) {
    int i = 0;
    int j = 0;
    ListNode* head = NULL;
    for (i = 0; group[i].n > 0; ++i) {
        for (j = 0; j < group[i].n; ++j) {
            head = makeList(head, group[i].vals[j]);
        }
        int count = 0;
        ListNode* kElem = findKElem(head, group[i].k, &count);
        if (kElem) {
            printf("==%d\n", kElem->m_nkey);
        }
        releaseList(head);
        head = NULL;
    }
}


int main(void) {
    int n = 0;
    int vals[1000] = {0};
    int k = 0;
    Group group[10] = {0};
    fd_set rFds;
    fd_set rFdsBak;
    FD_ZERO(&rFds);
    int fd = 0;
    findKthNode();
    // int i = 0;
    // while (1) {
    //     FD_ZERO(&rFds);
    //     FD_SET(fd, &rFds);
    //     struct timeval tv = {6, 10000};
    //     int ret = select(fd+1, &rFds, NULL, NULL, &tv);
    //     if (ret < 0) {
    //         printf("select error\n");
    //         break;
    //     } else if (ret == 0) {
    //         printf("out of time\n");
    //         break;
    //     } else {
    //         if FD_ISSET(0, &rFds) {
    //             printf("start to read\n");
    //             scanf("%d", &group[i].n);
    //             getchar();
    //             int j = 0;
    //             for (j = 0; j < group[i].n; ++j) {
    //                 scanf("%d", &group[i].vals[j]);
    //             }
    //             getchar();
    //             scanf("%d", &group[i].k);
    //             getchar();
    //             ++i;
    //         }
    //     }
    // }
    // getKthElem(group);
    return 0;
}