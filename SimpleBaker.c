#include <stdio.h>
#define P 5 // number of clients
#define R 3 // number of resource types

int allocation[P][R] = {
    {0,1,0},
    {2,0,0},
    {3,0,2},
    {2,1,1},
    {0,0,2}
};

int maximum[P][R] = {
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}
};

int available[R] = {10,5,7};
int need[P][R]; 


void calculateNeed() {
    for(int i=0; i<P; i++) {
        for(int j=0; j<R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    // Print Need Matrix
    printf("\nNeed Matrix:\n");
    for(int i=0; i<P; i++) {
        for(int j=0; j<R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}


int isSafe() {
    int finish[P] = {0};
    int work[R];
    // Initialize work = available
    for(int i=0; i<R; i++) {
        work[i] = available[i];
    }
    int count = 0;
    while(count < P) {
        int found = 0;
        for(int i=0; i<P; i++) {
            if(finish[i] == 0) {
                int j, canRun = 1;
                for(j=0; j<R; j++) {
                    if(need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if(canRun) {
                    for(j=0; j<R; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if(found == 0) {
            return 0; // not safe
        }
    }
    return 1; // safe
}


void requestResources(int p, int request[]) {

    for(int j=0; j<R; j++) {
        if(request[j] > need[p][j]) {
            printf("Error: Request exceeds Need.\n");
            return;
        }
    }
  
    for(int j=0; j<R; j++) {
        if(request[j] > available[j]) {
            printf("Resources not available. Must wait.\n");
            return;
        }
    }
   
    for(int j=0; j<R; j++) {
        available[j] -= request[j];
        allocation[p][j] += request[j];
        need[p][j] -= request[j];
    }
    
    if(isSafe()) {
        printf("Request granted (system remains safe).\n");
    } else {
        printf("Request would make system unsafe. Request denied.\n");
        for(int j=0; j<R; j++) {
            available[j] += request[j];
            allocation[p][j] -= request[j];
            need[p][j] += request[j];
        }
    }
}

int main() {

    calculateNeed();
    if(isSafe())
        printf("\nSystem is in SAFE state.\n");
    else
        printf("\nSystem is in UNSAFE state.\n");
    
    int req[R] = {1,0,2}; 
    printf("\nProcessing Request for P1: (1,0,2)\n");
    requestResources(1, req);
    
    return 0;
}