/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015
 * mem.h is a header file that includes the externally used functions 
 */

#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <inttypes.h>

/* allocates a block of "size" bytes of memory and 
 * returns a pointer to the block
 */ 
void* getmem(uintptr_t size);

/* frees the block of memory the pointer "p" points to
 * and returns it to the free list
 */
void freemem(void* p);

/* sets and updates the values in the passed pointers based on the 
 * current status of the memory heap. The three given pointers point to:
 * total_size: total size in bytes allocated for the memory heap
 * total_free: total size in bytes in the free list including headers/links
 * n_free_blocks: number of free blocks in the free list 
 */
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks);

/* prints the information about each block on the free list
 * to the given file "f." The information should include
 * hexadecimal numbers indicating the address and length of each block
 */
void print_heap(FILE * f);

/* checks whether there are errors with the free list
 */
void check_heap();

#endif
