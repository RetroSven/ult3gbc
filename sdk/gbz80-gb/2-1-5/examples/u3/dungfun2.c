#include <gb.h>
#include "u3.h"


#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))
#define smallmapdat ((unsigned char*)(0xA800))
#define SCROLLDELAY 20

extern UBYTE currdungtile ;

extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern UBYTE screenx ;
extern UBYTE screeny;
extern UBYTE playerx ;
extern UBYTE playery ;

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

extern UBYTE dunglevel ;
extern UBYTE dungx ;
extern UBYTE dungy ;
extern UBYTE dungdir ;
extern UBYTE dungnumber ;
extern UBYTE dungrefresh ;
extern UBYTE torchtime ;

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


unsigned char wistoolowdat3[] = {
	'W'+0x1D,'I'+0x1D,'S'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,'O'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'W'+0x1D,0x82
};

unsigned char mptoolowdat3[] = {
	'M'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,'O'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'W'+0x1D,0x82,0x5d 
};

unsigned char notorchesdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,'R'+0x1D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,0x82,0x5D
};

unsigned char nogemsdat2[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'G'+0x1D,'E'+0x1D,'M'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D
};

unsigned char whodat5[] = {
	'W'+0x1D,'H'+0x1D,'O'+0x1D,0x83,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d,0x5d
};

unsigned char deaddat4[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82 
} ;

unsigned char charstat6[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};
unsigned char chardat7[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};

unsigned char clericormagedat3[] = {
	'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D,
	'W'+0x1D,'I'+0x1D,'Z'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D,0x5D
};






