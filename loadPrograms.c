#include "archi.h"

extern uint16_t memory[];

uint8_t	loadProgram(char *programLocation){
    uint16_t	origin, maxRead, *ptr;
	size_t		ret;
	FILE		*file;

	file = fopen(programLocation, "rb");
    if (!file)
		return 0;
    fread(&origin, sizeof(uint16_t), 1, file); // read first 16 bits to know where to load the program
    origin = toLittleEnd(origin); // need to turn everything to little endian notation

    maxRead = MEMORY_SIZE - origin; // get the max read size
    ptr = memory + origin;
    ret = fread(ptr, sizeof(uint16_t), maxRead, file);

    while (ret-- > 0){ // turn everything into little endian
        *ptr = toLittleEnd(*ptr);
        ptr++;
    }
    fclose(file);
	return 0;
}