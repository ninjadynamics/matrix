#include "array.h"

#include "vram.h"
#include "neslib.h"

//#link "vram.c"
//#link "chr_matrix.s"

static word addr;
static char col;
static char x;
static char y;
static char c;
static char r;

static char i;

static char len[32];
static char start[32];
static char previous[32];



static void putChar(char _i, char _x, char _y, char _c) {
  addr = NTADR(NAMETABLE_A, _x, _y);
  vram_buffer[VRB_TILES_MSB(_i) ] = MSB(addr);
  vram_buffer[VRB_TILES_LSB(_i) ] = LSB(addr);
  vram_buffer[VRB_TILES_DATA(_i)] = _c; 
}

// main function, run after console reset
void main(void) {  

  // set palette colors
  pal_col(0,0x0F);	// black
  pal_col(1,0x0F);	// shadow
  pal_col(2,0x2A);	// character
  pal_col(3,0x30);	// cursor
  
  // Set the VRAM buffer
  set_vram_update(vram_buffer);  
  
  vram_adr(NTADR_A(0, 0));
  vram_fill(NULL, 1024);  
  
  // enable PPU rendering (turn on screen)
  ppu_on_all();  
  
  for (i = 0; i < 32; ++i) {
    start[i] = rand8() % 30;
  }
  
  for (i = 0; i < 32; ++i) {
    len[i] = 2 + rand8() % 8;
  }
        
  // infinite loop
  while (1) {   
    
    // Cursor
    for (col = 0; col < 32; ++col) {
      x = col;
      r = rand8();
      if (r < 192) continue;
      if (r < 224) {
        c = 0;
        //start[col] = rand8() % 30;
        //len[col] = 2 + rand8() % 8;
      }
      else {
        c = (rand8() % 0x70);
      }      
      
      putChar(col, x, (start[col] + y) % 30, 0x70 + c);      
      previous[col] = c;
    }       
    vram_buffer[LAST_INDEX_OF(vram_buffer)] = NT_UPD_EOF;
    ppu_wait_nmi();
    
    
    // Character
    for (col = 0; col < 32; ++col) {
      x = col;
      putChar(col, x, (start[col] + y) % 30, !previous[col] ? 0 : (rand8() % 0x70));      
    }    
    vram_buffer[LAST_INDEX_OF(vram_buffer)] = NT_UPD_EOF;
    ppu_wait_nmi();    
    
    ++y;    
  };
}
