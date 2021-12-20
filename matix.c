
#include "array.h"

#include "vram.h"
#include "neslib.h"

//#link "vram.c"
//#link "chr_generic.s"

static word addr;
static char f = 0;


// main function, run after console reset
void main(void) {

  // set palette colors
  pal_col(0,0x0F);	// black
  pal_col(1,0x0A);	// green
  pal_col(2,0x30);	// white
  pal_col(3,0xA0);	// lime

  
  // Set the VRAM buffer
  set_vram_update(vram_buffer);  
  
  vram_adr(NTADR_A(0, 0));
  vram_fill(NULL, 1024);  
  
  // enable PPU rendering (turn on screen)
  ppu_on_all();  
    
  // infinite loop
  while (1) {

    	addr = NTADR(NAMETABLE_A, 3, f  % 30);
        vram_buffer[VRB_TILES_MSB(0) ] = MSB(addr);
        vram_buffer[VRB_TILES_LSB(0) ] = LSB(addr);
    	vram_buffer[VRB_TILES_DATA(0)] = (0x41 + (f++ % 22));    

      	addr = NTADR(NAMETABLE_A, 6, (f + 6) % 30);
        vram_buffer[VRB_TILES_MSB(1) ] = MSB(addr);
        vram_buffer[VRB_TILES_LSB(1) ] = LSB(addr);
    	vram_buffer[VRB_TILES_DATA(1)] = (0x41 + (50 - f % 22));    

    
    
    	vram_buffer[LAST_INDEX_OF(vram_buffer)] = NT_UPD_EOF;
  	ppu_wait_nmi();
  };
}