unsigned char clericspelldescdat3[] = {
	0x5D,'A'+0x1D,'P'+0x1D,'P'+0x1D,'A'+0x1D,'R'+0x1D,0x5D,'U'+0x1D,'N'+0x1D,'E'+0x1D,'M'+0x1D,0x5D, 
	0x5D,'O'+0x1D,'P'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D,   
	0x5D,0x5D,0x5D,0x5D,'H'+0x1D,'E'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,0x5D,0x5D,0x79,0x78,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'L'+0x1D,'U'+0x1D,'M'+0x1D,'I'+0x1D,'N'+0x1D,'A'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	'B'+0x1D,'R'+0x1D,'I'+0x1D,'E'+0x1D,'F'+0x1D,0x5D,'L'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'1'+0x48,'5'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'R'+0x1D,'E'+0x1D,'C'+0x1D,0x5D,'S'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,'U'+0x1D,'P'+0x1D,0x5D,'1'+0x48,0x5D,'L'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'L'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'2'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'R'+0x1D,'E'+0x1D,'C'+0x1D,0x5D,'D'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'O'+0x1D,'W'+0x1D,'N'+0x1D,0x5D,'1'+0x48,0x5D,'L'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'L'+0x1D, 
	0x5D,0x5D,0x5D,0x5D,'2'+0x48,'5'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'L'+0x1D,'I'+0x1D,'B'+0x1D,0x5D,'R'+0x1D,'E'+0x1D,'C'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'T'+0x1D,'E'+0x1D,'L'+0x1D,'E'+0x1D,'P'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'3'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'A'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D,
	'C'+0x1D,'U'+0x1D,'R'+0x1D,'E'+0x1D,0x5D,'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,
	0x5D,0x5D,0x5D,0x7B,0x7D,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,
	0x5D,0x5D,'S'+0x1D,'E'+0x1D,'Q'+0x1D,'U'+0x1D,'I'+0x1D,'T'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D, 
	'E'+0x1D,'X'+0x1D,'I'+0x1D,'T'+0x1D,0x5D,'D'+0x1D,'U'+0x1D,'N'+0x1D,'G'+0x1D,'E'+0x1D,'O'+0x1D,'N'+0x1D, 
	0x5D,0x5D,0x5D,0x5D,'4'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'S'+0x1D,'O'+0x1D,'M'+0x1D,'I'+0x1D,'N'+0x1D,'A'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,'L'+0x1D,'O'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,'L'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'4'+0x48,'5'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
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

unsigned char clericspellsdat3[] = {
	'A'+0x1D,'P'+0x1D,'P'+0x1D,'A'+0x1D,'R'+0x1D,'U'+0x1D,'N'+0x1D, 
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,0x5D, 
	'L'+0x1D,'U'+0x1D,'M'+0x1D,'I'+0x1D,'N'+0x1D,'A'+0x1D,'E'+0x1D,
	'R'+0x1D,'E'+0x1D,'C'+0x1D,0x5D,'S'+0x1D,'U'+0x1D,0x5D,
	'R'+0x1D,'E'+0x1D,'C'+0x1D,0x5D,'D'+0x1D,'U'+0x1D,0x5D,
	'L'+0x1D,'I'+0x1D,'B'+0x1D,0x5D,'R'+0x1D,'E'+0x1D,'C'+0x1D,
	'A'+0x1D,'L'+0x1D,'C'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D, 
	'S'+0x1D,'E'+0x1D,'Q'+0x1D,'U'+0x1D,'I'+0x1D,'T'+0x1D,'U'+0x1D,
	'S'+0x1D,'O'+0x1D,'M'+0x1D,'I'+0x1D,'N'+0x1D,'A'+0x1D,'E'+0x1D,
	'S'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'T'+0x1D,'U'+0x1D,'M'+0x1D, 
	'V'+0x1D,'I'+0x1D,'E'+0x1D,'D'+0x1D,'A'+0x1D,0x5D,0x5D, 
	'S'+0x1D,'U'+0x1D,'R'+0x1D,'M'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D, 
	'A'+0x1D,'N'+0x1D,'J'+0x1D,'U'+0x1D,'S'+0x1D,'E'+0x1D,'R'+0x1D
};

unsigned char wizardspelldescdat3[] = {
	0x5D,0x5D,0x5D,'L'+0x1D,'O'+0x1D,'R'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'B'+0x1D,'R'+0x1D,'I'+0x1D,'E'+0x1D,'F'+0x1D,0x5D,'L'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'1'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,'D'+0x1D,'O'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,'C'+0x1D,'R'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D, 
	'D'+0x1D,'O'+0x1D,'W'+0x1D,'N'+0x1D,0x5D,'1'+0x48,0x5D,'L'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'L'+0x1D, 
	0x5D,0x5D,0x5D,0x5D,'1'+0x48,'5'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,'S'+0x1D,'U'+0x1D,'R'+0x1D,0x5D,'A'+0x1D,'C'+0x1D,'R'+0x1D,'O'+0x1D,'N'+0x1D,0x5D,0x5D, 
	0x5D,'U'+0x1D,'P'+0x1D,0x5D,'1'+0x48,0x5D,'L'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'L'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'2'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,'D'+0x1D,'A'+0x1D,'G'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'R'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D, 
	0x5D,'L'+0x1D,'O'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,'L'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'4'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,'F'+0x1D,'A'+0x1D,'L'+0x1D,0x5D,'D'+0x1D,'I'+0x1D,'V'+0x1D,'I'+0x1D,0x5D,0x5D, 
	'C'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'C'+0x1D,'L'+0x1D,'E'+0x1D,'R'+0x1D,'I'+0x1D,'C'+0x1D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'4'+0x48,'5'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,'A'+0x1D,'L'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D, 
	0x5D,'S'+0x1D,'T'+0x1D,'O'+0x1D,'P'+0x1D,0x5D,'T'+0x1D,'I'+0x1D,'M'+0x1D,'E'+0x1D,0x5D,0x5D, 
	0x5D,0x5D,0x5D,0x5D,'6'+0x48,'0'+0x48,'M'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char wizardspellsdat3[] = {
	'L'+0x1D,'O'+0x1D,'R'+0x1D,'U'+0x1D,'M'+0x1D,0x5D,0x5D,
	'D'+0x1D,'O'+0x1D,'R'+0x1D,'A'+0x1D,'C'+0x1D,'R'+0x1D,'N'+0x1D,
	'S'+0x1D,'U'+0x1D,'R'+0x1D,'A'+0x1D,'C'+0x1D,'R'+0x1D,'N'+0x1D,
	'D'+0x1D,'A'+0x1D,'G'+0x1D,'L'+0x1D,'O'+0x1D,'R'+0x1D,'M'+0x1D,
	'F'+0x1D,'A'+0x1D,'L'+0x1D,'D'+0x1D,'I'+0x1D,'V'+0x1D,'I'+0x1D,
	'A'+0x1D,'L'+0x1D,'T'+0x1D,'A'+0x1D,'I'+0x1D,'R'+0x1D,0x5D,
};

void formatnumber10(UWORD num,UBYTE length)
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




void charscreen7(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat7);

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber10(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat6+(UWORD)player->status );

	formatnumber10(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber10(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber10(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}

UBYTE choosechar5()
{
	UBYTE p, keys, currchar ;


	writegamemessage(whodat5) ;

	for ( p=0; p<4 ; p++ )
		charscreen7(&(players[p]),p) ;

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

UBYTE dopeergem2(UBYTE spell)
{
	UBYTE pnum, p, q, tilenum, palnum ;



	if ( !spell )
	{
		pnum = choosechar5() ;
		if ( pnum==99 )
			return 0 ;
		if ( players[pnum].status>1 )
		{
			writegamemessage(deaddat4) ;
			return 1 ;
		}

		if ( players[pnum].gems==0 )
		{
			writegamemessage(nogemsdat2) ;
			return 1 ;

		}

		(players[pnum].gems)-- ;
	}

	waitpadup() ;

	if ( LCDC_REG&0x08 )
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
	VBK_REG=1 ;
	for ( q=0 ; q < 18 ; q++ )
		set_data2(vidbase+((UWORD)q<<5L),screenbuf3,20L) ;
	VBK_REG=0 ;

	for ( p = 0 ; p < 16 ; p++ )
		for ( q = 0 ; q < 16 ; q++ )
		{
			palnum = *((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(((UWORD)p)<<4L)+(UWORD)q)) ;
			switch ( palnum )
			{
				//case 0x00 : tilenum = 0x5DU ; break ;
				case 0x01 : tilenum = 0x83U ; break ;
				case 0x02 : tilenum = 0x83U ; break ;
				case 0x03 : tilenum = 0x83U ; break ;
				case 0x04 : tilenum = 0x83U ; break ;
				case 0x05 : tilenum = 0x83U ; break ;
				case 0x06 : tilenum = 0x83U ; break ;
				case 0x08 : tilenum = 0x83U ; break ;
				case 0x10 : tilenum = 0xAAU ; break ;
				case 0x20 : tilenum = 0xABU ; break ;
				case 0x30 : tilenum = 0xACU ; break ;
				case 0x40 : tilenum = 0x83U ; break ;
				case 0x80U : tilenum = 0x3AU ; break ;
				case 0xA0U : tilenum = 0xAEU ; break ;
				case 0xC0U : tilenum = 0xAFU ; break ;
				default : tilenum = 0x5DU ; break ;
			}
			if ( (p==dungy)&&(q==dungx) )
				tilenum = 0x5CU ;
			set_data2(vidbase+(((UWORD)(p+1))<<5L)+(UWORD)q+2L,(unsigned char*)&tilenum,1L) ;
		}
	for ( p=9; p<38 ; p++ )
		move_sprite(p,0,0) ;
	if ( LCDC_REG & 0x08 )
		LCDC_REG &= 0xF7 ;	//select $9800-$9BFF
	else
		LCDC_REG |= 0x08 ;	//select $9C00-$9FFF


	waitpad(0xFF) ;
	waitpadup() ;

	if ( LCDC_REG & 0x08 )
		LCDC_REG &= 0xF7 ;	//select $9800-$9BFF
	else
		LCDC_REG |= 0x08 ;	//select $9C00-$9FFF

	return 1 ;

}

UBYTE getmenuselection6(UBYTE numlines,unsigned char *menudata, void (*descptr)(UBYTE,unsigned char*),
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
	memcpy(screenbuf3,menudata+((UWORD)currline*7L),7L) ;
	writegamemessage(screenbuf3) ;

	return currline ;

}
void showspelldesc3(UBYTE spellnum, unsigned char *descdat)
{
	unsigned char screenbuf4[12] ;

	memset(screenbuf4,0x5D,12L) ;
	set_bkg_tiles2( 0, 13, 12, 1, (unsigned char*)screenbuf4);
	set_bkg_tiles2( 0, 17, 12, 1, (unsigned char*)screenbuf4);

	set_bkg_tiles2(0,14,12,1,descdat+((UWORD)spellnum*36L)) ;
	set_bkg_tiles2(0,15,12,1,descdat+((UWORD)spellnum*36L)+12L) ;
	set_bkg_tiles2(0,16,12,1,descdat+((UWORD)spellnum*36L)+24L) ;

}
void magiceffect4(UBYTE spellnum)
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
void relocate_random()
{
	UBYTE nx, ny ;
	unsigned char dtile ;

	dtile = 1 ;

	while ( dtile!=0 )
	{
		nx = make_rnd(16) ;
		ny = make_rnd(16) ;
		dtile = *((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(((UWORD)ny)<<4L)+(UWORD)nx)) ;


	}

	currdungtile = 0 ; 
	dungx = nx ;
	dungy = ny ;


}

unsigned char nochestdat2[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'C'+0x1D,'H'+0x1D,'E'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x5D
} ;
unsigned char anddat3[] = {
	'A'+0x1D,'N'+0x1D,'D'+0x1D,
} ;
unsigned char weaponsdat6[] = {
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

unsigned char armorsdat6[] = {
	'S'+0x1D,'K'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,0X5D,
	'C'+0x1D,'L'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,0X5D,0X5D,0X5D,
	'L'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,'H'+0x1D,'E'+0x1D,'R'+0x1D,0X5D,
	'C'+0x1D,'H'+0x1D,'A'+0x1D,'I'+0x1D,'N'+0x1D,0X5D,0X5D,0X5D,
};

unsigned char golddat3[] = {
	'G'+0x1D,'O'+0x1D,'L'+0x1D,'D'+0x1D
} ;

UBYTE dogetchest3(UBYTE spell,UBYTE pnum, unsigned char dungtile)
{
	unsigned char atile ;
	UBYTE avoidtrap, gold ;
	UBYTE damage,extratype ;

	if ( dungtile!=0x40 )
	{
		writegamemessage(nochestdat2) ;
		return 0 ;
	}

	if ( ((make_rnd(0))&0x03)==0 )
		return 0 ;

	gold = make_rnd(0x64) | 0x30 ;
	if ( gold >0x64 )
		gold -= 0x64 ;

	memset(screenbuf3,0x5D,12L) ;
	formatnumber10((UWORD)gold,2) ;
	memcpy(screenbuf3+3L,golddat3,4L) ;
	writegamemessage(screenbuf3) ;
	players[pnum].gold += (UWORD)gold ;
	if ( players[pnum].gold > 9999 )
		players[pnum].gold = 9999 ;

	if ( make_rnd(0)<0x40 )
	{
		memset(screenbuf3,0x5D,12L) ;
		memcpy(screenbuf3,anddat3,3L) ;

		extratype = make_rnd(0) ;
		if ( (extratype & 0x80U)==0 )
		{
			extratype &= (make_rnd(0))&0x07 ;
			if ( extratype )
				if ( players[pnum].weapons[extratype] < 9 )
				{
					memcpy(screenbuf3+4L,weaponsdat6+(UWORD)((extratype)<<3),8L) ;
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
						memcpy(screenbuf3+4L,armorsdat6+(UWORD)((extratype)<<3),8L) ;
						(players[pnum].armors[extratype])++ ;
						writegamemessage(screenbuf3) ;
					}

			}


		}



	}

	*((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) = 0x00 ;
	return 1 ;
}

UBYTE docastspell2(UBYTE pnum)
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
		pnum = choosechar5() ;
		if ( pnum==99 )
			return 0 ;
	}

	if ( players[pnum].status>1 )
	{
		writegamemessage(deaddat4) ;
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
		clericmage = getmenuselection6(2,clericormagedat3,NULL,NULL) ;
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
			clericmage = getmenuselection6(2,clericormagedat3,NULL,NULL) ;
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



//Appar Unem - open chest without triggering trap  5
//Sanctu  - light healing  10
//Luminae - short duration light  15
//Rec Su - up one dungeon level 20
//Rec Du - down one dungeon level  25
//Lib Rec - random teleport in dungeon  30
//Alcort - neutralize poison  35
//Sequitu - return to surface from dungeon  40
//Sominae - long duration light  45
//Sanctu Mani - powerful healing  50
//Vieda - shows surroundings - like peering into a gem  55
//Surmandum - raise dead - if it fails he/she will become ashes  65
//Anju Sermani - return ashed person to life - costs 5 wisdom points  75

	if ( clericmage==1 )
	{
		spell = getmenuselection6(13,clericspellsdat3,showspelldesc3,clericspelldescdat3) ;

		if ( spell==0 )
		{
			if ( players[pnum].magic <5 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 5 ;
			magiceffect4(1) ;
			dogetchest3(1,pnum,*((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx))) ;

		}
		if ( (spell==1) || (spell==9) )
		{
			if ( spell==1 )
				cost =10 ;
			else
				cost = 50 ;
			if ( players[pnum].magic <cost )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar5() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect4((cost/5)+1) ;
			amt = arand() &0x00FF;

			if ( spell==1 )
				amt = make_rnd(21)+10 ;
			else
				amt	= make_rnd(0x51)+0x14 ;

			players[thechar].currHP += (UBYTE)amt ;
			if ( players[thechar].currHP > players[thechar].maxHP )
				players[thechar].currHP = players[thechar].maxHP ;
			players[pnum].magic -= cost ;
			charscreen7(&players[thechar],thechar) ;


		}
		if ( spell==2 )
		{
			if ( players[pnum].magic <15 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			if ( torchtime<10 )
				torchtime=10 ;

			magiceffect4(4) ;
			players[pnum].magic -= 15 ;

		}
		if ( spell==3 )
		{
			if ( players[pnum].magic <20 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(5) ;
			players[pnum].magic -= 20 ;
			if ( dunglevel==0 )
			{
				dunglevel=99 ;
				dungrefresh=0 ;
			}
			else
			{
				dunglevel-- ;
				relocate_random() ;
				writedunglevel() ;

			}

		}
		if ( spell==4 )
		{
			if ( players[pnum].magic <25 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(6) ;
			players[pnum].magic -= 25 ;
			if ( dunglevel!=7 )
			{
				dunglevel++ ;
				relocate_random() ;
				writedunglevel() ;

			}

		}
		if ( spell==5 )
		{
			if ( players[pnum].magic <30 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(7) ;
			players[pnum].magic -= 30 ;
			relocate_random() ;

		}
		if ( spell==6 )
		{
			if ( players[pnum].magic <35 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar5() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect4(8) ;
			if ( players[thechar].status==0x01 )
				players[thechar].status=0x00 ;
			players[pnum].magic -= 35 ;
			charscreen7(&players[thechar],thechar) ;


		}
		if ( spell==7 )
		{
			if ( players[pnum].magic <40 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(9) ;
			players[pnum].magic -= 40 ;
			dunglevel=99 ;
			dungrefresh = 0 ;

		}
		if ( spell==8 )
		{
			if ( players[pnum].magic <45 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			torchtime=235U ;

			magiceffect4(10) ;
			players[pnum].magic -= 45 ;

		}
		if ( spell==10 ) //peer gem
		{
			if ( players[pnum].magic <55 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(12) ;
			players[pnum].magic -= 55 ;
			dopeergem2(1) ;
		}
		if ( spell==11 ) //raise dead
		{
			if ( players[pnum].magic <65 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar5() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect4(14) ;

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
			charscreen7(&players[thechar],thechar) ;
		}
		if ( spell==12 )  //raise ashed
		{
			if ( players[pnum].magic <75 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			if ( players[pnum].wis<10 )
			{
				writegamemessage(wistoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			thechar = choosechar5() ;
			if ( thechar==99 )
				return 0 ;
			magiceffect4(16) ;

			players[pnum].magic -= 75 ;
			if ( players[thechar].status==0x03 )
			{
				players[thechar].status=0x00 ;
				players[thechar].currHP = 1L ;
				numalive++ ;
			}
			players[pnum].wis -= 5 ;
			charscreen7(&players[thechar],thechar) ;
		}
		if ( spell==99 )
			return 0 ;


	}
	else
	{

//Lorum - short duration light  10
//Dor Acron - down one dungeon level  15
//Sur Acron - up on dungeon level  20
//Dag Lorum - long duration light  40
//Fal Divi - cast this then you can cast a cleric spell  45
//Altair - stops time  60

		spell = getmenuselection6(6,wizardspellsdat3,showspelldesc3,wizardspelldescdat3) ;
		if ( spell==99 )
			return 0 ;
		if ( spell==0 )
		{
			if ( players[pnum].magic <10 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			if ( torchtime<10 )
				torchtime = 10 ;

			magiceffect4(3) ;
			players[pnum].magic -= 10 ;

		}
		if ( spell==1 )
		{
			if ( players[pnum].magic <15 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(4) ;
			players[pnum].magic -= 15 ;
			if ( dunglevel!=7 )
			{
				dunglevel++ ;
				relocate_random() ;
				writedunglevel() ;

			}

		}
		if ( spell==2 )
		{
			if ( players[pnum].magic <20 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(5) ;
			players[pnum].magic -= 20 ;
			if ( dunglevel==0 )
				dunglevel=99 ;
			else
			{
				dunglevel-- ;
				relocate_random() ;
				writedunglevel() ;

			}

		}
		if ( spell==3 )
		{
			if ( players[pnum].magic <40 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			torchtime = 235;

			magiceffect4(9) ;
			players[pnum].magic -= 40 ;

		}
		if ( spell==4 )	//castcleric
		{
			if ( players[pnum].magic <45 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			players[pnum].magic -= 45 ;
			q = players[pnum].skill ;
			players[pnum].skill = 2;
			docastspell2(pnum) ;
			players[pnum].skill = q;
		}
		if ( spell==5 )	//stop time
		{
			if ( players[pnum].magic <60 )
			{
				writegamemessage(mptoolowdat3) ;
				attackmisssfx(120U) ;
				return 0 ;

			}
			magiceffect4(13) ;
			players[pnum].magic -= 60 ;
			stoptime = 10 ;
		}
	}
	charscreen7(&players[pnum],pnum) ;

	if ( cheat_fullmp!=0 )
		players[pnum].magic = 99 ;
	return 1 ;   
}

UBYTE doignite(UBYTE pnum, UBYTE lightnum)
{

	if ( pnum>3 )
	{
		pnum = choosechar5() ;
		if ( pnum==99 )
			return 0 ;
		if ( players[pnum].status>1 )
		{
			writegamemessage(deaddat4) ;
			return 1 ;
		}
		if ( players[pnum].torches==0 )
		{
			writegamemessage(notorchesdat) ;
			return 0 ;
		}
		(players[pnum].torches)-- ;
	}
	torchtime = lightnum ;

	return 1 ;

}
UBYTE checkdungeonencounter()
{
	UBYTE monnum ;
	UBYTE dtile ;

	monnum = 0 ;

	dtile = *((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) ;

	if ( (make_rnd(0x83U+dunglevel)&0x80U)&&(dtile==0x00) )
	{
		monnum = make_rnd(dunglevel+0x02) ;
		if ( monnum >= 7 )
			monnum = 6 ;
		monnum += 0x1E ;
	}
	return monnum ;


}
