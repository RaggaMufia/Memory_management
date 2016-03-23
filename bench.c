/* Daehyun Kim & Peter Won
 * CSE374 Hw 5
 * Feb 17 2015
 * bench.c is a source file that tests getmem and freemem.
 * It randomly calls getmem and freemem for testing.
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run_bench(int prm[]);
void print_stats(clock_t start_t);

int main(int argc, char** argv) {
  // default parameter values
  int prm[6] = {10000, 50, 10, 200, 20000, time(NULL)};
  FILE *f = fopen("free_list.txt", "w");
  // update the parameter values if the user gives the inputs
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      // convert to binary integers
      prm[i-1] = atoi(argv[i]);
    }
  }
  run_bench(prm);
  print_heap(f);
  return 0;
}

/* takes in an array of command-line parameters and 
 * runs the experiment, printing statistics at every 10% of the 
 * progress.
 */
void run_bench(int prm[]) {
  // 6 parameters
  int ntrials = prm[0];
  int pctget = prm[1];
  int pctlarge = prm[2];
  int small_limit = prm[3];
  int large_limit = prm[4];
  int random_seed = prm[5];

  // random number generator
  srand(random_seed);
  int mem_choice; // getmem or freemem
  int size_choice; // small or large
  int num_mem = 0; // number of block pointers
  int block_size; // requested block size
  // array to keep track of the allocated blocks
  uintptr_t* mem = (uintptr_t*)malloc(ntrials * sizeof(*mem));
  clock_t start_t = clock(); // initial clock

  for (int i = 1; i <= ntrials; i++) {
    mem_choice = rand() % 100;
    if (mem_choice < pctget) { // pctget % of choosing getmem
      size_choice = rand() % 100;
      if (size_choice < pctlarge) { // pctlarge % of choosing large
	// request a large block whose size is a random number
	// between small_limit and large_limit 
	block_size = rand() % (large_limit-small_limit) + small_limit;
      } else { // choose small
	// request a small block whose size is a random number
	// between 1 and small_limit
	block_size = rand() % small_limit + 1;
      }
      mem[num_mem] = (uintptr_t)getmem(block_size);
      num_mem++;
    } else { // choose freemem
      if (num_mem > 0) {
	// pick a random previously allocated block to free
	int random = rand() % num_mem;
	freemem((uintptr_t*) mem[random]);
	mem[random] = mem[num_mem-1]; // replace the pointed block 
	num_mem--; // decrement the number of pointers
      }
    }
    // at every 10% of calls, print statistics
    if (i % (ntrials/10) == 0) {
      print_stats(start_t);
    }
  }
  
}

/* prints statistics regarding the current status of the memory 
 * management including the total CPU time taken by the bench so far,
 * the total amount of storage acquired, the total number of free blocks,
 * and the average size of free blocks in bytes. This function takes in
 * the initial time in clock when the implementation started.
 */
void print_stats(clock_t start_t) {
  clock_t current_t = clock();
  uintptr_t total_size = 0;
  uintptr_t total_free = 0;
  uintptr_t n_free_blocks = 0;
  get_mem_stats(&total_size, &total_free, &n_free_blocks);
  // print the CPU time in seconds as a float value
  // with 2 digits after the decimal point
  printf("Total CPU time so far: %.10f\n",
	 ((float)current_t-start_t)/CLOCKS_PER_SEC);
  printf("Total amount of storage acquired: %lu bytes\n", total_size);
  printf("Total number of free blocks: %lu\n", n_free_blocks);
  if (n_free_blocks == 0) {
    printf("Average size of free blocks: 0 bytes\n");
  } else {
    printf("Average size of free blocks: %lu bytes\n",
	   total_free/n_free_blocks);
  }
}
