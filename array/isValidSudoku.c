/**
有效的数独
请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
 

注意：

一个有效的数独（部分已被填充）不一定是可解的。
只需要根据以上规则，验证已经填入的数字是否有效即可。
空白格用 '.' 表示。
 
输入：board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：true
示例 2：

输入：board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：false
解释：除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。 但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
 

提示：

board.length == 9
board[i].length == 9
board[i][j] 是一位数字（1-9）或者 '.'

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/x2f9gg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "uthash/src/uthash.h"
#include "stdbool.h"

typedef struct hashTable {
    char key;
    UT_hash_handle hh;
} hashTable;


void delete_all(hashTable* hNums) {
  struct hashTable *cur_num, *tmp;

  HASH_ITER(hh, hNums, cur_num, tmp) {
    HASH_DEL(hNums, cur_num);  /* delete; users advances to next */
    free(cur_num);             /* optional- if you want to free  */
  }
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    hashTable *hNums = NULL;
    hashTable *hElm = NULL;
    int i,j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (board[i][j] == '.') continue;
            HASH_FIND(hh, hNums, &board[i][j], sizeof(char), hElm);
            if (hElm == NULL){
                hElm = (hashTable*)malloc(sizeof(hashTable));
                hElm->key = board[i][j];
                HASH_ADD(hh, hNums, key, sizeof(hElm->key), hElm);
            }
            else
            {
                delete_all(hNums);
                hNums = NULL;
                return false;
            }
        }
        delete_all(hNums);
        hNums = NULL;
    }
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (board[j][i] == '.') continue;
            HASH_FIND(hh, hNums, &board[j][i], sizeof(char), hElm);

            if (hElm == NULL){
                hElm = (hashTable*)malloc(sizeof(hashTable));
                hElm->key = board[j][i];
                HASH_ADD(hh, hNums, key, sizeof(hElm->key), hElm);
            }else
            {
                delete_all(hNums);
                hNums = NULL;
                return false;
            }
        }
        delete_all(hNums);
        hNums = NULL;
    }
    int startRow, startCol;
    for (startRow = 0; startRow < 9; startRow += 3){
        for (startCol = 0; startCol < 9; startCol += 3){
            for (i = startRow; i < startRow + 3; i++){
                for (j = startCol; j < startCol + 3; j++){
                    if (board[i][j] == '.') continue;
                    HASH_FIND(hh, hNums, &board[i][j], sizeof(char), hElm);
                    if (hElm == NULL){
                        hElm = (hashTable*)malloc(sizeof(hashTable));
                        hElm->key = board[i][j];
                        HASH_ADD(hh, hNums, key, sizeof(hElm->key), hElm);
                    }
                    else
                    {
                        delete_all(hNums);
                        hNums = NULL;
                        return false;
                    }
                }
            }
            delete_all(hNums);
            hNums = NULL;
        }
    }
    return true;
}

char* board[] = 
{"83..7...."
,"6..195..."
,".98....6."
,"8...6...3"
,"4..8.3..1"
,"7...2...6"
,".6....28."
,"...419..5"
,"....8..79"};


/**
[[".",".",".",".","5",".",".","1","."]
,[".","4",".","3",".",".",".",".","."]
,[".",".",".",".",".","3",".",".","1"]
,["8",".",".",".",".",".",".","2","."]
,[".",".","2",".","7",".",".",".","."]
,[".","1","5",".",".",".",".",".","."]
,[".",".",".",".",".","2",".",".","."]
,[".","2",".","9",".",".",".",".","."]
,[".",".","4",".",".",".",".",".","."]]
 * 
 */
char * board1[] = 
{"....5..1."
,".4.3....."
,".....4..2"
,"8......2."
,"..2.7...."
,".15......"
,".....2..."
,".2.9....."
,"..4......"};

/**
[["8",".","3",".",".",".",".",".","."]
,[".",".",".",".",".",".",".","2","."]
,[".","1",".",".",".",".",".","7","."]
,["1",".",".",".",".",".",".",".","3"]
,[".",".",".",".",".","2",".",".","."]
,[".",".",".",".",".","3",".",".","."]
,[".",".",".",".","6",".",".",".","."]
,["9",".",".",".",".",".","6",".","."]
,[".",".","1",".",".","4",".",".","."]]
 */
char * board2[] = 
{"8.3......"
,".......2."
,".1.....7."
,"1.......3"
,".....2..."
,".....3..."
,"....6...."
,"9.....6.."
,"..1..4..."};

bool isValidSudoku_1(char** board, int boardSize, int* boardColSize){
    int rows[9][9] = {0};
    int cols[9][9] = {0};
    int sub[3][3][9] = {0};
    int i, j, index;
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                index = board[i][j] - '0' - 1; //相当于hash
                rows[i][index]++;
                cols[j][index]++;
                sub[i/3][j/3][index]++;
                if (rows[i][index] > 1 || cols[j][index] > 1 || sub[i/3][j/3][index] > 1){
                    return false;
                }
            }

        }
    }
    return true;
}



int main(void){
    int colSize = 9;
    printf("ret:%d\n", isValidSudoku_1(board2, sizeof(board)/sizeof(char), &colSize));
    return 0;
}