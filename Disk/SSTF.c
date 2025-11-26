/**
 * C Program to simulate Shortest Seek Time First (SSTF) Disk Scheduling Algorithm.
 * * Logic:
 * 1. Maintain an array of requests and a 'visited' array to track serviced requests.
 * 2. From the current head position, find the unvisited request with the minimum 
 * seek distance (absolute difference).
 * 3. Service that request, add the distance to total seek time, and mark it as visited.
 * 4. Repeat until all requests are serviced.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int main() {
    int n, head, i, count = 0;
    int total_seek_time = 0;
    int *requests, *visited;

    printf("--- SSTF Disk Scheduling Algorithm ---\n");

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    requests = (int *)malloc(n * sizeof(int));
    visited = (int *)calloc(n, sizeof(int)); // Initialize visited array to 0

    printf("Enter the request sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence is:\n");
    printf("%d", head);

    // Loop until all requests are serviced
    while(count < n) {
        int min_dist = INT_MAX;
        int index = -1;

        // Find the nearest unvisited request
        for(i = 0; i < n; i++) {
            if(!visited[i]) {
                int dist = abs(requests[i] - head);
                if(dist < min_dist) {
                    min_dist = dist;
                    index = i;
                }
            }
        }

        if(index != -1) {
            // Service the request
            visited[index] = 1;
            total_seek_time += min_dist;
            head = requests[index];
            printf(" -> %d", head);
            count++;
        }
    }

    printf("\n\nTotal Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);

    free(requests);
    free(visited);
    return 0;
}