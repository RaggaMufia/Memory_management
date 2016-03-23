#include "mem.h"
#include "mem_impl.h"

/* test program
 */
int main(int argc, char** argv) {
  FILE *f = fopen("free_list.txt", "w");
  uintptr_t total_size;
  uintptr_t total_free;
  uintptr_t n_free_blocks;
  getmem(10000);
  void* test2 = getmem(1000);
  freemem(test2);
  getmem(2000);
  getmem(3000);
  //void* test3 = getmem(7000);
  //freemem(test3);
 // getmem(500);
  //freemem(test1);
 void* test4 = getmem(200000);
  freemem(test4);
 // getmem(10000);
  get_mem_stats(&total_size, &total_free, &n_free_blocks);
  printf("Total amount of storage acquired: %lu bytes\n", total_size);
  printf("Total number of free blocks: %lu\n", n_free_blocks);
  /* if (n_free_blocks == 0) { */
  /*   printf("Average size of free blocks: 0 bytes\n"); */
  /* } else { */
  /*   printf("Average size of free blocks: %lu bytes\n", */
  /* 	   total_free/n_free_blocks); */
  /* } */
  printf("Total free: %lu bytes\n", total_free);
  print_heap(f); 
  return 0;
}
