#include "array.h"
#include "vram.h"

byte vram_buffer[VRAM_BUFFER_SIZE] = {
    // Update Buffer Structure:
    // - - - - - - - - - - - - - - - - -
    // [  0] MSB
    // [  1] LSB
    // [  2] Number of tiles
    // [3:x] Tile data (read from map)
    // (...)
    // [ -1] End of Buffer (NT_UPD_EOF)
    // - - - - - - - - - - - - - - - - -
    // Tiles
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,  
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,
    MSB(NTADR_A(0, 0)), LSB(NTADR_A(0, 0)), 0,      
    NT_UPD_EOF
};
