#include <gb.h>
#include "u3.h"

#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

extern UBYTE whirldirectx ;
extern UBYTE whirldirecty ;

extern UWORD windctr ;
extern UBYTE winddir ;
extern UWORD whirlctr ;

extern UBYTE extragame ;
extern PLAYER players[] ;
extern MONSTER monsters[] ;
extern UBYTE nummonsters ;
extern UBYTE numplayers; 

extern UBYTE changemusic ;

extern UBYTE inexodus ;
extern UBYTE die_exodus ;

extern UBYTE peermap ;

extern unsigned char varlist[120] ;

extern UWORD party_specials ;

extern UBYTE playerx ;
extern UBYTE playery ;
extern UBYTE screenx ;
extern UBYTE screeny ;
extern UBYTE need_refresh ;
extern UBYTE inside ;
extern UBYTE transport ;

extern UBYTE numalive ;

extern UBYTE stoptime ;

extern unsigned char *vidbase ;

extern UBYTE delayscroll ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern unsigned char screenbuf3[] ;
extern UBYTE mapnum ;


unsigned char sexes3[] = {
	'M'+0x1D,
	'F'+0x1D,
	'O'+0x1D
};

unsigned char races3[] = {
	'H'+0x1D,
	'E'+0x1D,
	'D'+0x1D,
	'F'+0x1D,
	'B'+0x1D
};

