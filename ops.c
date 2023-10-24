#include "archi.h"
#include <stdlib.h>

extern uint16_t registers[];
extern uint16_t memory[];

void op_BR(){

}
// 15    12    9     6 5 4    3     0
//  |0001 | DS | SR1 | 0 | 00 | SR2 | >> DS = SR1 + SR2;
//  |0001 | DS | SR1 | 1 |   Imm    | >> DR = SR1 + Imm;
void op_ADD(){
    char isImmidiateMode, dist, src1, src2;

    isImmidiateMode = registers[IR] >> 5 & 0b1;
    dist = registers[IR] >> 9 & 0b111;
    src1 = registers[IR] >> 6 & 0b111;
    if (isImmidiateMode)
        registers[dist] = registers[src1] + SIGN_EXTAND(registers[IR] & 0x1f, 5);
    else
        registers[dist] = registers[src1] + registers[registers[IR] & 7];
    UpdateCondReg(&registers[dist]);
}

void op_LD(){

}

void op_ST(){

}

void op_JSR(){

}

void op_AND(){

}

void op_LDR(){

}   
           
void op_STR(){

}   
           
void op_RTI(){

}

void op_NOT(){

}

void op_LDI(){

}

void op_STI(){

}

void op_JMP(){

}

void op_RES(){

}

void op_LEA(){

}

void op_TRAP(){

}