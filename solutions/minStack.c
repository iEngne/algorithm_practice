/**
 * @file minStack.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
最小栈
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。
 

示例 1:

输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
 

提示：

-231 <= val <= 231 - 1
pop、top 和 getMin 操作总是在 非空栈 上调用
push, pop, top, and getMin最多被调用 3 * 104 次
相关标签
栈
设计

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnkq37/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"
#include "stdlib.h"
typedef struct Node{
    int val;
    struct Node* next;
}Node;

typedef struct {
    Node* head;
} MinStack;


MinStack* minStackCreate() {
    MinStack* stack = (MinStack*)malloc(sizeof(MinStack));
    stack->head = NULL;
    return stack;
}

void minStackPush(MinStack* obj, int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->next = obj->head;
    obj->head = node;
}

void minStackPop(MinStack* obj) {
    if (obj->head){
        Node* tmp = obj->head;
        obj->head = obj->head->next;
        free(tmp);
    }
}

int minStackTop(MinStack* obj) {
    if (obj->head){
        return obj->head->val;
    }
    return -1;
}

int minStackGetMin(MinStack* obj) {
    int min = 0x7fffffff;
    Node* tmp = obj->head;
    for(;tmp; tmp = tmp->next){
        if (min > tmp->val){
            min = tmp->val;
        }
    }
    return min;
}

void minStackFree(MinStack* obj) {
    for(;obj->head;){
        Node* tmp = obj->head;
        obj->head = obj->head->next;
        free(tmp);
    }
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/

int main(void){
    int nums[] = {3,2,9,0,-1,-19,5,6};
    MinStack* obj = minStackCreate();
    int i = 0;
    for (; i < sizeof(nums)/sizeof(int); ++i){
        minStackPush(obj, nums[i]);
    }

    
    minStackPop(obj);
    
    int param_3 = minStackTop(obj);
    printf("top:%d\n", param_3);
    int param_4 = minStackGetMin(obj);
    printf("min:%d\n", param_4);
    minStackFree(obj);
}