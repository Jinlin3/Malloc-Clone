# CS214 - mylittlemalloc (Jack Lin)
### Reporting Errors
Within the mymalloc() and myfree() functions, there are multiple guard clauses that will detect misuse and report them using the file name and line number given in the parameters.
### Error Testing
#### My library must satisfy these conditions:
* mymalloc() reserves only unallocated memory
* mymalloc() returns a pointer to an object that does not overlap with other chunks of allocated memory
* myfree() deallocates memory only when currently allocated
* myfree() coalesces adjacent free blocks
#### My Test Plan:
1. Allocate ten 20-byte blocks

Expected Outcome:
Ten 24-byte blocks (struct node* size is 4 bytes) and one last block being free with 3856 bytes

2. Allocate a 5000-byte block

Expected Outcome:
Getting an error message

3. Free each block starting from the last and then immediately trying to free again

Expected Outcome:
Error messages on the 2nd free attempt
One 4096-byte chunk

4. Allocate four 100-byte blocks

Expected Outcome:
Four 100-byte blocks and one last block being free with 3680 bytes

5. Free block 1 and 3, and then free block 2

Expected Outcome:
One free block of 312 bytes followed by an allocated block of 104 bytes followed by a free block of 3680 bytes

**Will use printMem() to view linked list structure for testing!**
