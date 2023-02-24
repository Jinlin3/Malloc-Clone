# CS214 - mylittlemalloc (Jack Lin - jjl327)
### mymalloc()
The mymalloc() function was primarily implemented using a linked list structure. Each node in the structure contains a size_t value that specifies how large each chunk is and an integer value specifying whether it is already in use. The function takes the input's size and adds the size of the metadata to avoid underestimating space needed.

To start, the function traverses through the linked list, looking for a chunk that meets the space requirement. Once found, if the chunk exceeds the space requirement, the function splits the chunk into 2 pieces; the first one labeled as "in-use" and the second one as "free". The first chunk will be split perfectly into the size required for the payload and the metadata while the second chunk will be the excess space. If the whole of the linked list has been traversed and no nodes have been found, mymalloc() will throw an error. Similarly, if the caller requests space larger than 4096 at the start, mymalloc() will throw an error.

### myfree()
The myfree() function primarily used guard clauses in order to check for errors early before preceding on with deallocation. A pointer is set to the head of the linked list and is traversed through the nodes until a chunk with the caller's size requirements are found, or until the end of the list. While traversing, the function compares each node's address in memory to the user's pointer to check if it is a valid pointer. Before deallocation, the function checks if the pointer has already been freed by checking the integer value associated with usage. If all conditions are met, it frees the current chunk and coalesces adjacent free chunks by setting a pointer behind the current pointer, adding sizes together, and using linked list techniques to remove extra nodes. It also checks the chunks in front of the current chunk and uses the same techniques.

Within the mymalloc() and myfree() functions, there are multiple guard clauses that will detect misuse and report them using the file name and line number given in the parameters.
### Error Testing
#### My library must satisfy these conditions:
1. mymalloc() reserves only unallocated memory
2. mymalloc() returns a pointer to an object that does not overlap with other chunks of allocated memory
3. mymalloc() returns an error when memory requested exceeds the memory available
4. myfree() deallocates memory only when currently allocated
5. myfree() coalesces adjacent free blocks
#### My Test Plan:
* Allocate ten 20-byte blocks (for checking conditions 1 and 2)

Expected Outcome:
Ten 24-byte blocks (struct node* size is 4 bytes) and one last block being free with 3856 bytes

* Allocate a 5000-byte block (for checking condition 3)

Expected Outcome:
Getting an error message

* Free each block starting from the last and then immediately trying to free again (for checking condition 4)

Expected Outcome:
Error messages on the 2nd free attempt
One 4096-byte chunk

**(Tests 4 and 5 are for checking conditions 4 and 5)**

* Allocate four 100-byte blocks

Expected Outcome:
Four 100-byte blocks and one last block being free with 3680 bytes

* Free block 1 and 3, and then free block 2

Expected Outcome:
One free block of 312 bytes followed by an allocated block of 104 bytes followed by a free block of 3680 bytes

**Will use printMem to view linked list structure for testing!**