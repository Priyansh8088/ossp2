#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[], int n_frames) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] != -1) printf("%d ", frames[i]);
        else printf("- ");
    }
    printf("\n");
}

bool isPagePresent(int frames[], int n_frames, int page) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == page) return true;
    }
    return false;
}

// --- Optimal Logic ---
void Optimal(int pages[], int n_pages, int n_frames) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < n_frames; i++) frames[i] = -1;
    
    int page_faults = 0;

    printf("\nRef\tFrames\n");
    for (int i = 0; i < n_pages; i++) {
        printf("%d\t", pages[i]);
        
        if (isPagePresent(frames, n_frames, pages[i])) {
            printFrames(frames, n_frames);
            continue;
        }
        
        page_faults++;
        
        // Check for empty slot
        int empty_slot = -1;
        for(int j=0; j<n_frames; j++) {
            if(frames[j] == -1) {
                empty_slot = j;
                break;
            }
        }

        if (empty_slot != -1) {
            frames[empty_slot] = pages[i];
        } else {
            // Find victim: page not used for longest time
            int furthest = -1;
            int victim_idx = -1;

            for (int j = 0; j < n_frames; j++) {
                int next_use = -1;
                for (int k = i + 1; k < n_pages; k++) {
                    if (pages[k] == frames[j]) {
                        next_use = k;
                        break;
                    }
                }
                
                if (next_use == -1) { // Never used again
                    victim_idx = j;
                    break;
                }
                
                if (next_use > furthest) {
                    furthest = next_use;
                    victim_idx = j;
                }
            }
            frames[victim_idx] = pages[i];
        }
        printFrames(frames, n_frames);
    }
    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int n_pages, n_frames;

    printf("--- Optimal Page Replacement ---\n");
    printf("Enter number of frames: ");
    scanf("%d", &n_frames);

    printf("Enter number of pages: ");
    scanf("%d", &n_pages);

    printf("Enter reference string: ");
    for (int i = 0; i < n_pages; i++) scanf("%d", &pages[i]);

    Optimal(pages, n_pages, n_frames);

    return 0;
}