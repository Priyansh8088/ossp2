#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Helper to print current frames state
void printFrames(int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

// Helper to check if a page exists in frames
bool isPagePresent(int frames[], int n_frames, int page) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}

// --- FIFO Logic ---
void FIFO(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < n_frames; i++) frames[i] = -1; // Initialize empty
    
    int page_faults = 0;
    int current = 0; // Pointer for FIFO replacement

    printf("\nRef\tFrames\t\tStatus\n");
    for (int i = 0; i < n_pages; i++) {
        printf("%d\t", pages[i]);
        
        if (!isPagePresent(frames, n_frames, pages[i])) {
            frames[current] = pages[i];
            current = (current + 1) % n_frames;
            page_faults++;
            printFrames(frames, n_frames);
        } else {
            printFrames(frames, n_frames);
            // printf("\tHit"); 
        }
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int n_pages, n_frames;

    printf("--- FIFO Page Replacement ---\n");
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);

    printf("Enter number of pages: ");
    scanf("%d", &n_pages);

    printf("Enter reference string: ");
    for (int i = 0; i < n_pages; i++) {
        scanf("%d", &pages[i]);
    }

    FIFO(pages, n_pages, n_frames);

    return 0;
}