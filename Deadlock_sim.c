#include <stdio.h>

// Constants defined based on the new data center problem statement
#define TOTAL_PROCESSES_PER_WEEK 5000
#define DEADLOCK_PER_WEEK 1
#define PROCESSES_TERMINATED_PER_DEADLOCK 40
#define AVERAGE_EXECUTION_TIME 1.5 // in hours
#define CPU_IDLE_TIME_PERCENTAGE 18.0 

// Banker's Algorithm specific constants
#define EXECUTION_TIME_INCREASE_PERCENTAGE 12.0 // 12% overhead
#define UTILIZATION_REDUCTION_PERCENTAGE 4.0    // 4% reduction due to safety checks

// ------------------------------------------------------
// HELPER FUNCTIONS
// ------------------------------------------------------

// Calculate Total CPU Time required for the week's processes
// Formula: Total Processes * Average Execution Time per Job
double calculateTotalCPUTimePerWeek(int totalProcesses, double execTime) {
    return totalProcesses * execTime;
}

// Calculate CPU time lost due to killing processes when deadlock occurs
// Formula: Deadlocks * Processes Terminated * Execution Time (Assuming full work lost)
double calculateCPULostTimeDueToDeadlock(int deadlocksPerWeek, int terminatedPerDeadlock, double execTime) {
    return deadlocksPerWeek * terminatedPerDeadlock * execTime;
}

// Calculate Idle CPU Time based on percentage
double calculateIdleCPUTime(double totalCPUTime) {
    return totalCPUTime * (CPU_IDLE_TIME_PERCENTAGE / 100.0);
}

// Calculate Resource Utilization Percentage
// Formula: (Effective Time / Total Time) * 100
double resourceUtilization(double totalCPUTime, double idleCPUTime, double lostCPUTime) {
    double effectiveCPUTime = totalCPUTime - idleCPUTime - lostCPUTime;
    return (effectiveCPUTime / totalCPUTime) * 100.0;
}

// ------------------------------------------------------
// SIMULATION 1: Without Deadlock Avoidance
// ------------------------------------------------------
void simulateWithoutDeadlockAvoid() {
    printf("\n=== (a) SIMULATION: WITHOUT DEADLOCK AVOIDANCE ===\n");
    
    // 1. Calculate Total CPU Time (Base)
    double totalCPUTime = calculateTotalCPUTimePerWeek(TOTAL_PROCESSES_PER_WEEK, AVERAGE_EXECUTION_TIME);
    
    // 2. Calculate Idle Time
    double idleCPUTime = calculateIdleCPUTime(totalCPUTime);
    
    // 3. Calculate Lost Time due to Deadlocks
    double lostCPUTime = calculateCPULostTimeDueToDeadlock(DEADLOCK_PER_WEEK, 
                                                         PROCESSES_TERMINATED_PER_DEADLOCK, 
                                                         AVERAGE_EXECUTION_TIME);
    
    int totalProcessesLost = DEADLOCK_PER_WEEK * PROCESSES_TERMINATED_PER_DEADLOCK;

    // 4. Calculate Metrics
    double util = resourceUtilization(totalCPUTime, idleCPUTime, lostCPUTime);

    printf("Total CPU Time: %.2f hours\n", totalCPUTime);
    printf("------------------------------------------------\n");
    printf("Number of Processes Lost/Restarted: %d\n", totalProcessesLost);
    printf("CPU Idle Percentage: %.2f%%\n", CPU_IDLE_TIME_PERCENTAGE);
    printf("Lost CPU Time (Deadlocks): %.2f hours\n", lostCPUTime);
    printf("Resource Utilization Percentage: %.2f%%\n", util);
}

// ------------------------------------------------------
// SIMULATION 2: With Banker's Algorithm
// ------------------------------------------------------
void simulateWithBankersAlgo() {
    printf("\n=== (b) SIMULATION: WITH BANKER'S ALGORITHM ===\n");
    
    // 1. Adjust Execution Time (12% Overhead)
    double newExecutionTime = AVERAGE_EXECUTION_TIME * (1.0 + (EXECUTION_TIME_INCREASE_PERCENTAGE / 100.0));
    
    // 2. Calculate New Total CPU Time
    double totalCPUTime = calculateTotalCPUTimePerWeek(TOTAL_PROCESSES_PER_WEEK, newExecutionTime);
    
    // 3. Calculate Idle Time (Percentage remains same relative to total time)
    double idleCPUTime = calculateIdleCPUTime(totalCPUTime);
    
    // 4. Lost Time is 0 (Deadlocks eliminated)
    double lostCPUTime = 0.0; 
    int totalProcessesLost = 0;
    
    // 5. Calculate Metrics
    double util = resourceUtilization(totalCPUTime, idleCPUTime, lostCPUTime);
    
    // 6. Apply specific penalty for Banker's overhead on Utilization
    // "reduce overall resource utilization by 4% due to additional safety checks"
    double adjustedUtil = util - UTILIZATION_REDUCTION_PERCENTAGE;

    printf("Total CPU Time (with overhead): %.2f hours\n", totalCPUTime);
    printf("------------------------------------------------\n");
    printf("Number of Processes Lost/Restarted: %d (Eliminated)\n", totalProcessesLost);
    printf("CPU Idle Percentage: %.2f%%\n", CPU_IDLE_TIME_PERCENTAGE);
    printf("Resource Utilization (Calculated): %.2f%%\n", util);
    printf("Resource Utilization (Final with -%.0f%% Penalty): %.2f%%\n", UTILIZATION_REDUCTION_PERCENTAGE, adjustedUtil);
}

// ------------------------------------------------------
// MAIN
// ------------------------------------------------------
int main() {
    simulateWithoutDeadlockAvoid();
    simulateWithBankersAlgo();
    return 0;
}