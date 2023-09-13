#include <gb.h>
#include "u3.h"


#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

#define SCROLLDELAY 20

extern UBYTE inexodus ;
extern UBYTE playerscreentile ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern UBYTE screenx ;
extern UBYTE screeny;
extern UBYTE playerx ;
extern UBYTE playery ;
extern UBYTE peermap ;

extern UBYTE ingenerator ;
extern UBYTE extragame ;

extern UBYTE transport ; //0=walking, 1=ship, 2=horse
extern UBYTE need_refresh ;
extern UBYTE delayscroll ;
extern UBYTE moves ;
extern UBYTE inside ;
extern UBYTE dir ;
extern UBYTE moon1 ;
extern UBYTE moon2 ;
extern UBYTE nummonsters ;
extern UBYTE numplayers ;
extern UBYTE stoptime ;
extern UBYTE stoptimebattle ;

extern UBYTE cheat_xray ;
extern UBYTE cheat_nofight ;
extern UBYTE cheat_nohurt ;
extern UBYTE cheat_noblock ;
extern UBYTE cheat_fullmp ;
extern UBYTE cheat_noclass ;
extern UBYTE omnieye ;

extern unsigned char *vidbase ;
extern unsigned char screenbuf3[] ;

extern PLAYER players[] ;
extern MONSTER monsters[] ;

extern BATTLEMONSTERS baddies[9] ;
//extern BATTLEPLAYERS  goodies[4] ;
extern UBYTE numbaddies ;
extern UBYTE numgoodies ;
extern UBYTE numalive ;

extern UBYTE playerslocs ;
extern UBYTE monsterslocs ;
extern UBYTE monsterpower ;
extern UBYTE monstertile ;
extern UBYTE monsterexp ;
extern UBYTE monsterstat ;
extern UBYTE monsterattrib ;
extern UBYTE masskill ;
extern UBYTE mapnum ;
extern UBYTE moonchanges ;

UBYTE monstertile ;
extern UBYTE baddemeanor ;

unsigned char screenbuf[11][11] ;
unsigned char screenbuf2[32] ;

unsigned char visibletiles[11][11] ;

unsigned char alldeaddat2[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D, 
} ;

unsigned char canceldat2[] = {
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x5d,0x5d,0x5d
} ;
unsigned char dirdat4[] = {
	'D'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x83,0x5d,0x5D
};
unsigned char firedat[] = {
	'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D
};

unsigned char monsternames[] = {
	'B'+0x1D,'R'+0x1D,'I'+0x1D,'G'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'P'+0x1D,'U'+0x1D,'R'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'O'+0x1D,'B'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'R'+0x1D,'O'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'Z'+0x1D,'O'+0x1D,'M'+0x1D,'B'+0x1D,'I'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'E'+0x1D,'M'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'I'+0x1D,'T'+0x1D,'A'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'A'+0x1D,'R'+0x1D,'G'+0x1D,'O'+0x1D,'Y'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'A'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'N'+0x1D,'A'+0x1D,'T'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'B'+0x1D,'R'+0x1D,'A'+0x1D,'D'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'R'+0x1D,'I'+0x1D,'F'+0x1D,'F'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'Y'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'O'+0x1D,'R'+0x1D,'C'+0x1D,'U'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'E'+0x1D,'V'+0x1D,'I'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D

} ;

