#include <stdio.h>
#include <stdlib.h>


struct  A
{
    unsigned int a;
    //char b;
    double c;
    short d;
    char e;

} a;


int main(void)
{
    printf("sizeof(struct A):%d\n", sizeof(struct A));
    printf("%p, %p, %p\n", &a.a, &a.d, &a.e);
    printf("rand_max:%d\n", RAND_MAX);
    return 0;
}