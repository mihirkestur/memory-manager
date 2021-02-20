**BEST FIT ALLOCATION POLICY**

In best fit policy, the block having size that is greater than or equal to the requested size but, least size
among the available blocks of memory is returned/allocated.

Book structure has 4 fields;<br>
**memory_type**     ; Indicates if the memory block is allocated(1) or unallocated(2)<br>
**free_memory_size**; Has the free memory available/in use i.e. (memory of the block - size of book structure) <br>
**next_block**      ; This is a pointer that points to the next book keeping structure (next memory block) or NULL<br>
**previous_block**  ; This is a pointer that points to the previous book keeping structure (previous memory block) or NULL<br>

**Allocation:**
Allocate size n to global character array<br>
Size should be strictly greater than size of book keeping structure<br>

**Myalloc:**
The global character array should be allocated, if not function returns NULL<br>
The size requested should be strictly greater than zero and less than or equal to total size<br>
Entire memory is traversed to find the most optimal block that satisfies all conditions of best fit policy<br>
1   The first available free memory block is allocated<br>
2   The memory block allocated should have the least free memory amongst the blocks which are free<br>
3   In case the remaining free space after allocation of a particular optimal block is less than or equal to the
size of the book structure the remaining free space is allocated to the optimal block itself.<br>
If there is no block found return NULL

**Myfree:**
If a NULL pointer is passed, function simply returns<br>
The entire memory array is traversed to find if the pointer passed points to a valid memory block in the array<br>
If it is not there then function simply returns<br>
The block requested to be deleted is also checked if it is allocated<br>
If valid memory is found it is deleted<br>
Checks are made to see if there are any blocks that are free and are then merged <br>

**display_mem_map:**
Display function prints the entire memory array. The first column indicates the starting index for a particular 
memory block. The second column represents the memory consumed by that particular block. The last column shows
the type of that particular block, i.e. 0 => book keeping record, 1 => Allocated memory block, 2 => Free space.

**print_book:**
This function when called simply prints the size of the book keeping structure.

**To run**
```bash
$ gcc *.c
$ ./a.out
```