unsigned char classes3[] = {
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

unsigned char condcodes3[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};

unsigned char cardsdat3[] = {
	'D'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,
	'L'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5d,
	'S'+0x1D,'O'+0x1D,'L'+0x1D,0x5d,0x5d,
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5d
};

unsigned char marksdat3[] = {
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,
	'F'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,0x5d,
	'S'+0x1D,'N'+0x1D,'A'+0x1D,'K'+0x1D,'E'+0x1D,
	'K'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5d
};

unsigned char stats111[] = {
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
unsigned char stats222[] = {
	0X5D,0x5d,'L'+0x1D,0x8A,0x5d,0x5d,
	0X5D,0x5d,'M'+0x1D,0x8A,0x5d,0x5d,
	'F'+0x1D,0x8A,0x5d,0x5d,0x5d,0x5d,
	0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,
	'D'+0x1D,'E'+0x1D,'X'+0x1D,0x8A,0x5d,0x5d,
	'W'+0x1D,'I'+0x1D,'S'+0x1D,0x8A,0x5d,0x5d,
	'K'+0x1D,'E'+0x1D,'Y'+0x1D,0x8A,0x5d,0x5d,
	'T'+0x1D,'O'+0x1D,'R'+0x1D,0x8A,0x5d,0x5d
};

unsigned char stats333[] = {
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,0x5d,'L'+0x1D,'I'+0x1D,'S'+0x1D,'T'+0x1D,
	'A'+0x1D,'R'+0x1D,'M'+0x1D,'O'+0x1D,'R'+0x1D,0X5D,0x5d,'L'+0x1D,'I'+0x1D,'S'+0x1D,'T'+0x1D
};
unsigned char stats444[] = {
	'A'+0x1D,'W'+0x1D,'A'+0x1D,'I'+0x1D,'T'+0x1D,'S'+0x1D,
	'J'+0x1D,'O'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D
};


unsigned char weaponsdat5[] = {
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
unsigned char armorsdat5[] = {
	'S'+0x1D,'K'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'C'+0x1D,'L'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,0X5D,0X5D,0X5D,
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,
	'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,
	0x91,0x7A,0X5D,'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,
	0x91,0x7A,0X5D,'P'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'T'+0x1D,'I'+0x1D,'C'+0x1D,0X5D,0X5D
} ;


unsigned char canceldat3[] = {
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x5d,0x5d,0x5d
} ;


unsigned char whodat4[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};
unsigned char donedat2[] = {
	'D'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char dirdat5[] = {
	0x5D,0x5D,'E'+0x1D,'N'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,
	'D'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D
};

unsigned char emptydat3[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char deaddat3[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82 
} ;

unsigned char chardat6[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};

void formatnumber8(UWORD num,UBYTE length)
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

void charscreen6(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat6);

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber8(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, condcodes3+(UWORD)player->status );

	formatnumber8(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber8(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber8(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}

UBYTE getdir3()
{
	UBYTE dir, p, keys ;

	memset(screenbuf3,0x5D,12L) ;
	for ( p = 0 ; p<5 ; p++ )
		set_bkg_tiles2(0,p+13,12,1,(unsigned char*)screenbuf3) ;

	memset(screenbuf3,0x00,12L) ;
	VBK_REG=1 ;

	for ( p = 0 ; p<5 ; p++ )
		set_bkg_tiles2(0,p+13,12,1,(unsigned char*)screenbuf3) ;

	VBK_REG=0 ;

	set_bkg_tiles2(1,15,9,1,dirdat5);
	set_bkg_tiles2(1,16,9,1,dirdat5+9L);

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

	waitpadup() ;
	return dir ;


}


UBYTE choosechar4()
{
	UBYTE p, keys, currchar ;


	writegamemessage(whodat4) ;

	for ( p=0; p<4 ; p++ )
		charscreen6(&(players[p]),p) ;

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

UBYTE getmenuselection5(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
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



UBYTE doztats()
{

	UBYTE n, currarmor, currweapon, joykeys, done ;
	UBYTE currsel,nextptr, which ;
	unsigned char *vidbase2 ;


	which = choosechar4() ;
	if ( which==99 )
	{
		//writegamemessage(canceldat3) ;
		return 0 ;
	}

	//move_sprite(5,0,0) ;
	if ( LCDC_REG&0x08 )   //select $9C00-$9FFF
		vidbase2 = (unsigned char*)0x9800 ;
	else
		vidbase2 = (unsigned char*)0x9C00 ;


	memset(screenbuf3,0x5DU,32UL) ;

	for ( n = 0 ; n<18 ; n++ )
		set_data2(vidbase2+((UWORD)n*32UL),screenbuf3,20UL) ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf3,0x00U,32UL) ;
	for ( n = 0 ; n<18 ; n++ )
		set_data2(vidbase2+((UWORD)n*32UL),screenbuf3,20UL) ;
	VBK_REG = 0;		// select palette bank 

	set_data2(vidbase2,players[which].name,0x07UL) ;


//    memset(screenbuf3,0x3AU,32UL) ;
	memset(screenbuf3,0x5dU,32UL) ;
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
		set_data2(vidbase2+(32L*(UWORD)n),stats111+((UWORD)(n-1)*6L),6L) ;

	for ( n=0 ; n<8 ; n++ )
		set_data2(vidbase2+0x0DUL+(32L*(UWORD)n),stats222+((UWORD)n*6L),6L) ;

	set_data2(vidbase2+4UL+(32L*10L),stats333,11L) ;
	set_data2(vidbase2+4UL+(32L*11L),stats333+11L,11L) ;

	if ( players[which].inparty )
		set_data2(vidbase2+0x0DUL+(32L*3L),stats444+6L,6L) ;
	else
		set_data2(vidbase2+0x0DUL+(32L*3L),stats444,6L)	;

	set_data2(vidbase2+2UL+(8L*32L),weaponsdat5+(8L*(UWORD)players[which].weapon),8L) ;
	set_data2(vidbase2+2UL+(9L*32L),armorsdat5+(8L*(UWORD)players[which].armor),8L) ;

	formatnumber8(players[which].currHP,4) ;
	screenbuf3[4] = 0x92 ;
	set_data2(vidbase2+2UL+(1L*32L),screenbuf3,5L) ;

	formatnumber8(players[which].maxHP,4) ;
	set_data2(vidbase2+7UL+(1L*32L),screenbuf3,4L) ;

	set_data2(vidbase2+0x0BUL+(0L*32L),condcodes3+(UWORD)players[which].status,1L) ;

	formatnumber8( players[which].food,4) ;
	set_data2(vidbase2+0x0FUL+(2L*32L),screenbuf3,4L) ;

	formatnumber8( players[which].gold,4) ;
	set_data2(vidbase2+2UL+(3L*32L),screenbuf3,4L) ;

	formatnumber8( (UWORD)players[which].magic,2) ;
	set_data2(vidbase2+0x11UL+(1L*32L),screenbuf3,2L) ;
	formatnumber8( ((UWORD)(players[which].level)),2) ;
	set_data2(vidbase2+0x11UL+(0L*32L),screenbuf3,2L) ;

	formatnumber8( players[which].exp,4) ;
	set_data2(vidbase2+0x02UL+(2L*32L),screenbuf3,4L) ;

	formatnumber8( (UWORD)players[which].str,2) ;
	set_data2(vidbase2+0x04UL+(4L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].dex,2) ;
	set_data2(vidbase2+0x11UL+(4L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].intel,2) ;
	set_data2(vidbase2+0x04UL+(5L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].wis,2) ;
	set_data2(vidbase2+0x11UL+(5L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].gems,2) ;
	set_data2(vidbase2+0x04UL+(6L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].keys,2) ;
	set_data2(vidbase2+0x11UL+(6L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].powders,2) ;
	set_data2(vidbase2+0x04UL+(7L*32L),screenbuf3,2L) ;
	formatnumber8( (UWORD)players[which].torches,2) ;
	set_data2(vidbase2+0x11UL+(7L*32L),screenbuf3,2L) ;

	set_data2(vidbase2+0x08UL+(0L*32L),sexes3+((UWORD)players[which].sex),1L) ;
	set_data2(vidbase2+0x09UL+(0L*32L),races3+((UWORD)players[which].race),1L) ;
	set_data2(vidbase2+0x0AUL+(0L*32L),classes3+((UWORD)players[which].skill),1L) ;

	for ( n=0 ; n<4 ; n++ )
		if ( (players[which].markcard>>n)&0x01 )
			set_data2(vidbase2+0x07UL+(14L*32L)+((UWORD)(n&0x01)*6L)+((UWORD)(n&0x02)*16L),
					  cardsdat3+((UWORD)n*5L),5L) ;

	for ( n=0 ; n<4 ; n++ )
		if ( (players[which].markcard>>(4+n))&0x01 )
			set_data2(vidbase2+0x07UL+(12L*32L)+((UWORD)(n&0x01)*6L)+((UWORD)(n&0x02)*16L),
					  marksdat3+((UWORD)n*5L),5L) ;


	VBK_REG = 1;		// select palette bank 
	memset(screenbuf3,0x04U,32UL) ;
	set_data2(vidbase2+0x04UL+(32L*10L),screenbuf3,11L) ;
	VBK_REG = 0;		// select palette bank 

	done=0 ;
	currsel = 0 ; //weapon line selected
	currarmor = 99 ;
	currweapon = 99 ;    

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
					set_data2(vidbase2+0x04UL+(32L*10L),stats333,11L) ;
				}
				else
				{
					currweapon = nextptr ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].weapons)[currweapon]+0x78 ;
					memcpy(screenbuf3+2L,weaponsdat5+((UWORD)currweapon*8L),8L) ;
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
					set_data2(vidbase2+0x04UL+(32L*11L),stats333+11L,11L) ;
				}
				else
				{
					currarmor = nextptr ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].armors)[currarmor]+0x78 ;
					memcpy(screenbuf3+2L,armorsdat5+((UWORD)currarmor*8L),8L) ;
					set_data2(vidbase2+0x04UL+(32L*11L),screenbuf3,11L) ;
				}


			}

			waitpadup() ;
		}

		if ( joykeys&J_LEFT )
		{
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
					set_data2(vidbase2+0x04UL+(32L*10L),stats333,11L) ;
				}
				else
				{
					currweapon = nextptr-1 ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].weapons)[currweapon]+0x78 ;
					memcpy(screenbuf3+2L,weaponsdat5+((UWORD)currweapon*8L),8L) ;
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
					set_data2(vidbase2+0x04UL+(32L*11L),stats333+11L,11L) ;
				}
				else
				{
					currarmor = nextptr-1 ;
					memset(screenbuf3,0x5D,11L) ;
					screenbuf3[0] = (players[which].armors)[currarmor]+0x78 ;
					memcpy(screenbuf3+2L,armorsdat5+((UWORD)currarmor*8L),8L) ;
					set_data2(vidbase2+0x04UL+(32L*11L),screenbuf3,11L) ;
				}


			}

			waitpadup() ;
		}

		if ( (joykeys&J_UP)||(joykeys&J_DOWN) )
		{
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

			waitpadup() ;

		}

		if ( joykeys&J_B )
		{
			done = 99 ;	 //cancel, backup
			waitpadup() ;
			break ;
		}
	}    


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

	//move_sprite( 5, 56,64 );
	need_refresh = 1 ;

	return 0 ;
}