unsigned char tiledescdat[] = {
	'W'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'R'+0x1D,'A'+0x1D,'S'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'N'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'R'+0x1D,'E'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'U'+0x1D,'N'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'U'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'O'+0x1D,'W'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'F'+0x1D,'L'+0x1D,'O'+0x1D,'O'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'H'+0x1D,'O'+0x1D,'R'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'F'+0x1D,'R'+0x1D,'I'+0x1D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'H'+0x1D,'I'+0x1D,'R'+0x1D,'L'+0x1D,'P'+0x1D,'O'+0x1D,'O'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'H'+0x1D,'I'+0x1D,'R'+0x1D,'L'+0x1D,'P'+0x1D,'O'+0x1D,'O'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'H'+0x1D,'I'+0x1D,'R'+0x1D,'L'+0x1D,'P'+0x1D,'O'+0x1D,'O'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'H'+0x1D,'I'+0x1D,'R'+0x1D,'L'+0x1D,'P'+0x1D,'O'+0x1D,'O'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'E'+0x1D,'A'+0x1D,0x5D,'S'+0x1D,'E'+0x1D,'R'+0x1D,'P'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,0x5D, 
	'M'+0x1D,'A'+0x1D,'N'+0x1D,0x5D,'O'+0x1D,0x5D,'W'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
	'P'+0x1D,'I'+0x1D,'R'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'E'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,'A'+0x1D,'N'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'J'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'U'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,'B'+0x1D,'R'+0x1D,'I'+0x1D,'T'+0x1D,'I'+0x1D,'S'+0x1D,'H'+0x1D, 
	'F'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'I'+0x1D,'Z'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'H'+0x1D,'I'+0x1D,'E'+0x1D,'F'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'O'+0x1D,'R'+0x1D,'C'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'K'+0x1D,'E'+0x1D,'L'+0x1D,'E'+0x1D,'T'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'I'+0x1D,'A'+0x1D,'N'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'A'+0x1D,'E'+0x1D,'M'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'P'+0x1D,'I'+0x1D,'N'+0x1D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'R'+0x1D,'A'+0x1D,'G'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'B'+0x1D,'A'+0x1D,'L'+0x1D,'R'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'D'+0x1D,'U'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'I'+0x1D,'E'+0x1D,'L'+0x1D,'D'+0x1D,0x5D, 
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'I'+0x1D,'E'+0x1D,'L'+0x1D,'D'+0x1D,0x5D, 
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'I'+0x1D,'E'+0x1D,'L'+0x1D,'D'+0x1D,0x5D, 
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'I'+0x1D,'E'+0x1D,'L'+0x1D,'D'+0x1D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'V'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'V'+0x1D,'O'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'A'+0x1D,'B'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'B'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'C'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'F'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'I'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'J'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'K'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'M'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'O'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'Q'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'U'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'V'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'W'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'X'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'Z'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'E'+0x1D,'R'+0x1D,'P'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'E'+0x1D,'R'+0x1D,'P'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'N'+0x1D,'O'+0x1D,'N'+0x1D,'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D, 
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'N'+0x1D,'O'+0x1D,'N'+0x1D,'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D, 
	'S'+0x1D,'H'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'R'+0x1D,'A'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'V'+0x1D,'O'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char conflictdat[] = {
	'C'+0x1D,'O'+0x1D,'N'+0x1D,'F'+0x1D,'L'+0x1D,'I'+0x1D,'C'+0x1D,'T'+0x1D,0x82,0x5D,0x5D,0x5D
} ;

unsigned char press_a_dat[] = {
	'P'+0x1D,'R'+0x1D,'E'+0x1D,'S'+0x1D,'S'+0x1D,0x5D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char monsterstatdat[] = {
//exp,dex/str,hp,attribs (high nibble=magic (1=damage,2=poison), low nibble=projectile)
//    [20 20 f0 f0 c0 60 a0 80 30 50 70 a0 c0 e0 f0 f0]
//merchant
	0x01,0x00,0x20,0x00,
//jester
	0x02,0x05,0x20,0x00,
//orc
	0x03,0x0A,0x30,0x00,
//skeleton
	0x04,0x0F,0x50,0x00,
//ranger
	0x05,0x14,0xF0,0x00,
//thief
	0x05,0x14,0x80,0x00,
//cleric
	0x06,0x19,0x60,0x02,
//giant
	0x06,0x19,0x70,0x00,
//horse
	0x06,0x19,0x70,0x00,
//fighter
	0x08,0x1e,0xc0,0x00,
//daemon
	0x08,0x1e,0xa0,0x01,
//wizard
	0x0a,0x23,0xa0,0x01,
//pincher
	0x0a,0x23,0xc0,0x00,
//dragon
	0x0f,0x28,0xe0,0x01,
//sea serpent
	0x0f,0x28,0xE0,0x10,
//manowar
	0x14,0x2D,0xF0,0x20,
//guard
	0x0f,0x37,0xf0,0x00,
//balron
	0x14,0x37,0xf0,0x20,
//floor
	0x14,0x3C,0xF0,0x00,
//lord british
	0x14,0x63,0xF0,0x00
} ;


unsigned char playerscoords[] = {
//regular 4-formation
	4,7,
	6,7,
	3,9,
	7,9,
//on ship for land battle and ship-ship battle
	3,7,
	6,7,
	2,9,
	7,9,
//on ship water battle
	3,4,
	6,4,
	2,5,
	7,5
//
};
unsigned char monsterscoords[] = {
//water monsters attacking ship
	5,0,
	7,0,
	4,1,
	6,1,
	4,9,
	6,9,
	5,10,
	7,10,
//water monsters attacking land players
	3,1,
	5,1,
	2,2,
	7,2,
	3,3,
	4,3,
	5,3,
	6,3,
//guards - all land monsters
	5,0,
	3,1,
	7,1,
	2,2,
	5,2,
	8,2,
	4,3,
	6,3,
};

unsigned char chardat[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};

unsigned char charstat[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};

unsigned char starvingdat[] = {
	'S'+0x1D,'T'+0x1D,'A'+0x1D,'R'+0x1D,'V'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x82,0x5D,0x5D,0x5D
};

unsigned char poisondat[] = {
	'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5d,0x5d,0x5d 
} ;

unsigned char invalidmovedat[] = {
	'I'+0x1D,'N'+0x1D,'V'+0x1D,'A'+0x1D,'L'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,'M'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D
};

unsigned char directiondat[] = {
	'N'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,'H'+0x1D,
	'S'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,'H'+0x1D,
	'E'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5d,
	'W'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5d
};

UBYTE moongates[] = {
	8,8,
	46,57,
	27,15,
	58,36,
	29,15,
	55,12,
	31,31,
	31,58
};

void formatnumber2(UWORD num,UBYTE length)
{
	UBYTE n ;
	unsigned char ch ;
	UWORD tens ;

	tens =1 ;

	for ( n=0 ; n<length-1 ; n++ )
		tens = tens*10 ;

	for ( n=0 ; n<length ; n++ )
	{
		ch=0x78U ; //'0'
		while ( num>= tens )
		{
			num -= tens ;
			ch++ ;
		}
		tens = tens/10 ;
		*((unsigned char*)screenbuf2+(UWORD)n) = ch ;


	}

}


void update_screen()
{
	UBYTE n, iterx, itery, mask ;
	BYTE ux,uy ;

	/*
	if (delayscroll-- == 0)
	{
	   if (++mode4tiles==4)
		  mode4tiles=0 ;
	   if (++mode8tiles==8)
		  mode8tiles=0 ;
 
	   set_bkg_data2(  0x00, 0x01, u3tiles+(UWORD)((UWORD)mode4tiles<<4) );
	   set_bkg_data2(  0x0F, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x0FL)<<4) );
	   set_bkg_data2(  0x26, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x26L)<<4) );
	   set_bkg_data2(  0x2A, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x2AL)<<4) );
	   set_bkg_data2(  0x32, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x32L)<<4) );
	   delayscroll = SCROLLDELAY ;
	}
	*/

//   if (!need_refresh)
	//return ;
	memset(screenbuf2,0x5D,12L) ;
//        formatnumber2((UWORD)playerx,2) ;
	//      writegamemessage(screenbuf2) ;
	//    formatnumber2((UWORD)playery,2) ;
	//  writegamemessage(screenbuf2) ;
	//need_refresh = 0 ;


	if ( LCDC_REG&0x10 )
	{
		vidbase = (unsigned char*)0x9800 ;
		//set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	}
	else
	{
		vidbase = (unsigned char*)0x9C00 ;
		//set_data2((unsigned char*)0x9C00,(unsigned char*)0x9800,0x400UL) ;
	}


	ux = screenx ;
	uy = screeny ;

	itery = 0 ;
	while ( itery != 11 )
	{
		if ( uy>63 )
			uy = 0 ;
		iterx = 0 ;
		ux = screenx ;
		while ( iterx != 11 )
		{
			if ( ux>63 )
				ux = 0 ;
			*((unsigned char*)screenbuf+(((UWORD)itery)*11L)+iterx) = *((unsigned char*)0xA000+(((UWORD)uy)<<6L)+((UWORD)ux));
			ux++ ;
			iterx++ ;
		}
		uy++ ;
		itery++ ;
	}

	if ( inside )
	{
		if ( screeny>58 )
			for ( uy=screeny ; uy!=64  ; uy++ )
				memset((unsigned char*)screenbuf+(UWORD)((uy-screeny)*11),0x04,11L) ;

		if ( screenx>58 )
			for ( ux=screenx ; ux!=64  ; ux++ )
				for ( iterx=0 ; iterx!=11 ; iterx++ )
					*((unsigned char*)screenbuf+(UWORD)(11*iterx)+(UWORD)(ux-screenx) ) = 0x04 ;

		for ( uy=screeny ; ((uy<59) && (uy>53)) ; uy-- )
			memset((unsigned char*)screenbuf+(UWORD)((10-(screeny-uy))*11),0x04,11L) ;

		for ( ux=screenx ; ((ux<59) && (ux>53)) ; ux-- )
			for ( iterx=0 ; iterx!=11 ; iterx++ )
				*((unsigned char*)screenbuf+(UWORD)(11*iterx)+(UWORD)(10-(screenx-ux)) ) = 0x04 ;
	}

	memset((unsigned char*)visibletiles,1,121L) ;

	n=0 ;

	if ( ( cheat_xray == 0 ) && ( omnieye == 0 ) )
	{
		while ( n!=80U )
		{
			ux = *(check_order+(UWORD)n)>>4 ;
			uy = *(check_order+(UWORD)n)&0x0F ;

			if ( (visibletiles[ux][uy]) && ((*(tile_attribs+(UWORD)(screenbuf[uy][ux])))&0x10) )
			{
				if ( ux==5 )
				{
					if ( uy<5 )
					{
						while ( --uy>=0 )
						{
							for ( iterx=ux-1 ; iterx <= 6 + (5-ux) ; iterx++ )
							{
								visibletiles[iterx][uy] = 0 ;
								screenbuf[uy][iterx] = 0x3BU ;
							}
							ux-- ;

						}
					}
					else
					{
						while ( ++uy<=10 )
						{
							for ( iterx=ux-1 ; iterx <= 6 + (5-ux) ; iterx++ )
							{
								visibletiles[iterx][uy] = 0 ;
								screenbuf[uy][iterx] = 0x3BU ;
							}
							ux-- ;

						}
					}
				}
				else
					if ( uy==5 )
				{
					if ( ux<5 )
					{
						while ( --ux>=0 )
						{
							for ( itery=uy-1 ; itery <= 6 + (5-uy) ; itery++ )
							{
								visibletiles[ux][itery] = 0 ;
								screenbuf[itery][ux] = 0x3BU ;
							}
							uy-- ;

						}
					}
					else
					{
						while ( ++ux<=10 )
						{
							for ( itery=uy-1 ; itery <= 6 + (5-uy) ; itery++ )
							{
								visibletiles[ux][itery] = 0 ;
								screenbuf[itery][ux] = 0x3BU ;
							}
							uy-- ;

						}
					}

				}
				else
					if ( ux<5 )
				{
					if ( uy<5 )
					{
						while ( (--ux >=0) && (--uy>=0) )
						{
							visibletiles[ux][uy] = 0 ;
							screenbuf[uy][ux] = 0x3BU ;
						}
					}
					else
					{
						while ( (--ux >=0) && (++uy<=10) )
						{
							visibletiles[ux][uy] = 0 ;
							screenbuf[uy][ux] = 0x3BU ;
						}
					}
				}
				else
				{
					if ( uy<5 )
					{
						while ( (++ux <=10) && (--uy>=0) )
						{
							visibletiles[ux][uy] = 0 ;
							screenbuf[uy][ux] = 0x3BU ;
						}
					}
					else
					{
						while ( (++ux <=10) && (++uy<=10) )
						{
							visibletiles[ux][uy] = 0 ;
							screenbuf[uy][ux] = 0x3BU ;
						}
					}
				}

			}


			n++ ;
		}
	}

	*((unsigned char*)screenbuf+60L) = playerscreentile ;

	disable_interrupts2() ;
	for ( n = 0 ; n!=11 ; n++ )
		set_data2(vidbase+(((UWORD)n+1L)<<5L)+1L,(unsigned char*)screenbuf+((UWORD)n*11L),11L) ;
	enable_interrupts2() ;

	//set_bkg_tiles2( 1, 1, 11, 11, (unsigned char*)screenbuf );

	VBK_REG = 1;		// select palette bank 

	ux = screenx ;
	uy = screeny ;

	itery = 0 ;
	while ( itery != 11 )
	{
		if ( uy>63 )
			uy = 0 ;
		iterx = 0 ;
		ux = screenx ;
		while ( iterx != 11 )
		{
			if ( ux>63 )
				ux = 0 ;
			*((unsigned char*)screenbuf+(((UWORD)itery)*11L)+iterx) = *(tile_palettes+(UWORD)(*((unsigned char*)0xA000+(((UWORD)uy)<<6L)+((UWORD)ux))));

			ux++ ;
			iterx++ ;
		}
		uy++ ;
		itery++ ;
	}

	if ( inside )
	{
		if ( screeny>58 )
			for ( uy=screeny ; uy!=64  ; uy++ )
				memset((unsigned char*)screenbuf+(UWORD)((uy-screeny)*11),0x02,11L) ;


		if ( screenx>58 )
			for ( ux=screenx ; ux!=64  ; ux++ )
				for ( iterx=0 ; iterx!=11 ; iterx++ )
					*((unsigned char*)screenbuf+(UWORD)(11*iterx)+(UWORD)(ux-screenx) ) = 0x02 ;

		for ( uy=screeny ; ((uy<59) && (uy>53)) ; uy-- )
			memset((unsigned char*)screenbuf+(UWORD)((10-(screeny-uy))*11),0x02,11L) ;

		for ( ux=screenx ; ((ux<59) && (ux>53)) ; ux-- )
			for ( iterx=0 ; iterx!=11 ; iterx++ )
				*((unsigned char*)screenbuf+(UWORD)(11*iterx)+(UWORD)(10-(screenx-ux)) ) = 0x02 ;
	}

	*((unsigned char*)screenbuf+60L) = 0x01 ;
	disable_interrupts2() ;
	for ( n = 0 ; n!=11 ; n++ )
		set_data2(vidbase+(((UWORD)n+1L)<<5L)+1L,(unsigned char*)screenbuf+((UWORD)n*11L),11L) ;
	enable_interrupts2() ;
	//  set_bkg_tiles2( 1, 1, 11, 11, (unsigned char*)screenbuf );

	VBK_REG = 0;		// select data bank 

	if ( LCDC_REG&0x10 )
		LCDC_REG &= 0xEF ;	//select $9800-$9BFF
	else
		LCDC_REG |= 0x10 ;	//select $9C00-$9FFF


}



void charscreen(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf2,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf2 );

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat );

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber2(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf2 );

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat+(UWORD)player->status );

	formatnumber2(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf2 );

	formatnumber2(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf2 );

	formatnumber2(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf2 );

	*(unsigned char*)screenbuf2 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf2 );


}

