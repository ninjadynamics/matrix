#include "array.h"

#include "vram.h"
#include "neslib.h"

//#link "vram.c"
//#link "chr_matrix.s"

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

  // set palette colors
  pal_col(0, 0x0F);	// black
  pal_col(1, 0x0F);	// black
  pal_col(2, 0x2A);	// green
  pal_col(3, 0x30);	// white  
  
  pal_col(28, 0x0F);	// black
  pal_col(29, 0x0F);	// black
  pal_col(30, 0x2A);	// character
  pal_col(31, 0x30);	// cursor

  
  // Set the VRAM buffer
  set_vram_update(vram_buffer);  
  
  vram_adr(NTADR_A(0, 0));
  vram_fill(NULL, 1024);  
  
  // enable PPU rendering (turn on screen)
  ppu_on_all();  
  
  for (i = 0; i < 32; ++i) {
    start[i] = rand8() % 30;
  }  
        
  density = 248;
  dir = -1; 

  while (1) {   
    
    density += dir;
    if (density == 224 || density == 248) dir = -dir;
    
    for (x = 0; x < 32; ++x) {      
      r = rand8();
      if (r < 192) continue;
      r < density ? (chars[x] = 0): chars[x] = rand8() % 0x70;
    }       
        
    // Green
    for (x = 0; x < 32; ++x) {
      chars[x] = !chars[x] ? 0 : (rand8() % 0x70);
      tileY = (start[x] + y) % 30; pixelY = (tileY * 8);
      sprId = oam_spr(x * 8, pixelY - 1, 0x70 + chars[x], 0x03, sprId);
      //sprId = oam_spr(x * 8, pixelY - 1, 0xFF, 0x02, sprId);      
      putChar(x, x, tileY, chars[x]);      
      
    }   
    vram_buffer[LAST_INDEX_OF(vram_buffer)] = NT_UPD_EOF;
    ppu_wait_nmi();
    oam_hide_rest(sprId);    
    sprId = 0;
    ++y;    
  };
}
