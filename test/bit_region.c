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
#include <stdio.h>


struct A 
{
    unsigned int a:2;
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



int main(void)
{
    /** 字节序 高地址      ------>        低地址
     *  0b 10101010 11001010 10001011 10110011
     *                         位序 bit7-->bit0
     * 小端字节序，其内部位序是最低有效位在bit0的地方
     */
    int x[] = {0b10101010110010101000101110110011, 0xbbbbbbbb};
    printf("sizeof(struct A):%d\n", sizeof(struct A));
    struct A* m = (struct A*)&x;
    struct B* n = (struct B*)&x;
    printf("a:%p\n", m);
    printf("b:%p\n", n);
    printf("m:%#x, %#x, %#x, %#x\n", m->a, m->b, m->c, m->d);
    printf("n:%#x, %#x, %#x, %#x\n", n->a, n->b, n->c, n->d);
    return 0;
}