void flashchar2(UBYTE pnum, UBYTE sfx)
{
	UBYTE q ;

	memset(screenbuf3,0x04,7L) ;
	disable_interrupts2();
	VBK_REG = 1 ;
	for ( q=0 ; q<4 ; q++ )
		set_bkg_tiles2(13,q+(pnum<<2)+1,7,1,(unsigned char*)screenbuf3) ;
	VBK_REG = 0 ;
	enable_interrupts2() ;
	playerhitsfx(170U);
	//delay(1250) ;
	disable_interrupts2();
	VBK_REG = 1 ;
	memset(screenbuf3,0x00,7L) ;
	for ( q=0 ; q<4 ; q++ )
		set_bkg_tiles2(13,q+(pnum<<2)+1,7,1,(unsigned char*)screenbuf3) ;
	VBK_REG = 0 ;
	enable_interrupts2();


}
unsigned char deaddat7[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82 
} ;

void damageplayer4(UBYTE pnum, UBYTE damage)
{
	if ( cheat_nohurt != 0 )
		return ;

	if ( (UWORD)damage < players[pnum].currHP )
		players[pnum].currHP -= (UWORD)damage ;
	else
	{
		players[pnum].currHP = 0L ;
		players[pnum].status = 0x02 ;
		numalive-- ;
		screenbuf3[0] = 'D'+0x1D ;
		set_data2((unsigned char*)0x9800+19L+(32L*(2+(pnum<<2))),screenbuf3,1L) ;
		set_data2((unsigned char*)0x9C00+19L+(32L*(2+(pnum<<2))),screenbuf3,1L) ;
		writegamemessage(deaddat7) ;

	}
	formatnumber2( (UWORD)(players[pnum].currHP),4) ;
	set_data2((unsigned char*)0x9800+14L+(32L*(2+(pnum<<2))),(unsigned char*)screenbuf2,4L) ;
	set_data2((unsigned char*)0x9C00+14L+(32L*(2+(pnum<<2))),(unsigned char*)screenbuf2,4L) ;


}

