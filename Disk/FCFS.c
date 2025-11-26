/**
 * C Program to simulate First-Come, First-Served (FCFS) Disk Scheduling Algorithm.
 * * Logic:
 * 1. Accept the number of requests and the request queue.
 * 2. Accept the initial position of the disk head.
 * 3. Process requests in the order they appear in the queue.
 * 4. Calculate the absolute distance (seek time) between the current head position 
 * and the next request.
 * 5. Add this distance to the total seek time.
 * 6. Move the head to the new request position.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int i, n, head, total_seek_time = 0;
    int *requests;

    printf("--- FCFS Disk Scheduling Algorithm ---\n");

    // Input number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    // Allocate memory for requests
    requests = (int *)malloc(n * sizeof(int));

    // Input the request queue
    printf("Enter the request sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence is:\n");
    printf("%d", head); // Start point

    // Calculate total seek time
    for(i = 0; i < n; i++) {
        // Calculate absolute difference
        total_seek_time += abs(requests[i] - head);
        
        // Move head to the current request
        head = requests[i];
        
        printf(" -> %d", head);
    }

    printf("\n\nTotal Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);

    free(requests);
    return 0;
}