#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>


struct __kfifo {
	unsigned int	in;
	unsigned int	out;
	unsigned int	mask;
	unsigned int	esize;
	void		*data;
};

#define __STRUCT_KFIFO_COMMON(datatype, recsize, ptrtype) \
	union { \
		struct __kfifo	kfifo; \
		datatype	*type; \
		const datatype	*const_type; \
		char		(*rectype)[recsize]; \
		ptrtype		*ptr; \
		ptrtype const	*ptr_const; \
	}

#define __STRUCT_KFIFO(type, size, recsize, ptrtype) \
{ \
	__STRUCT_KFIFO_COMMON(type, recsize, ptrtype); \
	type		buf[((size < 2) || (size & (size - 1))) ? -1 : size]; \
}

#define STRUCT_KFIFO(type, size) \
	struct __STRUCT_KFIFO(type, size, 2, type)

#define kfifo_recsize(fifo)	(sizeof(*(fifo)->rectype))


typedef int (*pfunc)(int);


#define A (1)

/**
 * @brief 测试read的系统调用
 * 
 * @return int 
 */
int main(void) {

    FILE* fp = fopen("test_const.c", "r+");
    if (!fp) {
        printf("open error!\n");
        return -1;
    }
    char buffer[1000] = {0};
    fread(buffer, 1, 999, fp);
    printf("%s\n", buffer);
    fclose(fp);
	STRUCT_KFIFO(int, 8) fifo;
    printf("%d\n", kfifo_recsize(&fifo));

    //signal(2,SIG_IGN);
    while (1) {
        sleep(1);
        printf("sleeping...\n");
    }
    return 0;
}