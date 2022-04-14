#include "stdio.h"


/*
给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1:

输入: prices = [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
示例 2:

输入: prices = [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
示例 3:

输入: prices = [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 

提示：

1 <= prices.length <= 3 * 104
0 <= prices[i] <= 104

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x2zsx1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/


// 原来写的代码，逻辑太复杂，自己都不想看了，太绕了...
int maxProfit1(int* prices, int pricesSize){
    int i = 0,j = 1;
    int find = 0;
    int max = 0;
    if (j >= pricesSize)
    {
        return max;
    }
    for (;;)
    {
        if (prices[j] > prices[i])
        {
            for (;;)
            {
                if (j+1 == pricesSize)
                {
                    if (find == 0)
                    {
                        max += prices[j] - prices[i];
                    }
                    return max;
                }
                if (prices[j + 1] < prices[j])
                {
                    find = 1;
                    break;
                }
                j++;
            }
        }
        else if (prices[j] <= prices[i])
        {
            i++;
            j++;
            if (j >= pricesSize)
            {
                return max;
            }
        }
        if (find == 1)
        {
            max += prices[j] - prices[i];
            find = 0;
            i = j+1;
            if (i >= pricesSize)
            {
                return max;
            }
            j = i + 1;
            if (j >= pricesSize)
            {
                return max;
            }
        }
    }
}


/* 使用单调栈 */
int maxProfit2(int* prices, int pricesSize){
    int* stack = (int*)malloc(pricesSize * sizeof(int));
    int stackIndex = 0;
    stack[stackIndex++] = prices[0];
    int max = 0;
    for (int i = 1; i < pricesSize; ++i)
    {
        if (stack[stackIndex - 1] <= prices[i])
        {
            stack[stackIndex++] = prices[i];
        }
        else
        {
            max += stack[stackIndex - 1] - stack[0];
            stackIndex = 0;
            stack[stackIndex++] = prices[i];
        }
    }
    /* 有可能数据一直是单调递增的，数据全部在栈里 */
    if (stackIndex >= 1)
    {
        max += stack[stackIndex - 1] - stack[0];
    }
    free(stack);
    return max;
}


/* 再优化，栈里只记录最小最大值 */
int maxProfit(int* prices, int pricesSize){
    int stack[2];
    int stackIndex = 0;
    stack[stackIndex++] = prices[0];
    int max = 0;
    for (int i = 1; i < pricesSize; ++i)
    {
        if (stack[stackIndex - 1] <= prices[i])
        {
            if (stackIndex == 2)
            {
                stackIndex = 1;
            }
            stack[stackIndex++] = prices[i];
        }
        else
        {
            max += stack[stackIndex - 1] - stack[0];
            stackIndex = 0;
            stack[stackIndex++] = prices[i];
        }
    }
    if (stackIndex >= 1)
    {
        max += stack[stackIndex - 1] - stack[0];
    }
    return max;
}

int main(void)
{
    int prices[] = {1,2,3,4,5};
    printf("sizeof(prices):%d\n", sizeof(prices)/sizeof(int));
    int profit = maxProfit(prices, sizeof(prices)/sizeof(int));
    printf("profit:%d", profit);
    return 0;
}