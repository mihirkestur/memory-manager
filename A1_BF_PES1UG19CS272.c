#include<stdio.h>
#include<stdlib.h>
#include "assignment_1.h"
int size;
char *p;
typedef struct block_structure{
    int memory_type; //Encoded_status : 0 - book, 1 - allocated, 2 - free
    int free_memory_size; //block size in bytes
    struct block_structure *next_block;
}memory_block;
/*
allocate function designates a memory block of size "n", 
all operations are performed within this memory i.e. allocation/deallocation
*/
void allocate(int n){
    //here, the entire memory is allocated to a global pointer p ; character array
    p = (char *)malloc(sizeof(char)*n);
    size = n;
    memory_block *book = (memory_block *)p;
    book->memory_type = 0;
    book->free_memory_size = n - sizeof(memory_block);
    book->next_block = NULL;
}
void* mymalloc(int size){

}
void myfree(void *b){

}
void print_book(){
    //size of the book-keeping structure is printed
    long int size_of_structure = sizeof(memory_block);
    printf("%ld\n", size_of_structure);
}
void display_mem_map(){
    memory_block *traverse_blocks = (memory_block *)p;
    int index = 0;
    while(traverse_blocks != NULL){
        printf("%d\t%ld\t%d\n",index,sizeof(memory_block),traverse_blocks->memory_type);
        printf("%d\t%d\t%d\n",index,traverse_blocks->free_memory_size,traverse_blocks->memory_type);
        traverse_blocks = traverse_blocks->next_block;
        index = index + traverse_blocks->free_memory_size;
    }
}