void eatfood()
{
	UBYTE p,q ;
	for ( p=0 ; p<4 ; p++ )
	{
		if ( ( players[p].inparty) && 
			 ( players[p].status <2) )
		{
			if ( players[p].food )
			{
				(players[p].food)-- ;
				if ( players[p].currHP < players[p].maxHP )
					players[p].currHP++ ;

				formatnumber2( (UWORD)(players[p].food),4) ;
				set_data2((unsigned char*)0x9800+14L+(32L*(3+(p<<2))),(unsigned char*)screenbuf2,4L) ;
				set_data2((unsigned char*)0x9C00+14L+(32L*(3+(p<<2))),(unsigned char*)screenbuf2,4L) ;
				formatnumber2( (UWORD)(players[p].currHP),4) ;
				set_data2((unsigned char*)0x9800+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
				set_data2((unsigned char*)0x9C00+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
			}
			else
			{
				/*
			   memset(screenbuf2,0x04,7L) ;
			   disable_interrupts2();
			   VBK_REG = 1 ;
			   for (q=0 ; q<4 ; q++)
				  set_bkg_tiles2(13,q+(p<<2)+1,7,1,(unsigned char*)screenbuf2) ;
			   starvingsfx() ;
			   memset(screenbuf2,0x00,7L) ;
			   for (q=0 ; q<4 ; q++)
				  set_bkg_tiles2(13,q+(p<<2)+1,7,1,(unsigned char*)screenbuf2) ;
			   VBK_REG = 0 ;
			   enable_interrupts2();
				  */
				writegamemessage(starvingdat) ;
				damageplayer4(p,5) ;
				flashchar2(p,0) ;
				/*
		   if (players[p].currHP<6L)
		   {
			   players[p].currHP = 0L ;
			  players[p].status = 2 ;
			  numalive-- ;
			  set_data2((unsigned char*)0x9800+19L+(32L*(2+(p<<2))),charstat+2L,1L) ;
			  set_data2((unsigned char*)0x9C00+19L+(32L*(2+(p<<2))),charstat+2L,1L) ;
		   }
		   else
			   players[p].currHP -= 5L ;
		   
		   formatnumber2( (UWORD)(players[p].currHP),4) ;
		   set_data2((unsigned char*)0x9800+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
		   set_data2((unsigned char*)0x9C00+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
				  */
			}

		}

	}

}

void update_moons()
{
	if ( moon2==7 )
		moon2 = 0 ;
	else
		moon2++	;
	if ( inside<2 )
	{
		//screenbuf2[0] = moon2+0x78 ;
		screenbuf2[0] = moon2+0xB0;
		set_data2((unsigned char*)0x9800+7L,(unsigned char*)screenbuf2,1L) ;
		set_data2((unsigned char*)0x9C00+7L,(unsigned char*)screenbuf2,1L) ;
	}

	moonchanges++ ;
	if ( moonchanges>2 )
	{
		moonchanges = 0 ;

		if ( inside==0 )
			*((unsigned char*)0xA000+(64L*(UWORD)(moongates[(moon1<<1)]))+
			  (UWORD)(moongates[(moon1<<1)+1])) = 0x04 ;
		if ( moon1==7 )
			moon1 = 0 ;
		else
			moon1++	;
		if ( inside==0 )
			*((unsigned char*)0xA000+(64L*(UWORD)(moongates[(moon1<<1)]))+
			  (UWORD)(moongates[(moon1<<1)+1])) = 0x32 ;

		if ( inside<2 )
		{
			//screenbuf2[0] = moon1+0x78 ;
			screenbuf2[0] = moon1+0xB0 ;
			set_data2((unsigned char*)0x9800+5L,(unsigned char*)screenbuf2,1L) ;
			set_data2((unsigned char*)0x9C00+5L,(unsigned char*)screenbuf2,1L) ;
		}
	}

	if ( inside==0 )
	{
		if ( (moon1==0)&&(moon2==0) )
		{
			*((unsigned char*)0xA000+(53L*64L)+37L) = 0x09 ;
			need_refresh=1 ;

		}
		if ( (moon1==0)&&(moon2==1) )
		{
			*((unsigned char*)0xA000+(53L*64L)+37L) = 0x06 ;
			need_refresh=1 ;
		}


	}

}
void refresh_moongate()
{
	UBYTE p ;

	for ( p=0 ; p<8 ; p++ )
	{
		if ( p!=moon1 )
			*((unsigned char*)0xA000+(64L*(UWORD)(moongates[(p<<1)]))+
			  (UWORD)(moongates[(p<<1)+1])) = 0x04 ;
		else
			*((unsigned char*)0xA000+(64L*(UWORD)(moongates[(p<<1)]))+
			  (UWORD)(moongates[(p<<1)+1]))	= 0x32 ;


	}

}

UBYTE moveOK(UBYTE newx, UBYTE newy, UBYTE monstile, UBYTE attrib)
{
	UBYTE newtile ;

	if ( (newy==playery) && (newx==playerx) )
	{
		if ( attrib&0xF0U )
			return 2 ;
		else
		{
			if ( (attrib&0x0F)==0x01 )
				return 3 ;
			else
				return 0 ;
		}
	}

	newtile = *((unsigned char*)0xA000+((UWORD)(((UWORD)newy)<<6))+(UWORD)newx) ;
	if ( (monstile >= 0x0F) && (monstile<=0x15) )
		if ( newtile == 0x00 )
			return 1 ;
		else
			return 0 ;
	else
		if ( (tile_attribs[newtile])&0x40 )
		return 1 ;
	else
		return 0 ;
}

UBYTE move_monsters(UBYTE n)
{
	UBYTE newposx, newposy ;
	UBYTE rndval ;
	UBYTE retval ;
	unsigned char oldtile ;


	newposx = monsters[n].x ;
	newposy = monsters[n].y ;
	if ( (monsters[n].attribs)&0x03 )  //monster is mobile
	{
		if ( (monsters[n].attribs)&0x01 )  //move towards character
		{
			if ( inside )
			{
				if ( monsters[n].x>playerx )
					newposx = monsters[n].x - 1 ;
				if ( monsters[n].x<playerx )
					newposx = monsters[n].x + 1 ;
				if ( monsters[n].y>playery )
					newposy = monsters[n].y - 1 ;
				if ( monsters[n].y<playery )
					newposy = monsters[n].y + 1 ;

			}
			else
			{
				if ( monsters[n].x > playerx )
				{
					if ( monsters[n].x-playerx>32U )
					{
						if ( monsters[n].x==63 )
							newposx = 0 ;
						else
							newposx	= monsters[n].x +1 ;

					}
					else  //no way monsters[n].x is 0
						newposx	= monsters[n].x-1 ;

				}
				if ( monsters[n].x < playerx )
				{
					if ( playerx-monsters[n].x>32U )
					{
						if ( monsters[n].x==0 )
							newposx = 63 ;
						else
							newposx	= monsters[n].x -1 ;

					}
					else  //no way monsters[n].x is 63
						newposx	= monsters[n].x+1 ;

				}
				if ( monsters[n].y > playery )
				{
					if ( monsters[n].y-playery>32U )
					{
						if ( monsters[n].y==63 )
							newposy = 0 ;
						else
							newposy	= monsters[n].y +1 ;

					}
					else  //no way monsters[n].y is 0
						newposy	= monsters[n].y-1 ;

				}
				if ( monsters[n].y < playery )
				{
					if ( playery-monsters[n].y>32U )
					{
						if ( monsters[n].y==0 )
							newposy = 63 ;
						else
							newposy	= monsters[n].y -1 ;

					}
					else  //no way monsters[n].y is 63
						newposy	= monsters[n].y+1 ;

				}


			}


		}
		else //move randomly - either 1 in x dir or 1 in y dir or nowhere
		{
			if ( (make_rnd(0))&0x80U )	//move random x dir
			{
				if ( (make_rnd(0))&0x80U )
					if ( monsters[n].x==63 )
						if ( inside != 0 )
							return 0 ;
						else
							newposx	= 0 ;
					else
						newposx	= monsters[n].x+1 ;
				else
					if ( monsters[n].x==0 )
					if ( inside != 0 )
						return 0 ;
					else
						newposx	= 63 ;
				else
					newposx	= monsters[n].x-1 ;
			}

			if ( (make_rnd(0))&0x80U )	//move random y dir
			{
				if ( (make_rnd(0))&0x80U )
					if ( monsters[n].y==63 )
						if ( inside != 0 )
							return 0 ;
						else
							newposy	= 0 ;
					else
						newposy	= monsters[n].y +1 ;
				else
					if ( monsters[n].y==0 )
					if ( inside != 0 )
						return 0 ;
					else
						newposy	= 63 ;
				else
					newposy	= monsters[n].y -1 ;
			}

		}

		if ( (retval=(moveOK(newposx, newposy, monsters[n].tile,monsters[n].attribs)))==2 )
			return 2 ;
		else
			if ( retval==0 )
		{
			//      if (monsters[n].attribs&0xF0U)
			//    {
			if ( (retval=(moveOK(monsters[n].x, newposy, monsters[n].tile,monsters[n].attribs)))==2 )
				return 2 ;
			else
			{
				if ( retval==0 )
				{
					if ( (retval=(moveOK(newposx, monsters[n].y, monsters[n].tile,monsters[n].attribs)))==2 )
						return 2 ;
					else
						if ( retval!=0 )
						newposy = monsters[n].y ;
				}
				else
					newposx	= monsters[n].x ;
			}
			//}     


		}
		if ( retval==3 )
//			if ((monsters[n].tile==0x15)||(monsters[n].tile==0x23))
			//return 1 ;
			//else
			return 0 ;

		if ( retval )  //makemove
		{
			disable_interrupts2() ;
			SWITCH_RAM_MBC5(3) ;
			oldtile = *((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[n].y))<<6))+(UWORD)(monsters[n].x)) ;
			SWITCH_RAM_MBC5(1) ;
			enable_interrupts2() ;
			//if (oldtile==0x45)
			//	*((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[n].y))<<6))+(UWORD)(monsters[n].x)) = 0x0B ;
			//else
			*((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[n].y))<<6))+(UWORD)(monsters[n].x)) = oldtile ;
			*((unsigned char*)0xA000+((UWORD)(((UWORD)(newposy))<<6))+(UWORD)(newposx)) = monsters[n].tile ;
			monsters[n].x = newposx ;
			monsters[n].y = newposy ;

		}



	}

	//if ((monsters[n].tile==0x15)||(monsters[n].tile==0x23))
	//return 1 ;
	//else
	return 0 ;
}

