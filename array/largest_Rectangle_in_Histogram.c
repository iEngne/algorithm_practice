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
int main(void){
    int nums[] = {6,2,5,4,5,1,6};
    printf("maxArea:%d\n", largestRecArea(nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}
