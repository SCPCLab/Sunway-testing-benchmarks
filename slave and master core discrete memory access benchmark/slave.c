#include "slave.h"
#include "stdlib.h"

static inline unsigned long rtc_()
{
	unsigned long rpcc;
	asm volatile("rcsr %0, 4":"=r"(rpcc));
	return rpcc;
}

void func(int **t) {
	volatile int myid =  athread_get_id(-1);
	int *c = t[0];
	int *d = t[1];
	char *pr = (char*)t[2];
	int *a_slave;

	unsigned long st , ed;
	
	int i, j, tmp, z;

	if(myid==0)
	{
		st = rtc_();
		for(z=0; z<100; z++)
		{
			a_slave = (int*)malloc(sizeof(int)*100*100);

			for(i=0; i<100; i++)
			{
				for(j=0; j<100; j++)
				{
					*(a_slave+i*100+j) = i + j + 3;
				}
			}

			for(i=0; i<100; i++)
			{
				for(j=0; j<100; j++)
				{
					tmp=*(a_slave+i*100+j);
				}
			}

			free(a_slave);
		}

		ed = rtc_();

		sprintf(pr, "Slave: 片上内存连续访存：%ld", ed-st);
	}

	if(myid==1)
	{
		st = rtc_();
		for(z=0; z<100; z++)
		{
			a_slave = (int*)malloc(sizeof(int)*100*100);

			for(j=0; j<100; j++)
			{
				for(i=0; i<100; i++)
				{
					*(a_slave+i*100+j) = i + j + 3;
				}
			}

			for(j=0; j<100; j++)
			{
				for(i=0; i<100; i++)
				{
					tmp=*(a_slave+i*100+j);
				}
			}

			free(a_slave);
		}

		ed = rtc_();

		sprintf(pr+50, "Slave: 片上内存离散访存：%ld", ed-st);
	}

	if(myid==2)
	{
		//GLD memory access
		st = rtc_();
		for(i=0; i<1000; i++)
		{
			for(j=0; j<1000; j++)
			{
				tmp = *(c+i*1000+j);
			}
		}
		ed = rtc_();
		sprintf(pr+100, "Slave: GLD访问主存-连续:%ld", ed-st);
	}

	if(myid==3)
	{
		st = rtc_();
		for(j=0; j<1000; j++)
		{
			for(i=0; i<1000; i++)
			{
				tmp = *(d+i*1000+j);
			}
		}
		ed = rtc_();
		sprintf(pr+150, "Slave: GLD访问主存-离散:%ld", ed-st);

	}
}