unsigned char yellcmds[] = {
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,0x5D,
	'E'+0x1D,'V'+0x1D,'O'+0x1D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'E'+0x1D,
};

unsigned char othercmds[] = {
	'S'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,
	'I'+0x1D,'N'+0x1D,'S'+0x1D,'E'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,
	'B'+0x1D,'R'+0x1D,'I'+0x1D,'B'+0x1D,'E'+0x1D,0x5D,0x5D,
	'D'+0x1D,'I'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,
	'P'+0x1D,'R'+0x1D,'A'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,
	'S'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,
};

unsigned char othercmds2[] = {
	'S'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,0x5D,
	'F'+0x1D,'O'+0x1D,'C'+0x1D,'U'+0x1D,'S'+0x1D,0x5D,0x5D,
	'C'+0x1D,'L'+0x1D,'I'+0x1D,'M'+0x1D,'B'+0x1D,0x5D,0x5D,
	'F'+0x1D,'R'+0x1D,'E'+0x1D,'E'+0x1D,'Z'+0x1D,'E'+0x1D,0x5D,
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'E'+0x1D,0x5D,0x5D,
	'O'+0x1D,'M'+0x1D,'N'+0x1D,'I'+0x1D,'E'+0x1D,'Y'+0x1D,'E'+0x1D,
	'A'+0x1D,'B'+0x1D,'S'+0x1D,'O'+0x1D,'R'+0x1D,'B'+0x1D,0x5D,
	'B'+0x1D,'U'+0x1D,'I'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,0x5D,
	'B'+0x1D,'O'+0x1D,'W'+0x1D,0x5D,0x5D,0x5D,0x5D,
//FOCUS
//CLIMB
//FREEZE
//FORCE
//OMNIEYE
//ABSORB
//BUILD
//BOW 
};


