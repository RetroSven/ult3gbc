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

extern UBYTE extragame ;

extern UBYTE inexodus ;

extern UBYTE peer_semaphore ;
extern UBYTE peermap ;

extern UBYTE ingenerator ;
extern UBYTE generatorx ;
extern UBYTE generatory ;
extern UBYTE generatortile ;

extern PLAYER players[] ;
extern MONSTER monsters[] ;
extern UBYTE nummonsters ;
extern UBYTE numplayers; 
extern UBYTE monsterattrib ;
extern UBYTE monsterpower ;

extern UBYTE cheat_xray ;
extern UBYTE cheat_nofight ;
extern UBYTE cheat_nohurt ;
extern UBYTE cheat_noblock ;
extern UBYTE cheat_fullmp ;
extern UBYTE cheat_noclass ;

extern UBYTE playerx ;
extern UBYTE playery ;
extern UBYTE screenx ;
extern UBYTE screeny ;
extern UBYTE need_refresh ;
extern UBYTE inside ;
extern UBYTE transport ;
extern UBYTE playerscreentile ;

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


UBYTE maxattribsdat[] = {
	75,75,75,75,    
	75,99,75,50,
	99,75,50,75,
	25,99,99,75,
	75,50,75,99

//'H'-0x04,'U'-0x04,'M'-0x04,'A'-0x04,'N'-0x04,0X5D,
//'E'-0x04,'L'-0x04,'F'-0x04,0X5D,0X5D,0X5D,
//'D'-0x04,'W'-0x04,'A'-0x04,'R'-0x04,'F'-0x04,0X5D,
//'F'-0x04,'U'-0x04,'Z'-0x04,'Z'-0x04,'Y'-0x04,0X5D,
//'B'-0x04,'O'-0x04,'B'-0x04,'B'-0x04,'I'-0x04,'T'-0x04

} ;

unsigned char shrinemap[] = {
	0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,
	0x3A,0x3A,0x3A,0x5D,0x5D,0x5D,0x5D,0x5D,0x3A,0x3A,0x3A,
	0x3A,0x3A,0x5D,0x5D,0x5D,0x26,0x5D,0x5D,0x5D,0x3A,0x3A,
	0x3A,0x5D,0x5D,0x5D,0x26,0x26,0x26,0x5D,0x5D,0x5D,0x3A,
	0x3A,0x5D,0x5D,0x5D,0x5D,0x26,0x5D,0x5D,0x5D,0x5D,0x3A,
	0x3A,0x5D,0x5D,0x5D,0x5D,0x26,0x5D,0x5D,0x5D,0x5D,0x3A,
	0x3A,0x5D,0x3A,0x5D,0x5D,0x5D,0x5D,0x5D,0x3A,0x5D,0x3A,
	0x3A,0x5D,0x3A,0x00,0x00,0x00,0x00,0x00,0x3A,0x5D,0x3A,
	0x3A,0x5D,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x5D,0x3A,
	0x3A,0x5D,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x3A,0x5D,0x3A,
	0x3A,0x5D,0x5D,0x3A,0x5D,0x5D,0x5D,0x3A,0x5D,0x5D,0x3A
};

unsigned char shazamdat[] = {
	'S'+0x1D,'H'+0x1D,'A'+0x1D,'Z'+0x1D,'A'+0x1D,'M'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d,0x5d,
};

unsigned char beoffdat[] = {
	'T'+0x1D,'H'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,'B'+0x1D,'E'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,'F'+0x1D,0x82 
} ;

unsigned char shrinetxt1[] = {
	0x5D,'S'+0x1D,'H'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'E'+0x1D,0x5D,'O'+0x1D,'F'+0x1D,0x5d,0x5d  
} ;
unsigned char shrineattribs[] = {
	0x5d,0x5d,'S'+0x1D,'T'+0x1D,'R'+0x1D,'E'+0x1D,'N'+0x1D,'G'+0x1D,'T'+0x1D,'H'+0x1D,0x5d,0x5d,
	0x5d,'D'+0x1D,'E'+0x1D,'X'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'T'+0x1D,'Y'+0x1D,0x5d,0x5d,
	'I'+0x1D,'N'+0x1D,'T'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,'I'+0x1D,'G'+0x1D,'E'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,
	0x5d,0x5d,0x5d,'W'+0x1D,'I'+0x1D,'S'+0x1D,'D'+0x1D,'O'+0x1D,'M'+0x1D,0x5d,0x5d,0x5d
};

unsigned char shrinetxt2[] = {
	0x5d,0x5d,'O'+0x1D,'F'+0x1D,'F'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5d,0x5d
} ;

unsigned char wistoolowdat[] = {
	'W'+0x1D,'I'+0x1D,'S'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,'O'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'W'+0x1D,0x82
};

unsigned char mptoolowdat[] = {
	'M'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,'O'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'W'+0x1D,0x82,0x5d 
};

unsigned char nogemsdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'G'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D
};

unsigned char whodat[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char noshipdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'S'+0x1D,'H'+0x1D,'I'+0x1D,'P'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d
} ;

unsigned char notheredat[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'H'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,0x82,0x5D,0x5D,0x5D
} ;

unsigned char chardat3[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};
unsigned char charstat3[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};
unsigned char anddat[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,
} ;

