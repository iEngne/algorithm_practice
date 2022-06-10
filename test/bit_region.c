/**
 * @file bit_region.c
 * @author your name (you@domain.com)
 * @brief 探索字节序和位序
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
// #undef __BYTE_ORDER__
// #define __BYTE_ORDER__ __ORDER_BIG_ENDIAN__
#include <stdio.h>
#include <stdlib.h>

struct A 
{
    unsigned int a:3;
    unsigned int b:1;
    unsigned int c:4;
    unsigned int d:5;
};

struct B
{
    unsigned int a:3;
    unsigned int b:2;
    unsigned int c:5;
    unsigned int d:6;
};


struct C {
        int a;
        int b;
        int c;
};


void foo(int *p)
{
        int a1 = 1;
        int a2 = 2;
        printf("&a1:%p, &a2:%p\n", &a1, &a2);
        return;
}


int main(void)
{
    /** 字节序 高地址      ------>        低地址
     *  0b 10101010 11001010 10001011 10110011
     *                         位序 bit7-->bit0
     * 小端字节序，其内部位序是最低有效位在bit0的地方
     */
    int x[] = {0b10101010110010101000101110110011, 0xbbbbbbbb};
    char y[] =  {0b11010, 0b11011, 0b11100, 0b11101};
    int h = 1, i = 2, j = 3;
    printf("&h:%p, &i:%p, &j:%p\n", &h, &i, &j);
    printf("sizeof(struct A):%d\n", sizeof(struct A));
    struct A* m = (struct A*)&x;
    struct B* n = (struct B*)&x;
    printf("m:%p\n", m);
    printf("n:%p\n", n);
    printf("m:%#x, %#x, %#x, %#x\n", m->a, m->b, m->c, m->d);
    printf("n:%#x, %#x, %#x, %#x\n", n->a, n->b, n->c, n->d);

    int* p = (int*)y;
    printf("*p:%#x\n", *p);
    printf("%p, %p, %p, %p", &y[0], &y[1], &y[2], &y[3]);



    struct C c;
    printf("&c.a:%p, &c.b:%p, &c.c:%p\n", &c.a, &c.b, &c.c);
    foo(p);
    int * po1 = (int*)malloc(16);
    int * po2 = (int*)malloc(16);
    printf("po1:%p, po2%p\n", po1, po2);
    free(po1);
    free(po2);

    return 0;
}