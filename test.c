#include <stdio.h>
#include "assignment_1.h"
void main()
{
	allocate(50);
	for(int i = 0; i < 50; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n"); 


	char *q1 = mymalloc(2 * sizeof(char));
	// q1[0] = 0x1;
	// q1[1] = 0x1;
	for(int i = 0; i < 20; ++i)
	{
		printf("%d ", q1[i]);
	}
	printf("\n"); 

	char *q2 = mymalloc(3 * sizeof(char));
	// q2[0] = 0x2;
	// q2[1] = 0x2;
	for(int i = 0; i < 20; ++i)
	{
		printf("%d ", q2[i]);
	}
	printf("\n");

	char *q3 = mymalloc(5 * sizeof(char));

	for(int i = 0; i < 50; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n");

	for(int i = 0; i < 80; ++i)
	{
		printf("%d ", p[i]);
	} 
	//printf("\n\n\n");

	myfree(q2);
	
	for(int i = 0; i < 80; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n\n\n");

	char *q4 = mymalloc(5 * sizeof(char));
	// myfree(q3);
	for(int i = 0; i < 50; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
	

	display_mem_map();

}
