#include <stdio.h>
#define P 4 // number of processes
#define R 3 // number of resource types

int max[P][R] = {
    {6,4,7},
    {5,3,5},
    {7,5,6},
    {4,4,3}
};

int alloc[P][R] = {
    {2,1,3},
    {1,2,1},
    {3,3,2},
    {1,0,1}
};

int avail[R] = {2,2,2};
int need[P][R];

// --------------------------------------------------
// Calculate Need = Max - Allocation
// --------------------------------------------------
void calculateNeed() {
    printf("\nNeed Matrix:\n");
    for(int i=0; i<P; i++) {
        for(int j=0; j<R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

// --------------------------------------------------
// Safety Algorithm (prints safe sequence)
// --------------------------------------------------
int isSafe() {
    int work[R];
    int finish[P] = {0};
    int safeSeq[P];
    int count = 0;
    
    for(int i=0; i<R; i++)
        work[i] = avail[i];
        
    while(count < P) {
        int found = 0;
        for(int i=0; i<P; i++) {
            if(finish[i] == 0) {
                int canRun = 1;
                for(int j=0; j<R; j++) {
                    if(need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if(canRun) {
                    for(int j=0; j<R; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0) {
            return 0; // unsafe
        }
    }
    // Print safe sequence
    printf("\nSafe Sequence: ");
    for(int i=0; i<P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 1; // safe
}

// --------------------------------------------------
// MAIN PROGRAM
// --------------------------------------------------
int main() {
    int choice;
    printf("BANKER'S ALGORITHM - DYNAMIC VERSION\n");
    while(1) {
        printf("\n-------------------------");
        printf("\n1. Show Need Matrix");
        printf("\n2. Check Safety");
        printf("\n3. Update Available Resources");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            calculateNeed();
        }
        else if(choice == 2) {
            calculateNeed();
            if(isSafe())
                printf("\nSystem is SAFE.\n");
            else
                printf("\nSystem is UNSAFE.\n");
        }
        else if(choice == 3) {
            printf("\nEnter new available resources (A B C): ");
            scanf("%d %d %d", &avail[0], &avail[1], &avail[2]);
            printf("Updated Available = (%d, %d, %d)\n", avail[0], avail[1], avail[2]);
            calculateNeed();
            if(isSafe())
                printf("\nSystem remains SAFE after update.\n");
            else
                printf("\nSystem becomes UNSAFE after update!\n");
        }
        else if(choice == 4) {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}