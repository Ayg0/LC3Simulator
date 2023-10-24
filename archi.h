# ifndef ARCHI_H
# define ARCHI_H
#include <stdio.h>
#include <stdint.h>

// Memory
// address space: 216 locations (16-bit addresses)
// addressability: 16 bits
# define MEMORY_SIZE (1 << 16)
// extand the sign value if the bit is 1; else don't
# define SIGN_EXTAND(val, bits)((val >> (bits - 1)) & 1 ? (val | 0xFFFF << bits) : val)
// Registers
// eight general-purpose registers: R0 - R7
// PC (program counter), condition codes
// each 16 bits wide
enum
{
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    PC,     /* program counter */
    IR,     /* Instruction Registers */
    COND,   /* program status register */
    R_COUNT
};


/*Source and destination operands are registers
These instructions do not reference memory.
ADD and AND can use “immediate” mode,
where one operand is hard-wired into the instruction*/
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};
// conditions
enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZER = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

// ops:
void op_BR();
void op_ADD();
void op_LD();
void op_ST();
void op_JSR();
void op_AND();
void op_LDR();
void op_STR();
void op_RTI();
void op_NOT();
void op_LDI();
void op_STI();
void op_JMP();
void op_RES();
void op_LEA();
void op_TRAP();

void    UpdateCondReg(uint16_t *reg);

#endif