/**
 * @file 128-.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-17
128. 最长连续序列
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

 

示例 1：

输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
示例 2：

输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
 

提示：

0 <= nums.length <= 105
-109 <= nums[i] <= 109
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <uthash/src/uthash.h>
#include <math.h>





typedef struct hash_map
{
    int key; // 保存原数组的值
    int val; // 保存原数组的下标
    UT_hash_handle hh;
} hash_map;


void delete_hash_map(hash_map* h_nums)
{
    hash_map* current_elem, *tmp;
    HASH_ITER(hh, h_nums, current_elem, tmp)
    {
        HASH_DELETE(hh, h_nums, current_elem);
        free(current_elem);
    }
}


/********************* 只使用hash表的方法 *******************/
int longestConsecutive(int* nums, int numsSize){
    int i;
    hash_map* h_table = NULL;
    hash_map* h_elm =  NULL;
    for (i = 0; i < numsSize; ++i)
    {
        /* 将数组中的数全部放到hash表中，并且去重 */
        HASH_FIND(hh, h_table, &nums[i], sizeof(int), h_elm);
        if (!h_elm)
        {
            h_elm = (hash_map*)malloc(sizeof(hash_map));
            h_elm->key = nums[i];
            // HASH_ADD中的第三个参数是第五个参数的filedname.
            HASH_ADD(hh, h_table, key, sizeof(int), h_elm);
        }
    }
    int seq_max_len = 0;
    int seq_current_len = 0;
    for (i = 0; i < numsSize; ++i)
    {
        int num = nums[i];
        num -= 1;
        HASH_FIND(hh, h_table, &num, sizeof(int), h_elm);
        if (!h_elm)
        {
            num = nums[i] + 1;
            seq_current_len = 1;
            HASH_FIND(hh, h_table, &num, sizeof(int), h_elm);
            while (h_elm)
            {
                ++seq_current_len;
                ++num;
                HASH_FIND(hh, h_table, &num, sizeof(int), h_elm);
            }
            seq_max_len = fmax(seq_max_len, seq_current_len);
        }
    }
    delete_hash_map(h_table);
    return seq_max_len;
}

/****************** 使用并查集+hash表 ***********************/
int* init_union_sets(int len)
{
    int* union_sets = (int*)malloc(sizeof(int) * len);
    int i = 0;
    for(; i < len; ++i)
    {
        union_sets[i] = -1; // 根节点设为-1
    }
    return union_sets;
}

/**
 * @brief 查找根节点并把沿途的所有父节点设为根节点
 * 
 * @param m 
 * @param union_sets 
 * @return int 
 */
int find(int m, int* union_sets)
{
    if (union_sets[m] < 0)
    {
        return m;
    }
    return union_sets[m] = find(union_sets[m], union_sets);
}


void merge(int m, int n, int* union_sets)
{
    int fa_m = find(m, union_sets);
    int fa_n = find(n, union_sets);
    if (fa_m == fa_n)
    {
        return;
    }
    /* 根节点中数值越小，说明子节点越多 */
    if (union_sets[fa_m] < union_sets[fa_n])
    {
        union_sets[fa_m] += union_sets[fa_n];
        union_sets[fa_n] = fa_m;
    }
    else
    {
        union_sets[fa_n] += union_sets[fa_m];
        union_sets[fa_m] = fa_n;
    }
    return;
}

int longestConsecutive_1(int* nums, int numsSize)
{
    if (numsSize == 0)
    {
        return 0;
    }
    int* union_sets = init_union_sets(numsSize);
    int i;
    hash_map* h_nums = NULL;
    hash_map* h_elem = NULL;
    for (i = 0; i < numsSize; ++i)
    {
        HASH_FIND(hh, h_nums, &nums[i], sizeof(int), h_elem);
        /* hash表中不存在的数才操作，过滤重复元素 */
        if (!h_elem)
        {
            h_elem = (hash_map*)malloc(sizeof(hash_map));
            h_elem->key = nums[i]; // 数组的值作为hash_map的key
            h_elem->val = i; // 保存下标，并查集中的关系索引使用下标
            HASH_ADD(hh, h_nums, key, sizeof(int), h_elem);

            /* 看下比当前数小1的数有吗,有的话就可以算有个连续的区间了 */
            int num = nums[i] - 1;
            HASH_FIND(hh, h_nums, &num, sizeof(int), h_elem);
            if (h_elem)
            {
                merge(h_elem->val, i, union_sets);
            }
            /* 看下比当前数大1的数有吗,有的话就可以算有个连续的区间了 */
            num = nums[i] + 1;
            HASH_FIND(hh, h_nums, &num, sizeof(int), h_elem);
            if (h_elem)
            {
                merge(h_elem->val, i, union_sets);
            }
        }
    }
    int min = 0;
    for (i = 1; i < numsSize; ++i)
    {
        if (union_sets[i] < union_sets[min])
        {
            min = i;
        }
    }
    delete_hash_map(h_nums);
    return 0 - union_sets[min];
}


int main(void)
{
    int nums[] = {0,3,7,2,5,8,4,6,0,1};
    printf("%d\n", longestConsecutive_1(nums, sizeof(nums)/sizeof(int)));
    return 0;
}
