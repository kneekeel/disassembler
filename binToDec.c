/*
 * binToDec
 *
 * This function converts the binary digits from string[begin] to
 * string[end] to a decimal integer.
 *
 * int binToDec(char string[], int begin, int end)
 *   Pre-condition:  begin and end are valid indices in array string;
 *   		     every character from string[begin] to string[end]
 *		     (including those two) has a character value '0' or '1'
 *   Returns: the decimal equivalent of the binary number represented by
 *	      the characters in string[begin] - string[end].
 *            (If begin > end, this function arbitrarily returns 0.)
 *
 * For example, assume A is a character array that contains the
 *    following characters:
 *            '1'  '0'  '1'  '1'  '0'  '1'  '0'  '0'  '1'
 *    The call binToDec(A, 2, 5) converts the binary number 1101
 *    (represented by the substring A[2] - A[5]) to the decimal integer
 *    13 and returns it.
 * 
 * Note: The decimal value returned may appear to be negative if the
 * string being converted is long enough (end - begin + 1 == 32)
 * and if the first character is '1'.
 *
 * Implementation:
 *	Describe interesting implementation details here, if any.
 *  The binToDec function checks to see if the bounds of the beginning
 * 	and ending positions are valid. The algorithm figures out the number 
 * 	of potential characters that would be involved in the program, that value
 * 	is stored in power. The algorithm will calculate each index of the string[]
 * 	array inside the bounds, verify whether or not the indiviudal character at that
 * 	position is a 1, representing a '2'. The corresponding index will be 2 to the power
 * 	of whatever the power is equal to at that iteration. The iteration will run through 
 * 	left to right, i.e. 1 0 1 0 1 -> 2^4 + 2^2 + 2^0 = 21. Each iteration will lower the power 
 * 	and increment the currentIndex, until power is lower than 0, meaning that the 
 * 	calculations should be completed. 
 *
 * Author: Nikhil Sodemba
 *
 * Creation Date: January, 10th, 2020
 *
 */

#include <math.h>
#include <stdio.h>
#include "disassembler.h"

int binToDec(char string[], int begin, int end)
{
	int powOfTwo = 1;
	int k;
	int decimal = 0 ;
	if(end > 32 || begin < 0)
	{
		printError("The position(s) for the function is not in the bounds.\n");
		return -1;
	}
	else
	{
		for(k = end; k >= begin; k--)
		{
			if(string[k] == '1')
			{
				decimal += powOfTwo;
			}
			powOfTwo *= 2; 
		}
		return decimal;
	}
}
