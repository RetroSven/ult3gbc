#include <gb.h>
#include "u3.h"

#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

extern UBYTE blinkdelay ;
extern UBYTE tileon ;
extern UBYTE currplayer ;

extern BATTLEMONSTERS baddies[9] ;
//extern BATTLEPLAYERS  goodies[4] ;
extern PLAYER players[] ;
extern UBYTE monsterattrib ;
extern UBYTE monsterpower ;

extern UBYTE numbaddies; 
extern UBYTE numgoodies; 
extern UBYTE numalive ;

extern UBYTE stoptimebattle ;
extern UBYTE monstertile ;

extern unsigned char *vidbase ;

extern UBYTE delayscroll ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern unsigned char screenbuf3[] ;
extern UBYTE mapnum ;


#define SCROLLDELAY 20

unsigned char notallowed2[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'D'+0x1D,0x82, 
} ;

unsigned char nopowderdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'W'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,0x82,0x5d
} ;

unsigned char battlecommands[] = {
	'A'+0x1D,'T'+0x1D,'T'+0x1D,'A'+0x1D,'C'+0x1D,'K'+0x1D,0x5D,
	'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,
	'P'+0x1D,'O'+0x1D,'W'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,0x5D,
	'S'+0x1D,'T'+0x1D,'A'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x5D,
	'V'+0x1D,'O'+0x1D,'L'+0x1D,'U'+0x1D,'M'+0x1D,'E'+0x1D,0x5D
};

unsigned char passdat[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x79,0x5D,'P'+0x1D,'A'+0x1D,'S'+0x1D,'S'+0x1D
} ;

unsigned char readydat[] = {
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D 
} ;

unsigned char readieddat[] = {
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D

} ;

unsigned char weaponsdat2[] = {
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,'S'+0x1D,0X5D,0X5D,0X5D,
	'D'+0x1D,'A'+0x1D,'G'+0x1D,'G'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,0X5D,
	'M'+0x1D,'A'+0x1D,'C'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'S'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0X5D,0X5D,0X5D,
	'A'+0x1D,'X'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,0X5D,0X5D,
	'B'+0x1D,'O'+0x1D,'W'+0x1D,0X5D,0X5D,0X5D,0X5D,0X5D,
	'S'+0x1D,'W'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,0X5D,0X5D,0X5D,
	0x7A,'H'+0x1D,0X5D,'S'+0x1D,'W'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,
	0x91,0x7A,0X5D,'A'+0x1D,'X'+0x1D,'E'+0x1D,0X5D,0X5D,
	0x91,0x7A,0X5D,'B'+0x1D,'O'+0x1D,'W'+0x1D,0X5D,0X5D,
	0x91,0x7A,0X5D,'S'+0x1D,'W'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,
	'G'+0x1D,'L'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,'S'+0x1D,0X5D,0X5D,
	0x91,0x7C,0X5D,'A'+0x1D,'X'+0x1D,'E'+0x1D,0X5D,0X5D,
	0x91,0x7C,0X5D,'B'+0x1D,'O'+0x1D,'W'+0x1D,0X5D,0X5D,
	0x91,0x7C,0X5D,'S'+0x1D,'W'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'T'+0x1D,'I'+0x1D,'C'+0x1D,0X5D,0X5D
};


unsigned char stats11[] = {
	'H'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	'E'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	'G'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	'S'+0x1D,'T'+0x1D,'R'+0x1D,0x8A,0x5d,0x5d,
	'I'+0x1D,'N'+0x1D,'T'+0x1D,0x8A,0x5d,0x5d,
	'G'+0x1D,'E'+0x1D,'M'+0x1D,0x8A,0x5d,0x5d,
	'P'+0x1D,'D'+0x1D,'R'+0x1D,0x8A,0x5d,0x5d,
	'W'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	'A'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,
	0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,
	'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'S'+0x1D,0x8A,
	0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,
	'C'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,'S'+0x1D,0x8A
} ;
unsigned char stats22[] = {
	0X5D,0x5d,'L'+0x1D,0x8A,0x5d,0x5d,
	0X5D,0x5d,'M'+0x1D,0x8A,0x5d,0x5d,
	'F'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,
	'D'+0x1D,'E'+0x1D,'X'+0x1D,0x8A,0x5d,0x5d,
	'W'+0x1D,'I'+0x1D,'S'+0x1D,0x8A,0x5d,0x5d,
	'K'+0x1D,'E'+0x1D,'Y'+0x1D,0x8A,0x5d,0x5d,
	'T'+0x1D,'O'+0x1D,'R'+0x1D,0x8A,0x5d,0x5d
};

