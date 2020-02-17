/*
 * Main file for Disassembler project. 
 * 
 * This program is the main file for the disassemlber program. 
 * The program will take in a file, or read in lines from command line if there is no file
 * in the input. User can specify whether to turn debug mode on/off using 1 || 0, in the 
 * command line.
 * The file(s) intended for this program are machine code, where each MIPS Instruction is 32-bits long, 
 * each line of instruction should consist of 0's and 1's, if the instruction doesn't satisfy both 
 * condiditions, the program will execute the proper error to stderr. 
 * The program will validate each MIPS Instructions' opcode and then determine which format type the instruction 
 * belongs to: R-Format, I-Format, and J-Format. The formatType(...) function will determine the 
 * format type for the instruction, the logic is stated in the function declaration and body. 
 * Once, the program determines which format type the instruction belongs to, it will call the 
 * respective format type helper function to determine the validity of the instruction, using one
 * of the helper functions: rFormat(...), iFormat(...), jFormat(...).
 * Each function declaration (rFormat.c, iFormat.c, jFormat.c) provides details to the function(s).
 * Once, a valid MIPS Instruction is verified, the program will print out the resulting instruction 
 * to stdout. Turn off Debugging mode, to view a concise output of the program.
 * 
 * Author: Nikhil Sodemba
 * 
 * Creation Date: Feb, 12th, 2020
 *  
 */

#include "disassembler.h"

int main (int argc, char *argv[])
{
    FILE * fptr;               /* file pointer */
    char   buffer[BUFSIZ];     /* place to store line that is read in */
    int    length;             /* length of line read in */
    int    lineNum = 0;        /* keep track of input line numbers */

    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }
    /* Can turn debugging on or off here (debug_on() or debug_off())
     * if not specified on the command line.
     */
    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain an ASCII version of a valid MIPS machine
     * language instruction, represented as 32 character '0's and '1's
     * followed by a newline, rather an actual 32-bit binary MIPS
     * machine language instruction.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        lineNum++;

        /* If the last character in the string is a newline, "remove" it
         * by replacing it with a null byte.
         */
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[--length] = '\0';  
        if (buffer[length - 1] == '\r')
            buffer[--length] = '\0';    
        printf ("\nLine %d: %s\n", lineNum, buffer);
        printDebug ("\tLength: %d\n", length);

        // Verify whether or not, the current line contains valid MIPS Instruction
        int MIPSresult = verifyMIPSInstruction(lineNum, buffer);
        if (MIPSresult == 0)    // Invalid MIPS Instruction
        {
            printError("\tError: Invalid MIPS Instruction at line: %d.\n", lineNum);
        }
        else    // Valid MIPS Instruction
        {
            int formatResult = formatType(buffer);
            // R-Format
            if(formatResult == 0)   // Valid R-Format Opcode
            {
                printDebug("\tR-Format.\n");
                char * invalid = "Invalid";   
                char * result;
                result = rFormat(buffer);
                
                // Handle error response, when R-Format variables are invalid
                if(strcmp(invalid, result) == SAME)     // Invalid R-Format Instruction
                {
                    printError("\tError: Invalid R-Format Instruction, in variable(s) at line: %d.\n", lineNum);
                }
                else    // Valid R-Format Instruction, print statement in rFormat.c for instruction
                {
                    printDebug("\tValid R-Format Instruction!\n");
                }
            }
            // I-Format
            else if(formatResult == 1) 
            {
                printDebug("\tI-Format.\n");
                char * invalid = "Invalid";
                char * result;
                result = iFormat(buffer);

                // Handle error response, when I-Format variables are invalid
                if(strcmp(invalid, result) == SAME)     // Invalid I-Format Instruction 
                {
                    printError("\tError: Invalid I-Format Instruction, in variable(s) at line: %d.\n", lineNum);
                }
                else    // Valid I-Format Instruction, print statement in iFormat.c for instruction
                {
                    printDebug("\tValid I-Format Instruction.\n");
                }
                
            }
            // J-Format
            else if(formatResult == 2)
            {
                printDebug("\tJ-Format.\n");
                char * valid = "Valid";
                char * result;
                result = jFormat(buffer);

                // Handle response from J-Format, there should be no error, but I have provided an error
                // handler just in case something were to go wrong.
                if(strcmp(valid, result) == SAME)   // jFormat.c will print Instruction to stdout
                {
                    printDebug("\tValid J-Format Instruction.\n");
                }
                else
                {
                    printError("\tError: Invalid J-Format Instruction, at line: %d.\n", lineNum);
                } 
            }
            // Invalid opcode 
            else if(formatResult == -1)
            {
                printError("\tOpcode Error: Invalid opcode instruction, at line: %d.\n", lineNum);
            }
        }
    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}


/**
 * This helper function will determine the opcode (first 6 bits) for 
 * the instruction. Returns one of the format types: R-Format, I-Format, or J-Format.
 * 
 * Takes singular MIPS Instruction as argument in parameter. 
 * 
 * Returns 0 for R-format, 1 for I-Format and 2 for J-Format, 
 * returns -1 if the opcode is invalid and print appropiate error to stderr.
 * 
 */
int formatType(char string[])
{
    // All I-Format opcode instructions
    int iFormatOptions[] = {4,5,8,9,10,11,12,13,15,35,43};
    int k; // Increment value for looping through iFormatOptions array

    // Determines the opcode value, using the binToDec function for the first 6-bits.
    int opcode = binToDec(string,0,5);
    printDebug("\tThe opcode is: %d\n", opcode);
    // R-Format Instructions - opcode = 0
    if (opcode == 0)
    {
        return 0;
    }
    // J-Format Instructions - opcode = 2 || 3
    else if(opcode == 2 || opcode == 3)
    {
        return 2;
    }
    // I-Format if otherwise, or possible error if opcode not valid I-Format option. 
    else
    {
        for(k = 0; k < 11; k++)
        {
            // Valid I-Format Instruction
            if(iFormatOptions[k]==opcode)
            {
                return 1;
            }
        }
    }
    return -1;
}