unsigned char curses1[] = {
	'F'+0x1D,'E'+0x1D,'E'+0x1D,'L'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,0x83, 
};

unsigned char noeffectdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'E'+0x1D,'F'+0x1D,'F'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,0x82,0x5d,0x5d
};

void doscore()
{

	writegamemessage(noeffectdat) ;

}

unsigned char cardlist[] = {
	'D'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,
	'L'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,
	'S'+0x1D,'O'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,
	'M'+0x1D,'O'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D,
};

unsigned char exodead1[] = {
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

unsigned char noneowned[] = {
	'N'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,'O'+0x1D,'W'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5D,
} ;

void trapeffect4(UBYTE pnum)
{
	UBYTE p ;

	memset(screenbuf3,0x04,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;
	disable_interrupts2() ;
	VBK_REG=1 ;      
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1+(pnum<<2),7,1,screenbuf3) ;
	playerhitsfx(170U) ;
	//delay(150) ; //trap sound
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1+(pnum<<2),7,1,screenbuf3+7L) ;
	VBK_REG=0 ;      
	enable_interrupts2() ;


}

void doinsert(UBYTE pnum)
{
	unsigned char etile ;
	UBYTE whichcard ;
	unsigned char correctorder[4] ;
	UBYTE ex,ey ;

	get_bkg_tiles2(6,5,1,1,&etile) ;
	correctorder[0] = 1 ;
	correctorder[1] = 2 ;
	correctorder[2] = 3 ;
	correctorder[3] = 0 ;

	if ( (inexodus)&&(etile==0x25) )
	{
		whichcard = getmenuselection5(4,cardlist,NULL,NULL) ;
		if ( ((players[pnum].markcard)&(1<<whichcard))==0 )
		{
			writegamemessage(noneowned) ;

		}
		else
		{
			if ( correctorder[playerx-0x1E]==whichcard )
			{
				die_exodus |= (1<<whichcard);
				if ( die_exodus==0x0F )
				{
					changemusic = 9 ;
					for ( ey = 0; ey != 6 ; ey++ )
					{
						for ( ex = 0; ex != 5 ; ex++ )
						{
							writegamemessage(exodead1+(((UWORD)ey)*60L)+((UWORD)(ex*12))) ;
						}
						waitpadup() ;
						waitpad(0xFF) ;
					}


					inexodus = 0 ;


				}

			}
			else
			{
				players[pnum].currHP = 0L ;
				players[pnum].status = 0x02 ;
				numalive-- ;
				charscreen6(&(players[pnum]),pnum) ;
				trapeffect4(pnum) ;
				writegamemessage(deaddat3) ;

			}


		}


	}
	else
		writegamemessage(noeffectdat) ;


}

