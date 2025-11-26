#include <stdio.h>
#include <stdbool.h>

// Define constants for the number of clients (processes) and resources
#define N 5 // Number of clients
#define M 3 // Number of resources

// Global variables for the system state
int available[M] = {10, 5, 7}; // Initial Available resources
int max[N][M] = { // Maximum demand of each client
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[N][M] = { // Initial allocated resources
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[N][M]; // Calculated Need matrix

// Function Prototypes
void calculateNeedMatrix();
void printMatrix(int matrix[N][M]);
bool isSafe();
bool processRequest(int client_id, int request[M]);

// --- Main Program ---
int main() {
    printf("--- Banker's Algorithm Simulation ---\n\n");

    // a & b. Calculate and Print Need Matrix
    calculateNeedMatrix();
    printf("b. Need Matrix Calculated and Printed:\n");
    printMatrix(need);

    // c. Check initial system state
    printf("\n--- Initial Safety Check ---\n");
    if (isSafe()) {
        printf("c. The system is initially in a **SAFE STATE**.\n");
    } else {
        printf("c. The system is initially in an **UNSAFE STATE**.\n");
    }

    // d. Process a resource request example
    printf("\n--- Processing a Client Request (Example: Client 1 requests {1, 0, 2}) ---\n");
    int request1[M] = {1, 0, 2}; // Request from Client 1 (index 0)
    processRequest(0, request1);

    printf("\n--- Processing another Client Request (Example: Client 3 requests {3, 3, 0}) ---\n");
    int request2[M] = {3, 3, 0}; // Request from Client 3 (index 2)
    processRequest(2, request2);

    return 0;
}

void calculateNeedMatrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// a & b. Print Need matrix function
void printMatrix(int matrix[N][M]) {
    printf("Client | Resource 1 | Resource 2 | Resource 3\n");
    printf("-------|------------|------------|------------\n");
    for (int i = 0; i < N; i++) {
        printf("  P%d   |    %2d      |    %2d      |    %2d\n", i, matrix[i][0], matrix[i][1], matrix[i][2]);
    }
}

// c. Check if the system is in a safe state function
bool isSafe() {
    int work[M]; // Work vector, initialized to Available
    for (int j = 0; j < M; j++) {
        work[j] = available[j];
    }

    bool finish[N] = {false}; // Finish vector, initialized to false
    int safeSequence[N];
    int count = 0;

    printf("Available: (%d, %d, %d)\n", work[0], work[1], work[2]);
    printf("Safety Algorithm Steps:\n");

    while (count < N) {
        bool found = false;
        for (int i = 0; i < N; i++) {
            // Check if client P[i] is NOT finished AND Need[i] <= Work
            if (finish[i] == false) {
                int j;
                for (j = 0; j < M; j++) {
                    if (need[i][j] > work[j]) {
                        break; // Need > Work for resource j
                    }
                }

                // If inner loop completed, it means Need <= Work for all resources
                if (j == M) {
                    // P[i] can be finished.
                    printf("  -> Client P%d can finish. Releasing resources: (%d, %d, %d)\n",
                           i, allocation[i][0], allocation[i][1], allocation[i][2]);

                    // Work = Work + Allocation[i]
                    for (int k = 0; k < M; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;

                    printf("     New Work (Available): (%d, %d, %d)\n", work[0], work[1], work[2]);
                }
            }
        }

        // If no client was found that could finish, and not all clients are finished, it's unsafe.
        if (found == false && count < N) {
            printf("  -> Deadlock detected: No client can finish with current resources.\n");
            return false;
        }

        // If found is false but count == N, the loop would exit and return true
    }

    // If all clients finished successfully
    printf("\n  Safe Sequence Found: <");
    for (int i = 0; i < N; i++) {
        printf("P%d", safeSequence[i]);
        if (i < N - 1) printf(", ");
    }
    printf(">\n");

    return true;
}

// d. Function to process resource request by a client
bool processRequest(int client_id, int request[M]) {
    // 1. Check if the Request is valid (Request <= Need)
    for (int j = 0; j < M; j++) {
        if (request[j] > need[client_id][j]) {
            printf("Request for P%d denied: Request is greater than its remaining need.\n", client_id);
            return false;
        }
    }

    // 2. Check if the Request can be fulfilled (Request <= Available)
    for (int j = 0; j < M; j++) {
        if (request[j] > available[j]) {
            printf("Request for P%d temporarily denied: Bank does not have enough resources available.\n", client_id);
            return false;
        }
    }

    // 3. Temporarily allocate the resources (Hypothetical State)
    printf("Pre-allocating resources for P%d...\n", client_id);
    for (int j = 0; j < M; j++) {
        available[j] -= request[j];
        allocation[client_id][j] += request[j];
        need[client_id][j] -= request[j];
    }

    // 4. Check if the hypothetical state is safe
    if (isSafe()) {
        printf("\n**Request GRANTED** for P%d. System remains in a **SAFE STATE**.\n", client_id);
        return true; // Request granted
    } else {
        // 5. If unsafe, undo the temporary allocation (Restore original state)
        printf("\nRequest for P%d denied: Granting the request leads to an **UNSAFE STATE**. State restored.\n", client_id);
        for (int j = 0; j < M; j++) {
            available[j] += request[j];
            allocation[client_id][j] -= request[j];
            need[client_id][j] += request[j];
        }
        return false; // Request denied
    }
}