#include <stdio.h>

int main()
{
	int a,b;

	a = 5; b = 20;

	char s = a>b ? 'a' : 'b';
	

	printf("In this case, variable %c is greater.\n",
			s);

	return(0);
}