unsigned char yellevo[] = {
	'Y'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'E'+0x1D,'V'+0x1D,'O'+0x1D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'E'+0x1D, 
};

unsigned char cantpay[] = {
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'P'+0x1D,'A'+0x1D,'Y'+0x1D,0x5d,0x5d
};

void dobribe(UBYTE pnum) 
{
	UBYTE dir,r ;
	unsigned char gtile ;
	UBYTE mnum, mx, my ;


	if ( players[pnum].gold<100L )
	{
		writegamemessage(cantpay) ;
		return ;
	}

	dir = getdir3() ;
	if ( dir==0 )
	{
		writegamemessage(canceldat3) ;
		return ;
	}

	mx = playerx ;
	my = playery ;

	switch ( dir )
	{
		case 1 : 
			{
				get_bkg_tiles2(6,5,1,1,&gtile) ; 
				my = (playery-1)&0x3f ;
				break ;
			}
		case 2 : 
			{
				get_bkg_tiles2(6,7,1,1,&gtile) ; 
				my = (playery+1)&0x3f ;
				break ;
			}
		case 3 : 
			{
				get_bkg_tiles2(7,6,1,1,&gtile) ; 
				mx = (playerx+1)&0x3f ;
				break ;
			}
		case 4 : 
			{
				get_bkg_tiles2(5,6,1,1,&gtile) ; 
				mx = (playerx-1)&0x3f ;
				break ;
			}
		default : gtile = 0 ;break ;


	}

	if ( gtile==0x18 )
	{
		mnum = 0 ;
		while ( (mnum<nummonsters) && ((monsters[mnum].x != mx) || (monsters[mnum].y!=my)) )
			mnum++ ;

		if ( mnum==nummonsters )
			return ;

		for ( r=mnum ; r<nummonsters-1 ; r++ )
			memcpy((unsigned char*)&(monsters[r]),(unsigned char*)&(monsters[r+1]),MONSTERSIZE) ;
		nummonsters-- ;

		disable_interrupts2() ;
		SWITCH_RAM_MBC5(3) ;
		gtile = *((unsigned char*)0xA000+((UWORD)(((UWORD)(my))<<6))+(UWORD)(mx)) ;
		SWITCH_RAM_MBC5(1) ;
		enable_interrupts2() ;
		set_bkg_tiles2(mx,my,1,1,&gtile) ;
		VBK_REG=1 ;
		set_bkg_tiles2(mx,my,1,1,tile_palettes+(UWORD)gtile) ;
		VBK_REG=0 ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(my))<<6))+(UWORD)(mx)) = gtile ;

		players[pnum].gold -= 100L ;


	}
	else
	{
		writegamemessage(noeffectdat) ;
	}


}
unsigned char exoticdat[] = {
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'T'+0x1D,'I'+0x1D,'C'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D, 
};

