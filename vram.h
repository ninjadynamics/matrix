#ifndef _VRAM_H
#define _VRAM_H

#include "neslib.h"

#define BUFFER_SIZE      1

#define _ZERO            0
#define _COLUMNS         32

#define _VRB_TYPE_SINGLE 2
#define _VRB_TYPE_ARRAY  3
#define _VRB_TYPE_END    1

#define _SIZE_VRAM_BUFFER_COL    (_VRB_TYPE_SINGLE + BUFFER_SIZE)
#define _SIZE_VRAM_BUFFER_END    (_VRB_TYPE_END)

#define _SIZE_VRAM_BUFFER        (_COLUMNS * _SIZE_VRAM_BUFFER_COL)

#define VRAM_BUFFER_SIZE (   \
  _SIZE_VRAM_BUFFER +        \
  _SIZE_VRAM_BUFFER_END      \
)

// Tiles
#define VRB_TILES_MSB(_COL)      (_COL * _SIZE_VRAM_BUFFER_COL          )
#define VRB_TILES_LSB(_COL)      (VRB_TILES_MSB(_COL) + 1               )
#define VRB_TILES_DATA(_COL)     (VRB_TILES_MSB(_COL) + _VRB_TYPE_SINGLE)

// Swap bytes
#define SWAP_BYTES(value_16bit) ( \
  ((value_16bit << 8) & 0xff00) | ((value_16bit >> 8) & 0x00ff) \
)

// VRAM Address
#define NTADR(A, X, Y) ( \
  A | (((Y) << 5) | (X)) \
)

extern byte vram_buffer[VRAM_BUFFER_SIZE];

#endif // vram.h
