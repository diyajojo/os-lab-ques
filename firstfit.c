#include <stdio.h>

#define SIZE 10

int allocated[SIZE];

void firstFit(int blockSize[], int nb, int processSize[], int np)
{
    for (int i = 0; i < np; i++)
    {
        allocated[i] = -1; // Initialize allocation array
    }

    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            if (blockSize[j] >= processSize[i]) // Fixed allocation condition
            {
                blockSize[j] -= processSize[i]; // Reduce available block size
                allocated[i] = j; // Store block index
                break; // Move to the next process , no checking for other blocks
            }
        }
    }

    // Display allocation result
    printf("\nProcess Size\tBlock No.\n");
    for (int i = 0; i < np; i++)
    {
        printf("%d\t\t\t\t\t", processSize[i]);
        if (allocated[i] != -1)
        {
            printf("%d\n", allocated[i] + 1); // Display block index (1-based)
        }
        else
        {
            printf("Not Allocated\n");
        }
    }
}

int main()
{
    int blockSize[] = {250, 30, 456, 212, 117};
    int processSize[] = {100, 200, 300, 400};


    // no need , since we know its alreadt 5 for nb and 4 for np
    int nb = sizeof(blockSize) / sizeof(blockSize[0]);
    int np = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, nb, processSize, np);

    return 0;
}
