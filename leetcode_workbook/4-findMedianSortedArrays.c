/**
4. 寻找两个正序数组的中位数
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 
提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106

https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
 */


#include <stdio.h>
#include <math.h>
#include <limits.h>

/**
 * @brief 找到第k小的数,k从1开始
 * 
 * @param nums1 
 * @param nums1Size 
 * @param nums2 
 * @param nums2Size 
 * @param k 
 * @return int 
 */
int get_kth_elem(int* nums1, int nums1Size, int* nums2, int nums2Size, int k)
{
    int start_index1 = 0;
    int start_index2 = 0;
    int pivot_index1, pivot_index2;
    int k_ = k;
    while (1)
    {
        if (start_index1 == nums1Size)
        {
            printf("k:%d,val:%d\n", k_, nums2[start_index2 + k - 1]);
            return nums2[start_index2 + k - 1];
        }
        if (start_index2 == nums2Size)
        {
            printf("k:%d,val:%d\n", k_, nums1[start_index1 + k - 1]);
            return nums1[start_index1 + k - 1];
        }
        if (k == 1)
        {
            printf("k:%d,val:%d\n", k_, fmin(nums1[start_index1], nums2[start_index2]));
            return fmin(nums1[start_index1], nums2[start_index2]);
        }
        pivot_index1 = fmin(start_index1 + k / 2 - 1, nums1Size - 1);
        pivot_index2 = fmin(start_index2 + k / 2 - 1, nums2Size - 1);
        if (nums1[pivot_index1] <= nums2[pivot_index2])
        {
            k -= pivot_index1 - start_index1 + 1;
            start_index1 = pivot_index1 + 1;
        }
        else
        {
            k -= pivot_index2 - start_index2 + 1;
            start_index2 = pivot_index2 + 1;
        }
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int k;
    if ((nums1Size + nums2Size) % 2 == 0)
    {
        k = (nums1Size + nums2Size) / 2;
        return (double)(get_kth_elem(nums1, nums1Size, nums2, nums2Size, k) + get_kth_elem(nums1, nums1Size, nums2, nums2Size, k + 1)) / 2;
    }
    else
    {
        k = (nums1Size + nums2Size) / 2;
        return (double)get_kth_elem(nums1, nums1Size, nums2, nums2Size, k + 1);
    }
}


/**
方法二：划分数组
说明

方法一的时间复杂度已经很优秀了，但本题存在时间复杂度更低的一种方法。这里给出推导过程，勇于挑战自己的读者可以进行尝试。

思路与算法

为了使用划分的方法解决这个问题，需要理解「中位数的作用是什么」。在统计中，中位数被用来：

将一个集合划分为两个长度相等的子集，其中一个子集中的元素总是大于另一个子集中的元素。

如果理解了中位数的划分作用，就很接近答案了。

首先，在任意位置 ii 将 \text{A}A 划分成两个部分：


           left_A            |          right_A
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
由于 \text{A}A 中有 mm 个元素， 所以有 m+1m+1 种划分的方法（i \in [0, m]i∈[0,m]）。

\text{len}(\text{left\_A}) = i, \text{len}(\text{right\_A}) = m - ilen(left_A)=i,len(right_A)=m−i.

注意：当 i = 0i=0 时，\text{left\_A}left_A 为空集， 而当 i = mi=m 时, \text{right\_A}right_A 为空集。

采用同样的方式，在任意位置 jj 将 \text{B}B 划分成两个部分：


           left_B            |          right_B
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
将 \text{left\_A}left_A 和 \text{left\_B}left_B 放入一个集合，并将 \text{right\_A}right_A 和 \text{right\_B}right_B 放入另一个集合。 再把这两个新的集合分别命名为 \text{left\_part}left_part 和 \text{right\_part}right_part：


          left_part          |         right_part
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
当 \text{A}A 和 \text{B}B 的总长度是偶数时，如果可以确认：

\text{len}(\text{left\_part}) = \text{len}(\text{right\_part})len(left_part)=len(right_part)
\max(\text{left\_part}) \leq \min(\text{right\_part})max(left_part)≤min(right_part)
那么，\{\text{A}, \text{B}\}{A,B} 中的所有元素已经被划分为相同长度的两个部分，且前一部分中的元素总是小于或等于后一部分中的元素。中位数就是前一部分的最大值和后一部分的最小值的平均值：

\text{median} = \frac{\text{max}(\text{left}\_\text{part}) + \text{min}(\text{right}\_\text{part})}{2}
median= 
2
max(left_part)+min(right_part)
​
 

当 \text{A}A 和 \text{B}B 的总长度是奇数时，如果可以确认：

\text{len}(\text{left\_part}) = \text{len}(\text{right\_part})+1len(left_part)=len(right_part)+1
\max(\text{left\_part}) \leq \min(\text{right\_part})max(left_part)≤min(right_part)
那么，\{\text{A}, \text{B}\}{A,B} 中的所有元素已经被划分为两个部分，前一部分比后一部分多一个元素，且前一部分中的元素总是小于或等于后一部分中的元素。中位数就是前一部分的最大值：

\text{median} = \text{max}(\text{left}\_\text{part})
median=max(left_part)

第一个条件对于总长度是偶数和奇数的情况有所不同，但是可以将两种情况合并。第二个条件对于总长度是偶数和奇数的情况是一样的。

要确保这两个条件，只需要保证：

i + j = m - i + n - ji+j=m−i+n−j（当 m+nm+n 为偶数）或 i + j = m - i + n - j + 1i+j=m−i+n−j+1（当 m+nm+n 为奇数）。等号左侧为前一部分的元素个数，等号右侧为后一部分的元素个数。将 ii 和 jj 全部移到等号左侧，我们就可以得到 i+j = \frac{m + n + 1}{2}i+j= 
2
m+n+1
​
 。这里的分数结果只保留整数部分。

0 \leq i \leq m0≤i≤m，0 \leq j \leq n0≤j≤n。如果我们规定 \text{A}A 的长度小于等于 \text{B}B 的长度，即 m \leq nm≤n。这样对于任意的 i \in [0, m]i∈[0,m]，都有 j = \frac{m + n + 1}{2} - i \in [0, n]j= 
2
m+n+1
​
 −i∈[0,n]，那么我们在 [0, m][0,m] 的范围内枚举 ii 并得到 jj，就不需要额外的性质了。

如果 \text{A}A 的长度较大，那么我们只要交换 \text{A}A 和 \text{B}B 即可。

如果 m > nm>n ，那么得出的 jj 有可能是负数。

\text{B}[j-1] \leq \text{A}[i]B[j−1]≤A[i] 以及 \text{A}[i-1] \leq \text{B}[j]A[i−1]≤B[j]，即前一部分的最大值小于等于后一部分的最小值。

为了简化分析，假设 \text{A}[i-1], \text{B}[j-1], \text{A}[i], \text{B}[j]A[i−1],B[j−1],A[i],B[j] 总是存在。对于 i=0i=0、i=mi=m、j=0j=0、j=nj=n 这样的临界条件，我们只需要规定 \text{A}[-1]=\text{B}[-1]=-\inftyA[−1]=B[−1]=−∞，A[m]=\text{B}[n]=\inftyA[m]=B[n]=∞ 即可。这也是比较直观的：当一个数组不出现在前一部分时，对应的值为负无穷，就不会对前一部分的最大值产生影响；当一个数组不出现在后一部分时，对应的值为正无穷，就不会对后一部分的最小值产生影响。

所以我们需要做的是：

在 [0, m][0,m] 中找到 ii，使得：

\qquad \text{B}[j-1] \leq \text{A}[i]B[j−1]≤A[i] 且 \text{A}[i-1] \leq \text{B}[j]A[i−1]≤B[j]，其中 j = \frac{m + n + 1}{2} - ij= 
2
m+n+1
​
 −i

我们证明它等价于：

在 [0, m][0,m] 中找到最大的 ii，使得：

\qquad \text{A}[i-1] \leq \text{B}[j]A[i−1]≤B[j]，其中 j = \frac{m + n + 1}{2} - ij= 
2
m+n+1
​
 −i

这是因为：

当 ii 从 0 \sim m0∼m 递增时，\text{A}[i-1]A[i−1] 递增，\text{B}[j]B[j] 递减，所以一定存在一个最大的 ii 满足 \text{A}[i-1] \leq \text{B}[j]A[i−1]≤B[j]；

如果 ii 是最大的，那么说明 i+1i+1 不满足。将 i+1i+1 带入可以得到 \text{A}[i] > \text{B}[j-1]A[i]>B[j−1]，也就是 \text{B}[j - 1] < \text{A}[i]B[j−1]<A[i]，就和我们进行等价变换前 ii 的性质一致了（甚至还要更强）。

因此我们可以对 ii 在 [0, m][0,m] 的区间上进行二分搜索，找到最大的满足 \text{A}[i-1] \leq \text{B}[j]A[i−1]≤B[j] 的 ii 值，就得到了划分的方法。此时，划分前一部分元素中的最大值，以及划分后一部分元素中的最小值，才可能作为就是这两个数组的中位数。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */
double findMedianSortedArrays1(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    /* 假定nums1的长度小于等于nums2的长度，如果nums1长度大于nums2，互换 */
    if (nums1Size > nums2Size)
    {
        return findMedianSortedArrays1(nums2, nums2Size, nums1, nums1Size);
    }
    int left = 0;
    int right = nums1Size;
    int left_max = 0;
    int right_min = 0;
    /* 注意这里是小于等于 */
    while (left <= right)
    {
        /* i是nums1中划分点的数组小标, j是nums2中划分点的数组下标 */
        int i = (left + right) / 2;
        int j = (nums1Size + nums2Size + 1) / 2 - i;
        int nums_i_l = (i == 0 ? INT_MIN : nums1[i - 1]);
        int nums_j_l = (j == 0 ? INT_MIN : nums2[j - 1]);
        int nums_i   = (i == nums1Size ? INT_MAX : nums1[i]);
        int nums_j   = (j == nums2Size ? INT_MAX : nums2[j]);
        if (nums_i_l <= nums_j)
        {
            left_max = fmax(nums_i_l, nums_j_l);
            right_min = fmin(nums_i, nums_j);
            left = i + 1;
        }
        else
        {
            right = i - 1;
        }
    }
    return ((nums1Size + nums2Size) % 2 == 0) ? (left_max + right_min) / 2.0 : left_max;

}

int main(void)
{
    int arr1[] = {1,3, 5, 6, 10};
    int arr2[] = {2};
    printf("%lf\n", findMedianSortedArrays1(arr1, sizeof(arr1)/sizeof(int), arr2, sizeof(arr2)/sizeof(int)));
    return 0;
}