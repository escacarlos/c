/* detab.c */

#include <stdio.h>
#include "tabstops.h"

int main(int argc, char *argv[])
{
	int col, c, dist;

	parsestops(argc, argv);

	col = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (dist = dist2stop(col); dist > 0; --dist) {
				putchar(' ');
				++col;
			}
		} else {
			putchar(c);
			if (c == '\n')
				col = 0;
			else if (c == '\b' && col > 0)
				--col;
			else
				++col;
		}
	}
	return 0;
}