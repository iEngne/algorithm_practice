#include"stdio.h"
#include"stdlib.h"

/**
两个数组的交集 II
给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。

 

示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]
示例 2:

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]
 

提示：

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
 

进阶：

如果给定的数组已经排好序呢？你将如何优化你的算法？
如果 nums1 的大小比 nums2 小，哪种方法更优？
如果 nums2 的元素存储在磁盘上，内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x2y0c2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */

int cmpfunc(const void* a, const void* b){
    return (*(int*)a) - (*(int*)b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    qsort(nums1, nums1Size, sizeof(int), cmpfunc);
    qsort(nums2, nums2Size, sizeof(int), cmpfunc);
    int i = 0,j = 0,k = 0;
    int* ret = (int*)malloc((nums1Size < nums2Size? nums1Size : nums2Size)*sizeof(int));
    while (i < nums1Size && j < nums2Size){
        if (nums1[i] < nums2[j]){
            i++;
        }
        else if(nums1[i] > nums2[j]){
            j++;
        }
        else{
            ret[k] = nums1[i];
            k++;
            i++;
            j++;
        }
    }
    *returnSize = k;
    return ret;
}

int nums1[] = {4,9,5}, nums2[] = {9,4,9,8,4};

int main(){
    int size = 0;
    int * ret = intersect(nums1,sizeof(nums1)/sizeof(int), nums2, sizeof(nums2)/sizeof(int), &size);
    while (--size >= 0){
        printf("ret:%d\n", ret[size]);
    }
    free(ret);
    return 0;
}