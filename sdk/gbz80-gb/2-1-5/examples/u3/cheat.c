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
extern UBYTE changemusic ;
extern UBYTE die_exodus ;
extern UBYTE currROM ;
extern UBYTE mademove ;

extern UBYTE extragame ;

extern UBYTE inexodus ;

extern UBYTE peer_semaphore ;

extern UBYTE peermap ;
extern UBYTE ingenerator ;

extern PLAYER players[] ;
extern MONSTER monsters[] ;
extern UBYTE nummonsters ;
extern UBYTE numplayers; 
extern UBYTE monsterattrib ;
extern UBYTE monsterpower ;

extern UBYTE playerx ;
extern UBYTE playery ;
extern UBYTE screenx ;
extern UBYTE screeny ;
extern UBYTE need_refresh ;
extern UBYTE inside ;
extern UBYTE transport ;
extern UBYTE playerscreentile ;
extern UWORD party_specials ;

extern UBYTE numgoodies; 
extern UBYTE numalive ;

extern UBYTE stoptimebattle ;
extern UBYTE stoptime ;
extern UBYTE monstertile ;

extern unsigned char *vidbase ;

extern UBYTE delayscroll ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern unsigned char screenbuf3[] ;
extern UBYTE mapnum ;


extern UBYTE cheat_xray ;
extern UBYTE cheat_nofight ;
extern UBYTE cheat_nohurt ;
extern UBYTE cheat_noblock ;
extern UBYTE cheat_fullmp ;
extern UBYTE cheat_noclass ;

