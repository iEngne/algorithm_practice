/**
 * @file 1_divide.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-11
剑指 Offer II 001. 整数除法
给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。

 

注意：

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231, 231−1]。本题中，如果除法结果溢出，则返回 231 − 1
 

示例 1：

输入：a = 15, b = 2
输出：7
解释：15/2 = truncate(7.5) = 7
示例 2：

输入：a = 7, b = -3
输出：-2
解释：7/-3 = truncate(-2.33333..) = -2
示例 3：

输入：a = 0, b = 1
输出：0
示例 4：

输入：a = 1, b = 1
输出：1
 

提示:

-231 <= a, b <= 231 - 1
b != 0
 
 * @copyright Copyright (c) 2022
 * 
 */


// 快速乘,返回值true，表示商大于z，false表示商小于z
bool quickAdd(int y, int z, int x) {
    // x 和 y 是负数，z 是正数
    // 需要判断 z * y >= x 是否成立
    int result = 0, add = y;
    while (z) {
        if (z & 1) {
            // x是被除数
            // 需要保证 result + add >= x
            // 如果result + add < x 说明z取得太大，x / y得商小于z
            if (result < x - add) {
                return false;
            }
            result += add;
        }
        // 为什么要在(z != 1)的判定？
        // 因为z==1无需判定add + add >= x,因为 z >>= 1的时候，上面result + add判定过了，
        // 也没有下一次循环了。
        // 如果z == 1也去判定add + add，有可能add + add < x，导致返回了false，本来是要返回true的
        if (z != 1) {
            // 需要保证 add + add >= x
            // 为什么要判断add < x - add？因为上面的(z&1)不是每次循环都能进去判定是否
            // 小于x了，例如z等于0x100000000这种，开始循环的时候，result都是0，值都是保存在add里的。
            // 不加判定的话，add可能会越界了
            if (add < x - add) {
                return false;
            }
            add += add;
        }
        // 不能使用除法
        z >>= 1;
    }
    return true;
};

int divide(int a, int b) {
    // 考虑被除数为最小值的情况
    if (a == INT_MIN) {
        if (b == 1) {
            return INT_MIN;
        }
        if (b == -1) {
            return INT_MAX;
        }
    }
    // 除数最小好像可以不用判定
    // 考虑除数为最小值的情况
    // if (b == INT_MIN) {
    //     return a == INT_MIN ? 1 : 0;
    // }
    // 考虑被除数为 0 的情况
    if (a == 0) {
        return 0;
    }
    
    // 一般情况，使用二分查找
    // 将所有的正数取相反数，这样就只需要考虑一种情况
    bool rev = false;
    if (a > 0) {
        a = -a;
        rev = !rev;
    }
    if (b > 0) {
        b = -b;
        rev = !rev;
    }
    
    int left = 0, right = INT_MAX, ans = 0;
    while (left <= right) {
        // 注意溢出，并且不能使用除法
        int mid = left + ((right - left) >> 1);
        bool check = quickAdd(b, mid, a);
        if (check) {
            ans = mid;
            // 注意溢出
            if (mid == INT_MAX) {
                break;
            }
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return rev ? -ans : ans;
}