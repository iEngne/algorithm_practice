#include <stdio.h>
#include <assert.h>
#include <string.h>

/** 宏定义中"##"将##两边的第一个非空白内容拼接 */
#define A(a, b)  (b## b )
/** "#"将#后的第一个非空白内容当作带双引号的字符串 */
#define B(a, b)  ("a"# b )
#define C(a)   (# a )

int main(void) {
    int a = 2;
    assert(a == 2);
    printf("%d\n", A(12,12));
    char* b = B(12,13);
    printf("C():%s\n", C(1));
    char c[100] = "abdddddcd";
    printf("%d\n", strlen(c));
    char str[] = "abc";
    printf("%d, %d, %d\n", sizeof(str), strlen(str), sizeof('a'));
    int e = -5;
    int f = -7;
    printf("average:%d\n", (e & f) + ((e ^ f) >> 1));
    printf("average:%d\n", ((e & f) + (e | f)) >> 1);
    return 0;
}