unsigned char exodead2[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,0x5D,'I'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'A'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5D,'P'+0x1D,'A'+0x1D,'S'+0x1D,'S'+0x1D, 
	'T'+0x1D,'H'+0x1D,'A'+0x1D,'T'+0x1D,0x5D,'O'+0x1D,'N'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'I'+0x1D,'S'+0x1D, 
	'D'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,'E'+0x1D,'X'+0x1D,'O'+0x1D,'D'+0x1D,'U'+0x1D,'S'+0x1D,0x85,0x5D, 
	'H'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x89U,'B'+0x1D,'O'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D, 
	'I'+0x1D,'N'+0x1D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'N'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'O'+0x1D,'F'+0x1D,0x5D,'E'+0x1D,'V'+0x1D,'I'+0x1D,'L'+0x1D,0x85,0x5D,'W'+0x1D,'A'+0x1D,'S'+0x1D, 
	'V'+0x1D,'A'+0x1D,'N'+0x1D,'Q'+0x1D,'U'+0x1D,'I'+0x1D,'S'+0x1D,'H'+0x1D,'E'+0x1D,'D'+0x1D,0x5D,0x5D, 
	'F'+0x1D,'R'+0x1D,'O'+0x1D,'M'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,'S'+0x1D,'A'+0x1D,'R'+0x1D,'I'+0x1D,'A'+0x1D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'H'+0x1D,'A'+0x1D,'T'+0x1D,0x5D,'N'+0x1D,'O'+0x1D,'W'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'I'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,'A'+0x1D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D,0x5D, 
	'I'+0x1D,'N'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'U'+0x1D,'L'+0x1D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'A'+0x1D,0x5D,'S'+0x1D,'A'+0x1D,'G'+0x1D,'A'+0x1D,0x5D, 
	'C'+0x1D,'A'+0x1D,'N'+0x1D,0x5D,'O'+0x1D,'N'+0x1D,'L'+0x1D,'Y'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,0x5D, 
	'P'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'P'+0x1D,'E'+0x1D,'C'+0x1D,'U'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x82, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'O'+0x1D,'N'+0x1D,'W'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5D,0x5D,0x5D, 
	'U'+0x1D,'L'+0x1D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'A'+0x1D,0x5D,'I'+0x1D,'V'+0x1D,0x82,0x5D,0x5D, 
	'C'+0x1D,'O'+0x1D,'N'+0x1D,'G'+0x1D,'R'+0x1D,'A'+0x1D,'T'+0x1D,'U'+0x1D,0x89U,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'H'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'O'+0x1D,'M'+0x1D,'P'+0x1D,'L'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'D'+0x1D,0x5D,0x5D, 
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'D'+0x1D,'U'+0x1D,'S'+0x1D,0x8AU,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'U'+0x1D,'L'+0x1D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'A'+0x1D,0x5D,'3'+0x48,0x82,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'R'+0x1D,'E'+0x1D,'P'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'Y'+0x1D,0x5D,0x5D, 
	'F'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char cheatmenudat[] = {
	'M'+0x1D,'U'+0x1D,'S'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,0x5D,
	'X'+0x1D,'R'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,
	'N'+0x1D,'O'+0x1D,'F'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,
	'N'+0x1D,'O'+0x1D,'H'+0x1D,'U'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,
	'N'+0x1D,'O'+0x1D,'B'+0x1D,'L'+0x1D,'O'+0x1D,'C'+0x1D,'K'+0x1D,
	'F'+0x1D,'U'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'M'+0x1D,'P'+0x1D,
	'N'+0x1D,'O'+0x1D,'C'+0x1D,'L'+0x1D,'A'+0x1D,'S'+0x1D,'S'+0x1D,
	'M'+0x1D,'A'+0x1D,'X'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,
	0x91U,'P'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,
	0x89U,'P'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,
    'J'+0x1D,'U'+0x1D,'M'+0x1D,'P'+0x1D,'E'+0x1D,'N'+0x1D,'D'+0x1D,
} ;

unsigned char cheatdescdat[] = {
	0x5D,'T'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'M'+0x1D,'U'+0x1D,'S'+0x1D,'I'+0x1D,'C'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'E'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'R'+0x1D,'O'+0x1D,'U'+0x1D,'G'+0x1D,'H'+0x1D,0x5D, 
	0x5D,'A'+0x1D,'N'+0x1D,'Y'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'A'+0x1D,'U'+0x1D,'T'+0x1D,'O'+0x1D,0x5D,'W'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,0x5D, 
	'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,'Y'+0x1D,0x5D,'B'+0x1D,'A'+0x1D,'T'+0x1D,'T'+0x1D,'L'+0x1D,'E'+0x1D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'H'+0x1D,'P'+0x1D,0x5D,'N'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,'D'+0x1D,'E'+0x1D,'C'+0x1D,'R'+0x1D,'E'+0x1D,'A'+0x1D,'S'+0x1D,'E'+0x1D,'S'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'A'+0x1D,'L'+0x1D,'K'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'R'+0x1D,'O'+0x1D,'U'+0x1D,'G'+0x1D,'H'+0x1D, 
	0x5D,0x5D,'A'+0x1D,'N'+0x1D,'Y'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'M'+0x1D,'P'+0x1D,0x5D,'N'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,'D'+0x1D,'E'+0x1D,'C'+0x1D,'R'+0x1D,'E'+0x1D,'A'+0x1D,'S'+0x1D,'E'+0x1D,'S'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'A'+0x1D,'N'+0x1D,'Y'+0x1D,0x5D,'C'+0x1D,'H'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'N'+0x1D, 
	0x5D,0x5D,'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'Y'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'S'+0x1D,'P'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'M'+0x1D,'A'+0x1D,'X'+0x1D,0x5D,'O'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,0x5D, 
	0x5D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,'Y'+0x1D,'T'+0x1D,'H'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D, 
	'F'+0x1D,'O'+0x1D,'R'+0x1D,0x5D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,'Y'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D, 
    0x91U,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,'S'+0x1D,0x85U,0x5D,
    'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'S'+0x1D,0x85U,'P'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,
    'F'+0x1D,'O'+0x1D,'R'+0x1D,0x5D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,'Y'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,
    0x89U,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,'S'+0x1D,0x85U,0x5D,
    'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'S'+0x1D,0x85U,'P'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,
    'F'+0x1D,'O'+0x1D,'R'+0x1D,0x5D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,'Y'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,
    0x5D,0x5D,'J'+0x1D,'U'+0x1D,'M'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5D,0x5D,0x5D,
    0x5D,0x5D,'E'+0x1D,'N'+0x1D,'D'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,    
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

/*
+ALL CARDS, 
MARKS,POWERS
FOR EVERYONE
-ALL CARDS, 
MARKS,POWERS
FOR EVERYONE
  JUMP TO   
  ENDING    
 */
unsigned char chardat26[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};
unsigned char charstat26[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};

unsigned char whodat26[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char dirdat26[] = {
	'D'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x83,0x5d,0x5D
};

void formatnumber26(UWORD num,UBYTE length, UBYTE frommainmenu)
{
	UBYTE n ;
	unsigned char ch ;
	UWORD tens ;

	tens =1 ;

	for ( n=0 ; n<length-1 ; n++ )
		tens = tens*10 ;

	for ( n=0 ; n<length ; n++ )
	{
		if ( frommainmenu == 0 )
			ch=0x78U ; //'0'
		else
			ch=0x5E ; 

		while ( num>= tens )
		{
			num -= tens ;
			ch++ ;
		}
		tens = tens/10 ;
		*((unsigned char*)screenbuf3+(UWORD)n) = ch ;


	}

}

void charscreen26(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat26);

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber26(player->currHP,4,0) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat26+(UWORD)player->status );

	formatnumber26(player->food,4,0) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber26(player->magic,2,0) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber26(player->level,2,0) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}
unsigned char dirarr26[] = {
	'N'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

UBYTE getdir26()
{
	UBYTE dir, p, keys ;

	writegamemessage(dirdat26) ;

	waitpadup() ;
	dir = 0 ;
	while ( 1 )
	{
		keys = joypad() ;
		if ( keys&J_UP )
		{
			dir = 1 ;
			break ;
		}
		if ( keys&J_DOWN )
		{
			dir = 2 ;
			break ;
		}
		if ( keys&J_RIGHT )
		{
			dir = 3 ;
			break ;
		}
		if ( keys&J_LEFT )
		{
			dir = 4 ;
			break ;
		}
		if ( keys&J_B )
		{
			break ;
		}
	}    

	if ( dir )
	{
		writegamemessage(dirarr26+(((UWORD)(dir-1))*12L)) ;

	}
	waitpadup() ;
	return dir ;


}


UBYTE choosechar26()
{
	UBYTE p, keys, currchar ;


	writegamemessage(whodat26) ;

	for ( p=0; p<4 ; p++ )
		charscreen26(&(players[p]),p) ;

	memset(screenbuf3,0x04,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;
	VBK_REG=1 ;
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1,7,1,screenbuf3) ;
	VBK_REG=0 ;

	currchar=0 ;

	waitpadup() ;
	while ( 1 )
	{
		keys = joypad() ;
		if ( keys&J_UP )
		{
			VBK_REG=1 ;    
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3+7L) ;
			if ( currchar==0 )
				currchar = numplayers-1 ;
			else
				currchar-- ;
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3) ;
			VBK_REG=0 ;    
			waitpadup() ;

		}
		if ( keys&J_DOWN )
		{
			VBK_REG=1 ;    
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3+7L) ;
			if ( currchar==numplayers-1 )
				currchar = 0 ;
			else
				currchar++ ;
			for ( p=0 ; p<4 ; p++ )
				set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3) ;
			VBK_REG=0 ;    
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

	VBK_REG=1 ;
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1+(currchar<<2),7,1,screenbuf3+7L) ;
	VBK_REG=0 ;

	if ( keys==0 )
		currchar=99 ;

	return currchar ;
} 