void dodig(UBYTE pnum)
{
	if ( inside!=0 )
	{
		writegamemessage(noeffectdat) ;
		return ;
	}

	if ( (playerx==33)&&(playery==3) )
	{
		writegamemessage(exoticdat) ;
		if ( ((players[pnum].weapons)[15])<9 )
			((players[pnum].weapons)[15])++ ;
		return ;

	}
	if ( (playerx==19)&&(playery==44) )
	{
		writegamemessage(exoticdat) ;
		if ( ((players[pnum].armors)[7])<9 )
			((players[pnum].armors)[7])++ ;

		return ;
	}
	writegamemessage(noeffectdat) ;


}

unsigned char card1[] = {
	'A'+0x1D,0x5D,'C'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D,'W'+0x1D,'I'+0x1D,'T'+0x1D,'H'+0x1D,0x5D, 
} ;
unsigned char card2[] = {
	'S'+0x1D,'T'+0x1D,'R'+0x1D,'A'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;
unsigned char card3[] = {
	'M'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
} ;

void dosearch(UBYTE pnum)
{
	if ( peermap==12 )
	{
		//4,36 = shrine of strength - love
		//45,52 = shrine of dexterity - sol
		//6,6 = shrine of intelligence - moons
		//55,27 = shrine of wisdom - death

		if ( (playerx==4)&&(playery==36) )
		{
			writegamemessage(card1) ;
			writegamemessage(card2) ;
			writegamemessage(card3) ;
			players[pnum].markcard |= CARDLOVE ;
			return ;
		}
		if ( (playerx==45)&&(playery==52) )
		{
			writegamemessage(card1) ;
			writegamemessage(card2) ;
			writegamemessage(card3) ;
			players[pnum].markcard |= CARDSOL ;
			return ;
		}
		if ( (playerx==6)&&(playery==6) )
		{
			writegamemessage(card1) ;
			writegamemessage(card2) ;
			writegamemessage(card3) ;
			players[pnum].markcard |= CARDMOON ;
			return ;
		}
		if ( (playerx==55)&&(playery==27) )
		{
			writegamemessage(card1) ;
			writegamemessage(card2) ;
			writegamemessage(card3) ;
			players[pnum].markcard |= CARDDEATH ;
			return ;
		}


	}

	writegamemessage(noeffectdat) ;

}
void dopray()
{
	if ( (peermap==11)&&(playery==0x30)&&(playerx==0x30) )
	{
		writegamemessage(yellevo) ;
		party_specials |= 0x0100 ;
		return ;
	}
	writegamemessage(noeffectdat) ;

}

UBYTE doyellother(UBYTE yell)
{
	UBYTE numitems ;
	UBYTE p ;
	unsigned char *listdata ;
	UBYTE loffset ;
	UBYTE pnum ;
	UBYTE mcmd ;
	UBYTE realcmd ;


//curses
//evocare

//	party_specials |= 0x011F ;

	pnum = choosechar4() ;
	if ( pnum==99 )
		return 0 ;

	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat3) ;
		return 1 ;
	}


	if ( yell )
	{
		listdata = yellcmds ;
		loffset = 8 ;

	}
	else
	{
		if ( extragame != 0 )
			listdata = othercmds2 ;
		else
			listdata = othercmds ;
		loffset = 0 ;

	}


	p = 0 ;
	memset(varlist,0x5d,120L) ;

	memcpy(varlist,listdata,7L) ;
	numitems = 1 ;

	while ( p<8 )
	{
		if ( (party_specials>>(p+loffset))&0x01 )
		{
			memcpy(varlist+((UWORD)numitems)*7L,listdata+(((UWORD)(p+1))*7L),7L) ;
			numitems++ ;
		}
		p++ ;
	}

	mcmd = getmenuselection5(numitems,varlist,NULL,NULL) ;
	if ( mcmd==99 )
		return 0 ;


	p=0 ;
	while ( mcmd )
	{
		if ( (party_specials>>(p+loffset))&0x01 )
		{
			mcmd-- ;
			//realcmd = p ;
			//p = 9 ;
			//break ;
		}
		p++ ;
	}

	if ( yell )
	{
		if ( p==0 )//curses
		{
			writegamemessage(curses1) ;
			//writegamemessage(curses2) ;

		}
		else //evocare
		{
			if ( ((players[pnum].markcard)&MARKSNAKE) &&
				 (playerx==10) && ( (playery==0x38)||(playery==0x3B))&&(inside==0) )
			{
				playery = playery ^ 3 ;
				screeny = screeny ^ 5 ;
				need_refresh = 1 ;
				//magicsfx
			}
			else
				writegamemessage(noeffectdat) ;



		}


	}
	else
	{
		if ( extragame != 0 )
			return(p | ((pnum+1)<<4 )) ;

		switch ( p )
		{
			case 0 : doscore() ;  break ; //score
			case 1 : doinsert(pnum) ;  break ; //insert
			case 2 : dobribe(pnum) ;   break ; //bribe
			case 3 : dodig(pnum) ;  break ;	//dig
			case 4 : dopray() ;   break ; //pray
			case 5 : dosearch(pnum) ;   break ;	//search


		}



	}

	return 1 ;

}

