#include <gb.h>
#include "u3.h"

#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

extern MONSTER monsters[] ;
extern PLAYER players[] ;

extern UBYTE delayscroll ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern unsigned char screenbuf3[] ;
extern UBYTE inside ;

extern UBYTE extragame ;

extern UBYTE cheat_xray ;
extern UBYTE cheat_nofight ;
extern UBYTE cheat_nohurt ;
extern UBYTE cheat_noblock ;
extern UBYTE cheat_fullmp ;
extern UBYTE cheat_noclass ;

extern UBYTE inexodus ;

UBYTE blinkdelay ;
UBYTE tileon ;
UBYTE currplayer ;

UBYTE masskill ;

UBYTE stoptimebattle ;

unsigned char *vidbase ;
UBYTE mapnum ;


BATTLEMONSTERS baddies[9] ;
//BATTLEPLAYERS  goodies[4] ;
UBYTE numbaddies ;
UBYTE numgoodies ;
UBYTE numalive ;

#define SCROLLDELAY 20

UBYTE playerslocs ;
UBYTE monsterslocs ;
UBYTE monsterpower ;
UBYTE monsterexp ;
UBYTE monsterstat ;
UBYTE monsterattrib ;

unsigned char faildat[] = {
	'F'+0x1D,'A'+0x1D,'I'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d,0x5d,
} ;

unsigned char mptoolowdat2[] = {
	'M'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,'O'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'W'+0x1D,0x82,0x5d 
};

