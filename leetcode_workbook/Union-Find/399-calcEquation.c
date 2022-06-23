/**
 * @file 399.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-21
399. 除法求值
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

 

示例 1：

输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
示例 2：

输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]
示例 3：

输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]
 

提示：

1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj 由小写英文字母与数字组成
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash/src/uthash.h>

typedef struct HashMap
{
    char* key;
    int index;
    UT_hash_handle hh;
} HashMap;


int* initSets(int row, int column, double** weight)
{
    int* unionSets = (int*)malloc(row * column * sizeof(int));
    if (!unionSets)
    {
        *weight = NULL;
        return NULL;
    }
    *weight = (double*)malloc(row * column * sizeof(double));
    if (!*weight)
    {
        free(unionSets);
        *weight = NULL;
        return NULL;
    }
    int i = 0, j = 0;
    for (i = 0; i < row; ++i)
    {
        for (j = 0; j < column; ++j)
        {
            unionSets[i * column + j] = -1;
            (*weight)[i * column + j] = 1;
        }
    }
    return unionSets;
}


int findRoot(int x, int* unionSets, double* weight)
{
    // printf("x = %d, union[x] = %d\n", x, unionSets[x]);
    if (unionSets[x] <= -1)
    {
        return x;
    }
    /* 路径压缩需要计算新的权重 
       以下写法错误：
       unionSets[x] = findRoot(unionSets[x], unionSets, weight);
       weight[x] = weight[x] * weight[unionSets[x]];
       return unionSets[x];
       因为在上一个findRoot函数中，前一个节点到根节点的权值已经放在weight[unionSets[x]]中了
       如果用unionSets[x]去接返回值，unionSets[x]就是根节点了，那么weight[unionSets[x]]一直是1.
    */
    
    int fx = findRoot(unionSets[x], unionSets, weight);
    weight[x] = weight[x] * weight[unionSets[x]];
    // printf("x = %d, w = %lf, w_u_x = %lf\n", x, weight[x], weight[unionSets[x]]);
    unionSets[x] = fx;
    return unionSets[x];
}


void merge(int x, int y, int* unionSets, double value, double* weight)
{
    int fx = findRoot(x, unionSets, weight);
    int fy = findRoot(y, unionSets, weight);
    if (fx == fy)
    {
        return;
    }
    /* 默认是y->x方向，即x是被除数，y是除数 */
    /**
     *   fx     fy          fx --->fy
     *   ^      ^           ^      ^
     *   |      |           |      |
     *   x      |           x      |
     *   ^      ^                  ^
     *   |      |    ====>         |
     *   y -----+           y -----+
     * 
     */
    // 如果y-->fy，说明y已经指向其他的节点了，将y-->x转换为，x-->fy
    if (fy != y)
    {
        /* 所以前面需要判断fx==fy，要不然，根节点标识-1就被覆盖了 */
        unionSets[fx] = fy;
        // 这里即使fx == x，也没关系，因为此时weight[x] = 1
        weight[fx] = weight[y] / value / weight[x];
        // 如果fx == fy, 那么根节点中的节点数信息丢失
        unionSets[fx] = fy;
    }
    /**  如果y == fy,以下3种情况
     *   x -----> fx
     *   ^
     *   |
     *   y <---- a
     * 
     *   x ----> fx
     *   ^
     *   |
     *   y
     *   
     *   a ----> x ----> fx
     *           ^
     *           |
     *           y
     */
    else
    {
        unionSets[y] = x;
        weight[y] = value;
    }
    // printf("x:%d, y:%d, unionSets[x]:%d, unionSets[y]:%d, wei[x]:%lf, wei[y]:%lf\n",
    //          x, y, unionSets[x], unionSets[y], weight[x], weight[y]);
}

int isLinked(int x, int y, int* unisonSets, double* weight)
{
    int fx = findRoot(x, unisonSets, weight);
    int fy = findRoot(y, unisonSets, weight);
    //printf("isLinked: fx = %d, fy = %d\n", fx, fy);
    return fx == fy;
}

