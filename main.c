#include "archi.h"

uint16_t memory[MEMORY_SIZE];
uint16_t registers[R_COUNT];
uint8_t  HLT_FLAG = 1;
struct termios origTermios;

void (*ops[])() = {
    opBR,  opADD, opLD, opST, // 0000 => 0011 // 0  => 3
    opJSR, opAND, opLDR, opSTR, // 0100 => 0111 // 4  => 7
    opRTI, opNOT, opLDI, opSTI, // 1000 => 1011 // 8  => 11
    opJMP, opTMP, opLEA, opTRAP, // 1100 => 1111 // 12 => 15
    };

uint16_t    read_memory(uint16_t address){
    return memory[address];
}
void disableRawMode(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &origTermios);
  atexit(disableRawMode);
  struct termios raw = origTermios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int ac, char **av){
    int op, c;

	if (ac != 2)
		return 1;
    enableRawMode();
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
        // read(1, &c,1);
        // printDebug();
        ops[op]();
    }
}