unsigned char whodat2[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char chardat2[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};

unsigned char charstat2[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};

unsigned char clericormagedat[] = {
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,
	'W'+0x1D,'I'+0x1D,'Z'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D
};


unsigned char killeddat[] = {
	'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x5D,0x78,0x78,'E'+0x1D,'X'+0x1D,'P'+0x1D
};

unsigned char dirdat[] = {
	'D'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x83,0x5d,0x5D
};

unsigned char hitmsg[] = {
	'H'+0x1D,'I'+0x1D,'T'+0x1D
};

unsigned char missmsg[] = {
	'M'+0x1D,'I'+0x1D,'S'+0x1D,'S'+0x1D,'E'+0x1D,'D'+0x1D
};
unsigned char clericspelldescdat[] = {
	0x5D,0x5D,'P'+0x1D,'O'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,'R'+0x1D,'I'+0x1D,0x5D,0x5D,0x5D,
	'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'U'+0x1D,'N'+0x1D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D,   
	0x5D,0x5D,0x5D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x79,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'A'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x7B,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'I'+0x1D,0x5D,
	0x5D,0x5D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x91,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x7D,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'E'+0x1D,'X'+0x1D,'C'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x79,0x5D,'F'+0x1D,'O'+0x1D,'E'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7E,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
//0x5D,'S'+0x1D,'U'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,
//0x5D,'R'+0x1D,'A'+0x1D,'I'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D,
//0x5D,0x5D,0x5D,0x5D,0x7E,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'Z'+0x1D,'X'+0x1D,'K'+0x1D,'U'+0x1D,'Q'+0x1D,'Y'+0x1D,'B'+0x1D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7F,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
//'A'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,0x5D,'S'+0x1D,'E'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'I'+0x1D,
//'R'+0x1D,'E'+0x1D,'T'+0x1D,'U'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,'A'+0x1D,'S'+0x1D,'H'+0x1D,'E'+0x1D,'D'+0x1D,
//0x5D,0x7F,0x7D,'M'+0x1D,'P'+0x1D,0x92,0x7D,'W'+0x1D,'I'+0x1D,'S'+0x1D,0x5D,0x5D
};

unsigned char clericspellsdat[] = {
//a) Pontori - attempts to kill skeletons, ghouls and zombies in combat
//c) Sanctu  - light healing
//h) Alcort - neutralize poison
//k) Sanctu Mani - powerful healing
//m) Excum - kill one enemy
//n) Surmandum - raise dead - if it fails he/she will become ashes
//o) Zxkuqyb - Smeg all foes
//p) Anju Sermani - return ashed person to life - costs 5 wisdom points
	'P'+0x1D,'O'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,'R'+0x1D,'I'+0x1D,
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,
	'A'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,'M'+0x1D,
	'E'+0x1D,'X'+0x1D,'C'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,
//'S'+0x1D,'U'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,
	'Z'+0x1D,'X'+0x1D,'K'+0x1D,'U'+0x1D,'Q'+0x1D,'Y'+0x1D,'B'+0x1D,
//'A'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,'S'+0x1D,'E'+0x1D,'R'+0x1D

//'U'+0x1D,'N'+0x1D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D,
//'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,
//'C'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,
//'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x91,0x5D,0x5D,
//'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,
//'A'+0x1D,'L'+0x1D,'I'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,0x5D,
//'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x91,0x5D,0x5D,
//'U'+0x1D,'N'+0x1D,0x89,'A'+0x1D,'S'+0x1D,'H'+0x1D,0x5D

};
unsigned char wizardspelldescdat[] = {
	0x5D,0x5D,0x5D,'R'+0x1D,'E'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,
	0x5D,'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'S'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'M'+0x1D,'I'+0x1D,'T'+0x1D,'T'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,
	0x5D,'H'+0x1D,'U'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x79,0x5D,'F'+0x1D,'O'+0x1D,'E'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'F'+0x1D,'U'+0x1D,'L'+0x1D,'G'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,
	'H'+0x1D,'U'+0x1D,'R'+0x1D,'T'+0x1D,0x91,0x5D,0x79,0x5D,'F'+0x1D,'O'+0x1D,'E'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7A,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'M'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,
	'H'+0x1D,'U'+0x1D,'R'+0x1D,'T'+0x1D,0x91,0x91,0x5D,0x79,0x5D,'F'+0x1D,'O'+0x1D,'E'+0x1D,
	0x5D,0x5D,0x5D,0x5D,0x7B,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'F'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,'D'+0x1D,'I'+0x1D,'V'+0x1D,'I'+0x1D,0x5D,0x5D,
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,'S'+0x1D,'P'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,
	0x5D,0x5D,0x5D,0x5D,0x7C,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'N'+0x1D,'O'+0x1D,'X'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'H'+0x1D,'U'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7D,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'D'+0x1D,'E'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,
	0x5D,'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x79,0x5D,'F'+0x1D,'O'+0x1D,'E'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7D,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'A'+0x1D,'L'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,
	0x5D,'S'+0x1D,'T'+0x1D,'O'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7E,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,'D'+0x1D,'A'+0x1D,'G'+0x1D,0x5D,'M'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,
	0x5D,'H'+0x1D,'U'+0x1D,'R'+0x1D,'T'+0x1D,0x91,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7E,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'N'+0x1D,'E'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,
	0x5D,'W'+0x1D,'E'+0x1D,'A'+0x1D,'K'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7F,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'K'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7F,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char wizardspellsdat[] = {
	'R'+0x1D,'E'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,
	'M'+0x1D,'I'+0x1D,'T'+0x1D,'T'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,
	'F'+0x1D,'U'+0x1D,'L'+0x1D,'G'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,
	'M'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,
	'F'+0x1D,'A'+0x1D,'L'+0x1D,'D'+0x1D,'I'+0x1D,'V'+0x1D,'I'+0x1D,
	'N'+0x1D,'O'+0x1D,'X'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,
	'D'+0x1D,'E'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'P'+0x1D,0x5D,
	'A'+0x1D,'L'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,
	'D'+0x1D,'A'+0x1D,'G'+0x1D,'M'+0x1D,'E'+0x1D,'N'+0x1D,'T'+0x1D,
	'N'+0x1D,'E'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'P'+0x1D,0x5D,
	'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D,'X'+0x1D
//a) Repond - attempt to smeg all orcs, goblins or trolls in combat.
//b) Mittar - single projectile attack
//f) Fulgar - powerful single projectile attack
//h) Mentar - single projectile attack - supposed to crush targets mind
//j) Fal Divi - cast this then you can cast a cleric spell
//k) Noxum - damages all foes
//l) Decorp - kill a single foe
//m) Altair - stops time
//n) Dag Mentar - damages multiple/all foes (book isn't clear)
//o) Necorp - weakens foes
//p)        - smegs all foes 
};

void formatnumber3(UWORD num,UBYTE length)
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

void showspelldesc(UBYTE spellnum, unsigned char *descdat)
{
	unsigned char screenbuf4[12] ;

	memset(screenbuf4,0x5D,12L) ;

	disable_interrupts2() ;

	set_bkg_tiles2( 0, 13, 12, 1, (unsigned char*)screenbuf4);
	set_bkg_tiles2( 0, 17, 12, 1, (unsigned char*)screenbuf4);

	set_bkg_tiles2(0,14,12,1,descdat+((UWORD)spellnum*36L)) ;
	set_bkg_tiles2(0,15,12,1,descdat+((UWORD)spellnum*36L)+12L) ;
	set_bkg_tiles2(0,16,12,1,descdat+((UWORD)spellnum*36L)+24L) ;

	enable_interrupts2() ;

}

void charscreen2(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	disable_interrupts2() ;

	for ( n=0 ; n<4 ; n++ )
	{
		set_data2((unsigned char*)0x9C0D+((((UWORD)(n+1+(loc<<2)))<<5)),screenbuf3,7L) ;
		set_data2((unsigned char*)0x980D+((((UWORD)(n+1+(loc<<2)))<<5)),screenbuf3,7L) ;
		//set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	}

	if ( (player->inparty)==0 )
		return ;

	//set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat2 );
	for ( n=0 ; n!=3 ; n++ )
	{
		set_data2((unsigned char*)(0x9C0D+((((UWORD)(2+n+(loc<<2))))<<5)),chardat2+(UWORD)n,1L) ;
		set_data2((unsigned char*)(0x980D+((((UWORD)(2+n+(loc<<2))))<<5)),chardat2+(UWORD)n,1L) ;
	}


	//set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );

	set_data2((unsigned char*)(0x980D+((((UWORD)(1+(loc<<2))))<<5)),player->name,7L) ;
	set_data2((unsigned char*)(0x9C0D+((((UWORD)(1+(loc<<2))))<<5)),player->name,7L) ;

//   return ;
	formatnumber3(player->currHP,4) ;

	set_data2((unsigned char*)(0x980E +((((UWORD)(2+(loc<<2))))<<5)),screenbuf3,4L) ;
	set_data2((unsigned char*)(0x9C0E +((((UWORD)(2+(loc<<2))))<<5)),screenbuf3,4L) ;


	//set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	//set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat2+(UWORD)player->status );
	set_data2((unsigned char*)(0x9813+((((UWORD)(2+(loc<<2))))<<5)),charstat2+(UWORD)player->status,1L) ;
	set_data2((unsigned char*)(0x9C13+((((UWORD)(2+(loc<<2))))<<5)),charstat2+(UWORD)player->status,1L) ;

	formatnumber3(player->food,4) ;

	set_data2((unsigned char*)(0x980E +((((UWORD)(3+(loc<<2))))<<5)),screenbuf3,4L) ;
	set_data2((unsigned char*)(0x9C0E +((((UWORD)(3+(loc<<2))))<<5)),screenbuf3,4L) ;

	//set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber3(player->magic,2) ;
	//set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );
	set_data2((unsigned char*)(0x980E +((((UWORD)(4+(loc<<2))))<<5)),screenbuf3,2L) ;
	set_data2((unsigned char*)(0x9C0E +((((UWORD)(4+(loc<<2))))<<5)),screenbuf3,2L) ;

	formatnumber3(player->level,2) ;
	set_data2((unsigned char*)(0x9812+((((UWORD)(4+(loc<<2))))<<5)),screenbuf3,2L) ;
	set_data2((unsigned char*)(0x9C12+((((UWORD)(4+(loc<<2))))<<5)),screenbuf3,2L) ;
	//set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	//set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );
	set_data2((unsigned char*)(0x9811+((((UWORD)(4+(loc<<2))))<<5)),screenbuf3,1L) ;
	set_data2((unsigned char*)(0x9C11+((((UWORD)(4+(loc<<2))))<<5)),screenbuf3,1L) ;

	enable_interrupts2() ;

}
/*
void writegamemessage2(unsigned char *msgdat)
{
   UBYTE q ;
   
   for (q=0 ; q < 4 ; q++)
   {
	  set_data2(vidbase+(32L*(q+13)),vidbase+(32L*(q+14)),12L) ;
   }
	
   set_data2(vidbase+(32L*17),msgdat,12L) ;
   
}
*/
void blink()
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


UBYTE getmenuselection(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
					   unsigned char *descptrdat)
{
	UBYTE p ;
	UBYTE currline ;
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

	for ( p=0 ; p<numlines ; p++ )
		set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,menudata+((UWORD)p*7L),7L); 

	currline = 0 ;
	memset(screenbuf3,0x04,7L) ;
	VBK_REG=1 ;      
	set_data2(vidbase+(32L*1L)+13L,screenbuf3,7L); 
	VBK_REG=0 ;      

	if ( descptr )
		descptr(currline,descptrdat) ;

	waitpadup() ;

	currline = 0 ;
	while ( 1 )
	{
		blink() ;
		keys = joypad() ;
		if ( keys&J_UP )
		{
			VBK_REG=1 ;    
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 
			if ( currline==0 )
				currline = numlines-1 ;
			else
				currline-- ;
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3,7L); 
			VBK_REG=0 ;    
			if ( descptr )
				descptr(currline,descptrdat) ;
			waitpadup() ;

		}
		if ( keys&J_DOWN )
		{
			VBK_REG=1 ;    
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 
			if ( currline==numlines-1 )
				currline = 0 ;
			else
				currline++ ;
			set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3,7L); 
			VBK_REG=0 ;    
			if ( descptr )
				descptr(currline,descptrdat) ;
			waitpadup() ;


		}
		if ( keys&J_A )
		{
			keys = 1 ;
			waitpadup() ;      
			break ;
		}
		if ( keys&J_B )
		{
			keys = 0 ;
			waitpadup() ;      
			break ;
		}

	}


	VBK_REG=1 ;      
	set_data2(vidbase+(32L*((UWORD)currline+1L))+13L,screenbuf3+7L,7L); 
	VBK_REG=0 ;      

	blinkdelay = 1 ;
	tileon=0 ;   
	blink() ;

	if ( keys==0 )
		return 99 ;

	memset(screenbuf3,0x5d,12L) ;
	memcpy(screenbuf3,menudata+((UWORD)currline*7L),7L) ;
	writegamemessage(screenbuf3) ;
	return currline ;

}


