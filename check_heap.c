/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015
 * check_heap checks for possible problems with the free list.
 */ 

#include "mem.h"
#include "mem_impl.h"
#include <assert.h>

void check_heap() {
    Block* current = free_list;
    Block* next;

    while (current) {
        // checks if the block size is positive and not smaller 
        // than the minimum block size
        assert((intptr_t) current->size > 0 && current->size >= MINIMUM_BLOCK_SIZE);
        if (current->next) {
            next = current->next;
            // checks if the blocks are ordered with strictly increasing
            // memory addresses and also checks if they overlap or touch
	    assert((uintptr_t)current < (uintptr_t)next);
	    /* assert((uintptr_t)current + current->size + HEADER_SIZE  */
	    /* 	   != (uintptr_t)next); */
            /* assert((uintptr_t)current + current->size + HEADER_SIZE */
            /*        < (uintptr_t)next); */
        }
	current = current->next;
    }
}
