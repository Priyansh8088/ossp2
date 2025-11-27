#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {

    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int start_head = 53;
    int n = sizeof(requests) / sizeof(requests[0]);
    

    int left[n], right[n];
    int left_count = 0, right_count = 0;

    int total_seek_time = 0;
    int current_head = start_head;


    qsort(requests, n, sizeof(int), compare);

  
    for (int i = 0; i < n; i++) {
        if (requests[i] >= start_head) {
            right[right_count++] = requests[i];
        } else {
            left[left_count++] = requests[i];
        }
    }

    printf("Sequence of Service:\n");
    printf("%d (Start)", start_head);

    
    for (int i = 0; i < right_count; i++) {
        int distance = abs(right[i] - current_head);
        total_seek_time += distance;
        current_head = right[i];
        printf(" -> %d", current_head);
    }

    
    if (left_count > 0) {
        int distance = abs(left[0] - current_head);
        total_seek_time += distance;
        current_head = left[0];
        printf(" -> %d", current_head);
        
        
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