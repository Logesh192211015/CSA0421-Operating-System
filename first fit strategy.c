#include <stdio.h>

#define MAX_BLOCKS 100

typedef struct {
    int start_address;
    int end_address;
    int size;
    int is_allocated;
} MemoryBlock;

void initializeMemoryBlocks(MemoryBlock blocks[], int num_blocks) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        blocks[i].start_address = -1;
        blocks[i].end_address = -1;
        blocks[i].size = 0;
        blocks[i].is_allocated = 0;
    }
}

int allocateMemory(MemoryBlock blocks[], int num_blocks, int process_size) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        if (blocks[i].is_allocated == 0 && blocks[i].size >= process_size) {
            blocks[i].is_allocated = 1;
            return blocks[i].start_address;
        }
    }
    return -1;
}

int main() {
    MemoryBlock blocks[MAX_BLOCKS];
    int num_blocks, process_size, i, start_address;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &num_blocks);

    printf("Enter the details of memory blocks:\n");
    for (i = 0; i < num_blocks; i++) {
        printf("Block %d start address: ", i + 1);
        scanf("%d", &blocks[i].start_address);
        printf("Block %d end address: ", i + 1);
        scanf("%d", &blocks[i].end_address);
        blocks[i].size = blocks[i].end_address - blocks[i].start_address + 1;
        blocks[i].is_allocated = 0;
    }

    printf("Enter the size of the process: ");
    scanf("%d", &process_size);

    start_address = allocateMemory(blocks, num_blocks, process_size);

    if (start_address != -1) {
        printf("Memory allocated successfully at address %d\n", start_address);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}
