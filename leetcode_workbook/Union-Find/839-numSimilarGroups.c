/**
 * @file 839.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-21
839. 相似字符串组
如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

给你一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。请问 strs 中有多少个相似字符串组？

 

示例 1：

输入：strs = ["tars","rats","arts","star"]
输出：2
示例 2：

输入：strs = ["omv","ovm"]
输出：1
 

提示：

1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] 只包含小写字母。
strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int* initSets(int size)
{
    int* mergeSets = (int*)malloc(size * sizeof(int));
    if (!mergeSets)
    {
        return NULL;
    }
    int i = 0;
    for (i = 0; i < size; ++i)
    {
        mergeSets[i] = -1;
    }
    return mergeSets;
}


int findRoot(int x, int* mergeSets)
{
    if (mergeSets[x] <= -1)
    {
        return x;
    }
    mergeSets[x] = findRoot(mergeSets[x], mergeSets);
    return mergeSets[x];
}


void merge(int x, int y, int* mergeSets)
{
    int fx = findRoot(x, mergeSets);
    int fy = findRoot(y, mergeSets);
    if (fx == fy)
    {
        return;
    }
    if (mergeSets[fx] <= mergeSets[fy])
    {
        mergeSets[fx] += mergeSets[fy];
        mergeSets[fy] = fx;
    }
    else
    {
        mergeSets[fy] += mergeSets[fx];
        mergeSets[fx] = fy;
    }
}

int isSimilar(char* x, char* y)
{
    int i;
    int count = 0;
    for (i = 0; x[i]; ++i)
    {
        if (x[i] != y[i])
        {
            ++count;
        }
    }
    return (count == 0 || count == 2);
}

int numSimilarGroups(char ** strs, int strsSize){
    int i, j;
    int* mergeSets = initSets(strsSize);
    for (i = 1; i < strsSize; ++i)
    {
        for (j = i - 1; j >= 0; --j)
        {
            printf("i:%d, j:%d, %s, %s\n", i, j, strs[i], strs[j]);
            if (isSimilar(strs[i], strs[j]))
            {
                printf("i:%d, j:%d, merge:%s, %s\n", i, j, strs[i], strs[j]);
                merge(i, j, mergeSets);
                continue;
            }
        }
    }
    int count = 0;
    for (i = 0; i < strsSize; ++i)
    {
        if (mergeSets[i] <= -1)
        {
            ++count;
        }
    }
    free(mergeSets);
    return count;
}


int main(void)
{
    char* arr[] = {"tars","rats","arts","star"};
    printf("%d\n", numSimilarGroups(arr, sizeof(arr)/sizeof(char*)));
    return 0;
}