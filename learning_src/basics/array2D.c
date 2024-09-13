#include <stdio.h>

void printarr(int a[3][2]);
void printdetail(int a[3][2]);
void print_usingptr(int a[3][2]);

int main()
{
	int a[3][2];
	int count=0;
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<2; j++)
		{
			a[i][j] = count;
			count++;
		}
	}
	
	printarr(a);
	printdetail(a);
	print_usingptr(a);
}

void printarr(int a[3][2])
{
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<2; j++)
		{
			printf("value in array %d\n",a[i][j]);
		}
	}
		
}

void printdetail(int a[3][2])
{
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<2; j++)
		{
			printf("value in array %d and address is %16lu\n",a[i][j],&a[i][j]);
		}
	}
}

void print_usingptr(int a[3][2])
{
	int *b;
	b=a;
	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<2; j++)
		{
			printf("value in array %d and address is %16lu\n",*b,b);
			b++;
		}
	}
}
