#include <stdio.h>
#include <stdlib.h>

int main() {
    int req[] = {82, 170, 43, 140, 24, 16, 190};
    int n = 7;
    int head = 50;
    int visited[7] = {0};
    int total = 0;
    
    for(int c = 0; c < n; c++) {
        int min = 9999;
        int index = -1;
        // find nearest request
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                int dist = abs(req[i] - head);
                if(dist < min) {
                    min = dist;
                    index = i;
                }
            }
        }
        // move head to nearest
        total += abs(req[index] - head);
        head = req[index];
        visited[index] = 1;
    }
    
    printf("SSTF Total Movement = %d tracks\n", total);
    printf("SSTF Seek Time = %.2f ms\n", total * 0.06);
    
    return 0;
}