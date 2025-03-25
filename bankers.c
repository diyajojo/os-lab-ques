#include <stdio.h>

#define MAX 10

int max[MAX][MAX], alloc[MAX][MAX], avail[MAX], tempavail[MAX], need[MAX][MAX], finish[MAX];
int p = 0, r = 0, canRun = 0;
int count = 0;

int Safe(int p, int r, int tempavail[], int finish[]) 
{
    int done;
    count = 0;

    while (count < p) {
        done = 0;
        for (int i = 0; i < p; i++)
         {
            if (finish[i] == 0) 
            {
                canRun = 1;
                
                // Calculate need matrix
                for (int j = 0; j < r; j++) 
                {
                    need[i][j] = max[i][j] - alloc[i][j];
                    if (need[i][j] > tempavail[j]) 
                    {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun == 1) 
                {
                    // Process can execute
                    for (int j = 0; j < r; j++)
                     {
                        tempavail[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    count++;
                    done = 1;
                }
            }
        }
        // exits the entire safe function if deadlock is detected
        if (done == 0)
            return 0;  // Deadlock detected
    }
    // at the end of while loop, if all processes are finished
    return 1;  // No deadlock
}

int main() {

    printf("Enter number of processes and resources:\n");
    scanf("%d%d", &p, &r);

    printf("Enter max resource matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocated resource matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for (int i = 0; i < r; i++) 
    {
        scanf("%d", &avail[i]);
        tempavail[i] = avail[i];
    }

    for (int i = 0; i < p; i++) 
    {
        finish[i] = 0;
    }

    if (Safe(p, r, tempavail, finish))
        printf("Deadlock not present\n");
    else
        printf("Deadlock detected\n");

    return 0;
}
