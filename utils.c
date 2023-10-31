#include "archi.h"

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

void	printDebug(){
	for (uint8_t i = 0; i < 8; i++)
		printf("R%d: %X\n", i, registers[i]);
	printf("PC: %X\n", registers[PC]);
	printf("IR: %X\n", registers[IR]);
	printf("COND: %X\n", registers[COND]);
}