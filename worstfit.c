#include <stdio.h>

#define SIZE 10

int allocated[SIZE];

void worstFit(int blockSize[], int nb, int processSize[], int np) {
    for (int i = 0; i < np; i++) {
        allocated[i] = -1; // Initialize as not allocated
    }

    for (int i = 0; i < np; i++) {
        int maxIndex = -1;

        for (int j = 0; j < nb; j++) {
            // First check if the block can fit the process
            if (blockSize[j] >= processSize[i]) {  
                // Then check if it's the largest available block
                if (maxIndex == -1 || blockSize[j] > blockSize[maxIndex]) {
                    maxIndex = j;
                }
            }
        }

        // If a suitable block is found, allocate the process
        if (maxIndex != -1) {
            allocated[i] = maxIndex;
            blockSize[maxIndex] -= processSize[i]; // Reduce block size
        }
    }

    // Print allocation results
    printf("Process size\t\tBlock number\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t\t\t", processSize[i]);
        if (allocated[i] != -1) {
            printf("%d\n", allocated[i]);
        } else {
            printf("Not allocated\n");
        }
    }
}

int main() {
    int blockSize[] = {250, 30, 456, 212, 117};
    int processSize[] = {100, 200, 300, 400};

    // nned to calculate the size of the array , gives same result
    int nb = sizeof(blockSize) / sizeof(blockSize[0]);
    int np = sizeof(processSize) / sizeof(processSize[0]);

    worstFit(blockSize, nb, processSize, np);

    return 0;
}
