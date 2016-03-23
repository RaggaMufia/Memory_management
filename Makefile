
bench: bench.o getmem.o freemem.o get_mem_stats.o print_heap.o check_heap.o
	gcc -Wall -std=c11 -g -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o check_heap.o
bench.o: bench.c mem.h 
	gcc -Wall -std=c11 -g -c bench.c
#test: test.o getmem.o freemem.o get_mem_stats.o print_heap.o check_heap.o
#	gcc -Wall -std=c11 -g -o test test.o getmem.o freemem.o get_mem_stats.o print_heap.o check_heap.o
#test.o: test.c mem.h
#	gcc -Wall -std=c11 -g -c test.c
getmem.o: getmem.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c getmem.c
freemem.o: freemem.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c freemem.c
get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c get_mem_stats.c
print_heap.o: print_heap.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c print_heap.c
check_heap.o: check_heap.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c check_heap.c
test: bench
	./bench
dist: bench
	git log > git.log
	tar -cvf hw5.tar *.c *.h git.log README.md Makefile	
clean: 
	rm -f *.o *~ bench test git.log hw5.tar
