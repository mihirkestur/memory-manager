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
    //traverse block has the first block; and optimal block is initialised to null.
    memory_block *traverse_block = (memory_block *)p, *optimal_block = NULL;
    //if size greater than allocated or if size negative
    if(size < 0){ //size > size ||
        return NULL;
    }
    //traverse the entire memory block to find the optimal place to allocate
    while(traverse_block != NULL){
        /*optimal block is assigned to the first block that has free space 
        greater than or equal to the required amount*/
        if((optimal_block == NULL) && (traverse_block->memory_type == 2) && (traverse_block->free_memory_size >= size)){
            optimal_block = traverse_block;
        }
        /*this checks for a block that is much more optimal, that is if it has lesser memory available 
        than the previously assigned block,but greater than the required size*/
        else if((optimal_block != NULL) && (traverse_block->memory_type == 2) && (traverse_block->free_memory_size >= size)
        && (traverse_block->free_memory_size < optimal_block->free_memory_size)){
            optimal_block = traverse_block;
        }
        //moving to the next block
        traverse_block = traverse_block->next_block; 
    }
    //if no optimal block found
    if(optimal_block == NULL){
        return NULL;
    }
    //if some optimal block is found
    else{
        memory_block *temp_next_block = optimal_block->next_block; //noting optimal block's next block
        int free_size = optimal_block->free_memory_size; //the size of the optimal block is noted
        optimal_block->free_memory_size = size; //size of the optimal block is changed to the allocation size
        optimal_block->memory_type = 1; //marking optimal block as allocated
        //creating a book for the unallocated block (if any)
        if((free_size - size) > sizeof(memory_block)){
            memory_block *book = (memory_block *)(optimal_block + (optimal_block->free_memory_size) + 1); //creating book for unallocated block
            optimal_block->next_block = book; //optimal block's next points to the newly created unallocated block
            book->free_memory_size = free_size - size - sizeof(memory_block); //unallocated blocks size is assigned
            book->memory_type = 2; //marking unallocated block as unallocated
            book->next_block = temp_next_block; //assigning next block to unallocated block
            book->previous_block = optimal_block; //assigning the previous block as the optimal block
        }
        //if the unallocated size is less than book's size
        else{
            //changing the memory type to allocated
            optimal_block->memory_type = 1;
        }
    }
    //returns a pointer to the optimal block i.e. allocated block.
    return optimal_block;
}
void myfree(void *b){
    if(b == NULL){
        return;
    }
    memory_block *delete_block = (memory_block *)b;
    //if the block requested to be deleted is allocated, only then it is elligible to be freed.
    if(delete_block->memory_type == 1){
        memory_block *block_above = delete_block->previous_block, *block_below = delete_block->next_block;
        //if there is a block below and the block is free; then merge
        if((block_below != NULL) && (block_below->memory_type == 2)){
            
            delete_block->next_block = block_below->next_block;
            delete_block->free_memory_size = sizeof(memory_block) + block_below->free_memory_size + delete_block->free_memory_size;
            delete_block->memory_type = 2;
        }
        //if there is a block above and the block is free; then merge
        if((block_above != NULL) && (block_above->memory_type == 2)){
            block_above->next_block = delete_block->next_block;
            block_above->free_memory_size = sizeof(memory_block) + delete_block->free_memory_size + block_above->free_memory_size;
            block_above->memory_type = 2;
        }
        //if there is a block below but is not free; then simply mark it as freed.
        if((block_below != NULL) && (block_below->memory_type == 1)){
            delete_block->memory_type = 2;
        }
        //if there is a block above but is not free; then simply mark it as freed.
        if((block_above != NULL) && (block_above->memory_type == 1)){
            delete_block->memory_type = 2;
        }
        //if there is no block above or below; then also simply mark it as freed
        if((block_above == NULL) && (block_below == NULL)){
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
    //start from beginning 
    memory_block *traverse_blocks = (memory_block *)p;
    //index variable prints the start of each block
    int index = 0;
    //traverse entire memory to find blocks
    while(traverse_blocks != NULL){
        printf("%d\t%ld\t%d\n",index,sizeof(memory_block),0);
        index = index + sizeof(memory_block);
        printf("%d\t%d\t%d\n",index,traverse_blocks->free_memory_size,traverse_blocks->memory_type);
        index = index + traverse_blocks->free_memory_size;
        traverse_blocks = traverse_blocks->next_block;
    }
}