#include "archi.h"

extern uint16_t registers[];
extern uint16_t memory[];

// extand the sign value if the bit is 1; else don't
uint16_t signExtend(uint16_t val, uint8_t bits){
	if (val >> (bits - 1) & 1)
		val |= 0xFFFF << bits;
	return val;
}
// turn to little endian: 
uint16_t toLittleEnd(uint16_t val){
    return (val << 8) | (val >> 8);
}
// update the condition register
void    updateCondReg(uint16_t reg){
    if (reg  == 0)
        registers[COND] = FL_ZER;
    else if (reg >> 15)
        registers[COND] = FL_NEG;
    else
        registers[COND] = FL_POS;
}

uint16_t *getMemory(uint16_t address){
	return (&memory[address]);
}

void	printDebug(){
	printf("\n------------- Debug INFO --------------\n");
	for (uint8_t i = 0; i < 8; i++)
		printf("R%d:   0x%X\n", i, registers[i]);
	printf("PC:   0x%X\n", registers[PC]);
	printf("IR:   0x%X\n", registers[IR]);
	printf("COND: 0x%X\n", registers[COND]);
	printf("-------------    END    --------------\n");
}