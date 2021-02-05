#include<stdio.h>
#include<stdlib.h>
#include "assignment_1.h"
//defining the global variables
int size = 0;
char *p = NULL;
typedef struct block_structure{
    int memory_type; //Encoded_status : 0 - book, 1 - allocated, 2 - free
    int free_memory_size; //block size in bytes
    struct block_structure *next_block;
    struct block_structure *previous_block;
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
    book->memory_type = 2; //free memory
    book->free_memory_size = n - sizeof(memory_block);
    book->next_block = NULL;
    book->previous_block = NULL;
}
void* mymalloc(int size){
    memory_block *traverse_block = (memory_block *)p, *optimal_block = NULL;
    //if size greater than allocated or if size negative
    if(size < 0){ //size > size ||
        return NULL;
    }
    while(traverse_block != NULL){
        if((optimal_block == NULL) && (traverse_block->memory_type == 2) && (traverse_block->free_memory_size >= size)){
            optimal_block = traverse_block;
        }
        else if((optimal_block != NULL) && (traverse_block->memory_type == 2) && (traverse_block->free_memory_size >= size)
        && (traverse_block->free_memory_size < optimal_block->free_memory_size)){
            optimal_block = traverse_block;
        }
        traverse_block = traverse_block->next_block; 
    }
    if(optimal_block == NULL){
        return NULL;
    }
    else{
        int free_size = optimal_block->free_memory_size;
        optimal_block->free_memory_size = size;
        optimal_block->memory_type = 1;
        memory_block *book = (memory_block *)(optimal_block + optimal_block->free_memory_size);
        optimal_block->next_block = book;
        book->free_memory_size = free_size - size - sizeof(memory_block);
        book->memory_type = 2;
        book->next_block = NULL;
        book->previous_block = optimal_block;
        return optimal_block;
    }
}
void myfree(void *b){
    if(b == NULL){
        return;
    }
    memory_block *delete_block = (memory_block *)b;
    if(delete_block->memory_type == 1){
        memory_block *block_above = delete_block->previous_block, *block_below = delete_block->next_block;
        if((block_below != NULL) && (block_below->memory_type == 2)){
            printf("below\n");//debug line remove!
            delete_block->next_block = block_below->next_block;
            delete_block->free_memory_size = sizeof(memory_block) + block_below->free_memory_size + delete_block->free_memory_size;
            delete_block->memory_type = 2;
        }
        if((block_above != NULL) && (block_above->memory_type == 2)){
            printf("above\n");//debug line remove!
            block_above->next_block = delete_block->next_block;
            block_above->free_memory_size = sizeof(memory_block) + delete_block->free_memory_size + block_above->free_memory_size;
            block_above->memory_type = 2;
        }
        if((block_below != NULL) && (block_below->memory_type == 1)){
            printf("below none\n");//debug line remove!
            delete_block->memory_type = 2;
        }
        if((block_above != NULL) && (block_above->memory_type == 1)){
            printf("above none\n");//debug line remove!
            delete_block->memory_type = 2;
        }
        if((block_above == NULL) && (block_below == NULL)){
            printf("entire block\n");//debug line remove!
            delete_block->memory_type = 2;
        }
    }
    return;
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
        printf("%d\t%ld\t%d\n",index,sizeof(memory_block),0);
        index = index + sizeof(memory_block);
        printf("%d\t%d\t%d\n",index,traverse_blocks->free_memory_size,traverse_blocks->memory_type);
        index = index + traverse_blocks->free_memory_size;
        traverse_blocks = traverse_blocks->next_block;
    }
}