unsigned char dirarr[] = {
	'N'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

UBYTE getdir()
{
	UBYTE p, keys, dir ;

	/*
	memset(screenbuf3,0x5D,12L) ;
	for (p = 0 ; p<5 ; p++)
	   set_data2(vidbase+(32L*((UWORD)p+13L)),screenbuf3,12L) ;
 
	memset(screenbuf3,0x00,12L) ;
	VBK_REG=1 ;
	
	for (p = 0 ; p<5 ; p++)
	   set_data2(vidbase+(32L*((UWORD)p+13L)),screenbuf3,12L) ;
	
	VBK_REG=0 ;
	  */
	writegamemessage(dirdat) ;

	//set_data2(vidbase+(32L*15L)+1L,dirdat,9L) ;
	//set_data2(vidbase+(32L*16L)+1L,dirdat+9L,9L) ;

	waitpadup() ;
	while ( 1 )
	{
		blink() ;
		keys = joypad() ;
		if ( keys&J_UP )
		{
			dir = 1 ;
			waitpadup() ;
			break ;
		}
		if ( keys&J_DOWN )
		{
			dir = 2 ;
			waitpadup() ;
			break ;


		}
		if ( keys&J_RIGHT )
		{
			dir = 3 ;
			waitpadup() ;
			break ;


		}
		if ( keys&J_LEFT )
		{
			dir = 4 ;
			waitpadup() ;
			break ;


		}
		if ( keys&J_B )
		{
			dir = 0 ;
			waitpadup() ;
			break ;


		}




	}    
	if ( dir )
	{
		writegamemessage(dirarr+(((UWORD)(dir-1))*12L)) ;


	}

	blinkdelay = 1 ;
	tileon=0 ;   
	blink() ;
	return dir ;

}

void showmonsterhit(UBYTE mnum, UBYTE sprite)
{
	memset(screenbuf3,0x5D,12L); 
	memcpy(screenbuf3,hitmsg,3L) ;
	writegamemessage(screenbuf3) ;
	move_sprite( sprite, baddies[mnum].x*8+16,baddies[mnum].y*8+24 );
	playerhitsfx(170U) ;
	//delay(150) ;
	move_sprite( sprite, 0,0);


}


void killbaddie(UBYTE mnum, UBYTE pnum)
{
	UBYTE r ;
	unsigned char kmsg[12] ;

	formatnumber3((UWORD)monsterexp,2) ;
	memcpy(kmsg,killeddat,12L) ;
	memcpy(kmsg+7L,screenbuf3,2L) ;
	writegamemessage(kmsg) ;

	players[pnum].exp += (UWORD)monsterexp ;
	if ( players[pnum].exp > 9999L )
		players[pnum].exp = 9999L ;

	set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
			  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
			  (11L*((UWORD)(baddies[mnum].y)))+(UWORD)baddies[mnum].x,1L) ;
	VBK_REG=1 ;
	set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
			  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
									  (11L*((UWORD)(baddies[mnum].y)))+(UWORD)baddies[mnum].x)),1L) ;
	VBK_REG=0 ;
	for ( r=mnum ; r<numbaddies-1 ; r++ )
		memcpy((unsigned char*)&(baddies[r]),(unsigned char*)&(baddies[r+1]),3L) ;
	numbaddies-- ;

}

