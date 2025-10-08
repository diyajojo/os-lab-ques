#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[3];
    int locctr, start, length;

    FILE *input = fopen("input.txt", "r");      // Program instructions
    FILE *optab = fopen("optab.txt", "r");      // Operation codes (like ADD, SUB)
    FILE *symtab = fopen("symtab.txt", "w");    // Symbol table to store labels
    FILE *intermediate = fopen("intermediate.txt", "w"); // Stores intermediate file with addresses
    FILE *lenfile = fopen("length.txt", "w");   // Stores program length

    // Read first line from input file
    fscanf(input, "%s %s %s", label, opcode, operand);

    // If program starts with START, set starting address
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand); // convert operand (string) to number
        locctr = start;        // location counter starts from here
        fprintf(intermediate, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    // Process all instructions until END
    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // If label exists, add to symbol table
        if (strcmp(label, "**") != 0) {
            fprintf(symtab, "%s\t%d\n", label, locctr);
        }

        // Check opcode in optab
        fscanf(optab, "%s %s", code, mnemonic);
        while (strcmp(code, "END") != 0) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3; // normal instruction takes 3 bytes
                break;
            }
            fscanf(optab, "%s %s", code, mnemonic);
        }

        // If opcode is directive, handle separately
        if (strcmp(opcode, "WORD") == 0) locctr += 3;
        else if (strcmp(opcode, "RESW") == 0) locctr += 3 * atoi(operand);
        else if (strcmp(opcode, "BYTE") == 0) locctr += 1;
        else if (strcmp(opcode, "RESB") == 0) locctr += atoi(operand);

        fscanf(input, "%s %s %s", label, opcode, operand);
        rewind(optab); // reset optab to start for next instruction
    }

    // Print last line
    fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // Calculate program length
    length = locctr - start;
    fprintf(lenfile, "%d", length);
    printf("\nThe length of the program is: %d\n", length);

    // Close all files
    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(intermediate);
    fclose(lenfile);

    return 0;
}
