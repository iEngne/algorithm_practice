#include <stdio.h>

int main(void) {
    int a = -4;
    int b = a >> 1;
    printf("%d\n", b);
    int c = 0x7fffffff;
    int d = c << 1;
    printf("c = %d\n", c);
    printf("d = %d\n", d);
    int e = 0x80000001;
    int f = e << 1;
    printf("e = %d, f = %d\n", e, f);
    return 0;
}