void moongatesfx() 
{
	UBYTE s,t ;

	disable_interrupts2() ;

	VBK_REG = 1 ;
	for ( s = 0 ; s!=11 ; s++ )
	{
		get_bkg_tiles2(1,s+1,11,1,screenbuf3) ;
		for ( t = 0 ; t!=11 ; t++ )
			screenbuf3[t] += 4 ;
		set_bkg_tiles2(1,s+1,11,1,screenbuf3) ;
	}
	VBK_REG = 0 ;
	enable_interrupts2() ;
	magicsfx2(0,12,0) ;
	disable_interrupts2() ;

	VBK_REG = 1 ;
	for ( s = 0 ; s!=11 ; s++ )
	{
		get_bkg_tiles2(1,s+1,11,1,screenbuf3) ;
		for ( t = 0 ; t!=11 ; t++ )
			screenbuf3[t] -= 4 ;
		set_bkg_tiles2(1,s+1,11,1,screenbuf3) ;
	}
	VBK_REG = 0 ;
	enable_interrupts2() ;

}

void checkmoongate()
{
	if ( inside==0 )
		if ( (screenx<55)&&(screeny<55) )
			if ( (screenx+5==moongates[(moon1<<1)+1]) &&
				 (screeny+5==moongates[(moon1<<1)]) )
			{
				update_screen() ;
				moongatesfx() ;
				screenx = moongates[(moon2<<1)+1]-5 ;
				screeny = moongates[(moon2<<1)]-5 ;
				playerx = screenx+5 ;
				playery = screeny+5 ;
				update_screen() ;
				moongatesfx() ;
			}

}


