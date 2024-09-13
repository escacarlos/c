#include <stdio.h>

int main() {
	int v;

	printf("Enter an integer greater than zero: ");
	scanf("%d", &v);

	if(v<1) return(1);

	printf("%d is an %s number.\n", v, (v%2)?"odd":"even");

	return(0);
}

