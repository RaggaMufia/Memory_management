/* Daehyun Kim & Peter Won */
/* CSE374 Hw 5 */
/* Feb 17 2015 */
/* getmem.c is a source file that allocates a block of memory */

#include <stdlib.h>
#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

void request_space();
Block* find_block(uintptr_t size);

/* takes in "size" and allocates a block of memory as big as the "size"
 * in bytes and returns a pointer to the block of memory
 */
void* getmem(uintptr_t size) {
    check_heap();
    if (size == 0) {
        return NULL;
    }

    if (size % HEADER_SIZE != 0) {
        // adjust the size so it is a multiple of 16.
        size = (size / HEADER_SIZE + 1) * HEADER_SIZE;
    }
    
    if (size < MINIMUM_BLOCK_SIZE) {
        size = MINIMUM_BLOCK_SIZE;
    }
  
    Block* iter;         // iterator block
    Block* temp;         // splitted block
    Block* return_block; // block to be returned to user
    Block* prev;         // block previous to the returning block

    return_block = find_block(size);
    // if there is no free block of the requested size
    if (!return_block) {
      // if the requested size is bigger than the default value
      if (size > DEFAULT_BLOCK_SIZE + HEADER_SIZE) {
        return_block = malloc((size + HEADER_SIZE));
        if (return_block == NULL) {
            fprintf(stderr, "request_space: malloc failed\n");
            exit(1);
        }
        return_block->size = size;
	return_block->next = NULL;
        total_malloc += size + HEADER_SIZE;
	return (Block*)((uintptr_t)return_block + HEADER_SIZE);
      } else { // requested size is less than or equal to the default
        request_space(size);
	return_block = find_block(size);
      }
    }
    
    // iterate through the free list to find the block
    // directly previous to the returned block
    iter = free_list;
    if (return_block == free_list) {
        prev = free_list;
    } else {
      while (iter && iter->next) {
    	if (iter->next == return_block) {
    	  prev = iter;
	  break;
    	} else {
    	  iter = iter->next;
    	}
      }
    }

    if (return_block->size >= (size + HEADER_SIZE + MINIMUM_BLOCK_SIZE)) {
        // spilit the block
        temp = (Block*) ((uintptr_t)return_block + HEADER_SIZE + size);
        temp->size = return_block->size - HEADER_SIZE - size;
        temp->next = return_block->next;
        return_block->size = size;
        return_block->next = NULL;
    } else {
        // remove the block from freelist 
        temp = return_block->next;
    }
    // remove from the free list
    // front case
    if (prev == return_block) {
        free_list = temp;
    } else {
        prev->next = temp;
    }
    check_heap();
    return (Block*)((uintptr_t)return_block + HEADER_SIZE);

}
/* takes in "size" and finds the block on the free_list 
 * that is big enough to allocate the given size
 */
Block* find_block(uintptr_t size) {
    Block* free_block;
    free_block = free_list;
    while (free_block) {
        if (free_block->size >= size) {
	    return free_block;
	} else {
	    free_block = free_block->next;
	}
    }
    return NULL;
}

/* if there is no free block big enough and 
 * the requested size is less than or equal to the default,
 * asks the system for an appropriate amount of memory
 */
void request_space() {
    Block* space;
    space = malloc(DEFAULT_BLOCK_SIZE + HEADER_SIZE);
    if (space == NULL) {
      fprintf(stderr, "request_space: malloc failed\n");
        exit(1);
    }
    space->size = DEFAULT_BLOCK_SIZE;
    total_malloc += DEFAULT_BLOCK_SIZE + HEADER_SIZE;
   
    insert_block(space);
}



