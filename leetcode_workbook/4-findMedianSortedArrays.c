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


int main(void)
{
    int arr1[] = {1,3, 5, 6, 10};
    int arr2[] = {2};
    printf("%lf\n", findMedianSortedArrays(arr1, sizeof(arr1)/sizeof(int), arr2, sizeof(arr2)/sizeof(int)));
    return 0;
}