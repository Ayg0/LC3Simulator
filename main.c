#include "archi.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t memory[MEMORY_SIZE];
uint16_t registers[R_COUNT];
uint8_t  HLT_FLAG = 1;
void (*ops[])() = {
    opBr, opAdd,
    };

void    UpdateCondReg(uint16_t *reg){
    if (*reg  == 0)
        registers[COND] = FL_ZER;
    else if (*reg >> 15)
        registers[COND] = FL_NEG;
    else
        registers[COND] = FL_POS;
}

uint16_t    read_memory(uint16_t address){
    return memory[address];
}
int main(int ac, char **av){
    int op;
	if (ac != 2)
		return 1;
	loadProgram(av[1]);
    // initialization
    registers[PC] = 0x3000;
    while(registers[PC] < 0xFFFF){
        // fetch
        registers[IR] = read_memory(registers[PC]);
        // decode
        op = registers[IR] >> 12;
        // execution
		if (op > 1){
			printDebug();
			while(1);
		}
        ops[op]();
        while(HLT_FLAG);
    }
}
