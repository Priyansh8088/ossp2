#include <stdio.h>
#include <stdbool.h>

// Configuration
#define FRAMES 4
#define REF_LEN 16

// Function to print the current state of frames
void printFrames(int frames[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("_ "); // Represents empty
        else
            printf("%d ", frames[i]);
    }
    printf("]");
}

int main() {
    // 1. Input Data
    int referenceString[REF_LEN] = {7, 5, 2, 3, 1, 4, 2, 5, 3, 7, 5, 6, 2, 1, 4, 3};
    int frames[FRAMES];
    int timeLastUsed[FRAMES]; // Tracks when a frame was last accessed
    int pageFaults = 0;
    int counter = 0; // Global time counter

    // 2. Initialize frames to -1 (Empty)
    for (int i = 0; i < FRAMES; i++) {
        frames[i] = -1;
        timeLastUsed[i] = 0;
    }

    // 3. Process the reference string
    for (int i = 0; i < REF_LEN; i++) {
        int page = referenceString[i];
        bool found = false;
        int frameIndex = -1;
        counter++; // Increment global time

        // Check if page is already in memory (Hit)
        for (int j = 0; j < FRAMES; j++) {
            if (frames[j] == page) {
                found = true;
                frameIndex = j;
                timeLastUsed[j] = counter; // Update usage time
                break;
            }
        }

        printf("  %2d   ", page);
        printFrames(frames, FRAMES);

        if (found) {
            printf("   Hit                      \n");
        } else {
            // Page Fault (Miss)
            pageFaults++;
            
            // Check for empty space first
            bool hasEmpty = false;
            for(int j=0; j<FRAMES; j++) {
                if(frames[j] == -1) {
                    frames[j] = page;
                    timeLastUsed[j] = counter;
                    hasEmpty = true;
                    printf("   Miss (Loaded into empty) \n");
                    break;
                }
            }

            // If no empty space, find LRU to replace
            if(!hasEmpty) {
                int lruIndex = 0;
                int minTime = timeLastUsed[0];

                // Find the index with the smallest 'timeLastUsed'
                for(int j=1; j<FRAMES; j++) {
                    if(timeLastUsed[j] < minTime) {
                        minTime = timeLastUsed[j];
                        lruIndex = j;
                    }
                }

                int replacedPage = frames[lruIndex];
                frames[lruIndex] = page;
                timeLastUsed[lruIndex] = counter;
                printf("   Miss (Replaced %d)       \n", replacedPage);
            }
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}