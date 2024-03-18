#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1024


typedef struct Block {
    int size;
    int free;
    struct Block *prev;
    struct Block *next;
} Block;

char heap[HEAP_SIZE];


Block *head = (void*)heap;


void initHeap() {
    head->size = HEAP_SIZE - sizeof(Block);
    head->free = 1;
    head->prev = NULL;
    head->next = NULL;
}

void* allocate(int size) {
    Block *current = head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size + sizeof(Block)) {
                Block *newBlock = (void*)((void*)current + sizeof(Block) + size);
                newBlock->size = current->size - sizeof(Block) - size;
                newBlock->free = 1;
                newBlock->next = current->next;
                newBlock->prev = current;
                
                if (current->next != NULL) {
                    current->next->prev = newBlock;
                }
                current->next = newBlock;
                current->size = size;
            }
            current->free = 0;
            return (void*)current + sizeof(Block);
        }
        current = current->next;
    }
    return NULL; 
}

void freeMemory(void *ptr) {
    Block *block = (void*)((void*)ptr - sizeof(Block));
    block->free = 1;

 
    if ((block->next != NULL) && block->next->free) {
        block->size += sizeof(Block) + block->next->size;
        block->next = block->next->next;
        if (block->next != NULL) {
            block->next->prev = block;
        }
    }


    if ((block->prev != NULL) && block->prev->free) {
        block->prev->size += sizeof(Block) + block->size;
        block->prev->next = block->next;
        if (block->next != NULL) {
            block->next->prev = block->prev;
        }
    }
}

int main() {
    initHeap(); 

    void *ptr1 = allocate(10); 
    void *ptr2 = allocate(200); 
    void *ptr3 = allocate(100);
    void *ptr4 = allocate(30);
    
    freeMemory(ptr2); 
    freeMemory(ptr3);
    void *ptr5 = allocate(30);
    void *ptr6 = allocate(250);
    printf("Allocated at %p and %p and %p AND %p and %p and %p\n", ptr1, ptr2, ptr3,ptr4,ptr5,ptr6);

    return 0;
}
