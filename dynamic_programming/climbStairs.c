/**
爬楼梯
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

 

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
 

提示：

1 <= n <= 45
相关标签
记忆化搜索
数学
动态规划

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xn854d/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

/// 爬楼梯这个就是求斐波那契数列第n项的值///

int climbStairs(int n){
    int pre_pre = 1;
    int pre = 2;
    if (n == 1){
        return pre_pre;
    }else if (n == 2){
        return pre;
    }
    int i = 3;
    int cur = 0;
    for (; i <= n; ++i){
        cur = pre + pre_pre;
        pre_pre = pre;
        pre = cur;
    }
    return cur;
}