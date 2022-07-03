/**
 * @file HJ54.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-27
HJ54 表达式求值
题目
题解(6)
讨论(208)
排行
面经new
简单  通过率：57.21%  时间限制：1秒  空间限制：32M
知识点
字符串
基础数学
栈
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
给定一个字符串描述的算术表达式，计算出结果值。

输入字符串长度不超过 100 ，合法的字符包括 ”+, -, *, /, (, )” ， ”0-9” 。

数据范围：运算过程中和最终结果均满足 |val| \le 2^{31}-1 \∣val∣≤2 
31
 −1  ，即只进行整型运算，确保输入的表达式合法
输入描述：
输入算术表达式

输出描述：
计算出结果值

示例1
输入：
400+5
复制
输出：
405

 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 对于需要先计算出后面结果的情况，可以使用递归计算出
 * 后面的值
 */


int getResult(char* str, int* cur) {
    int num = 0;
    char operator = '+';
    int buffer[100];
    int top = 0;
    while (str[*cur]) {
        /* 如果有括号先计算括号的值 */
        if (str[*cur] == '(') {
            ++(*cur);
            num = getResult(str, cur);
        }

        while (str[*cur] && str[*cur] >= '0' && str[*cur] <= '9') {
            num = num * 10 + str[*cur] - '0';
            ++(*cur);
        }
        switch (operator) {
            case '+': 
                buffer[top++] = num;
                break;
            case '-':
                buffer[top++] = -num;
                break;
            /** 乘除的优先级高，直接计算 */
            case '*':
                buffer[top - 1] *= num;
                break;
            case '/':
                buffer[top - 1] /= num;
                break;
        }
        /* 匹配右括号 */
        if (str[*cur] == ')') {
            ++(*cur);
            break;
        }
        num = 0;
        operator = str[*cur];
        ++(*cur);
    }
    int i = 0;
    num = 0;
    for (i = 0; i < top; ++i)
    {
        num += buffer[i];
    }
    return num;
}


int main(void)
{
    char buffer[102] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = 0;
    int pos = 0;
    printf("%d\n", getResult(buffer, &pos));
    return 0;
}