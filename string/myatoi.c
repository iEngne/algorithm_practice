#include "stdio.h"
#include <limits.h>
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

int myAtoi(char * s){
    int i = 0;
    int* nums = (int*)malloc(strlen(s)*sizeof(int));
    while (s[i] == ' ')++i;
    bool negative = false;
    if (s[i] == '-'){
        ++i;
        negative = true;
    }else if
    (s[i] == '+'){
        ++i;
    }
    while (s[i] == '0')++i;
    int j = 0;
    for (;(s[i] >= '0' && s[i] <= '9'); ++i, ++j){
        nums[j] = s[i];
    }
    int ret = 0;
    int newRet = 0;
    for (i = 0; i < j; ++i){
        int tmp = nums[i] - '0';
        // 判断正数是否越界，因为负数小于等于-2147483648都返回-2147483648
        // 所以只判断正数就行。
        if (ret > (INT_MAX - tmp)/10){
            if (negative) return INT_MIN;
            else return INT_MAX;
        }
        newRet=(ret * 10 + tmp);
        ret = newRet;
    }
    free(nums);
    if (negative) return -ret;
    return ret;
}

int main(void){
    char s[] = "A man, a plan, a canal: Panama";
    char p[] = "2147483646";

    printf("::%d\n", myAtoi(p));
    return 0;
}