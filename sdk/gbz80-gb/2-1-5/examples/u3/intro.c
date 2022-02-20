//pressing start after title screen - turn off display before showing dointro

#include <gb.h>

//#include "u3title.c"
#include "u3.h"

#define titletiles ((unsigned char*)(0xA000))
#define introtiles ((unsigned char*)(0xAAC0))
#define exodusmap ((unsigned char*)(0xB240))
#define exodusmap2 ((unsigned char*)(0xB2EB))
#define ult3map ((unsigned char*)(0xB396))
#define intromap ((unsigned char*)(0xB42E))
#define intropalmap ((unsigned char*)(0xB4A0))
#define intromoves ((unsigned char*)(0xB512))
#define fromhell ((unsigned char*)(0xB7D2))
#define fromhellmap ((unsigned char*)(0xB972))
#define smallnums ((unsigned char*)(0xB98C))
#define spritenums ((unsigned char*)(0xBA4C))
#define text1 ((unsigned char*)(0xBA63))
#define text2 ((unsigned char*)(0xBA6F))
#define text3 ((unsigned char*)(0xBA7C))
#define text4 ((unsigned char*)(0xBA8B))
#define text5 ((unsigned char*)(0xBA9A))
#define text6 ((unsigned char*)(0xBAA9))
#define text7 ((unsigned char*)(0xBAB9))
#define text8 ((unsigned char*)(0xBAC9))
#define text9 ((unsigned char*)(0xBAD3))
#define text10 ((unsigned char*)(0xBAE1))
#define text11 ((unsigned char*)(0xBAF4))
#define stats1 ((unsigned char*)(0xBAFD))
#define stats2 ((unsigned char*)(0xBB51))
#define stats3 ((unsigned char*)(0xBB81))
#define stats4 ((unsigned char*)(0xBB97))
#define weaponsdat ((unsigned char*)(0xBBA3))
#define armorsdat ((unsigned char*)(0xBC23))
#define sexes ((unsigned char*)(0xBC73))
#define races ((unsigned char*)(0xBC85))
#define classes ((unsigned char*)(0xBCA3))
#define createchardata ((unsigned char*)(0xBD1C))
#define errornummap ((unsigned char*)(0xBD8E))
#define okcreatemap ((unsigned char*)(0xBDB2))
#define okdeletemap ((unsigned char*)(0xBDBF))
#define okdispersemap ((unsigned char*)(0xBDCC))
#define yesmap ((unsigned char*)(0xBDDB))
#define nomap ((unsigned char*)(0xBDDE))
#define errorpartymap ((unsigned char*)(0xBDE0))
#define errorinpartymap ((unsigned char*)(0xBDEF))
#define errorformedmap ((unsigned char*)(0xBE15))
#define formpartymap ((unsigned char*)(0xBE33))
#define selectmap ((unsigned char*)(0xBE5F))
#define donemap ((unsigned char*)(0xBE66))	
#define slashdat ((unsigned char*)(0xBE6D))	
#define condcodes ((unsigned char*)(0xBE7D))	
#define cardsdat ((unsigned char*)(0xBE81))	
#define marksdat ((unsigned char*)(0xBE95))	

extern PLAYER players[] ;

extern UBYTE isnewgame ;

unsigned char screenbuf1[32] ;
unsigned char *checksum ;
UBYTE numleft ;

UBYTE partyarr[4] ;

UBYTE partyexists()
{
	UBYTE found, n ;
	found = 0 ;
	n=0 ;

	SWITCH_RAM_MBC5(0) ;    
	while ( (n<12) && !found )
	{
		if ( *(unsigned char*)(0xA004+((UWORD)n<<7UL)+58UL) )
			found = 1 ;
		else
			n++	;
	}
	SWITCH_RAM_MBC5(2) ;    
	return found ;

}

void displaymessage(UBYTE xpos, UBYTE ypos, UBYTE xlen, UBYTE ylen,
					unsigned char *msgdata)
{
	UBYTE n ;

	memset(screenbuf1,0x5DU,32UL) ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	for ( n = 0 ; n<6 ; n++ )
		set_data2((unsigned char*)0x9800+(((UWORD)n+10L)*32UL),screenbuf1,19UL) ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf1,0x00U,32UL) ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	for ( n = 0 ; n<6 ; n++ )
		set_data2((unsigned char*)0x9800+(((UWORD)n+10L)*32UL),screenbuf1,19UL) ;
	VBK_REG = 0;		// select palette bank 

	for ( n=0 ; n<ylen ; n++ )
		set_data2((unsigned char*)(0x9800+(32L*((UWORD)n+(UWORD)ypos))+(UWORD)xpos),msgdata+((UWORD)n*(UWORD)xlen),(UWORD)xlen) ;

	LCDC_REG &= 0xF7 ;	//select $9800-$9BFF

	waitpad(J_A) ;
	waitpadup() ;



	LCDC_REG |= 0x08 ;	//select $9C00-$9FFF


}

UBYTE yesno(unsigned char* questiontext, UBYTE qlen)
{
	UBYTE n, joykeys, retval ;

	memset(screenbuf1,0x5DU,32UL) ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	for ( n = 0 ; n<6 ; n++ )
		set_data2((unsigned char*)0x9800+(((UWORD)n+10L)*32UL),screenbuf1,19UL) ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf1,0x00U,32UL) ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	for ( n = 0 ; n<6 ; n++ )
		set_data2((unsigned char*)0x9800+(((UWORD)n+10L)*32UL),screenbuf1,19UL) ;
	VBK_REG = 0;		// select palette bank 

	set_data2((unsigned char*)(0x9800+(32L*11L)+((19-qlen)>>1)),questiontext,(UWORD)qlen) ;

	set_data2((unsigned char*)(0x9808+(32L*13L)),yesmap,3L) ;
	set_data2((unsigned char*)(0x9808+(32L*14L)),nomap,2L) ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf1,0x04U,3UL) ;
	set_data2((unsigned char*)(0x9808+(32L*14L)),screenbuf1,3L) ;
	VBK_REG = 0;		// select palette bank 

	LCDC_REG &= 0xF7 ;	//select $9800-$9BFF

	joykeys = 0 ;
	retval=1 ;
	while ( ! (joykeys&J_A) )
	{
		joykeys =joypad() ;
		if ( (joykeys&J_UP)||(joykeys&J_DOWN) )
		{
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x00U,3UL) ;
			set_data2((unsigned char*)(0x9808+(32L*((UWORD)retval+13L))),screenbuf1,3L) ;

			if ( retval==0 )
				retval=1 ;
			else
				retval=0 ;

			memset(screenbuf1,0x04U,3UL) ;
			set_data2((unsigned char*)(0x9808+(32L*((UWORD)retval+13L))),screenbuf1,3L) ;
			VBK_REG = 0;	 // select palette bank 
			waitpadup() ;

		}



	}
	waitpadup() ;


	if ( retval==0 )
	{
		memset(screenbuf1,0x5DU,32UL) ;
		for ( n = 0 ; n<6 ; n++ )
			set_data2((unsigned char*)0x9C00+(((UWORD)n+10L)*32UL),screenbuf1,19UL) ;

		memset(screenbuf1,0x0U,32UL) ;
		VBK_REG = 1;	 // select palette bank 
		for ( n = 0 ; n<6 ; n++ )
			set_data2((unsigned char*)0x9C00+(((UWORD)n+10L)*32UL),screenbuf1,19UL) ;
		VBK_REG = 0;	 // select palette bank 


	}

	LCDC_REG |= 0x08 ;	//select $9C00-$9FFF

	return(retval==0); 
}

