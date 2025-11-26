#include <stdio.h>

int main() {
    float tlb_hit_ratio;
    float tlb_access_time;
    float mem_access_time;
    float eat;
    

    printf("Enter TLB Hit Ratio (e.g., 0.80 for 80%%): ");
    if (scanf("%f", &tlb_hit_ratio) != 1) {
        printf("Invalid input.\n");
        return 1;
    }


    if (tlb_hit_ratio > 1.0) {
        tlb_hit_ratio = tlb_hit_ratio / 100.0;
    }


    printf("Enter TLB Access Time (in nanoseconds): ");
    scanf("%f", &tlb_access_time);

   
    printf("Enter Main Memory Access Time (in nanoseconds): ");
    scanf("%f", &mem_access_time);


    // Formula: EAT = (Hit_Ratio * Hit_Time) + (Miss_Ratio * Miss_Time)
    float time_on_hit = tlb_access_time + mem_access_time;

    float time_on_miss = tlb_access_time + (2 * mem_access_time);

    eat = (tlb_hit_ratio * time_on_hit) + ((1.0 - tlb_hit_ratio) * time_on_miss);


    printf("Time on Hit:  %.2f ns\n", time_on_hit);
    printf("Time on Miss: %.2f ns\n", time_on_miss);
    printf("Effective Access Time (EAT): %.2f ns\n", eat);

    return 0;
}