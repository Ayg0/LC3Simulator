#include "archi.h"
#include <stdint.h>
#include <stdio.h>

uint16_t memory[MEMORY_SIZE];
uint16_t registers[R_COUNT];
uint8_t  HLT_FLAG = 1;
void (*ops[])() = {
    op_BR,op_ADD,op_LD,op_ST,op_JSR,op_AND,
    op_LDR,op_STR,op_RTI,op_NOT,op_LDI,
    op_STI,op_JMP,op_RES,op_LEA,op_TRAP};

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
int main(){
    // test ADD
// // 15    12    9     6 5 4    3     0
// //  |0001 | DS | SR1 | 0 | 00 | SR2 | >> DS = SR1 + SR2;
// //  |0001 | DS | SR1 | 1 |   Imm    | >> DR = SR1 + Imm;
    memory[0x3000] = 0b0001001001000010;
    registers[R1] = 0;
    registers[R2] = -5;
    int op;
    // initialization
    registers[PC] = 0x3000;
    while(registers[PC] < 0xFFFF){
        // fetch
        registers[IR] = read_memory(registers[PC]);
        // decode
        op = registers[IR] >> 12;
        // execution
        ops[op]();
        // if (registers[COND] == FL_POS)
        //     printf("POS\n");
        // else if (registers[COND] == FL_ZER)
        //     printf("ZERO\n");
        // else if (registers[COND] == FL_NEG)
        //     printf("NEG\n");
        while(HLT_FLAG);
    }
}
