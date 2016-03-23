/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015
 * mem.impl.h is a header file that includes the functions that are 
 * internally implemented.
 */

#ifndef MEM_IMPL_H
#define MEM_IMPL_H
#define MINIMUM_BLOCK_SIZE 32       // minumum block size
#define DEFAULT_BLOCK_SIZE 4096     // default block size
#define HEADER_SIZE sizeof(Block) // size of the header
#include <inttypes.h>

// blocks of free memory, arranged in a list
typedef struct block {
  uintptr_t size; // size in bytes of the block
  struct block* next; // pointer to the next block in the list
} Block;

// points to the front of the list of free blocks
Block* free_list; 
// total malloc size
uintptr_t total_malloc;

void insert_block(Block* free_block);

#endif
