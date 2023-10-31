#include "archi.h"

int	loadProgram(char *programLocation){
    uint16_t origin;

    fread(&origin, sizeof(uint16_t), 1, file); // read first 16 bits to know where to load the program
    origin = toLittleEnd(origin); // need to turn everything to little endian notation

    uint16_t maxRead = MEMORY_SIZE - origin; // get the max read size
    uint16_t* p = memory + origin;
    size_t ret = fread(p, sizeof(uint16_t), maxRead, file);

    while (ret-- > 0){ // turn everything into little endian
        *p = toLittleEnd(*p);
        ++p;
    }
}