#include <stdio.h>
int main()
{
	int i;
	int* ia;
	i = 10;
	ia = &i;

	printf (" The adddress of i is %8li \n", ia);
	printf (" The value at that location is %d\n", i);
	printf (" The value at that location is %d\n", *ia);
	*ia = 50;
	printf (" The value of i is %d\n", i);
}