void formatnumber(UWORD num,UBYTE length)
{
	UBYTE n ;
	unsigned char ch ;
	UWORD tens ;

	tens =1 ;

	for ( n=0 ; n<length-1 ; n++ )
		tens = tens*10 ;

	for ( n=0 ; n<length ; n++ )
	{
		ch=0x5EU ; //'0'
		while ( num>= tens )
		{
			num -= tens ;
			ch++ ;
		}
		tens = tens/10 ;
		screenbuf1[n] = ch ;


	}

}

void showcharacter(UBYTE which)
{
	UBYTE n, currarmor, currweapon, joykeys, done ;
	UBYTE currsel,nextptr ;


	memset(screenbuf1,0x5DU,32UL) ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	for ( n = 0 ; n<16 ; n++ )
		set_data2((unsigned char*)0x9800+((UWORD)n*32UL),screenbuf1,19UL) ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf1,0x00U,32UL) ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	for ( n = 0 ; n<16 ; n++ )
		set_data2((unsigned char*)0x9800+((UWORD)n*32UL),screenbuf1,19UL) ;
	VBK_REG = 0;		// select palette bank 

	SWITCH_RAM_MBC5(0) ;    
	memcpy(&players[4],(unsigned char*)(0xA004+((UWORD)which<<7UL)),127L) ;
	SWITCH_RAM_MBC5(2) ;    

	set_data2((unsigned char*)0x9800,players[4].name,0x07UL) ;

	for ( n=1 ; n<15 ; n++ )
		set_data2((unsigned char*)(0x9800+(32L*(UWORD)n)),stats1+((UWORD)(n-1)*6L),6L) ;

	for ( n=0 ; n<8 ; n++ )
		set_data2((unsigned char*)(0x980D+(32L*(UWORD)n)),stats2+((UWORD)n*6L),6L) ;

	set_data2((unsigned char*)(0x9804+(32L*10L)),stats3,11L) ;
	set_data2((unsigned char*)(0x9804+(32L*11L)),stats3+11L,11L) ;

	if ( players[4].inparty )
		set_data2((unsigned char*)(0x980D+(32L*3L)),stats4+6L,6L) ;
	else
		set_data2((unsigned char*)(0x980D+(32L*3L)),stats4,6L) ;

	set_data2((unsigned char*)(0x9802+(8L*32L)),weaponsdat+(8L*(UWORD)players[4].weapon),8L) ;
	set_data2((unsigned char*)(0x9802+(9L*32L)),armorsdat+(8L*(UWORD)players[4].armor),8L) ;

	formatnumber(players[4].currHP,4) ;
	screenbuf1[4] = 0x27 ;
	set_data2((unsigned char*)(0x9802+(1L*32L)),screenbuf1,5L) ;

	formatnumber(players[4].maxHP,4) ;
	set_data2((unsigned char*)(0x9807+(1L*32L)),screenbuf1,4L) ;

	set_data2((unsigned char*)(0x980B+(0L*32L)),condcodes+(UWORD)(players[4].status),1L) ;

	formatnumber( players[4].food,4) ;
	set_data2((unsigned char*)(0x980F+(2L*32L)),screenbuf1,4L) ;

	formatnumber( players[4].gold,4) ;
	set_data2((unsigned char*)(0x9802+(3L*32L)),screenbuf1,4L) ;

	formatnumber( (UWORD)(players[4].magic),2) ;
	set_data2((unsigned char*)(0x9811+(1L*32L)),screenbuf1,2L) ;
	formatnumber( ((UWORD)(players[4].level)),2) ;
	set_data2((unsigned char*)(0x9811+(0L*32L)),screenbuf1,2L) ;

	formatnumber( players[4].exp,4) ;
	set_data2((unsigned char*)(0x9802+(2L*32L)),screenbuf1,4L) ;

	formatnumber( (UWORD)players[4].str,2) ;
	set_data2((unsigned char*)(0x9804+(4L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].dex,2) ;
	set_data2((unsigned char*)(0x9811+(4L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].intel,2) ;
	set_data2((unsigned char*)(0x9804+(5L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].wis,2) ;
	set_data2((unsigned char*)(0x9811+(5L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].gems,2) ;
	set_data2((unsigned char*)(0x9804+(6L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].keys,2) ;
	set_data2((unsigned char*)(0x9811+(6L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].powders,2) ;
	set_data2((unsigned char*)(0x9804+(7L*32L)),screenbuf1,2L) ;
	formatnumber( (UWORD)players[4].torches,2) ;
	set_data2((unsigned char*)(0x9811+(7L*32L)),screenbuf1,2L) ;

	set_data2((unsigned char*)(0x9808+(0L*32L)),sexes+((UWORD)players[4].sex*6L),1L) ;
	set_data2((unsigned char*)(0x9809+(0L*32L)),races+((UWORD)players[4].race*6L),1L) ;
	set_data2((unsigned char*)(0x980A+(0L*32L)),classes+((UWORD)players[4].skill*11L),1L) ;

	for ( n=0 ; n<4 ; n++ )
		if ( (players[4].markcard>>n)&0x01 )
			set_data2((unsigned char*)(0x9807+(14L*32L)+((UWORD)(n&0x01)*6L)+((UWORD)(n&0x02)*16L)),
					  cardsdat+((UWORD)n*5L),5L) ;

	for ( n=0 ; n<4 ; n++ )
		if ( (players[4].markcard>>(4+n))&0x01 )
			set_data2((unsigned char*)(0x9807+(12L*32L)+((UWORD)(n&0x01)*6L)+((UWORD)(n&0x02)*16L)),
					  marksdat+((UWORD)n*5L),5L) ;


	VBK_REG = 1;		// select palette bank 
	memset(screenbuf1,0x04U,32UL) ;
	set_data2((unsigned char*)(0x9804+(32L*10L)),screenbuf1,11L) ;
	VBK_REG = 0;		// select palette bank 

	done=0 ;
	currsel = 0 ; //weapon line selected
	currarmor = 99 ;
	currweapon = 99 ;    

	LCDC_REG &= 0xF7 ;	//select $9800-$9BFF

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
					if ( (players[4].weapons)[nextptr] )
						break ;
					else
						nextptr++ ;

				if ( nextptr>=16 )
				{
					currweapon = 99 ;
					set_data2((unsigned char*)(0x9804+(32L*10L)),stats3,11L) ;
				}
				else
				{
					currweapon = nextptr ;
					memset(screenbuf1,0x5D,11L) ;
					screenbuf1[0] = (players[4].weapons)[currweapon]+0x5e ;
					memcpy(screenbuf1+2L,weaponsdat+((UWORD)currweapon*8L),8L) ;
					set_data2((unsigned char*)(0x9804+(32L*10L)),screenbuf1,11L) ;
				}


			}
			else
			{
				if ( currarmor==99 )
					nextptr = 0 ;
				else
					nextptr	= currarmor+1 ;

				while ( nextptr<8 )
					if ( (players[4].armors)[nextptr] )
						break ;
					else
						nextptr++ ;

				if ( nextptr>=8 )
				{
					currarmor = 99 ;
					set_data2((unsigned char*)(0x9804+(32L*11L)),stats3+11L,11L) ;
				}
				else
				{
					currarmor = nextptr ;
					memset(screenbuf1,0x5D,11L) ;
					screenbuf1[0] = (players[4].armors)[currarmor]+0x5e ;
					memcpy(screenbuf1+2L,armorsdat+((UWORD)currarmor*8L),8L) ;
					set_data2((unsigned char*)(0x9804+(32L*11L)),screenbuf1,11L) ;
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
					if ( (players[4].weapons)[nextptr-1] )
						break ;
					else
						nextptr-- ;

				if ( nextptr==0 )
				{
					currweapon = 99 ;
					set_data2((unsigned char*)(0x9804+(32L*10L)),stats3,11L) ;
				}
				else
				{
					currweapon = nextptr-1 ;
					memset(screenbuf1,0x5D,11L) ;
					screenbuf1[0] = (players[4].weapons)[currweapon]+0x5e ;
					memcpy(screenbuf1+2L,weaponsdat+((UWORD)currweapon*8L),8L) ;
					set_data2((unsigned char*)(0x9804+(32L*10L)),screenbuf1,11L) ;
				}


			}
			else
			{
				if ( currarmor==99 )
					nextptr = 8 ;
				else
					nextptr	= currarmor ;

				while ( nextptr>0 )
					if ( (players[4].armors)[nextptr-1] )
						break ;
					else
						nextptr-- ;

				if ( nextptr==0 )
				{
					currarmor = 99 ;
					set_data2((unsigned char*)(0x9804+(32L*11L)),stats3+11L,11L) ;
				}
				else
				{
					currarmor = nextptr-1 ;
					memset(screenbuf1,0x5D,11L) ;
					screenbuf1[0] = (players[4].armors)[currarmor]+0x5e ;
					memcpy(screenbuf1+2L,armorsdat+((UWORD)currarmor*8L),8L) ;
					set_data2((unsigned char*)(0x9804+(32L*11L)),screenbuf1,11L) ;
				}


			}

			waitpadup() ;
		}

		if ( (joykeys&J_UP)||(joykeys&J_DOWN) )
		{
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x00U,32UL) ;
			set_data2((unsigned char*)(0x9804+(32L*(10L+(UWORD)currsel))),screenbuf1,11L) ;
			VBK_REG = 0;	 // select palette bank 

			if ( currsel==0 )
				currsel=1;
			else
				currsel	= 0 ;

			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x04U,32UL) ;
			set_data2((unsigned char*)(0x9804+(32L*(10L+(UWORD)currsel))),screenbuf1,11L) ;
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



	LCDC_REG |= 0x08 ;	//select $9C00-$9FFF

}

UBYTE playerlisting(UBYTE empty) 
{
	UBYTE currline, n, joykeys ;

	VBK_REG = 1;		// select palette bank 

	memset(screenbuf1,2U,19L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 0;		// select palette bank 


	memset(screenbuf1,0x5DU,32L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	for ( n=0 ; n<12 ;n++ )
		screenbuf1[n] = n+0x1A ;

	set_bkg_tiles2( 0, 10, 1, 6, (unsigned char*)screenbuf1 );
	set_bkg_tiles2( 10, 10, 1, 6, (unsigned char*)screenbuf1+0x06L );


	SWITCH_RAM_MBC5(0) ;    
	for ( n=0 ; n<6 ; n++ )
	{
		if ( *(unsigned char*)(0xA004+((UWORD)n<<7L)) )
			set_bkg_tiles2(2,10+n,7,1,(unsigned char*)(0xA004+((UWORD)n<<7L)));
		if ( *(unsigned char*)(0xA004+((UWORD)(n+6)<<7L)) )
			set_bkg_tiles2(12,10+n,7,1,(unsigned char*)(0xA004+((UWORD)(n+6)<<7L)));
	}
	SWITCH_RAM_MBC5(2) ;    

	currline = 0 ;

	VBK_REG = 1;		// select palette bank 
	memset(screenbuf1,6,19L) ;

	if ( currline<6 )
		set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
	else
		set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 0;		// select palette bank 

	while ( 1 )
	{
		joykeys = joypad() ;

		if ( joykeys&J_UP )
		{
			VBK_REG = 1;	  // select palette bank 

			memset(screenbuf1,2,19L) ;
			if ( currline<6 )
				set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
			else
				set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

			if ( currline==0 )
				currline = 5 ;
			else
				if ( currline==6 )
				currline = 11;
			else
				currline-- ;

			memset(screenbuf1,6,19L) ;
			if ( currline<6 )
				set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
			else
				set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

			VBK_REG = 0;	  // select palette bank 
			waitpadup(); 


		}
		if ( (joykeys&J_LEFT)||(joykeys&J_RIGHT) )
		{
			VBK_REG = 1;	  // select palette bank 

			memset(screenbuf1,2,19L) ;
			if ( currline<6 )
				set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
			else
				set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

			if ( currline<6 )
				currline += 6 ;
			else
				currline -= 6 ;

			memset(screenbuf1,6,19L) ;
			if ( currline<6 )
				set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
			else
				set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

			VBK_REG = 0;	  // select palette bank 
			waitpadup(); 


		}
		if ( joykeys&J_DOWN )
		{
			VBK_REG = 1;	  // select palette bank 

			memset(screenbuf1,2,19L) ;
			if ( currline<6 )
				set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
			else
				set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

			if ( currline==5 )
				currline = 0 ;
			else
				if ( currline==11 )
				currline = 6;
			else
				currline++ ;

			memset(screenbuf1,6,19L) ;
			if ( currline<6 )
				set_bkg_tiles2( 0,10+currline, 9, 1, (unsigned char*)screenbuf1 );
			else
				set_bkg_tiles2( 10,10+(currline-6), 9, 1, (unsigned char*)screenbuf1 );

			VBK_REG = 0;	  // select palette bank 
			waitpadup(); 


		}
		if ( joypad()&J_A )
		{
			SWITCH_RAM_MBC5(0) ;    

			if ( *(unsigned char*)(0xA004+((UWORD)currline<<7L)) )
				if ( empty==0 )
					break ;
				else
				{
				}
			else
				if ( empty==1 )
				break ;
			SWITCH_RAM_MBC5(2) ;    
		}
		if ( joypad()&J_B )
		{
			currline=99U ;
			break ;
		}

		wait_vbl_done() ;
	}

	SWITCH_RAM_MBC5(2) ;    
	waitpadup() ;
	return currline ;
}

void examineregister()
{ 
	UBYTE playernum ;

	while ( (playernum=playerlisting(0)) !=99U )
		showcharacter(playernum) ;

}

UBYTE getclassrace (UBYTE linelen, UBYTE ypos, UBYTE maxnum, unsigned char *charmap,
					UBYTE *val )
{
	UBYTE joykeys ;

	VBK_REG = 1;	 // select palette bank 
	memset(screenbuf1,6,19L) ;
	set_bkg_tiles2( 6, ypos, linelen, 1, (unsigned char*)screenbuf1 );
	VBK_REG = 0;	 // select palette bank 

	joykeys=joypad() ;

	while ( !((joykeys&J_A) || (joykeys&J_B)) )
	{
		if ( (joykeys&J_RIGHT)||(joykeys&J_DOWN) )
		{
			if ( *val==maxnum )
				*val = 0 ;
			else
				(*val)++ ;

			set_bkg_tiles2(6,ypos,linelen,1,charmap+( (UWORD)(*val)*(UWORD)linelen)) ;
			waitpadup() ;
		}
		if ( (joykeys&J_LEFT)||(joykeys&J_UP) )
		{
			if ( *val==0 )
				*val = maxnum ;
			else
				(*val)-- ;

			set_bkg_tiles2(6,ypos,linelen,1,charmap+( (UWORD)(*val)*(UWORD)linelen)) ;
			waitpadup() ;
		}

		joykeys=joypad() ;    
	}    

	waitpadup() ;    
	VBK_REG = 1;	 // select palette bank 
	memset(screenbuf1,2,19L) ;
	set_bkg_tiles2( 6, ypos, linelen, 1, (unsigned char*)screenbuf1 );
	VBK_REG = 0;	 // select palette bank 
	return joykeys ;
}


UBYTE getattribs (UBYTE xpostens, UBYTE ypos, UBYTE *val )
{
	UBYTE joykeys, xposcurr ;

	VBK_REG = 1;	 // select palette bank 
	memset(screenbuf1,6,19L) ;
	set_bkg_tiles2( xpostens, ypos, 1, 1, (unsigned char*)screenbuf1 );
	VBK_REG = 0;	 // select palette bank 

	xposcurr = xpostens ;
	joykeys=joypad() ;

	while ( !((joykeys&J_A) || (joykeys&J_B)) )
	{
		if ( (joykeys&J_RIGHT)||(joykeys&J_LEFT) )
		{
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x02,9L) ;
			set_bkg_tiles2(xposcurr,ypos,1,1,(unsigned char*)screenbuf1) ;
			if ( xposcurr==xpostens )
				xposcurr++ ;
			else
				xposcurr-- ;

			memset(screenbuf1,0x06,9L) ;
			set_bkg_tiles2(xposcurr,ypos,1,1,(unsigned char*)screenbuf1) ;
			VBK_REG = 0;	 // select palette bank 
		}
		if ( joykeys&J_DOWN )
		{
			if ( xposcurr==xpostens )
			{
				if ( *val > 9 )
				{
					*val -=10 ;
					formatnumber((UWORD)*val,2) ;
					set_bkg_tiles2( xpostens, ypos, 2, 1, (unsigned char*)screenbuf1 );
					//(*( (unsigned char*)(0x9C00+(UWORD)xposcurr+(UWORD)((UWORD)ypos*32L))))-- ;
					numleft += 10 ;
				}
			}
			else
			{
				if ( (*val > 0) && ((*val)%10 !=0) )
				{
					*val -=1 ;
					formatnumber((UWORD)*val,2) ;
					set_bkg_tiles2( xpostens, ypos, 2, 1, (unsigned char*)screenbuf1 );
					//(*( (unsigned char*)(0x9C00+(UWORD)xposcurr+(UWORD)((UWORD)ypos*32L))))-- ;
					numleft++  ;
				}
			}

		}
		if ( joykeys&J_UP )
		{
			if ( xposcurr==xpostens )
			{
				if ( numleft > 9 )
				{
					*val +=10 ;
					formatnumber((UWORD)*val,2) ;
					set_bkg_tiles2( xpostens, ypos, 2, 1, (unsigned char*)screenbuf1 );
					//(*( (unsigned char*)(0x9C00+(UWORD)xposcurr+(UWORD)((UWORD)ypos*32L))))++ ;
					numleft -=10 ;
				}
			}
			else
			{
				if ( (numleft > 0) && ((*val)%10 !=9) )
				{
					*val +=1 ;
					formatnumber((UWORD)*val,2) ;
					set_bkg_tiles2( xpostens, ypos, 2, 1, (unsigned char*)screenbuf1 );
					//(*( (unsigned char*)(0x9C00+(UWORD)xposcurr+(UWORD)((UWORD)ypos*32L))))++ ;
					numleft -= 1 ;
				}
			}

		}
		if ( (joykeys&J_UP)||(joykeys&J_DOWN) )
		{
			formatnumber((UWORD)numleft,2) ;
			set_bkg_tiles2( 2, 15, 2, 1, (unsigned char*)screenbuf1 );
		}
		if ( joykeys )
			waitpadup() ;

		joykeys=joypad() ;
	}

	waitpadup() ;    
	VBK_REG = 1;	 // select palette bank 
	memset(screenbuf1,2,19L) ;
	set_bkg_tiles2( xposcurr, ypos, 1, 1, (unsigned char*)screenbuf1 );
	VBK_REG = 0;	 // select palette bank 
	return joykeys ;
}

void createcharacter() 
{
	UBYTE currline, n, joykeys, playernum, done ;
	UBYTE textpos ;

	memset(players[4].name,(unsigned char)('A'-0x04),7L) ;
	players[4].skill = 0 ;
	players[4].race = 0 ;
	players[4].str = 0 ;
	players[4].dex = 0 ;
	players[4].intel = 0 ;
	players[4].wis = 0 ;
	players[4].sex = 0 ;
	numleft = 50 ;

	playernum=playerlisting(1) ;

	if ( playernum==99U )
		return ;

	players[4].rosterpos = playernum ;

	memset(screenbuf1,0x5DU,32L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 1;	 // select palette bank 

	memset(screenbuf1,2,19L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	screenbuf1[1] = 6 ;
	set_bkg_tiles2(6,10,1,1,(unsigned char*)(screenbuf1+1L)) ;

	VBK_REG = 0;	 // select palette bank 


	set_bkg_tiles2(0,10,19,6,createchardata) ;    

	done = 0 ;
	textpos = 0 ;

	while ( done==0 )
	{
		joykeys = joypad() ;
		if ( joykeys&J_RIGHT )
		{
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x02,19L) ;
			set_bkg_tiles2(6+textpos,10,1,1,(unsigned char*)screenbuf1) ;
			if ( textpos==6 )
				textpos = 0 ;
			else
				textpos++ ;
			memset(screenbuf1,0x06,19L) ;
			set_bkg_tiles2(6+textpos,10,1,1,(unsigned char*)(screenbuf1+1L)) ;
			VBK_REG = 0;	 // select palette bank 
			waitpadup() ;
		}
		if ( joykeys&J_LEFT )
		{
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x02,19L) ;
			set_bkg_tiles2(6+textpos,10,1,1,(unsigned char*)screenbuf1) ;
			if ( textpos==0 )
				textpos = 6 ;
			else
				textpos-- ;
			memset(screenbuf1,0x06,19L) ;
			set_bkg_tiles2(6+textpos,10,1,1,(unsigned char*)(screenbuf1+1L)) ;
			VBK_REG = 0;	 // select palette bank 
			waitpadup() ;
		}
		if ( joykeys&J_DOWN )
		{
			if ( players[4].name[textpos]=='Z'-0x04 )
				players[4].name[textpos]=0x5D ;
			else
				if ( players[4].name[textpos]==0x5D )
				players[4].name[textpos]='A'-0x04 ;
			else
				(players[4].name[textpos])++ ;
			set_bkg_tiles2(6,10,7,1,players[4].name) ;
			waitpadup() ;
		}
		if ( joykeys&J_UP )
		{
			if ( players[4].name[textpos]=='A'-0x04 )
				players[4].name[textpos]=0x5D ;
			else
				if ( players[4].name[textpos]==0x5D )
				players[4].name[textpos]='Z'-0x04 ;
			else
				(players[4].name[textpos])-- ;
			set_bkg_tiles2(6,10,7,1,players[4].name) ;
			waitpadup() ;
		}
		if ( joykeys&J_B )
		{
			done = 2 ;
			break ;
		}
		if ( joykeys&J_A )
		{
			waitpadup() ;
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,0x02,19L) ;
			set_bkg_tiles2(6+textpos,10,1,1,(unsigned char*)screenbuf1) ;
			memset(screenbuf1,0x06,1L) ;
			set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;
			VBK_REG = 0;	 // select palette bank 
			textpos = 0 ;
			while ( done==0 )
			{
				joykeys = joypad() ;

				if ( (joykeys&J_UP)||(joykeys&J_DOWN)||(joykeys&J_LEFT)||(joykeys&J_RIGHT) )
				{
					if ( players[4].sex==0 )
					{
						players[4].sex=1 ;
						screenbuf1[0] = 'F'-0x04 ;
						set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;
					}
					else
						if ( players[4].sex==1 )
					{
						players[4].sex=2 ;
						screenbuf1[0] = 'O'-0x04 ;
						set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;


					}
					else
					{
						players[4].sex=0 ;
						screenbuf1[0] = 'M'-0x04 ;
						set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;


					}


					waitpadup() ;
				}
				if ( joykeys&J_B )
				{
					waitpadup() ;
					textpos = 0 ;
					VBK_REG = 1;	   // select palette bank 
					screenbuf1[0] = 2 ;
					set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;
					screenbuf1[0] = 6 ;
					set_bkg_tiles2(6,10,1,1,(unsigned char*)(screenbuf1)) ;
					VBK_REG = 0;	   // select palette bank 
					break ;
				}
				if ( joykeys&J_A )
				{
					waitpadup() ;
					VBK_REG = 1;	   // select palette bank 
					screenbuf1[0] = 2 ;
					set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;
					VBK_REG = 0;	   // select palette bank 
					while ( done==0 )
					{
						joykeys = joypad() ;

						if ( (getclassrace(6,11,4,races,&(players[4].race)))&J_A )
							while ( done==0 )
							{
								if ( (getclassrace(11,12,10,classes,&(players[4].skill)))&J_A )
									while ( done==0 )
									{
										if ( (getattribs(4,13,&(players[4].str)))&J_A )
											while ( done==0 )
											{
												if ( (getattribs(16,13,&(players[4].dex)))&J_A )
													while ( done==0 )
													{
														if ( (getattribs(4,14,&(players[4].intel)))&J_A )
															while ( done==0 )
															{
																if ( (getattribs(16,14,&(players[4].wis)))&J_A )
																{
																	if ( (players[4].str>4)&&(players[4].dex>4)&&(players[4].intel>4)&&(players[4].wis>4) )
																	{
																		if ( yesno(okcreatemap,13) )
																		{
																			done=1 ;
																			break ;
																		}
																	}
																	else
																		displaymessage(0,12,18,2,errornummap) ;
																	//shownumerror() ;
																}
																else
																	break ;
															}
														else
															break ;
													}
												else
													break ;
											}
										else
											break ;
									}
								else
									break ;
							}
						else
						{
							VBK_REG = 1;	 // select palette bank 
							screenbuf1[0] = 6 ;
							set_bkg_tiles2(18,10,1,1,(unsigned char*)screenbuf1) ;
							VBK_REG = 0;	 // select palette bank 
							break ;
						}

					}
				}
			}

		}


	}

	waitpadup() ;
	if ( done==1 )
	{
		players[4].currHP = 150UL ;
		players[4].maxHP = 150UL ;
		players[4].status = 0 ;
		players[4].food = 150UL ;
		players[4].gold = 150UL ;
		players[4].magic = 0x00 ;
		players[4].level = 0x01 ;
		players[4].exp = 0x0000 ;
		players[4].gems = 0x00 ;
		players[4].keys = 0x00 ;
		players[4].powders=0x00 ;
		players[4].torches=0x00 ;
		players[4].weapon = 0x01 ;
		players[4].armor = 0x01 ;
		memset(players[4].weapons+1L,0x00,15L) ;
		memset(players[4].armors+1L,0x00,7L) ;
		memset(players[4].weapons,0x01,1L) ;
		memset(players[4].armors,0x01,1L) ;
		players[4].markcard = 0x00 ;
		players[4].inparty = 0x00 ;
		SWITCH_RAM_MBC5(0) ;    
		memcpy((unsigned char*)(0xA004+((UWORD)playernum<<7UL)),&players[4],127L) ;
		n = 0 ;
		for ( checksum=(unsigned char*)0xA000 ; checksum < (unsigned char*)0xBFFF ; checksum++ )
			n += *checksum ;
		memcpy((unsigned char*)(0xBFFF),&n,1L) ;
		SWITCH_RAM_MBC5(2) ;    

	}
}

UBYTE getplayer(UBYTE pnum) 
{
	UBYTE joykeys ;
	UBYTE done ;
	UBYTE whichplayer ;
	UBYTE nextptr ;
	unsigned char isthere ;

	set_bkg_tiles2( 11, 11+pnum, 7, 1, donemap );

	VBK_REG = 1;	 // select palette bank 

	memset(screenbuf1,6,19L) ;
	set_bkg_tiles2( 11, 11+pnum, 7, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 0;	 // select palette bank 

	done=0 ;
	whichplayer = 99 ; //done
	while ( done==0 )
	{
		joykeys = joypad() ;
		if ( (joykeys&J_RIGHT)||(joykeys&J_DOWN) )
		{
			if ( whichplayer==99 )
				nextptr = 0 ;
			else
				nextptr	= whichplayer+1 ;
			while ( nextptr <12 )
			{
				SWITCH_RAM_MBC5(0) ;
				isthere = *(unsigned char*)(0xA004+((UWORD)nextptr<<7L)) ;
				SWITCH_RAM_MBC5(2) ;
				if ( (isthere) &&
					 (partyarr[0]!=nextptr) && (partyarr[1]!=nextptr) &&
					 (partyarr[2]!=nextptr) )
					break;
				else
					nextptr++ ;

			}
			if ( nextptr>=12 )
			{
				set_bkg_tiles2( 11, 11+pnum, 7, 1, donemap );
				whichplayer=99 ;
			}
			else
			{
				SWITCH_RAM_MBC5(0) ;
				set_bkg_tiles2( 11, 11+pnum, 7, 1, (unsigned char*)(0xA004+((UWORD)nextptr<<7L)) );
				whichplayer=nextptr;
				SWITCH_RAM_MBC5(2) ;
			}

			waitpadup() ;
		}
		if ( (joykeys&J_LEFT)||(joykeys&J_UP) )
		{
			if ( whichplayer==99 )
				nextptr = 12 ;
			else
				nextptr	= whichplayer ;
			while ( nextptr >0 )
			{
				SWITCH_RAM_MBC5(0) ;
				isthere = *(unsigned char*)(0xA004+(((UWORD)nextptr-1L)<<7L)) ;
				SWITCH_RAM_MBC5(2) ;
				if ( (isthere) &&
					 (partyarr[0]!=nextptr-1) && (partyarr[1]!=nextptr-1) &&
					 (partyarr[2]!=nextptr-1) )
					break;
				else
					nextptr-- ;

			}
			if ( nextptr==0 )
			{
				set_bkg_tiles2( 11, 11+pnum, 7, 1, donemap );
				whichplayer=99 ;
			}
			else
			{
				SWITCH_RAM_MBC5(0) ;
				set_bkg_tiles2( 11, 11+pnum, 7, 1, (unsigned char*)(0xA004+(((UWORD)nextptr-1L)<<7L)) );
				whichplayer = nextptr-1 ;
				SWITCH_RAM_MBC5(2) ;
			}

			waitpadup() ;
		}
		if ( joykeys&J_B )
		{
			done = 99 ;	 //cancel, backup
			waitpadup() ;
			break ;
		}
		if ( joykeys&J_A )
		{
			if ( whichplayer==99 )	//done selecting
				done=98 ;
			else
			{
				done=1 ;
				partyarr[pnum] = whichplayer ;
			}
			VBK_REG = 1;	 // select palette bank 
			memset(screenbuf1,2,19L) ;
			set_bkg_tiles2( 11, 11+pnum, 7, 1, (unsigned char*)screenbuf1 );
			VBK_REG = 0;	 // select palette bank 
			waitpadup() ;
			break ;
		}
	}    

	VBK_REG = 1;	 // select palette bank 

	memset(screenbuf1,2,19L) ;
	set_bkg_tiles2( 11, 11+pnum, 7, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 0;	 // select palette bank 

	if ( done==99 )
	{
		memset(screenbuf1,0x5d,19L) ;
		set_bkg_tiles2( 11, 11+pnum, 7, 1, (unsigned char*)screenbuf1 );
	}

	if ( done==1 )	//valid character, progress
		done = whichplayer ;

	return done ;

}

void formparty() 
{
	UBYTE done ;
	UBYTE playernum,n ;
	if ( partyexists() )
	{
		displaymessage(2,12,15,2,errorformedmap) ;
		//showformederror() ;
		return ;
	}


	memset(screenbuf1,0x5DU,32L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 1;	 // select palette bank 

	memset(screenbuf1,2,19L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );


	VBK_REG = 0;	 // select palette bank 


	set_bkg_tiles2(0,11,11,4,formpartymap) ;    

	done = 0 ;
	memset(partyarr,(unsigned char)0x99,4L) ;

	while ( done==0 )
	{
		if ( (playernum=(getplayer(0))) >90 )
		{
			if ( playernum==98 )
			{
				done=1 ;
				break ;
			}
			done=2;
			break ;
		}
		else
		{
			while ( done==0 )
			{
				if ( (playernum=(getplayer(1))) >90 )
				{
					if ( playernum==98 )
					{
						done=1 ;
						break ;
					}
					partyarr[0]=0x99 ;
					memset(screenbuf1,0x5DU,7L) ;
					set_bkg_tiles2( 11, 11, 7, 1, screenbuf1);
					break ;

				}
				else
				{
					while ( done==0 )
					{
						if ( (playernum=(getplayer(2))) >90 )
						{
							if ( playernum==98 )
							{
								done=1 ;
								break ;
							}
							partyarr[1]=0x99 ;
							memset(screenbuf1,0x5DU,7L) ;
							set_bkg_tiles2( 11, 12, 7, 1, screenbuf1);
							break ;
						}
						else
						{
							while ( done==0 )
							{
								if ( (playernum=(getplayer(3))) >90 )
								{
									if ( playernum==98 )
									{
										done=1 ;
										break ;
									}
									partyarr[2]=0x99 ;
									memset(screenbuf1,0x5DU,7L) ;
									set_bkg_tiles2( 11, 13, 7, 1, screenbuf1);
									break ;
								}
								else
								{
									done=1 ;
									break ;
								}

							}
						}

					}
				}

			}
		}
	}


	SWITCH_RAM_MBC5(0) ;
	if ( done==1 )	//DONE
	{
		for ( n=0 ; n<4 ; n++ )
			if ( partyarr[n]!=99 )
				*(unsigned char*)(0xA004+((UWORD)(partyarr[n])<<7UL)+58UL) = n+1 ;

		n = 0 ;
		for ( checksum=(unsigned char*)0xA000 ; checksum < (unsigned char*)0xBFFF ; checksum++ )
			n += *checksum ;
		memcpy((unsigned char*)(0xBFFF),&n,1L) ;
		isnewgame = 1 ;
	}
	SWITCH_RAM_MBC5(2) ;
}


UWORD weaponcost2[] = {
	0L,
	5L,
	30L,
	60L,
	125L,
	350L,
	200L,
	250L,
	400L,
	1050L,
	800L,
	1200L,
	2700L,
	6550L,
	4550L,
} ;


UWORD armorcost2[] = {
	0L,
	75L,
	195L,
	575L,
	2500L,
	6130L,
	8250L
};


void disperseparty() 
{
	UBYTE t,n,lcv1,lcv2 ;
	UBYTE tarr[4] ;
	UWORD totgold ;
	UBYTE abortspread ;




	if ( !(partyexists()) )
	{
		displaymessage(2,12,15,1,errorpartymap) ;
		//     showpartyerror() ;
		return ;
	}


	if ( yesno(okdispersemap,15) )
	{
		memset(tarr,0,4L) ;
		abortspread = 0 ;
		t = 0 ;
		totgold = 0L ;
		SWITCH_RAM_MBC5(0) ;
		for ( n=0 ; n!=12 ; n++ )
		{
			memcpy(&players[4],(unsigned char*)(0xA004+((UWORD)n<<7UL)),127L) ;

			if ( players[4].inparty )
			{
				tarr[t++] = n ;
				totgold += players[4].gold ;
				if ( totgold>12000L )
					abortspread = 1 ;
				totgold += weaponcost2[players[4].weapon] ;
				if ( totgold>12000L )
					abortspread = 1 ;
				totgold += armorcost2[players[4].armor] ;
				for ( lcv1=0 ; lcv1!=16 ; lcv1++ )
					for ( lcv2=0 ; lcv2 != (players[4].weapons)[lcv1] ; lcv2++ )
					{
						totgold += weaponcost2[lcv1] ;
						if ( totgold>12000L )
							abortspread = 1 ;

					}
				for ( lcv1=0 ; lcv1!=8 ; lcv1++ )
					for ( lcv2=0 ; lcv2 != (players[4].armors)[lcv1] ; lcv2++ )
					{
						totgold += armorcost2[lcv1] ;
						if ( totgold>12000L )
							abortspread = 1 ;

					}


			}
		}

		totgold /= (UWORD)t ;
		for ( n=0 ; n!=t ; n++ )
		{
			memcpy(&players[4],(unsigned char*)(0xA004+((UWORD)(tarr[n])<<7UL)),127L) ;
			if ( (t>1)&&(abortspread==0) )
			{
				players[4].gold = totgold ;
				players[4].weapon = 0 ;
				players[4].armor = 0 ;
				memset(players[4].armors,0,8L) ;
				memset(players[4].weapons,0,16L) ;
				players[4].armors[0]=1 ;
				players[4].weapons[0]=2 ;
			}
			players[4].inparty = 0 ;
			memcpy((unsigned char*)(0xA004+((UWORD)(tarr[n])<<7UL)),&players[4],127L) ;


		}

		n = 0 ;
		for ( checksum=(unsigned char*)0xA000 ; checksum != (unsigned char*)0xBFFF ; checksum++ )
			n += *checksum ;
		memcpy((unsigned char*)(0xBFFF),&n,1L) ;
		SWITCH_RAM_MBC5(2) ;


	}

}

void terminatecharacter() 
{
	UBYTE playernum,n ;

	if ( (playernum = playerlisting(0))!=99 )
	{
		SWITCH_RAM_MBC5(0) ;
		if ( *(unsigned char*)(0xA004+((UWORD)playernum<<7UL)+58UL) )
		{
			SWITCH_RAM_MBC5(2) ;
			displaymessage(0,12,19,2,errorinpartymap) ;
			//showinpartyerror() ;
			return ;
		}
		SWITCH_RAM_MBC5(2) ;
		if ( yesno(okdeletemap,13) )
		{
			SWITCH_RAM_MBC5(0) ;
			memset((unsigned char*)(0xA004+((UWORD)playernum<<7UL)),0x00,127L) ;
			n = 0 ;
			for ( checksum=(unsigned char*)0xA000 ; checksum < (unsigned char*)0xBFFF ; checksum++ )
				n += *checksum ;
			memcpy((unsigned char*)(0xBFFF),&n,1L) ;
			SWITCH_RAM_MBC5(2) ;
		}
	}
}

unsigned char liksangdat[] = {
	'W' - 0x04,'W' -0x04 ,'W' -0x04 ,'Z'+0x10 ,'L' -0x04 ,'I' -0x04,'K' -0x04,'Z'+0x15 ,'S' -0x04 ,'A' -0x04 ,'N' -0x04 ,'G' -0x04,'Z'+0x10,'C' -0x04,'O' -0x04,'M' -0x04, 
} ;

void titlescreen()
{
	UBYTE n ;

	VBK_REG = 1;		// select palette bank 

	memset(screenbuf1,1,32L) ;
	for ( n = 0 ; n<32 ; n++ )
		set_bkg_tiles2( 0, n, 32, 1, (unsigned char*)screenbuf1 );

#ifndef LIKSANG
	memset(screenbuf1,2,19L) ;
	for ( n = 0 ; n<9 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	memset(screenbuf1,0,19L) ;
	for ( n = 0 ; n<8 ; n++ )
		set_bkg_tiles2( 0, n+9, 19, 1, (unsigned char*)screenbuf1 );
#endif

	VBK_REG = 0;		// select palette bank 

#ifndef LIKSANG
	memset(screenbuf1,171U,32L) ;
#else
	memset(screenbuf1,0x5D,32L) ;
#endif

	for ( n = 0 ; n<32 ; n++ )
		set_bkg_tiles2( 0, n, 32, 1, (unsigned char*)screenbuf1 );

#ifndef LIKSANG   
	set_bkg_tiles2( 0, 0, 19, 9, (unsigned char*)exodusmap );

	set_bkg_tiles2( 0, 9, 19, 8, (unsigned char*)ult3map );
	set_bkg_data2(  0, 172U, titletiles );
#else
	set_bkg_tiles2( 0, 0, 16, 1, liksangdat ) ;
	memset(screenbuf1,1,19L) ;
	VBK_REG=1 ;
	set_bkg_tiles2( 0, 0, 16, 1, screenbuf1 ) ;
	VBK_REG=0 ;
	set_bkg_data2(  0, 172U, introtiles );
#endif


	SCX_REG = 0xFC ;
	SCY_REG = 0xFC ;

}

void dointro()
{
	UBYTE mode4, mode8 ;
	UBYTE n ;
	UWORD moveind ;
	UBYTE introx, introy ;

	VBK_REG = 1;		// select palette bank 

	memset(screenbuf1,1,32L) ;
	for ( n = 0 ; n<32 ; n++ )
		set_bkg_tiles2( 0, n, 32, 1, (unsigned char*)screenbuf1 );

	memset(screenbuf1,2,19L) ;
	for ( n = 0 ; n<9 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	set_bkg_tiles2( 0, 10, 19, 6, intropalmap );

	VBK_REG = 0;		// select palette bank 


	for ( n = 0 ; n<23 ; n++ )
	{
		set_sprite_prop( n, 0x01 );
		move_sprite( n, 0,0 );
		set_sprite_tile( n, spritenums[n] );
	}


	move_sprite( 21, 12,144U );
	move_sprite( 8, 52,128U );
	set_sprite_prop( 0, 0x00 );
	set_sprite_prop( 1, 0x00 );
	set_sprite_prop( 18, 0x02 );



	memset(screenbuf1,0x76U,32L) ;
	for ( n = 0 ; n<32 ; n++ )
		set_bkg_tiles2( 0, n, 32, 1, (unsigned char*)screenbuf1 );

#ifndef LIKSANG
	set_bkg_tiles2( 0, 0, 19, 9, (unsigned char*)exodusmap2 );
#endif

	set_bkg_tiles2( 0, 10, 19, 6, (unsigned char*)intromap );

#ifndef LIKSANG
	set_bkg_tiles2( 3, 9, 12, 1, text1 );
#endif

	set_bkg_tiles2( 3, 16, 13, 1, text2 );

	set_data2((unsigned char*)0x8000,introtiles,0x770UL) ;
	set_data2((unsigned char*)0x8770,titletiles,0x760UL) ;

	SCX_REG = 0xFC ;
	SCY_REG = 0xF8 ;


	SHOW_SPRITES;
	DISPLAY_ON ;
	enable_interrupts2();

	mode4 = 0 ;
	mode8 = 0 ;
	moveind = 0L ;

	n=0 ;
	screenbuf1[0] = 0 ;
	while ( 1 )
	{
		if ( joypad()&J_START )
			screenbuf1[0] = 1 ;
		else
			if ( screenbuf1[0] )
			break ;

		if ( ++n==20 )
		{
			n = 0 ;

			if ( intromoves[moveind]!=0xFFU )
			{
				if ( intromoves[moveind]==0x80U )
					moveind = 0L ;
				else
				{
					if ( intromoves[moveind]&0x01 )	 //place it
					{
						introy = 0 ;
						introx = intromoves[moveind+1L]; 
						while ( introx > 18 )
						{
							introy++ ;
							introx -= 19 ;
						}
						move_sprite(intromoves[moveind]>>1,(introx*8)+12,(introy+13)*8) ;
					}
					else  //hide it
						move_sprite(intromoves[moveind]>>1,0,0)	;



				}



			}
			moveind += 2L ;
		}

		if ( (n%5)==0 )
		{
			if ( ++mode4==4 )
				mode4=0 ;
			if ( ++mode8==8 )
				mode8=0 ;

			set_bkg_data2(  0x00, 0x01, introtiles+(UWORD)(mode4<<4) );
			set_bkg_data2(  0x2A, 0x01, introtiles+(UWORD)(((UWORD)(mode8)+0x2AL)<<4) );
			set_bkg_data2(  0x32, 0x01, introtiles+(UWORD)(((UWORD)(mode8)+0x32L)<<4) );
		}

		wait_vbl_done() ;
		//waitpad(J_START) ;
		//waitpadup() ;
	}

	//waitpadup() ;    
	for ( n = 0 ; n<23 ; n++ )
		move_sprite( n, 0,0 );

}

unsigned char text5b[] = {
	'T' -0x04,'E' -0x04 ,'S' -0X04,'T' -0x04 ,0x5D ,'G' -0x04 ,
	'A' -0x04 ,'M' -0x04,'E' -0x04, 0x5D ,'M' -0X04 ,'U' -0X04 ,'S' -0x04 ,'I' -0x04 ,'C' -0x04 

};

UBYTE mainmenu()
{
	UBYTE currline, n, joykeys ;


	set_data2((unsigned char*)0x8000,fromhell,0x1A0UL) ;
	set_data2((unsigned char*)0x81A0,smallnums,0xC0UL) ;
	set_data2((unsigned char*)0x8260,introtiles+0x770,0x10UL) ;
	set_data2((unsigned char*)0x8270,slashdat,0x10UL) ;

	VBK_REG = 1;		// select palette bank 

	memset(screenbuf1,2,19L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 0;		// select palette bank 


	memset(screenbuf1,0x5DU,32L) ;
	for ( n = 10 ; n<16 ; n++ )
		set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

	set_bkg_tiles2( 3, 10, 13, 2, (unsigned char*)fromhellmap );

	set_bkg_tiles2( 2, 12, 15, 1, text3 );

	set_bkg_tiles2( 2, 13, 15, 1, text4 );

	set_bkg_tiles2( 2, 14, 15, 1, text5 );

	set_bkg_tiles2( 2, 15, 15, 1, text5b );

	memset(screenbuf1,0x76U,32L) ;
	set_bkg_tiles2( 3, 16, 13, 1, (unsigned char*)screenbuf1 );



	SCX_REG = 0xFC ;
	SCY_REG = 0xF8 ;


	currline = 0 ;

	DISPLAY_ON ;

	VBK_REG = 1;		// select palette bank 

	memset(screenbuf1,6,19L) ;
	set_bkg_tiles2( 2,12+currline, 15, 1, (unsigned char*)screenbuf1 );

	VBK_REG = 0;		// select palette bank 


	screenbuf1[0] = 0 ;
	n=0 ;

	while ( 1 )
	{
		joykeys = joypad() ;

		if ( joykeys&J_UP )
		{
			VBK_REG = 1;	  // select palette bank 

			memset(screenbuf1,2,19L) ;
			set_bkg_tiles2( 2,12+currline, 15, 1, (unsigned char*)screenbuf1 );

			if ( currline==0 )
				currline = 3 ;
			else
				currline-- ;

			memset(screenbuf1,6,19L) ;
			set_bkg_tiles2( 2,12+currline, 15, 1, (unsigned char*)screenbuf1 );

			VBK_REG = 0;	  // select palette bank 
			waitpadup(); 


		}
		if ( joykeys&J_DOWN )
		{
			VBK_REG = 1;	  // select palette bank 

			memset(screenbuf1,2,19L) ;
			set_bkg_tiles2( 2,12+currline, 15, 1, (unsigned char*)screenbuf1 );

			if ( currline==3 )
				currline = 0 ;
			else
				currline++ ;

			memset(screenbuf1,6,19L) ;
			set_bkg_tiles2( 2,12+currline, 15, 1, (unsigned char*)screenbuf1 );

			VBK_REG = 0;	  // select palette bank 
			waitpadup(); 


		}

		if ( joypad()&J_A )
		{
			if ( (currline==2) && (!(partyexists())) )
			{
				waitpadup() ;
				displaymessage(2,12,15,1,errorpartymap) ;

			}
			else
				break ;
		}

		wait_vbl_done() ;
	}

	waitpadup() ;

	return currline ;    

}

void rostermenu()
{
	UBYTE currline, n, joykeys ;

	currline = 0 ;
	while ( currline!=5 )
	{
		VBK_REG = 1;		// select palette bank 

		memset(screenbuf1,2,19L) ;
		for ( n = 10 ; n<16 ; n++ )
			set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

		VBK_REG = 0;		// select palette bank 


		memset(screenbuf1,0x5DU,32L) ;
		for ( n = 10 ; n<16 ; n++ )
			set_bkg_tiles2( 0, n, 19, 1, (unsigned char*)screenbuf1 );

		set_bkg_tiles2( 1, 10, 16, 1, text6 );

		set_bkg_tiles2( 1, 11, 16, 1, text7 );

		set_bkg_tiles2( 4, 12, 10, 1, text8 );

		set_bkg_tiles2( 2, 13, 14, 1, text9 );

		set_bkg_tiles2( 0, 14, 19, 1, text10 );

		set_bkg_tiles2( 5, 15, 9, 1, text11 );

		currline = 0 ;

		DISPLAY_ON ;

		VBK_REG = 1;		// select palette bank 

		memset(screenbuf1,6,19L) ;
		set_bkg_tiles2( 0,10+currline, 19, 1, (unsigned char*)screenbuf1 );

		VBK_REG = 0;		// select palette bank 


		screenbuf1[0] = 0 ;
		n=0 ;

		while ( 1 )
		{
			joykeys = joypad() ;

			if ( joykeys&J_UP )
			{
				VBK_REG = 1;	   // select palette bank 

				memset(screenbuf1,2,19L) ;
				set_bkg_tiles2( 0,10+currline, 19, 1, (unsigned char*)screenbuf1 );

				if ( currline==0 )
					currline = 5 ;
				else
					currline-- ;

				memset(screenbuf1,6,19L) ;
				set_bkg_tiles2( 0,10+currline, 19, 1, (unsigned char*)screenbuf1 );

				VBK_REG = 0;	   // select palette bank 
				waitpadup(); 


			}
			if ( joykeys&J_DOWN )
			{
				VBK_REG = 1;	   // select palette bank 

				memset(screenbuf1,2,19L) ;
				set_bkg_tiles2( 0,10+currline, 19, 1, (unsigned char*)screenbuf1 );

				if ( currline==5 )
					currline = 0 ;
				else
					currline++ ;

				memset(screenbuf1,6,19L) ;
				set_bkg_tiles2( 0,10+currline, 19, 1, (unsigned char*)screenbuf1 );

				VBK_REG = 0;	   // select palette bank 
				waitpadup(); 


			}

			if ( joypad()&J_A )
				break ;

			wait_vbl_done() ;
		}


		waitpadup() ;

		if ( currline==0 )
			examineregister() ;
		else
			if ( currline==1 )
			createcharacter() ;
		else
			if ( currline==2 )
			formparty() ;
		else
			if ( currline==3 )
			disperseparty() ;
		else
			if ( currline==4 )
			terminatecharacter() ;
	}   
}

//denials
//if in party, cannot delete
//if party formed, cannot form again
