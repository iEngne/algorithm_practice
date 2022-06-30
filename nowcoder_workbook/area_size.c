/**
 * @file area_size.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-15
求三个矩形的相交面积
输入：
1 6 4 4
2 5 3 3
0 3 5 5
解释：三行为三个矩形，第一二列为左上角 横纵坐标，第三四列分别为矩形长宽
 * @copyright Copyright (c) 2022
 * 
 */


#include "stdio.h"

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Rect
{
    Point left_top;
    Point right_bottom;
} Rect;


int main(void)
{
    Rect rect[3] = {0};
    int i = 0;
    for (i = 0; i < 3; ++i)
    {
        scanf("%d %d %d %d", &rect[i].left_top.x, &rect[i].left_top.y, &rect[i].right_bottom.x, &rect[i].right_bottom.y);
        /* 将长宽改为右下角坐标 */
        rect[i].right_bottom.x = rect[i].left_top.x + rect[i].right_bottom.x;
        rect[i].right_bottom.y = rect[i].left_top.y - rect[i].right_bottom.y;
    } 
    Rect rectMerge;
    rectMerge.left_top.x = rect[0].left_top.x;
    rectMerge.left_top.y = rect[0].left_top.y;
    rectMerge.right_bottom.x = rect[0].right_bottom.x;
    rectMerge.right_bottom.y = rect[0].right_bottom.y;
    for (i = 1; i < 3; ++i)
    {
        /* 左上角x取最大值 */
        if (rect[i].left_top.x > rectMerge.left_top.x)
        {
            rectMerge.left_top.x = rect[i].left_top.x;
        }
        /* 左上角y取最小值 */
        if (rect[i].left_top.y < rectMerge.left_top.y)
        {
            rectMerge.left_top.y = rect[i].left_top.y;
        }
        /* 右下角x取最小值 */
        if (rect[i].right_bottom.x < rectMerge.right_bottom.x)
        {
            rectMerge.right_bottom.x = rect[i].right_bottom.x;
        }
        /* 右小角y取最大值 */
        if (rect[i].right_bottom.y > rectMerge.right_bottom.y)
        {
            rectMerge.right_bottom.y = rectMerge.right_bottom.y;
        }
    }
    printf("%d, %d, %d, %d\n", rectMerge.left_top.x, rectMerge.left_top.y, rectMerge.right_bottom.x, rectMerge.right_bottom.y);
    int area = (rectMerge.right_bottom.x - rectMerge.left_top.x) * (rectMerge.left_top.y - rectMerge.right_bottom.y);
    printf("%d\n", area);
    return 0;
}