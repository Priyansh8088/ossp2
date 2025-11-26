#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] != -1) printf("%d ", frames[i]);
        else printf("- ");
    }
    printf("\n");
}

// --- LFU Logic ---
void LFU(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES];
    int freq[MAX_FRAMES];    // Frequency of pages
    int arrival[MAX_FRAMES]; // Time of arrival (for FIFO tie-break)
    
    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }

    int page_faults = 0;

    printf("\nRef\tFrames\n");
    for (int i = 0; i < n_pages; i++) {
        printf("%d\t", pages[i]);
        
        int found_idx = -1;
        for (int j = 0; j < n_frames; j++) {
            if (frames[j] == pages[i]) {
                found_idx = j;
                break;
            }
        }

        if (found_idx != -1) {
            freq[found_idx]++;
            printFrames(frames, n_frames);
        } else {
            page_faults++;
            int victim = -1;
            
            // Fill empty slots
            for (int j = 0; j < n_frames; j++) {
                if (frames[j] == -1) {
                    victim = j;
                    break;
                }
            }

            if (victim == -1) {
                int min_freq = INT_MAX;
                int min_arrival = INT_MAX;

                for (int j = 0; j < n_frames; j++) {
                    // Find min freq, break ties with FIFO (arrival time)
                    if (freq[j] < min_freq) {
                        min_freq = freq[j];
                        min_arrival = arrival[j];
                        victim = j;
                    } else if (freq[j] == min_freq) {
                        if (arrival[j] < min_arrival) {
                            min_arrival = arrival[j];
                            victim = j;
                        }
                    }
                }
            }

            frames[victim] = pages[i];
            freq[victim] = 1;      
            arrival[victim] = i;   
            printFrames(frames, n_frames);
        }
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int n_pages, n_frames;

    printf("--- LFU Page Replacement ---\n");
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);

    printf("Enter number of pages: ");
    scanf("%d", &n_pages);

    printf("Enter reference string: ");
    for (int i = 0; i < n_pages; i++) scanf("%d", &pages[i]);

    LFU(pages, n_pages, n_frames);

    return 0;
}