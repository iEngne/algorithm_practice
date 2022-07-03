#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

int values[] = { 88, 56, 100, 2, 25 };

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)b - *(int*)a );
}


void ttt(int a){
    printf("%d\n", a);
    return;
}

int main()
{
    int an[] = {1,2,3,4};
    ++an[0];
    printf("%d\n", an[0]);
    int * p = &an[0];
    int n;
    printf("p:%p, %d\n", p, *p);
    p++;
    printf("p++:%p, %d\n",p, *p); 
    printf("before\n");
    for( n = 0 ; n < 5; n++ ) {
        printf("%d ", values[n]);
    }

    qsort(values, 5, sizeof(int), cmpfunc);

    printf("\nafter:\n");
    for( n = 0 ; n < 5; n++ ) {
        printf("%d ", values[n]);
    }
    printf("\n");
    int a = 7;
    int b = 4;
    int c = 7/2*2;
    printf("%d\n", c);

    printf("%f\n", fmax(-1, -5));

    char a1[] = {'1', '2', '3', '4', '5'};
    sprintf(a1, "%s", "456");
    int i = 0;
    // 经测试sprintf会在结尾自动补一个0
    for (; i < sizeof(a1)/sizeof(char); ++i){
        printf("%d\n",a1[i]);
    }

    /* 将十六进制字符串转为int型 */
    char*  s = "C83A35230831";
    int low,high;
    i = 0;
    while (s[i])
    {
        high = s[i];
        low = s[i + 1];
        /* 大写字母转小写字母 */
        if (high >= 'a')
        {
            high = high - ('a' - 'A');
        }
        if (low >= 'a')
        {
            low = low - ('a' - 'A');
        }
        high = high - '0';
        low = low - '0';
        /* 如果是字母,转成数字 */
        if (high > 9)
        {
            high -= ('A' - '9' - 1);
        }
        if (low > 9)
        {
            low -= ('A' - '9' - 1);
        }
        printf("%5d ", high * 16 + low);
        i += 2;
    }
    printf("\n");
    char* str_buf = "Ceabefffaabb";
    int ref_bssid[6];
    for (i = 0; i < 6; i++)
    {
        sscanf(str_buf, "%02x", &ref_bssid[i]);
        printf("%#x ", ref_bssid[i]);
        str_buf += 2;
    }
    printf("\n");
    return(0);
}