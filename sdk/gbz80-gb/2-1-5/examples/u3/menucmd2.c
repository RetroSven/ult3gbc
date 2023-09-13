#include <gb.h>
#include "u3.h"

#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

extern PLAYER players[] ;
extern MONSTER monsters[] ;
extern UBYTE nummonsters ;
extern UBYTE numplayers; 

extern UBYTE playerx ;
extern UBYTE playery ;
extern UBYTE screenx ;
extern UBYTE screeny ;
extern UBYTE need_refresh ;
extern UBYTE inside ;
extern UBYTE transport ;

extern UWORD party_specials ;
extern UBYTE extragame ;

extern UBYTE numalive ;

extern UBYTE stoptime ;

extern unsigned char *vidbase ;

extern UBYTE delayscroll ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern unsigned char screenbuf3[] ;
extern UBYTE mapnum ;

unsigned char notallowed[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'A'+0x1D,'L'+0x1D,'L'+0x1D,'O'+0x1D,'W'+0x1D,'E'+0x1D,'D'+0x1D,0x82, 
} ;

unsigned char weargrid[] = {
	1,1,0,0,0,0,0,1,  //alchemist
	1,1,1,0,0,0,0,1,  //barbarian
	1,1,1,1,0,0,0,1,  //cleric
	1,1,0,0,0,0,0,1,  //druid
	1,1,1,1,1,1,1,1,  //fighter
	1,1,1,0,0,0,0,1,  //illusionist
	1,1,0,0,0,0,0,1,  //lark
	1,1,1,1,1,0,0,1,  //paladin
	1,1,1,1,1,1,1,1,  //ranger
	1,1,1,0,0,0,0,1,  //thief
	1,1,0,0,0,0,0,1,  //wizard


} ;

