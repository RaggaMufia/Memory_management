/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015 
 * print_heap.c is a source file that prints the information 
 * about each block on the free list. The information should include
 * hexadecimal numbers indicating the address and length of each block
 */

#include "mem.h"
#include "mem_impl.h"
#include <inttypes.h>
#include <stdio.h>

/* prints information about each block of memory in the free list
 * to the given file "f" 
 */
void print_heap(FILE * f) {
  Block* current = free_list;

  if (!current) {
    fprintf(f, "The free list is empty.\n");
  }
  while (current) {
    fprintf(f, "address: %p, ", current);
    fprintf(f, "size: %" PRIxPTR "\n", current->size);
    current = current->next;
  }
  fclose(f);
}
