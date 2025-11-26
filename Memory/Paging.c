#include <stdio.h>

int main() {
    int mem_size, page_size, process_size, total_frames, pages_req;
    int page_table[100]; // Maps Page Number -> Frame Number
    int logical_addr, physical_addr;
    int page_num, offset, frame_num;
    int choice;

    printf("--- Paging Technique Simulation ---\n");

    // 1. System Configuration
    printf("Enter Total Physical Memory Size (in Bytes): ");
    scanf("%d", &mem_size);

    printf("Enter Page Size (in Bytes): ");
    scanf("%d", &page_size);

    total_frames = mem_size / page_size;
    printf("Total number of Frames available in Memory: %d\n", total_frames);

    // 2. Process Allocation
    printf("\nEnter Process Size (in Bytes): ");
    scanf("%d", &process_size);

    // Calculate pages required (Ceiling division: (A + B - 1) / B)
    pages_req = (process_size + page_size - 1) / page_size;
    printf("Process requires %d pages.\n", pages_req);

    if (pages_req > total_frames) {
        printf("Error: Not enough memory to allocate this process!\n");
        return 1;
    }

    // 3. Create Page Table
    printf("\n--- Enter Page Table (Map Pages to Frames) ---\n");
    for (int i = 0; i < pages_req; i++) {
        printf("Enter Frame Number for Page %d: ", i);
        scanf("%d", &frame_num);

        // Basic validation
        if (frame_num >= total_frames || frame_num < 0) {
            printf("Error: Frame number %d is out of bounds (0 to %d). Try again.\n", frame_num, total_frames - 1);
            i--; // Retry this iteration
        } else {
            page_table[i] = frame_num;
        }
    }

    // 4. Address Translation Loop
    do {
        printf("\n--- Address Translation ---\n");
        printf("Enter a Logical Address to translate (-1 to exit): ");
        scanf("%d", &logical_addr);

        if (logical_addr == -1) break;

        if (logical_addr >= process_size) {
            printf("Error: Logical Address %d is invalid (Process limit is %d).\n", logical_addr, process_size);
            continue;
        }

        // Calculate Page Number and Offset
        page_num = logical_addr / page_size;
        offset = logical_addr % page_size;

        if (page_num >= pages_req) {
            // This case is technically covered by the process_size check, but good for safety
            printf("Error: Page number %d out of bounds.\n", page_num);
        } else {
            frame_num = page_table[page_num];
            
            // Formula: Physical Address = (Frame Number * Page Size) + Offset
            physical_addr = (frame_num * page_size) + offset;

            printf("\nDetails:\n");
            printf("  > Page Number: %d\n", page_num);
            printf("  > Offset:      %d\n", offset);
            printf("  > Frame Found: %d\n", frame_num);
            printf("  > Physical Address: %d\n", physical_addr);
        }

    } while (1);

    printf("Exiting simulation.\n");
    return 0;
}