unsigned char readygrid[] = {
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


unsigned char unlockmsg[] = {
	'U'+0x1D,'N'+0x1D,'L'+0x1D,'O'+0x1D,'C'+0x1D,'K'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5d,0x5d,0x5d
} ;

unsigned char nokeysdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'K'+0x1D,'E'+0x1D,'Y'+0x1D,'S'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char golddat2[] = {
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D
} ;
unsigned char anddat2[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D
} ;

unsigned char successdat[] = {
	'S'+0x1D,'U'+0x1D,'C'+0x1D,'C'+0x1D,'E'+0x1D,'S'+0x1D,'S'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char watchoutdat[] = {
	'W'+0x1D,'A'+0x1D,'T'+0x1D,'C'+0x1D,'H'+0x1D,0x5D,'O'+0x1D,'U'+0x1D,'T'+0x1D,0x82,0x5d,0x5d
};

unsigned char faileddat[] = {
	'F'+0x1D,'A'+0x1D,'I'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char readieddat2[] = {
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D

} ;
unsigned char readydat2[] = {
	'R'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,'Y'+0x1D,0x5D,'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'M'+0x1D,'O'+0x1D,'R'+0x1D,0x5d,0x5d
} ;

unsigned char onlyinsidedat[] = {
	'O'+0x1D,'N'+0x1D,'L'+0x1D,'Y'+0x1D,0x5D,'I'+0x1D,'N'+0x1D,'S'+0x1D,'I'+0x1D,'D'+0x1D,'E'+0x1D,0x82
};

unsigned char yesorno[] = {
	'N'+0x1D,'O'+0x1D,0x5d,0x5d,0x5d,0x5d,0x5d,
	'Y'+0x1D,'E'+0x1D,'S'+0x1D,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char savegamemsg1[] = {
	'S'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'M'+0x1D,'E'+0x1D,0x83,0x5d,0x5d
};
unsigned char savegamemsg2[] = {
	'D'+0x1D,'O'+0x1D,0x5D,'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'T'+0x1D,'U'+0x1D,'R'+0x1D,'N'+0x1D,0x5d
};

unsigned char savegamemsg3[] = {
	'O'+0x1D,'F'+0x1D,'F'+0x1D,0x5D,'G'+0x1D,'A'+0x1D,'M'+0x1D,'E'+0x1D,'B'+0x1D,'O'+0x1D,'Y'+0x1D,0x5d
};

unsigned char savegamemsg4[] = {
	'S'+0x1D,'A'+0x1D,'V'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x84,0x84,0x84,0x84,0x84,0x5d
};


unsigned char weaponsdat4[] = {
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
unsigned char armorsdat4[] = {
	'S'+0x1D,'K'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'C'+0x1D,'L'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,0X5D,0X5D,0X5D,
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,
	'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,
	0x91,0x7A,0X5D,'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,
	0x91,0x7A,0X5D,'P'+0x1D,'L'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,
	'E'+0x1D,'X'+0x1D,'O'+0x1D,'T'+0x1D,'I'+0x1D,'C'+0x1D,0X5D,0X5D
} ;

unsigned char handitems[] = {
	'F'+0x1D,'O'+0x1D,'O'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 
	'K'+0x1D,'E'+0x1D,'Y'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
	'G'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D, 
	'T'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D, 
	'P'+0x1D,'O'+0x1D,'W'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D, 
	'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D, 
	'A'+0x1D,'R'+0x1D,'M'+0x1D,'O'+0x1D,'R'+0x1D,'S'+0x1D,0x5D
};

unsigned char stoptimemsg[] = {
	'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,'S'+0x1D,'T'+0x1D,'O'+0x1D,'P'+0x1D,'P'+0x1D,'E'+0x1D,'D'+0x1D
};

UBYTE itemvals[] = {
	4,0,
	4,2,
	2,13,
	2,12,
	2,15,
	2,14,
	1,18,
	1,34
} ;

unsigned char modifymsg1[] = {
	'M'+0x1D,'O'+0x1D,'D'+0x1D,'I'+0x1D,'F'+0x1D,'Y'+0x1D,0x5D,'O'+0x1D,'R'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D
} ;

unsigned char modifymsg2[] = {
	'C'+0x1D,'H'+0x1D,'A'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,0x5D,'W'+0x1D,'I'+0x1D,'T'+0x1D,'H'+0x1D,0x5D
};

unsigned char joinmsg1[] = {
	'J'+0x1D,'O'+0x1D,'I'+0x1D,'N'+0x1D,0x5D,'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'O'+0x1D
} ;

unsigned char canceldat[] = {
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x5d,0x5d,0x5d
} ;

unsigned char howmuch[] = {
	'A'+0x1D,'M'+0x1D,'O'+0x1D,'U'+0x1D,'N'+0x1D,'T'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char handfrom[] = {
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'F'+0x1D,'R'+0x1D,'O'+0x1D,'M'+0x1D,0x5d,0x5d,0x5d
} ;
unsigned char handwhat[] = {
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'W'+0x1D,'H'+0x1D,'A'+0x1D,'T'+0x1D,0x83,0x5d,0x5d
} ;

unsigned char handto[] = {
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5d,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char whodat3[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};
unsigned char donedat[] = {
	'D'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char notheredat2[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D
} ;

unsigned char chardat5[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};
unsigned char charstat5[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};
unsigned char nopowderdat2[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'W'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,0x82,0x5d
} ;

unsigned char dirdat3[] = {
	'D'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x83,0x5d,0x5D
};

unsigned char emptydat2[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char deaddat2[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82 
} ;

void formatnumber7(UWORD num,UBYTE length)
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

void charscreen5(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat5);

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber7(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat5+(UWORD)player->status );

	formatnumber7(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber7(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber7(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}
unsigned char dirarr4[] = {
	'N'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

UBYTE getdir3()
{
	UBYTE dir, p, keys ;
/*   
   memset(screenbuf3,0x5D,12L) ;
   for (p = 0 ; p<5 ; p++)
	  set_bkg_tiles2(0,p+13,12,1,(unsigned char*)screenbuf3) ;

   memset(screenbuf3,0x00,12L) ;
   VBK_REG=1 ;
   
   for (p = 0 ; p<5 ; p++)
	  set_bkg_tiles2(0,p+13,12,1,(unsigned char*)screenbuf3) ;
   
   VBK_REG=0 ;

   set_bkg_tiles2(1,15,9,1,dirdat3);
   set_bkg_tiles2(1,16,9,1,dirdat3+9L);
*/  
	writegamemessage(dirdat3) ;

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
		writegamemessage(dirarr4+(((UWORD)(dir-1))*12L)) ;

	}

	waitpadup() ;
	return dir ;


}


UBYTE choosechar3()
{
	UBYTE p, keys, currchar ;


	writegamemessage(whodat3) ;

	for ( p=0; p<4 ; p++ )
		charscreen5(&(players[p]),p) ;

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

UBYTE getmenuselection4(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
						unsigned char *descptrdat)
{
	UBYTE p ;
	UBYTE currline ;
	UBYTE keys ;

	if ( LCDC_REG&0x10 )   //select $9C00-$9FFF
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

UWORD getamt(UBYTE digits, UWORD maxamt)
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
	formatnumber7(amt,4) ;
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
					formatnumber7(amt,4) ;
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
				formatnumber7(amt,4) ;
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


UBYTE dohand()
{
	UBYTE fromchar, tochar, joykeys, curritem ;
	UWORD *wordptr ;
	UBYTE *frombyteptr, *tobyteptr ;
	UBYTE isbyte ;
	UBYTE currweapon, currarmor, nextptr  ;
	UBYTE maxpos, done ;
	unsigned char *thedata ;
	UWORD amt ;
	UWORD maxamt ;



	writegamemessage(handfrom) ;

	fromchar = choosechar3() ;

	if ( fromchar==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	writegamemessage(handto) ;

	tochar = choosechar3() ;

	if ( (tochar==99)||(tochar==fromchar) )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	writegamemessage(handwhat) ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	memset(screenbuf3,0x04,12L) ;
	set_bkg_tiles2(0,17,7,1,handitems) ;
	VBK_REG=1 ;
	set_bkg_tiles2(0,17,7,1,screenbuf3) ;
	VBK_REG=0 ;

	curritem = 0 ;

	waitpadup() ;
	while ( 1 )
	{
		joykeys = joypad() ;
		if ( (joykeys&J_UP)||(joykeys&J_RIGHT) )
		{
			if ( curritem==7 )
				curritem = 0 ;
			else
				curritem++ ;
			set_bkg_tiles2(0,17,7,1,handitems+(UWORD)(curritem*7)) ;
			waitpadup() ;
		}
		if ( (joykeys&J_DOWN)||(joykeys&J_LEFT) )
		{
			if ( curritem==0 )
				curritem = 7 ;
			else
				curritem-- ;
			set_bkg_tiles2(0,17,7,1,handitems+(UWORD)(curritem*7)) ;
			waitpadup() ;
		}
		if ( joykeys&J_B )
		{
			curritem = 99 ;
			break ;
		}
		if ( joykeys&J_A )
			break ;
	}

	waitpadup() ;

	memset(screenbuf3,0x00,7L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(0,17,7,1,screenbuf3) ;
	VBK_REG=0 ;

	if ( curritem==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	isbyte = (itemvals[curritem*2]<4) ;
	if ( curritem==6 )
	{
		maxpos = 15 ;
		thedata = weaponsdat4 ;
		frombyteptr = (UBYTE*)(&(players[fromchar].weapons)) ;
	}
	if ( curritem==7 )
	{
		maxpos = 7 ;
		thedata = armorsdat4 ;
		frombyteptr = (UBYTE*)&((players[fromchar].armors)) ;
	}

	if ( curritem>5 )
	{
		nextptr = 1 ;

		while ( nextptr<maxpos+1 )
			if ( *(frombyteptr+(UWORD)nextptr) )
				break ;
			else
				nextptr++ ;
		if ( nextptr==maxpos+1 )
		{
			writegamemessage(emptydat2) ;
			return 0 ;

		}

		currweapon = nextptr ;
		memset(screenbuf3,0x5D,12L) ;
		memcpy(screenbuf3,thedata+((UWORD)currweapon*8L),8L) ;
		set_bkg_tiles2(0,17,12,1,screenbuf3) ;

		memset(screenbuf3,0x04,12L) ;
		VBK_REG=1 ;
		set_bkg_tiles2(0,17,12,1,screenbuf3) ;
		VBK_REG=0 ;

		waitpadup() ;
		done=0 ;
		while ( done==0 )
		{
			joykeys = joypad() ;
			if ( (joykeys&J_RIGHT)||(joykeys&J_UP) )
			{
				if ( currweapon==maxpos )
					nextptr = 1 ;
				else
					nextptr	= currweapon+1 ;

				while ( 1 )
				{
					if ( *(frombyteptr+(UWORD)nextptr) )
						break ;
					else
						nextptr++ ;
					if ( nextptr==maxpos+1 )
						nextptr=1 ;
				}

				currweapon = nextptr ;
				memset(screenbuf3,0x5D,12L) ;
				memcpy(screenbuf3,thedata+((UWORD)currweapon*8L),8L) ;
				set_bkg_tiles2(0,17,12,1,screenbuf3) ;


				waitpadup() ;
			}

			if ( (joykeys&J_LEFT)||(joykeys&J_DOWN) )
			{
				if ( currweapon==1 )
					nextptr = maxpos ;
				else
					nextptr	= currweapon-1 ;

				while ( 1 )
				{
					if ( *(frombyteptr+(UWORD)nextptr) )
						break ;
					else
						if ( nextptr==1 )
						nextptr=maxpos ;
					else
						nextptr-- ;
				}

				currweapon = nextptr ;
				memset(screenbuf3,0x5D,12L) ;
				memcpy(screenbuf3,thedata+((UWORD)currweapon*8L),8L) ;
				set_bkg_tiles2(0,17,12,1,screenbuf3) ;

				waitpadup() ;
			}

			if ( (joykeys&J_B)||(joykeys&J_A) )
			{
				memset(screenbuf3,0x00,12L);
				VBK_REG=1 ;
				set_bkg_tiles2(0,17,12,1,screenbuf3) ;
				VBK_REG=0 ;
				waitpadup() ;
				if ( joykeys&J_B )
				{
					//writegamemessage(canceldat) ;
					return 0 ;
				}
				else
					done=1 ;
			}

		}


		frombyteptr = ((UBYTE*)&(players[fromchar].food))+(UWORD)itemvals[curritem*2+1];
		frombyteptr += (UWORD)currweapon ;
		tobyteptr   = ((UBYTE*)&(players[  tochar].food))+(UWORD)itemvals[curritem*2+1];
		tobyteptr   += (UWORD)currweapon ;


	}
	else
	{
		frombyteptr = ((UBYTE*)&(players[fromchar].food))+(UWORD)itemvals[curritem*2+1];
		tobyteptr   = ((UBYTE*)&(players[tochar].food))+(UWORD)itemvals[curritem*2+1];
	}


	writegamemessage(howmuch) ;
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;

	if ( itemvals[curritem*2]==4 )
	{
		if ( 9999-(*((UWORD*)tobyteptr)) > (*((UWORD*)frombyteptr)) )
			maxamt = (*((UWORD*)frombyteptr)) ;
		else
			maxamt = 9999-(*((UWORD*)tobyteptr)) ;
	}
	if ( itemvals[curritem*2]==2 )
	{
		if ( 99-(*(tobyteptr)) > (*(frombyteptr)) )
			maxamt = (UWORD)(*(frombyteptr)) ;
		else
			maxamt = (UWORD)(99-(*tobyteptr)) ;
	}
	if ( itemvals[curritem*2]==1 )
	{
		if ( 9-(*(tobyteptr)) > (*(frombyteptr)) )
			maxamt = (UWORD)(*(frombyteptr)) ;
		else
			maxamt = (UWORD)(9-(*tobyteptr)) ;
	}

	amt = getamt(itemvals[curritem*2],maxamt) ;
	if ( amt==0L )
	{
		writegamemessage(emptydat2) ;
		return 0 ;
	}
	writegamemessage(donedat) ;   
	if ( isbyte )
	{
		*tobyteptr += (UBYTE)amt ;
		*frombyteptr -= (UBYTE)amt ;

	}
	else
	{
		*((UWORD*)tobyteptr) += amt ;
		*((UWORD*)frombyteptr) -= amt ;

	}
	return 1 ;
}

UBYTE dojoin() 
{
	UBYTE pnum,p ;
	UWORD amt ;

	writegamemessage(joinmsg1) ;
	pnum = choosechar3() ;
	if ( pnum==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	for ( p=0 ; p<numplayers ; p++ )
	{
		if ( p!=pnum )
		{
			amt = players[p].gold ;
			if ( amt+players[pnum].gold > 9999 )
				amt = 9999-players[pnum].gold ;
			players[pnum].gold += amt ;
			players[p].gold -= amt ;
		}
	}
	writegamemessage(donedat) ;
	return 1; 

}
UBYTE domodify()
{
	UBYTE fromchar, tochar ;

	writegamemessage(modifymsg1) ;
	fromchar = choosechar3() ;
	if ( fromchar==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	writegamemessage(modifymsg2) ;
	tochar = choosechar3() ;
	if ( (tochar==99)||(tochar==fromchar) )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	if ( (tochar>3)||(fromchar>3) )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	memcpy(&players[4],&players[fromchar],127UL) ;
	memcpy(&players[fromchar],&players[tochar],127UL) ;
	memcpy(&players[tochar],&players[4],127UL) ;

	players[fromchar].inparty = fromchar+1 ;
	players[tochar].inparty = tochar+1 ;
	charscreen5(&(players[tochar]),tochar) ;
	charscreen5(&(players[fromchar]),fromchar) ;
	return 1 ;
}

UBYTE donegate()
{
	UBYTE pnum ;

	pnum = choosechar3() ;

	if ( pnum==99 )
	{
//		writegamemessage(canceldat) ;
		return 0 ;
	}
	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat2) ;
		return 1 ;
	}

	if ( players[pnum].powders )
	{
		(players[pnum].powders)-- ;
		stoptime = 10 ;
		writegamemessage(stoptimemsg) ;
	}
	else
		writegamemessage(nopowderdat2) ;

	return 1 ;
}

UBYTE doquitsave()
{

//save characters in roster
//save sosaria map
//save pnum1, pnum2, pnum3, pnum4 (rosterpos)
//save playerxy,screenxy
//save transport
//save monsternum
//save monsters data

// when restoring, moons==0,0
// playernum = 

	UBYTE yesno, p, n, inparty ;
	unsigned char cpybuf[64] ;
	unsigned char *ctr ;

	if ( inside )
	{
		writegamemessage(notheredat2) ;
		return 1 ;
	}

	writegamemessage(savegamemsg1) ;
	yesno = getmenuselection4(2,yesorno,NULL,NULL) ;

	if ( yesno==1 )
	{
		memset(screenbuf3,0x5d,12L) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(savegamemsg2) ;
		writegamemessage(savegamemsg3) ;
		writegamemessage(screenbuf3) ;
		writegamemessage(savegamemsg4) ;
		disable_interrupts2() ;
		SWITCH_RAM_MBC5(0) ;

		for ( n=0 ; n<4 ; n++ )
			if ( players[n].inparty )
				for ( inparty = 0 ; inparty<7 ; inparty++ )
					if ( players[n].name[inparty] != 0x5D )
						players[n].name[inparty] -= 33 ;


		for ( p=0 ; p<numplayers ; p++ )
		{
			memcpy((unsigned char*)(0xA004+(((UWORD)players[p].rosterpos)<<7UL)),&players[p],127L) ;
			*(unsigned char*)(0xB604+(UWORD)p) = (unsigned char)players[p].rosterpos ;
		}
		for ( p=numplayers ; p<4; p++ )
			*(unsigned char*)(0xB604+(UWORD)p) = 99 ;

		for ( n=0 ; n<4 ; n++ )
			if ( players[n].inparty )
				for ( inparty = 0 ; inparty<7 ; inparty++ )
					if ( players[n].name[inparty] != 0x5D )
						players[n].name[inparty] += 33 ;

		for ( p=0 ; p<64 ; p++ )
		{
			SWITCH_RAM_MBC5(1) ;
			memcpy(cpybuf,(unsigned char*)(0xA000+(((UWORD)p)<<6)),64L) ;
			SWITCH_RAM_MBC5(0) ;
			memcpy((unsigned char*)(0xA604+(((UWORD)p)<<6)),cpybuf,64L) ;
		}

		*(unsigned char*)(0xB608) = (unsigned char)playerx ;
		*(unsigned char*)(0xB609) = (unsigned char)playery ;
		*(unsigned char*)(0xB60A) = (unsigned char)screenx ;
		*(unsigned char*)(0xB60B) = (unsigned char)screeny ;
		*(unsigned char*)(0xB60C) = (unsigned char)transport ;
		*(unsigned char*)(0xB60D) = (unsigned char)nummonsters ;
		memcpy((unsigned char*)0xB60E,monsters,MONSTERSIZE*32L) ;
		*(UWORD*)(0xB700) = party_specials ;  //party_special ;
		*(UBYTE*)(0xB702) = extragame ;	 //extragame ;

		n=0 ;
		for ( ctr=(unsigned char*)0xA000 ; ctr < (unsigned char*)0xBFFF ; ctr++ )
			n += *ctr ;
		memcpy((unsigned char*)(0xBFFF),&n,1L) ;

		SWITCH_RAM_MBC5(1) ;
		enable_interrupts2() ;
		writegamemessage(donedat) ;


	}
	else
		return 0 ;
	//	writegamemessage(canceldat) ;

	return 1 ;

}

void loadgame()
{

//save characters in roster
//save sosaria map
//save pnum1, pnum2, pnum3, pnum4 (rosterpos)
//save playerxy,screenxy
//save transport
//save monsternum
//save monsters data

// when restoring, moons==0,0
// playernum = 
	unsigned char cpybuf[64] ;
	UBYTE p ;

	SWITCH_RAM_MBC5(0) ;

	for ( p=0 ; p<64 ; p++ )
	{
		SWITCH_RAM_MBC5(0) ;
		memcpy(cpybuf,(unsigned char*)(0xA604+(((UWORD)p)<<6)),64L) ;
		SWITCH_RAM_MBC5(1) ;
		memcpy((unsigned char*)(0xA000+(((UWORD)p)<<6)),cpybuf,64L) ;
	}

	SWITCH_RAM_MBC5(0) ;

	playerx =*(unsigned char*)(0xB608);
	playery =*(unsigned char*)(0xB609);
	screenx =*(unsigned char*)(0xB60A);
	screeny =*(unsigned char*)(0xB60B);
	transport =*(unsigned char*)(0xB60C);
	nummonsters =*(unsigned char*)(0xB60D);
	party_specials = *(UWORD*)(0xB700) ;  //party_special ;
	extragame = *(UBYTE*)(0xB702) ;	 //extragame ;

	memcpy(monsters,(unsigned char*)0xB60E,MONSTERSIZE*32L) ;



}

unsigned char noweapons15[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'W'+0x1D,'E'+0x1D,'A'+0x1D,'P'+0x1D,'O'+0x1D,'N'+0x1D,'S'+0x1D,0x82U,0x5D
} ;

unsigned char noarmors15[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'A'+0x1D,'R'+0x1D,'M'+0x1D,'O'+0x1D,'R'+0x1D,0x82U,0x5D,0x5D,0x5D
} ;

UBYTE dowearready(UBYTE which)
{
	UBYTE done,joykeys,currweapon,nextptr, pnum, olditem ;
	unsigned char *listdata ;
	UBYTE *playeritems ;
	UBYTE maxnum ;
	unsigned char *thegrid ;
	UBYTE lcv1 ;

	pnum = choosechar3();
	if ( pnum==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	if ( players[pnum].status >1 )
	{
		writegamemessage(deaddat2) ;
		return 1 ;

	}
	done=0 ;
	nextptr = 0 ;

	if ( which==0 )
	{
		listdata = weaponsdat4 ;
		maxnum = 16 ;
		playeritems = players[pnum].weapons ;
		olditem = players[pnum].weapon ;
		thegrid = readygrid ;

		for ( lcv1 = 0 ; lcv1 < maxnum ; lcv1++ )
		{
			if ( players[pnum].weapons[lcv1] != 0 )
			{
				nextptr = lcv1 ;
				break ;
			}

			if ( lcv1 == maxnum-1 )
			{
				writegamemessage(noweapons15) ;
				return 0 ;
			}

		}

	}
	else
	{
		listdata = armorsdat4 ;
		maxnum = 8 ;
		playeritems = players[pnum].armors ;
		olditem = players[pnum].armor ;
		thegrid = weargrid ;

		for ( lcv1 = 0 ; lcv1 < maxnum ; lcv1++ )
		{
			if ( players[pnum].armors[lcv1] != 0 )
			{
				nextptr = lcv1 ;
				break ;
			}
			if ( lcv1 == maxnum-1 )
			{
				writegamemessage(noarmors15) ;
				return 0 ;
			}

		}

	}

	writegamemessage(readydat2+((UWORD)which*12L)) ;
	memset(screenbuf3,0x5d,12L) ;
	writegamemessage(screenbuf3) ;

	currweapon = nextptr ;
	memcpy(screenbuf3,listdata+((UWORD)currweapon*8L),8L) ;
	set_bkg_tiles2(0,17,12,1,screenbuf3) ;

	memset(screenbuf3,0x04,12L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(0,17,12,1,screenbuf3) ;
	VBK_REG=0 ;

	waitpadup() ;
	while ( done==0 )
	{
		joykeys = joypad() ;
		if ( joykeys&J_RIGHT )
		{
			if ( currweapon==maxnum-1 )
				nextptr = 0 ;
			else
				nextptr	= currweapon+1 ;

			while ( 1 )
			{
				if ( *(playeritems+(UWORD)nextptr) )
					break ;
				else
					nextptr++ ;

				if ( nextptr==maxnum )
					nextptr=0 ;
			}

			currweapon = nextptr ;
			memset(screenbuf3,0x5D,12L) ;
			memcpy(screenbuf3,listdata+((UWORD)currweapon*8L),8L) ;
			set_bkg_tiles2(0,17,12,1,screenbuf3) ;


			waitpadup() ;
		}

		if ( joykeys&J_LEFT )
		{
			if ( currweapon==0 )
				nextptr = maxnum-1 ;
			else
				nextptr	= currweapon-1 ;

			while ( 1 )
			{
				if ( *(playeritems+(UWORD)nextptr) )
					break ;
				else
					if ( nextptr==0 )
					nextptr=maxnum-1 ;
				else
					nextptr-- ;
			}

			currweapon = nextptr ;
			memset(screenbuf3,0x5D,12L) ;
			memcpy(screenbuf3,listdata+((UWORD)currweapon*8L),8L) ;
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


	memset(screenbuf3,0x5D,12L) ;
	memcpy(screenbuf3,listdata+((UWORD)currweapon*8L),8L) ;
	set_data2((unsigned char*)0x9800+(32L*17),screenbuf3,12L) ;
	set_data2((unsigned char*)0x9C00+(32L*17),screenbuf3,12L) ;


	if ( done==2 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	if ( *(thegrid+ ((UWORD)((players[pnum].skill)*maxnum)) + (UWORD)currweapon)==0 )
	{
		writegamemessage(notallowed) ;

	}
	else
	{
		writegamemessage(readieddat2) ;

		if ( which==0 )
			players[pnum].weapon = currweapon ;
		else
			players[pnum].armor	= currweapon ;

		(*(playeritems+(UWORD)currweapon))-- ;
		(*(playeritems+(UWORD)olditem))++ ;
	}

	return 1 ;


}
UBYTE dosteal()
{
	UBYTE pnum, dir, dist,p;
	UBYTE currx, curry, mapx, mapy, found ;
	unsigned char atile ;
	UBYTE stealskill ;
	UBYTE gold, extratype ;

	if ( !inside )
	{
		writegamemessage(onlyinsidedat) ;
		return 1 ;
	}

	pnum = choosechar3() ;
	if ( pnum==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat2) ;
		return 1 ;
	}

	dir = getdir3() ;
	if ( !dir )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	dist = 0 ;

	currx = 5 ;
	curry = 5 ;
	mapx = playerx ;
	mapy = playery ;
	found = 0 ;

	while ( (dist<3)&&(!found) )
	{

		if ( dir==1 )
		{
			curry-- ;
			mapy-- ;
		}
		if ( dir==2 )
		{
			curry++ ;
			mapy++ ;
		}
		if ( dir==3 )
		{
			currx++ ;
			mapx++ ;
		}
		if ( dir==4 )
		{
			currx-- ;
			mapx-- ;
		}

		get_bkg_tiles2(currx+1,curry+1,1,1,&atile) ;
		if ( (dist==0)&&((atile<0x3C)||(atile>0x56)) )
			break ;

		if ( (dist==1)&&(atile!=0x0B)&&(atile!=0x16) )
			break ;

		if ( (dist==2)&&(atile!=0x0C) )
			break ;

		if ( dist==2 )
			found= 1 ;
		dist++ ;

	}

	if ( found )
	{
		stealskill = players[pnum].dex ;

		if ( players[pnum].skill==9 ) //thief
			stealskill += 0x80U;
		else
			if ( (players[pnum].skill==0) || 
				 (players[pnum].skill==1) || 
				 (players[pnum].skill==5) || 
				 (players[pnum].skill==8) )
			stealskill += 0x40 ;

		if ( make_rnd(0) >= stealskill )
		{//didn't succeed
			if ( ((make_rnd(0))&0x03)==0 )
			{
				writegamemessage(watchoutdat) ;
				for ( p=0 ; p<32 ; p++ )
				{
					if ( monsters[p].tile==0x18 )
						monsters[p].attribs = 0x11 ;
				}
				attackmisssfx(120U) ;
				return 1 ;

			}
			else
			{
				writegamemessage(faileddat) ;
				return 1 ;

			}
		}
		else
		{
			writegamemessage(successdat) ;
			gold = make_rnd(0x64) | 0x30 ;
			if ( gold >0x64 )
				gold -= 0x64 ;

			memset(screenbuf3,0x5D,12L) ;
			formatnumber7((UWORD)gold,2) ;
			memcpy(screenbuf3+3L,golddat2,4L) ;
			writegamemessage(screenbuf3) ;
			players[pnum].gold += (UWORD)gold ;
			if ( players[pnum].gold > 9999 )
				players[pnum].gold = 9999 ;

			if ( make_rnd(0)<0x40 )
			{
				memset(screenbuf3,0x5D,12L) ;
				memcpy(screenbuf3,anddat2,3L) ;

				extratype = make_rnd(0) ;
				if ( (extratype & 0x80U)==0 )
				{
					extratype &= (make_rnd(0))&0x07 ;
					if ( extratype )
						if ( players[pnum].weapons[extratype] < 9 )
						{
							memcpy(screenbuf3+4L,weaponsdat4+(UWORD)((extratype)<<3),8L) ;
							(players[pnum].weapons[extratype])++ ;
							writegamemessage(screenbuf3) ;
						}
				}
				else
					extratype = 0 ;

				if ( extratype==0 )
				{
					extratype = make_rnd(0) ;
					if ( (extratype & 0x80U)==0 )
					{
						extratype &= (make_rnd(0))&0x03 ;
						if ( extratype )
							if ( players[pnum].armors[extratype] < 9 )
							{
								memcpy(screenbuf3+4L,armorsdat4+(UWORD)((extratype)<<3),8L) ;
								(players[pnum].armors[extratype])++ ;
								writegamemessage(screenbuf3) ;
							}

					}


				}


			}
			atile = 0x0b ;
			set_bkg_tiles2(currx+1,curry+1,1,1,&atile) ;
			*((unsigned char*)0xA000+((UWORD)(((UWORD)(mapy))<<6))+(UWORD)(mapx)) = atile ;

		}



	}
	else
	{
		writegamemessage(emptydat2) ;
		return 1;

	}
	return 1 ;

}
UBYTE dounlock()
{
	UBYTE pnum,dir, currx, curry ;
	UBYTE mapx, mapy ;
	unsigned char atile,btile ;

	pnum = choosechar3() ;
	if ( pnum==99 )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat2) ;
		return 1 ;
	};

	if ( players[pnum].keys==0 )
	{
		writegamemessage(nokeysdat) ;
		return 1 ;

	}
	dir = getdir3() ;
	if ( !dir )
	{
		//writegamemessage(canceldat) ;
		return 0 ;
	}

	currx = 5 ;
	curry = 5 ;
	mapx = playerx ;
	mapy = playery ;

	if ( dir==1 )
	{
		curry-- ;
		mapy-- ;
	}
	if ( dir==2 )
	{
		curry++ ;
		mapy++ ;
	}
	if ( dir==3 )
	{
		currx++ ;
		mapx++ ;
	}
	if ( dir==4 )
	{
		currx-- ;
		mapx-- ;
	}

	get_bkg_tiles2(currx+1,curry+1,1,1,&atile) ;

	if ( atile==0x45 )
	{
		(players[pnum].keys)-- ;
		writegamemessage(unlockmsg) ;
		get_bkg_tiles2(currx,curry+1,1,1,&atile) ;
		get_bkg_tiles2(currx+2,curry+1,1,1,&btile) ;

		if ( (atile==0x00)||(btile==0x00)||(atile==0x15)||(btile==0x15)||
			 (atile==0x0e)||(btile==0x0e) )
		{
			atile = 0 ;
			btile = 1 ;
		}
		else
		{
			atile = 0x0b ;
			btile = 0 ;
		}

		set_bkg_tiles2(currx+1,curry+1,1,1,&atile) ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(mapy))<<6))+(UWORD)(mapx)) = atile ;

		disable_interrupts2() ;
		VBK_REG=1 ;
		set_bkg_tiles2(currx+1,curry+1,1,1,&btile) ;
		VBK_REG=0 ;
		SWITCH_RAM_MBC5(3) ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(mapy))<<6))+(UWORD)(mapx)) = atile ;
		SWITCH_RAM_MBC5(1) ;
		enable_interrupts2() ;

	}
	else
	{
		writegamemessage(emptydat2) ;
		return 1 ;
	}

	return 1 ;
}

