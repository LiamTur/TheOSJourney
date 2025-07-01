/*round robin*/

#include <stdio.h>

#define MAX 10  // Maximum number of processes

// Structure to hold process details
struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int remainingTime;  // Remaining Time
    int waitingTime;    // Waiting Time
    int turnaroundTime; // Turnaround Time
};

void roundRobin(struct Process processes[], int n, int timeQuantum) {
	int currentTime = 0;
	int completed = 0;
	float totalWatingTime = 0, totalTurnaroundTime = 0;
	
	while (completed < n) {
		for(int i = 0; i < n; i++){
      			if(processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)  {
      				if(processes[i].remainingTime > timeQuantum) {
      				processes[i].remaniningTime -= timeQuantum;
      				currentTime += timeQuantum;
      			} else {
      			currentTime += processes[i].remainingTime;
      			processes[i].waitingTime = currentTime - processes[i].arrivalTime -processes[i].burstTime;
      			processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
      			totalWaitingTime += processes[i].waitingTime;
      			totalTurnaroundTime += processes[i].turnaroundTime;
      			processes[i].remainingTime = 0;
      			completed++;
      			}
		}
	}
}
}

// Main function
int main() {
    struct Process processes[MAX];
    int n, timeQuantum;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input processes' arrival times and burst times
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;  // Initialize remaining time
    }

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    // Run Round Robin Scheduling
    roundRobin(processes, n, timeQuantum);

    return 0;
}
