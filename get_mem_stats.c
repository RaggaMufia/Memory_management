/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015
 * get_mem_stats.c is a source file that sets and updates the values 
 * in the passed pointers based on the current status of the memory heap. 
 */

#include "mem.h"
#include "mem_impl.h"

/* updates statistics given the three pointers.
 * The three given pointers point to:
 * total_size: total size in bytes allocated for the memory heap
 * total_free: total size in bytes in the free list including headers/links
 * n_free_blocks: number of free blocks in the free list 
 */
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
		   uintptr_t* n_free_blocks) {
  *total_size = total_malloc;
  *total_free = 0;
  *n_free_blocks = 0;
  Block* current = free_list;
  // checks through the free list to update total_free and n_free_blocks
  while (current) {
    *total_free += current->size + HEADER_SIZE;
    (*n_free_blocks)++;
    current = current->next;
  } 
}
