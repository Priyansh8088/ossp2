#include <stdio.h>
#include <stdbool.h>

// Number of Processes and Resources
#define P 5
#define R 3

// Function to calculate the Need Matrix
void calculateNeed(int need[P][R], int max[P][R], int alloc[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool checkSafeState(int processes[], int avail[], int max[][R], int alloc[][R], int need[][R]) {
    int work[R];
    bool finish[P];
    int safeSeq[P];
    int count = 0;

    // Initialize Work as a copy of Available
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    // Initialize Finish array to false (0)
    for (int i = 0; i < P; i++)
        finish[i] = false;

    // Loop until all processes are finished or no safe sequence is found
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j])
                        break;
                }

                // If Need <= Work
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[p][k];
                    
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (found == false) {
            printf("System is NOT in a safe state.\n");
            return false;
        }
    }

    // If we reach here, the system is safe
    printf("\nSystem is in a SAFE state.\nSafe Sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d", safeSeq[i]);
        if (i != P - 1) printf(" -> ");
    }
    printf("\n");
    return true;
}

// Function to handle resource requests
void requestResources(int processes[], int avail[], int max[][R], int alloc[][R], int need[][R]) {
    int pid;
    int request[R];

    printf("\nEnter Process ID (0-4) making the request: ");
    scanf("%d", &pid);

    if (pid < 0 || pid >= P) {
        printf("Invalid Process ID.\n");
        return;
    }

    printf("Enter requested resources for P%d (A B C): ", pid);
    for (int i = 0; i < R; i++) {
        scanf("%d", &request[i]);
    }

    // Check 1: Request <= Need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[pid][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }

    // Check 2: Request <= Available
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i]) {
            printf("Process P%d must wait. Resources are not available.\n", pid);
            return;
        }
    }

    // Tentatively allocate resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        alloc[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    // Check if the new state is safe
    if (checkSafeState(processes, avail, max, alloc, need)) {
        printf("Request Granted.\n");
    } else {
        printf("Request Denied. It leads to an unsafe state.\n");
        // Rollback
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            alloc[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
    }
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    // Data from the image
    int alloc[P][R] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    int max[P][R] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    int avail[R] = {3, 3, 2}; // Available Resources A, B, C

    int need[P][R];
    calculateNeed(need, max, alloc);

    printf("--- Initial System State ---\n");
    
    // Initial Safety Check
    checkSafeState(processes, avail, max, alloc, need);

    // Loop for User Requests
    char choice;
    do {
        printf("\nDo you want to request resources? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            requestResources(processes, avail, max, alloc, need);
        }
    } while (choice == 'y' || choice == 'Y');

    return 0;
}