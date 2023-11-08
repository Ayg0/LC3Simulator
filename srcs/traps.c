#include "archi.h"

extern uint16_t registers[];
extern uint16_t memory[];

void    trapGetC(){
    registers[R0] = getchar();
    updateCondReg(R0);
}

void    trapOut(){
    uint8_t c = 0;

    c = registers[R0];
    write(1, &c, 1);
    fflush(stdout);
}

void    trapPuts(){
    uint16_t index;

    index = registers[R0];
    while (index < MEMORY_SIZE && memory[index]){
        if (memory[index] == '\n')
            write(1, "\r\n", 2);
        else
            write(1, &memory[index], 1);
        index++;
    }
    fflush(stdout);
}

void    trapIn(){
    printf("Input>> ");
    trapGetC();
    trapPuts();
}

void    trapPutp(){
    uint16_t index;
    uint8_t first, second;

    index = registers[R0];
    while (index < MEMORY_SIZE && memory[index]){
        first = memory[index] & 0xff;
        write(1, &first, 1);
        if ((second = (memory[index] >> 8)))
            write(1, &second, 1);
    }
    fflush(stdout);
}

void    trapHalt(){
    printf("\n. . . Program Halted . . .\n");
    while (1);
}
