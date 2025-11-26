#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compare integers for sorting
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    // --- Input Data ---
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int start_head = 53;
    int n = sizeof(requests) / sizeof(requests[0]);
    
    // Arrays to hold split requests
    int left[n], right[n];
    int left_count = 0, right_count = 0;
    
    // Total seek time accumulator
    int total_seek_time = 0;
    int current_head = start_head;

    // 1. Sort the initial request array
    qsort(requests, n, sizeof(int), compare);

    // 2. Split requests into Left (smaller than head) and Right (larger than head)
    //    We assume the head is moving in the 'increasing' direction (Right) first.
    for (int i = 0; i < n; i++) {
        if (requests[i] >= start_head) {
            right[right_count++] = requests[i];
        } else {
            left[left_count++] = requests[i];
        }
    }

    printf("Sequence of Service:\n");
    printf("%d (Start)", start_head);

    // 3. Service the RIGHT side (moving outwards)
    for (int i = 0; i < right_count; i++) {
        int distance = abs(right[i] - current_head);
        total_seek_time += distance;
        current_head = right[i];
        printf(" -> %d", current_head);
    }

    // 4. JUMP to the lowest request on the LEFT side (Wrap around)
    //    In C-LOOK, we jump from the highest request directly to the lowest request.
    if (left_count > 0) {
        int distance = abs(left[0] - current_head);
        total_seek_time += distance;
        current_head = left[0];
        printf(" -> %d", current_head);
        
        // 5. Service the remaining LEFT side
        for (int i = 1; i < left_count; i++) {
            distance = abs(left[i] - current_head);
            total_seek_time += distance;
            current_head = left[i];
            printf(" -> %d", current_head);
        }
    }

    printf("\n\n");
    printf("Total Seek Time: %d cylinders\n", total_seek_time);

    return 0;
}