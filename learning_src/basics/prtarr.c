#include <stdio.h>

void printarr(int *a[]);
void printarr_uningprt(int *a[]);
int *a[5];

int main()
{
	int i1=4, i2=3, i3=2, i4=1, i5=0;
	a[0]=&i1;
	a[1]=&i2;
	a[2]=&i3;
	a[3]=&i4;
	a[4]=&i5;

	printarr(a);
	printarr_uningprt(a);
}

void printarr(int *a[])
{
	printf("Address			Address in array		Value\n");
	for(int j=0;j<5;j++)
	{
		printf("%16u		%16u		%d\n",&a[j],a[j],*a[j]);
	}
}

void printarr_uningprt(int *a[])
{
	int j=0;
	printf("using pointer\n");
	for(int j=0;j<5;j++)
	{
		printf("%16u		%16u		%d\n",a,*a,**a);
		a++;
	}
}
