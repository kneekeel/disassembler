# Disassembler Programming Project - User Handbook

## Created by: Nikhil Sodemba

Welcome to the Disassembler Program. This program is intended to parse valid MIPS Instruction into its corresponding format type and validate whether or not, that instruction is correct.

Each MIPS Instruction is 32-bits long, and will be parsed into one of the three format types: R-Format, I-Format, and J-Format. The opcode (first 6 bits) of the MIPS Instruction showcases which format type the Instruction belongs to, if the opcode is invalid, the proper Error Handling logic will print the appropriate error to stderr.

The Disassembler program is important, as (most) computers and technology use binary notation in order to function, i.e. Machine Code. It is important to analyze how Machine Code is trasmitted into Assembly Language (low-level language).

**Important Notes:**

- The program will take an input (.txt) file, where each line of the file is some machine code instuction (of length 32-bits). Each line of machine code has to be of 32-bits, each character being either 0 or 1. If either of these cases fails, then the program will execute an error.
- Once the MIPS instruction has been validated, the program will determine which format-type the instruction belongs to, by evaluating the opcode.
- Each format type has its own validation, where errors can occur depending on the instruction. If there are no errors, the program will print the corresponding instruction into its low-level language (assembly language) to stdout.

**How to use the program:**

- Open up your terminal, with the correct path to the programs directory. Input "make disassembler" into the command line. This will create an output file, with which you can use the program.

- The input test file, "userTest.txt" is provided alongside the program. You can choose to use this file to experiment with the program, although there are other files which will work as well. In order to use the program, input "./disassembler userTest.txt 1", this will execute the program and you should see a lot of statements in your terminal. The "1" following the test file is used in order to turn debug mode on, you can input "0" instead of the "1", in order to just see the instruction and any errors. I suggest executing the program with "1".

**Sample Input/Output ("userText.txt"):**

The userText.txt file contains 12 lines of MIPS Instruction Machine Code. The first line will be a MIPS Instruction which is over 32-bits. The second line will be a MIPS Instruction which does not consist of solely 0's and 1's. The third line will be a MIPS Instruction which has an invalid opcode. The remaining 9 lines will be: 3 sets of 3 MIPS Instructions: each of differing format types (R-Format, I-Format, and J-Format), two lines are valid MIPS Instructions and one MIPS Instruction with invalid instructions in their respective formats.

    userText.txt Input File

    Input: 

    010101010101010101010101010101011
    01010101010234010101010101010101
    11111001010101010101010101010101
    00000001000010010101000000100000
    00000000100001010011000000100010
    00000000100000010001000011001000
    00010001000010010000000010001000
    10101100100001000000100010000000
    00111100010001000000100000000000
    00001000000000001001011000000100
    00001101000001000000000000100100
    11110100100001000000000100001000

    Output:

    Line 1: 010101010101010101010101010101011
        Length: 33
        Error: Line 1 does not have 32 characters.
        Error: Invalid MIPS Instruction at line: 1.

    Line 2: 01010101010234010101010101010101
        Length: 32
        Error: The current line: 2, does not have valid MIPS instructions, specificially at index: 11, that character being: 2.
        Error: Invalid MIPS Instruction at line: 2.

    Line 3: 11111001010101010101010101010101
        Length: 32
        The opcode is: 62
        Opcode Error: Invalid opcode instruction, at line: 3.

    Line 4: 00000001000010010101000000100000
        Length: 32
        The opcode is: 0
        R-Format.
        add  $t2, $t0, $t1
        Valid R-Format Instruction!

    Line 5: 00000000100001010011000000100010
        Length: 32
        The opcode is: 0
        R-Format.
        sub  $a2, $a0, $a1
        Valid R-Format Instruction!

    Line 6: 00000000100000010001000011001000
        Length: 32
        The opcode is: 0
        R-Format.
        Error: Invalid R-Format Instruction, in variable(s) at line: 6.

    Line 7: 00010001000010010000000010001000
        Length: 32
        The opcode is: 4
        I-Format.
        beq  $t0, $t1, 136
        Valid I-Format Instruction.

    Line 8: 10101100100001000000100010000000
        Length: 32
        The opcode is: 43
        I-Format.
        sw  $a0, 2176($a0)
        Valid I-Format Instruction.

    Line 9: 00111100010001000000100000000000
        Length: 32
        The opcode is: 15
        I-Format.
        Error: Invalid I-Format Instruction, in variable(s) at line: 9.

    Line 10: 00001000000000001001011000000100
        Length: 32
        The opcode is: 2
        J-Format.
        j  38404
        Valid J-Format Instruction.

    Line 11: 00001101000001000000000000100100
        Length: 32
        The opcode is: 3
        J-Format.
        jal  17039396
        Valid J-Format Instruction.

    Line 12: 11110100100001000000000100001000
        Length: 32
        The opcode is: 61
        Opcode Error: Invalid opcode instruction, at line: 12.

Alternatively, you can see the output of each input file in the directory in the outputAllFile.txt file. Feel free to experiment with new files of your own, or to edit any existing file and testing it.
