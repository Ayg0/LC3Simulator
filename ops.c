#include "archi.h"

extern uint16_t registers[];
extern uint16_t memory[];

void    opBR(){
    //15     12       9                 0
    // | 0000 | N Z P |     PCoffset    |
    uint8_t Flags = (registers[IR] >> 9) & 0x7; // | N Z P |
    uint16_t pcOffset = registers[IR] & 0x1FF; 	// | PCoffset |

    if (registers[COND] & Flags)
        registers[PC] += signExtend(pcOffset, 9);
}

void    opADD(){
    //15     12    9     6   5    3     0
    // | 0001 | DR | SR1 | 0 | 00 | SR2 | // mode 0 DR = SR1 + SR2;
    // | 0001 | DR | SR1 | 1 |    Imm   | // mode 1 DR = SR1 + Imm;
    uint8_t dr, sr1;

	dr = (registers[IR] >> 9) & 0x7;
	sr1 = (registers[IR] >> 6) & 0x7;
	if ((registers[IR] >> 5) & 0x1)
		registers[dr] = registers[sr1] + signExtend(registers[IR] & 0x1f, 5);
	else
		registers[dr] = registers[sr1] + registers[registers[IR] & 0x7];
    updateCondReg(registers[dr]);
}

void    opAND(){
    //15     12    9     6   5    3     0
    // | 0101 | DR | SR1 | 0 | 00 | SR2 | // mode 0 DR = SR1 & SR2;
    // | 0101 | DR | SR1 | 1 |    Imm   | // mode 1 DR = SR1 & Imm;
    uint8_t dr, sr1;

	dr = (registers[IR] >> 9) & 0x7;
	sr1 = (registers[IR] >> 6) & 0x7;
	if ((registers[IR] >> 5) & 0x1)
		registers[dr] = registers[sr1] & signExtend(registers[IR] & 0x1f, 5);
	else
		registers[dr] = registers[sr1] & registers[registers[IR] & 0x7];
    updateCondReg(registers[dr]);
}

void    opJMP(){
    //15     12     9       6           0
    // | 1100 | 000 | BaseR |           | // PC = BaseR;
    uint8_t base;

    base = (registers[IR] >> 6) & 0x7;
    registers[PC] = registers[base];
}

void opJSR(){

    //15     12  11    9      6        0
    // | 0100 | 0 | 00 | BASE |        | // mode 0 R7 = PC, PC = BASE;
    // | 0100 | 1 |      PcOffset      | // mode 1 R7 = PC, PC += PcOffset;
    uint8_t mode;
    mode = (registers[IR] >> 11) & 0x1;
    registers[R7] = registers[PC];
    if (mode)
        registers[PC] += signExtend(registers[IR] & 0x7ff, 11);
    else
        registers[PC] = registers[(registers[IR] >> 6) & 0x7];
}

void opLD(){
    //15     12      9                   0
    // | 0010 |  DR  |     PcOffset      | // DR = mem[PC + PcOffset] ;
    uint8_t DR;

    DR = (registers[IR] >> 9) & 0x7;
    registers[DR] = *getMemory(registers[PC] + signExtend(registers[IR] & 0x1ff, 9));
    updateCondReg(registers[DR]); 
}

void opLDI(){
    //15     12      9                   0
    // | 1010 |  DR  |     PcOffset      | // DR = mem[mem[PC + PcOffset]] ;
    uint8_t DR;

    DR = (registers[IR] >> 9) & 0x7;
    registers[DR] = *getMemory(*getMemory(registers[PC] + signExtend(registers[IR] & 0x1ff, 9)));
    updateCondReg(registers[DR]); 
}

void opLDR(){
    //15     12    9       6            0
    // | 0110 | DR | BaseR |   Offset   | // DR = mem[BaseR + offset];
    uint8_t DR, BaseR;

	DR = (registers[IR] >> 9) & 0x7;
	BaseR = (registers[IR] >> 6) & 0x7;
    registers[DR] = *getMemory(registers[BaseR] + signExtend(registers[IR] & 0x3f, 6));
    updateCondReg(registers[DR]);
}

void    opLEA(){
    //15     12    9                    0
    // | 1110 |  DR  |     PcOffset     | DR = PC + PcOffset
    uint8_t DR;

	DR = (registers[IR] >> 9) & 0x7;
    registers[DR] = registers[PC] + signExtend(registers[IR] & 0x1ff, 9);
    updateCondReg(registers[DR]);
};

void    opNOT(){
    //15     12    9     6            0
    // | 0110 | DR | SRC |            | // DR = NOT(SRC);
    uint8_t DR, SRC;

	DR = (registers[IR] >> 9) & 0x7;
	SRC = (registers[IR] >> 6) & 0x7;
    registers[DR] = ~(registers[SRC]);
    updateCondReg(registers[DR]);
};
// NOT YET MADE
void    opRTI(){
    printf("opRTI Didn't make it yet !!\nSorry future self . . .\n");
    exit(7);
}

void    opST(){
    //15     12      9                   0
    // | 0011 |  SR  |     PcOffset      | // mem[PC + PcOffset] = SR ;
    uint8_t SR;

    SR = (registers[IR] >> 9) & 0x7;
    *getMemory(registers[PC] + signExtend(registers[IR] & 0x1ff, 9)) = registers[SR];
}

void    opSTI(){
    //15     12      9                   0
    // | 1011 |  SR  |     PcOffset      | // mem[mem[PC + PcOffset]] = SR;
    uint8_t SR;
    uint16_t pcOffset;

    SR = (registers[IR] >> 9) & 0x7;
    pcOffset = signExtend(registers[IR] & 0x1ff, 9);
    *getMemory(*getMemory(registers[PC] + pcOffset)) = registers[SR];
}

void    opSTR(){
    //15     12    9       6            0
    // | 0111 | SR | BaseR |   Offset   | // mem[BaseR + offset] = SR;
    uint8_t SR, BaseR;

	SR = (registers[IR] >> 9) & 0x7;
	BaseR = (registers[IR] >> 6) & 0x7;
    *getMemory(registers[BaseR] + signExtend(registers[IR] & 0x3f, 6)) = registers[SR];
}

void    opTRAP(){
    //15     12      8                  0
    // | 0111 |      |      TRAPVECT8   | // do that;
    registers[R7] = registers[PC];
    uint8_t trapVector = registers[IR] & 0xFF;
    switch (trapVector)
    {
    case 0x20:
        trapGetC();
        break;
    case 0x21:
        trapOut();
        break;
    case 0x22:
        trapPuts();
        break;
    case 0x23:
        trapIn();
        break;
    case 0x24:
        trapPutp();
        break;
    case 0x25:
        trapHalt();
    default:
        break;
    }
    
};

void    opTMP(){
    
};