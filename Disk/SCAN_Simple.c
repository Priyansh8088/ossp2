#include <stdio.h>
#include <stdlib.h>

int main() {
    int req[] = {82, 170, 43, 140, 24, 16, 190};
    int n = 7;
    int head = 50;
    int total = 0;
    int disk_end = 199;
    
    // Step 1: Move upward from 50 -> requests >= 50
    for(int i = 0; i < n; i++) {
        if(req[i] >= head) {
            total += abs(req[i] - head);
            head = req[i];
        }
    }
    
    // Step 2: Move to 199 (end)
    total += abs(disk_end - head);
    head = disk_end;
    
    // Step 3: Now reverse and go downward -> 0
    total += disk_end; // distance 199 -> 0
    head = 0;
    
    // Step 4: Serve all requests < 50
    for(int i = 0; i < n; i++) {
        if(req[i] < 50) {
            total += abs(req[i] - head);
            head = req[i];
        }
    }
    
    printf("SCAN Total Movement = %d tracks\n", total);
    printf("SCAN Seek Time = %.2f ms\n", total * 0.06);
    
    return 0;
}