void postmove()
{
	UBYTE p,q,oins ;
	UBYTE maxmagic ;
	unsigned char atile ;

//set wind direction
//set moons,change/move moongates
//check if player on active moongate
//make hidden things appear
//move monsters
//decrease food
//check starving/poison
//every 10 moves, every 40 moves eat food
//every 4 moves change second moon
//every 12 moves change first moon
	if ( ++moves >239U )
		moves = 0 ;

	if ( inside==0 )
		oins = 0 ;
	else
		oins = 1 ;

	if ( dir )
	{
		if ( dir==5 )
		{
			writegamemessage(invalidmovedat) ;
			invalidmovesfx(80) ;
		}
		else
		{
			memset(screenbuf2,0x5D,12L) ;
			memcpy(screenbuf2,directiondat+(((UWORD)dir-1L)*5L),5L) ;
			writegamemessage(screenbuf2) ;
			movesfx(15,20,(playerscreentile==0x0D)) ;
		}
		dir = 0 ;
	}
	if ( (moves%(1<<(oins*2)))==0 )
		for ( p=0 ; p<4 ; p++ )
		{
			if ( (players[p].inparty) &&( players[p].status <2) )
			{
				maxmagic = 0 ;
				if ( players[p].skill==2 )
					maxmagic = players[p].wis ;
				if ( players[p].skill==10 )
					maxmagic = players[p].intel ;
				if ( (players[p].skill==7) || (players[p].skill==5) )
					maxmagic = players[p].wis/2 ;
				if ( (players[p].skill==6) || (players[p].skill==0) )
					maxmagic = players[p].intel/2 ;
				if ( players[p].skill==3 )
					if ( players[p].intel < players[p].wis )
						maxmagic = players[p].wis /2 ;
					else
						maxmagic = players[p].intel /2 ;
				if ( players[p].skill==8 )
					if ( players[p].intel > players[p].wis )
						maxmagic = players[p].wis /2 ;
					else
						maxmagic = players[p].intel /2 ;

				if ( players[p].magic < maxmagic )
				{
					if ( players[p].skill==3 )
					{
						if ( players[p].magic < players[p].wis/2 )
							players[p].magic++ ;
						if ( players[p].magic < players[p].intel/2 )
							players[p].magic++ ;
						if ( players[p].magic > maxmagic )
							players[p].magic = maxmagic ;
					}
					else
						players[p].magic++ ;
					formatnumber2( (UWORD)(players[p].magic),2) ;
					set_data2((unsigned char*)0x9800+14L+(32L*(4+(p<<2))),(unsigned char*)screenbuf2,2L) ;
					set_data2((unsigned char*)0x9C00+14L+(32L*(4+(p<<2))),(unsigned char*)screenbuf2,2L) ;
				}

				if ( players[p].status==1 )
				{
					/*
				   memset(screenbuf2,0x04,7L) ;
				   disable_interrupts2();
				   VBK_REG = 1 ;
				   for (q=0 ; q<4 ; q++)
					  set_bkg_tiles2(13,q+(p<<2)+1,7,1,(unsigned char*)screenbuf2) ;
				   starvingsfx() ;
				   memset(screenbuf2,0x00,7L) ;
				   for (q=0 ; q<4 ; q++)
					  set_bkg_tiles2(13,q+(p<<2)+1,7,1,(unsigned char*)screenbuf2) ;
				   VBK_REG = 0 ;
				   enable_interrupts2();
					  */
					writegamemessage(poisondat) ;
					damageplayer4(p,1) ;
					flashchar2(p,0) ;
					/*
			   (players[p].currHP)-- ;
			   formatnumber2( (UWORD)(players[p].currHP),4) ;
			   set_data2((unsigned char*)0x9800+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
			   set_data2((unsigned char*)0x9C00+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
			   if (players[p].currHP==0)
			   {
				  players[p].status = 2 ;
				  numalive-- ;
				  set_data2((unsigned char*)0x9800+19L+(32L*(2+(p<<2))),charstat+2L,1L) ;
				  set_data2((unsigned char*)0x9C00+19L+(32L*(2+(p<<2))),charstat+2L,1L) ;
			   }
			   */
				}

			}
		}

	if ( (moves%(10<<(oins*2)))==0 )
		eatfood() ;
	if ( !stoptime )
	{
		if ( (moves%(4<<(oins*2)))==0 )
			update_moons() ;
//      if ((moves%(12<<(inside*2)))==0)
//         update_moons(1) ;
	}

	if ( (inside==0)||(inside==1) )
	{
		atile = *((unsigned char*)0xA000+(((UWORD)playery)*64L)+((UWORD)playerx));

		if ( atile==0x2A )	//fire/lava
		{
			for ( p=0 ; p<numplayers ; p++ )
				if ( (players[p].status<2) && (!(players[p].markcard&MARKFIRE)) )
				{
					/*
				  disable_interrupts2();
				  memset(screenbuf2,0x04,7L) ;
				  VBK_REG = 1 ;
				  for (q=0 ; q<4 ; q++)
					 set_bkg_tiles2(13,q+(p<<2)+1,7,1,(unsigned char*)screenbuf2) ;
				  starvingsfx() ;
				  memset(screenbuf2,0x00,7L) ;
				  for (q=0 ; q<4 ; q++)
					 set_bkg_tiles2(13,q+(p<<2)+1,7,1,(unsigned char*)screenbuf2) ;
				  VBK_REG = 0 ;
				  enable_interrupts2();
					  */
					writegamemessage(firedat) ;
					damageplayer4(p,50) ;
					flashchar2(p,0) ;
					/*
   if (players[p].currHP<51)
   {
	  players[p].currHP = 0L ;
	  players[p].status = 2 ;
	  numalive-- ;
	  set_data2((unsigned char*)0x9800+19L+(32L*(2+(p<<2))),charstat+2L,1L) ;
	  set_data2((unsigned char*)0x9C00+19L+(32L*(2+(p<<2))),charstat+2L,1L) ;
   }
   else
	  players[p].currHP -= 50L ;
  
   formatnumber2( (UWORD)(players[p].currHP),4) ;
   set_data2((unsigned char*)0x9800+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
   set_data2((unsigned char*)0x9C00+14L+(32L*(2+(p<<2))),(unsigned char*)screenbuf2,4L) ;
					  */
				}


		}
	}

	if ( numalive==0 )
	{
		writegamemessage(alldeaddat2) ;
		while ( 1 )	; 

	}
	checkmoongate() ;       

}

