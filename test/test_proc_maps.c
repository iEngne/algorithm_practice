#include <stdio.h>
#include <unistd.h>

struct A {
    int a;
    struct B* b; // 这里是指针，即使struct B此时还没有定义也没关系，如果是
                 // struct B b; 就不行
};

struct B {
    int b;
};


int main(void) {
    int i = 0;
    while (1) {
        sleep(1);
        printf("%d\n", i++);
    }
    return 0;
}