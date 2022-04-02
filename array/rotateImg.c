
/**
旋转图像
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

 

示例 1：


输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
示例 2：


输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 

提示：

n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnhhkv/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */

#include "stdio.h"
#include "stdlib.h"


void rotate(int** matrix, int matrixSize, int* matrixColSize){
    int i, j;
    int (*p)[matrixSize] = (int(*)[])matrix;
    // (i, j) -> (j, s-1-i) -> (s-1-i, s-1-j) -> (s-1-j, i) -> (j, j)
    for (i = 0; i < matrixSize /  2; ++i){
        for (j = 0; j < (matrixSize + 1) / 2; ++j){
            int tmp = p[matrixSize - 1 - j][i];
            p[matrixSize - 1 -j][i] = p[matrixSize - 1 - i][matrixSize - 1 - j];
            p[matrixSize - 1 - i][matrixSize - 1 - j] = p[j][matrixSize - 1 - i];
            p[j][matrixSize - 1 - i] = p[i][j];
            p[i][j] = tmp;
        }
    }
}
void rotate_1(int** matrix1, int matrixSize, int* matrixColSize) {
    int (*matrix)[matrixSize] = (int(*)[])matrix1;
    for (int i = 0; i < matrixSize / 2; ++i) {
        for (int j = 0; j < (matrixSize + 1) / 2; ++j) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[matrixSize - j - 1][i];
            matrix[matrixSize - j - 1][i] = matrix[matrixSize - i - 1][matrixSize - j - 1];
            matrix[matrixSize - i - 1][matrixSize - j - 1] = matrix[j][matrixSize - i - 1];
            matrix[j][matrixSize - i - 1] = temp;
        }
    }
}



int main(void){
    int matrix[][4] = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    int m[][4] = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16},{1,2,3}};
    int colsize = 4;
    printf("s:%d\n", sizeof(matrix[0]));
    rotate((int**)matrix, 4, &colsize);
    for (int i = 0; i < colsize; ++i){
        for (int j = 0; j < colsize; ++j){
            printf("%d,", matrix[i][j]);
        }
            printf("\n");
    }
    return 0;
}