void monsterdamage(UBYTE pnum, UBYTE mnum, UBYTE sprite)
{
	UBYTE q, tohit, damage ;

	if ( extragame != 0 )
		damage = 120 ;
	else
		damage = 100 ;

	if ( (! ((inexodus==1) && (players[pnum].weapon!=0x0F))) && 
		 ((make_rnd(0)&0x80U)||(make_rnd(damage)<players[pnum].dex)) )
	{
		showmonsterhit(mnum,sprite) ;

		if ( (monsters[mnum].tile==0x19) || ( ( extragame != 0 ) && ( monsters[mnum].tile==0x18 ) ) )
			damage = 0 ;
		else
			damage = ((players[pnum].str)>>1) + make_rnd(((players[pnum].str)|0x01)+1) + (3*(players[pnum].weapon)) + 4 ;

		if ( baddies[mnum].hp > (UBYTE)damage )
			baddies[mnum].hp -= (UBYTE)damage ;
		else  //killed baddy
		{
			killbaddie(mnum,pnum) ;

		}

	}
	else //missed
	{
		memset(screenbuf3,0x5D,12L); 
		memcpy(screenbuf3,missmsg,6L) ;
		writegamemessage(screenbuf3) ;
		attackmisssfx(120U);

	}

}

UBYTE projectileattack(UBYTE pnum,UBYTE dir, UBYTE thesprite)
{
	UBYTE maxdir, p, projx, projy,q, found ;

	projx = players[pnum].x ;
	projy = players[pnum].y ;


	if ( dir==1 )
		maxdir=players[pnum].y ;
	else
		if ( dir==2 )
		maxdir = 10-players[pnum].y ;
	else
		if ( dir==3 )
		maxdir = 10 - players[pnum].x ;
	else
		maxdir = players[pnum].x ;

	for ( p=0,found=0 ; (p<maxdir) &&(!found) ; p++ )
	{
		if ( dir==1 )
			projy-- ;
		if ( dir==2 )
			projy++ ;
		if ( dir==3 )
			projx++ ;
		if ( dir==4 )
			projx-- ;

		move_sprite( thesprite, projx*8+16,projy*8+24 );
		delay(150) ;
		for ( q=0 ; (q < numbaddies)&&(!found) ; q++ )
			if ( (baddies[q].x==projx) && (baddies[q].y==projy) )
				found=1 ;


	}
	move_sprite( thesprite, 0,0) ;
	if ( found )
		return q;

	return 0 ;


}


