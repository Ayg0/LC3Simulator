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

uint8_t checkParams(int32_t ac, char **av, uint8_t *mode){
    if (ac < 2 || ((ac == 3) && strcmp(av[1], "-d"))){
        fprintf(stderr, "Bad params\nUsage: ./lc3Sim [-d] objFile\n");
        return 1;
    }
    if (!strcmp(av[1], "-d"))
        *mode = 1;
    return 0;
}

int main(int32_t ac, char **av){
    uint8_t op, c, mode;

    enableRawMode();
	if (checkParams(ac, av, &mode))
        return 1;
    if (loadProgram(av[1 + mode]))
        return 2;
    // initialization
    registers[PC] = 0x3000;
    while(registers[PC] < 0xFFFF){
        // fetch
        registers[IR] = read_memory(registers[PC]);
        registers[PC] += 1;
        // decode
        op = registers[IR] >> 12;
        // execution
        ops[op]();
        if (mode){
            printDebug();
            read(1, &c, 1);
        }
    }
    return 0;
}
