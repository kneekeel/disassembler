/*
 * verifyMIPSInstruction
 *
 * This function verifies that the string provided to it as a paramater
 * contains 32 characters representing binary digits (characters '0' and
 * '1'), followed by a null byte.  If the string contains the wrong
 * number of characters or contains invalid charaters (not '0' or '1'),
 * then the function prints an error message to stderr giving the line
 * number and an appropriate error message.
 *
 *   int verifyMIPSInstruction (int lineNum, char * instruction);
 *
 *	    Pre-condition:  instruction is a null-terminated string
 *	    Post-condition: the characters in "instruction" have not
 *			    been modified
 *	    Returns: 1 if instr contained 32 characters representing binary
 *			    digits ('0' and '1') followed by a null byte
 *		     0 if instr has the wrong number of characters or
 *		            contains invalid characters
 *	    Output: Prints an error message to stderr if necessary
 *
 * Implementation:
 *	Describe interesting implementation details here, if any.
 *  Reads the line from either the file or the standard input, 
 *  and verifies if the line contains valid MIPS Instructions. 
 *  The line will only contain valid instructions if, there are 
 *  32 characters in the line and all of the characters are either
 *  1's or 0's. If either case is invalid, it will report it to the
 *  user. 
 *
 * Author: Nikhil Sodemba
 *
 * Creation Date:  January, 10th, 2020
 *
 */

#include "disassembler.h"

static const int INSTR_LENGTH = 32;

int verifyMIPSInstruction (int lineNum, char * instr)
  /*  returns 1 if instr contains INSTR_LENGTH characters representing binary
   *  digits ('0' and '1'); 0 otherwise
   */
{
    int   length;
    int k; 

    length = strlen(instr);
    if (length != INSTR_LENGTH)
    {
        printError ("\t Error: Line %d does not have %d characters.\n",
                    lineNum, INSTR_LENGTH);
        return 0;
    }else 
    {
        for(k = 0; k < INSTR_LENGTH; k++)
        {
            if(instr[k] != '0' && instr[k] != '1')
            {
                printError("\t Error: The current line: %d, does not have valid MIPS instructions, specificially at index: %d, that character being: %c.\n", 
                    lineNum, k, instr[k]);
                return 0;
            }
        }
        // printf("\t The line: %d, contains valid MIPS instructions.\n", lineNum);
        return 1;
    }
}
