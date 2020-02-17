/**
 * J-Format Instructions 
 * 
 * Author: Nikhil Sodemba
 * Creation Date: Feb, 12th, 2020
 * 
 * This function is to process the MIPS Instruction based on J-Format Instructions.
 * The comments inside the function provide details to the logics of the function.
 */

#include "disassembler.h"

char * jFormat(char string[])
{
    static char * valid = "Valid";
    char *opFunct = "";

    // Array to hold opcode operations for J-Format instruction
    char *opChar [] = {"j", "jal"};

    int opCode = binToDec(string, 0, 5);
    int address = binToDec(string, 6, 31);

    // Opcode verified in disassembler.c (formatType(...)), can only be values 2 || 3
    if(opCode == 2)
    {
        opFunct = opChar[0];
    }
    else
    {
        opFunct = opChar[1];
    }

    // Print J-Format Instruction to stdout
    printf("\t%s  %d\n", opFunct, address);

    return valid;
}
