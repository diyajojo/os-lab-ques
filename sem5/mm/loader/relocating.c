#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert hexadecimal bitmask to binary bitmask
void convert(char hexMask[], char bitMask[]) {
    strcpy(bitMask, "");
    for (int i = 0; i < strlen(hexMask); i++) {
        switch (hexMask[i]) {
            case '0': strcat(bitMask, "0000"); break;
            case '1': strcat(bitMask, "0001"); break;
            case '2': strcat(bitMask, "0010"); break;
            case '3': strcat(bitMask, "0011"); break;
            case '4': strcat(bitMask, "0100"); break;
            case '5': strcat(bitMask, "0101"); break;
            case '6': strcat(bitMask, "0110"); break;
            case '7': strcat(bitMask, "0111"); break;
            case '8': strcat(bitMask, "1000"); break;
            case '9': strcat(bitMask, "1001"); break;
            case 'A': case 'a': strcat(bitMask, "1010"); break;
            case 'B': case 'b': strcat(bitMask, "1011"); break;
            case 'C': case 'c': strcat(bitMask, "1100"); break;
            case 'D': case 'd': strcat(bitMask, "1101"); break;
            case 'E': case 'e': strcat(bitMask, "1110"); break;
            case 'F': case 'f': strcat(bitMask, "1111"); break;
        }
    }
}

int main() {
    char progName[10], startAddrStr[10], lengthStr[10];
    char recordType[5], bitmaskHex[13], bitmaskBin[49];
    int startAddr, textAddr, textLen, opcode, addr, actualAddr;

    FILE *inputFile, *outputFile;

    printf("Enter the actual starting address (in hex): ");
    scanf("%x", &startAddr);

    inputFile = fopen("RLIN.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    outputFile = fopen("RLOUT.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    fscanf(inputFile, "%s", recordType);

    while (strcmp(recordType, "E") != 0) {
        if (strcmp(recordType, "H") == 0) {
            fscanf(inputFile, "%s %s %s", progName, startAddrStr, lengthStr);
            fscanf(inputFile, "%s", recordType);
        }

        if (strcmp(recordType, "T") == 0) {
            fscanf(inputFile, "%x %x %s", &textAddr, &textLen, bitmaskHex);
            textAddr += startAddr; // relocate text address
            convert(bitmaskHex, bitmaskBin);

            int numInstructions = textLen / 3;
            for (int i = 0; i < numInstructions; i++) {
                fscanf(inputFile, "%x %x", &opcode, &addr);
                if (bitmaskBin[i] == '1')
                    actualAddr = addr + startAddr; // relocation
                else
                    actualAddr = addr;

                fprintf(outputFile, "%04X %02X%04X\n", textAddr, opcode, actualAddr);
                textAddr += 3;
            }
            fscanf(inputFile, "%s", recordType);
        }
    }

    fclose(outputFile);
    fclose(inputFile);

    printf("Relocating loader completed.\n");
    return 0;
}
