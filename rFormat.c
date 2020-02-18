/**
 * R-Format Instructions
 * 
 * Author: Nikhil Sodemba
 * Creation Date: Feb, 12th, 2020
 * 
 * This function is to process the MIPS instruction based on R-Format instructions.
 * The function will determine if each MIPS Instruction has valid variables for: 
 * rs, rt, rd, shamt, and funct. The details of the logic is provided inside the function
 * and function declarations. The rFormat(...) function uses the verifyRformat(...) helper
 * function in order to verify that the variables are valid for R-Format Instructions.
 * The comments and function declaration, provides detail for the logic of each function.
 * 
 */

#include "disassembler.h"

char * rFormat(char string[])
{
    static char * invalid = "Invalid";
    static char * valid = "Valid";
    char * functOp = "";

    // Using this Data Structure approach since C doesn't allow hetergenous arrays
    // Two arrays parallel in index for funct operations
    int functInt [] = {32, 33, 34, 35, 36, 37, 39, 42, 43, 0, 2, 8};
    char * functChar [] = 
    {
        "add", "addu", "sub", "subu", "and", "or", "nor", "slt",
        "sltu", "sll", "srl", "jr"
    };
    int k;  // iterator value to determine index for funct operation

    // We do not need to calculate op for R-Format, it is 0 for all cases.
    int rs = binToDec(string, 6, 10);
    int rt = binToDec(string, 11, 15);
    int rd = binToDec(string, 16, 20);
    int shamt = binToDec(string, 21, 25);
    int funct = binToDec(string, 26, 31);

    // Ensure that the appropriate values are assigned for the given variables.
    int verification = verifyRformat(rs, rt, rd, shamt, funct);
    if(verification == 0)   // Invalid variables for R-Format Instruction
    {
        return invalid;
    }
    
    // find correct funct operation
    for(k = 0; k < 12; k++)
    {
        if(functInt[k]==funct)
        {
            functOp = functChar[k];
            break;
        }
    }
    char *rsReg , *rtReg, *rdReg;
    // R-Format instructions excluding sll, srl and jr
    if (funct > 30)     // Logic will work, after verification of variables
    {
        // Fetch register name 
        rsReg = getRegName(rs);
        rtReg = getRegName(rt);
        rdReg = getRegName(rd);
        // print resulting R-Format instruction to stdout
        printf("\t%s  %s, %s, %s\n", functOp, rdReg, rsReg, rtReg);
    }
    // R-Format instructings for sll and srl
    else if(funct == 0 || funct == 2)
    {
        // Fetch register name
        rtReg = getRegName(rt);
        rdReg = getRegName(rd);
        // print resulting R-Format instruction to stdout
        printf("\t%s  %s, %s, %d\n", functOp, rdReg, rtReg, shamt);
    }
    else if(funct == 8)
    {
        // Fetch register name
        rsReg = getRegName(rs);
        // print resulting R-Format instruction to stdout
        printf("\t%s  %s\n", functOp, rsReg);
    }

    return valid;
}


/**
 * This helper function will verify if we have the correct values for the variables
 * needed for the R-Format Instructions: rs, rt, rd, shamt, and funct.
 * 
 * Disclaimer: Program can change value of register $zero, logic has not been applied 
 * in order for manipulation of this register. Program also allows rs, rt, and rd 
 * to access all registers.
 * 
 * Takes all five variables as arugments
 * 
 * Returns 1 if all variables are valid, else 0.
 */
int verifyRformat(int rs, int rt, int rd, int shamt, int funct)
{
    // All possible values for funct stored in array
    int functOptions [] = {32, 33, 34, 35, 36, 37, 39, 42, 43, 0, 2, 8};
    int k;      // iterator for funct verification
    int functValid = 0;    // check for after functOptions iteration

    // Verification for rs
    if(rs > 31)
    {
        return 0;
    }
    // Verification for rt
    if(rt > 31)
    {
        return 0;
    }
    // Verification for rd
    if(rd > 31)
    {
        return 0;
    }
    // Verification that 
    // Verification for shamt
    // Can shift to a max of 11111 = 31, 0 < shamt < 32 -> Valid shamt
    if(shamt > 31)
    {
        return 0;
    }
    // Verification for funct
    for(k = 0; k < 12; k++)
    {
        if(functOptions[k]==funct)
        {
            // Increment functValid
            functValid ++;
            break;
        }
    }
    if(functValid == 0)
    {
        return 0;
    }
    // shamt should be 0 for all funct operations except sll && srl
    // Verification for shamt = 0 for all other funct operations apart from sll && srl
    if(funct != 0 && funct != 2)
    {
        if(shamt != 0)
        {
            return 0;
        }
    }
    else if(funct == 0 || funct == 2)    // if funct is an operation for sll || srl
    {
        if(shamt == 0)      // for the operations sll || srl, shamt must be 0 < shamt < 32
        {
            return 0;
        }
        if(rs != 0)    // sll && srl, use rt && rd for registers
        {
            return 0;
        }
    }  
    else if(funct == 8)     // jr only uses rs register
    {
        if(rt != 0 && rd != 0)
        {
            return 0;
        }       
        if(rs != 31)        // jr returns the last register ($ra) -> rs == 31 for jr
        {
            return 0;
        }
    }
    
    // Return 1, all variables are valid for R-Format Instructions
    return 1;
}
