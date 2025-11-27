#include <stdio.h>

int pages[] = {7,5,2,3,1,4,2,5,3,7,5,6,2,1,4,3};
int n = 16;
int frames = 4;

void print(int f[]) {
    for(int i=0; i<frames; i++){
        if(f[i]==-1) printf("- ");
        else printf("%d ", f[i]);
    }
}

// ==================== FIFO ====================
void FIFO() {
    int f[4], pointer = 0, faults = 0;
    for(int i=0; i<frames; i++) f[i] = -1;
    
    printf("\n\n=== FIFO ===\n");
    for(int i=0; i<n; i++) {
        int page = pages[i];
        int found = 0;
        for(int j=0; j<frames; j++)
            if(f[j]==page) found = 1;
            
        printf("Page %d -> ", page);
        if(!found){
            f[pointer] = page;
            pointer = (pointer+1)%frames;
            faults++;
            print(f); printf(" Fault\n");
        } else {
            print(f); printf(" Hit\n");
        }
    }
    printf("Total Faults (FIFO): %d\n", faults);
}

// ==================== LRU ====================
void LRU() {
    int f[4], used[4], faults=0;
    for(int i=0; i<frames; i++){ f[i]=-1; used[i]=-1;}
    
    printf("\n\n=== LRU ===\n");
    for(int i=0; i<n; i++){
        int page = pages[i], pos=-1;
        for(int j=0; j<frames; j++)
            if(f[j]==page) pos=j;
            
        printf("Page %d -> ", page);
        if(pos!=-1){
            used[pos] = i;
            print(f); printf(" Hit\n");
        } else {
            int lru = 0;
            for(int j=1; j<frames; j++)
                if(used[j] < used[lru]) lru=j;
                
            f[lru] = page;
            used[lru] = i;
            faults++;
            print(f); printf(" Fault\n");
        }
    }
    printf("Total Faults (LRU): %d\n", faults);
}

// ==================== LFU ====================
void LFU() {
    int f[4], freq[4], faults=0;
    for(int i=0; i<frames; i++){ f[i]=-1; freq[i]=0; }
    
    printf("\n\n=== LFU ===\n");
    for(int i=0; i<n; i++){
        int page = pages[i];
        int pos=-1;
        for(int j=0; j<frames; j++)
            if(f[j]==page) pos=j;
            
        printf("Page %d -> ", page);
        if(pos!=-1){
            freq[pos]++;
            print(f); printf(" Hit\n");
        } else {
            int lfu = 0;
            for(int j=1; j<frames; j++)
                if(freq[j] < freq[lfu]) lfu=j;
                
            f[lfu] = page;
            freq[lfu] = 1;
            faults++;
            print(f); printf(" Fault\n");
        }
    }
    printf("Total Faults (LFU): %d\n", faults);
}

// ==================== OPTIMAL ====================
int next_use(int page, int start){
    for(int i=start+1; i<n; i++)
        if(pages[i]==page) return i;
    return 9999;
}

void OPTIMAL() {
    int f[4], faults=0;
    for(int i=0; i<frames; i++) f[i]=-1;
    
    printf("\n\n=== OPTIMAL ===\n");
    for(int i=0; i<n; i++){
        int page = pages[i], pos=-1;
        for(int j=0; j<frames; j++)
            if(f[j]==page) pos=j;
            
        printf("Page %d -> ", page);
        if(pos!=-1){
            print(f); printf(" Hit\n");
        } else {
            int rep=0, far=-1;
            for(int j=0; j<frames; j++){
                int future = (f[j]==-1)?9999:next_use(f[j],i);
                if(future > far){
                    far = future;
                    rep = j;
                }
            }
            f[rep] = page;
            faults++;
            print(f); printf(" Fault\n");
        }
    }
    printf("Total Faults (OPTIMAL): %d\n", faults);
}

// ==================== SECOND CHANCE ====================
void SECOND_CHANCE() {
    int f[4], ref[4]={0}, pointer=0, faults=0;
    for(int i=0; i<frames; i++) f[i]=-1;
    
    printf("\n\n=== SECOND CHANCE ===\n");
    for(int i=0; i<n; i++){
        int page = pages[i], pos=-1;
        for(int j=0; j<frames; j++)
            if(f[j]==page){ pos=j; ref[j]=1; }
            
        printf("Page %d -> ", page);
        if(pos!=-1){
            print(f); printf(" Hit\n");
        } else {
            while(ref[pointer]==1){
                ref[pointer]=0;
                pointer=(pointer+1)%frames;
            }
            f[pointer]=page;
            ref[pointer]=1;
            pointer=(pointer+1)%frames;
            faults++;
            print(f); printf(" Fault\n");
        }
    }
    printf("Total Faults (Second Chance): %d\n", faults);
}

int main(){
    FIFO();
    LRU();
    LFU();
    OPTIMAL();
    SECOND_CHANCE();
    return 0;
}