UBYTE doattack(UBYTE pnum)
{
	UBYTE dir ;
	UBYTE projectile, weapon, attx, atty ;
	UBYTE p,found,q, themon ;

	if ( dir=getdir() )
	{
		attackswingsfx(120U) ; 
		weapon = players[pnum].weapon ;
		if ( (weapon==0x01) || (weapon==0x03) || (weapon==0x05) ||
			 (weapon==0x09) || (weapon==0x0D) )
			projectile = 1;
		else
			projectile = 0 ;

		if ( weapon==0x01 )
		{
			attx = players[pnum].x ;
			atty = players[pnum].y ;
			if ( (dir==1) && (atty) )
				atty-- ;
			if ( (dir==2) && (atty<10) )
				atty++ ;
			if ( (dir==3) && (attx<10) )
				attx++ ;
			if ( (dir==4) && (attx) )
				attx-- ;

			p=0 ;
			found = 0 ;
			while ( (p<numbaddies) && (!found) )
				if ( (baddies[p].x==attx) && (baddies[p].y==atty) )
					found = 1 ;
				else
					p++	;

			if ( found==1 )
				projectile = 0 ;

		}
		if ( projectile )
		{
			if ( themon=(projectileattack(pnum,dir,0)) )
				monsterdamage(pnum,themon-1,0) ;
			else
				attackmisssfx(120U)	;
			if ( weapon==1 )
			{
				if ( (players[pnum].weapons)[1] )
					((players[pnum].weapons)[1])-- ;
				else
				{
					players[pnum].weapon = 0 ;
					players[pnum].weapons[0] = 0 ;
				}

			}
		}
		else
		{
			if ( weapon!=0x01 )
			{
				attx = players[pnum].x ;
				atty = players[pnum].y ;
				if ( (dir==1) && (atty) )
					atty-- ;
				if ( (dir==2) && (atty<10) )
					atty++ ;
				if ( (dir==3) && (attx<10) )
					attx++ ;
				if ( (dir==4) && (attx) )
					attx-- ;

				p=0 ;
				found = 0 ;
				while ( (p<numbaddies) && (!found) )
					if ( (baddies[p].x==attx) && (baddies[p].y==atty) )
						found = 1 ;
					else
						p++	;
			}

			if ( found )
			{
				monsterdamage(pnum,p,0) ;

			}
			else  //missed- nothing there
			{
				memset(screenbuf3,0x5D,12L); 
				memcpy(screenbuf3,missmsg,6L) ;
				writegamemessage(screenbuf3) ;
				attackmisssfx(120U) ;
			}
		}
	}
	else
		return 0 ;

	return 1 ;   
}