void writewind()
{
	unsigned char wtile ;
	UBYTE oldv ;

//	oldv = VBK_REG ;

//	if (VBK_REG==1)
	//VBK_REG = 0 ;

	disable_interrupts2() ;

	switch ( winddir )
	{
		case 0 : 
			{
				wtile = 0x5DU ;
				set_data2((unsigned char*)0x9800+(12L*32L)+6L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+6L,&wtile,1L) ;
				//set_bkg_tiles2(4,12,1,1,&wtile) ;
				wtile = 0xB8U ;
				//set_bkg_tiles2(5,12,1,1,&wtile) ;
				set_data2((unsigned char*)0x9800+(12L*32L)+7L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+7L,&wtile,1L) ;
				wtile = 0xB9U ;
				//set_bkg_tiles2(6,12,1,1,&wtile) ;
				set_data2((unsigned char*)0x9800+(12L*32L)+8L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+8L,&wtile,1L) ;
				break ;

			}
		case 1 : 
			{
				wtile = 0xA4U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+6L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+6L,&wtile,1L) ;
				//set_bkg_tiles2(4,12,1,1,&wtile) ;
				wtile = 0xA5U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+7L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+7L,&wtile,1L) ;
				//set_bkg_tiles2(5,12,1,1,&wtile) ;
				wtile = 0xA6U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+8L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+8L,&wtile,1L) ;
				//set_bkg_tiles2(6,12,1,1,&wtile) ;
				break ;

			}
		case 2 : 
			{
				wtile = 0xA7U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+6L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+6L,&wtile,1L) ;
				//set_bkg_tiles2(4,12,1,1,&wtile) ;
				wtile = 0xA8U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+7L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+7L,&wtile,1L) ;
				//set_bkg_tiles2(5,12,1,1,&wtile) ;
				wtile = 0xA9U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+8L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+8L,&wtile,1L) ;
				//set_bkg_tiles2(6,12,1,1,&wtile) ;
				break ;

			}
		case 3 : 
			{
				wtile = 0x5DU ;
				set_data2((unsigned char*)0x9800+(12L*32L)+6L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+6L,&wtile,1L) ;
				//set_bkg_tiles2(4,12,1,1,&wtile) ;
				wtile = 0xA2U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+7L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+7L,&wtile,1L) ;
				//set_bkg_tiles2(5,12,1,1,&wtile) ;
				wtile = 0xA3U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+8L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+8L,&wtile,1L) ;
				//set_bkg_tiles2(6,12,1,1,&wtile) ;
				break ;

			}
		case 4 : 
			{
				wtile = 0x5DU ;
				set_data2((unsigned char*)0x9800+(12L*32L)+6L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+6L,&wtile,1L) ;
				//set_bkg_tiles2(4,12,1,1,&wtile) ;
				wtile = 0xA0U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+7L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+7L,&wtile,1L) ;
				//set_bkg_tiles2(5,12,1,1,&wtile) ;
				wtile = 0xA1U ;
				set_data2((unsigned char*)0x9800+(12L*32L)+8L,&wtile,1L) ;
				set_data2((unsigned char*)0x9C00+(12L*32L)+8L,&wtile,1L) ;
				//set_bkg_tiles2(6,12,1,1,&wtile) ;
				break ;

			}
		default : break;


	}
	enable_interrupts2() ;
