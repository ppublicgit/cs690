README for MYMALLOC library
Paul Abers
Created for CS 690

To build the system, simply call make and one of the options
    -- to build just the library: make lib
    -- to build just main: make main
    -- to build with debug: make debug
    -- to build all clean: make clean

To run simply call main
    -- ./main

The test main driver allocates 4 pointers and then subsequently frees them.
Each call is followed by a call to printFreeList() to show how the free list
changing with each call.
