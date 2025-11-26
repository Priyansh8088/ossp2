/**
 * C Program to simulate SCAN (Elevator) Disk Scheduling Algorithm.
 * * Logic:
 * 1. Sort the request array.
 * 2. Split requests into two groups: those less than the head (left) and 
 * those greater than the head (right).
 * 3. Depending on the chosen direction (1 for High/Right, 0 for Low/Left):
 * - If High: Service right requests -> Go to disk size limit -> Service left requests (in reverse).
 * - If Low: Service left requests (in reverse) -> Go to 0 -> Service right requests.
 */

#include <stdio.h>
#include <stdlib.h>

// Comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int i, n, head, disk_size, direction;
    int total_seek_time = 0;
    int *requests;
    int left[100], right[100];
    int left_count = 0, right_count = 0;

    printf("--- SCAN Disk Scheduling Algorithm ---\n");

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

    printf("Enter direction (1 for High/Right, 0 for Low/Left): ");
    scanf("%d", &direction);

    // Split requests into left and right of head
    for(i = 0; i < n; i++) {
        if(requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }

    // Sort both arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    printf("\nSeek Sequence is:\n");
    printf("%d", head);

    int current_head = head;

    // Logic for SCAN
    if(direction == 1) { 
        // Move Right
        for(i = 0; i < right_count; i++) {
            printf(" -> %d", right[i]);
            total_seek_time += abs(right[i] - current_head);
            current_head = right[i];
        }
        // Go to end of disk
        printf(" -> %d", disk_size - 1);
        total_seek_time += abs((disk_size - 1) - current_head);
        current_head = disk_size - 1;

        // Reverse and go Left
        for(i = left_count - 1; i >= 0; i--) {
            printf(" -> %d", left[i]);
            total_seek_time += abs(left[i] - current_head);
            current_head = left[i];
        }
    } else { 
        // Move Left
        for(i = left_count - 1; i >= 0; i--) {
            printf(" -> %d", left[i]);
            total_seek_time += abs(left[i] - current_head);
            current_head = left[i];
        }
        // Go to beginning of disk
        printf(" -> 0");
        total_seek_time += abs(0 - current_head);
        current_head = 0;

        // Reverse and go Right
        for(i = 0; i < right_count; i++) {
            printf(" -> %d", right[i]);
            total_seek_time += abs(right[i] - current_head);
            current_head = right[i];
        }
    }

    printf("\n\nTotal Seek Time: %d\n", total_seek_time);
    free(requests);
    return 0;
}