unsigned char faildat2[] = {
	'F'+0x1D,'A'+0x1D,'I'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char golddat[] = {
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D
} ;

unsigned char nochestdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char dirdat2[] = {
	'D'+0x1D,'I'+0x1D,'R'+0x1D,'E'+0x1D,'C'+0x1D,'T'+0x1D,'I'+0x1D,'O'+0x1D,'N'+0x1D,0x83,0x5d,0x5D
};

unsigned char emptydat[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char onlyfootdat[] = {
	'O'+0x1D,'N'+0x1D,'L'+0x1D,'Y'+0x1D,0x5D,'O'+0x1D,'N'+0x1D,0x5D,'F'+0x1D,'O'+0x1D,'O'+0x1D,'T'+0x1D
};

unsigned char notboardeddat[] = {
	'N'+0x1D,'O'+0x1D,'T'+0x1D,0x5D,'B'+0x1D,'O'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,'E'+0x1D,'D'+0x1D,0x5D
} ;

unsigned char deaddat[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82 
} ;
unsigned char weaponsdat3[] = {
	'H'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,'S'+0x1D,0X5D,0X5D,0X5D,
	'D'+0x1D,'A'+0x1D,'G'+0x1D,'G'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,0X5D,
	'M'+0x1D,'A'+0x1D,'C'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'S'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0X5D,0X5D,0X5D,
	'A'+0x1D,'X'+0x1D,'E'+0x1D,0X5D,0X5D,0X5D,0X5D,0X5D,
	'B'+0x1D,'O'+0x1D,'W'+0x1D,0X5D,0X5D,0X5D,0X5D,0X5D,
	'S'+0x1D,'W'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,0X5D,0X5D,0X5D,
	0x7A,'H'+0x1D,0X5D,'S'+0x1D,'W'+0x1D,'O'+0x1D,'R'+0x1D,'D'+0x1D,
	0x91,0x7A,0X5D,'A'+0x1D,'X'+0x1D,'E'+0x1D,0X5D,0X5D,
};

unsigned char armorsdat3[] = {
	'S'+0x1D,'K'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'C'+0x1D,'L'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,0X5D,0X5D,0X5D,
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,
	'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,
};


unsigned char clericormagedat2[] = {
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,
	'W'+0x1D,'I'+0x1D,'Z'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D
};

unsigned char clericspelldescdat2[] = {
	0x5D,'A'+0x1D,'P'+0x1D,'P'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,'U'+0x1D,'N'+0x1D,'E'+0x1D,'M'+0x1D,0x5D, 
	0x5D,'O'+0x1D,'P'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D,   
	0x5D,0x5D,0x5D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x79,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'A'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x7B,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'I'+0x1D,0x5D,
	0x5D,0x5D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x91,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x7D,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'V'+0x1D,'I'+0x1D,'E'+0x1D,'D'+0x1D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'S'+0x1D,'H'+0x1D,'O'+0x1D,'W'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'P'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x7D,0x7D,0x5D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,'S'+0x1D,'U'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,
	0x5D,'R'+0x1D,'A'+0x1D,'I'+0x1D,'S'+0x1D,'E'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7E,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	'A'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,0x5D,'S'+0x1D,'E'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'I'+0x1D,
	'R'+0x1D,'E'+0x1D,'T'+0x1D,'U'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,'A'+0x1D,'S'+0x1D,'H'+0x1D,'E'+0x1D,'D'+0x1D,
	0x5D,0x7F,0x7D,'M'+0x1D,'P'+0x1D,0x92,0x7D,'W'+0x1D,'I'+0x1D,'S'+0x1D,0x5D,0x5D
};

unsigned char clericspellsdat2[] = {
//b) Appar Unem - open chest without triggering trap
//c) Sanctu  - light healing
//h) Alcort - neutralize poison
//k) Sanctu Mani - powerful healing
//l) Vieda - shows surroundings - like peering into a gem
//n) Surmandum - raise dead - if it fails he/she will become ashes
//p) Anju Sermani - return ashed person to life - costs 5 wisdom points
	'A'+0x1D,'P'+0x1D,'P'+0x1D,'A'+0x1D,'R'+0x1D,'U'+0x1D,'N'+0x1D, 
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D, 
	'A'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D, 
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,'M'+0x1D, 
	'V'+0x1D,'I'+0x1D,'E'+0x1D,'D'+0x1D,'A'+0x1D,0x5D,0x5D, 
	'S'+0x1D,'U'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D, 
	'A'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,'S'+0x1D,'E'+0x1D,'R'+0x1D

};
unsigned char wizardspelldescdat2[] = {
	0x5D,'D'+0x1D,'A'+0x1D,'G'+0x1D,0x5D,'A'+0x1D,'C'+0x1D,'R'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D, 
	0x5D,'T'+0x1D,'E'+0x1D,'L'+0x1D,'E'+0x1D,'P'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x7B,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'F'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,'D'+0x1D,'I'+0x1D,'V'+0x1D,'I'+0x1D,0x5D,0x5D,
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,'S'+0x1D,'P'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,
	0x5D,0x5D,0x5D,0x5D,0x7C,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,'A'+0x1D,'L'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,
	0x5D,'S'+0x1D,'T'+0x1D,'O'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x7E,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char wizardspellsdat2[] = {
	'D'+0x1D,'A'+0x1D,'G'+0x1D,'A'+0x1D,'C'+0x1D,'R'+0x1D,'O'+0x1D, 
	'F'+0x1D,'A'+0x1D,'L'+0x1D,'D'+0x1D,'I'+0x1D,'V'+0x1D,'I'+0x1D, 
	'A'+0x1D,'L'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D
//g) Dag Acron - random teleport on surface
//j) Fal Divi - cast this then you can cast a cleric spell
//m) Altair - stops time
};

unsigned char bombtrapdat[] = {
	'B'+0x1D,'O'+0x1D,'M'+0x1D,'B'+0x1D,0x5D,'T'+0x1D,'R'+0x1D,'A'+0x1D,'P'+0x1D,0x82,0x5D,0x5D
} ;

unsigned char poisontrapdat[] = {
	'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,'T'+0x1D,'R'+0x1D,'A'+0x1D,'P'+0x1D,0x82
} ;

unsigned char acidtrapdat[] = {
	'A'+0x1D,'C'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,'T'+0x1D,'R'+0x1D,'A'+0x1D,'P'+0x1D,0x82,0x5D,0x5D  
} ;

unsigned char gastrapdat[] = {
	'G'+0x1D,'A'+0x1D,'S'+0x1D,0x5D,'T'+0x1D,'R'+0x1D,'A'+0x1D,'P'+0x1D,0x82,0x5D,0x5D,0x5D
} ;

unsigned char avoidtrapdat[] = {
	'T'+0x1D,'R'+0x1D,'A'+0x1D,'P'+0x1D,0x5D,'E'+0x1D,'V'+0x1D,'A'+0x1D,'D'+0x1D,'E'+0x1D,'D'+0x1D,0x82 
} ;

unsigned char hitdat[] = {
	'H'+0x1D,'I'+0x1D,'T'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D
} ;

unsigned char destroydat[] = {
	'D'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,'R'+0x1D,'O'+0x1D,'Y'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5d,0x5d
};

void formatnumber6(UWORD num,UBYTE length)
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

void charscreen4(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat3);

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber6(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat3+(UWORD)player->status );

	formatnumber6(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber6(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber6(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}
unsigned char dirarr3[] = {
	'N'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'O'+0x1D,'U'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
};

UBYTE getdir2()
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
 
	set_bkg_tiles2(1,15,9,1,dirdat2);
	set_bkg_tiles2(1,16,9,1,dirdat2+9L);
	  */
	writegamemessage(dirdat2) ;

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
		writegamemessage(dirarr3+(((UWORD)(dir-1))*12L)) ;

	}
	waitpadup() ;
	return dir ;


}

UBYTE domapattack()
{
	UBYTE p, dir ;
	UBYTE tilex, tiley ; 
	UBYTE monx, mony ;


	tilex = 6 ;
	tiley = 6 ;
	monx = playerx ;
	mony = playery ;

	dir = getdir2() ;

	if ( dir==1 )
	{
		tiley = 5 ;
		if ( inside )
			mony-- ;
		else
			if ( mony==0 )
			mony = 63 ;
		else
			mony-- ;
	}
	if ( dir==2 )
	{
		tiley = 7 ;
		if ( inside )
			mony++ ;
		else
			if ( mony==63 )
			mony = 0 ;
		else
			mony++ ;
	}
	if ( dir==3 )
	{
		tilex = 7 ;
		if ( inside )
			monx++ ;
		else
			if ( monx==63 )
			monx = 0 ;
		else
			monx++ ;
	}
	if ( dir==4 )
	{
		tilex = 5 ;
		if ( inside )
			monx-- ;
		else
			if ( monx==0 )
			monx = 63 ;
		else
			monx-- ;
	}

	if ( dir )
	{
		if ( ( ingenerator ) && ( monx==generatorx ) && ( mony==generatory) )
		{
			dir = 49 ;
		}
		else
		{

			get_bkg_tiles2(tilex,tiley,1,1,screenbuf3) ;
			if ( tile_attribs[screenbuf3[0]] & 0x08 )
			{
				dir = 0 ;
				while ( (dir<nummonsters) && ((monsters[dir].x != monx) || (monsters[dir].y!=mony)) )
					dir++ ;

				if ( dir==nummonsters )
				{
					dir = 99 ;
					writegamemessage(emptydat) ;
				}

			}
			else
			{
				dir=99 ;
				writegamemessage(emptydat) ;

			}
		}


	}
	else
		dir=99 ;

	for ( monx=0 ; monx<4;monx++ )
		charscreen4(&players[monx],monx) ;

	return dir+1 ;
}

UBYTE doboard()
{
	unsigned char oldtile, atile ;
	atile = *((unsigned char*)0xA000+(((UWORD)playery)*64L)+((UWORD)playerx));
//   get_bkg_tiles2(6,6,1,1,screenbuf3) ;
	if ( transport!=0 )
	{
		writegamemessage(onlyfootdat) ;
		return 0 ;
	}
	if ( atile==0x0D )	//horse
	{
		transport=2 ;
		playerscreentile = 0x0D ;
		//set_sprite_tile(5,0x0D) ;
		screenbuf3[0] = 0x00 ;
		disable_interrupts2() ;
		SWITCH_RAM_MBC5(3) ;
		oldtile = *((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) ;
		SWITCH_RAM_MBC5(1) ;
		enable_interrupts2() ;
		set_bkg_tiles2(6,6,1,1,&oldtile) ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) = oldtile ;

	}
	else
		if ( atile==0x0E )	//frigate
	{
		transport=1 ;
		playerscreentile = 0x0E ;
		//set_sprite_tile(5,0x0E) ;
		screenbuf3[0] = 0x00 ;
		set_bkg_tiles2(6,6,1,1,screenbuf3) ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) = 0x00 ;

		if ( ( peermap == 14 ) && ( extragame != 0  ) && ( playerx == 0 ) && ( playery == 1) )
			return 1 ;

		//  set_sprite_tile( 5, 0x5CU ); human


	}
	else
		writegamemessage(emptydat) ;

	return 0 ;

}

void doxit()
{
	unsigned char oldtile ;

	if ( transport==0 )
	{
		writegamemessage(notboardeddat) ;
		return ;
	}
	playerscreentile = 0x5CU ;
	//set_sprite_tile( 5, 0x5CU ); 
	if ( transport==1 )
		oldtile = 0x0E ;
	else
		oldtile	= 0x0D ;

	transport = 0 ;
	set_bkg_tiles2(6,6,1,1,&oldtile) ;
	*((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) = oldtile ;



}


UBYTE choosechar2()
{
	UBYTE p, keys, currchar ;


	writegamemessage(whodat) ;

	for ( p=0; p<4 ; p++ )
		charscreen4(&(players[p]),p) ;

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

UBYTE dopeergem(UBYTE spell)
{
	UBYTE pnum, p, q, tilenum, palnum ;


	if ( extragame != 0 )
		return 0 ;

	if ( !spell )
	{
		pnum = choosechar2() ;
		if ( pnum==99 )
			return 0 ;
		if ( players[pnum].status>1 )
		{
			writegamemessage(deaddat) ;
			return 1 ;
		}

		if ( players[pnum].gems==0 )
		{
			writegamemessage(nogemsdat) ;
			return 1 ;

		}

		(players[pnum].gems)-- ;
	}

	waitpadup() ;

	//move_sprite( 5, 0,0 );
	wait_vbl_done() ;

	if ( LCDC_REG&0x10 )
	{
		vidbase = (unsigned char*)0x9800 ;
	}
	else
	{
		vidbase = (unsigned char*)0x9C00 ;
	}


	memset(screenbuf3,0x5D,20L) ;
	for ( q=0 ; q < 18 ; q++ )
		set_data2(vidbase+((UWORD)q<<5L),screenbuf3,20L) ;
	memset(screenbuf3,0x00,20L) ;
	disable_interrupts2() ;
	VBK_REG=1 ;
	for ( q=0 ; q < 18 ; q++ )
		set_data2(vidbase+((UWORD)q<<5L),screenbuf3,20L) ;
	VBK_REG=0 ;
	enable_interrupts2() ;


	peer_semaphore=1 ;
	while ( peer_semaphore==1 )
		;  //empty loop 

	disable_interrupts2() ;
	DISPLAY_OFF ;
	/*
	tilenum = 0x5D ;
	palnum = 0 ;
	for (p = 0 ; p < 11 ; p++)
		for (q = 0 ; q < 11 ; q++)
		{
			set_bkg_tiles2(q+1,p+1,1,1,(unsigned char*)&tilenum) ;
			VBK_REG=1 ;
			set_bkg_tiles2(q+1,p+1,1,1,(unsigned char*)&palnum) ;
			VBK_REG=0 ;
		}
		*/
	tilenum = 0x94 ;
	for ( p = 0 ; p < 8 ; p++ )
		for ( q = 0 ; q < 8 ; q++ )
		{
			set_data2(vidbase+(((UWORD)(p+5))<<5L)+(UWORD)q+6L,(unsigned char*)&tilenum,1L) ;
			tilenum++ ;
		}
	if ( LCDC_REG & 0x10 )
		LCDC_REG &= 0xEF ;	//select $9800-$9BFF
	else
		LCDC_REG |= 0x10 ;	//select $9C00-$9FFF

	DISPLAY_ON ;
	enable_interrupts2() ;

	waitpad(0xFF) ;
	waitpadup() ;
	disable_interrupts2() ;
	DISPLAY_OFF ;

	if ( vidbase==(unsigned char*)0x09800 )
	{
		set_data2(vidbase,(unsigned char*)0x9C00,0x400) ;
		VBK_REG=1 ;
		set_data2(vidbase,(unsigned char*)0x9C00,0x400) ;
		VBK_REG=0 ;
		LCDC_REG |= 0x10 ;	//select $9C00-$9FFF
	}
	else
	{
		set_data2(vidbase,(unsigned char*)0x9800,0x400) ;
		VBK_REG=1 ;
		set_data2(vidbase,(unsigned char*)0x9800,0x400) ;
		VBK_REG=0 ;
		LCDC_REG &= 0xEF ;	//select $9800-$9BFF
	}

	peer_semaphore=2 ;
	enable_interrupts2() ;
	while ( peer_semaphore==2 )
		;  //empty loop
	disable_interrupts2() ;

	need_refresh=1 ;
	//move_sprite( 5, 56,64 );
	enable_interrupts2() ;

	DISPLAY_ON ;

	return 1 ;

}

UBYTE getmenuselection3(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
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

	memset(screenbuf3,0x5d,12L) ;
	for ( keys=0 ; keys !=4 ; keys++ )
		writegamemessage(screenbuf3) ;

	memcpy(screenbuf3,menudata+((UWORD)currline*7L),7L) ;
	writegamemessage(screenbuf3) ;

	return currline ;

}
void showspelldesc2(UBYTE spellnum, unsigned char *descdat)
{
	unsigned char screenbuf4[12] ;

	memset(screenbuf4,0x5D,12L) ;
	set_bkg_tiles2( 0, 13, 12, 1, (unsigned char*)screenbuf4);
	set_bkg_tiles2( 0, 17, 12, 1, (unsigned char*)screenbuf4);

	set_bkg_tiles2(0,14,12,1,descdat+((UWORD)spellnum*36L)) ;
	set_bkg_tiles2(0,15,12,1,descdat+((UWORD)spellnum*36L)+12L) ;
	set_bkg_tiles2(0,16,12,1,descdat+((UWORD)spellnum*36L)+24L) ;

}
void magiceffect3(UBYTE spellnum)
{
	UBYTE p ;

	magicsfx1(20+(spellnum*5)) ;
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
void trapeffect(UBYTE pnum)
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

UBYTE testplayerdex2(UBYTE pnum)
{
	UBYTE playerdex ;

	playerdex = players[pnum].dex ;

	if ( (players[pnum].inparty==0)||(players[pnum].status>1) )
		return 0 ;

	if ( players[pnum].skill==9 ) //thief
		playerdex += 0x80U;
	else
		if ( (players[pnum].skill==0) || 
			 (players[pnum].skill==1) || 
			 (players[pnum].skill==5) || 
			 (players[pnum].skill==8) )
		playerdex += 0x40 ;

	if ( make_rnd(0) < playerdex )
		return 1;

	return 0 ;


}

void damageplayer2(UBYTE pnum, UBYTE damage)
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
		writegamemessage(deaddat) ;

	}
	formatnumber6( (UWORD)(players[pnum].currHP),4) ;
	set_data2((unsigned char*)0x9800+14L+(32L*(2+(pnum<<2))),(unsigned char*)screenbuf3,4L) ;
	set_data2((unsigned char*)0x9C00+14L+(32L*(2+(pnum<<2))),(unsigned char*)screenbuf3,4L) ;


}

void cannonfire2()
{
	UBYTE n ;
	UBYTE damage ;

	for ( n=0 ; n!=4 ; n++ )
	{
		if ( (players[n].inparty)&&(players[n].status<2) )
		{
			damage = (make_rnd(0)) & 0x77 ;
			damage = ((damage>>4)*10) + (damage&0x0F) ;
			damageplayer2(n,damage) ;
			trapeffect(n) ;


		}


	}


}

UBYTE dogetchest(UBYTE spell,UBYTE pnum, UBYTE indungeon, unsigned char dungtile)
{
	unsigned char atile ;
	UBYTE avoidtrap, gold ;
	UBYTE damage,extratype ;

	if ( indungeon )
	{
		if ( dungtile!=0x40 )
		{
			writegamemessage(nochestdat) ;
			return 1 ;
		}
	}
	else
	{
		atile = *((unsigned char*)0xA000+(((UWORD)playery)*64L)+((UWORD)playerx));
		if ( atile!=0x0C )
		{
			writegamemessage(nochestdat) ;
			return 1 ;
		}
	}

	if ( !spell )
	{
		pnum = choosechar2() ;
		if ( pnum==99 )
			return 0 ;

		if ( players[pnum].status>1 )
		{
			writegamemessage(deaddat) ;
			return 1;
		}

		if ( (make_rnd(0))&0x80U )
		{
			avoidtrap = testplayerdex2(pnum) ;
			switch ( make_rnd(4) )
			{
				case 0 : 
					{
						writegamemessage(acidtrapdat) ;
						if ( avoidtrap==0 )
						{
							damage = (make_rnd(0)) & 0x37 ;
							damage = ((damage>>4)*10) + (damage&0x0F) ;
							damageplayer2(pnum,damage) ;
							trapeffect(pnum) ;
						}
						break ;


					}

				case 1 : 
					{
						writegamemessage(poisontrapdat) ;
						if ( avoidtrap==0 )
						{
							players[pnum].status=0x01 ;
							trapeffect(pnum) ;
						}
						break ;
					}
				case 2 : 
					{
						writegamemessage(gastrapdat) ;
						if ( avoidtrap==0 )
						{
							for ( gold=0 ; gold!=4 ; gold++ )
							{
								if ( (players[gold].inparty)&&(players[gold].status==0) )
								{
									players[gold].status = 0x01 ;
									charscreen4(&players[gold],gold) ;
									trapeffect(gold) ;
								}

							}
						}
						break ;
					}
				case 3 : 
					{
						writegamemessage(bombtrapdat) ;
						if ( avoidtrap==0 )
							cannonfire2() ;
						break ;
					}

			}
			if ( avoidtrap )
			{
				writegamemessage(avoidtrapdat) ;
				attackmisssfx(120U) ;
			}

		}
	}
	else
	{
		if ( ((make_rnd(0))&0x03)==0 )
			return 0 ;
	}

	gold = make_rnd(0x64) | 0x30 ;
	if ( gold >0x64 )
		gold -= 0x64 ;

	memset(screenbuf3,0x5D,12L) ;
	formatnumber6((UWORD)gold,2) ;
	memcpy(screenbuf3+3L,golddat,4L) ;
	writegamemessage(screenbuf3) ;
	players[pnum].gold += (UWORD)gold ;
	if ( players[pnum].gold > 9999 )
		players[pnum].gold = 9999 ;

	if ( make_rnd(0)<0x40 )
	{
		memset(screenbuf3,0x5D,12L) ;
		memcpy(screenbuf3,anddat,3L) ;

		extratype = make_rnd(0) ;
		if ( (extratype & 0x80U)==0 )
		{
			extratype &= (make_rnd(0))&0x07 ;
			if ( extratype )
				if ( players[pnum].weapons[extratype] < 9 )
				{
					memcpy(screenbuf3+4L,weaponsdat3+(UWORD)((extratype)<<3),8L) ;
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
						memcpy(screenbuf3+4L,armorsdat3+(UWORD)((extratype)<<3),8L) ;
						(players[pnum].armors[extratype])++ ;
						writegamemessage(screenbuf3) ;
					}

			}


		}



	}

	if ( !indungeon )
	{
		disable_interrupts2() ;
		SWITCH_RAM_MBC5(3) ;
		atile = *((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) ;
		if ( atile==0x0C )
		{
			atile = 0x0B ;
			*((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) = atile ;
		}

		SWITCH_RAM_MBC5(1) ;
		enable_interrupts2() ;
		//set_bkg_tiles2(6,6,1,1,&atile) ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(playery))<<6))+(UWORD)(playerx)) = atile ;
	}

	return 1 ;
}

UBYTE docastspell(UBYTE pnum)
{
	UBYTE dir ;
	UBYTE p,themon,q ;
	UBYTE clericmage ; //1=cleric, 2=mage, 0=no spells
	UBYTE spell ;
	UBYTE thechar ;
	UWORD amt ;
	UBYTE cost, kill ;

	if ( pnum>3 )
	{
		pnum = choosechar2() ;
		if ( pnum==99 )
			return 0 ;
	}

	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat) ;
		return 1 ;


	}
	memset(screenbuf3,0x5d,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;
	for ( p=0 ; p<16;p++ )
	{
		set_bkg_tiles2(13,p+1,7,1,screenbuf3); 
		VBK_REG=1 ;       
		set_bkg_tiles2(13,p+1,7,1,screenbuf3+7L); 
		VBK_REG=0 ;       
	}

	if ( cheat_fullmp != 0 )
		players[pnum].magic = 99 ;

	if ( cheat_noclass != 0 )
	{
		clericmage = getmenuselection3(2,clericormagedat2,NULL,NULL) ;
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
			clericmage = getmenuselection3(2,clericormagedat2,NULL,NULL) ;
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
		spell = getmenuselection3(7,clericspellsdat2,showspelldesc2,clericspelldescdat2) ;

		if ( spell==0 )
		{
			if ( players[pnum].magic <5 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 5 ;
			magiceffect3(2) ;
			if ( dogetchest(1,pnum,0,0) ==0 )
				writegamemessage(faildat2) ;

		}
		if ( (spell==1) || (spell==3) )
		{
			if ( spell==1 )
				cost =10 ;
			else
				cost = 50 ;
			if ( players[pnum].magic <cost )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar2() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect3((cost/5)+1) ;
			amt = arand() &0x00FF;

			if ( spell==1 )
				amt = make_rnd(21)+10 ;
			else
				amt	= make_rnd(0x51)+0x14 ;

			players[thechar].currHP += (UBYTE)amt ;
			if ( players[thechar].currHP > players[thechar].maxHP )
				players[thechar].currHP = players[thechar].maxHP ;
			players[pnum].magic -= cost ;
			charscreen4(&players[thechar],thechar) ;


		}
		if ( spell==2 )
		{
			if ( players[pnum].magic <35 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar2() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect3(8) ;
			if ( players[thechar].status==0x01 )
				players[thechar].status=0x00 ;
			players[pnum].magic -= 35 ;
			charscreen4(&players[thechar],thechar) ;


		}
		if ( spell==4 )	//peer gem
		{
			if ( extragame != 0 )
			{
				writegamemessage(faildat2) ;
				attackmisssfx(120U) ;
				return 0 ;
			}

			if ( players[pnum].magic <55 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect3(12) ;
			players[pnum].magic -= 55 ;
			dopeergem(1) ;
		}
		if ( spell==5 )	//raise dead
		{
			if ( players[pnum].magic <65 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar2() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect3(14) ;

			players[pnum].magic -= 65 ;
			if ( (make_rnd(0))&0x03 )
			{
				if ( players[thechar].status==0x02 )
				{
					players[thechar].status=0x00 ;
					players[thechar].currHP = 1L ;
					numalive++ ;
				}
			}
			else
			{
				if ( players[thechar].status==0x02 )
					players[thechar].status=0x03 ;
			}
			charscreen4(&players[thechar],thechar) ;
		}
		if ( spell==6 )	 //raise ashed
		{
			if ( players[pnum].magic <75 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			if ( players[pnum].wis<10 )
			{
				writegamemessage(wistoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar2() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect3(16) ;

			players[pnum].magic -= 75 ;
			if ( players[thechar].status==0x03 )
			{
				players[thechar].status=0x00 ;
				players[thechar].currHP = 1L ;
				numalive++ ;
			}
			players[pnum].wis -= 5 ;
			charscreen4(&players[thechar],thechar) ;
		}
		if ( spell==99 )
			return 0 ;


	}
	else
	{
		spell = getmenuselection3(3,wizardspellsdat2,showspelldesc2,wizardspelldescdat2) ;
		if ( spell==99 )
			return 0 ;
//g) Dag Acron - random teleport on surface
//j) Fal Divi - cast this then you can cast a cleric spell
//m) Altair - stops time
		if ( spell==0 )	//random teleport on surface
		{
			if ( (inside!=0)||(playerscreentile==0x0E) )
			{
				writegamemessage(notheredat) ;
				attackmisssfx(120U) ;
				return 0 ;
			}

			if ( players[pnum].magic <30 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}

			players[pnum].magic -= 30;
			magiceffect3(7) ;

			if ( extragame != 0 )
			{
				if ( ( playerx == 14 ) && ( playery == 54 ) )
				{
					p = 55 ;
					q = 59 ;
				}
				if ( ( playerx == 33 ) && ( playery == 27 ) )
				{
					p = 49 ;
					q = 32 ;
				}

			}
			else
			{
				dir = 0;
				while ( !( (dir==0x04)||(dir==0x05)||(dir==0x06)||(dir==0x0B) ) )
				{
					p = make_rnd(64) ;
					q = make_rnd(64) ;
					if ( p == 49 )
						p-- ;
					dir = *((unsigned char*)0xA000+(((UWORD)q)*64L)+((UWORD)p)) ;
				}
			}

			playerx = p ;
			playery = q ;
			screenx = (p-5)&0x3F ;
			screeny = (q-5)&0x3F ;

		}
		if ( spell==1 )	//castcleric
		{
			if ( players[pnum].magic <45 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 45 ;
			q = players[pnum].skill ;
			players[pnum].skill = 2;
			docastspell(pnum) ;
			players[pnum].skill = q;
		}
		if ( spell==2 )	//stop time
		{
			if ( extragame != 0 )
			{
				writegamemessage(faildat2) ;
				attackmisssfx(120U) ;
				return 0 ;

			}

			if ( players[pnum].magic <60 )
			{
				writegamemessage(mptoolowdat) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect3(13) ;
			players[pnum].magic -= 60 ;
			stoptime = 10 ;
		}
	}
	charscreen4(&players[pnum],pnum) ;

	if ( cheat_fullmp!=0 )
		players[pnum].magic = 99 ;
	return 1 ;   
}

void doshrine(UBYTE theattrib)
{
	UBYTE pnum, n,r ;
	UWORD offering ;
	UBYTE joykeys ;
	UBYTE maxattrib ;
	UBYTE *ptrattrib2 ;


	pnum = choosechar2() ;

	if ( pnum==99 )
		return ;

	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat) ;
		return ;
	}

	changemusic = extragame ? 14 : 3 ;

	if ( extragame != 0 )
		maxattrib = 99U ;
	else
		maxattrib = maxattribsdat[(players[pnum].race*4)+theattrib] ;

	ptrattrib2 = (&(players[pnum].str)) + (UWORD)theattrib ;

	//move_sprite(5,0,0) ;
	set_bkg_tiles2(1,1,11,11,shrinemap) ;
	VBK_REG=1 ;
	for ( n=0 ; n<11 ; n++ )
	{
		for ( r=0 ; r<11 ; r++ )
			screenbuf3[r] = *(tile_palettes+(UWORD)(*(shrinemap+(UWORD)r+(UWORD)(n*11)))) ;
		set_bkg_tiles2(1,n+1,11,1,screenbuf3) ;
	}
	VBK_REG=0 ;

	writegamemessage(shrinetxt1) ;
	writegamemessage(shrineattribs+(UWORD)(theattrib*12)) ;   
	memset(screenbuf3,0x5D,12L) ;
	writegamemessage(screenbuf3) ;
	writegamemessage(shrinetxt2) ;
	writegamemessage(screenbuf3) ;
	offering = 0L ;
	formatnumber6(offering,4) ;
	set_bkg_tiles2(4,17,4,1,screenbuf3) ;
	memset(screenbuf3,0x04,4L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(4,17,4,1,screenbuf3) ;
	VBK_REG=0 ;

	while ( 1 )
	{
		joykeys = joypad() ;
		if ( (joykeys&J_UP)||(joykeys&J_RIGHT) )
		{
			if ( (players[pnum].gold >= offering+100L)&&
				 (*ptrattrib2 + (UBYTE)((offering+100L)/100L) <= maxattrib) )
				offering+=100L;


		}
		if ( (joykeys&J_DOWN)||(joykeys&J_LEFT) )
		{
			if ( offering>0L )
				offering-=100L;


		}
		if ( (joykeys&J_DOWN)||(joykeys&J_LEFT) ||
			 (joykeys&J_UP)||(joykeys&J_RIGHT) )
		{
			formatnumber6(offering,4) ;
			set_bkg_tiles2(4,17,4,1,screenbuf3) ;
			waitpadup() ;

		}
		if ( joykeys&J_A )
			break ;


		if ( joykeys&J_B )
		{
			offering = 1L ;
			break ;



		}



	} 

	memset(screenbuf3,0x00,4L) ;
	VBK_REG=1 ;
	set_bkg_tiles2(4,17,4,1,screenbuf3) ;
	VBK_REG=0 ;
	if ( offering<100L )
	{
		writegamemessage(beoffdat) ;

	}
	else
	{
		writegamemessage(shazamdat) ;
		players[pnum].gold -= offering ;
		n = (UBYTE)(offering/100L);
		*ptrattrib2 = *ptrattrib2 + n ;
	}
	waitpadup() ;   
	//move_sprite( 5, 56,64 );
	changemusic = extragame ? 32 : 11 ;
}

unsigned char enterlocsdat[] = {
	30,2, //castle1
	46,7,
	6,13,
	19,57,
	7,44,
	56,6,
	18,31,
	49,34,
	45,18, //castle britannia
	34,16, //town rudan
	46,19, //town britain
	56,31, //town confusion
	37,53, //town dusk
	47,58, //town proul
	49,58  //town pirate stronghold
} ;

UBYTE ingeneratordat[] = {
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0   
} ;

UBYTE generatorxydat[] = {
	32,11,
	18,8,
	32,16,
	10,10,
	45,6,
	60,19,
	32,4,
	51,13,
	0,0,
	0,0,
	0,0,
	0,0,
	0,0,
	0,0,
	0,0,
	0,0,

} ;

UBYTE generatortiledat[] = {
	26,
	22,
	19,
	22,
	36,
	22,
	35,
	22,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,  

} ;

UBYTE doenter()
{
	unsigned char atile ;
	UBYTE n, returntown ;

	atile = *((unsigned char*)0xA000+(((UWORD)playery)*64L)+((UWORD)playerx));

	if ( inside )
	{
		if ( atile == 0x5BU )
		{
			if ( (playerx==4)&&(playery==36) )
				doshrine(0) ;
			if ( (playerx==45)&&(playery==52) )
				doshrine(1) ;
			if ( (playerx==6)&&(playery==6) )
				doshrine(2) ;
			if ( (playerx==55)&&(playery==27) )
				doshrine(3) ;

			return 99 ;
			//4,36 = shrine of strength
			//45,52 = shrine of dexterity
			//6,6 = shrine of intelligence
			//55,27 = shrine of wisdom
			//enter shrine
		}

	}
	else
	{
		if ( extragame )
		{
			if ( (playerx==37) && (playery==18) )
				return 50 ;

			returntown = 99U ;

			for ( n = 0 ; n != 15 ; n++ )
			{
				if ( ( playerx == *(enterlocsdat + ((UWORD)(n*2)) ) ) &&
					 ( playery == *(enterlocsdat + ((UWORD)(n*2)) + 1L ) ) )
					returntown = n ;

			}

			if ( returntown != 99U )
			{
				ingenerator = ingeneratordat[returntown] ;
				generatorx = generatorxydat[returntown<<1] ;
				generatory = generatorxydat[(returntown<<1)+1] ;
				generatortile = generatortiledat[returntown] ;
				return returntown ;
			}
		}
		else
		{
			if ( atile==0x08 )
			{//dungeon
				if ( (playerx==46)&&(playery==7) )
					return 0xF0U ;
				if ( (playerx==49)&&(playery==34) )
					return 0xF1U ;
				if ( (playerx==19)&&(playery==57) )
					return 0xF2U ;
				if ( (playerx==9)&&(playery==28) )
					return 0xF3U ;
				if ( (playerx==56)&&(playery==6) )
					return 0xF4U ;
				if ( (playerx==58)&&(playery==30) )
					return 0xF5U ;
				if ( (playerx==58)&&(playery==44) )
					return 0xF6U ;

				//		  46,7 - dardin's pit
				//49,34 - fires of hell
				//19,57 - m
				//9,28 - mines of morinia
				//56,6 - perinian depths
				//58,30 - time
				//58,44 - p

				//		  return 0xF0U ;

			}
			else
				if ( (atile==0x09)||(atile==0x0A) )
			{
				if ( (playerx==45) && (playery==18) )
					return 0 ;
				if ( (playerx==37) && (playery==53) )
					return 1 ;
				if ( (playerx==56) && (playery==31) )
					return 2 ;
				if ( (playerx==18) && (playery==31) )
					return 3 ;
				if ( (playerx==10) && (playery==53) )
				{
					inexodus = 1 ;
					return 4 ;
				}
				if ( (playerx==30) && (playery==2) )
					return 5 ;
				if ( (playerx==7) && (playery==44) )
					return 6 ;
				if ( (playerx==46) && (playery==19) )
					return 7 ;
				if ( (playerx==47) && (playery==58) )
					return 8 ;
				if ( (playerx==49) && (playery==58) )
					return 9 ;
				if ( (playerx==6) && (playery==13) )
					return 10 ;
				if ( (playerx==34) && (playery==16) )
					return 11 ;
			}
			else
				if ( (playerx==37) && (playery==18) )
				return 50 ;

		}               

	}
	writegamemessage(emptydat) ;

	return 99 ;

//45,18 = castle britannia
//37,53 = dawn
//56,31 = death
//18,31 = devils gulch	
//10,53 = castle exodus
//30,02 = fawn
//07,44 = grey
//46,19 = britain
//49,58 = montor east
//47,58 = montor west
//06,13 = moon
//34,16 = yew


//u4
//castle1=30,2
//dungeon1=46,7
//castle2=6,13
//dungeon2=19,57
//castle3=7,44
//dungeon3=56,6
//castle4=18,31
//dungeon4=49,34
//castbrit = 45,18
//towne1=34,16
//towne2=46,19
//towne3=56,31
//towne4=37,53
//towne5=47,58
//towne6=49,58

}

UBYTE dofirecannon()
{
	UBYTE dir, p, found, r ;
	UBYTE cannonx, cannony ;
	UBYTE bkgx, bkgy ;
	unsigned char atile ;
	UBYTE hitbrit ;

	if ( transport!=1 )
	{
		writegamemessage(noshipdat) ;
		return 1 ;
	}

	dir = getdir2() ;

	if ( !dir )
		return 0 ;

	hitbrit = 0 ;   
	cannonx = playerx ;
	cannony = playery ;
	bkgx = 5 ;
	bkgy = 5 ;
	firecannonsfx(170U) ;
	p = 0 ;
	found = 0 ;

	while ( (p<3) && (!found) )
	{
		if ( dir==1 )
		{
			if ( cannony==0 )
				cannony=63 ;
			else
				cannony-- ;
			bkgy-- ;
		}
		if ( dir==2 )
		{
			if ( cannony==63 )
				cannony=0 ;
			else
				cannony++ ;
			bkgy++ ;
		}
		if ( dir==3 )
		{
			if ( cannonx==63 )
				cannonx=0 ;
			else
				cannonx++ ;
			bkgx++ ;
		}
		if ( dir==4 )
		{
			if ( cannonx==0 )
				cannonx=63 ;
			else
				cannonx-- ;
			bkgx-- ;
		}

		move_sprite(0,bkgx*8+16,bkgy*8+24 );
		p++ ;
		if ( (*(tile_attribs+ (UWORD)((*((unsigned char*)0xA000+(((UWORD)cannony)*64L)+((UWORD)cannonx)))))&0x08) )
		{
			found++ ;
			playerhitsfx(200U) ;
			//cannonhitsfx
			//delay(250) ;
			dir = 0 ;
			while ( (dir<nummonsters) && ((monsters[dir].x != cannonx) || (monsters[dir].y!=cannony)) )
				dir++ ;

			if ( dir<nummonsters )
			{
				if ( ((monsters[dir].tile==0x15) && ((make_rnd(0))&0x80U) &&
					  ((make_rnd(0))&0x80U) ) || ((monsters[dir].tile!=0x15)&&((make_rnd(0))&0x80U)) )
				{

					if ( ( extragame != 0 ) && ( monsters[dir].tile == 25 ) )
					{
						hitbrit++ ;
					}

					for ( r=dir ; r<nummonsters-1 ; r++ )
						memcpy((unsigned char*)&(monsters[r]),(unsigned char*)&(monsters[r+1]),MONSTERSIZE) ;
					nummonsters-- ;

					disable_interrupts2() ;
					SWITCH_RAM_MBC5(3) ;
					atile = *((unsigned char*)0xA000+((UWORD)(((UWORD)(cannony))<<6))+(UWORD)(cannonx)) ;
					SWITCH_RAM_MBC5(1) ;
					enable_interrupts2() ;
					set_bkg_tiles2(bkgx+1,bkgy+1,1,1,&atile) ;
					VBK_REG=1 ;
					set_bkg_tiles2(bkgx+1,bkgy+1,1,1,tile_palettes+(UWORD)atile) ;
					VBK_REG=0 ;
					*((unsigned char*)0xA000+((UWORD)(((UWORD)(cannony))<<6))+(UWORD)(cannonx)) = atile ;

					writegamemessage(destroydat) ;   
				}
				else
					writegamemessage(hitdat) ;
			}

		}
		else
			if ( (*((unsigned char*)0xA000+((UWORD)(((UWORD)(cannony))<<6))+(UWORD)(cannonx)))==0x07 )
		{
			move_sprite(0,0,0 );
			found++ ;
		}


		if ( found==0 )
			delay(250) ;

	}
	move_sprite(0,0,0) ;

	if ( hitbrit != 0 )
	{
		specialsfx() ;
		for ( r = 0 ; r < nummonsters ; r++ )
		{
			if ( monsters[r].tile == 24 )
			{
				monsters[r].tile = 23 ;
				monsters[r].attribs = 0x02 ;
			}
		}

		atile = 11 ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(44))<<6))+(UWORD)(15)) = atile ;
		SWITCH_RAM_MBC5(3) ;
		*((unsigned char*)0xA000+((UWORD)(((UWORD)(44))<<6))+(UWORD)(15)) = atile ;
		SWITCH_RAM_MBC5(1) ;
	}

	return 1 ;
}
