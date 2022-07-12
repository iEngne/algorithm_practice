/**
 * @file min_stack.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-12
剑指 Offer 30. 包含min函数的栈
定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

 

示例:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.
 

提示：

各函数的调用总次数不超过 20000 次
 

注意：本题与主站 155 题相同：https://leetcode-cn.com/problems/min-stack/
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct {
    int size;
    unsigned int stackTop;
    unsigned int deStackTop;
    int* stack;
    int* deStack;
} MinStack;

#define DEFAULT_SIZE (128)
/** initialize your data structure here. */

MinStack* minStackCreate() {
    MinStack* minstack = (MinStack*)malloc(sizeof(MinStack));
    minstack->size = DEFAULT_SIZE;
    minstack->stackTop  = 0;
    minstack->deStackTop = 0;
    minstack->stack = (int*)malloc(DEFAULT_SIZE * sizeof(int));
    minstack->deStack = (int*)malloc(DEFAULT_SIZE * sizeof(int));
    return minstack;
}

void minStackPush(MinStack* obj, int x) {
    assert(obj);
    if (obj->stackTop == obj->size) {
        int* tmp = (int*)malloc((obj->size << 1) * sizeof(int));
        memcpy(tmp, obj->stack, obj->size * sizeof(int));
        free(obj->stack);
        obj->stack = tmp;
        obj->size <<= 1;
        tmp = (int*)malloc(obj->size * sizeof(int));
        memcpy(tmp, obj->deStack, obj->deStackTop * sizeof(int));
        free(obj->deStack);
        obj->deStack = tmp;
    }
    obj->stack[obj->stackTop++] = x;
    if (obj->deStackTop == 0) {
        obj->deStack[obj->deStackTop++] = x;
    }else if (x <= obj->deStack[obj->deStackTop - 1]) {
        obj->deStack[obj->deStackTop++] = x;
    }
}

void minStackPop(MinStack* obj) {
    assert(obj);
    --obj->stackTop;
    if (obj->stack[obj->stackTop] == obj->deStack[obj->deStackTop - 1]) {
        --obj->deStackTop;
    }
}

int minStackTop(MinStack* obj) {
    assert(obj);
    return obj->stack[obj->stackTop - 1];
}

int minStackMin(MinStack* obj) {
    assert(obj);
    return obj->deStack[obj->deStackTop - 1];
}

void minStackFree(MinStack* obj) {
    assert(obj);
    if (obj->stack) {
        free(obj->stack);
    }
    if (obj->deStack) {
        free(obj->deStack);
    }
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackMin(obj);
 
 * minStackFree(obj);
*/

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackMin(obj);
 
 * minStackFree(obj);
*/


int main(void) {
    MinStack* obj = minStackCreate();
    minStackPush(obj, -2);
    minStackPush(obj, 0);
    minStackPush(obj, -3);
    printf("min = %d\n", minStackMin(obj));
    minStackPop(obj);
    printf("top = %d\n", minStackTop(obj));
    printf("min = %d\n", minStackMin(obj));
    minStackFree(obj);
    return 0;
}