#include <gb.h>


/* Gameboy Color palette 0 */
#define bkgCGBPal0c0 RGB_WHITE
#define bkgCGBPal0c1 RGB_CYAN
#define bkgCGBPal0c2 RGB_RED
#define bkgCGBPal0c3 RGB_BLACK

/* Gameboy Color palette 1 */
#define bkgCGBPal1c0 RGB_WHITE
#define bkgCGBPal1c1 RGB_WHITE
#define bkgCGBPal1c2 RGB_BLUE
#define bkgCGBPal1c3 RGB_BLACK

/* Gameboy Color palette 2 */
#define bkgCGBPal2c0 RGB_WHITE
#define bkgCGBPal2c1 RGB_LIGHTGRAY
#define bkgCGBPal2c2 RGB_GREEN
#define bkgCGBPal2c3 RGB_BLACK

/* Gameboy Color palette 3 */
#define bkgCGBPal3c0 RGB_WHITE
#define bkgCGBPal3c1 RGB_YELLOW
#define bkgCGBPal3c2 RGB_BROWN
#define bkgCGBPal3c3 RGB_BLACK

/* Gameboy Color palette 4 */
#define bkgCGBPal4c0 RGB_BLACK
#define bkgCGBPal4c1 RGB_WHITE-RGB_CYAN
#define bkgCGBPal4c2 RGB_WHITE-RGB_RED
#define bkgCGBPal4c3 RGB_WHITE

/* Gameboy Color palette 5 */
#define bkgCGBPal5c0 RGB_BLACK
#define bkgCGBPal5c1 RGB_BLACK
#define bkgCGBPal5c2 RGB_WHITE-RGB_BLUE
#define bkgCGBPal5c3 RGB_WHITE

/* Gameboy Color palette 6 */
#define bkgCGBPal6c0 RGB_BLACK
#define bkgCGBPal6c1 RGB_BLACK
#define bkgCGBPal6c2 RGB_WHITE-RGB_GREEN
#define bkgCGBPal6c3 RGB_WHITE

/* Gameboy Color palette 7 */
#define bkgCGBPal7c0 RGB_BLACK
#define bkgCGBPal7c1 RGB_WHITE-RGB_YELLOW
#define bkgCGBPal7c2 RGB_WHITE-RGB_BROWN
#define bkgCGBPal7c3 RGB_WHITE


/* Super Gameboy palette 0 */
#define bkgSGBPal0c0 0
#define bkgSGBPal0c1 0
#define bkgSGBPal0c2 0
#define bkgSGBPal0c3 0

/* Super Gameboy palette 1 */
#define bkgSGBPal1c0 4104
#define bkgSGBPal1c1 6
#define bkgSGBPal1c2 0
#define bkgSGBPal1c3 0

/* Super Gameboy palette 2 */
#define bkgSGBPal2c0 4104
#define bkgSGBPal2c1 6
#define bkgSGBPal2c2 0
#define bkgSGBPal2c3 0

/* Super Gameboy palette 3 */
#define bkgSGBPal3c0 4104
#define bkgSGBPal3c1 6
#define bkgSGBPal3c2 0
#define bkgSGBPal3c3 0

/* Gameboy Color palette 0 */
#define foreCGBPal0c0 RGB_WHITE
#define foreCGBPal0c1 RGB_CYAN
#define foreCGBPal0c2 RGB_RED
#define foreCGBPal0c3 RGB_BLACK
/* Gameboy Color palette 1 */
#define foreCGBPal1c0 RGB_WHITE
#define foreCGBPal1c1 RGB_WHITE
#define foreCGBPal1c2 RGB_BLUE
#define foreCGBPal1c3 RGB_BLACK

/* Gameboy Color palette 2 */
#define foreCGBPal2c0 RGB_WHITE
#define foreCGBPal2c1 RGB_WHITE
#define foreCGBPal2c2 RGB_GREEN
#define foreCGBPal2c3 RGB_BLACK

/* Gameboy Color palette 3 */
#define foreCGBPal3c0 RGB_WHITE
#define foreCGBPal3c1 RGB_YELLOW
#define foreCGBPal3c2 RGB_BROWN
#define foreCGBPal3c3 RGB_BLACK