void smegall(UBYTE percent, UBYTE kill, UBYTE damage, UBYTE pnum, UBYTE sprite)
{
	UBYTE q,r ;
	UBYTE amt ;

	for ( q=1 ; q<numbaddies+1 ; q++ )
	{
		if ( make_rnd(0)&0x03 )
		{
			showmonsterhit(q-1,sprite) ;
			if ( kill )
				baddies[q-1].hp = 0 ;
			else
			{
				amt = make_rnd(damage+1) ;
				if ( amt>baddies[q-1].hp )
					baddies[q-1].hp = 0 ;
				else
					baddies[q-1].hp	-= amt ;
			}
			if ( baddies[q-1].hp==0 )
			{
				killbaddie(q-1,pnum); 
				q-- ;
			}
		}


	}    

}

UBYTE choosechar()
{
	UBYTE p, keys, currchar ;

	for ( p=0 ; p<4;p++ )
		charscreen2(&players[p],p) ;

	writegamemessage(whodat2) ;

	memset(screenbuf3,0x04,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;

	disable_interrupts2() ;

	VBK_REG=1 ;
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1,7,1,screenbuf3) ;
	VBK_REG=0 ;

	enable_interrupts2() ;

	currchar=0 ;

	waitpadup() ;
	while ( 1 )
	{
		blink() ;
		keys = joypad() ;
		if ( keys&J_UP )
		{
			disable_interrupts2() ;
			VBK_REG=1 ;    
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3+7L) ;
			if ( currchar==0 )
				currchar = numgoodies-1 ;
			else
				currchar-- ;
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3) ;
			VBK_REG=0 ;    
			enable_interrupts2() ;
			waitpadup() ;

		}
		if ( keys&J_DOWN )
		{
			disable_interrupts2() ;
			VBK_REG=1 ;    
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3+7L) ;
			if ( currchar==numgoodies-1 )
				currchar = 0 ;
			else
				currchar++ ;
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3) ;
			VBK_REG=0 ;    
			enable_interrupts2() ;
			waitpadup() ;


		}
		if ( keys&J_A )
		{
			waitpadup() ;      
			keys=1 ;
			break ;
		}
		if ( keys&J_B )
		{
			keys=0 ;
			waitpadup() ;      
			break ;
		}



	}      

	disable_interrupts2() ;
	VBK_REG=1 ;
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3+7L) ;
	VBK_REG=0 ;
	enable_interrupts2() ;
	blinkdelay = 1 ;
	tileon=0 ;   
	blink() ;

	if ( keys==0 )
		currchar=99 ;

	return currchar ;
} 

void magiceffect(UBYTE spellnum)
{
	UBYTE p ;

	magicsfx1(20+(spellnum*5)) ;

	disable_interrupts2() ;

	VBK_REG=1 ;
	get_bkg_tiles2(1,1,11,11,(unsigned char*)0xBF80) ;

	for ( p=0 ; p < 121 ; p++ )
		if ( *((unsigned char*)0xBF80+(UWORD)p) < 4 )
			*((unsigned char*)0xBF80+(UWORD)p) += 4 ;

	set_bkg_tiles2(1,1,11,11,(unsigned char*)0xBF80) ;

	enable_interrupts2() ;

	magicsfx2(0,10+(spellnum*2),0) ;

	disable_interrupts2() ;
	for ( p=0 ; p < 121 ; p++ )
		if ( *((unsigned char*)0xBF80+(UWORD)p) > 3 )
			*((unsigned char*)0xBF80+(UWORD)p) -= 4 ;

	set_bkg_tiles2(1,1,11,11,(unsigned char*)0xBF80) ;
	VBK_REG=0 ;
	enable_interrupts2() ;

}