//	if (oldv==1)
	//VBK_REG = 1 ;
}

void dowinds() 
{
	UBYTE q ;

	if ( inside>1 )
		return ;

	q = winddir ;
	while ( q==winddir )
	{
		q = make_rnd(9) ;
		if ( q>=5 )
			q-=4 ;
	}

	winddir = q ;
	writewind() ;

}
UBYTE whirlvars[] = {
	0x00,0x01,
	0x01,0x01,
	0x01,0x00,
	0x01,0xFFU,
	0x00,0xFFU,
	0xFFU,0xFFU,
	0xFFU,0x00,
	0xFFU,0x01
};
unsigned char shipdestroyed1[] = {
	'A'+0x1D,0x5D,'S'+0x1D,'H'+0x1D,'I'+0x1D,'P'+0x1D,0x5D,'W'+0x1D,'A'+0x1D,'S'+0x1D,0x5D,0x5D, 
} ;
unsigned char shipdestroyed2[] = {
	'D'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,'R'+0x1D,'O'+0x1D,'Y'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5D,0x5D, 
} ;


extern UBYTE hitship ;

void dowhirl()
{
	UBYTE q ;
	UBYTE newx, newy ;
	UBYTE bkgx,bkgy ;
	unsigned char wtile,wtile2 ;


	if ( (inside!=0)||(hitship==1) )
		return ;

	if ( make_rnd(8)==0 )
	{
		q = make_rnd(8) ;
		whirldirectx = whirlvars[q<<1] ;
		whirldirecty = whirlvars[(q<<1)+1] ;


	}
	else
	{
		newx = (monsters[31].x+whirldirectx)&0x3f ;
		newy = (monsters[31].y+whirldirecty)&0x3f ;
		wtile = *((unsigned char*)0xA000+(((UWORD)newy)<<6)+((UWORD)newx)) ;
		if ( (wtile==0)||(wtile==0x0E) )
		{
			wtile2 = wtile ;
			*((unsigned char*)0xA000+(((UWORD)newy)<<6)+((UWORD)newx)) = 0x0F ;
			*((unsigned char*)0xA000+(((UWORD)(monsters[31].y))<<6)+((UWORD)(monsters[31].x))) = 0x00 ;
			bkgx = ((monsters[31].x)-screenx)&0x3F ;
			bkgy = ((monsters[31].y)-screeny)&0x3F ;
			if ( (bkgx<11) &&(bkgy<11) )
			{
				get_bkg_tiles2(bkgx+1,bkgy+1,1,1,&wtile) ;
				if ( wtile!=0x3B )
				{
					wtile = 0x00 ;
					set_bkg_tiles2(bkgx+1,bkgy+1,1,1,&wtile) ;
				}
			}
			bkgx = (newx-screenx)&0x3F ;
			bkgy = (newy-screeny)&0x3F ;
			if ( (bkgx<11) &&(bkgy<11) )
			{
				get_bkg_tiles2(bkgx+1,bkgy+1,1,1,&wtile) ;
				if ( wtile!=0x3B )
				{
					wtile = 0x0F ;
					set_bkg_tiles2(bkgx+1,bkgy+1,1,1,&wtile) ;
				}
			}

			monsters[31].x = newx ;
			monsters[31].y = newy ;

			if ( (newx==playerx)&&(newy==playery) )
			{
				hitship=1 ;
				transport = 1 ;


			}
			if ( wtile2==0x0E )
			{
				writegamemessage(shipdestroyed1) ;
				writegamemessage(shipdestroyed2) ;
				whirlpoolsfx(250U) ;

			}

		}
		else
		{
			q = make_rnd(8) ;
			whirldirectx = whirlvars[q<<1] ;
			whirldirecty = whirlvars[(q<<1)+1] ;

		}


	}


}
