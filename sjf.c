#include <stdio.h>

#define MAX 10

int np, at[MAX], bt[MAX], wt[MAX], tat[MAX], count = 0, ct = 0;
int done[MAX] = {0}; 

void findTime(int np, int at[], int bt[], int wt[], int tat[]) {
    while (count < np) {
        int minBurst = 1e9;
        int selectedProcess = -1;

        // Find the process with the shortest burst time among available ones
        for (int i = 0; i < np; i++) {
            // at[i] should be less than ct , and burst time should be lesser than minburst
            if (at[i] <= ct && done[i] == 0 && bt[i] < minBurst) 
            {
                minBurst = bt[i];
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1) {
            ct++; // No process available, move time forward
        } else {
            wt[selectedProcess] = ct - at[selectedProcess]; // Waiting time
            tat[selectedProcess] = wt[selectedProcess] + bt[selectedProcess]; // Turnaround time
            ct += bt[selectedProcess]; // Update time
            done[selectedProcess] = 1; // Mark process as completed
            count++;
        }
    }
}

void findAvg(int np, int at[], int bt[]) {
    int totalWT = 0, totalTAT = 0;
    
    findTime(np, at, bt, wt, tat);

    printf("PID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < np; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWT / np);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / np);
}

int main() {
    np = 5;
    int at[] = {0, 2, 3, 1, 4}; 
    int bt[] = {12, 3, 46, 34, 45}; 


    findAvg(np, at, bt); 

    return 0;
}