unsigned char stats33[] = {
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,0x5d,'L'+0x1D,'I'+0x1D,'S'+0x1D,'T'+0x1D,
	'A'+0x1D,'R'+0x1D,'M'+0x1D,'O'+0x1D,'R'+0x1D,0X5D,0x5d,'L'+0x1D,'I'+0x1D,'S'+0x1D,'T'+0x1D
};
unsigned char stats44[] = {
	'A'+0x1D,'W'+0x1D,'A'+0x1D,'I'+0x1D,'T'+0x1D,'S'+0x1D,
	'J'+0x1D,'O'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D
};


unsigned char armorsdat2[] = {
	'S'+0x1D,'K'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'C'+0x1D,'L'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,0X5D,0X5D,0X5D,
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,
	'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,
	0x91,0x7A,0X5D,'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,
	0x91,0x7A,0X5D,'P'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'T'+0x1D,'I'+0x1D,'C'+0x1D,0X5D,0X5D,
	0X5D,0X5D,0X5D,0X5D,0X5D,0X5D,0X5D,0X5D,
	0X5D,0X5D,0X5D,0X5D,0X5D,0X5D,0X5D,0X5D
};
unsigned char sexes2[] = {
	'M'+0x1D,
	'F'+0x1D,
	'O'+0x1D
};

unsigned char races2[] = {
	'H'+0x1D,
	'E'+0x1D,
	'D'+0x1D,
	'F'+0x1D,
	'B'+0x1D
};

unsigned char classes2[] = {
	'A'+0x1D,
	'B'+0x1D,
	'C'+0x1D,
	'D'+0x1D,
	'F'+0x1D,
	'I'+0x1D,
	'L'+0x1D,
	'P'+0x1D,
	'R'+0x1D,
	'T'+0x1D,
	'W'+0x1D
};

unsigned char condcodes2[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};

unsigned char cardsdat2[] = {
	'D'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,
	'L'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5d,
	'S'+0x1D,'O'+0x1D,'L'+0x1D,0x5d,0x5d,
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5d
};

unsigned char marksdat2[] = {
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,
	'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x5d,
	'S'+0x1D,'N'+0x1D,'A'+0x1D,'K'+0x1D,'E'+0x1D,
	'K'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5d
};

unsigned char dungmenudat[] = {
	'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'E'+0x1D,'S'+0x1D,'C'+0x1D,'E'+0x1D,'N'+0x1D,'D'+0x1D,
	'G'+0x1D,'E'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
	'I'+0x1D,'G'+0x1D,'N'+0x1D,'I'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,
	'J'+0x1D,'O'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D, 
	'K'+0x1D,'L'+0x1D,'I'+0x1D,'M'+0x1D,'B'+0x1D,0x5D,0x5D,
	'M'+0x1D,'O'+0x1D,'D'+0x1D,'I'+0x1D,'F'+0x1D,'Y'+0x1D,0x5D, 
	'N'+0x1D,'E'+0x1D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D, 
	'O'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D, 
	'P'+0x1D,'E'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,0x5D, 
	'V'+0x1D,'O'+0x1D,'L'+0x1D,'U'+0x1D,'M'+0x1D,'E'+0x1D,0x5D, 
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
	'Y'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D, 
	'Z'+0x1D,'T'+0x1D,'A'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x5D
};

unsigned char mainmenudat[] = {
	'A'+0x1D,'T'+0x1D,'T'+0x1D,'A'+0x1D,'C'+0x1D,'K'+0x1D,0x5D, 
	'B'+0x1D,'O'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,0x5D, 
	'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'N'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D, 
	'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'E'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
	'J'+0x1D,'O'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'O'+0x1D,'O'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'D'+0x1D,'I'+0x1D,'F'+0x1D,'Y'+0x1D,0x5D, 
	'N'+0x1D,'E'+0x1D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D, 
	'O'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D, 
	'P'+0x1D,'E'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,0x5D, 
	'S'+0x1D,'T'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D, 
	'T'+0x1D,'A'+0x1D,'L'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D, 
	'U'+0x1D,'N'+0x1D,'L'+0x1D,'O'+0x1D,'C'+0x1D,'K'+0x1D,0x5D, 
	'V'+0x1D,'O'+0x1D,'L'+0x1D,'U'+0x1D,'M'+0x1D,'E'+0x1D,0x5D, 
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
	'X'+0x1D,'I'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'Y'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D, 
	'Z'+0x1D,'T'+0x1D,'A'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x5D
};

