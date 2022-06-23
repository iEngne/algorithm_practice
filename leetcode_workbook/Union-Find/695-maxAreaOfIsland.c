#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * initSetS(int** grid, int gridSize, int gridColSize)
{
    int* unionSets = (int*)malloc(gridSize * gridColSize * sizeof(int));
    if (!unionSets)
    {
        printf("error! out of mem\n");
        return NULL;
    }
    memset(unionSets, 10, gridSize * gridColSize * sizeof(int));
    int i, j;
    for (i = 0; i < gridSize; ++i)
    {
        for (j = 0; j < gridColSize; ++j)
        {
            if (grid[i][j] == 1)
            {
                unionSets[i * gridColSize + j] = -1;
            }
        }
    }
    return unionSets;
}


int find(int x, int* unionSets)
{
    if (unionSets[x] <= -1)
    {
        return x;
    }
    unionSets[x] = find(unionSets[x], unionSets);
    return unionSets[x];
}


void merge(int x, int y, int* unionSets)
{
    int fx = find(x, unionSets);
    int fy = find(y, unionSets);
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

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize){
    int* unionSets = initSetS(grid, gridSize, *gridColSize);
    if (!unionSets)
    {
        return 0;
    }
    int i, j;
    for (i = 0; i < gridSize; ++i)
    {
        for (j = 0; j < *gridColSize; ++j)
        {
            if (grid[i][j] == 1)
            {
                int x, y;
                //grid[i][j] = 0;
                if (i - 1 >= 0 && grid[i - 1][j] == 1)
                {
                    x = i * *gridColSize + j;
                    y = (i - 1) * *gridColSize + j;
                    merge(x, y, unionSets);
                }
                if (i + 1 < gridSize && grid[i + 1][j] == 1)
                {
                    x = i * *gridColSize + j;
                    y = (i + 1) * *gridColSize + j;
                    merge(x, y, unionSets);
                }
                if (j - 1 >= 0 && grid[i][j - 1] == 1)
                {
                    x = i * *gridColSize + j;
                    y = i * *gridColSize + j - 1;
                    merge(x, y, unionSets);
                }
                if (j + 1 < *gridColSize && grid[i][j + 1] == 1)
                {
                    x = i * *gridColSize + j;
                    y = i * *gridColSize + j + 1;
                    merge(x, y, unionSets);
                }
            }
        }
    }

    int min = 0;
    for (i = 1; i < gridSize * *gridColSize; ++i)
    {
        if (unionSets[i] <= -2 && unionSets[i] > -10000 && unionSets[i] < min)
        {
            min = unionSets[i];
        }
    }
    free(unionSets);
    if (min != 0)
    {
        min = 0 - min;
    }
    return min;
}



int main(void)
{
    int matrix[][13] = {{0,0,1,0,0,0,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,1,1,1,0,0,0},
                        {0,1,1,0,1,0,0,0,0,0,0,0,0},
                        {0,1,0,0,1,1,0,0,1,0,1,0,0},
                        {0,1,0,0,1,1,0,0,1,1,1,0,0},
                        {0,0,0,0,0,0,0,0,0,0,1,0,0},
                        {0,0,0,0,0,0,0,1,1,1,0,0,0},
                        {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    int* grid[8];
    int i;
    for (i = 0; i < 8; ++i)
    {
        grid[i] = matrix[i];
    }
    int column = 13;
    int ret = maxAreaOfIsland(grid, 8, &column);
    printf("ret:%d\n", ret);
    return;
}

