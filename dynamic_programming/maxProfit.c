/**
买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

 

示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
 

提示：

1 <= prices.length <= 105
0 <= prices[i] <= 104
相关标签
数组
动态规划

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xn8fsh/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */


#include "stdio.h"

// 类似于找数组中最长递增子序列，子序列在数组中的位置可以不连续
int maxProfit(int* prices, int pricesSize){
    int minPrice = prices[0];
    int maxProfit = 0;
    int i = 1;
    for (; i < pricesSize; ++i){
        // 如果当前价格比之前的最小价格都小，那么不可能在这个价格卖
        // 所以不影响利润，将最小价格保存，continue
        if (prices[i] < minPrice){
            minPrice = prices[i];
            continue;
        }
        // 如果当前价格大于之前的最小价格，看看利润有多少，跟之前的最大利润比较
        // 如果利润比之前的大，就保存这个值
        int tmp = prices[i] - minPrice;
        if (tmp > maxProfit){
            maxProfit = tmp;
        }
    }
    return maxProfit;
}