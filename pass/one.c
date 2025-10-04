#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[20];
    int length, start, locctr = 0;

    FILE *input = fopen("input.txt", "r");
    FILE *optab = fopen("opcode.txt", "r");
    FILE *symtab = fopen("symtab.txt", "w");
    FILE *intermediate = fopen("intermediate.txt", "w");
    FILE *lenfile = fopen("length.txt", "w");

    if (!input || !optab || !symtab || !intermediate || !lenfile) {
        printf("Error opening one of the files.\n");
        return 1;
    }

    fscanf(input, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(intermediate, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0) {
            fprintf(symtab, "%s\t%d\n", label, locctr);
        }

        rewind(optab);
        fscanf(optab, "%s %s", code, mnemonic);

        while (!feof(optab)) {
            if (strcmp(code, opcode) == 0) {
                locctr += 3;
                break;
            }
            fscanf(optab, "%s %s", code, mnemonic);
        }

        if (strcmp(opcode, "WORD") == 0)
            locctr += 3;
        else if (strcmp(opcode, "RESW") == 0)
            locctr += 3 * atoi(operand);
        else if (strcmp(opcode, "BYTE") == 0)
            locctr += 1;
        else if (strcmp(opcode, "RESB") == 0)
            locctr += atoi(operand);

        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;
    printf("Length of the program is %d\n", length);
    fprintf(lenfile, "%d", length);

    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(intermediate);
    fclose(lenfile);

    return 0;
}
