#include <stdio.h>
#include <string.h>

#define MAX 20

// Structure to represent a memory block
typedef struct {
    int id;
    int size;
    int process_id; // -1 if free
} Block;

// Structure to represent a process
typedef struct {
    int id;
    int size;
} Process;

// Helper to reset blocks before running a new algorithm
void resetBlocks(Block blocks[], int n, const int initial_sizes[]) {
    for (int i = 0; i < n; i++) {
        blocks[i].id = i + 1;
        blocks[i].size = initial_sizes[i];
        blocks[i].process_id = -1; // -1 indicates the block is free
    }
}

// Helper to print the allocation table
void printAllocation(Block blocks[], int n_blocks, Process processes[], int n_processes) {
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\tFragment\n");
    for (int i = 0; i < n_processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i].size);
        
        int allocated = 0;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].process_id == i + 1) {
                printf("%d\t\t%d\t\t%d\n", blocks[j].id, blocks[j].size, blocks[j].size - processes[i].size);
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("Not Allocated\t-\t\t-\n");
        }
    }
    printf("\n");
}

// 1. First Fit Algorithm
void firstFit(Block blocks[], int n_blocks, Process processes[], int n_processes) {
    printf("--- First Fit Allocation ---\n");
    
    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_blocks; j++) {
            // Find the first block that is free and fits the process
            if (blocks[j].process_id == -1 && blocks[j].size >= processes[i].size) {
                blocks[j].process_id = i + 1; // Allocate block j to process i
                break; // Move to next process
            }
        }
    }
    printAllocation(blocks, n_blocks, processes, n_processes);
}

// 2. Best Fit Algorithm
void bestFit(Block blocks[], int n_blocks, Process processes[], int n_processes) {
    printf("--- Best Fit Allocation ---\n");

    for (int i = 0; i < n_processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].process_id == -1 && blocks[j].size >= processes[i].size) {
                // If no block selected yet, or this block is tighter (smaller) than the current best
                if (bestIdx == -1 || blocks[j].size < blocks[bestIdx].size) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block was found
        if (bestIdx != -1) {
            blocks[bestIdx].process_id = i + 1;
        }
    }
    printAllocation(blocks, n_blocks, processes, n_processes);
}

// 3. Worst Fit Algorithm
void worstFit(Block blocks[], int n_blocks, Process processes[], int n_processes) {
    printf("--- Worst Fit Allocation ---\n");

    for (int i = 0; i < n_processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j].process_id == -1 && blocks[j].size >= processes[i].size) {
                // If no block selected yet, or this block is larger than the current worst
                if (worstIdx == -1 || blocks[j].size > blocks[worstIdx].size) {
                    worstIdx = j;
                }
            }
        }

        // If a suitable block was found
        if (worstIdx != -1) {
            blocks[worstIdx].process_id = i + 1;
        }
    }
    printAllocation(blocks, n_blocks, processes, n_processes);
}

int main() {
    Block blocks[MAX];
    int block_sizes_backup[MAX]; // To reset sizes between runs
    Process processes[MAX];
    int n_blocks, n_processes;

    // Input Memory Blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &n_blocks);
    printf("Enter size of each block:\n");
    for (int i = 0; i < n_blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block_sizes_backup[i]);
    }

    // Input Processes
    printf("\nEnter number of processes: ");
    scanf("%d", &n_processes);
    printf("Enter size of each process:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].id = i + 1;
    }
    

    // Run First Fit
    resetBlocks(blocks, n_blocks, block_sizes_backup);
    firstFit(blocks, n_blocks, processes, n_processes);

    // Run Best Fit
    resetBlocks(blocks, n_blocks, block_sizes_backup);
    bestFit(blocks, n_blocks, processes, n_processes);

    // Run Worst Fit
    resetBlocks(blocks, n_blocks, block_sizes_backup);
    worstFit(blocks, n_blocks, processes, n_processes);

    return 0;
}