void deleteAll(HashMap* hHead)
{
    HashMap* current, *tmp;
    HASH_ITER(hh, hHead, current, tmp)
    {
        HASH_DEL(hHead, current);
        free(current);
    }
    return;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* calcEquation(char *** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char *** queries, int queriesSize, int* queriesColSize, int* returnSize)
{
    HashMap* hHead = NULL;
    HashMap* hElem  = NULL;
    HashMap* hElem1 = NULL;
    int i, j;
    // 1. 通过hash表去除重复的字符串，并分配index，将字符串跟index关联，便于通过数组存储
    int index = 0;
    for (i = 0; i < equationsSize; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            HASH_FIND(hh, hHead, (equations[i][j]), strlen(equations[i][j]), hElem);
            if (!hElem)
            {
                hElem = (HashMap*)malloc(sizeof(HashMap));
                hElem->key = equations[i][j];
                hElem->index = index++;
                HASH_ADD(hh, hHead, key[0], strlen(equations[i][j]), hElem);
                //HASH_ADD_STR(hHead, key, hElem);
            }
        }
    }
    // 2. 通过并查集进行查找和合并
    double* weight = NULL;
    int* unionSets = initSets(index, equationsColSize[0], &weight);
    for (i = 0; i < equationsSize; ++i)
    {
        HASH_FIND(hh, hHead, equations[i][0], strlen(equations[i][0]), hElem);
        if (!hElem)
        {
            printf("error:%d\n", __LINE__);
        }
        HASH_FIND(hh, hHead, equations[i][1], strlen(equations[i][1]), hElem1);
        if (!hElem1)
        {
            printf("error:%d\n", __LINE__);
        }
        int x = hElem->index;
        int y = hElem1->index;
        merge(x, y, unionSets, values[i], weight);
        // printf("x = %d, y = %d, union[x] = %d, union[y] = %d, weight = %lf\n", x, y, unionSets[x], unionSets[y], weight[i]);
    }

    // 3. 计算要求解的值
    double* retVal = (double*)malloc(queriesSize * sizeof(double));
    for (i = 0; i < queriesSize; ++i)
    {
        // printf("i:%d, addr:%p = [%s]\n", i, queries[i][0], queries[i][0]);
        HASH_FIND(hh, hHead, queries[i][0], strlen(queries[i][0]), hElem);
        if (!hElem)
        {
            //printf("error:%d\n", __LINE__);
        }
        HASH_FIND(hh, hHead, queries[i][1], strlen(queries[i][1]), hElem1);
        if (!hElem1)
        {
            //printf("error:%d\n", __LINE__);
        }
        if (!hElem1 || !hElem)
        {
            retVal[i] = -1.0;
            continue;
        }
        // printf("x = %d, parent = %d, weight:%lf\n", hElem->index, unionSets[hElem->index], weight[hElem->index]);
        // printf("y = %d, parent = %d, weight:%lf\n", hElem1->index, unionSets[hElem1->index], weight[hElem1->index]);
        if (!isLinked(hElem->index, hElem1->index, unionSets, weight))
        {
            retVal[i] = -1.0;
            continue;
        }
        int x = hElem->index;
        int y = hElem1->index;
        int fx = findRoot(hElem->index, unionSets, weight);
        int fy = findRoot(hElem1->index, unionSets, weight);
        //printf("fx = %d, fy = %d, weight[x] = %lf, weight[y] = %lf\n", fx, fy, weight[x], weight[y]);
        retVal[i] = weight[y] / weight[x];
    }
    *returnSize = queriesSize;
    free(unionSets);
    free(weight);
    deleteAll(hHead);
    return retVal;
}


int main(void)
{
    //char* equations[][2] = {{"a","b"},{"b","c"},{"bc","cd"}};
    // char* equations[][2] = {{"a","b"},{"b","c"}};
    // char* equations[][2] = {{"a","b"},{"e","f"},{"b","e"}};
    // char* equations[][2] = {{"a","b"},{"b","c"}, {"a", "c"}};
    // char* equations[][2] = {{"a","c"},{"b","e"}, {"c", "d"}, {"e", "d"}};
    char* equations[][2] = {{"a","e"},{"b","e"}};
    int sizeEq = sizeof(equations)/sizeof(equations[0]);
    char** eq[sizeEq];
    int i;

    //double values[] = {1.5,2.5,5.0};
    //double values[] = {2.0,3.0};
    // double values[] = {3.4,1.4,2.3};
    // double values[] = {2.0, 3.0, 6.0};
    // double values[] = {2.0, 3.0, 0.5, 5.0};
    double values[] = {4.0,3.0};
    int valSize = sizeof(values) / sizeof(values[0]);

    int sizeEqCol = 2;
    for (i = 0; i < sizeEq; ++i)
    {
        eq[i] = equations[i];
    }

    // char* queries[][2] = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};
    // char* queries[][2] = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
    // char* queries[][2] = {{"b","a"},{"a","f"},{"f","f"},{"e","e"},{"c","c"},{"a","c"},{"f","e"}};
    // char* queries[][2] = {{"a","b"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
    // char* queries[][2] = {{"a", "b"}};
    char* queries[][2] = {{"a","b"},{"e","e"},{"x","x"}};
    int sizeQu = sizeof(queries)/sizeof(queries[0]);
    char** qu[sizeQu];
    int sizeQuCol = 2;
    for (i = 0; i < sizeQu; ++i)
    {
        qu[i] = queries[i];
    }

    int retSize = 0;
    double* ret = calcEquation(eq, sizeEq, &sizeEqCol, values, valSize, qu, sizeQu, &sizeEqCol, &retSize);
    for (i = 0; i < retSize; ++i)
    {
        printf("%lf\n", ret[i]);
    }
    return 0;
}
