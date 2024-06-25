# Simple Memory Allocator

## Overview
This project is a simple memory allocator implemented in C. It provides basic memory allocation and deallocation functionality similar to `malloc` and `free` in standard libraries. The allocator manages a fixed-size heap and uses a linked list of memory blocks to keep track of allocated and free memory.

## Features
1. **Initialize Heap**: Set up the initial heap space.
2. **Allocate Memory**: Allocate a block of memory from the heap.
3. **Free Memory**: Deallocate a previously allocated block of memory and merge adjacent free blocks.
