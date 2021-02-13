#include <stdio.h>
#include <stdlib.h>
#include "assignment_1.h"
void main()
{
	allocate(1000);
	
	char* p1 = (char*)mymalloc(50*sizeof(char));
	
	char* p2 = (char*)mymalloc(100*sizeof(char));
	
	char* p3 = (char*)mymalloc(500*sizeof(char));
	
	char* p4 = (char*)mymalloc(101*sizeof(char));
	
	display_mem_map();
	printf("\n");
	
	myfree(p4);
	
	display_mem_map();
	printf("\n");
	
	char* p5 = (char*)mymalloc(50*sizeof(char));
	
	display_mem_map();
	printf("\n");
	
	myfree(p5);
display_mem_map();
	printf("5\n");
	myfree(p1);
	display_mem_map();
	printf("1\n");
	myfree(p2);
	
	display_mem_map();
	printf("2\n");

	myfree(p3);
	
	display_mem_map();
	printf("3\n");
}
