#include "archi.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint16_t memory[MEMORY_SIZE];
uint16_t registers[R_COUNT];
uint8_t  HLT_FLAG = 1;
void (*ops[])() = {
    opBR,  opADD, opLD, opTMP, // 0000 => 0011 // 0  => 3
    opJSR, opAND, opLDR, opTMP, // 0100 => 0111 // 4  => 7
    opTMP, opTMP, opLDI, opTMP, // 1000 => 1011 // 8  => 11
    opJMP, opTMP, opTMP, opTMP, // 1100 => 1111 // 12 => 15
    };

uint16_t    read_memory(uint16_t address){
    return memory[address];
}
int main(int ac, char **av){
    int op;

    int c;
	if (ac != 2)
		return 1;
	loadProgram(av[1]);
    // initialization
    registers[PC] = 0x3000;
    while(registers[PC] < 0xFFFF){
        // fetch
        registers[IR] = read_memory(registers[PC]);
        registers[PC] += 1;
        // decode
        op = registers[IR] >> 12;
        // execution
        if (op == 0b1111){
            printDebug();
            return (printf("PROGRAMM HALTED\n"));
        }
        ops[op]();
    }
}
