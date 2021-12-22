#include "array.h"

#include "vram.h"
#include "neslib.h"

//#link "vram.c"
//#link "chr_matrix.s"

//#define USE_OPAQUE_CHAR 

#define CHR_MASK   (0x0F)
#define CHR_START  (0x60)
#define CHR_AMOUNT (0xFF - CHR_START)

static word addr;

static char x;
static char y;
static char r;

static char i;

static char start[32];
static char chars[32];

static char sprId;
static char tileY, pixelY;

static char density;
static signed char dir;

void putChar(char _i, char _x, char _y, char _c) {
  addr = NTADR(NAMETABLE_A, _x, _y);
  vram_buffer[VRB_TILES_MSB(_i) ] = MSB(addr);
  vram_buffer[VRB_TILES_LSB(_i) ] = LSB(addr);
  vram_buffer[VRB_TILES_DATA(_i)] = _c; 
}

// main function, run after console reset
void main(void) {  

  // Characters
  pal_col( 0, 0x0F);	// black
  pal_col( 1, 0x0F);	// black
  pal_col( 2, 0x2A);	// green
  pal_col( 3, 0x30);	// white  
  
  // Cursor
  pal_col(28, 0x0F);	// black
  pal_col(29, 0x0F);	// black
  pal_col(30, 0x30);	// white
  pal_col(31, 0x30);	// white
  
  // Set the VRAM buffer
  set_vram_update(vram_buffer);  
  
  // Clear the VRAM buffer
  vram_adr(NTADR_A(0, 0));
  vram_fill(NULL, 1024);  
  
  // Enable PPU rendering (turn on screen)
  ppu_on_all();  
  
  // Define the Y starting positions for each column
  for (i = 0; i < 32; ++i) {
    start[i] = rand8() % 30;
  }  
        
  // Set the code density
  density = 248;
  dir = -1; 

  // Enter the Matrix
  while (1) {
    
    // Make the density oscilate
    density += dir;
    if (density == 224 || density == 248) dir = -dir;
    
    // Don't ask me, it just works
    for (x = 0; x < 32; ++x) {      
      r = rand8();
      if (r < 192) continue;
      chars[x] = (r >= density);      
    }       
        
    // Put the characters on screen    
    for (x = 0; x < 32; ++x) {      
      // Set the random character in the buffer
      if (chars[x]) chars[x] = CHR_START + (rand8() % CHR_AMOUNT);
      
      // Calculate the Y tile and pixel positions
      tileY = (start[x] + y) % 30; pixelY = (tileY * 8);
      
      // Draw the character in white using a sprite
      sprId = oam_spr(x * 8, pixelY - 1, chars[x], 0x03, sprId);
      
      #ifdef USE_OPAQUE_CHAR      
      // Draw an opaque blank character in order to "erase" what's below
      sprId = oam_spr(x * 8, pixelY - 1, 0x0F, 0x02, sprId); // Optional    
      #endif
      
      // Draw the character in green using a background tile
      putChar(x, x, tileY, chars[x]);            
    }   
    
    // Clean-up
    vram_buffer[LAST_INDEX_OF(vram_buffer)] = NT_UPD_EOF;
    oam_hide_rest(sprId); sprId = 0;
    ppu_wait_nmi();    
    
    // Increase Y position and loop
    ++y;    
  };
}