unsigned char menudescdat[] = {
	'A'+0x1D,'T'+0x1D,'T'+0x1D,'A'+0x1D,'C'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'B'+0x1D,'O'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,'V'+0x1D,'E'+0x1D,'S'+0x1D,'S'+0x1D,'E'+0x1D,'L'+0x1D, 
	'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'S'+0x1D,'P'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D, 
	'E'+0x1D,'N'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'N'+0x1D,'N'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D, 
	'G'+0x1D,'E'+0x1D,'T'+0x1D,0x5D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'R'+0x1D,'A'+0x1D,'D'+0x1D,'E'+0x1D,0x5D,'I'+0x1D,'T'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x5D, 
	'J'+0x1D,'O'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'O'+0x1D,'O'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'D'+0x1D,'I'+0x1D,'F'+0x1D,'Y'+0x1D,0x5D,'O'+0x1D,'R'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D, 
	'N'+0x1D,'E'+0x1D,'G'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D, 
	'O'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'P'+0x1D,'E'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,'T'+0x1D,0x5D,'G'+0x1D,'E'+0x1D,'M'+0x1D,0x5D, 
	'S'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D, 
	'S'+0x1D,'T'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'A'+0x1D,'L'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'U'+0x1D,'N'+0x1D,'L'+0x1D,'O'+0x1D,'C'+0x1D,'K'+0x1D,0x5D,'D'+0x1D,'O'+0x1D,'O'+0x1D,'R'+0x1D,0x5D, 
	'V'+0x1D,'O'+0x1D,'L'+0x1D,'U'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'M'+0x1D,'O'+0x1D,'R'+0x1D,0x5D,0x5D, 
	'X'+0x1D,'I'+0x1D,'T'+0x1D,0x5D,'V'+0x1D,'E'+0x1D,'S'+0x1D,'S'+0x1D,'E'+0x1D,'L'+0x1D,0x5D,0x5D, 
	'Y'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'Z'+0x1D,'T'+0x1D,'A'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;


void formatnumber4(UWORD num,UBYTE length)
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
		*((unsigned char*)screenbuf3+(UWORD)n) = ch ;


	}

}
/*
void writegamemessage3(unsigned char *msgdat)
{
   UBYTE q ;
   
   for (q=0 ; q < 4 ; q++)
   {
	  set_data2(vidbase+(32L*(q+13)),vidbase+(32L*(q+14)),12L) ;
   }
	
   set_data2(vidbase+(32L*17),msgdat,12L) ;
   
}
*/
void blink2()
{
	unsigned char ch ;


	disable_interrupts2() ; 
	if ( tileon )
	{
		if ( !--blinkdelay )
		{
			get_bkg_tiles2(players[currplayer].x+1,players[currplayer].y+1,1,1,&ch) ;
			set_data2(vidbase+(32L*((UWORD)(players[currplayer].y)+1L))+(UWORD)players[currplayer].x+1L,
					  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
					  (11L*((UWORD)(players[currplayer].y)))+(UWORD)players[currplayer].x,1L) ;
			VBK_REG=1 ;
			set_data2(vidbase+(32L*((UWORD)(players[currplayer].y)+1L))+(UWORD)players[currplayer].x+1L,
					  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
											  (11L*((UWORD)(players[currplayer].y)))+(UWORD)players[currplayer].x)),1L) ;
			VBK_REG=0 ;
			blinkdelay = 10 ;
			tileon=0 ;
		}
	}
	else
	{
		if ( !--blinkdelay )
		{
			set_data2(vidbase+(32L*((UWORD)(players[currplayer].y)+1L))+(UWORD)players[currplayer].x+1L,
					  (unsigned char*)&(players[currplayer].tile),1L) ;
			VBK_REG=1 ;
			set_data2(vidbase+(32L*((UWORD)(players[currplayer].y)+1L))+(UWORD)players[currplayer].x+1L,
					  tile_palettes+(UWORD)(players[currplayer].tile),1L) ;
			VBK_REG=0 ;
			blinkdelay = 20 ;
			tileon=1 ;
		}


	}

	enable_interrupts2() ;

	wait_vbl_done() ;

}

UBYTE checkmon(UBYTE px, UBYTE py)
{
	UBYTE p, found ;

	p=0 ;
	found = 0 ;

	while ( (p<numbaddies) && (!found) )
		if ( (baddies[p].x==px) && (baddies[p].y==py) )
			found++ ;
		else
			p++	;

	return found ;

}