UBYTE castspell(UBYTE pnum, UBYTE mn)
{
	UBYTE dir ;
	UBYTE p,themon,q ;
	UBYTE clericmage ; //1=cleric, 2=mage, 0=no spells
	UBYTE spell ;
	UBYTE thechar ;
	UBYTE amt ;
	UBYTE cost, kill ;
	UBYTE mtile ;


	if ( inside==2 )
		mtile = mn ;
	else
		mtile = monsters[mn].tile ;


	memset(screenbuf3,0x5d,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;
	for ( p=0 ; p<16;p++ )
	{
		set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,screenbuf3,7L); 
		VBK_REG=1 ;       
		set_data2(vidbase+(32L*((UWORD)(p)+1L))+13L,screenbuf3+7L,7L); 
		VBK_REG=0 ;       
	}

	if ( cheat_fullmp!=0 )
		players[pnum].magic = 99 ;

	if ( cheat_noclass != 0 )
	{
		clericmage = getmenuselection(2,clericormagedat,NULL,NULL) ;
		if ( clericmage==99 )
			return 0;
		clericmage++ ;
	}
	else
	{

		if ( (players[pnum].skill==0) || (players[pnum].skill==6) || (players[pnum].skill==10) )
			clericmage = 2 ;
		else
			if ( (players[pnum].skill==2) || (players[pnum].skill==5) || (players[pnum].skill==7) )
			clericmage = 1 ;
		else
			if ( (players[pnum].skill==3) || (players[pnum].skill==8) )
		{
			clericmage = getmenuselection(2,clericormagedat,NULL,NULL) ;
			if ( clericmage==99 )
				return 0;
			clericmage++ ;
		}
		else
		{
			//clericmage=0 ;  //no magic msg
			return 0;
		}
	}


	if ( clericmage==1 )
	{
		spell = getmenuselection(6,clericspellsdat,showspelldesc,clericspelldescdat) ;
		if ( spell==0 )
			if ( (masskill==1)&&(mtile==0x1F) )
			{
				magiceffect(1) ;
				smegall(70,1,0,pnum,1) ;
				masskill = 0 ;
			}
			else
			{
				writegamemessage(faildat) ;
				attackmisssfx(120U) ;
				//fail

			}
		if ( (spell==1) || (spell==3) )
		{
			if ( spell==1 )
				cost =5 ;
			else
				cost = 50 ;
			if ( players[pnum].magic <cost )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				//mp too low ;
				return 0 ;

			}
			thechar = choosechar() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect((cost/5)+1) ;
			if ( spell==1 )
				amt = make_rnd(21)+10 ;
			else
				amt	= make_rnd(0x51)+0x14 ;

			players[thechar].currHP += (UBYTE)amt ;
			if ( players[thechar].currHP > players[thechar].maxHP )
				players[thechar].currHP = players[thechar].maxHP ;
			players[pnum].magic -= cost ;
			charscreen2(&players[pnum],pnum) ;
			charscreen2(&players[thechar],thechar) ;


		}
		if ( spell==2 )
		{
			if ( players[pnum].magic <35 )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect(8) ;
			if ( players[thechar].status==0x01 )
				players[thechar].status=0x00 ;
			players[pnum].magic -= 35 ;
			charscreen2(&players[pnum],pnum) ;
			charscreen2(&players[thechar],thechar) ;


		}
		if ( spell==4 )
		{
			if ( players[pnum].magic <60 )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			if ( dir=getdir() )
			{
				magiceffect(13) ;
				players[pnum].magic -= 60 ;
				if ( themon=(projectileattack(pnum,dir,1)) )
				{
					showmonsterhit(themon-1,1) ;
					killbaddie(themon-1,pnum) ;
				}

			}
		}
		/*
		if (spell==15)
		{
		   if (players[pnum].magic <65)
		   {
			  writegamemessage(mptoolowdat2) ;
			  return 0 ;
			  
		   }
		   thechar = choosechar() ;
		   if (thechar==99)
			  return 0 ;
		   magiceffect() ;
		   
		   players[pnum].magic -= 65 ;
		   if (  ((((UWORD)arand()&0x00FF)*100UL)/255UL)   <= (UWORD)(players[pnum].wis))
		   {
			  if (players[thechar].status==0x02) 
			  {
				 players[thechar].status=0x00 ;
				 numalive++ ;
			  }
		   }
		   else
		   {
			  if (players[thechar].status==0x02) 
				 players[thechar].status=0x03 ;
		   }
		   charscreen2(&players[pnum],pnum) ;
		   charscreen2(&players[thechar],thechar) ;
		}
		*/
		if ( spell==5 )
		{
			if ( players[pnum].magic <70 )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 70 ;
			magiceffect(15) ;
			smegall(100,1,0,pnum,1) ;

		}
		/*
		if (spell==17)
		{
		   if (players[pnum].magic <75)
		   {
			  writegamemessage(mptoolowdat2) ;
			  return 0 ;
			  
		   }
  
		   thechar = choosechar() ;
		   if (thechar==99)
			  return 0 ;
		   magiceffect() ;
		   
		   players[pnum].magic -= 75 ;
		   if (  ((((UWORD)arand()&0x00FF)*100UL)/255UL)   <= (UWORD)(players[pnum].wis))
		   {
			  if (players[thechar].status==0x03) 
			  {
				 players[thechar].status=0x00 ;
				 numalive++ ;
			  }
		   }
		   players[pnum].wis -= 5 ;
		   charscreen2(&players[pnum],pnum) ;
		   charscreen2(&players[thechar],thechar) ;
		}
		*/
		if ( spell==99 )
			return 0 ;


//a) Pontori - attempts to kill skeletons, ghouls and zombies in combat
//c) Sanctu  - light healing
//h) Alcort - neutralize poison
//k) Sanctu Mani - powerful healing
//m) Excum - kill one enemy
//n) Surmandum - raise dead - if it fails he/she will become ashes
//o) Zxkuqyb - Smeg all foes
//p) Anju Sermani - return ashed person to life - costs 5 wisdom points

	}
	else
	{
		spell = getmenuselection(11,wizardspellsdat,showspelldesc,wizardspelldescdat) ;
		if ( spell==99 )
			return 0 ;
		if ( spell==0 )
		{
			if ( (masskill==1)&&(mtile==0x1E) )
			{
				magiceffect(1) ;
				smegall(70,1,0,pnum,1) ;
				masskill=0 ;
			}
			else
			{
				writegamemessage(faildat) ;
				attackmisssfx(120U) ;
				//fail

			}
		}
		if ( (spell==1)||(spell==2)||(spell==3)||(spell==6) )
		{
			if ( spell==1 )
			{
				cost=5 ;
				amt=(make_rnd(0x29))|0x10 ;
				kill = 0 ;
			}
			if ( spell==2 )
			{
				cost=25 ;
				amt=0x4B ;
				kill = 0 ;
			}
			if ( spell==3 )
			{
				cost=35 ;
				amt=players[pnum].intel ;
				kill = 0 ;
			}
			if ( spell==6 )
			{
				cost=55 ;
				amt=99 ;
				kill = 1 ;
			}
			if ( players[pnum].magic <cost )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			if ( dir=getdir() )
			{
				players[pnum].magic -= cost ;
				magiceffect((cost/5)+1) ;
				if ( themon=(projectileattack(pnum,dir,1)) )
				{
					showmonsterhit(themon-1,1) ;
					if ( kill )
						killbaddie(themon-1,pnum) ;
					else
						if ( baddies[themon-1].hp > amt )
						baddies[themon-1].hp -= amt ;
					else  //killed baddy
						killbaddie(themon-1,pnum) ;
				}

			}
		}
		if ( spell==4 )	//castcleric
		{
			if ( players[pnum].magic <45 )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 45 ;
			q = players[pnum].skill ;
			players[pnum].skill = 2;
			castspell(pnum,mn) ;
			players[pnum].skill = q;
		}
		if ( (spell==5) || (spell==8) || (spell==10) ) //damage all
		{
			if ( spell==5 )
			{
				cost=50 ;
				amt=0x4B;
				kill = 0 ;
			}
			if ( spell==8 )
			{
				cost=65 ;
				amt=(players[pnum].intel)<<1 ;
				kill = 0 ;
			}
			if ( spell==10 )
			{
				cost=75 ;
				amt=200U ;
				kill = 1 ;
			}
			if ( players[pnum].magic <cost )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect((cost/5)+1) ;
			players[pnum].magic -= cost ;
			smegall(100,kill,amt,pnum,1) ;
		}
		if ( spell==7 )	//stop time
		{
			if ( extragame != 0 )
			{
				writegamemessage(faildat) ;
				attackmisssfx(120U) ;
				return 0 ;
			}

			if ( players[pnum].magic <60 )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect(13) ;
			players[pnum].magic -= 60 ;
			stoptimebattle = 10 ;
		}
		if ( spell==9 )	//weaken all
		{
			if ( players[pnum].magic <70 )
			{
				writegamemessage(mptoolowdat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 70 ;
			magiceffect(15) ;
			monsterpower = 10 ;
			for ( p=0 ; p<numbaddies ; p++ )
			{
				baddies[p].hp = 5 ;
				move_sprite( 0, baddies[p].x*8+16,baddies[p].y*8+24 );
				delay(150) ;
			}
			move_sprite( 0, 0,0) ;
		}
	}
//a) Repond - attempt to smeg all orcs, goblins or trolls in combat.
//b) Mittar - single projectile attack
//f) Fulgar - powerful single projectile attack
//h) Mentar - single projectile attack - supposed to crush targets mind
//j) Fal Divi - cast this then you can cast a cleric spell
//k) Noxum - damages all foes
//l) Decorp - kill a single foe
//m) Altair - stops time
//n) Dag Mentar - damages multiple/all foes (book isn't clear)
//o) Necorp - weakens foes
//p)        - smegs all foes 
	return 1 ;   
}

/*
void update_screen6()
{
   
   if (delayscroll-- == 0)
   {
	  if (++mode4tiles==4)
		 mode4tiles=0 ;
	  if (++mode8tiles==8)
		 mode8tiles=0 ;

	  set_bkg_data2(  0x00, 0x01, u3tiles+(UWORD)((UWORD)mode4tiles<<4) );
//      set_bkg_data2(  0x0F, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x0FL)<<4) );
//      set_bkg_data2(  0x26, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x26L)<<4) );
//      set_bkg_data2(  0x2A, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x2AL)<<4) );
//      set_bkg_data2(  0x32, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x32L)<<4) );
	  delayscroll = SCROLLDELAY ;
   }
}
*/
