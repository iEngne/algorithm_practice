/**
 * @file primeNumber.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
计数质数
给定整数 n ，返回 所有小于非负整数 n 的质数的数量 。

 

示例 1：

输入：n = 10
输出：4
解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
示例 2：

输入：n = 0
输出：0
示例 3：

输入：n = 1
输出：0
 

提示：

0 <= n <= 5 * 106
相关标签
数组
数学
枚举
数论

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnzlu6/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"


///////////////////////////判断质数///////////////////////////
/**
 * @brief 枚举法
 *
 * 版本1：根据质数的定义，对于大于2的自然数n，从2开始到n-1看是否存在能整除n的数，
 * 如果存在，则是合数，否则为质数
 *
 * 版本2：无需判断从2~n-1的所有数，只需要判断2~n的平方根的数是否能整除就行
 * 
 * 版本3：对于所有大于3的质数具有6n+1(n >= 1)或者6n-1的性质
 * 
 */
//结合2和3的代码示例，时间复杂度O(sqrt(n))
// leetcode中，计算从1到709486有几个质数，耗时28ms
bool isPrime3(int n){
    if (n == 1){
        return false;
    }
    if (n == 2 || n == 3){
        return true;
    }
    if (n % 6 != 1 && n % 6 != 5){
        return false;
    }
    int i;
    int j = sqrt(n);
    for (i = 5; i <= j; i += 6){
        // 形如6n+1(n >= 1)或者6n-1的合数，一定可以被6k+1或者6k-1的数所整除
        if (n % i == 0 || n % (i + 2) == 0){
            return false;
        }
    }
    printf("%d ", n);
    return true;
}

/**
 * @brief 分解质因数-短除法
 * 版本1：要从最小的质数除起（依次除于质数2 3 5....)一直到n，时间复杂度为O(n)
 * 
 * 版本2：n中最多只含有一个大于sqrt(n)的质因子。
 *       证明：通过反证法：如果有两个大于sqrt(n)的因子，那么相乘会大于n，矛盾。证毕
 *       于是我们发现最多只有一个大于sqrt(n)的因子，对其进行优化。先考虑比sqrt(n)小的，代码和质数的判定类似
 *       最后如果n还是>1，说明此时的n就是大于sqrt(n)的唯一质因子，输出即可，时间复杂度O(sqrt(n))
 * 这种方法，运算次数太多，还不如枚举法
 */
bool divide1(int n)
{
    int s = 0;
    for(int i = 2; i <= n; ++i)
    {
        // 证明一下循环里面的i一定是一个质数：假如 i 是一个合数，
        // 那么它一定可以分解成多个质因子相乘的形式，
        // 这多个质因子同时也是 n 的质因子且比i要小，
        // 而比i小的数在之前的循环过程中一定是被条件除完了的，所以i不可能是合数，只可能是质数
        if(n % i == 0)//i一定是质数
        {
            while(n % i == 0)//短除法分解质因数
            {
                n /= i;
                ++s;//统计质因数的个数
            }
        }
    }
    return s > 1? false:true;
}

// 使用此方法，leetcode中，计算从1到709486有几个质数，耗时408ms
bool divide2(int n)
{
    int s = 0;
    for(int i = 2; i <= n / i; ++i)
    {
        if(n % i == 0)//i一定是质数
        {
            //s = 0;
            while(n % i == 0)//短除法分解质因数
            {
                n /= i;
                ++s;//统计质因数的个数
            }
            //printf("%d %d\n", i, s);
        }
    }
    //if(n > 1) printf("%d %d\n", n, 1);//当n没有变化的时候，输出本身和1
    n > 1? ++s:s; // n还是大于1的，说明此时的n就是一个质数，s需要加1
    return s > 1? false:true;
}

int countPrimes(int n){
    int i = 0;
    int res = 0;
    for (i = 2; i <= n; ++i){
        divide1(i)?++res:res;
    }
    return res;
}

///////////////////////////筛质数///////////////////////////
/**
 * 朴素筛法
 * 枚举i：2~n，从前往后把每个数对应的倍数都删除掉，这样筛过之后，所有剩下的数都是质数
 */


//朴素筛法-O(nlogn)
// leetcode n=709486时耗时28ms
int countPrimes1(int n){
    // 存储质数
    int* primeNums = (int*)malloc(n * sizeof(int));
    // 计数
    int count = 0;
    // 标记
    int* flag = (int*)calloc(n + 1, sizeof(int));
    int i,j;
    for (i = 2; i < n; ++i){
        if (!flag[i]){
            primeNums[count++] = i;
        }
        // 将所有i的倍数都标记，这些标记的数肯定是合数
        for (j = i + i; j < n; j += i){
            flag[j] = true;
        }
    }
    free(primeNums);
    free(flag);
    return count;
}