void initcombatscreen(UBYTE n,UBYTE playertile)
{
	UBYTE tochange ;
	UBYTE p,q ;
	UBYTE done ;
	UBYTE isship ;


	if ( (inside==0x21) && (!baddemeanor) )
	{
		baddemeanor++ ;
		for ( p=0 ; p<32 ; p++ )
		{
			if ( (monsters[p].tile==0x18)||(monsters[p].tile==0x19) )
				monsters[p].attribs = 0x11 ;
		}


	}

	stoptimebattle = 0 ;
	if ( make_rnd(0)&0x80U )
		masskill = 1 ;
	else
		masskill = 0 ;

	waitpadup() ;

	if ( inside==0x22 )
		monstertile = n ;
	else
		monstertile	= monsters[n].tile ;

	if ( transport==1 )
	{
		if ( monstertile==0x15 )
		{
			mapnum=0x08 ;
			playerslocs = 0x01 ;
			monsterslocs = 0x01 ;
		}
		else
			if ( (monstertile==0x13) ||(monstertile==0x14) )
		{
			mapnum=0x06 ;
			playerslocs = 0x02 ;
			monsterslocs = 0x00 ;
		}
		else
		{
			mapnum=0x07 ;
			playerslocs = 0x01 ;
			monsterslocs = 0x02 ;
		}
	}
	else
	{
		if ( monstertile==0x15 )
		{
			mapnum=0x00 ;
			playerslocs = 0x00 ;
			monsterslocs = 0x01 ;
		}
		else
			if ( (monstertile==0x13) ||(monstertile==0x14) )
		{
			mapnum=0x05 ;
			playerslocs = 0x00 ;
			monsterslocs = 0x01 ;
		}
		else
			if ( playertile==0x05 )
		{
			mapnum=0x01 ;
			playerslocs = 0x00 ;
			monsterslocs = 0x02 ;
		}
		else
			if ( playertile==0x06 )
		{
			mapnum=0x03 ;
			playerslocs = 0x00 ;
			monsterslocs = 0x02 ;
		}
		else
			if ( (playertile==0x0B) || ( monstertile==0x0B ) )
		{
			mapnum=0x02 ;
			playerslocs = 0x00 ;
			monsterslocs = 0x02 ;
		}
		else
		{
			mapnum=0x04 ;
			playerslocs = 0x00 ;
			monsterslocs = 0x02 ;
		}
	}


	if ( LCDC_REG&0x10 )
	{
		vidbase = (unsigned char*)0x9800 ;
		VBK_REG=1 ;
		set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
		VBK_REG=0 ;
		set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	}
	else
	{
		vidbase = (unsigned char*)0x9C00 ;
		VBK_REG=1 ;
		set_data2((unsigned char*)0x9C00,(unsigned char*)0x9800,0x400UL) ;
		VBK_REG=0 ;
		set_data2((unsigned char*)0x9C00,(unsigned char*)0x9800,0x400UL) ;
	}


	for ( p = 0 ; p<11 ; p++ )
		set_data2(vidbase+(32L*((UWORD)p+1L))+1L,(unsigned char*)battlemaps+((UWORD)p*11L)+((UWORD)mapnum*121UL),11L) ;

	VBK_REG=1 ;

	for ( p = 0 ; p<11 ; p++ )
	{
		for ( q = 0 ; q<11 ; q++ )
			*((unsigned char*)screenbuf3+(UWORD)q) = *(tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)p*11L)+(UWORD)q+((UWORD)mapnum*121UL))));
		set_data2(vidbase+(32L*((UWORD)p+1L))+1L,(unsigned char*)screenbuf3,11L) ;
	}

	VBK_REG=0 ;


	numbaddies = 0 ;
	numgoodies = 0 ;
	numalive = 0 ;

	for ( p=0 ; p < 4 ; p++ )
	{
		if ( players[p].inparty )
		{
			numgoodies++ ;
			if ( players[p].status<2 )
			{
				numalive++ ;
				players[p].x = *(playerscoords+(UWORD)(playerslocs<<3)+(UWORD)(p<<1)) ;
				players[p].y = *(playerscoords+(UWORD)(playerslocs<<3)+(UWORD)(p<<1)+1L) ;
				switch ( players[p].skill )
				{
					case 0 : players[p].tile = 0x1C ; break ;
					case 1 : players[p].tile = 0x1A ; break ;
					case 2 : players[p].tile = 0x1B ; break ;
					case 3 : players[p].tile = 0x1B ; break ;
					case 4 : players[p].tile = 0x1A ; break ;
					case 5 : players[p].tile = 0x1C ; break ;
					case 6 : players[p].tile = 0x17 ; break ;
					case 7 : players[p].tile = 0x1A ; break ;
					case 8 : players[p].tile = 0x5C ; break ;
					case 9 : players[p].tile = 0x1D ; break ;
					case 10 : players[p].tile = 0x1C ; break ;
					default : players[p].tile = 0x1A ; break ;
				}
				set_data2(vidbase+(32L*((UWORD)(players[p].y)+1L))+(UWORD)players[p].x+1L,
						  (unsigned char*)&(players[p].tile),1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[p].y)+1L))+(UWORD)players[p].x+1L,
						  tile_palettes+(UWORD)(players[p].tile),1L) ;
				VBK_REG=0 ;

			}
		}
	}

	isship = 0 ;

	if ( monstertile==0x15 )
	{
		monstertile = 0x1D ;
		isship = 1 ;
	}

	switch ( monstertile )
	{
		case 0x16 : monsterstat = 0x00 ; break ;
		case 0x17 : monsterstat = 0x01 ; break ;
		case 0x1E : monsterstat = 0x02 ; break ;
		case 0x1F : monsterstat = 0x03 ; break ;
		case 0x5C : monsterstat = 0x04 ; break ;
		case 0x1D : monsterstat = 0x05 ; break ;
		case 0x1B : monsterstat = 0x06 ; break ;
		case 0x20 : monsterstat = 0x07 ; break ;
		case 0x0D : monsterstat = 0x08 ; break ;
		case 0x1A : monsterstat = 0x09 ; break ;
		case 0x21 : monsterstat = 0x0A ; break ;
		case 0x1C : monsterstat = 0x0B ; break ;
		case 0x22 : monsterstat = 0x0C ; break ;
		case 0x23 : monsterstat = 0x0D ; break ;
		case 0x13 : monsterstat = 0x0E ; break ;
		case 0x14 : monsterstat = 0x0F ; break ;
		case 0x18 : monsterstat = 0x10 ; break ;
		case 0x24 : monsterstat = 0x11 ; break ;
		case 0x0B : monsterstat = 0x12 ; break ;
		case 0x19 : monsterstat = 0x13 ; break ;
		default   : monsterstat = 0x03 ; break ;

	}
	monsterpower = *(monsterstatdat+((UWORD)(monsterstat<<2))+2L) ;
	monsterexp = *(monsterstatdat+((UWORD)(monsterstat<<2))) ;
	monsterattrib = *(monsterstatdat+((UWORD)(monsterstat<<2))+3L) ;

	for ( p=0 ; p < 8 ; p++ )
	{
		baddies[p].x = *(monsterscoords+((UWORD)(monsterslocs<<4))+(UWORD)(p<<1)) ;
		baddies[p].y = *(monsterscoords+((UWORD)(monsterslocs<<4))+(UWORD)(p<<1)+1L) ;
		baddies[p].hp = make_rnd(monsterpower+1) | 0x0F ;

		if ( extragame != 0 )
		{
			if ( baddies[p].hp < 220 )
				baddies[p].hp += 30 ;
		}


	}
	for ( p=0 ; p < 8 ; p++ )
	{
		tochange = make_rnd(8) ;
		memcpy((unsigned char*)&(baddies[8]),(unsigned char*)&(baddies[p]),3L) ;
		memcpy((unsigned char*)&(baddies[p]),(unsigned char*)&(baddies[tochange]),3L) ;
		memcpy((unsigned char*)&(baddies[tochange]),(unsigned char*)&(baddies[8]),3L) ;

	}

	if ( extragame != 0 )
	{
		if ( inside==0x21 )
		{
			if ( monstertile == 0x18 )
				numbaddies = 8 ;
			else
				if ( ( peermap <= 0x07 ) )
			{
				numbaddies = 8 ;
			}
			else
				if ( ( ingenerator ) || ( peermap == 15 ) )
				numbaddies = make_rnd(8)+1 ;
			else
				if ( isship == 1 )
				numbaddies = make_rnd(8)+1 ;
			else
				numbaddies = 1 ;
		}
		else
			numbaddies = make_rnd(8)+1 ;
	}
	else
	{
		if ( inexodus )
			numbaddies=8 ;
		else
			if ( inside==0x21 )
			if ( monstertile==0x18 )
				numbaddies=8 ;
			else
				if ( (peermap==12) )
				numbaddies= make_rnd(8)+1;
			else
				numbaddies = 1 ;
		else
			numbaddies= make_rnd(8)+1;
	}

	for ( p=0 ; p<numbaddies ; p++ )
	{
		set_data2(vidbase+(32L*((UWORD)(baddies[p].y)+1L))+(UWORD)baddies[p].x+1L,
				  (unsigned char*)&(monstertile),1L) ;
		VBK_REG=1 ;
		set_data2(vidbase+(32L*((UWORD)(baddies[p].y)+1L))+(UWORD)baddies[p].x+1L,
				  tile_palettes+(UWORD)(monstertile),1L) ;
		VBK_REG=0 ;

	}

	if ( LCDC_REG&0x10 )
		LCDC_REG &= 0xEF ;	//select $9800-$9BFF
	else
		LCDC_REG |= 0x10 ;	//select $9C00-$9FFF

	writegamemessage(conflictdat) ;
	if ( (monstertile>=0x1D)&&(monstertile<=0x24)&&(playery&0x01) )
		memcpy(screenbuf3,monsternames+(((UWORD)((2*(monstertile-0x1D))+(playerx&0x01)))*12L),12L) ;
	else
		memcpy(screenbuf3,tiledescdat+(((UWORD)(monstertile))*12L),12L)	;
	for ( p=12 ; (p>0)&&(screenbuf3[p-1]==0x5D) ; p-- )
		;  //empty loop


	if ( (p<12) && (screenbuf3[p-1]!=('S'+0x1D)) )
		screenbuf3[p] = 'S'+0x1D ;
	writegamemessage(screenbuf3) ;
	writegamemessage(press_a_dat) ;
}
unsigned char dirarr2[] = {
	'N'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

UBYTE getdir4()
{
	UBYTE dir, p, keys, dir2 ;
/*   
   memset(screenbuf3,0x5D,12L) ;
   for (p = 0 ; p<5 ; p++)
	  set_bkg_tiles2(0,p+13,12,1,(unsigned char*)screenbuf3) ;

   memset(screenbuf3,0x00,12L) ;
   VBK_REG=1 ;
   
   for (p = 0 ; p<5 ; p++)
	  set_bkg_tiles2(0,p+13,12,1,(unsigned char*)screenbuf3) ;
   
   VBK_REG=0 ;

   set_bkg_tiles2(1,15,9,1,dirdat4);
   set_bkg_tiles2(1,16,9,1,dirdat4+9L);
*/  
	writegamemessage(dirdat4) ;

	waitpadup() ;
	dir = 0 ;
	while ( 1 )
	{
		keys = joypad() ;
		if ( keys&J_UP )
		{
			dir = 1 ;
			dir2 = 1 ;
			break ;
		}
		if ( keys&J_DOWN )
		{
			dir = 2 ;
			dir2 = 7 ;
			break ;
		}
		if ( keys&J_RIGHT )
		{
			dir = 3 ;
			dir2 = 5 ;
			break ;
		}
		if ( keys&J_LEFT )
		{
			dir = 4 ;
			dir2 = 3 ;
			break ;
		}
		if ( keys&J_B )
		{
			break ;
		}
	}    

	if ( dir )
	{
		writegamemessage(dirarr2+(((UWORD)(dir-1))*12L)) ;
	}

	waitpadup() ;
	return dir2 ;


}

UBYTE dolook()
{
	UBYTE dir,p ;
	unsigned char atile ;

	dir = getdir4() ;
	if ( !dir )
	{
		//writegamemessage(canceldat2) ;
		return 0 ;
	}

	get_bkg_tiles2(5,5,3,3,screenbuf3) ;
	atile = *(screenbuf3+(UWORD)dir) ;

	if ( ( atile == 58 ) && ( extragame != 0 ) )
		return dir|0x20 ;

	if ( (atile>=0x1D)&&(atile<=0x24)&&(playery&0x01) )
		memcpy(screenbuf3,monsternames+(((UWORD)((2*(atile-0x1D))+(playerx&0x01)))*12L),12L) ;
	else
		memcpy(screenbuf3,tiledescdat+(((UWORD)(atile))*12L),12L) ;
	for ( p=12 ; (p>0)&&(screenbuf3[p-1]==0x5D) ; p-- )
		;  //empty loop


	writegamemessage(screenbuf3) ;
	return 1 ;
}