UBYTE playerturn(UBYTE pnum)
{
	UBYTE joykeys,cmd ;
	UBYTE done,p ;
	unsigned char ch ;

	blinkdelay = 20 ;
	tileon=1 ;   
	currplayer = pnum ;
	done = 0 ;
	if ( players[pnum].status>1 )
		return 0 ;

	waitpadup() ;
	while ( !done )
	{
		blink2() ;
		joykeys = joypad() ;

		disable_interrupts2() ;
		if ( joykeys&J_UP )
		{
			get_bkg_tiles2(players[pnum].x+1,players[pnum].y,1,1,&ch) ;
			if ( (players[pnum].y>0) && ((tile_attribs[ch])&0x01) && (!checkmon(players[pnum].x, players[pnum].y-1)) )
			{
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
						  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x,1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
												  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x)),1L) ;
				VBK_REG=0 ;
				(players[pnum].y)-- ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)&(players[pnum].tile),1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(players[pnum].tile),1L) ;
				VBK_REG=0 ;
				movesfx(15,20,0) ;
				break ;

			}
			else
			{
				invalidmovesfx(80) ;

			}

		}

		if ( joykeys&J_DOWN )
		{
			get_bkg_tiles2(players[pnum].x+1,players[pnum].y+2,1,1,&ch) ;
			if ( (players[pnum].y<10) && ((tile_attribs[ch])&0x01) && (!checkmon(players[pnum].x, players[pnum].y+1)) )
			{
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
						  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x,1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
												  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x)),1L) ;
				VBK_REG=0 ;
				(players[pnum].y)++ ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)&(players[pnum].tile),1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(players[pnum].tile),1L) ;
				VBK_REG=0 ;
				movesfx(15,20,0) ;
				break ;

			}
			else
			{
				invalidmovesfx(80) ;

			}

		}

		if ( joykeys&J_RIGHT )
		{
			get_bkg_tiles2(players[pnum].x+2,players[pnum].y+1,1,1,&ch) ;
			if ( (players[pnum].x<10) && ((tile_attribs[ch])&0x01) && (!checkmon(players[pnum].x+1, players[pnum].y)) )
			{
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
						  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x,1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
												  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x)),1L) ;
				VBK_REG=0 ;
				(players[pnum].x)++ ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)&(players[pnum].tile),1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(players[pnum].tile),1L) ;
				VBK_REG=0 ;
				movesfx(15,20,0) ;
				break ;

			}
			else
			{
				invalidmovesfx(80) ;

			}

		}

		if ( joykeys&J_LEFT )
		{
			get_bkg_tiles2(players[pnum].x,players[pnum].y+1,1,1,&ch) ;
			if ( (players[pnum].x>0) && ((tile_attribs[ch])&0x01) && (!checkmon(players[pnum].x-1, players[pnum].y)) )
			{
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
						  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x,1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
												  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x)),1L) ;
				VBK_REG=0 ;
				(players[pnum].x)-- ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  (unsigned char*)&(players[pnum].tile),1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
						  tile_palettes+(UWORD)(players[pnum].tile),1L) ;
				VBK_REG=0 ;
				movesfx(15,20,0) ;
				break ;

			}
			else
			{
				invalidmovesfx(80) ;

			}

		}

		if ( joykeys&J_A )
		{
			done=1 ;
		}

		if ( joykeys&J_B )
		{
			memcpy(screenbuf3,passdat,12L); 
			screenbuf3[6] +=pnum ;
			writegamemessage(screenbuf3) ;
			waitpadup() ;
			break ;
		}
		enable_interrupts2() ;
	}

	waitpadup() ;
	blinkdelay = 1 ;
	tileon=0 ;   
	blink2() ;

	return done ;
}
void update_screen7()
{

	if ( delayscroll-- == 0 )
	{
		if ( ++mode4tiles==4 )
			mode4tiles=0 ;
		if ( ++mode8tiles==8 )
			mode8tiles=0 ;

		disable_interrupts2() ;
		set_bkg_data2(  0x00, 0x01, u3tiles+(UWORD)((UWORD)mode4tiles<<4) );
		set_bkg_data2(  0x0F, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x0FL)<<4) );
		set_bkg_data2(  0x26, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x26L)<<4) );
		set_bkg_data2(  0x2A, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x2AL)<<4) );
		set_bkg_data2(  0x32, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x32L)<<4) );
		enable_interrupts2() ;
		delayscroll = SCROLLDELAY ;
	}
}

