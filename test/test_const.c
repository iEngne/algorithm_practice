#include <stdio.h>

int main(void)
{
    const double pi = 3.14;
    double* ptr = &pi; // 编译出现警告，没出错
    *ptr = 3;
    printf("%lf\n", pi); // pi = 3，还是修改了pi的值
    return 0;
}