book structure:
has 4 fields;
size available: i.e free size, excluding the size of book
status: 1,2; allocated,unallocated
next book
previous book

edge cases
allocate: if i pass amount more than physical memory
what happens if i do allocate (0) or negative value

myalloc:
if p unallocated
if size greater than allocated or size negative
check if size available is greater than or equal to size
and also memory type is 2 i.e. free

myfree:
what happens if i pass some unallocated pointer
1   there is block above and is empty
2   there is block above and is not empty
3   there is no block above
4   there is block below and is empty
5   there is block below and is not empty
6   there is no block below

take care of allocated nothing but asked for gold