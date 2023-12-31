# ifndef ARCHI_H
# define ARCHI_H
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>

// Memory
// address space: 216 locations (16-bit addresses)
// addressability: 16 bits
# define MEMORY_SIZE (1 << 16)

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
// memory mapped reg
enum
{
    MR_KBSR = 0xFE00, /* keyboard status */
    MR_KBDR = 0xFE02  /* keyboard data */
};

// ops:
void    opBR();
void    opADD();
void    opAND();
void    opJMP();
void    opJSR();
void    opTMP();
void    opLD();
void    opLDI();
void    opLDR();
void    opLEA();
void    opNOT();
void    opRTI();
void    opST();
void    opSTI();
void    opSTR();
void    opTRAP();
// traps:
void    trapGetC();
void    trapOut();
void    trapPuts();
void    trapIn();
void    trapPutp();
void    trapHalt();

void		printDebug();
void        updateCondReg(uint16_t reg);
uint8_t		loadProgram(char *programLocation);
uint16_t	toLittleEnd(uint16_t val);
uint16_t	signExtend(uint16_t val, uint8_t bits);
uint16_t    *getMemory(uint16_t address);
#endif