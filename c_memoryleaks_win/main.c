#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int* offset_x = (int*)malloc(sizeof(int));
	int* offset_y = (int*)malloc(sizeof(int));

	if (offset_x == NULL || offset_y == NULL)
	{
		return 1;
	}

	*offset_x = 10;
	*offset_y = 20;

	free(offset_x);
	free(offset_y);
	//_CrtDumpMemoryLeaks();
	return 0;
}