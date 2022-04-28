/**
最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

 

示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
 

提示：

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 仅由小写英文字母组成

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnmav1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

char * longestCommonPrefix(char ** strs, int strsSize){
    int i = 0;
    int j = 0;
    int len = strlen(strs[0]);
    char *minStr = strs[0];
    for (i = 1; i < strsSize; ++i){
        if (strlen(strs[i]) < len){
            minStr = strs[i];
        }
    }
    char *s = (char*)calloc(strlen(minStr) + 1,sizeof(char));
    for(j = 0; minStr[j]; ++j){
        char c = minStr[j];
        for (i = 0; i < strsSize; ++i){
            if (c != strs[i][j]){
                memcpy(s, minStr, j);
                return s;
            }
        }
    }
    memcpy(s, minStr, strlen(minStr));
    return s;
}

int main(void){
    char* strs[] = {"flower","flow","flight"};
    char* s = longestCommonPrefix(strs, sizeof(strs)/sizeof(char*));
    printf("%s ", s);
    free(s);
    return 0;
}