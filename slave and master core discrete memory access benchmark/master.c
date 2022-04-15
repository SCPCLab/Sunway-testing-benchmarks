#include<stdio.h>
#include<stdlib.h>
#include<athread.h>


extern SLAVE_FUN(func)();

static inline unsigned long rpcc()
{
	unsigned long time;
	asm("rtc %0": "=r" (time) : );
	return time;
}

int main() {

	unsigned long st , ed;
	
	int i, j;
	int *a = (int*)malloc(1000*1000*sizeof(int));
	int *b = (int*)malloc(1000*1000*sizeof(int));
	int *c = (int*)malloc(1000*1000*sizeof(int));
	int *d = (int*)malloc(1000*1000*sizeof(int));

	char *pr = (char*)malloc(4*50*sizeof(char));

	int **t[3];
	t[0] = c;
	t[1] = d;
	t[2] = (int*)pr;

	int tmp;

	for(i=0; i<1000; i+=1)
	{
		for(j=0; j<1000; j+=1)
		{
			*(a+i*1000+j) = i + j + 3;
			*(b+i*1000+j) = i + j + 3;
			*(c+i*1000+j) = i + j + 3;
			*(d+i*1000+j) = i + j + 3;
		}
	}

	st = rpcc();
	for(i=0; i<1000; i+=1)
	{
		for(j=0; j<1000; j+=1)
		{
			tmp = *(a+i*1000+j);
			//*(a+i*100+j)-=1;
			//*(a+i*100+j)+=1;
		}
	}
	ed = rpcc();

	printf("Master: 主存连续访问耗时：%ld\n", ed-st);


	st = rpcc();
	for(j=0; j<1000; j+=1)
	{
		for(i=0; i<1000; i+=1)
		{
			tmp = *(b+i*1000+j);
			//*(b+i*100+j)-=1;
			//*(b+i*100+j)+=1;
		}
	}
	ed = rpcc();

	printf("Master: 主存离散访问耗时：%ld\n", ed-st);

	athread_init();                 
	athread_spawn(func, t);  
	athread_join();
	athread_halt();

	puts(pr);
	puts(pr+50);
	puts(pr+100);
	puts(pr+150);

	return 0;

}