UBYTE getmenuselection2(UBYTE numlines,unsigned char *menudata, UBYTE doblink)
{
	UBYTE p ;
	UBYTE currline, currpage ;
	UBYTE keys ;

	memset(screenbuf3,0x5d,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;
	for ( p=0 ; p<16;p++ )
	{
		set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,screenbuf3,7L); 
		VBK_REG=1 ;       
		set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,screenbuf3+7L,7L); 
		VBK_REG=0 ;       
	}

	if ( numlines>16 )
		for ( p=0 ; p<16 ; p++ )
			set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,menudata+((UWORD)p*7L),7L);
	else
		for ( p=0 ; p<numlines ; p++ )
			set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,menudata+((UWORD)p*7L),7L); 


	currline = 0 ;
	currpage = 0 ;
	memset(screenbuf3,0x04,7L) ;
	VBK_REG=1 ;      
	set_data2(vidbase+(32L*1L)+13L,screenbuf3,7L); 
	VBK_REG=0 ;      

	waitpadup() ;

	while ( 1 )
	{
		if ( doblink )
			blink2() ;
		keys = joypad() ;
		if ( keys&J_UP )
		{
			VBK_REG=1 ;    
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 
			if ( currline==0 )
				if ( numlines>16 )
					if ( currpage>0 )
						currline = numlines-17 ;
					else
						currline = 15 ;
				else
					currline = numlines -1 ;
			else
				currline-- ;
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3,7L); 
			VBK_REG=0 ;    
			waitpadup() ;

		}
		if ( keys&J_DOWN )
		{
			VBK_REG=1 ;    
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 

			if ( numlines>16 )
				if ( currpage>0 )
					if ( currline==numlines-17 )
						currline = 0 ;
					else
						currline++ ;
				else
					if ( currline==15 )
					currline = 0 ;
				else
					currline++ ;
			else
				if ( currline==numlines-1 )
				currline = 0 ;
			else
				currline++ ;
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3,7L); 
			VBK_REG=0 ;    
			waitpadup() ;


		}
		if ( (keys&J_LEFT)||(keys&J_RIGHT) )
		{
			if ( numlines>16 )
			{
				VBK_REG=1 ;     
				set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 
				currline = 0 ;
				set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3,7L); 
				VBK_REG=0 ;     
				memset(screenbuf3,0x5D,7L) ;
				if ( currpage==0 )
				{
					for ( p=0 ; p<numlines-16 ; p++ )
						set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,menudata+((UWORD)(p+16)*7L),7L); 
					for ( p=numlines-16 ; p<16 ; p++ )
						set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,screenbuf3,7L); 
					currpage = 1 ;
				}
				else
				{
					for ( p=0 ; p<16 ; p++ )
						set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,menudata+((UWORD)p*7L),7L); 
					currpage = 0 ;
				}
				memset(screenbuf3,0x04,7L) ;
				waitpadup() ;
			}


		}
		if ( keys&J_A )
		{
			waitpadup() ;      
			keys = 0 ;
			break ;
		}
		if ( keys&J_B )
		{
			waitpadup() ;      
			keys = 1 ;
			break ;
		}

	}



	VBK_REG=1 ;      
	set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 
	VBK_REG=0 ;      


	blinkdelay = 1 ;
	tileon=0 ;   
	if ( doblink )
		blink2() ;
	if ( keys )
		return 99 ;
	else
		if ( numlines>16 )
	{
		memset(screenbuf3,0x5d,12L) ;
		memcpy(screenbuf3,menudata+(((UWORD)(currpage*16 + currline))*7L),7L) ;
		writegamemessage(screenbuf3) ;
		return(currpage*16 + currline) ;
	}

	memset(screenbuf3,0x5d,12L) ;
	memcpy(screenbuf3,menudata+((UWORD)currline*7L),7L) ;
	writegamemessage(screenbuf3) ;

	return currline ;

}


UBYTE battlemainmenu()
{
	return getmenuselection2(6,battlecommands,1) ;   

}

unsigned char timestoppeddat[] = {
	'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'S'+0x1D,'T'+0x1D,'O'+0x1D,'P'+0x1D,'P'+0x1D,'E'+0x1D,'D'+0x1D, 
} ;

UBYTE powderbattle(UBYTE pnum)
{
	if ( players[pnum].powders )
	{
		stoptimebattle = 10 ;
		(players[pnum].powders)-- ;
		writegamemessage(timestoppeddat) ;
		return 1 ;
	}

	writegamemessage(nopowderdat) ;
	return 0 ;
}

unsigned char readygrid2[] = {
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,  //alchemist
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  //barbarian
	1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,  //cleric
	1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,  //druid
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  //fighter
	1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,  //illusionist
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  //lark
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  //paladin
	1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,  //ranger
	1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,  //thief
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,  //wizard


} ;

unsigned char noweapons7[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D,0x82U,0x5D
} ;

