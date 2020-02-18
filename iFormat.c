/**
 * I-Format Instructions 
 * 
 * Author: Nikhil Sodemba 
 * Creation Date: Feb, 12th, 2020
 * 
 * This function is to process MIPS Instruction based on I-Format Instructions.
 * The function uses verifyIformat(...) helper function in order to verify the 
 * variables for I-Format Instructions: opcode, rs, rt, and immediate. The 
 * program is functionable to signed binary integers for the immediate.
 * See the comments in functions to see the logic.  
 * 
 */

#include "disassembler.h"

char * iFormat(char string[])
{
    static char * valid = "Valid";
    static char * invalid = "Invalid";
    char * functOp = "";

    // Using this Data Structure approach since C doesn't allow hetergenous arrays
    // Two arrays parallel in index for opcode functions
    int opInt [] = {4,5,8,9,12,13,10,11,15,35,43};
    char * opChar [] = 
    {
        "beq", "bne", "addi", "addiu", "andi", "ori", "slti", "sltiu",
        "lui", "lw", "sw"
    };
    int k;      // iterator value to determine operation from opcode

    // Variables needed for I-Format instructions
    int opcode = binToDec(string, 0, 5);
    int rs = binToDec(string, 6, 10);
    int rt = binToDec(string, 11, 15);
    int immediate = binToDec(string, 17, 31);   // Will be considering this as a signed binary integer

    // Verify if the given variables are valid for I-Format Instruction 
    int verification = verifyIformat(opcode, rs, rt, immediate);
    if(verification == 0)   // invalid variables
    {
        return invalid;
    }

    char *rsReg , *rtReg;

    // Determine positive/negative value for immediate variable
    if(string[16] == '1')   // negative signed binary integer for immediate
    {
        immediate = immediate * -1;
    }   // else do nothing, leave it as positive integer

    // retrieve valid opcode operation from opcode
    for(k = 0; k < 11; k++)
    {
        if(opInt[k] == opcode)
        {
            functOp = opChar[k];
            break;
        }
    }

    // lui - I-Format instruction 
    if(opcode == 15)
    {
        // retrieve rt register
        rtReg = getRegName(rt);
        // print I-Format Instruction 
        printf("\t%s  %s, %d\n", functOp, rtReg, immediate);
    }
    // lw and sw I-format instruction
    else if(opcode == 35 || opcode == 43)
    {
        // retrieve valid registers
        rsReg = getRegName(rs);
        rtReg = getRegName(rt);
        // print I-Format Instruction 
        printf("\t%s  %s, %d(%s)\n",functOp, rtReg, immediate, rsReg);
    }
    // beq and bne I-format Instruction
    else if(opcode == 4 || opcode == 5)
    {
        // retrieve valid registers
        rsReg = getRegName(rs);
        rtReg = getRegName(rt);
        // print I-Format Instruction 
        printf("\t%s  %s, %s, %d\n", functOp, rsReg, rtReg, immediate);
    }
    // all other operations for I-Format instruction
    else
    {
        // retrieve valid registers
        rsReg = getRegName(rs);
        rtReg = getRegName(rt);
        // print I-Format Instruction 
        printf("\t%s  %s, %s, %d\n",functOp, rtReg, rsReg, immediate);
    }
    return valid;
}

/**
 * This helper function will if we have the correct values for the required 
 * variables for I-Format instruction: opcode, rs, rt, and immediate
 * 
 * Disclaimer: rs and rt can access all registers.
 * 
 * Takes all four variables as arguments
 * 
 * Returns 1 if all variables are valid, 0 if otherwise.
 */
int verifyIformat(int opcode, int rs, int rt, int immediate)
{
    // opcode is verified as a valid I-Format variable through the check for format type in disassembler.c
    
    // Verification for rs
    if(rs > 31)
    {
        return 0;
    }
    if(rt > 31)
    {
        return 0;
    }
    // Verification for lui operation - only uses rt register
    if(opcode == 15)
    {
        if(rs != 0)
        {
            return 0;
        }
    }
    // Verification for immediate, has to be in range -32,768 - 32,767
    // Logic for immediate variable only considers positive values 
    if (immediate > 32768)
    {
        return 0;
    }
    return 1;
}
