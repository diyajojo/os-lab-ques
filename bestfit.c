#include <stdio.h>

#define MAX 10

int allocated[MAX];

void bestFit(int blockSize[], int nb, int processSize[], int np)
{
    // Initialize allocation array to -1 (meaning "not allocated")
    for (int i = 0; i < np; i++)
    {
        allocated[i] = -1;
    }

    // Best-fit allocation
    for (int i = 0; i < np; i++)
    {
        int minIndex = -1; // Track best-fit block

        for (int j = 0; j < nb; j++)
        {
            if (blockSize[j] >= processSize[i]) // Block must be large enough
            {
                if (minIndex == -1 || blockSize[j] < blockSize[minIndex])
                {
                    minIndex = j; // Choose smaller fitting block
                }
            }
        }

        // If a block is found, allocate memory
        if (minIndex != -1)
        {
            blockSize[minIndex] -= processSize[i]; // Reduce available size
            allocated[i] = minIndex; // Store allocated block index
        }
    }

    // Display results
    printf("\nProcess Size\tBlock Number\n");
    for (int i = 0; i < np; i++)
    {
        printf("%d\t\t", processSize[i]);
        if (allocated[i] != -1)
        {
            printf("%d\n", allocated[i] + 1); // Display 1-based block index
        }
        else
        {
            printf("Not Allocated\n");
        }
    }
}

int main()
{
    int blockSize[] = {100, 200, 300, 400, 500};
    int processSize[] = {212, 113, 456, 70};
    int nb = sizeof(blockSize) / sizeof(blockSize[0]);
    int np = sizeof(processSize) / sizeof(processSize[0]);

    bestFit(blockSize, nb, processSize, np);

    return 0;
}
