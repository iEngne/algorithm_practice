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


int isMerged(int x, int y, int* unionSets)
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
        if (isMerged(edges[i][0], edges[i][1], unionSets))
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