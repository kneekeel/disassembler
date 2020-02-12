/*
 * Main file for Disassembler project. 
 * 
 * Currently, includes nothing -- expected changes to be made throughout
 *      the progress of the project. 
 * 
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
        printDebug ("\t Length: %d\n", length);

        int resultMIPS = verifyMIPSInstruction(lineNum, buffer);
        printf("\t The result of the MIPS verification was: ");
        if (resultMIPS == 0)
        {
            printf("Not valid.\n");
        }else
        {
            /* Once the MIPS Instructions receive a vaild MIPS instruction, the program will
             * calculate the decimal number based on the instructions and the two parameters
             * for the bounds in binToDec function call. Currently, the program will only test
             * one Decimal calculation, although it could easily be structured to return multiple
             * conversions, even allowing the user to input the numbers for the start and end 
             * positions. 
             */
            printf("Valid! Calculating Decimal number for random start and end positions...\n");
            int result = binToDec(buffer, 2,8);
            /* Test cases for the binToDec function, testing for bounds on the position. */
            /* int result = binToDec(buffer, -1, 18); */
            /* int result = binToDec(buffer, 3, 33); */
            if (result == -1)
            {
                printf("\t Invalid position(s), when calculating corresponding decimal number.\n");
            }
            else 
            {
                if (result > 127)
                {
                    printf("\t The decimal value cannot be represented in ascii conversion.\n");
                    printf("\t The decimal value is: %d\n", result);
                }
                printf("\t The decimal value is: %d\n", result);
                printf("\t The character for the decimal value is: %c\n", result);
            }
        }
    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