/**
埃氏筛法是对朴素筛法的一种优化方式，我们并不需要把2~n的每一个数的倍数都删掉，可以只把所有质数的倍数删掉！
因为合数的倍数，肯定也是比这个合数小的质数的某个倍数
时间复杂度：O(n * loglogn)，近似O(n)
 * // leetcode n = n=709486时耗时8ms
 */
int countPrimes2(int n){
    // 存储质数
    //int* primeNums = (int*)malloc(n * sizeof(int));
    // 计数
    int count = 0;
    // 标记
    int* flag = (int*)calloc(n, sizeof(int));
    int i,j;
    for (i = 2; i < n; ++i){
        // 进入这个if条件的都是质数，合数都在之前的循环中被标记为true了
        if (!flag[i]){
            // primeNums[count++] = i;
            ++count;
            // 将所有i的倍数都标记，这些标记的数肯定是合数
            for (j = i + i; j < n; j += i){
                flag[j] = 1;
            }
        }

    }
    //free(primeNums);
    free(flag);
    return count;
}

/**
线性（欧拉）筛法
埃氏筛法的缺陷 ：对于一个合数，有可能被筛多次。例如 30 = 2 * 15 = 3 * 10 = 5*6……
那么如何确保每个合数只被筛选一次呢？我们只要用它的最小质因子来筛选即可，这便是欧拉筛法。
欧拉筛法的基本思想 ：在埃氏筛法的基础上，让每个合数只被它的最小质因子筛选一次，以达到不重复的目的。
 */
int countPrimes3(int n){
    // 存储质数
    int* primeNums = (int*)malloc(n * sizeof(int));
    // 计数
    int count = 0;
    // 标记合数
    int* flag = (int*)calloc(n, sizeof(int));
    int i,j;
    for (i = 2; i < n; ++i){
        // 将数从小到大遍历的过程中，没被标记的数一定是质数
        if (!flag[i]){
            primeNums[count++] = i;
            ++count;
        }
        // 以下这组循环，意思是以一个固定的倍数i去乘以不同的质数，并加上0 == i % primeNums[j]判断来保证
        // 这些数是以primeNums[j]为最小质因数的合数
        for (j = 0; i * primeNums[j] < n; ++j){
            // primeNums[]存放的是从小到大排列的质数，i在这组循环中都是不变的，当j从0开始遍历的时候，
            // 一开始的一次或几次循环中，i*primeNums[j]得到的合数，肯定是以primeNums[j]为最小质因数的。
            // 那么这些数都可以打上标记。i % primeNums[j] == 0是在判断primeNums[j]是不是i的最小质因数.
            // 当j继续增大，也就是质数继续增大，如果出现i可以被某个primeNums[j]整除，
            // 说明此时i可以分解成primeNums[j]和一个比primeNums[j]大的质数的乘积，
            // 那么此时primeNums[j]的值还是i*primeNums[j]的最小质因数，但是下一次循环，
            // 也就是primeNums[k]*i(k等于上一次循环的j+1)的值，却不是以primeNums[k]为最小质因数的合数了，
            // 因为此时i已经可以被上一次循环的primeNums[j]因式分解，i可以表示成m*primeNums[j](m>=primeNums[j]),
            // primeNums[j]比primeNums[k]小，所以primeNums[k]*i的最小质因数是上次循环的primeNums[j],
            // 于是primeNums[j+1]*i可以表示成 primeNums[j+1]*m*primeNums[j],
            // 令primeNums[j+1]*m为i',这不就是后面会遍历到的数吗？所以不应该这次循环中标记，
            // 所以当i % primeNums[j] == 0时，应该推出循环了。
            flag[i * primeNums[j]] = 1;
            // j继续增大，会不会一直找不到primeNums[j]可以整除i,不可能，为什么？
            // 因为小于等于i的质数已经都放进了primeNUms[]中,在这些质数中一定存在一个质数可以整除i。
            if ((0 == i % primeNums[j])){
                break;
            }
        }
    }
    free(primeNums);
    free(flag);
    return count;
}

int main(int argc, char** argv){
    int n = 709486;
    if (argc > 1){
        n = atoi(argv[1]);
    }
    printf("count:%d\n", countPrimes2(n));
    return 0;
}