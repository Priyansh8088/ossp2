#include <stdio.h>

// Constants defined based on the new problem statement
#define TOTAL_PROCESSES_PER_WEEK 3000
#define DEADLOCK_PER_WEEK 2
#define PROCESSES_TERMINATED_PER_DEADLOCK 25
#define AVERAGE_EXECUTION_TIME 2.0 // in hours
#define CPU_IDLE_TIME_PERCENTAGE 28.0 

// Banker's Algorithm specific constants
#define EXECUTION_TIME_INCREASE_PERCENTAGE 10.0 // 10% overhead
#define UTILIZATION_REDUCTION_PERCENTAGE 3.0    // 3% reduction due to safety checks

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

// Calculate Turnaround Time
double calculateTurnaroundTime(double totalCPUTime, int totalProcesses) {
    return totalCPUTime / totalProcesses;
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
    // (Deadlocks occur 2x a week, terminating 25 processes each time)
    double lostCPUTime = calculateCPULostTimeDueToDeadlock(DEADLOCK_PER_WEEK, 
                                                         PROCESSES_TERMINATED_PER_DEADLOCK, 
                                                         AVERAGE_EXECUTION_TIME);
                                                         
    // 4. Calculate Metrics
    double util = resourceUtilization(totalCPUTime, idleCPUTime, lostCPUTime);
    double turnaround = calculateTurnaroundTime(totalCPUTime, TOTAL_PROCESSES_PER_WEEK);

    printf("Total Processes: %d\n", TOTAL_PROCESSES_PER_WEEK);
    printf("Total CPU Time: %.2f hours\n", totalCPUTime);
    printf("Idle CPU Time: %.2f hours\n", idleCPUTime);
    printf("Lost CPU Time (Deadlocks): %.2f hours\n", lostCPUTime);
    printf("------------------------------------------------\n");
    printf("Average Turnaround Time: %.4f hours\n", turnaround);
    printf("Number of Deadlocks per Week: %d\n", DEADLOCK_PER_WEEK);
    printf("Resource Utilization: %.2f%%\n", util);
}

// ------------------------------------------------------
// SIMULATION 2: With Banker's Algorithm
// ------------------------------------------------------
void simulateWithBankersAlgo() {
    printf("\n=== (b) SIMULATION: WITH BANKER'S ALGORITHM ===\n");
    
    // 1. Adjust Execution Time (10% Overhead)
    double newExecutionTime = AVERAGE_EXECUTION_TIME * (1.0 + (EXECUTION_TIME_INCREASE_PERCENTAGE / 100.0));
    
    // 2. Calculate New Total CPU Time
    double totalCPUTime = calculateTotalCPUTimePerWeek(TOTAL_PROCESSES_PER_WEEK, newExecutionTime);
    
    // 3. Calculate Idle Time (Percentage remains same relative to total time)
    double idleCPUTime = calculateIdleCPUTime(totalCPUTime);
    
    // 4. Lost Time is 0 (Deadlocks eliminated)
    double lostCPUTime = 0.0; 
    
    // 5. Calculate Metrics
    double util = resourceUtilization(totalCPUTime, idleCPUTime, lostCPUTime);
    double turnaround = calculateTurnaroundTime(totalCPUTime, TOTAL_PROCESSES_PER_WEEK);
    
    // 6. Apply specific penalty for Banker's overhead on Utilization
    // "reduce overall resource utilization by 3% due to additional safety checks"
    double adjustedUtil = util - UTILIZATION_REDUCTION_PERCENTAGE;

    printf("New Average Execution Time: %.4f hours (+%.0f%%)\n", newExecutionTime, EXECUTION_TIME_INCREASE_PERCENTAGE);
    printf("Total CPU Time: %.2f hours\n", totalCPUTime);
    printf("Idle CPU Time: %.2f hours\n", idleCPUTime);
    printf("Lost CPU Time (Deadlocks): %.2f hours\n", lostCPUTime);
    printf("------------------------------------------------\n");
    printf("Average Turnaround Time: %.4f hours\n", turnaround);
    printf("Number of Deadlocks per Week: 0 (Eliminated)\n");
    printf("Resource Utilization (Raw): %.2f%%\n", util);
    printf("Resource Utilization (Adjusted -%.0f%%): %.2f%%\n", UTILIZATION_REDUCTION_PERCENTAGE, adjustedUtil);
}

// ------------------------------------------------------
// MAIN
// ------------------------------------------------------
int main() {
    simulateWithoutDeadlockAvoid();
    simulateWithBankersAlgo();
    return 0;
}