UBYTE doready(UBYTE pnum)
{
	UBYTE done,joykeys,currweapon,nextptr, olditem ;
	UBYTE lcv1 ;

	done=0 ;
	nextptr = 0 ;

	while ( nextptr<16 )
	{
		if ( (players[pnum].weapons)[nextptr] )
			break ;
		else
			nextptr++ ;

		if ( nextptr == 16 )
		{
			writegamemessage( noweapons7 ) ;
			return 0 ;
		}

	}

	writegamemessage(readydat) ;
	memset(screenbuf3,0x5d,12L) ;
	writegamemessage(screenbuf3) ;

	olditem = players[pnum].weapon ;

	currweapon = nextptr ;
	memset(screenbuf3,0x5D,12L) ;
	memcpy(screenbuf3,weaponsdat2+((UWORD)currweapon*8L),8L) ;

	disable_interrupts2() ;
	set_bkg_tiles2(0,17,12,1,screenbuf3) ;

	memset(screenbuf3,0x04,12L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(0,17,12,1,screenbuf3) ;
	VBK_REG=0 ;

	enable_interrupts2() ;

	waitpadup() ;
	while ( done==0 )
	{
		joykeys = joypad() ;
		if ( joykeys&J_RIGHT )
		{
			if ( currweapon==15 )
				nextptr = 0 ;
			else
				nextptr	= currweapon+1 ;

			while ( 1 )
			{
				if ( (players[pnum].weapons)[nextptr] )
					break ;
				else
					nextptr++ ;
				if ( nextptr==16 )
					nextptr=0 ;
			}

			currweapon = nextptr ;
			memset(screenbuf3,0x5D,12L) ;
			memcpy(screenbuf3,weaponsdat2+((UWORD)currweapon*8L),8L) ;
			disable_interrupts2() ;
			set_bkg_tiles2(0,17,12,1,screenbuf3) ;
			enable_interrupts2() ;


			waitpadup() ;
		}

		if ( joykeys&J_LEFT )
		{
			if ( currweapon==0 )
				nextptr = 15 ;
			else
				nextptr	= currweapon-1 ;

			while ( 1 )
			{
				if ( (players[pnum].weapons)[nextptr] )
					break ;
				else
					if ( nextptr==0 )
					nextptr=15 ;
				else
					nextptr-- ;
			}

			currweapon = nextptr ;
			memset(screenbuf3,0x5D,12L) ;
			memcpy(screenbuf3,weaponsdat2+((UWORD)currweapon*8L),8L) ;
			set_bkg_tiles2(0,17,12,1,screenbuf3) ;

			waitpadup() ;
		}

		if ( joykeys&J_B )
		{
			waitpadup() ;
			done=2 ;
		}

		if ( joykeys&J_A )
		{
			waitpadup() ;
			done=1 ;

		}
	}

	memset(screenbuf3,0x00,12L);
	VBK_REG=1 ;
	set_bkg_tiles2(0,17,12,1,screenbuf3) ;
	VBK_REG=0 ;

	if ( done==2 )
		return 0 ;

	if ( *(readygrid2+ ((UWORD)((players[pnum].skill)*16)) + (UWORD)currweapon)==0 )
	{
		writegamemessage(notallowed2) ;

	}
	else
	{

		writegamemessage(readieddat) ;
		players[pnum].weapon = currweapon ;

		(players[pnum].weapons[currweapon])-- ;
		(players[pnum].weapons[olditem])++ ;
	}

	return 1 ;

}

void dostats(UBYTE which)
{
	UBYTE n, currarmor, currweapon, joykeys, done ;
	UBYTE currsel,nextptr ;
	unsigned char *vidbase2 ;

	if ( LCDC_REG&0x08 )   //select $9C00-$9FFF
		vidbase2 = (unsigned char*)0x9800 ;
	else
		vidbase2 = (unsigned char*)0x9C00 ;


	disable_interrupts2() ;

	memset(screenbuf3,0x5DU,32UL) ;

	for ( n = 0 ; n<18 ; n++ )
		set_data2(vidbase2+((UWORD)n*32UL),screenbuf3,20UL) ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf3,0x00U,32UL) ;
	for ( n = 0 ; n<18 ; n++ )
		set_data2(vidbase2+((UWORD)n*32UL),screenbuf3,20UL) ;
	VBK_REG = 0;		// select palette bank 

	set_data2(vidbase2,players[which].name,0x07UL) ;


	memset(screenbuf3,0x3AU,32UL) ;
	set_data2(vidbase2+(32L*17UL),screenbuf3,32L) ;
	set_data2(vidbase2+(32L*31UL),screenbuf3,32L) ;
	for ( n=0 ; n<18 ; n++ )
	{
		set_data2(vidbase2+19UL+(32L*(UWORD)n),screenbuf3,1L) ;
		set_data2(vidbase2+31UL+(32L*(UWORD)n),screenbuf3,1L) ;


	}
	SCX_REG = 0xFC ;
	SCY_REG = 0xFC ;

	for ( n=1 ; n<15 ; n++ )
		set_data2(vidbase2+(32L*(UWORD)n),stats11+((UWORD)(n-1)*6L),6L) ;

	for ( n=0 ; n<8 ; n++ )
		set_data2(vidbase2+0x0DUL+(32L*(UWORD)n),stats22+((UWORD)n*6L),6L) ;

	set_data2(vidbase2+4UL+(32L*10L),stats33,11L) ;
	set_data2(vidbase2+4UL+(32L*11L),stats33+11L,11L) ;

	if ( players[which].inparty )
		set_data2(vidbase2+0x0DUL+(32L*3L),stats44+6L,6L) ;
	else
		set_data2(vidbase2+0x0DUL+(32L*3L),stats44,6L) ;

	set_data2(vidbase2+2UL+(8L*32L),weaponsdat2+(8L*(UWORD)players[which].weapon),8L) ;
	set_data2(vidbase2+2UL+(9L*32L),armorsdat2+(8L*(UWORD)players[which].armor),8L) ;

	formatnumber4(players[which].currHP,4) ;
	screenbuf3[4] = 0x92 ;
	set_data2(vidbase2+2UL+(1L*32L),screenbuf3,5L) ;

	formatnumber4(players[which].maxHP,4) ;
	set_data2(vidbase2+7UL+(1L*32L),screenbuf3,4L) ;

	set_data2(vidbase2+0x0BUL+(0L*32L),condcodes2+(UWORD)players[which].status,1L) ;

	formatnumber4( players[which].food,4) ;
	set_data2(vidbase2+0x0FUL+(2L*32L),screenbuf3,4L) ;

	formatnumber4( players[which].gold,4) ;
	set_data2(vidbase2+2UL+(3L*32L),screenbuf3,4L) ;

	formatnumber4( (UWORD)players[which].magic,2) ;
	set_data2(vidbase2+0x11UL+(1L*32L),screenbuf3,2L) ;
	formatnumber4( ((UWORD)(players[which].level)),2) ;
	set_data2(vidbase2+0x11UL+(0L*32L),screenbuf3,2L) ;

	formatnumber4( players[which].exp,4) ;
	set_data2(vidbase2+0x02UL+(2L*32L),screenbuf3,4L) ;

	formatnumber4( (UWORD)players[which].str,2) ;
	set_data2(vidbase2+0x04UL+(4L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].dex,2) ;
	set_data2(vidbase2+0x11UL+(4L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].intel,2) ;
	set_data2(vidbase2+0x04UL+(5L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].wis,2) ;
	set_data2(vidbase2+0x11UL+(5L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].gems,2) ;
	set_data2(vidbase2+0x04UL+(6L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].keys,2) ;
	set_data2(vidbase2+0x11UL+(6L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].powders,2) ;
	set_data2(vidbase2+0x04UL+(7L*32L),screenbuf3,2L) ;
	formatnumber4( (UWORD)players[which].torches,2) ;
	set_data2(vidbase2+0x11UL+(7L*32L),screenbuf3,2L) ;

	set_data2(vidbase2+0x08UL+(0L*32L),sexes2+((UWORD)players[which].sex),1L) ;
	set_data2(vidbase2+0x09UL+(0L*32L),races2+((UWORD)players[which].race),1L) ;
	set_data2(vidbase2+0x0AUL+(0L*32L),classes2+((UWORD)players[which].skill),1L) ;

	for ( n=0 ; n<4 ; n++ )
		if ( (players[which].markcard>>n)&0x01 )
			set_data2(vidbase2+0x07UL+(14L*32L)+((UWORD)(n&0x01)*6L)+((UWORD)(n&0x02)*16L),
					  cardsdat2+((UWORD)n*5L),5L) ;

	for ( n=0 ; n<4 ; n++ )
		if ( (players[which].markcard>>(4+n))&0x01 )
			set_data2(vidbase2+0x07UL+(12L*32L)+((UWORD)(n&0x01)*6L)+((UWORD)(n&0x02)*16L),
					  marksdat2+((UWORD)n*5L),5L) ;


	VBK_REG = 1;		// select palette bank 
	memset(screenbuf3,0x04U,32UL) ;
	set_data2(vidbase2+0x04UL+(32L*10L),screenbuf3,11L) ;
	VBK_REG = 0;		// select palette bank 

	done=0 ;
	currsel = 0 ; //weapon line selected
	currarmor = 99 ;
	currweapon = 99 ;    

	enable_interrupts2() ;

	if ( vidbase2==(unsigned char*)0x09800 )
		LCDC_REG &= 0xF7 ;	//select $9800-$9BFF
	else
		LCDC_REG |= 0x08 ;	//select $9C00-$9FFF

	waitpadup() ;
	while ( done==0 )
	{
		joykeys = joypad() ;
		if ( joykeys&J_RIGHT )
		{
			disable_interrupts2() ;
			if ( currsel==0 )  //weapon line
			{
				if ( currweapon==99 )
					nextptr = 0 ;
				else
					nextptr	= currweapon+1 ;

				while ( nextptr<16 )
					if ( (players[which].weapons)[nextptr] )
						break ;
					else
						nextptr++ ;

				if ( nextptr>=16 )
				{
					currweapon = 99 ;
					set_data2(vidbase2+0x04UL+(32L*10L),stats33,11L) ;
				}
				else
				{
					currweapon = nextptr ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].weapons)[currweapon]+0x78 ;
					memcpy(screenbuf3+2L,weaponsdat2+((UWORD)currweapon*8L),8L) ;
					set_data2(vidbase2+0x04UL+(32L*10L),screenbuf3,11L) ;
				}


			}
			else
			{
				if ( currarmor==99 )
					nextptr = 0 ;
				else
					nextptr	= currarmor+1 ;

				while ( nextptr<8 )
					if ( (players[which].armors)[nextptr] )
						break ;
					else
						nextptr++ ;

				if ( nextptr>=8 )
				{
					currarmor = 99 ;
					set_data2(vidbase2+0x04UL+(32L*11L),stats33+11L,11L) ;
				}
				else
				{
					currarmor = nextptr ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].armors)[currarmor]+0x78 ;
					memcpy(screenbuf3+2L,armorsdat2+((UWORD)currarmor*8L),8L) ;
					set_data2(vidbase2+0x04UL+(32L*11L),screenbuf3,11L) ;
				}


			}
			enable_interrupts2() ;         

			waitpadup() ;
		}

		if ( joykeys&J_LEFT )
		{
			disable_interrupts2() ;
			if ( currsel==0 )  //weapon line
			{
				if ( currweapon==99 )
					nextptr = 16 ;
				else
					nextptr	= currweapon ;

				while ( nextptr>0 )
					if ( (players[which].weapons)[nextptr-1] )
						break ;
					else
						nextptr-- ;

				if ( nextptr==0 )
				{
					currweapon = 99 ;
					set_data2(vidbase2+0x04UL+(32L*10L),stats33,11L) ;
				}
				else
				{
					currweapon = nextptr-1 ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].weapons)[currweapon]+0x78 ;
					memcpy(screenbuf3+2L,weaponsdat2+((UWORD)currweapon*8L),8L) ;
					set_data2(vidbase2+0x04UL+(32L*10L),screenbuf3,11L) ;
				}


			}
			else
			{
				if ( currarmor==99 )
					nextptr = 8 ;
				else
					nextptr	= currarmor ;

				while ( nextptr>0 )
					if ( (players[which].armors)[nextptr-1] )
						break ;
					else
						nextptr-- ;

				if ( nextptr==0 )
				{
					currarmor = 99 ;
					set_data2(vidbase2+0x04UL+(32L*11L),stats33+11L,11L) ;
				}
				else
				{
					currarmor = nextptr-1 ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].armors)[currarmor]+0x78 ;
					memcpy(screenbuf3+2L,armorsdat2+((UWORD)currarmor*8L),8L) ;
					set_data2(vidbase2+0x04UL+(32L*11L),screenbuf3,11L) ;
				}


			}
			enable_interrupts2() ;         
			waitpadup() ;
		}

		if ( (joykeys&J_UP)||(joykeys&J_DOWN) )
		{
			disable_interrupts2() ;
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf3,0x00U,32UL) ;
			set_data2(vidbase2+0x04UL+(32L*(10L+(UWORD)currsel)),screenbuf3,11L) ;
			VBK_REG = 0;	 // select palette bank 

			if ( currsel==0 )
				currsel=1;
			else
				currsel	= 0 ;

			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf3,0x04U,32UL) ;
			set_data2(vidbase2+0x04UL+(32L*(10L+(UWORD)currsel)),screenbuf3,11L) ;
			VBK_REG = 0;	 // select palette bank 
			enable_interrupts2() ;         

			waitpadup() ;

		}

		if ( joykeys&J_B )
		{
			done = 99 ;	 //cancel, backup
			waitpadup() ;
			break ;
		}
	}    


	disable_interrupts2() ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf3,0x00U,32UL) ;
	set_data2(vidbase2+0x04UL+(32L*(10L+(UWORD)currsel)),screenbuf3,11L) ;
	VBK_REG = 0;		// select palette bank 

	SCX_REG = 0x00 ;
	SCY_REG = 0x00 ;
	if ( vidbase2==(unsigned char*)0x09800 )
	{
		set_data2(vidbase2,(unsigned char*)0x9C00,0x400) ;
		VBK_REG=1 ;
		set_data2(vidbase2,(unsigned char*)0x9C00,0x400) ;
		VBK_REG=0 ;
		LCDC_REG |= 0x08 ;	//select $9C00-$9FFF
	}
	else
	{
		set_data2(vidbase2,(unsigned char*)0x9800,0x400) ;
		VBK_REG=1 ;
		set_data2(vidbase2,(unsigned char*)0x9800,0x400) ;
		VBK_REG=0 ;
		LCDC_REG &= 0xF7 ;	//select $9800-$9BFF
	}

	enable_interrupts2() ;
}

