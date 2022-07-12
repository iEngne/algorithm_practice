#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_hdl(int sig) {
    printf("signal = %d\n", sig);
    return;
}


int main(void) {
    signal(SIGABRT, sig_hdl);
    printf("111\n");
    // abort(); )
    while (1) {
        sleep(2);
        printf("sleeping\n");
    }
    printf("222\n");
    return 0;
}