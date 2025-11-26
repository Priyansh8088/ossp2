/**
 * C Program to simulate C-SCAN (Circular SCAN) Disk Scheduling Algorithm.
 * * Logic:
 * 1. Sort the requests.
 * 2. Split into left and right arrays based on initial head position.
 * 3. If direction is High (Right):
 * - Service requests to the right.
 * - Move to end of disk (disk_size - 1).
 * - Jump to beginning of disk (0). NOTE: This jump is counted in seek time, 
 * but no requests are serviced during the jump.
 * - Service remaining requests on the left side (starting from 0 upwards).
 */

#include <stdio.h>
#include <stdlib.h>

// Comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int i, n, head, disk_size;
    int total_seek_time = 0;
    int *requests;
    int left[100], right[100];
    int left_count = 0, right_count = 0;

    printf("--- C-SCAN Disk Scheduling Algorithm ---\n");

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk size (max cylinder value): ");
    scanf("%d", &disk_size);

    requests = (int *)malloc(n * sizeof(int));

    printf("Enter the request sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Note: C-SCAN usually assumes a fixed direction (e.g., Right/High)
    // We will assume movement towards higher values.

    for(i = 0; i < n; i++) {
        if(requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }

    // Sort arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    printf("\nSeek Sequence is:\n");
    printf("%d", head);

    int current_head = head;

    // 1. Service requests on the right
    for(i = 0; i < right_count; i++) {
        printf(" -> %d", right[i]);
        total_seek_time += abs(right[i] - current_head);
        current_head = right[i];
    }

    // 2. Move to the end of the disk
    printf(" -> %d", disk_size - 1);
    total_seek_time += abs((disk_size - 1) - current_head);
    current_head = disk_size - 1;

    // 3. Jump to the beginning of the disk (0)
    printf(" -> 0");
    total_seek_time += abs(0 - current_head);
    current_head = 0;

    // 4. Service the remaining requests (left part, moving upwards)
    for(i = 0; i < left_count; i++) {
        printf(" -> %d", left[i]);
        total_seek_time += abs(left[i] - current_head);
        current_head = left[i];
    }

    printf("\n\nTotal Seek Time: %d\n", total_seek_time);
    
    free(requests);
    return 0;
}