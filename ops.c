#include "archi.h"

extern uint16_t registers[];
extern uint16_t memory[];

void    opBr(){
    //15     12       9                 0
    // | 0000 | N Z P |     PCoffset    |
    uint8_t Flags = (registers[IR] >> 9) & 0x7; // | N Z P |
    uint16_t pcOffset = registers[IR] & 0x1FF; 	// | PCoffset |

    if (registers[COND] & Flags)
        registers[PC] += signExtend(pcOffset, 9);
}

void    opAdd(){
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

void    opAnd(){
    //15     12    9     6   5    3     0
    // | 0101 | DR | SR1 | 0 | 00 | SR2 | // mode 0 DR = SR1 & SR2;
    // | 0101 | DR | SR1 | 1 |    Imm   | // mode 1 DR = SR1 & Imm;
    uint8_t dr, sr1;

	dr = (registers[IR] >> 9) & 0x7;
	sr1 = (registers[IR] >> 6) & 0x7;
	if ((registers[IR] >> 5) & 0x1)
		registers[dr] = registers[sr1] + signExtend(registers[IR] & 0x1f, 5);
	else
		registers[dr] = registers[sr1] + registers[registers[IR] & 0x7];
    updateCondReg(registers[dr]);
}
void    opTMP(){
    
};