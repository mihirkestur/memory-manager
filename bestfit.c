#include<stdio.h>
#include<stdlib.h>
#include "assignment_1.h"
//defining the global variables
int size = 0;   //memory is 0 initially
char *p = NULL; //character array is null initially
//book keeping structure
typedef struct block_structure{
    int memory_type;                        //1 => allocated, 2 => unallocated
    int free_memory_size;                   //memory available for use 
    struct block_structure *next_block;     //points to next block or null 
    struct block_structure *previous_block; //points to previous block or null
}memory_block;
int size_of_structure = sizeof(memory_block);
void allocate(int n){
    //if size asked to be allocated is valid i.e. greater than book size and 0
    if(n > 0 && n > sizeof(memory_block)){
        //global pointer p pointing to a character array of size given by the client i.e. "n"
        p = (char *)malloc(sizeof(char)*n);
        size = n;                              //global size set to n
        memory_block *book = (memory_block *)p;//book keeping structure created
        book->memory_type = 2;                 //marked as free memory
        //free memory is total memory - memory of book keeping structure
        book->free_memory_size = n - sizeof(memory_block); 
        book->next_block = NULL;               //next block is null
        book->previous_block = NULL;           //previous block is null
    }
}
//changing the argument name from size to requested_size since it clashed with the global variable size
void* mymalloc(int requested_size){
    //return if requested_size greater than allocated or if requested_size negative or if p is unallocated
    if(requested_size <= 0 || requested_size > size || p == NULL){ 
        return NULL;
    }
    //traverse block has the first block; and optimal block is initialised to null.
    memory_block *traverse_block = (memory_block *)p, *optimal_block = NULL;
    //traverse the entire memory block to find the optimal place to allocate
    while(traverse_block != NULL){
        /*The first block that has free space greater than or equal to the required amount is assigned
        to the optimal block if it is NULL*/
        if((optimal_block == NULL) && (traverse_block->memory_type == 2) && (traverse_block->free_memory_size >= requested_size)){
            optimal_block = traverse_block;
        }
        /*This checks if a block is much more optimal, that is if it has lesser memory available 
        than the previously assigned block,but greater than the requested_size*/
        else if((optimal_block != NULL) && (traverse_block->memory_type == 2) && (traverse_block->free_memory_size >= requested_size)
        && (traverse_block->free_memory_size < optimal_block->free_memory_size)){
            optimal_block = traverse_block;
        }
        traverse_block = traverse_block->next_block; //moving to the next block
    }
    //if no optimal block found 
    if(optimal_block == NULL){
        return NULL;
    }
    //if some optimal block is found
    else{
        int free_size = optimal_block->free_memory_size; //the size of the optimal block is noted
        //creating a book for the unallocated portion (if any)
        //checking if remaining space has enough memory for a book structure
        if((free_size - requested_size) > sizeof(memory_block)){
            optimal_block->free_memory_size = requested_size; //size of the optimal block is changed to the allocation size
            optimal_block->memory_type = 1;         //marking optimal block as allocated
            memory_block *temp_next_block = optimal_block->next_block; //noting optimal block's next block
            memory_block *book = (memory_block *)(optimal_block + sizeof(memory_block) + (optimal_block->free_memory_size)); //creating book for unallocated block
            optimal_block->next_block = book;       //optimal block's next points to the newly created unallocated block
            book->free_memory_size = free_size - requested_size - sizeof(memory_block); //unallocated blocks size is assigned
            book->memory_type = 2;                  //marking unallocated block as unallocated
            book->next_block = temp_next_block;     //assigning next block to unallocated block
            book->previous_block = optimal_block;   //assigning the previous block as the optimal block
        }
        //if the unallocated size is less than book's size
        else{
            //changing the memory type to allocated
            optimal_block->memory_type = 1;
        }
    }
    //returns a pointer to the workable space of the optimal block. i.e. free memory
    return (char *)optimal_block + sizeof(memory_block);
}
void myfree(void *b)
{
    //if b passed is null then return
    if(b == NULL){
        return;
    }
    //getting the address of the book of the block that is to be deleted
    memory_block *delete_block = (memory_block*)((char*)b-sizeof(memory_block));
    //to see if the block requested to be deleted is valid; setting flag to 1 if not found.
    memory_block *search_block = (memory_block *)p; int flag = 1;
    while(search_block != NULL){
        if(search_block == delete_block){
            //if found flag set to 0 and normal freeing procedure takes place
            flag = 0;
            break;
        }
        search_block = search_block->next_block; //go to next block 
    }
    //if no block found; return.
    if(flag){
        return;
    }
    //perform deletion only if it is allocated
    if(delete_block->memory_type == 1){
        //noting blocks above and below of the block that is to be deleted
        memory_block *block_above, *block_below;
        block_below = delete_block->next_block;     
        block_above = delete_block->previous_block;
        //if block that is to be deleted is last block
        if(block_below == NULL){
            //if it is the only block simply mark it unallocated
            if(block_above == NULL){
                delete_block->memory_type = 2;
                return;
            }
            //if there are blocks above
            else{
                //simply mark it as unallocated if above is occupied
                if(block_above->memory_type == 1){
                    delete_block->memory_type = 2;
                }
                //if above block is free then merge 
                else{
                    delete_block->memory_type = 2;
                    delete_block->previous_block->next_block = delete_block->next_block;
                    delete_block->previous_block->free_memory_size = delete_block->previous_block->free_memory_size + delete_block->free_memory_size + sizeof(memory_block);
                    //delete block now becomes the previous block
                    delete_block = delete_block->previous_block;
                    //so, block above is the next block to delete block
                    block_below = delete_block->next_block;
                    //block below becomes the previous block to delete block
                    block_above = delete_block->previous_block;
                }
                
            }
            
        }
        //for all other cases
        if(!(block_above != NULL && block_below == NULL)){
            delete_block->memory_type = 2;
            //if there is a block above and it is free then merge
            if(block_above != NULL && block_above->memory_type == 2){
                delete_block->previous_block->next_block = delete_block->next_block;
                delete_block->next_block->previous_block = delete_block->previous_block;
                delete_block->previous_block->free_memory_size = delete_block->previous_block->free_memory_size + delete_block->free_memory_size+sizeof(memory_block);
                //delete block made as the block above
                delete_block = delete_block->previous_block;
                //so block below becomes next block of delete block
                block_below = delete_block->next_block;
                //then, block above becomes the previous block of the delete block
                block_above = delete_block->previous_block;
            }
            //if there is a block below and it is free then merge
            if(block_below != NULL && block_below->memory_type == 2){
                //free size noted
                int free_size = delete_block->next_block->free_memory_size;
                delete_block->next_block = delete_block->next_block->next_block;
                //if there is a block below then the prevous block points to the current block
                if(delete_block->next_block != NULL){
                    delete_block->next_block->previous_block = delete_block;
                }
                delete_block->free_memory_size = delete_block->free_memory_size + free_size + sizeof(memory_block);
            }
        }
    }
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
        printf("%d\t%ld\t%d\n",index,sizeof(memory_block),0);   //print the book structure
        index = index + sizeof(memory_block);
        printf("%d\t%d\t%d\n",index,traverse_blocks->free_memory_size,traverse_blocks->memory_type);
        index = index + traverse_blocks->free_memory_size;
        traverse_blocks = traverse_blocks->next_block;
    }
}
