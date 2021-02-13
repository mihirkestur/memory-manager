Name    :   Mihir Madhusudan Kestur
SRN     :   PES1UG19CS272
SECTION :   E 
SEMESTER:   4

Last three digits of my srn = 272 => (272%3) + 1 = 3

BEST FIT ALLOCATION POLICY

In best fit policy, the block having size that is greater than or equal to the requested size but, least size
among the available blocks of memory is returned/allocated.

Book structure has 4 fields;
memory_type     ; Indicates if the memory block is allocated(1) or unallocated(2)
free_memory_size; Has the free memory available/in use i.e. (memory of the block - size of book structure) 
next_block      ; This is a pointer that points to the next book keeping structure (next memory block) or NULL
previous_block  ; This is a pointer that points to the previous book keeping structure (previous memory block) or NULL

Allocation:
?what if it is already allocated?
Allocate size n to global character array
Size should be strictly greater than size of book keeping structure

Myalloc:
The global character array should be allocated, if not function returns NULL
The size requested should be strictly greater than zero and less than or equal to total size
Entire memory is traversed to find the most optimal block that satisfies all conditions of best fit policy
If there is no block found return NULL


Myfree:
If a NULL pointer is passed, function simply returns
The entire memory array is traversed to find if the pointer passed points to a valid memory block in the array
If it is not there then function simply returns
The block requested to be deleted is also checked if it is allocated
If a valid memory block is found, there can be 6 possibilities:
1   There is block above and it is empty        => The block is merged
2   There is block above and it is not empty    => Left alone
3   There is no block above                     => Nothing can be done
4   There is block below and it is empty        => The block is merged 
5   There is block below and it is not empty    => Left alone
6   There is no block below                     => Nothing can be done
So taking care of these conditions every time free function is called, there can never be two consecutive blocks
which are free

display_mem_map:
Display function prints the entire memory array. The first column indicates the starting index for a particular 
memory block. The second column represents the memory consumed by that particular block. The last column shows
the type of that particular block, i.e. 0 => book keeping record, 1 => Allocated memory block, 2 => Free space.

print_book:
This function when called simply prints the size of the book keeping structure.

what happens if i request size = total memory
