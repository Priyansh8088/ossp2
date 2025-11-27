#include <stdio.h>

// Constants defined in the notes
#define TOTAL_PROCESSES_PER_WEEK 5000
#define DEADLOCK_PER_WEEK 1
#define PROCESSES_TERMINATED_PER_DEADLOCK 40
#define AVERAGE_EXECUTION_TIME 1.5 // in some time unit
#define CPU_IDLE_TIME_PERCENTAGE 15.0 // Interpreted as 15 from handwriting
#define RESOURCE_UTILIZATION_DECREASE_PER 4.0
#define EXECUTION_TIME_INCREASE_PERCENTAGE 12.0 // Overhead of Banker's Algorithm

// ------------------------------------------------------
// HELPER FUNCTIONS (From Image 1)
// ------------------------------------------------------

// Calculate Total CPU Time required for the week's processes
double calculateTotalCPUTimePerWeek(int totalProcesses) {
    return totalProcesses * AVERAGE_EXECUTION_TIME;
}

// Calculate CPU time lost due to killing processes when deadlock occurs
double calculateCPULostTimeDueToDeadlock(int deadlocksPerWeek, int terminatedPerDeadlock, double execTime) {
    return deadlocksPerWeek * terminatedPerDeadlock * execTime;
}

// Calculate Resource Utilization Percentage
double resourceUtilization(double totalCPUTime, double idleCPUTime, double lostCPUTime) {
    double effectiveCPUTime = totalCPUTime - idleCPUTime - lostCPUTime;
    return (effectiveCPUTime / totalCPUTime) * 100.0;
}

// ------------------------------------------------------
// HELPER FUNCTIONS (From Image 2)
// ------------------------------------------------------

double calculateIdleCPUTime(double totalCPUTime) {
    return totalCPUTime * (CPU_IDLE_TIME_PERCENTAGE / 100.0);
}

double calculateTurnaroundTime(double totalCPUTime, int totalProcesses) {
    return totalCPUTime / totalProcesses;
}

// ------------------------------------------------------
// SIMULATION 1: Without Deadlock Avoidance
// ------------------------------------------------------
void simulateWithoutDeadlockAvoid() {
    printf("\n=== SIMULATION: WITHOUT DEADLOCK AVOIDANCE ===\n");
    
    double totalCPUTime = calculateTotalCPUTimePerWeek(TOTAL_PROCESSES_PER_WEEK);
    double idleCPUTime = calculateIdleCPUTime(totalCPUTime);
    double lostCPUTime = calculateCPULostTimeDueToDeadlock(DEADLOCK_PER_WEEK, 
                                                         PROCESSES_TERMINATED_PER_DEADLOCK, 
                                                         AVERAGE_EXECUTION_TIME);
                                                         
    double util = resourceUtilization(totalCPUTime, idleCPUTime, lostCPUTime);
    double turnaround = calculateTurnaroundTime(totalCPUTime, TOTAL_PROCESSES_PER_WEEK);

    printf("Total CPU Time: %.2f\n", totalCPUTime);
    printf("Idle CPU Time: %.2f\n", idleCPUTime);
    printf("Lost CPU Time (Deadlocks): %.2f\n", lostCPUTime);
    printf("Resource Utilization: %.2f%%\n", util);
    printf("Turnaround Time: %.4f\n", turnaround);
}

// ------------------------------------------------------
// SIMULATION 2: With Banker's Algorithm
// ------------------------------------------------------
void simulateWithBankersAlgo() {
    printf("\n=== SIMULATION: WITH BANKER'S ALGORITHM ===\n");
    
    // Banker's algorithm adds overhead, increasing execution time
    double newExecutionTime = AVERAGE_EXECUTION_TIME * (1.0 + (EXECUTION_TIME_INCREASE_PERCENTAGE / 100.0));
    
    // Calculate new total time based on increased execution time
    double totalCPUTime = TOTAL_PROCESSES_PER_WEEK * newExecutionTime;
    
    // Idle time is still a percentage of total time
    double idleCPUTime = calculateIdleCPUTime(totalCPUTime);
    
    // With Banker's, we assume NO deadlocks, so lost time is 0
    double lostCPUTime = 0.0; 
    
    double util = resourceUtilization(totalCPUTime, idleCPUTime, lostCPUTime);
    double turnaround = calculateTurnaroundTime(totalCPUTime, TOTAL_PROCESSES_PER_WEEK);

    printf("New Execution Time (w/ Overhead): %.4f\n", newExecutionTime);
    printf("Total CPU Time: %.2f\n", totalCPUTime);
    printf("Idle CPU Time: %.2f\n", idleCPUTime);
    printf("Lost CPU Time (Deadlocks): %.2f\n", lostCPUTime);
    printf("Resource Utilization: %.2f%%\n", util);
    printf("Turnaround Time: %.4f\n", turnaround);
}

// ------------------------------------------------------
// MAIN
// ------------------------------------------------------
int main() {
    simulateWithoutDeadlockAvoid();
    simulateWithBankersAlgo();
    return 0;
}