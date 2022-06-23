/**
 * @file 684-findRedundantConnection.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
684. 冗余连接
树可以看成是一个连通且 无环 的 无向 图。

给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的边。

 

示例 1：



输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]
示例 2：



输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]
 

提示:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
edges 中无重复元素
给定的图是连通的 
 */

#include <stdio.h>
#include <stdlib.h>

int* initSets(int size)
{
    int* unionSets = (int*)malloc((size + 1) * sizeof(int));
    if (!unionSets)
    {
        return NULL;
    }
    int i = 0;
    for (i = 0; i < size + 1; ++i)
    {
        unionSets[i] = -1;
    }
    return unionSets;
}


int findRoot(int x, int* unionSets)
{
    if (unionSets[x] <= -1)
    {
        return x;
    }
    unionSets[x] = findRoot(unionSets[x], unionSets);
    return unionSets[x];
}


void merge(int x, int y, int* unionSets)
{
    int fx = findRoot(x, unionSets);
    int fy = findRoot(y, unionSets);
    if (fx == fy)
    {
        return;
    }
    if (unionSets[fx] <= unionSets[fy])
    {
        unionSets[fx] += unionSets[fy];
        unionSets[fy] = fx;
    }
    else
    {
        unionSets[fy] += unionSets[fx];
        unionSets[fx] = fy;
    }
    return;
}


int isLinked(int x, int y, int* unionSets)
{
    int fx = findRoot(x, unionSets);
    int fy = findRoot(y, unionSets);
    return fx == fy;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int* retArray = (int*)malloc(2 * sizeof(int));
    if (!retArray)
    {
        printf("error! out of mem, line:%d\n", __LINE__);
        *returnSize = 0;
        goto _exit0;
    }
    int* unionSets = initSets(edgesSize);
    if (!unionSets)
    {
        printf("error! out of mem\n");
        goto _exit1;
    }
    int i;
    for (i = 0; i < edgesSize; ++i)
    {
        if (isLinked(edges[i][0], edges[i][1], unionSets))
        {
            retArray[0] = edges[i][0];
            retArray[1] = edges[i][1];
            *returnSize = 2;
        }
        merge(edges[i][0], edges[i][1], unionSets);
    }
    return retArray;
_exit1:
    free(retArray);
_exit0:
    return retArray;
}


int main(void)
{
    //int arr[][2] = {{1,2},{1,3},{2,3}};
    // int arr[][2] = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    int arr[][2] = {{1,3},{3,4},{1,5},{3,5},{2,3}};
    int i = 0;
    int* edges[sizeof(arr)/sizeof(arr[0])];
    for (; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        edges[i] = arr[i];
    }
    int column = 2;
    int retSize = 0;
    int* ret = findRedundantConnection(edges, sizeof(arr)/sizeof(arr[0]), &column, &retSize);
    printf("%d, %d\n", ret[0], ret[1]);
    free(ret);
    return 0;
}