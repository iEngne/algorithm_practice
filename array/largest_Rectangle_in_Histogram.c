#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
/**
 * @brief 计算直方图中内接矩形的最大面积
 * 假设每个直方图的宽为1,高度由一个数组nums给出
 * 
 */


typedef struct monoStack{
    int* stBuf;  ///< 单调栈存储空间，保存数组下标
    int  stSize; ///< 栈大小
    int  stTopP; ///< 栈顶索引，索引处是下一个未使用空间
} monoStack;

void initStack(monoStack* pStack, int stSize){
    pStack->stBuf = (int*)malloc(sizeof(int) * stSize);
    pStack->stSize = stSize;
    pStack->stTopP = 0;
}

void deInitStack(monoStack* pStack){
    free(pStack->stBuf);
}

int popStack(monoStack* pStack){
    if (pStack->stTopP != 0){
        return pStack->stBuf[--pStack->stTopP];
    }else{
        return -1;
    }
}
bool isEmpty(monoStack* pStack){
    if (pStack->stTopP == 0){
        return true;
    }else{
        return false;
    }
}

int getTopElmt(monoStack* pStack){
    if (!isEmpty(pStack)){
        int tmp = pStack->stTopP - 1;
        return pStack->stBuf[tmp];
    }else{
        return -1;
    }
}

void pushStack(monoStack* pStack, int i){
    if (pStack->stSize != pStack->stTopP){
        pStack->stBuf[pStack->stTopP++] = i;
    }
}

int largestRecArea(int* a, int len){
    monoStack decrStack;
    initStack(&decrStack, len);
    int i , j, maxArea = 0, area;
    for (i = 0; i < len; i++){
        while ((!isEmpty(&decrStack)) && (a[getTopElmt(&decrStack)] > a[i])){
            j = popStack(&decrStack);
            area = a[j] * (i - getTopElmt(&decrStack) - 1 );
            if (area > maxArea){
                maxArea = area;
            } 
        }
        pushStack(&decrStack, i);
    }
    while (!isEmpty(&decrStack))
    {
        j = popStack(&decrStack);
        area = a[j] * (i - getTopElmt(&decrStack) - 1);
        if (area > maxArea){
            maxArea = area;
        } 
    }
    deInitStack(&decrStack);
    return maxArea;
}



/**
 * 基本思路：假设内接矩形的左右边界为left，right,那么矩形的
 * 面积就被left和right之间最小的高所限制。那么我们不断以最小的高为
 * pivot进行分割，递归计算分别计算povit左右两边的面积，再比较大小，确定最大的面积
 */
int findMin(int* nums, int left, int right) {
    int min = left;
    int i;
    for (i = left + 1; i <= right; ++i) {
        if (nums[i] < nums[min]) {
            min = i;
        }
    }
    return min;
}

int findMax(int a, int b, int c) {
    if (a > b) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b > c) {
            return b;
        } else {
            return c;
        }
    }
}


int largestRectAreaR(int* nums, int left, int right) {
    if (left > right) {
        return 0;
    }
    int minIndex = findMin(nums, left, right);
    int max = 0;
    max = (right - left + 1) * nums[minIndex];

    int maxL = 0;
    int maxR = 0;
    maxL = largestRectAreaR(nums, left, minIndex - 1);
    maxR = largestRectAreaR(nums, minIndex + 1, right);
    max = findMax(max, maxL, maxR);

    return max;
}


int largestRectArea(int* nums, int len) {
    int left = 0;
    int right = len - 1;
    return largestRectAreaR(nums, left, right);
}


int main(void){
    int nums[] = {6,2,5,4,5,1,6};
    // int nums[] = {6, 2};
    printf("maxArea:%d\n", largestRecArea(nums, sizeof(nums)/sizeof(nums[0])));
    printf("maxArea:%d\n", largestRectArea(nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}
