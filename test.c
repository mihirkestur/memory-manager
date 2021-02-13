#include <stdio.h>
#include "assignment_1.h"
void main()
{
	allocate(200);
	char *a = (char *)mymalloc(0*sizeof(char));
	display_mem_map();
	printf("\n");
	char *b = (char *)mymalloc(20*sizeof(char));
	display_mem_map();
	printf("\n");
	char *c = (char *)mymalloc(20*sizeof(char));
	display_mem_map();
	printf("\n");
	myfree(b);
	display_mem_map();
	myfree(c);
	display_mem_map();
	printf("\n");
	allocate(100);
	display_mem_map();
}
