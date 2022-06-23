/**
 * @file 200-numIslands.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-20
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

 

示例 1：

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1
示例 2：

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/number-of-islands
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count = 0;

int* initSets(char** grid, int row, int column)
{
    int i, j;
    int* unionSets = (int*)malloc(sizeof(int) * row * column);
    memset(unionSets, 0 , sizeof(int) * row * column);
    if (!unionSets)
    {
        printf("error!!\n");
        return NULL;
    }
    for (i = 0; i < row; ++i)
    {
        for (j = 0; j < column; ++j)
        {
            if (grid[i][j] == '1')
            {
                unionSets[i * column + j] = -1;
                ++count;
            }
        }
    }
    return unionSets;
}


int find(int m, int* unionSets)
{
    if (unionSets[m] < 0)
    {
        return m;
    }
    unionSets[m] = find(unionSets[m], unionSets);
    return unionSets[m];
}


void merge(int m, int n, int* unionSets)
{
    int fm = find(m, unionSets);
    int fn = find(n, unionSets);
    if (fm == fn)
    {
        return;
    }
    if (unionSets[fm] < unionSets[fn])
    {
        unionSets[fm] += unionSets[fn];
        unionSets[fn] = fm;
    }
    else
    {
        unionSets[fn] += unionSets[fm];
        unionSets[fm] = fn;
    }
    --count;
    return;
}


int numIslands(char** grid, int gridSize, int* gridColSize){
    int i, j;
    int* unionSets = initSets(grid, gridSize, *gridColSize);
    if (!unionSets)
    {
        return 0;
    }
    for (i = 0; i < gridSize; ++i)
    {
        for (j = 0; j < *gridColSize; ++j)
        {
            if (grid[i][j] == '1')
            {
                //grid[i][j] = '0';
                if (i - 1 >= 0 && grid[i - 1][j] == '1')
                {
        
                    merge((i - 1) * *gridColSize + j, i * *gridColSize + j, unionSets);
                }
                if (i + 1 < gridSize && grid[i + 1][j] == '1')
                {
                    merge((i + 1) * *gridColSize + j, i * *gridColSize + j, unionSets);
                }
                if (j - 1 >= 0 && grid[i][j - 1] == '1')
                {
                    merge(i * *gridColSize + j - 1, i * *gridColSize + j, unionSets);
                }
                if (j + 1 < *gridColSize && grid[i][j + 1] == '1')
                {
                    merge(i * *gridColSize + j + 1, i * *gridColSize + j, unionSets);
                }
            }
        }
    }
    return count;
}


int main(void)
{
    char matrix[][5] = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int i;
    char* grid[4];
    for (i = 0; i < 4; ++i)
    {
        grid[i] = matrix[i];
    }

    int column = 5;
    printf("%d\n", numIslands(grid, 4, &column));
    return 0;
}