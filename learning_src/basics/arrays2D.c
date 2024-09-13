#include <stdio.h>
void printarr(int a[]);
void printdetail(int a[]);
void print_usingptr(int a[]);
int main()
{
	int a[5];
	for(int i = 0; i<5; i++)
	{ 
		a[i] = i;
	}
	printarr(a);
	printdetail(a);
	print_usingptr(a);
}

void printarr(int a[])
{
	for (int i = 0; i < 5; i++)
	{
		printf("value in array %d\n", a[i]);
	}
}

void printdetail(int a[])
{
	for(int i = 0; i<5; i++)
	{
		printf("value in array %d and address is %16lu\n", a[i],&a[i]);
	}
}

void print_usingptr(int a[])
{
	int *b;
	b=a;
	for(int i=0; i<5; i++)
	{
		printf("value in array %d and address is %16lu\n",*b,b);
		b++;
	}
}
