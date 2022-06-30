#include <stdio.h>


int main(int argc, int** argv)
{
    int a = 1;
    if (argc > 1) {
        a = atoi(argv[1]);
    }
    switch (a) {
        case 1: case 2: case 3:
            printf("111\n");
            break;
        case 4: case 5: case 6:
            printf("222\n");
            break;
    }
    return 0;
}