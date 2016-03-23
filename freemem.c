/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015
 * freemem.c is a source file that frees the block of memery and
 * returns it to the free list
 */

#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

void insert_block(Block* free_block);
void combine_blocks(Block* first, Block* second);

/* takes in a pointer to a block of memory and 
 * returns the block pointed by to the free list.
 * if the block is located adjacent to other free blocks,
 * combine the blocks into one single block
 */ 
void freemem(void* p) {
  check_heap();
  Block* current = free_list;
  Block* free_block = (Block*) ((uintptr_t) p - HEADER_SIZE);
  
  // does nothing if point p is NULL
  if (!p) {
    return;
  }
  
  insert_block(free_block);
  // checks through the free list
  while (current && current->next) {
    // if two free blocks are adjacent to each other, combine the two
    if ((uintptr_t)current + current->size + HEADER_SIZE
	== (uintptr_t)current->next) {
      combine_blocks(current, current->next);
    } else {
      current = current->next;
    }
  }
  check_heap();
}

/* takes in a block pointer to a block of memory
 * allocated by getmem and inserts the block
 * into the free list of memory
 */
void insert_block(Block* free_block) {
  Block* current = free_list;
 
  // when the entire list is empty
  if (!current) {
    free_list = free_block; // given block is the front of the free list
    return;
  } else {
     // front case
    if ((uintptr_t)free_block < (uintptr_t)current) {
       free_block->next = current; // links free list to end of given block
       free_list = free_block; // given block is the front of the free list
       return;
     } else {
      while (current->next && 
	     (uintptr_t)free_block > (uintptr_t)current->next) {
	 current = current->next; // find the position of the block on the list
       }
       // end case
       if (!current->next) {
	 current->next = free_block; // given block is the end of the list
	 return;
       } else { // add the block to the correct position on the list
	 free_block->next = current->next;
	 current->next = free_block;
       }
     }
  }
}

/* takes in two block pointers and combines the 
 * two blocks of memory pointed by into one single block
 */
void combine_blocks(Block* first, Block* second) {
  first->size += second->size + HEADER_SIZE;
  first->next = second->next;
}

