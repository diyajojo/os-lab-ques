#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[20];
    char symlabel[20];
    int address, length, start, symadd;

    FILE *intermediate = fopen("intermediate.txt", "r");
    FILE *optab = fopen("optab.txt", "r");
    FILE *symtab = fopen("symtab.txt", "r");
    FILE *lenfile = fopen("length.txt", "r");

    if (!intermediate || !optab || !symtab || !lenfile) {
        printf("Error opening file(s)\n");
        return 1;
    }

    fscanf(intermediate, "%s %s %s", label, opcode, operand);
    fscanf(lenfile, "%d", &length);

    if (strcmp(opcode, "START") == 0)
        start = atoi(operand);
    else
        start = 0;

    printf("H^%s^%06d^%06X\n", label, start, length);

    while (fscanf(intermediate, "%d %s %s %s", &address, label, opcode, operand) == 4) {
        if (strcmp(opcode, "END") == 0)
            break;

        int found = 0;
        rewind(optab);

        // Check if opcode is in optab
        while (fscanf(optab, "%s %s", code, mnemonic) == 2) {
            if (strcmp(opcode, code) == 0) {
                found = 1;
                rewind(symtab);

                int opadd = 0;
                while (fscanf(symtab, "%s %d", symlabel, &symadd) == 2) {
                    if (strcmp(operand, symlabel) == 0) {
                        opadd = symadd;
                        break;
                    }
                }

                printf("T^%06d^%s%06d\n", address, mnemonic, opadd);
                break;  // exit opcode search
            }
        }

        // Handle WORD or BYTE if opcode not found
        if (!found) {
            if (strcmp(opcode, "WORD") == 0)
                printf("T^%06d^%06X\n", address, atoi(operand));
            else if (strcmp(opcode, "BYTE") == 0)
                printf("T^%06d^%06X\n", address, atoi(operand));
        }
    }

    // End record
    printf("E^%06d\n", start);

    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(lenfile);

    return 0;
}