UBYTE getmenuselection26(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
						 unsigned char *descptrdat)
{
	UBYTE p ;
	UBYTE currline ;
	UBYTE keys ;

	if ( LCDC_REG&0x08 )   //select $9C00-$9FFF
		vidbase = (unsigned char*)0x9C00 ;
	else
		vidbase	= (unsigned char*)0x9800 ;

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
			waitpadup() ;      
			keys=1 ;
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

	if ( keys==0 )
		return 99 ;

	memset(screenbuf3,0x5d,12L) ;
	for ( keys=0 ; keys !=4 ; keys++ )
		writegamemessage(screenbuf3) ;

	memcpy(screenbuf3,menudata+((UWORD)currline*7L),7L) ;
	writegamemessage(screenbuf3) ;

	return currline ;

}
void showcheatdesc(UBYTE cheatnum, unsigned char *descdat)
{
	unsigned char screenbuf4[12] ;

	memset(screenbuf4,0x5D,12L) ;
	set_bkg_tiles2( 0, 13, 12, 1, (unsigned char*)screenbuf4);
	set_bkg_tiles2( 0, 17, 12, 1, (unsigned char*)screenbuf4);

	set_bkg_tiles2(0,14,12,1,descdat+((UWORD)cheatnum*36L)) ;
	set_bkg_tiles2(0,15,12,1,descdat+((UWORD)cheatnum*36L)+12L) ;
	set_bkg_tiles2(0,16,12,1,descdat+((UWORD)cheatnum*36L)+24L) ;

}