/* Gameboy Color palette 4 */
#define foreCGBPal4c0 RGB_BLACK
#define foreCGBPal4c1 RGB_WHITE-RGB_CYAN
#define foreCGBPal4c2 RGB_WHITE-RGB_RED
#define foreCGBPal4c3 RGB_WHITE

/* Gameboy Color palette 5 */
#define foreCGBPal5c0 RGB_BLACK
#define foreCGBPal5c1 RGB_BLACK
#define foreCGBPal5c2 RGB_WHITE-RGB_BLUE
#define foreCGBPal5c3 RGB_WHITE

/* Gameboy Color palette 6 */
#define foreCGBPal6c0 RGB_BLACK
#define foreCGBPal6c1 RGB_BLACK
#define foreCGBPal6c2 RGB_WHITE-RGB_GREEN
#define foreCGBPal6c3 RGB_WHITE

/* Gameboy Color palette 7 */
#define foreCGBPal7c0 RGB_BLACK
#define foreCGBPal7c1 RGB_WHITE-RGB_YELLOW
#define foreCGBPal7c2 RGB_WHITE-RGB_BROWN
#define foreCGBPal7c3 RGB_WHITE

/* Super Gameboy palette 0 */
#define foreSGBPal0c0 0
#define foreSGBPal0c1 0
#define foreSGBPal0c2 0
#define foreSGBPal0c3 18

/* Super Gameboy palette 1 */
#define foreSGBPal1c0 6108
#define foreSGBPal1c1 8935
#define foreSGBPal1c2 6596
#define foreSGBPal1c3 6368

/* Super Gameboy palette 2 */
#define foreSGBPal2c0 6108
#define foreSGBPal2c1 8935
#define foreSGBPal2c2 6596
#define foreSGBPal2c3 6368

/* Super Gameboy palette 3 */
#define foreSGBPal3c0 6108
#define foreSGBPal3c1 8935
#define foreSGBPal3c2 6596
#define foreSGBPal3c3 6368

UWORD bkg_p[] = {
	bkgCGBPal0c0,bkgCGBPal0c1,bkgCGBPal0c2,bkgCGBPal0c3,
	bkgCGBPal1c0,bkgCGBPal1c1,bkgCGBPal1c2,bkgCGBPal1c3,
	bkgCGBPal2c0,bkgCGBPal2c1,bkgCGBPal2c2,bkgCGBPal2c3,
	bkgCGBPal3c0,bkgCGBPal3c1,bkgCGBPal3c2,bkgCGBPal3c3,
	bkgCGBPal4c0,bkgCGBPal4c1,bkgCGBPal4c2,bkgCGBPal4c3,
	bkgCGBPal5c0,bkgCGBPal5c1,bkgCGBPal5c2,bkgCGBPal5c3,
	bkgCGBPal6c0,bkgCGBPal6c1,bkgCGBPal6c2,bkgCGBPal6c3,
	bkgCGBPal7c0,bkgCGBPal7c1,bkgCGBPal7c2,bkgCGBPal7c3
};

UWORD obj_p[] = {
	foreCGBPal0c0,foreCGBPal0c1,foreCGBPal0c2,foreCGBPal0c3,
	foreCGBPal1c0,foreCGBPal1c1,foreCGBPal1c2,foreCGBPal1c3,
	foreCGBPal2c0,foreCGBPal2c1,foreCGBPal2c2,foreCGBPal2c3,
	foreCGBPal3c0,foreCGBPal3c1,foreCGBPal3c2,foreCGBPal3c3,
	foreCGBPal4c0,foreCGBPal4c1,foreCGBPal4c2,foreCGBPal4c3,
	foreCGBPal5c0,foreCGBPal5c1,foreCGBPal5c2,foreCGBPal5c3,
	foreCGBPal6c0,foreCGBPal6c1,foreCGBPal6c2,foreCGBPal6c3,
	foreCGBPal7c0,foreCGBPal7c1,foreCGBPal7c2,foreCGBPal7c3
};
