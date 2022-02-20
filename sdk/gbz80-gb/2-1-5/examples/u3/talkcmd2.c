#include <gb.h>
#include "u3.h"

#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

extern UBYTE playerscreentile ;
extern UBYTE blinkdelay ;
extern UBYTE tileon ;
extern UBYTE currplayer ;
extern UBYTE peermap ;

extern UBYTE changemusic ;
extern UBYTE extragame ;

extern UBYTE peer_semaphore ;

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


unsigned char whodat21[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char gooddaydat21[] = {
	'G'+0x1D,'O'+0x1D,'O'+0x1D,'D'+0x1D,0x5D,'D'+0x1D,'A'+0x1D,'Y'+0x1D,0x82,0x5d,0x5d,0x5d
};

unsigned char notheredat21[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D
} ;

unsigned char chardat21[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};
unsigned char charstat21[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};
unsigned char anddat21[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,
} ;

unsigned char golddat21[] = {
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D
} ;



unsigned char yesno21[] = {
	'N'+0x1D,'O'+0x1D,0x5d,0x5d,0x5d,0x5d,0x5d,
	'Y'+0x1D,'E'+0x1D,'S'+0x1D,0x5d,0x5d,0x5d,0x5d
};


void formatnumber21(UWORD num,UBYTE length)
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

void charscreen21(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat21);

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber21(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat21+(UWORD)player->status );

	formatnumber21(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber21(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber21(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}


UBYTE choosechar21()
{
	UBYTE p, keys, currchar ;


	writegamemessage(whodat21) ;

	for ( p=0; p<4 ; p++ )
		charscreen21(&(players[p]),p) ;

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


UWORD getamt21(UBYTE digits, UWORD maxamt)
{
	UWORD amt ;
	UBYTE currentdigit,p ;
	UBYTE digitvalue ;
	UBYTE joykeys ;
	UWORD multiplier ;
	unsigned char thedigit ;

	amt =0L ;
	multiplier = 1L ;
	currentdigit=0 ;
	digitvalue = 0 ;
	formatnumber21(amt,4) ;
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
					formatnumber21(amt,4) ;
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
				formatnumber21(amt,4) ;
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
				return 0L ;
			else
				break ;
		}

	}

	return amt ;

}

UBYTE getmenuselection21(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
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

	return currline ;

}


void shopwadesc2(UBYTE currline, unsigned char *descptr)
{
	unsigned char screenbuf4[12] ;

	memset(screenbuf4,0x5D,12L) ;
	set_bkg_tiles2( 0, 13, 12, 1, (unsigned char*)screenbuf4);
	set_bkg_tiles2( 0, 16, 12, 1, (unsigned char*)screenbuf4);
	//set_bkg_tiles2( 0, 17, 12, 1, (unsigned char*)screenbuf4);

	set_bkg_tiles2(0,14,12,1,descptr+((UWORD)currline*24L)) ;
	set_bkg_tiles2(0,15,12,1,descptr+((UWORD)currline*24L)+12L) ;


}

void shophealdesc(UBYTE currline, unsigned char *descptr)
{
	unsigned char screenbuf4[12] ;

	memset(screenbuf4,0x5D,12L) ;
	//set_bkg_tiles2( 0, 13, 12, 1, (unsigned char*)screenbuf4);
	set_bkg_tiles2( 0, 16, 12, 1, (unsigned char*)screenbuf4);
	//set_bkg_tiles2( 0, 17, 12, 1, (unsigned char*)screenbuf4);

	set_bkg_tiles2(0,13,12,1,descptr+((UWORD)currline*36L)) ;
	set_bkg_tiles2(0,14,12,1,descptr+((UWORD)currline*36L)+12L) ;
	set_bkg_tiles2(0,15,12,1,descptr+((UWORD)currline*36L)+24L) ;


}

unsigned char guildlist[] = {
	'K'+0x1D,'E'+0x1D,'Y'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,
	'T'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,
	'P'+0x1D,'O'+0x1D,'W'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,
	'G'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,
} ;

unsigned char guilddesclist[] = {
	0x5D,0x5D,0x5D,0x5D, 'K'+0x1D,'E'+0x1D,'Y'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D, '5'+0x48,'0'+0x48,'G'+0x1D,'P'+0x1D,0x5D,'E'+0x1D,'A'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,0x5D,
	0x5D,0x5D, 'T'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,
	0x5D, '6'+0x48,0x5D,'G'+0x1D,'P'+0x1D,0x5D,'E'+0x1D,'A'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,0x5D,
	0x5D,0x5D, 'P'+0x1D,'O'+0x1D,'W'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,
	0x5D, 0x81,'0'+0x48,'G'+0x1D,'P'+0x1D,0x5D,'E'+0x1D,'A'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D, 'G'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D, '7'+0x48,'5'+0x48,'G'+0x1D,'P'+0x1D,0x5D,'E'+0x1D,'A'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,0x5D,
} ;

unsigned char guildshop1[] = {
	'G'+0x1D,'U'+0x1D,'I'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,'S'+0x1D,'H'+0x1D,'O'+0x1D,'P'+0x1D,0x5D,0x5D, 
} ;

unsigned char guildshop2[] = {
	'Y'+0x1D,'O'+0x1D,'U'+0x1D,'R'+0x1D,0x5D,'N'+0x1D,'E'+0x1D,'E'+0x1D,'D'+0x1D,'S'+0x1D,0x83,0x5D, 
} ;

unsigned char guildthank1[] = {
	'T'+0x1D,'H'+0x1D,'A'+0x1D,'N'+0x1D,'K'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x85,0x5D,0x5D, 
} ;
unsigned char guildthank2[] = {
	'C'+0x1D,'O'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,'G'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0x82,0x5D, 
} ;

unsigned char guildnotenough1[]= {
	'I'+0x1D,0x86,'M'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,'R'+0x1D,'R'+0x1D,'Y'+0x1D,0x85,0x5D,0x5D, 
} ;
unsigned char guildnotenough2[]= {
	'B'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'H'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D, 
} ;
unsigned char guildnotenough3[]= {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char guildnotenough4[]= {
	'F'+0x1D,'U'+0x1D,'N'+0x1D,'D'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char guildmany[] = {
	'H'+0x1D,'O'+0x1D,'W'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'Y'+0x1D,0x83,0x5D,0x5D,0x5D, 
} ;

UBYTE guildcosts[] = {
	50,
	6,
	90,
	75
};

void doguild(UBYTE tnum, UBYTE pnum)
{


	UBYTE maxamt,amt ;
	UBYTE price ;
	UBYTE nomore,p ;
	UBYTE whichitem ;
	UBYTE *numptr ;

	changemusic = extragame ? 17 : 7 ;

	nomore = 0 ;

	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(guildshop1) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	waitpadup() ;
	waitpad(0xFF) ;

	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(guildshop2) ;
	whichitem = getmenuselection21(4,guildlist,shopwadesc2,guilddesclist) ;
	if ( whichitem==99 )
	{
		memset(screenbuf3,0x5D,12L) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(guildthank1) ;
		writegamemessage(guildthank2) ;
		return ;

	}

	if ( whichitem==0 )
		numptr = &(players[pnum].keys) ;
	else
		if ( whichitem==1 )
		numptr = &(players[pnum].torches) ;
	else
		if ( whichitem==2 )
		numptr = &(players[pnum].powders) ;
	else
		numptr = &(players[pnum].gems) ;


	writegamemessage(guildmany) ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	if ( 99-(*numptr) < (UBYTE) ((players[pnum].gold)/((UWORD)guildcosts[whichitem])) )
		maxamt = 99-(*numptr) ;
	else
		maxamt = (UBYTE) ((players[pnum].gold)/((UWORD)guildcosts[whichitem])) ;
	amt = getamt21(2,maxamt) ;

	if ( amt )
	{
		players[pnum].gold -= ((UWORD)amt*(UWORD)guildcosts[whichitem]) ;
		(*numptr) += amt ;
	}

	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(guildthank1) ;
	writegamemessage(guildthank2) ;



}

UWORD healcosts[] = {
	100,
	200,
	500,
	900
};


unsigned char healer1[] = {
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char healer2[] = {
	'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char heallist[] = {
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,
	'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,
	'R'+0x1D,'E'+0x1D,'S'+0x1D,'U'+0x1D,'R'+0x1D,'C'+0x1D,'T'+0x1D,
	'R'+0x1D,'E'+0x1D,'C'+0x1D,'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,
} ;

unsigned char healdesclist[] = {
	0x5D,0x5D,0x5D,'C'+0x1D,'U'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,'1'+0x48,'0'+0x48,'0'+0x48,0x5D,'G'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,'R'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'H'+0x1D,'P'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,'2'+0x48,'0'+0x48,'0'+0x48,0x5D,'G'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D, 
	'R'+0x1D,'E'+0x1D,'S'+0x1D,'U'+0x1D,'R'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D, 
	0x5D,'R'+0x1D,'A'+0x1D,'I'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,'5'+0x48,'0'+0x48,'0'+0x48,0x5D,'G'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'A'+0x1D,'L'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D, 
	'R'+0x1D,'A'+0x1D,'I'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,'S'+0x1D,'H'+0x1D,'E'+0x1D,'D'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x81,'0'+0x48,'0'+0x48,0x5D,'G'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D, 
} ;

unsigned char healbye1[] = {
	'F'+0x1D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
}; 
unsigned char healbye2[] = {
	'W'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'M'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
}; 
unsigned char healbye3[] = {
	'C'+0x1D,'H'+0x1D,'I'+0x1D,'L'+0x1D,'D'+0x1D,'R'+0x1D,'E'+0x1D,'N'+0x1D,0x84,0x5D,0x5D,0x5D, 
}; 

unsigned char healnotenough1[] = {
	'I'+0x1D,0x86,'M'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,'R'+0x1D,'R'+0x1D,'Y'+0x1D,0x85,0x5D,0x5D, 
} ;
unsigned char healnotenough2[] = {
	'B'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char healnotenough3[] = {
	'H'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char healnotenough4[] = {
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,'E'+0x1D,'N'+0x1D,'O'+0x1D,'U'+0x1D,'G'+0x1D,'H'+0x1D,0x84, 
} ;

unsigned char notinjured[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'I'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,'D'+0x1D,0x82, 
} ;

unsigned char notpoisoned[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D, 
} ;
unsigned char notdead[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82,0x5D,0x5D,0x5D, 
} ;
unsigned char notashes[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'A'+0x1D,'S'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,0x82,0x5D,0x5D, 
} ;

unsigned char donedat21[] = {
	'D'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

void healsfx() 
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

void dohealer(UBYTE tnum, UBYTE pnum)
{

	UBYTE price ;
	UBYTE nomore,p ;
	UBYTE whichitem ;
	UBYTE *numptr ;
	UBYTE healpnum ;

	changemusic = extragame ? 17 : 7 ;

	nomore = 0 ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(healer1) ;
	writegamemessage(healer2) ;
	writegamemessage(screenbuf3) ;
	waitpadup() ;
	waitpad(0xFF) ;
	while ( !nomore )
	{

		memset(screenbuf3,0x5D,12L) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(guildshop2) ;
		whichitem = getmenuselection21(4,heallist,shophealdesc,healdesclist) ;
		if ( whichitem==99 )
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(healbye1) ;
			writegamemessage(healbye2) ;
			writegamemessage(healbye3) ;
			return ;

		}


		healpnum = choosechar21() ;
		if ( healpnum==99 )
			continue ;

		if ( players[pnum].gold < healcosts[whichitem] )
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(healnotenough1) ;
			writegamemessage(healnotenough2) ;
			writegamemessage(healnotenough3) ;
			writegamemessage(healnotenough4) ;


		}
		else
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			if ( whichitem==0 )
			{
				if ( players[healpnum].status==1 )
				{
					players[pnum].gold -= healcosts[whichitem] ;
					players[healpnum].status = 0 ;
					healsfx() ;
					writegamemessage(donedat21) ;

				}
				else
				{
					writegamemessage(notpoisoned); 

				}


			}
			else
				if ( whichitem==1 )
			{
				if ( (players[healpnum].status<2)&&(players[healpnum].currHP < players[healpnum].maxHP) )
				{
					players[pnum].gold -= healcosts[whichitem] ;
					players[healpnum].currHP = players[healpnum].maxHP ;
					healsfx() ;
					writegamemessage(donedat21) ;

				}
				else
				{
					writegamemessage(notinjured); 

				}

			}
			else
				if ( whichitem==2 )
			{
				if ( players[healpnum].status==2 )
				{
					players[pnum].gold -= healcosts[whichitem] ;
					players[healpnum].status = 0 ;
					players[healpnum].currHP = 1L ;
					healsfx() ;
					writegamemessage(donedat21) ;

				}
				else
				{
					writegamemessage(notdead); 

				}

			}
			else
			{
				if ( players[healpnum].status==3 )
				{
					players[pnum].gold -= healcosts[whichitem] ;
					players[healpnum].status = 0 ;
					players[healpnum].currHP = 1L ;
					healsfx() ;
					writegamemessage(donedat21) ;

				}
				else
				{
					writegamemessage(notashes); 

				}

			}

		}
		for ( p=0; p<4 ; p++ )
			charscreen21(&(players[p]),p) ;
		waitpadup() ;
		waitpad(0xFF) ;

	}




}

unsigned char stable1[] = {
	'E'+0x1D,'Q'+0x1D,'U'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char stable2[] = {
	'E'+0x1D,'M'+0x1D,'P'+0x1D,'O'+0x1D,'R'+0x1D,'I'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char stable3[] = {
	'0'+0x48,0x5D,'H'+0x1D,'O'+0x1D,'R'+0x1D,'S'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char stable4[] = {
	'C'+0x1D,'O'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'0'+0x48,'0'+0x48,'0'+0x48,'G'+0x1D,'P'+0x1D,0x5D,0x5D, 
} ;
unsigned char stable5[] = {
	'W'+0x1D,'I'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char stable6[] = {
	'B'+0x1D,'U'+0x1D,'Y'+0x1D,0x83,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char stableno1[] = {
	'A'+0x1D,'H'+0x1D,0x85,0x5D,'T'+0x1D,'O'+0x1D,'O'+0x1D,0x5D,'B'+0x1D,'A'+0x1D,'D'+0x1D,0x84, 
} ;
unsigned char stableno2[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char stableno3[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'I'+0x1D,'N'+0x1D,0x5D, 
} ;
unsigned char stableno4[] = {
	'T'+0x1D,'O'+0x1D,'W'+0x1D,'N'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char stableyes1[] = {
	'M'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char stableyes2[] = {
	'R'+0x1D,'I'+0x1D,'D'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char stableyes3[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'R'+0x1D,'U'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char stableyes4[] = {
	'F'+0x1D,'R'+0x1D,'I'+0x1D,'E'+0x1D,'N'+0x1D,'D'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

void dostable(UBYTE tnum, UBYTE pnum)
{

	UWORD price ;
	UBYTE nomore,p ;
	UBYTE yesno ;


	changemusic = extragame ? 17 : 7 ;
	nomore = 0 ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(stable1) ;
	writegamemessage(stable2) ;
	writegamemessage(screenbuf3) ;
	waitpadup() ;
	waitpad(0xFF) ;

	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	memcpy(screenbuf3,stable3,12L); 
	for ( p=0 ; p<4 ; p++ )
		if ( players[p].inparty )
			(screenbuf3[0])++ ;
	writegamemessage(screenbuf3) ;
	memcpy(screenbuf3,stable4,12L); 
	price = 0L ;
	for ( p=0 ; p<4 ; p++ )
		if ( players[p].inparty )
		{
			screenbuf3[5] += 2 ;
			price += 200L ;
		}
	writegamemessage(screenbuf3) ;
	writegamemessage(stable5) ;
	writegamemessage(stable6) ;

	yesno = getmenuselection21(2,yesno21,NULL,NULL) ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	if ( yesno==1 )
	{
		if ( players[pnum].gold < price )
		{
			writegamemessage(healnotenough1) ;
			writegamemessage(healnotenough2) ;
			writegamemessage(healnotenough3) ;
			writegamemessage(healnotenough4) ;


		}
		else
		{
			writegamemessage(stableyes1) ;
			writegamemessage(stableyes2) ;
			writegamemessage(stableyes3) ;
			writegamemessage(stableyes4) ;
			players[pnum].gold -= price ;
			playerscreentile = 0x0D ;
			transport = 2 ;
		} 


	}
	else
	{
		writegamemessage(stableno1) ;
		writegamemessage(stableno2) ;
		writegamemessage(stableno3) ;
		writegamemessage(stableno4) ;


	}




}


unsigned char oracle1[] = {
	'R'+0x1D,'A'+0x1D,'D'+0x1D,'R'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x8A,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracle2[] = {
	'P'+0x1D,'R'+0x1D,'O'+0x1D,'P'+0x1D,'H'+0x1D,'E'+0x1D,'T'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracle3[] = {
	'L'+0x1D,'I'+0x1D,'F'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracle4[] = {
	'H'+0x1D,'O'+0x1D,'W'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracle5[] = {
	'1'+0x48,'0'+0x48,'0'+0x48,'G'+0x1D,'P'+0x1D,0x5D,'I'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracle6[] = {
	'Y'+0x1D,'O'+0x1D,'U'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracle7[] = {
	'O'+0x1D,'F'+0x1D,'F'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x83,0x5D,0x5D,0x5D, 
} ;

unsigned char oraclepre1[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D, 
} ;
unsigned char oraclepre2[] = {
	'S'+0x1D,'A'+0x1D,'G'+0x1D,'E'+0x1D,0x5D,'S'+0x1D,'A'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oraclepre3[] = {
	'U'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleA11[] = {
	'I'+0x1D,'F'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'N'+0x1D,0x5D, 
} ;
unsigned char oracleA12[] = {
	'S'+0x1D,'O'+0x1D,'L'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'M'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA13[] = {
	'R'+0x1D,'H'+0x1D,'Y'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x86,'L'+0x1D,'L'+0x1D, 
} ;
unsigned char oracleA14[] = {
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA15[] = {
	'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'S'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA16[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA17[] = {
	'C'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,'S'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA18[] = {
	'H'+0x1D,'I'+0x1D,'D'+0x1D,'D'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,'H'+0x1D,'O'+0x1D,'L'+0x1D,'Y'+0x1D,0x5D, 
} ;
unsigned char oracleA19[] = {
	'S'+0x1D,'H'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleA21[] = {
	'O'+0x1D,'F'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'S'+0x1D,0x5D,'I'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracleA22[] = {
	'S'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA23[] = {
	'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'B'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,'4'+0x48,0x5D,'O'+0x1D,'F'+0x1D, 
} ;
unsigned char oracleA24[] = {
	'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x85,0x5D,'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,0x85, 
} ;
unsigned char oracleA25[] = {
	'S'+0x1D,'N'+0x1D,'A'+0x1D,'K'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA26[] = {
	'K'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleA31[] = {
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'I'+0x1D,'R'+0x1D,0x5D, 
} ;
unsigned char oracleA32[] = {
	'U'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,'I'+0x1D,'N'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'V'+0x1D,'I'+0x1D,'L'+0x1D, 
} ;
unsigned char oracleA33[] = {
	'G'+0x1D,'U'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x85,0x5D,'O'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA34[] = {
	'D'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x86,'L'+0x1D,'L'+0x1D, 
} ;
unsigned char oracleA35[] = {
	'S'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,'L'+0x1D,'Y'+0x1D,0x5D,'B'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D, 
} ;

unsigned char oracleA41[] = {
	'S'+0x1D,'H'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA42[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA43[] = {
	'A'+0x1D,'G'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,'B'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,'4'+0x48,0x5D, 
} ;
unsigned char oracleA44[] = {
	'T'+0x1D,'O'+0x1D,0x5D,'W'+0x1D,'H'+0x1D,'I'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D, 
} ;
unsigned char oracleA45[] = {
	'G'+0x1D,'O'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'P'+0x1D,'R'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D, 
} ;

unsigned char oracleA51[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,'U'+0x1D,'S'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracleA52[] = {
	'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA53[] = {
	'I'+0x1D,'N'+0x1D,'U'+0x1D,'M'+0x1D,'E'+0x1D,'R'+0x1D,'A'+0x1D,'B'+0x1D,'L'+0x1D,'E'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracleA54[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'C'+0x1D,'L'+0x1D,'U'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA55[] = {
	'T'+0x1D,'H'+0x1D,'R'+0x1D,'O'+0x1D,'U'+0x1D,'G'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,'I'+0x1D, 
} ;
unsigned char oracleA56[] = {
	'S'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleA61[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA62[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,'S'+0x1D,'U'+0x1D,'I'+0x1D,'T'+0x1D,'S'+0x1D,0x5D, 
} ;
unsigned char oracleA63[] = {
	'D'+0x1D,'O'+0x1D,0x5D,'N'+0x1D,'U'+0x1D,'M'+0x1D,'B'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'4'+0x48,0x85, 
} ;
unsigned char oracleA64[] = {
	'C'+0x1D,'A'+0x1D,'L'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,'L'+0x1D,0x85,0x5D, 
} ;
unsigned char oracleA65[] = {
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x85,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,0x5D, 
} ;
unsigned char oracleA66[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleA71[] = {
	'U'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA72[] = {
	'M'+0x1D,'O'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,'R'+0x1D,'S'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D, 
} ;
unsigned char oracleA73[] = {
	'M'+0x1D,'U'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'G'+0x1D,'O'+0x1D,0x5D,'F'+0x1D,'O'+0x1D,'R'+0x1D,0x5D, 
} ;
unsigned char oracleA74[] = {
	'G'+0x1D,'U'+0x1D,'I'+0x1D,'D'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA75[] = {
	'F'+0x1D,'R'+0x1D,'O'+0x1D,'M'+0x1D,0x5D,'A'+0x1D,'B'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,0x5D, 
} ;

unsigned char oracleA81[] = {
	'T'+0x1D,'O'+0x1D,0x5D,'A'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'E'+0x1D,0x5D, 
} ;
unsigned char oracleA82[] = {
	'I'+0x1D,'N'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA83[] = {
	'C'+0x1D,'R'+0x1D,'Y'+0x1D,'P'+0x1D,'T'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA84[] = {
	'S'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,0x85,0x5D,'T'+0x1D,'O'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracleA85[] = {
	'D'+0x1D,'U'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA86[] = {
	'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'M'+0x1D,'U'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleA87[] = {
	'F'+0x1D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleA91[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'S'+0x1D,'E'+0x1D,'E'+0x1D,'K'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracleA92[] = {
	'O'+0x1D,'U'+0x1D,'T'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D, 
} ;
unsigned char oracleA93[] = {
	'O'+0x1D,'F'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5D,0x5D, 
} ;
unsigned char oracleA94[] = {
	'H'+0x1D,'E'+0x1D,'L'+0x1D,'P'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'I'+0x1D,'F'+0x1D,0x5D, 
} ;
unsigned char oracleA95[] = {
	'H'+0x1D,'E'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char oraclemore1[] = {
	'M'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oraclemore2[] = {
	'O'+0x1D,'F'+0x1D,'F'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x83,0x5D,0x5D,0x5D, 
} ;

unsigned char oracleleave1[] = {
	'F'+0x1D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleleave2[] = {
	'W'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char oracleleave3[] = {
	'G'+0x1D,'O'+0x1D,'O'+0x1D,'D'+0x1D,0x5D,'L'+0x1D,'U'+0x1D,'C'+0x1D,'K'+0x1D,0x82,0x5D,0x5D, 
} ;


void dooracle(UBYTE tnum, UBYTE pnum)
{

	UWORD amt ;
	UBYTE nomore,p ;
	UBYTE maxamt ;
	UBYTE yesno ;


	changemusic = extragame ? 17 : 7 ;
	nomore = 0 ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(oracle1) ;
	writegamemessage(oracle2) ;
	writegamemessage(oracle3) ;
	writegamemessage(screenbuf3) ;
	waitpadup() ;
	waitpad(0xFF) ;

	while ( 1 )
	{
		memset(screenbuf3,0x5D,12L) ;
		writegamemessage(oracle4) ;
		writegamemessage(oracle5) ;
		writegamemessage(oracle6) ;
		writegamemessage(oracle7) ;
		writegamemessage(screenbuf3) ;

		if ( players[pnum].gold/100L < 9L )
			maxamt = (UBYTE)(players[pnum].gold/100L) ;
		else
			maxamt = 9 ;

		amt= getamt21(1,maxamt) ;

		if ( amt==0L )
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleleave1) ;
			writegamemessage(oracleleave2) ;
			writegamemessage(oracleleave3) ;
			break ;

		}

		memset(screenbuf3,0x5D,12L) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(oraclepre1) ;
		writegamemessage(oraclepre2) ;
		writegamemessage(oraclepre3) ;

		if ( amt==1L )
		{
			writegamemessage(oracleA11) ;
			writegamemessage(oracleA12) ;
			writegamemessage(oracleA13) ;
			writegamemessage(oracleA14) ;
			writegamemessage(oracleA15) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA16) ;
			writegamemessage(oracleA17) ;
			writegamemessage(oracleA18) ;
			writegamemessage(oracleA19) ;
		}
		else
			if ( amt==2L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA21) ;
			writegamemessage(oracleA22) ;
			writegamemessage(oracleA23) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA24) ;
			writegamemessage(oracleA25) ;
			writegamemessage(oracleA26) ;
		}
		else
			if ( amt==3L )
		{
			writegamemessage(oracleA31) ;
			writegamemessage(oracleA32) ;
			writegamemessage(oracleA33) ;
			writegamemessage(oracleA34) ;
			writegamemessage(oracleA35) ;
		}
		else
			if ( amt==4L )
		{
			writegamemessage(oracleA41) ;
			writegamemessage(oracleA42) ;
			writegamemessage(oracleA43) ;
			writegamemessage(oracleA44) ;
			writegamemessage(oracleA45) ;
		}
		else
			if ( amt==5L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA51) ;
			writegamemessage(oracleA52) ;
			writegamemessage(oracleA53) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA54) ;
			writegamemessage(oracleA55) ;
			writegamemessage(oracleA56) ;
		}
		else
			if ( amt==6L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA61) ;
			writegamemessage(oracleA62) ;
			writegamemessage(oracleA63) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA64) ;
			writegamemessage(oracleA65) ;
			writegamemessage(oracleA66) ;
		}
		else
			if ( amt==7L )
		{
			writegamemessage(oracleA71) ;
			writegamemessage(oracleA72) ;
			writegamemessage(oracleA73) ;
			writegamemessage(oracleA74) ;
			writegamemessage(oracleA75) ;
		}
		else
			if ( amt==8L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA81) ;
			writegamemessage(oracleA82) ;
			writegamemessage(oracleA83) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleA84) ;
			writegamemessage(oracleA85) ;
			writegamemessage(oracleA86) ;
			writegamemessage(oracleA87) ;
		}
		else
		{
			writegamemessage(oracleA91) ;
			writegamemessage(oracleA92) ;
			writegamemessage(oracleA93) ;
			writegamemessage(oracleA94) ;
			writegamemessage(oracleA95) ;
		}



		waitpadup() ;
		waitpad(0xFF) ;

		amt *= 100L ;
		players[pnum].gold -= amt ;

		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(oraclemore1) ;
		writegamemessage(oraclemore2) ;

		if ( getmenuselection21(2,yesno21,NULL,NULL)!=1 )
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(oracleleave1) ;
			writegamemessage(oracleleave2) ;
			writegamemessage(oracleleave3) ;
			break ;
		}
		for ( p=0; p<4 ; p++ )
			charscreen21(&(players[p]),p) ;

	}


}


unsigned char british1[] = {
	'W'+0x1D,'E'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'M'+0x1D,'Y'+0x1D,0x5D,0x5D, 
};
unsigned char british2[] = {
	'C'+0x1D,'H'+0x1D,'I'+0x1D,'L'+0x1D,'D'+0x1D,0x84,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char britishdone[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'M'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D, 
};


unsigned char britishmark1[] = {
	'S'+0x1D,'E'+0x1D,'E'+0x1D,'K'+0x1D,0x5D,'Y'+0x1D,'E'+0x1D,0x85,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char britishmark2[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char britishmark3[] = {
	'O'+0x1D,'F'+0x1D,0x5D,'K'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D, 
};

unsigned char britishup1[] = {
	'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char britishup2[] = {
	'G'+0x1D,'R'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char britishnotyet1[] = {
	'E'+0x1D,'X'+0x1D,'P'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'E'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,0x5D, 
};
unsigned char britishnotyet2[] = {
	'M'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

void magiceffect21(UBYTE spellnum)
{
	UBYTE p ;

	VBK_REG=1 ;
	get_bkg_tiles2(1,1,11,11,(unsigned char*)0xBF80) ;

	for ( p=0 ; p < 121 ; p++ )
		if ( *((unsigned char*)0xBF80+(UWORD)p) < 4 )
			*((unsigned char*)0xBF80+(UWORD)p) += 4 ;

	set_bkg_tiles2(1,1,11,11,(unsigned char*)0xBF80) ;
	magicsfx2(0,10+(spellnum*2),0) ;

	for ( p=0 ; p < 121 ; p++ )
		if ( *((unsigned char*)0xBF80+(UWORD)p) > 3 )
			*((unsigned char*)0xBF80+(UWORD)p) -= 4 ;

	set_bkg_tiles2(1,1,11,11,(unsigned char*)0xBF80) ;
	VBK_REG=0 ;

}

void dobritish(UBYTE tnum, UBYTE pnum)
{
	UBYTE reallevel ;

	changemusic = extragame ? 13 : 2 ;

	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(british1) ;
	writegamemessage(british2) ;


	if ( players[pnum].maxHP > 2450 )
	{
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(britishdone) ;
		return ;
	}

	reallevel = ((UBYTE) (players[pnum].exp/100L))+1 ;

	if ( reallevel > 25 )
		reallevel = 25 ;



	if ( reallevel <= players[pnum].level )
	{
		writegamemessage(screenbuf3) ;
		writegamemessage(britishnotyet1) ;
		writegamemessage(britishnotyet2) ;
		return ;
	}

	if ( ( players[pnum].markcard&0x80U ) == 0 )
	{
		if ( players[pnum].level < 5 )
		{
			if ( reallevel > 5 )
				reallevel = 5 ;
		}
		else
		{
			writegamemessage(britishmark1) ;
			writegamemessage(britishmark2) ;
			writegamemessage(britishmark3) ;
			return ;
		}
	}




	writegamemessage(screenbuf3) ;
	writegamemessage(britishup1) ;
	writegamemessage(britishup2) ;
	magiceffect21(4) ;
	players[pnum].maxHP = ((UWORD)(reallevel) * 100L ) + 50L; 
	players[pnum].currHP = players[pnum].maxHP;
	players[pnum].level = reallevel ;

/*
	if (reallevel>players[pnum].level)
	{
		if ( ( players[pnum].markcard&0x80U ) != 0 )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(britishup1) ;
			writegamemessage(britishup2) ;
			magiceffect21(4) ;
			players[pnum].maxHP = ((UWORD)(reallevel) * 100L ) + 50L; 
			players[pnum].currHP = players[pnum].maxHP;
			players[pnum].level = reallevel ;
		}
		else
		{
			if ( players[pnum].level < 5)
			{
				if ( reallevel > 5 )
					reallevel = 5 ;
					
				writegamemessage(screenbuf3) ;
				writegamemessage(britishup1) ;
				writegamemessage(britishup2) ;
				magiceffect21(4) ;
				players[pnum].maxHP = ((UWORD)(reallevel) * 100L ) + 50L; 
				players[pnum].currHP = players[pnum].maxHP;
				players[pnum].level = reallevel ;
	
	
			}
			else
			{
				writegamemessage(britishmark1) ;
				writegamemessage(britishmark2) ;
				writegamemessage(britishmark3) ;
			}
		}
		
	}
	else
	{
		writegamemessage(screenbuf3) ;
		writegamemessage(britishnotyet1) ;
		writegamemessage(britishnotyet2) ;
		return ;
	}
	


	if ((reallevel > 5)&&((players[pnum].markcard&0x80U)==0))
	{
		if (players[pnum].level < 5)
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(britishup1) ;
			writegamemessage(britishup2) ;
			magiceffect21(4) ;

			players[pnum].maxHP = 550L;
			players[pnum].currHP = 550L;
			players[pnum].level = 5 ;


		}
		else
		{
			writegamemessage(britishmark1) ;
			writegamemessage(britishmark2) ;
			writegamemessage(britishmark3) ;
		}
	}
	else
		if (reallevel>players[pnum].level)
		{
			else
			{
				writegamemessage(screenbuf3) ;
				writegamemessage(britishup1) ;
				writegamemessage(britishup2) ;
				magiceffect21(4) ;
				players[pnum].maxHP = ((UWORD)(reallevel) * 100L ) + 50L; 
				players[pnum].currHP = players[pnum].maxHP;
				players[pnum].level = reallevel ;
			}

		}
		else
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(britishnotyet1) ;
			writegamemessage(britishnotyet2) ;



		}
*/

}

unsigned char publeavegood1[] = {
	'I'+0x1D,'T'+0x1D,0x86,'S'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,'A'+0x1D,0x5d
};

unsigned char publeavegood2[] = {
	'P'+0x1D,'L'+0x1D,'E'+0x1D,'A'+0x1D,'S'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5d,0x5d,0x5d
};

unsigned char publeavebad1[] = {
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'M'+0x1D,'Y'+0x1D,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char publeavebad2[] = {
	'S'+0x1D,'H'+0x1D,'O'+0x1D,'P'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5d,0x5d,0x5d,0x5d
};

unsigned char publeavebad3[] = {
	'S'+0x1D,'C'+0x1D,'U'+0x1D,'M'+0x1D,0x82,0x82,0x82,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char pubanother[] = {
	'A'+0x1D,'N'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d
};


unsigned char pubdat1[] = {
	'W'+0x1D,'E'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5d,0x5d
} ;

unsigned char pubdat2[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'P'+0x1D,'U'+0x1D,'B'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d
};

unsigned char pubdat3[] = {
	'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x85,0x5D,'F'+0x1D,'R'+0x1D,'I'+0x1D,'E'+0x1D,'N'+0x1D,'D'+0x1D
} ;

unsigned char pubdat4[] = {
	'H'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,0x5D,'D'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'K'+0x1D
}; 

unsigned char pubdat5[] = {
	'I'+0x1D,'T'+0x1D,0x5D,'C'+0x1D,'O'+0x1D,'S'+0x1D,'T'+0x1D,'S'+0x1D,0x5D,0x7F,'G'+0x1D,'P'+0x1D
};

unsigned char pubdat6[] = {
	'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'P'+0x1D,'A'+0x1D,'Y'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char pubmsg11[] = {
	'T'+0x1D,'H'+0x1D,'A'+0x1D,'N'+0x1D,'K'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D, 
} ;
unsigned char pubmsg12[] = {
	'K'+0x1D,'I'+0x1D,'N'+0x1D,'D'+0x1D,'L'+0x1D,'Y'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg21[] = {
	'A'+0x1D,'M'+0x1D,'B'+0x1D,'R'+0x1D,'O'+0x1D,'S'+0x1D,'I'+0x1D,'A'+0x1D,0x85,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg22[] = {
	'E'+0x1D,'V'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg23[] = {
	'O'+0x1D,'F'+0x1D,0x5D,'I'+0x1D,'T'+0x1D,0x83,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg31[] = {
	'D'+0x1D,'A'+0x1D,'W'+0x1D,'N'+0x1D,0x85,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg32[] = {
	'C'+0x1D,'I'+0x1D,'T'+0x1D,'Y'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg33[] = {
	'M'+0x1D,'Y'+0x1D,'T'+0x1D,'H'+0x1D,'S'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg34[] = {
	'M'+0x1D,'A'+0x1D,'G'+0x1D,'I'+0x1D,'C'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg41[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg42[] = {
	'C'+0x1D,'O'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x5D, 
};
unsigned char pubmsg43[] = {
	'O'+0x1D,'F'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg44[] = {
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D,0x5D,'F'+0x1D,'I'+0x1D,'N'+0x1D,'D'+0x1D,'S'+0x1D,0x5D, 
};
unsigned char pubmsg45[] = {
	'L'+0x1D,'I'+0x1D,'N'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg51[] = {
	'N'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg52[] = {
	'C'+0x1D,'R'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,'S'+0x1D,0x85,0x5D,0x5D, 
};
unsigned char pubmsg53[] = {
	'N'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,'Y'+0x1D,0x5D,'D'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,0x85,0x5D, 
};
unsigned char pubmsg54[] = {
	'S'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg55[] = {
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,'F'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D, 
};
unsigned char pubmsg56[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'E'+0x1D,0x5D,'E'+0x1D,'M'+0x1D,'B'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,0x82, 
};

unsigned char pubmsg61[] = {
	'N'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,'R'+0x1D,'E'+0x1D,'T'+0x1D,'U'+0x1D,'R'+0x1D,'N'+0x1D,0x5D, 
};
unsigned char pubmsg62[] = {
	'O'+0x1D,'R'+0x1D,0x5D,'S'+0x1D,'O'+0x1D,0x5D,'I'+0x1D,0x86,'M'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg63[] = {
	'T'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,'F'+0x1D,'R'+0x1D,'O'+0x1D,'M'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg64[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'O'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg65[] = {
	'D'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg66[] = {
	'C'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg71[] = {
	'S'+0x1D,'H'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D,0x5D, 
};
unsigned char pubmsg72[] = {
	'K'+0x1D,'N'+0x1D,'O'+0x1D,'W'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,'G'+0x1D,'E'+0x1D,0x85,0x5D,0x5D, 
};
unsigned char pubmsg73[] = {
	'S'+0x1D,'H'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'S'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D,0x5D, 
};
unsigned char pubmsg74[] = {
	'S'+0x1D,'T'+0x1D,'R'+0x1D,'E'+0x1D,'N'+0x1D,'G'+0x1D,'T'+0x1D,'H'+0x1D,0x85,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg75[] = {
	'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'S'+0x1D,'T'+0x1D, 
};
unsigned char pubmsg76[] = {
	'I'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg77[] = {
	'B'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'K'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg81[] = {
	'F'+0x1D,'O'+0x1D,'U'+0x1D,'N'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg82[] = {
	'F'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg83[] = {
	'F'+0x1D,'O'+0x1D,'U'+0x1D,'N'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg84[] = {
	'F'+0x1D,'O'+0x1D,'U'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg85[] = {
	'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg86[] = {
	'F'+0x1D,'O'+0x1D,'U'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'I'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg87[] = {
	'D'+0x1D,'U'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg88[] = {
	'B'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'L'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg91[] = {
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'D'+0x1D,'U'+0x1D,'S'+0x1D,0x8A,0x5D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg92[] = {
	'U'+0x1D,'L'+0x1D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'A'+0x1D,0x5D,'I'+0x1D,'I'+0x1D,'I'+0x1D,0x5D,0x5D, 
};
unsigned char pubmsg93[] = {
	'W'+0x1D,'H'+0x1D,'I'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,'I'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg94[] = {
	'N'+0x1D,'E'+0x1D,'X'+0x1D,'T'+0x1D,0x83,0x5D,'N'+0x1D,'O'+0x1D,'W'+0x1D,0x5D,0x5D,0x5D, 
};
unsigned char pubmsg95[] = {
	'C'+0x1D,'O'+0x1D,'U'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D, 
};

unsigned char pubmsg101[] = {
	'S'+0x1D,'E'+0x1D,'E'+0x1D,'K'+0x1D,0x5D,'Y'+0x1D,'E'+0x1D,0x5D,'O'+0x1D,'U'+0x1D,'T'+0x1D,0x5D, 
};
unsigned char pubmsg102[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5D, 
};
unsigned char pubmsg103[] = {
	'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D, 
};
unsigned char pubmsg104[] = {
	'O'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,'W'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,'I'+0x1D,'S'+0x1D,0x5D,'A'+0x1D, 
};
unsigned char pubmsg105[] = {
	'S'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'I'+0x1D,'N'+0x1D,'D'+0x1D,0x82,0x5D,0x5D, 
};

void dopub(UBYTE tnum, UBYTE pnum)
{

	UWORD amt ;
	UBYTE nomore,p ;



	changemusic = extragame ? 17 : 7 ;
	nomore = 0 ;

	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(pubdat1) ;
	writegamemessage(pubdat2) ;
	waitpadup() ;
	waitpad(0xFF) ;
	while ( !nomore )
	{
		for ( p=0; p<4 ; p++ )
			charscreen21(&(players[p]),p) ;
		writegamemessage(pubdat3) ;
		writegamemessage(pubdat4) ;
		writegamemessage(pubdat5) ;
		writegamemessage(pubdat6) ;

		memset(screenbuf3,0x5D,12L) ;
		writegamemessage(screenbuf3) ;
		amt = getamt21(4,players[pnum].gold) ;
		memset(screenbuf3,0x5D,12L) ;

		if ( amt<7L )
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(publeavebad1) ;
			writegamemessage(publeavebad2) ;
			writegamemessage(publeavebad3) ;
			break ;

		}
		else
			if ( amt<10L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg11) ;
			writegamemessage(pubmsg12) ;
		}
		else
			if ( amt<20L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg21) ;
			writegamemessage(pubmsg22) ;
			writegamemessage(pubmsg23) ;
		}
		else
			if ( amt<30L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg31) ;
			writegamemessage(pubmsg32) ;
			writegamemessage(pubmsg33) ;
			writegamemessage(pubmsg34) ;
		}
		else
			if ( amt<40L )
		{
			writegamemessage(pubmsg41) ;
			writegamemessage(pubmsg42) ;
			writegamemessage(pubmsg43) ;
			writegamemessage(pubmsg44) ;
			writegamemessage(pubmsg45) ;
		}
		else
			if ( amt<50L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg51) ;
			writegamemessage(pubmsg52) ;
			writegamemessage(pubmsg53) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg54) ;
			writegamemessage(pubmsg55) ;
			writegamemessage(pubmsg56) ;
		}
		else
			if ( amt<60L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg61) ;
			writegamemessage(pubmsg62) ;
			writegamemessage(pubmsg63) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg64) ;
			writegamemessage(pubmsg65) ;
			writegamemessage(pubmsg66) ;
		}
		else
			if ( amt<70L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg71) ;
			writegamemessage(pubmsg72) ;
			writegamemessage(pubmsg73) ;
			writegamemessage(pubmsg74) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg75) ;
			writegamemessage(pubmsg76) ;
			writegamemessage(pubmsg77) ;
		}
		else
			if ( amt<80L )
		{
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg81) ;
			writegamemessage(pubmsg82) ;
			writegamemessage(pubmsg83) ;
			writegamemessage(pubmsg84) ;
			waitpadup() ;
			waitpad(0xFF) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(pubmsg85) ;
			writegamemessage(pubmsg86) ;
			writegamemessage(pubmsg87) ;
			writegamemessage(pubmsg88) ;
		}
		else
			if ( amt<90L )
		{
			writegamemessage(pubmsg91) ;
			writegamemessage(pubmsg92) ;
			writegamemessage(pubmsg93) ;
			writegamemessage(pubmsg94) ;
			writegamemessage(pubmsg95) ;
		}
		else
		{
			writegamemessage(pubmsg101) ;
			writegamemessage(pubmsg102) ;
			writegamemessage(pubmsg103) ;
			writegamemessage(pubmsg104) ;
			writegamemessage(pubmsg105) ;
		}


		players[pnum].gold -= amt ;
		waitpadup();
		waitpad(0xFF) ;
		memset(screenbuf3,0x5D,12L) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(pubanother) ;
		nomore = !(getmenuselection21(2,yesno21,NULL,NULL)) ;
		if ( nomore )
		{
			memset(screenbuf3,0x5D,12L) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(screenbuf3) ;
			writegamemessage(publeavegood1) ;
			writegamemessage(publeavegood2) ;

		}


	}

}

UBYTE dotransact2(UBYTE tnum, UBYTE tcode)
{
	UBYTE pnum;

	pnum = tcode&0x0F ;


	switch ( tcode&0xF0 )
	{
		case 0x10 : dohealer(tnum,pnum) ; break ;
		case 0x20 : doguild(tnum,pnum) ; break ;
		case 0x30 : dooracle(tnum,pnum) ; break ;
		case 0x40 : dostable(tnum,pnum) ; break ;
		case 0x50 : dobritish(tnum,pnum) ; break ;
		case 0x60 : dopub(tnum,pnum) ; break ;
		default : break ;

	}

	if ( (tcode&0xF0)!=0x50 )
		changemusic = calcmusic(peermap) ;


	return 1 ;
}