void allpowers(UBYTE add)
{
	UBYTE n ;
	UBYTE damage ;

    if ( add != 0 ) 
    {
        if ( extragame == 0 )
            party_specials = 0x0FUL ;
        else
            party_specials = 0x0FFFUL ;

        for ( n=0 ; n!=4 ; n++ )
        {
            if ( players[n].inparty )
            {
                players[n].markcard=0xFFU ;
            }
        }
    }
    else
    {
        party_specials = 0x0UL ;

        for ( n=0 ; n!=4 ; n++ )
        {
            if ( players[n].inparty )
            {
                players[n].markcard=0x0U ;
            }
        }
    }
}

void domaxall()
{
	UBYTE n ;
	UBYTE damage ;

	for ( n=0 ; n!=4 ; n++ )
	{
		if ( players[n].inparty )
		{
			players[n].gold = 9999L ;
			players[n].keys=99U ;
			players[n].gems=99U ;
			players[n].currHP = 9999L ;
			players[n].maxHP = 9999L ;
			players[n].magic = 99U ;
			players[n].dex=99U ;
			players[n].str=99U ;
			players[n].wis=99U ;
			players[n].intel=99U ;
			players[n].food = 9999 ;
			players[n].exp = 9999L ;
			players[n].level = 99U ;
			players[n].powders=99U ;
			players[n].torches=99U ;
			memset(players[n].armors,9,8L) ;
			memset(players[n].weapons,9,16L) ;
		}


	}


}
void doselectmusic(UBYTE digits, UWORD maxamt)
{
	UWORD amt ;
	UBYTE currentdigit,p ;
	UBYTE digitvalue ;
	UBYTE joykeys ;
	UWORD multiplier ;
	unsigned char thedigit ;

	memset(screenbuf3,0x5d,12L) ;
	writegamemessage(screenbuf3) ;

	amt =0L ;
	multiplier = 1L ;
	currentdigit=0 ;
	digitvalue = 0 ;
	formatnumber26(amt,4,0) ;
	set_bkg_tiles2(4,17,4,1,screenbuf3) ;
	memset(screenbuf3,0x04,4L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(7,17,1,1,screenbuf3) ;
	VBK_REG=0 ;

	waitpadup() ;


	while ( 1 )
	{
		joykeys=joypad() ;
		if ( joykeys&J_UP )
		{
			if ( digitvalue<9 )
			{
				if ( amt + multiplier <= maxamt )
				{
					digitvalue++ ;
					amt += multiplier ;
					formatnumber26(amt,4,0) ;
					set_bkg_tiles2(4,17,4,1,screenbuf3) ;
				}


			}

			waitpadup() ;
		}
		if ( joykeys&J_DOWN )
		{
			if ( digitvalue )
			{
				digitvalue-- ;
				amt -= multiplier ;
				formatnumber26(amt,4,0) ;
				set_bkg_tiles2(4,17,4,1,screenbuf3) ;

			}

			waitpadup() ;
		}

		if ( joykeys&J_RIGHT )
		{
			screenbuf3[0] = 0x04 ;
			screenbuf3[1] = 0x00 ;
			VBK_REG=1 ;
			set_bkg_tiles2(7-currentdigit,17,1,1,screenbuf3+1) ;
			VBK_REG=0 ;
			if ( currentdigit==0 )
			{
				currentdigit = digits-1 ;
				multiplier=1L ;
				for ( p=0 ; p<currentdigit ; p++ )
					multiplier *= 10L ;
			}
			else
			{
				currentdigit-- ;
				multiplier /= 10L ;
			}
			VBK_REG=1 ;
			set_bkg_tiles2(7-currentdigit,17,1,1,screenbuf3) ;
			VBK_REG=0 ;

		}
		if ( joykeys&J_LEFT )
		{
			screenbuf3[0] = 0x04 ;
			screenbuf3[1] = 0x00 ;
			VBK_REG=1 ;
			set_bkg_tiles2(7-currentdigit,17,1,1,screenbuf3+1) ;
			VBK_REG=0 ;
			if ( currentdigit==digits-1 )
			{
				currentdigit = 0 ;
				multiplier = 1L ;
			}
			else
			{
				currentdigit++ ;
				multiplier *= 10L ;
			}
			VBK_REG=1 ;
			set_bkg_tiles2(7-currentdigit,17,1,1,screenbuf3) ;
			VBK_REG=0 ;


		}
		if ( (joykeys&J_LEFT)||(joykeys&J_RIGHT) )
		{
			get_bkg_tiles2(7-currentdigit,17,1,1,&thedigit) ;
			digitvalue = thedigit-0x78U ;
			waitpadup() ;  
		}
		if ( (joykeys&J_B)||(joykeys&J_A) )
		{
			screenbuf3[1] = 0x00 ;
			VBK_REG=1 ;
			set_bkg_tiles2(7-currentdigit,17,1,1,screenbuf3+1) ;
			VBK_REG=0 ;
			waitpadup() ;
			if ( joykeys&J_B )
				return  ;
			else
				changemusic	= (UBYTE)amt ;
		}

	}


}

void domainmusic()
{
	UWORD amt ;
	UBYTE currentdigit,p ;
	UBYTE digitvalue ;
	UBYTE joykeys ;
	UWORD multiplier ;
	UBYTE digits ;
	UWORD maxamt ;
	unsigned char thedigit ;

	maxamt = 35 ;
	digits = 2 ;


	memset(screenbuf3,0x5d,15L) ;

	set_bkg_tiles2( 2, 12, 15, 1, screenbuf3 );

	set_bkg_tiles2( 2, 13, 15, 1, screenbuf3 );

	set_bkg_tiles2( 2, 14, 15, 1, screenbuf3 );

	set_bkg_tiles2( 2, 15, 15, 1, screenbuf3 );

	VBK_REG = 1;		// select palette bank 

	memset(screenbuf3,0,15L) ;
	set_bkg_tiles2( 2, 15, 15, 1, (unsigned char*)screenbuf3 );
	set_bkg_tiles2(8,13,2,1,screenbuf3) ;

	VBK_REG = 0;		// select palette bank 

	amt =0L ;
	multiplier = 1L ;
	currentdigit=0 ;
	digitvalue = 0 ;

	formatnumber26(amt,2,1) ;

	set_bkg_tiles2(8,13,2,1,screenbuf3) ;
	memset(screenbuf3,0x04,4L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(9,13,1,1,screenbuf3) ;
	VBK_REG=0 ;

	waitpadup() ;


	while ( 1 )
	{
		joykeys=joypad() ;
		if ( joykeys&J_UP )
		{
			if ( digitvalue<9 )
			{
				if ( amt + multiplier <= maxamt )
				{
					digitvalue++ ;
					amt += multiplier ;
					formatnumber26(amt,2,1) ;
					set_bkg_tiles2(8, 13,2,1,screenbuf3) ;
				}


			}

			waitpadup() ;
		}
		if ( joykeys&J_DOWN )
		{
			if ( digitvalue )
			{
				digitvalue-- ;
				amt -= multiplier ;
				formatnumber26(amt,2,1) ;
				set_bkg_tiles2(8, 13,2,1,screenbuf3) ;

			}

			waitpadup() ;
		}

		if ( joykeys&J_RIGHT )
		{
			screenbuf3[0] = 0x04 ;
			screenbuf3[1] = 0x00 ;
			VBK_REG=1 ;
			set_bkg_tiles2(9-currentdigit,13,1,1,screenbuf3+1) ;
			VBK_REG=0 ;
			if ( currentdigit==0 )
			{
				currentdigit = digits-1 ;
				multiplier=1L ;
				for ( p=0 ; p<currentdigit ; p++ )
					multiplier *= 10L ;
			}
			else
			{
				currentdigit-- ;
				multiplier /= 10L ;
			}
			VBK_REG=1 ;
			set_bkg_tiles2(9-currentdigit,13,1,1,screenbuf3) ;
			VBK_REG=0 ;

		}
		if ( joykeys&J_LEFT )
		{
			screenbuf3[0] = 0x04 ;
			screenbuf3[1] = 0x00 ;
			VBK_REG=1 ;
			set_bkg_tiles2(9-currentdigit,13,1,1,screenbuf3+1) ;
			VBK_REG=0 ;
			if ( currentdigit==digits-1 )
			{
				currentdigit = 0 ;
				multiplier = 1L ;
			}
			else
			{
				currentdigit++ ;
				multiplier *= 10L ;
			}
			VBK_REG=1 ;
			set_bkg_tiles2(9-currentdigit,13,1,1,screenbuf3) ;
			VBK_REG=0 ;


		}
		if ( (joykeys&J_LEFT)||(joykeys&J_RIGHT) )
		{
			get_bkg_tiles2(9-currentdigit,13,1,1,&thedigit) ;
			digitvalue = thedigit- 0x5E ;
			waitpadup() ;  
		}
		if ( (joykeys&J_B)||(joykeys&J_A) )
		{
			waitpadup() ;
			if ( joykeys&J_B )
			{
				screenbuf3[1] = 0x00 ;
				VBK_REG=1 ;
				set_bkg_tiles2(9-currentdigit,13,1,1,screenbuf3+1) ;
				VBK_REG=0 ;
				return  ;
			}
			else
				changemusic	= (UBYTE)amt ;
		}

	}


}

void jumpending()
{
    UBYTE ey ;
    UBYTE ex ;
    
        if ( extragame == 0 )
        {
            die_exodus = 0x0F ;
            changemusic = 9 ;
            for ( ey = 0; ey != 6 ; ey++ )
            {
                for ( ex = 0; ex != 5 ; ex++ )
                {
                    writegamemessage(exodead2+(((UWORD)ey)*60L)+((UWORD)(ex*12))) ;
                }
                waitpadup() ;
                waitpad(0xFF) ;
            }


            inexodus = 0 ;
        }
        else
        {
            currROM = 28 ;
            SWITCH_ROM_MBC5(28L) ;
            mademove = doextraother(7) ;

            currROM = 36 ;
            SWITCH_ROM_MBC5(36UL) ;

            shoot_main() ;
        }
}

void docheat()
{
	UBYTE cheatnum ;

	cheatnum = getmenuselection26(11,cheatmenudat,showcheatdesc,cheatdescdat) ;

	switch ( cheatnum )
	{
		case 0 : 
			{
				doselectmusic(2,35) ;
				break ;
			}
		case 1 : 
			{
				cheat_xray += 0x80U ;
				break ;
			}
		case 2 : 
			{
				cheat_nofight += 0x80U ;
				break ;
			}
		case 3 : 
			{
				cheat_nohurt += 0x80U ;
				break ;
			}
		case 4 : 
			{
				cheat_noblock += 0x80U ;
				break ;
			}
		case 5 : 
			{
				cheat_fullmp += 0x80U ;
				break ;
			}
		case 6 : 
			{
				cheat_noclass += 0x80U ;
				break ;
			}
		case 7 : 
			{
				domaxall() ;
				break ;
			}
		case 8 : 
			{
				allpowers(1) ;
				break ;
			}
		case 9 : 
			{
				allpowers(0) ;
				break ;
			}
		case 10 : 
			{
				jumpending() ;
				break ;
			}
		default : break ;
	}

	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
}


unsigned char killgendat1[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'C'+0x1D,'H'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,0x5D, 
	'S'+0x1D,'E'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'M'+0x1D,'O'+0x1D,'A'+0x1D,'N'+0x1D,0x5D,'A'+0x1D,'S'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D, 
	'R'+0x1D,'E'+0x1D,'M'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'I'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x5D, 
	'C'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x84U,0x84U,0x84U,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char killgendat2[] = {
	0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'H'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D,0x5D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'P'+0x1D,'I'+0x1D,'E'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'D'+0x1D,'U'+0x1D,'S'+0x1D,0x82U,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

void killgenerator()
{
	UBYTE kg ;

	for ( kg = 0 ; kg < 5 ; kg++ )
	{
		writegamemessage(killgendat1 + (UWORD)(kg*12)) ;
	}

	waitpad(0xFF) ;
	waitpadup() ;

	for ( kg = 0 ; kg < 5 ; kg++ )
	{
		writegamemessage(killgendat2 + (UWORD)(kg*12)) ;
	}

	specialsfx() ;

	waitpad(0xFF) ;
	waitpadup() ;

	switch ( peermap )
	{
		case 0 : party_specials |= 0x0100 ; break ;
		case 2 : party_specials |= 0x0200 ; break ;
		case 4 : party_specials |= 0x0400 ; break ;
		case 6 : party_specials |= 0x0800 ; break ;
		default : break ;
	}

	ingenerator = 0 ;   
}
