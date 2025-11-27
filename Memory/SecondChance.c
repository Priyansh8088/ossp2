#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] != -1) printf("%d ", frames[i]);
        else printf("- ");
    }
    printf("\n");
}


void SecondChance(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES];
    int ref_bit[MAX_FRAMES]; 
    int ptr = 0; 
    int page_faults = 0;

    for (int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        ref_bit[i] = 0;
    }

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
            ref_bit[found_idx] = 1; 
            printFrames(frames, n_frames);
        } else {
            page_faults++;
            
            while (1) {
                if (frames[ptr] == -1) { 
                    frames[ptr] = pages[i];
                    ref_bit[ptr] = 1; 
                    ptr = (ptr + 1) % n_frames;
                    break;
                }

                if (ref_bit[ptr] == 0) { 
                    frames[ptr] = pages[i];
                    ref_bit[ptr] = 1;
                    ptr = (ptr + 1) % n_frames;
                    break;
                } else { 
                    ref_bit[ptr] = 0;
                    ptr = (ptr + 1) % n_frames;
                }
            }
            printFrames(frames, n_frames);
        }
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int n_pages, n_frames;

    printf("--- Second Chance (Clock) Replacement ---\n");
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);

    printf("Enter number of pages: ");
    scanf("%d", &n_pages);

    printf("Enter reference string: ");
    for (int i = 0; i < n_pages; i++) scanf("%d", &pages[i]);

    SecondChance(pages, n_pages, n_frames);

    return 0;
}