/**
 * @file HJ26.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-23
HJ26 字符串排序
题目
题解(273)
讨论(659)
排行
面经new
中等  通过率：39.63%  时间限制：1秒  空间限制：32M
知识点
字符串
排序
warning 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
描述
编写一个程序，将输入字符串中的字符按如下规则排序。

规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。

如，输入： Type 输出： epTy

规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。

如，输入： BabA 输出： aABb

规则 3 ：非英文字母的其它字符保持原来的位置。


如，输入： By?e 输出： Be?y

数据范围：输入的字符串长度满足 1 \le n \le 1000 \1≤n≤1000 

输入描述：
输入字符串
输出描述：
输出字符串
示例1
输入：
A Famous Saying: Much Ado About Nothing (2012/8).
复制
输出：
A aaAAbc dFgghh: iimM nNn oooos Sttuuuy (2012/8).
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

int main(void)
{
    char buffer[1002] = {0};
    fgets(buffer, sizeof(buffer), stdin);
    int i = 0;
    int j = 0;
    int tmp = 0;
    int chr = 0;
    for (i = 1; buffer[i]; ++i)
    {
        chr = buffer[i];
        for (j = i - 1; j >= 0; --j)
        {
            /** 非字母 */
            if (!((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')))
            {
                break;
            }
            /* 如果待比较的下一个字母是大写 */
            if (buffer[j] >= 'A' && buffer[j] <= 'Z')
            {
                /* 大小写相同 */
                if (buffer[j] == chr || buffer[j] + 32 == chr)
                {
                    break;
                }
                if (chr >= 'A' && chr <= 'Z' && chr >= buffer[j])
                {
                    break;
                }
                if (chr >= 'a' && chr <= 'z' && chr - 32 >= buffer[j])
                {
                    break;
                }
            }
            else if (buffer[j] >= 'a' && buffer[j] <= 'z')
            {
                /* 大小写相同 */
                if (buffer[j] == chr || buffer[j] - 32 == chr)
                {
                    break;
                }
                if (chr >= 'A' && chr <= 'Z' && chr + 32 >= buffer[j])
                {
                    break;
                }
                if (chr >= 'a' && chr <= 'z' && chr >= buffer[j])
                {
                    break;
                }
            }
            /* 非字母,跳过 */
            else
            {
                /* 记录跳过的个数 */
                tmp++;
                continue;
            }
            buffer[j + 1 + tmp] = buffer[j];
            tmp = 0;
        }
        buffer[j + 1 + tmp] = chr;
        tmp = 0;
    }
    printf("%s\n", buffer);
    return 0;
}