/**
外观数列
给定一个正整数 n ，输出外观数列的第 n 项。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。

你可以将其视作是由递归公式定义的数字字符串序列：

countAndSay(1) = "1"
countAndSay(n) 是对 countAndSay(n-1) 的描述，然后转换成另一个数字字符串。
前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
第一项是数字 1 
描述前一项，这个数是 1 即 “ 一 个 1 ”，记作 "11"
描述前一项，这个数是 11 即 “ 二 个 1 ” ，记作 "21"
描述前一项，这个数是 21 即 “ 一 个 2 + 一 个 1 ” ，记作 "1211"
描述前一项，这个数是 1211 即 “ 一 个 1 + 一 个 2 + 二 个 1 ” ，记作 "111221"
要 描述 一个数字字符串，首先要将字符串分割为 最小 数量的组，每个组都由连续的最多 相同字符 组成。然后对于每个组，先描述字符的数量，然后描述字符，形成一个描述组。要将描述转换为数字字符串，先将每组中的字符数量用数字替换，再将所有描述组连接起来。

例如，数字字符串 "3322251" 的描述如下图：

"3322251" --> "23321511"

 

示例 1：

输入：n = 1
输出："1"
解释：这是一个基本样例。
示例 2：

输入：n = 4
输出："1211"
解释：
countAndSay(1) = "1"
countAndSay(2) = 读 "1" = 一 个 1 = "11"
countAndSay(3) = 读 "11" = 二 个 1 = "21"
countAndSay(4) = 读 "21" = 一 个 2 + 一 个 1 = "12" + "11" = "1211"
 

提示：

1 <= n <= 30

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/top-interview-questions-easy/xnpvdm/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * 
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"



char * countAndSay(int n){
    if (n == 1){
        char *p = (char*)calloc(2,1);
        *p = '1';
        return p;
    }
    else{
        char *s = countAndSay(n - 1);
        // int len = strlen(s)*3;
        // 由于长度无法确定，又是存字符串，所以用calloc，
        // 先申请2倍于上一个返回的内存
        char *t = (char*)calloc(strlen(s)*3, sizeof(char));
        int i = 0;
        int j = 0;
        int count = 1;
        char c = s[0];
        for (0;s[i];++i){
            c = s[i];
            if (s[i] != s[i+1]){
                sprintf(t+j,"%d", count);
                ++j;
                t[j] = c;
                ++j;
                // 内存可能不够了，重新申请
                // if (j + 2 >= len - 1){
                //     len *= 2;
                //     char *t1 = (char*)calloc(len, 1);
                //     memcpy(t1, t, len / 2);
                //     free(t);
                //     t = t1;
                // }
                count = 1;
            }else {
                ++count;
            }
        }
        free(s);
        return t;
    }
}

int main(void){
    printf("%s\n", countAndSay(30));
    return 0;
}