#include <gb.h>
#include <stdlib.h>
#include <rand.h>
#include "u3.h"

#define MAXCLOCK 3
#define MAXWIND 7500L
#define MAXWHIRL 1200L
#define WHIRLPMOVE 60L
#define WINDPMOVE 375L
#define JOYPADDELAY 20
#define SCROLLDELAY 20

/* ************************************************************ */

//ROM Bank 1
#define sosaria_tilemap  ((unsigned char*)(0x4000))

//ROM Bank 2
#define u3tiles ((unsigned char*)(0x4000))
#define tile_palettes ((unsigned char*)(0x4930))
#define check_order ((unsigned char*)(0x49F0))
#define bkg_p ((UWORD*)(0x4A40))
#define obj_p ((UWORD*)(0x4A80))
//#define battlemaps ((UWORD*)(0x4AC0))
#define dungtiles ((unsigned char*)(0x4F01))
#define dungdoors ((unsigned char*)(0x5471))
#define borderdat ((unsigned char*)(0x5731))

#define tile_attribs  ((unsigned char*)(0xB990))

#define u3tiles2 ((unsigned char*)(0xB000))

UBYTE hitship ;

unsigned char modpaltitle[20] ;


unsigned char alldeaddat[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D, 
} ;

unsigned char canceldat4[] = {
	'C'+0x1D,'A'+0x1D,'N'+0x1D,'C'+0x1D,'E'+0x1D,'L'+0x1D,'L'+0x1D,'E'+0x1D,'D'+0x1D,0x5d,0x5d,0x5d
} ;
unsigned char whirl1[] = {
	'A'+0x1D,0x5D,'H'+0x1D,'U'+0x1D,'G'+0x1D,'E'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'W'+0x1D,'I'+0x1D,'R'+0x1D,'L'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	0x89U,'W'+0x1D,'H'+0x1D,'I'+0x1D,'R'+0x1D,'L'+0x1D,'P'+0x1D,'O'+0x1D,'O'+0x1D,'L'+0x1D,0x89U,0x5D, 
	'E'+0x1D,'N'+0x1D,'G'+0x1D,'U'+0x1D,'L'+0x1D,'F'+0x1D,'S'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D, 
	'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'S'+0x1D,'H'+0x1D,'I'+0x1D,'P'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'R'+0x1D,'A'+0x1D,'G'+0x1D,'G'+0x1D,'I'+0x1D,'N'+0x1D,'G'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'B'+0x1D,'O'+0x1D,'T'+0x1D,'H'+0x1D,0x5D,'T'+0x1D,'O'+0x1D,0x5D,'A'+0x1D,0x5D,0x5D,0x5D, 
	'W'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,'Y'+0x1D,0x5D,'G'+0x1D,'R'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D, 
} ;

unsigned char whirl2[] = {
	'A'+0x1D,'S'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'W'+0x1D,'A'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D, 
	'E'+0x1D,'N'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D,'S'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,'R'+0x1D,0x5D, 
	'L'+0x1D,'U'+0x1D,'N'+0x1D,'G'+0x1D,'S'+0x1D,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,0x5D,0x5D, 
	'P'+0x1D,'A'+0x1D,'S'+0x1D,'S'+0x1D,0x5D,'I'+0x1D,'N'+0x1D,'T'+0x1D,'O'+0x1D,0x5D,0x5D,0x5D, 
	'D'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,'N'+0x1D,'E'+0x1D,'S'+0x1D,'S'+0x1D,0x82,0x5D,0x5D,0x5D, 
	'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'A'+0x1D,'W'+0x1D,'A'+0x1D,'K'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,0x5D, 
	'O'+0x1D,'N'+0x1D,0x5D,'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'S'+0x1D,'H'+0x1D,'O'+0x1D,'R'+0x1D,'E'+0x1D, 
	'O'+0x1D,'F'+0x1D,0x5D,'A'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D, 
	'F'+0x1D,'O'+0x1D,'R'+0x1D,'G'+0x1D,'O'+0x1D,'T'+0x1D,'T'+0x1D,'E'+0x1D,'N'+0x1D,0x5D,0x5D,0x5D, 
	'L'+0x1D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x84,0x5D,'Y'+0x1D,'O'+0x1D,'U'+0x1D,'R'+0x1D,0x5D,0x5D, 
	'S'+0x1D,'H'+0x1D,'I'+0x1D,'P'+0x1D,0x5D,'A'+0x1D,'N'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D,0x5D, 
	'C'+0x1D,'R'+0x1D,'E'+0x1D,'W'+0x1D,0x5D,'L'+0x1D,'O'+0x1D,'S'+0x1D,'T'+0x1D,0x5D,'T'+0x1D,'O'+0x1D, 
	'T'+0x1D,'H'+0x1D,'E'+0x1D,0x5D,'S'+0x1D,'E'+0x1D,'A'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D, 
} ;

unsigned char whirl3[] = {
	'A'+0x1D,'L'+0x1D,'L'+0x1D,0x5D,'I'+0x1D,'S'+0x1D,0x5D,'D'+0x1D,'A'+0x1D,'R'+0x1D,'K'+0x1D,0x82, 
	'Y'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'M'+0x1D,'A'+0x1D,'D'+0x1D,'E'+0x1D,0x5D,'I'+0x1D,'T'+0x1D,0x82, 
} ;

unsigned char turnrightdat[] = {
//0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,0x97
	'T'+0x1D,'U'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,'R'+0x1D,'I'+0x1D,'G'+0x1D,'H'+0x1D,'T'+0x1D,0x5D,0x5D
} ;
unsigned char turnleftdat[] = {
	'T'+0x1D,'U'+0x1D,'R'+0x1D,'N'+0x1D,0x5D,'L'+0x1D,'E'+0x1D,'F'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D
} ;

unsigned char moveforwarddat[] = {
	'M'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'F'+0x1D,'O'+0x1D,'R'+0x1D,'W'+0x1D,'A'+0x1D,'R'+0x1D,'D'+0x1D
} ;

unsigned char movebackdat[] = {
	'M'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D,0x5D,'B'+0x1D,'A'+0x1D,'C'+0x1D,'K'+0x1D,0x5D,0x5D,0x5D
} ;

unsigned char noladderdat[] = {
	'N'+0x1D,'O'+0x1D,0x5D,'L'+0x1D,'A'+0x1D,'D'+0x1D,'D'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,0x5D,0x5D
} ;

unsigned char invalidmovedat2[] = {
	'I'+0x1D,'N'+0x1D,'V'+0x1D,'A'+0x1D,'L'+0x1D,'I'+0x1D,'D'+0x1D,0x5D,'M'+0x1D,'O'+0x1D,'V'+0x1D,'E'+0x1D
};

unsigned char menubanksdat[] = {
	9, //attack
	9, //board
	9, //cast
	9, //enter
	9, //fire
	9, //get
	15,	 //hand
	15,	 //join gold
	5,	//look
	15,	//modify order
	15,	//negate time
	16,	//other
	9, //peer
	15,	//quit/save
	15,	//ready
	15,	//steal
	20,	//transact
	15,	//unlock
	15,	//volume
	15,	//wear
	9, //xit
	16,	//yell
	16	//zstats
};

unsigned char dungbanksdat[] = {
	19,	//cast
	18,	//descend
	9, //get
	15,	 //hand
	19,	//ignite
	15,	 //join gold
	18,	//klimb
	15,	//modify order
	15,	//negate time
	16,	//other
	19,	//peer
	15,	//ready
	15,	//volume
	15,	//wear
	16,	//yell
	16	//zstats
};

UBYTE stat_int ;

UBYTE generatorx, generatory, ingenerator, generatortile ;

UBYTE didfreezesfx ;

UBYTE filled_delay ;

UBYTE cheat_xray ;
UBYTE cheat_nofight ;
UBYTE cheat_nohurt ;
UBYTE cheat_noblock ;
UBYTE cheat_fullmp ;
UBYTE cheat_noclass ;

UBYTE frozennum ;

UBYTE omnieye  ;

UBYTE changemusic ;
UBYTE musicbank ;
UBYTE musicnum ;
UBYTE musicctr ;

UBYTE curr_sfx ;
UBYTE change_sfx ;

UBYTE musicvars[] = {
	22,0, //u3wander
	22,1, //u3rulebrit
	22,7, //alive  ??? shrine, fountain, mark, timelord
	22,3, //castle
	22,5, //combat
	22,6, //dungeon
	22,8, //shopping
	22,9, //towne
	22,2, //victory  ??? - ambrosia
	22,4,  //castfire
	22,2, //ambrosia u3

	22,15, //u4wander
	22,12, //u4fanfare
	22,14, //u4shrine
	22,10, //u4castle
	22,11, //u4combat
	22,13, //u4shopping
	27,1,  //victory
	22,16, //altbritish
	23,0,  //balron1
	23,1,  //balron2
	23,2,  //balron3
	23,3,  //balron4
	23,4,  //balron5
	23,5,  //balron6
	23,6,  //balron7
	23,7,  //newtown1
	23,8,  //newtown2
	24,0,  //newtown3
	24,1,  //newtown4
	24,2,  //newtown5
	27,0,  //legacy
	27,1,  //victory
	24,3,  //legacy_sfx
	27,2,  //deadsong
};


unsigned char *musicdat_start ;
unsigned char *datasong_ptr ;
UBYTE volume_on ;


unsigned char varlist[120] ;

UBYTE playerscreentile ;

UBYTE whirldirectx ;
UBYTE whirldirecty ;

UBYTE baddemeanor ;
UBYTE dunglevel ;
UBYTE dungx ;
UBYTE dungy ;
UBYTE dungdir ;
UBYTE dungnumber ;
UBYTE dungrefresh ;
UBYTE torchtime ;
extern unsigned char currdungtile ;
extern UBYTE numalive ;

UWORD windctr ;
UBYTE winddir ;
UWORD whirlctr ;

UBYTE die_exodus ;

UBYTE inexodus ;
UBYTE fasterflip ;

UBYTE peer_semaphore ;
UBYTE peermap ;

UBYTE dir ;

UBYTE stoptime ;
extern UBYTE stoptimebattle ;

UBYTE isnewgame ;
UBYTE extragame ;

UBYTE screenx, screeny;
UBYTE playerx, playery;
UBYTE mademove  ;
unsigned char screenbuf3[32] ;

UBYTE whichvbl ;
UBYTE currROM ;
UBYTE currRAM ;

UWORD party_specials ;
//otheralways=score
//yellalways=curse
//0001 = INSERT
//0002 = BRIBE
//0004 = DIG
//0008 = PRAY
//0010 = SEARCH
//0100 = EVOCARE (yell)

UBYTE transport ; //0=walking, 1=ship, 2=horse

UBYTE mode4tiles ;
UBYTE mode8tiles ;
UBYTE need_refresh ;
UBYTE joykeys, lastkey ;
UBYTE joywait ;

UBYTE moon1, moon2 ;
UBYTE moonchanges ;

UBYTE moves ;

UBYTE leaving ;

struct VALIDMOVES
{
	UBYTE north : 1 ;
	UBYTE south : 1 ;
	UBYTE east  : 1 ;
	UBYTE west  : 1 ;
	UBYTE unused: 4 ;
} validmoves ;

UBYTE delayscroll ;

unsigned char *ctr ;


PLAYER players[5] ;
MONSTER monsters[32] ;
UBYTE nummonsters ;
UBYTE numplayers ;
UBYTE inside ;


extern UBYTE numgoodies ;
extern UBYTE numbaddies ;

extern unsigned char mainmenudat[] ;
extern unsigned char dungmenudat[] ;

/* Seed for the random number generator */
fixed seed;


void disable_interrupts2()
{
	stat_int = 0 ;
	disable_interrupts() ;
}

void enable_interrupts2()
{
	stat_int = 1 ;
	enable_interrupts() ;
}

void set_bkg_data2( UBYTE x, UBYTE y, unsigned char *vv )
{
	disable_interrupts();
	set_bkg_data( x, y, vv ) ;

	if ( stat_int != 0 )
		enable_interrupts() ;

}

void set_bkg_tiles2( UBYTE x, UBYTE y, UBYTE x2, UBYTE y2, unsigned char *vv )
{
	disable_interrupts();
	set_bkg_tiles( x, y, x2, y2, vv ) ;

	if ( stat_int != 0 )
		enable_interrupts() ;

}

void get_bkg_tiles2( UBYTE x, UBYTE y, UBYTE x2, UBYTE y2, unsigned char *vv )
{
	disable_interrupts();
	get_bkg_tiles( x, y, x2, y2, vv ) ;

	if ( stat_int != 0 )
		enable_interrupts() ;

}

void set_data2( unsigned char *vv, unsigned char* vv2, UWORD wrd )
{
	disable_interrupts();
	set_data( vv, vv2, wrd ) ;

	if ( stat_int != 0 )
		enable_interrupts() ;

}

void remotecall( UBYTE callingBank, UBYTE procBank, void (*thefunc)(void) )
{
	currROM = procBank ;
	SWITCH_ROM_MBC5( (UWORD)procBank ) ;

	thefunc() ;

	currROM = callingBank ;
	SWITCH_ROM_MBC5( (UWORD)callingBank ) ;

}

unsigned char passdat2[] = 
{
	'P'+0x1D,'A'+0x1D,'S'+0x1D,'S'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D,0x5D
};


void writegamemessage(unsigned char *msgdat)
{
	UBYTE q ;

	disable_interrupts2() ;

	for ( q=0 ; q < 4 ; q++ )
	{
		set_data2((unsigned char*)0x9800+(32L*(q+13)),(unsigned char*)0x9800+(32L*(q+14)),12L) ;
		set_data2((unsigned char*)0x9C00+(32L*(q+13)),(unsigned char*)0x9C00+(32L*(q+14)),12L) ;
	}

	set_data2((unsigned char*)0x9800+(32L*17),msgdat,12L) ;
	set_data2((unsigned char*)0x9C00+(32L*17),msgdat,12L) ;

	enable_interrupts2() ;

}


UBYTE make_rnd( UBYTE i )
{
	UBYTE therand ;
	if ( i==0 )
		return rand() ;
	else
		while ( (therand=rand()) >= i )
			;
	return( therand );
}



void magicsfx1(UBYTE lenvar)
{
	UBYTE r, freqLOW, freqHI ;
	UWORD bigfreq ;

	disable_interrupts2() ;
	NR12_REG = 0xF0U ; 
	NR11_REG = 0x80U ;
	NR10_REG = 0x00U ;
	NR51_REG = 0x11U;

	for ( r=0 ; r != lenvar ; r++ )
	{
		bigfreq = ((( (UWORD)(make_rnd(128U)+85) ) * 31L) / 4L ) ;
		freqLOW = (UBYTE)(bigfreq & 0x00FFL) ;
		freqHI = (UBYTE)((bigfreq & 0x0700) >> 8) ;


		NR13_REG = freqLOW;						  // 8bits of data
		NR14_REG = 0x80U | freqHI;			  // 3bits of data

		delay(25) ;

	}
	NR51_REG = 0x00 ; 
	enable_interrupts2() ;

}

void magicsfx2(UBYTE freqvar, UBYTE lenvar, UBYTE freqvar2)
{
	UBYTE r, t,freqLOW, freqHI ;
	UWORD bigfreq ;

	disable_interrupts2() ;
	NR12_REG = 0xF0U ; 
	NR11_REG = 0x80U ;
	NR10_REG = 0x00U ;
	NR51_REG = 0x11U;

	for ( t=0 ; t != lenvar ; t++ )
	{
		for ( r=0 ; r != 20 ; r++ )
		{

			bigfreq = 2036L + (((UWORD)freqvar));
			freqLOW = bigfreq & 0x00FF ;
			freqHI = (bigfreq & 0x0700) >> 8 ;

			NR13_REG = freqLOW;						  // 8bits of data
			NR14_REG = 0x80U | freqHI;			  // 3bits of data

			delay(2) ;
			bigfreq = 884L + (((UWORD)freqvar2));
			freqLOW = bigfreq & 0x00FF ;
			freqHI = (bigfreq & 0x0700) >> 8 ;

			NR13_REG = freqLOW;						  // 8bits of data
			NR14_REG = 0x80U | freqHI;			  // 3bits of data
			delay(2) ;
		}

	}
	NR51_REG = 0x00 ; 
	enable_interrupts2() ;

}


void attackswingsfx(UBYTE lenvar)
{

	disable_interrupts2() ;
	NR10_REG = 0x2FU ;
	NR11_REG = 0x9FU ;
	NR12_REG = 0xF0U ;
	NR13_REG = 0x1FU ;
	NR14_REG = 0xBFU ;
	NR51_REG = 0x11U ;
	delay(lenvar) ;
	NR51_REG = 0x00U ; 
	enable_interrupts2() ;
}

void attackmisssfx(UBYTE lenvar)
{

	disable_interrupts2() ;
	NR10_REG = 0x27U ;
	NR11_REG = 0x9FU ;
	NR12_REG = 0xF0U ;
	NR13_REG = 0x1FU ;
	NR14_REG = 0xBFU ;
	NR51_REG = 0x11U ;
	delay(lenvar) ;
	NR51_REG = 0x00U ; 
	enable_interrupts2() ;
}

void whirlpoolsfx(UBYTE lenvar)
{

	disable_interrupts2() ;
	NR10_REG = 0x7FU ;
	NR11_REG = 0x80U ;
	NR12_REG = 0xF7U ;
	NR13_REG = 0x32U ;
	NR14_REG = 0xBFU ;
	NR51_REG = 0x11U ;
	delay(((UWORD)lenvar)*5L) ;
	NR51_REG = 0x00U ; 
	enable_interrupts2() ;
}

void playerhitsfx(UBYTE lenvar)
{
	NR41_REG = 0x0CU ;
	NR42_REG = 0xF0U ;
	NR43_REG = 0x45U ;
	NR44_REG = 0x80U ;
	NR51_REG |= 0x88U ;
	delay(lenvar) ;
	NR51_REG &= 0x77U ; 
}

void firecannonsfx(UBYTE lenvar)
{

	disable_interrupts2() ;
	NR10_REG = 0x2DU ;
	NR11_REG = 0x80U ;
	NR12_REG = 0xF0U ;
	NR13_REG = 0x42U ;
	NR14_REG = 0xBFU ;
	NR51_REG = 0x11U ;
	delay(lenvar);
	NR51_REG = 0x00U ; 
	enable_interrupts2() ;
	/*
	NR41_REG = 0x0CU ;
	NR42_REG = 0xF7U ;
	NR43_REG = 0x7CU ;
	NR44_REG = 0x80U ;
	NR51_REG |= 0x88U ;
	delay(lenvar) ;
	NR51_REG &= 0x77U ; 
	*/
}

void movesfx(UBYTE lenvar, UBYTE lenvar2, UBYTE gallop)
{
	NR41_REG = 0x3BU ;
	NR42_REG = 0xF0U ;
	NR43_REG = 0x5FU ;
	NR44_REG = 0x80U ;
	NR51_REG |= 0x88U ;
	delay(lenvar) ;
	NR51_REG &= 0x77U ; 
	delay(lenvar2) ;
	NR51_REG |= 0x88U ;
	delay(lenvar) ;
	NR51_REG &= 0x77U ; 
	if ( gallop!=0 )
	{
		delay(lenvar2) ;
		NR51_REG |= 0x88U ;
		delay(lenvar) ;
		NR51_REG &= 0x77U ; 
	}
}

void forcefieldsfx(UBYTE lenvar)
{
	NR41_REG = 0x00U ;
	NR42_REG = 0xF0U ;
	NR43_REG = 0x3DU ;
	NR44_REG = 0x80U ;
	NR51_REG |= 0x88U ;
	delay(lenvar) ;
	NR51_REG &= 0x77U ; 
}
void invalidmovesfx(UBYTE lenvar)
{
	NR41_REG = 0x34U ;
	NR42_REG = 0xF0U ;
	NR43_REG = 0x59U ;
	NR44_REG = 0x80U ;
	NR51_REG |= 0x88U ;
	delay(80U) ;
	NR43_REG = 0x5AU ;
	delay(80U) ;
	NR51_REG &= 0x77U ; 

}

void loadit() 
{
	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;

	set_bkg_data2(  0x5D, 37, u3tiles+ ( 0x5DUL * 16UL ) );

	currROM = 36 ;
	SWITCH_ROM_MBC5(36UL) ;
}


void loadu3tiles() 
{
	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;

	set_bkg_data2(  0, 0x93U, u3tiles );
	set_sprite_data(  7, 0x07, u3tiles+( 89UL << 4UL ) );
	set_sprite_data(  0, 0x07, u3tiles+( 30UL << 4UL ) );

	currROM = 36 ;
	SWITCH_ROM_MBC5(36UL) ;
}

void init_screen()
{
	UBYTE n, inparty;

	SWITCH_RAM_MBC5(0) ;
	memset(players,0x00,4L*127UL); 

	numplayers = 0 ;


	for ( n=0 ; n<12 ; n++ )
	{
		inparty = *(unsigned char*)(0xA004+((UWORD)n<<7L)+58UL) ;
		if ( inparty )
		{
			memcpy(&(players[inparty-1]),(unsigned char*)(0xA004+((UWORD)n<<7L)),127L) ;
			numplayers++ ;
		}

	}

	for ( n=0 ; n<4 ; n++ )
		if ( players[n].inparty )
			for ( inparty = 0 ; inparty<7 ; inparty++ )
				if ( players[n].name[inparty] != 0x5D )
					players[n].name[inparty] += 33 ;



	if ( isnewgame )
	{
		party_specials = 0L ;
		extragame = 0 ;

		SWITCH_RAM_MBC5(0) ;

		currROM = 1 ;
		SWITCH_ROM_MBC5( 1UL) ;
		memcpy((unsigned char*)0xA604,(unsigned char*)0x4000,4096UL) ;

		*(unsigned char*)(0xB608) = 44 ;
		*(unsigned char*)(0xB609) = 20 ;
		*(unsigned char*)(0xB60A) = 39 ; 
		*(unsigned char*)(0xB60B) = 15 ; 
		*(unsigned char*)(0xB60C) = 0 ; 
		*(unsigned char*)(0xB60D) = 0 ; 
		memset(monsters,0,MONSTERSIZE*32L) ;
		monsters[31].x=3 ;
		monsters[31].y=38 ;
		monsters[31].attribs = 0x12 ;
		monsters[31].tile = 0x0F ; //0f
		memcpy((unsigned char*)0xB60E,monsters,MONSTERSIZE*32L) ;

		*(UWORD*)(0xB700) = 0L ;  //party_special ;
		*(UBYTE*)(0xB702) = 0L ;  //extragame ;

		n=0 ;
		for ( ctr=(unsigned char*)0xA000 ; ctr < (unsigned char*)0xBFFF ; ctr++ )
			n += *ctr ;
		memcpy((unsigned char*)(0xBFFF),&n,1L) ;

	}

	currROM = 15 ;
	SWITCH_ROM_MBC5(15UL) ;
	loadgame() ;

	currROM = extragame ? 25 : 1 ;
	SWITCH_ROM_MBC5( extragame ? 25UL : 1UL) ;
	SWITCH_RAM_MBC5(3) ;

	memcpy((unsigned char*)0xA000,(unsigned char*)0x4000,4096UL) ;
	//copy sosaria map into RAM3

	SWITCH_RAM_MBC5(1) ;


	*((unsigned char*)(0xA008+(8L<<6))) = 0x32 ;  //moongate

	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;

	memcpy((unsigned char*)0xB000,(unsigned char*)0x4000,4096UL) ;
	//copy tile/palette information into RAM1

	currROM = 28 ;
	SWITCH_ROM_MBC5(28UL) ;

	draw_border() ;

	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;

	set_bkg_data2(  0, 0x93U, u3tiles );
	set_bkg_data2(  0xD4, 0x27U, dungtiles );

	peermap = 99 ;

	if ( transport==0 )
		playerscreentile = 0x5C;
	else
		if ( transport==1 )
		playerscreentile = 0x0E;
	else
		playerscreentile = 0x0D; 

	set_sprite_prop( 5, 0x01 );
	set_sprite_tile( 0, 0x59U );
	set_sprite_prop( 0, 0x00 );
	set_sprite_tile( 1, 0x5AU );
	set_sprite_prop( 1, 0x00 );

	currROM = 5 ;
	SWITCH_ROM_MBC5(5L) ;
	for ( n=0 ; n < 4 ; n++ )
		if ( players[n].inparty )
			charscreen(&(players[n]),n) ;
	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;
	set_bkg_data2(  0x94, 0x40U, borderdat);
}


void initialize_memory()
{
	UBYTE n ;

	SWITCH_RAM_MBC5(1) ;
	memset((unsigned char*)(0xA000),0,0x2000) ;
	SWITCH_RAM_MBC5(2) ;
	memset((unsigned char*)(0xA000),0,0x2000) ;
	SWITCH_RAM_MBC5(3) ;
	memset((unsigned char*)(0xA000),0,0x2000) ;
	SWITCH_RAM_MBC5(0) ;
	memset((unsigned char*)(0xA000),0,0x2000) ;
	memcpy((unsigned char*)(0xA000),"U3GB",4L) ;
	n = 'U' + '3' + 'G' + 'B' ;
	memcpy((unsigned char*)(0xBFFF),&n,1L) ;


}

void update_screen_main()
{

	if ( delayscroll-- == 0 )
	{
		if ( ++mode4tiles==4 )
			mode4tiles=0 ;
		if ( ++mode8tiles==8 )
			mode8tiles=0 ;

		disable_interrupts2() ;

		set_bkg_data2(  0x00, 0x01, u3tiles2+(UWORD)((UWORD)mode4tiles<<4) );
		set_bkg_data2(  0x0F, 0x01, u3tiles2+(UWORD)(((UWORD)(mode4tiles)+0x0FL)<<4) );
		set_bkg_data2(  0x26, 0x01, u3tiles2+(UWORD)(((UWORD)(mode4tiles)+0x26L)<<4) );
		set_bkg_data2(  0x2A, 0x01, u3tiles2+(UWORD)(((UWORD)(mode8tiles)+0x2AL)<<4) );
		set_bkg_data2(  0x32, 0x01, u3tiles2+(UWORD)(((UWORD)(mode8tiles)+0x32L)<<4) );

		enable_interrupts2() ;

		delayscroll = SCROLLDELAY ;
	}
}

void dovolume()
{
	volume_on = !volume_on ;
	if ( volume_on==0 )
		NR51_REG=0x00 ;

}
void tint()
{

//	disable_interrupts2() ;
	if ( changemusic!=0 )
	{
		musicbank = musicvars[(changemusic-1)<<1] ;
		musicnum = musicvars[((changemusic-1)<<1)+1] ;
		SWITCH_ROM_MBC5((UWORD)musicbank) ;
		stopmusic() ;
		init_music() ;
		stopmusic() ;
		SWITCH_ROM_MBC5((UWORD)currROM) ;
		changemusic = 0 ;


	}
	if ( volume_on==1 )
	{
		SWITCH_ROM_MBC5((UWORD)musicbank) ;
		music() ;
		SWITCH_ROM_MBC5((UWORD)currROM) ;

	}


//	enable_interrupts2() ;

}

void myVBL()
{

//	disable_interrupts2() ;

	if ( (inside==0)||(inside==1) )
	{
		update_screen_main() ;
		/*
		if (need_refresh!=0)
		{
			SWITCH_ROM_MBC5(5L) ;
			SWITCH_RAM_MBC5(1) ;
			update_screen() ;
			SWITCH_ROM_MBC5((UWORD)currROM) ;
			need_refresh =0 ;
		}*/
	}

//	tint() ;        

	if ( peer_semaphore!=0 )
	{
		disable_interrupts2() ;
		if ( peer_semaphore==1 )
		{
			currROM = 14 ;
			SWITCH_ROM_MBC5(14L) ;
			if ( peermap==99 )
				set_bkg_data2(  0x94, 0x40U, (unsigned char*)0x4000);
			else
				set_bkg_data2(  0x94, 0x40U, (unsigned char*)0x4400+(((UWORD)peermap)<<10));
			currROM = 9 ;
			SWITCH_ROM_MBC5(9L) ;
			//formatnumber6((UWORD)oldbank,4) ;
			//writegamemessage(screenbuf3) ;
//			SWITCH_ROM_MBC5((UWORD)oldbank) ;
		}
		else
			if ( peer_semaphore==2 )
		{
			currROM = 2 ;
			SWITCH_ROM_MBC5(2L) ;

			set_bkg_data2(  0x94, 0x40U, borderdat);
			currROM = 9 ;
			SWITCH_ROM_MBC5(9L) ;
			//formatnumber6((UWORD)oldbank,4) ;
			//writegamemessage(screenbuf3) ;
//				SWITCH_ROM_MBC5((UWORD)oldbank) ;
		}
		peer_semaphore = 0 ;
		enable_interrupts2() ;
	}
//	enable_interrupts2() ;
}


UBYTE validmove(UBYTE dir)
{
	UBYTE backupROM ;
	UBYTE vretval ;

	backupROM = currROM ;

	currROM = 28 ;
	SWITCH_ROM_MBC5(28L) ;

	vretval = validmove28( dir ) ;

	currROM = backupROM ;
	SWITCH_ROM_MBC5( (UWORD)currROM ) ;

	return vretval ;


}

void changebank(UBYTE thebank)
{
	if ( inside==2 )
	{
		currROM = thebank ;
		SWITCH_ROM_MBC5((UWORD)thebank) ;
	}
	else
	{
		disable_interrupts2() ;
		currROM = thebank ;
		SWITCH_ROM_MBC5((UWORD)thebank) ;
		whichvbl = thebank ;
		enable_interrupts2() ;
	}

} 

void combat(UBYTE n, UBYTE thetile)
{
	UBYTE p, q,done, action,cmd,done2 ;


	inside |= 0x20 ;
	changemusic = extragame ? 16 : 5 ;
	disable_interrupts2() ;
	//move_sprite( 5, 0,0 );
	currROM = 5 ;
	SWITCH_ROM_MBC5(5UL) ;
	initcombatscreen(n, thetile) ;
	currROM = 6 ;
	SWITCH_ROM_MBC5(6UL) ;
	if ( inside!=2 )
		whichvbl = 6 ;
	enable_interrupts2() ;

	waitpad(J_A) ;

	if ( cheat_nofight )
		done = 1 ;
	else
		done = 0 ;

	while ( !done )
	{
		for ( p = 0 ; p<numgoodies ; p++ )
		{
			if ( numbaddies==0 )
			{
				done=1 ;
				break ;
			}
			done2 = 0 ;
			changebank(7) ;
			while ( action=(playerturn(p)) )
			{
				cmd=battlemainmenu();
				switch ( cmd )
				{
					case 0 : 
						{
							changebank(6) ;
							done2=doattack(p) ; 
							changebank(7) ;
							break ;	 //attack

						}
					case 1 : 
						{
							changebank(6) ;
							done2=castspell(p,n) ;
							changebank(7) ;
							break ;	 //cast
						}

					case 2 : done2=powderbattle(p) ; break ;  //powder
					case 3 : done2=doready(p) ; break ;	 //ready
					case 4 : dostats(p) ; break ;  //stats
					case 5 : dovolume(); break ;  //volume
					default : break ;



				}

				changebank(6) ;
				for ( q=0 ; q<4;q++ )
					charscreen2(&players[q],q) ;
				changebank(7) ;
				if ( done2 )
					break ;
			}
		}

		changebank(5) ;
		postmove() ;
		if ( inexodus )
			stoptimebattle=0 ;

		if ( stoptimebattle )
			stoptimebattle-- ;
		else
		{
			changebank(8) ;
			for ( p=0 ; p<numbaddies ; p++ )
			{
				done = monsterturn(p) ;
				if ( numalive==0 )
				{
					writegamemessage(alldeaddat) ;
					while ( 1 )	; 

				}
				if ( done )
					break ;
			}
			changebank(6) ;
		}
	}

	inside &= 0xDF ;

	changebank(8) ;
	if ( done==1 )	//victory
	{
		//remove monster,
		//place treasure chest where monster was
		dovictory(n) ;


	}
	else  //all players dead
	{
		doalldead() ;
		//everyone dead - sent to castle british and revive


	}   


	changebank(5) ;

	//move_sprite( 5, 56,64 );


	if ( cheat_nofight )
    {
        waitpadup() ;
    }

}


void restoresosaria() 
{
	UBYTE p ;
	unsigned char cpybuf[64] ;

	didfreezesfx = 0 ;

	if ( die_exodus == 0x0F )
	{
		volume_on = 1 ;
		dovolume() ;
		currROM = 28 ;
		SWITCH_ROM_MBC5(28L) ;
		newgame_expo() ;
		disable_interrupts2() ;

		currROM = 25 ;
		SWITCH_ROM_MBC5(25L) ;

		SWITCH_RAM_MBC5(1) ;
		memcpy((unsigned char*)(0xA000), (unsigned char*)(0x4000), 4096L) ;
		SWITCH_RAM_MBC5(3) ;
		memcpy((unsigned char*)(0xA000), (unsigned char*)(0x4000), 4096L) ;
		SWITCH_RAM_MBC5(2) ;
		memcpy((unsigned char*)(0xA000), (unsigned char*)(0x4000), 4096L) ;

// RAM0 = players dat 0xA000, stored map of sosaria 0xA604, 
// RAM1 = dynamic map of sosaria 0xA000, 
// RAM2 = stored map of dymanic sosaria when entering new place
// RAM3 = static map of sosaria

		currROM = 28 ;
		SWITCH_ROM_MBC5(28L) ;
		init_extra_game() ;

		currROM = 5 ;
		SWITCH_ROM_MBC5(5L) ;
		SWITCH_RAM_MBC5(1) ;
		refresh_moongate() ;
		if ( (moon1==0)&&(moon2==0) )
			*((unsigned char*)0xA000+(53L*64L)+37L) = 0x09 ;
		else
			*((unsigned char*)0xA000+(53L*64L)+37L)	= 0x06 ;

		enable_interrupts2() ;
		return ;

	}

	changemusic = extragame ? 12 : 1 ;
	inexodus = 0 ;
	ingenerator = 0 ;
	die_exodus = 0 ;
	disable_interrupts2() ;
	for ( p=0 ; p<64 ; p++ )
	{
		SWITCH_RAM_MBC5(2) ;
		memcpy(cpybuf,(unsigned char*)(0xA000+(((UWORD)p)<<6)),64L) ;
		SWITCH_RAM_MBC5(1) ;
		memcpy((unsigned char*)(0xA000+(((UWORD)p)<<6)),cpybuf,64L) ;
	}

	SWITCH_RAM_MBC5(2) ;
	playerx = *(unsigned char*)(0xB000) ;
	playery = *(unsigned char*)(0xB001) ;
	nummonsters = *(unsigned char*)(0xB002) ;
	screenx = *(unsigned char*)(0xB003) ;
	screeny = *(unsigned char*)(0xB004) ;

	memcpy(monsters,(unsigned char*)(0xB005),MONSTERSIZE*32L) ;
	currROM = extragame ? 25 : 1 ;
	SWITCH_ROM_MBC5(extragame ? 25UL : 1UL) ;
	SWITCH_RAM_MBC5(3) ;
	memcpy((unsigned char*)0xA000,(unsigned char*)0x4000,4096L) ;
	inside = 0 ;
	//SWITCH_ROM_MBC5(14L) ;
	//set_bkg_data2(  0x94, 0x40U, (unsigned char*)0x4000);

	peermap = 99 ;


	currROM = 5 ;
	SWITCH_ROM_MBC5(5L) ;
	SWITCH_RAM_MBC5(1) ;
	refresh_moongate() ;
	if ( (moon1==0)&&(moon2==0) )
		*((unsigned char*)0xA000+(53L*64L)+37L) = 0x09 ;
	else
		*((unsigned char*)0xA000+(53L*64L)+37L)	= 0x06 ;

	enable_interrupts2() ;

}

void backupsosaria()
{
	UBYTE p ;
	unsigned char cpybuf[64] ;


	for ( p=0 ; p<64 ; p++ )
	{
		SWITCH_RAM_MBC5(1) ;
		memcpy(cpybuf,(unsigned char*)(0xA000+(((UWORD)p)<<6)),64L) ;
		SWITCH_RAM_MBC5(2) ;
		memcpy((unsigned char*)(0xA000+(((UWORD)p)<<6)),cpybuf,64L) ;
	}

	*(unsigned char*)(0xB000) = (unsigned char)playerx ;
	*(unsigned char*)(0xB001) = (unsigned char)playery ;
	*(unsigned char*)(0xB002) = (unsigned char)nummonsters ;
	*(unsigned char*)(0xB003) = (unsigned char)screenx ;
	*(unsigned char*)(0xB004) = (unsigned char)screeny ;

	memcpy((unsigned char*)(0xB005),monsters,MONSTERSIZE*32L) ;



}

unsigned char dungheader[] = {
	'L'+0x1D,'E'+0x1D,'V'+0x1D,'E'+0x1D,'L'+0x1D,0x8A,0x78
};
unsigned char dungendheader[] = {
	0x95,0x95,0x5d,0x5d,0x5d,0x5d,0x5d,0x95,0x95
};

void writedunglevel()
{
	disable_interrupts2() ;
	screenbuf3[0] = 0x79+dunglevel ;
	set_data2((unsigned char*)0x9809,screenbuf3,1L) ;
	set_data2((unsigned char*)0x9C09,screenbuf3,1L) ;
	enable_interrupts2() ;

}

void dodungeon(UBYTE themap)
{
	UBYTE joykeys,n, actioncmd, monnum, didaction ;

	changemusic = 6 ;
	changebank(6) ;
	for ( n=0 ; n<4;n++ )
		charscreen2(&players[n],n) ;
	changebank(5) ;

	disable_interrupts2() ;

	inside=2 ;
	screenbuf3[0] = 0x9CU ;
	set_bkg_tiles2(4,12,1,1,(unsigned char*)screenbuf3) ;
	screenbuf3[0] = 0x9DU ;
	set_bkg_tiles2(5,12,1,1,(unsigned char*)screenbuf3) ;

	memset(screenbuf3,0x5D,11L) ;
	for ( n=0 ; n!=11 ; n++ )
		set_bkg_tiles2(1,1+n,11,1,screenbuf3) ;

	set_data2((unsigned char*)0x9802,dungheader,7L) ;
	set_data2((unsigned char*)0x9C02,dungheader,7L) ;
	torchtime = 0 ;
    didaction = 0 ;

	//move_sprite(5,0,0) ;


	whichvbl=18 ;
	backupsosaria() ;
//16x16 dungeon map  0x100
//tilemaps =~ 1K   0x400


	currROM = 2 ;
	SWITCH_ROM_MBC5(2L) ;
	SWITCH_RAM_MBC5(1) ;
	memcpy((unsigned char*)0xA800,(unsigned char*)0x5171,0x400UL) ;
	set_bkg_data2(  0x26, 0x2CU, dungdoors );

	currROM = 17 ;
	SWITCH_ROM_MBC5(17L) ;
	//current level = 0xA000
	//level above current = 0xA500 
	//level below current = 0xA600
	memcpy((unsigned char*)0xA000,(unsigned char*)0x4000+(((UWORD)(themap&0x0F))*0x800L),0x800UL) ;
	//memcpy((unsigned char*)0xA600,(unsigned char*)0x4100+(((UWORD)(themap&0x0F))*0x800L),0x100UL) ;

	dunglevel=0 ;
	writedunglevel() ;
	dungx=1 ;
	dungy=1 ;
	dungdir=1 ;
	dungnumber=(themap&0x0F) ;
	dungrefresh = 0 ;

	mademove = 0 ;

	currdungtile = *((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) ;

	currROM = 18 ;
	SWITCH_ROM_MBC5(18L) ;
	enable_interrupts2() ;
	update_screen_dungeon(1) ;
	while ( 1 )
	{
		joykeys = joypad() ;
		if ( joykeys&J_RIGHT )
		{
			if ( isvaliddungmove(1) )
			{
				if ( dungdir==3 )
					dungdir=0 ;
				else
					dungdir++ ;
				writegamemessage(turnrightdat) ;
				update_screen_dungeon(1) ;
				movesfx(15,20,0) ;
				mademove = 1 ;
			}
			else
			{
				writegamemessage(invalidmovedat2) ;
				invalidmovesfx(80) ;
			}
			waitpadup() ;
            didaction = 1 ;
		}
		if ( joykeys&J_LEFT )
		{
			if ( isvaliddungmove(1) )
			{
				if ( dungdir==0 )
					dungdir=3 ;
				else
					dungdir-- ;
				writegamemessage(turnleftdat) ;
				update_screen_dungeon(1) ;
				movesfx(15,20,0) ;
				mademove = 1 ;
			}
			else
			{
				writegamemessage(invalidmovedat2) ;
				invalidmovesfx(80) ;
			}
			waitpadup() ;
            didaction = 1 ;
		}
		if ( joykeys&J_UP )
		{
			if ( isvaliddungmove(2) )
			{
				writegamemessage(moveforwarddat) ;
				update_screen_dungeon(1) ;
				movesfx(15,20,0) ;
				mademove = 1 ;
			}
			else
			{
				writegamemessage(invalidmovedat2) ;
				invalidmovesfx(80) ;
			}
			waitpadup() ;
            didaction = 1 ;

		}
		if ( joykeys&J_DOWN )
		{
			if ( isvaliddungmove(3) )
			{
				writegamemessage(movebackdat) ;
				update_screen_dungeon(1) ;
				movesfx(15,20,0) ;
				mademove = 1 ;
			}
			else
			{
				writegamemessage(invalidmovedat2) ;
				invalidmovesfx(80) ;
			}
			waitpadup() ;
            didaction = 1 ;

		}

		if ( joykeys&J_B )
		{
			writegamemessage(passdat2) ;
			mademove = 1 ;
			waitpadup() ;
            didaction = 1 ;
		}
		if ( joykeys&J_A )
		{
			dungrefresh=1 ;

			currROM = 7 ;
			SWITCH_ROM_MBC5(7L);

			actioncmd=getmenuselection2(16,dungmenudat,0) ;

			mademove = 1 ;
			currROM = dungbanksdat[actioncmd] ;
			SWITCH_ROM_MBC5((UWORD)(dungbanksdat[actioncmd])) ;

			switch ( actioncmd )
			{
				case 0 : mademove = docastspell2(99) ; break ;
				case 1 : 
					{
						if ( (currdungtile==0x20) || (currdungtile==0x30) )
						{
							dunglevel++ ;
							writedunglevel() ;
							currdungtile = *((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) ;
						}
						else
						{
							writegamemessage(noladderdat) ;
							invalidmovesfx(80);
							mademove = 0 ;
						}
						break ;
					}
				case 2 : 
					{
						mademove = dogetchest(0,0,1,*((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx))) ; 
						if ( mademove )
						{
							*((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) = 0x00 ;
						}
						break ;
					}
				case 3 : mademove = dohand() ; break ;
				case 4 : 
					{
						mademove = doignite(99,255U) ; 
						break ;
					}
				case 5 : mademove = dojoin() ; break ; 
				case 6 : 
					{
						if ( (currdungtile==0x10) || (currdungtile==0x30) )
						{
							if ( dunglevel==0 )
							{
								dunglevel=99 ;
								dungrefresh = 0 ;
							}
							else
							{
								dunglevel-- ;
								writedunglevel() ;
								currdungtile = *((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) ;
							}
						}
						else
						{
							writegamemessage(noladderdat) ;
							invalidmovesfx(80);
							mademove = 0 ;
						}
						break ;
					}
				case 7 : mademove = domodify() ; break ;
				case 8 : mademove = donegate() ; break ; 
				case 9 : mademove = doyellother(0) ; break ; //doother
				case 10 : mademove = dopeergem2(0) ; break ; 
				case 11 : mademove = dowearready(0) ; break ;
				case 12 : dovolume() ; break ; //dovolume
				case 13 : mademove = dowearready(1) ; break ;
				case 14 : mademove = doyellother(1) ; break ; //doyell
				case 15 : mademove = doztats() ; break ;
				default : { mademove = 0 ; dungrefresh = 2 ; break ; }


			}
			if ( (mademove==0)&&(actioncmd<16) )
				writegamemessage(canceldat4) ;
			waitpadup() ;
            didaction = 1 ;
			//move_sprite(5,0,0) ;
		}
		if ( mademove )
		{
			mademove = 0 ;
			currROM = 5 ;
			SWITCH_ROM_MBC5(5L) ;
			postmove() ;

			if ( stoptime )
				stoptime-- ;
			else
			{
				currROM = 19 ;
				SWITCH_ROM_MBC5(19L) ;
				if ( monnum=checkdungeonencounter() )
				{
					for ( n=9; n<38 ; n++ )
						move_sprite(n,0,0) ;
					currROM = 5 ;
					SWITCH_ROM_MBC5(5L) ;
					combat(monnum,0x0B) ;
					changemusic = 6 ;
					dungrefresh = 1 ;

				}
			}

			currROM = 18 ;
			SWITCH_ROM_MBC5(18L) ;


		}
		if ( dungrefresh )
		{
			currROM = 6 ;
			SWITCH_ROM_MBC5(6L) ;
			for ( n=0 ; n<4;n++ )
				charscreen2(&players[n],n) ;
			currROM = 18 ;
			SWITCH_ROM_MBC5(18L) ;
			if ( dungrefresh==1 )
				update_screen_dungeon(1) ;
			dungrefresh = 0 ;
		}


		if ( dunglevel==99 )
			break ;
        
        if ( didaction != 0 ) 
        {
            didaction = 0 ;
            currROM = 18 ;
            SWITCH_ROM_MBC5(18L) ;
            update_screen_dungeon(0) ;
            enable_interrupts2() ;
        }
            
	}

	disable_interrupts2() ;

	for ( n=9; n<38 ; n++ )
		move_sprite(n,0,0) ;
	currROM = 2 ;
	SWITCH_ROM_MBC5(2L) ;
	set_bkg_data2(  0, 0x93U, u3tiles );
	memcpy((unsigned char*)0xB000,(unsigned char*)0x4000,4096UL) ;
	changebank(5) ;
	inside=0 ;

	enable_interrupts2() ;

	restoresosaria() ;

	disable_interrupts2() ;
	//move_sprite( 5, 56,64 );
	set_data2((unsigned char*)0x9802,dungendheader,8L) ;
	set_data2((unsigned char*)0x9C02,dungendheader,8L) ;
	screenbuf3[0] = moon2+0xB0;
	set_data2((unsigned char*)0x9800+7L,(unsigned char*)screenbuf3,1L) ;
	set_data2((unsigned char*)0x9C00+7L,(unsigned char*)screenbuf3,1L) ;
	screenbuf3[0] = moon1+0xB0 ;
	set_data2((unsigned char*)0x9800+5L,(unsigned char*)screenbuf3,1L) ;
	set_data2((unsigned char*)0x9C00+5L,(unsigned char*)screenbuf3,1L) ;


	screenbuf3[0] = 0x9EU ;
	screenbuf3[1] = 0x9FU ;

	set_data2((unsigned char*)0x9984,screenbuf3,2L) ;
	set_data2((unsigned char*)0x9D84,screenbuf3,2L) ;


	enable_interrupts2() ;

	changemusic = 1;
	need_refresh = 1 ;


}

UBYTE maptomusic[] = {
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	10,
	19,
	8,
	27,
	28,
	29,
	30,
	31,
	32
} ;

UBYTE calcmusic( UBYTE cmvar)
{

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

	if ( extragame )
	{
		if ( cmvar == 99 )
			return 12 ;
		else
			if ( cmvar > 15 )
			return 12 ;
		else
			return maptomusic[cmvar] ;
	}
	else
	{


		if ( cmvar==0 )
			return 4 ;
		else if ( cmvar==4 )
			return 10 ;
		else if ( cmvar==12 )
			return  9 ;
		else if ( cmvar==99 )
			return  1 ;
		else
			return 8 ;
	}



}

void loadnewmap(UBYTE themap)
{
	UBYTE r ;

	baddemeanor = 0 ;
	frozennum = 0 ;

	if ( themap==99 )
		return ;

	if ( themap==50 )
	{
		currROM = 26 ;
		SWITCH_ROM_MBC5(26L) ;
		docheat() ;
		currROM = 5 ;
		SWITCH_ROM_MBC5(5L) ;
		return ;
	}

	if ( themap&0xF0 )	//dungeon
	{
		dodungeon(themap) ;


	}
	else  //town, castle, ambrosia
	{
		disable_interrupts2() ;

		changemusic = calcmusic(themap) ;


		backupsosaria() ;

		currROM = ( extragame ? 29 : 10 ) + (themap/4L) ;
		SWITCH_ROM_MBC5( ( extragame ? 29L : 10L ) + ((UWORD)themap/4L)) ;
		SWITCH_RAM_MBC5(3) ;
		memcpy((unsigned char*)0xA000,(unsigned char*)0x4000+(0x1000* (UWORD)(themap%4)),4096L) ;
		SWITCH_RAM_MBC5(1) ;
		memcpy((unsigned char*)0xA000,(unsigned char*)0x4000+(0x1000* (UWORD)(themap%4)),4096L) ;
		inside = 1 ;


		currROM = extragame ? 33 : 13 ;
		SWITCH_ROM_MBC5( extragame ? 33L : 13L) ;
		memcpy(monsters,(unsigned char*)(0x5160+(0x1C0L*(UWORD)themap)),MONSTERSIZE*32L) ;
		//loadmonsters/talk

		playerx = *(unsigned char*)(0x5000+(UWORD)(themap*4)) ;
		playery = *(unsigned char*)(0x5001+(UWORD)(themap*4)) ;
		screenx = *(unsigned char*)(0x5002+(UWORD)(themap*4)) ;
		screeny = *(unsigned char*)(0x5003+(UWORD)(themap*4)) ;

		nummonsters = 0 ;

		for ( r = 0 ; r<32 ; r++ )
			if ( monsters[r].tile )
			{
				nummonsters++ ;
				*(unsigned char*)(0xA000+((UWORD)(monsters[r].y)*64L)+(UWORD)(monsters[r].x)) = monsters[r].tile ;
			}


		peermap = themap ;
		//SWITCH_ROM_MBC5(14L) ;
		//set_bkg_data2(  0x94, 0x40U, (unsigned char*)0x4400+(((UWORD)themap)<<10));

		currROM = 5 ;
		SWITCH_ROM_MBC5(5L) ;
		enable_interrupts2() ;
	}
}

void specialsfx()
{
	UBYTE backupROM ;

	backupROM = currROM ;

	currROM = 28 ;
	SWITCH_ROM_MBC5(28L) ;

	specialsfx28() ;

	currROM = backupROM ;
	SWITCH_ROM_MBC5( (UWORD)currROM ) ;

}

void main()
{
	UBYTE menuselection ;
	UBYTE n ;
	UBYTE actioncmd ;
	unsigned char atile ;




	disable_interrupts2();
	LCDC_REG |= 0x18 ;
	DISPLAY_OFF;
	cpu_fast() ;


	currROM = 43 ;
	SWITCH_ROM_MBC5(43UL) ;
	title_animate1() ;

	isnewgame = 0 ;

	stat_int = 0 ;

	extragame = 0 ;

	changemusic = 0 ;
	curr_sfx = 0 ;
	change_sfx = 0 ;
	didfreezesfx = 0 ;
	musicbank = 22 ;


	DISPLAY_OFF ;
	disable_interrupts2() ;

	ENABLE_RAM_MBC5 ;
	SWITCH_RAM_MBC5(0) ;
	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;

	if ( ( *(unsigned char*)(0xA000)=='U') &&
		 ( *(unsigned char*)(0xA001)=='3') &&
		 ( *(unsigned char*)(0xA002)=='G') &&
		 ( *(unsigned char*)(0xA003)=='B') )  //we've used it before
	{
		n = 0 ;
		for ( ctr=(unsigned char*)0xA000 ; ctr < (unsigned char*)0xBFFF ; ctr++ )
			n += *ctr ;
		if ( n != *(unsigned char*)(0xBFFF) )
			initialize_memory() ;
	}
	else  //1st time running cart
		initialize_memory()	;

	set_bkg_palette( 0, 1, &bkg_p[0] );
	set_bkg_palette( 1, 1, &bkg_p[4] );
	set_bkg_palette( 2, 1, &bkg_p[8] );
	set_bkg_palette( 3, 1, &bkg_p[12] );
	set_bkg_palette( 4, 1, &bkg_p[16] );
	set_bkg_palette( 5, 1, &bkg_p[20] );
	set_bkg_palette( 6, 1, &bkg_p[24] );
	set_bkg_palette( 7, 1, &bkg_p[28] );
	set_sprite_palette( 0, 1, &obj_p[0] );
	set_sprite_palette( 1, 1, &obj_p[4] );
	set_sprite_palette( 2, 1, &obj_p[8] );
	set_sprite_palette( 3, 1, &obj_p[12] );
	set_sprite_palette( 4, 1, &obj_p[16] );
	set_sprite_palette( 5, 1, &obj_p[20] );
	set_sprite_palette( 6, 1, &obj_p[24] );
	set_sprite_palette( 7, 1, &obj_p[28] );


	currROM = 4 ;
	SWITCH_ROM_MBC5(4UL) ;
	SWITCH_RAM_MBC5(2) ;  
	memcpy((unsigned char*)0xA000,(unsigned char*)0x4000,0x2000L) ;

	currROM = 3 ;
	SWITCH_ROM_MBC5(3UL) ;
	titlescreen() ;
	SHOW_BKG ;
	DISPLAY_ON ;
	enable_interrupts2();

#ifndef LIKSANG
	waitpad(J_START) ;
	waitpadup() ;
#else
	delay(2000) ;
#endif

	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;

//	currROM = 36 ;
	//SWITCH_ROM_MBC5(36UL) ;

//	shoot_main() ;

	seed.b.l = DIV_REG;

	DISPLAY_OFF ;
	disable_interrupts2() ;

	changemusic = extragame ? 12 : 1 ;
	peer_semaphore = 0 ;
	whirldirectx = 0 ;
	whirldirecty = 1 ;
	windctr = 0 ;
	winddir= 0 ;
	whirlctr = 0 ;
	volume_on = 1 ;
	musicctr = MAXCLOCK ;
	whichvbl = 18 ;
	inside = 10 ;
	add_VBL(myVBL);
	add_TIM(tint);
//  TMA_REG = 0xFCU; 
	TMA_REG = 0xF9U; 
	TAC_REG = 0x04U;
	//set_interrupts(VBL_IFLAG);
	//set_interrupts(TIM_IFLAG);
	set_interrupts(TIM_IFLAG | VBL_IFLAG);

//  enable_interrupts2() ;
//  while (1)
	//;


	currROM = 3 ;
	SWITCH_ROM_MBC5(3UL) ;
	while ( 1 )
	{
		dointro() ;
		menuselection=1 ;
		while ( menuselection==1 )
		{
			menuselection = mainmenu() ;
			if ( menuselection==0 )	 //return to view
				break ;
			if ( menuselection==1 )	 //organize a party
				rostermenu() ;
			if ( menuselection==2 )	//journey onward - check first, if it comes back here we're OK
				break ;
			if ( menuselection==3 )	//test game music
			{
				currROM = 26 ;
				SWITCH_ROM_MBC5(26L) ;
				domainmusic() ;
				currROM = 3 ;
				SWITCH_ROM_MBC5(3UL) ;
				menuselection = 1 ;
			}
		}

		if ( menuselection==0 )
			continue ;
		else
			break ;

	}

	DISPLAY_OFF ;
	disable_interrupts2() ;

	SWITCH_RAM_MBC5(0) ;



	currROM = 2 ;
	SWITCH_ROM_MBC5(2UL) ;
	SWITCH_RAM_MBC5(1) ;

	init_screen() ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	VBK_REG=1 ;
	set_data2((unsigned char*)0x9800,(unsigned char*)0x9C00,0x400UL) ;
	VBK_REG=0 ;

//  screenx = 0 ;
//  screeny = 0 ;
//  playerx = 5 ;
//  playery = 5 ;

	peer_semaphore = 0 ;
	peermap = 99 ;

	need_refresh = 1 ;
	inexodus = 0 ;
	die_exodus = 0 ;
	whichvbl = 5 ;
	joywait = JOYPADDELAY ;
	lastkey = 0 ;
	mode4tiles = 0 ;
	mode8tiles = 0 ;
	delayscroll = SCROLLDELAY ;
//  transport = 0 ;
//  nummonsters = 0 ;
	inside = 0 ;
	moves = 0 ;
	moon1 = 0 ;
	moon2 = 0 ;
	stoptime = 0 ;

	currROM = 5 ;
	SWITCH_ROM_MBC5(5UL) ;
	SWITCH_RAM_MBC5(1) ;
	update_screen() ;
	//myVBL() ;

//      waitpadup();
	seed.b.h = DIV_REG;
	initarand(seed.w);
//  add_VBL(myVBL);
//  set_interrupts(VBL_IFLAG);


	SCX_REG = 0x00 ;
	SCY_REG = 0x00 ;
	DISPLAY_ON;
	enable_interrupts2();

	currROM = 16 ;
	SWITCH_ROM_MBC5(16L) ;
	writewind() ;


	currROM = 5 ;  
	SWITCH_ROM_MBC5(5L) ;

	/*
	players[0].gold = 9999L ;
	players[0].keys=99 ;
	players[0].gems=99 ;
	players[0].markcard=0xFFU ;
	memset(players[0].armors,2,8L) ;
	memset(players[0].weapons,2,16L) ;
	memset(players[1].armors,2,8L) ;
	memset(players[1].weapons,2,16L) ;
	memset(players[2].armors,2,8L) ;
	memset(players[2].weapons,2,16L) ;
	players[0].currHP = 2550L ;
	players[0].maxHP = 2550L ;
	players[1].currHP = 2550L ;
	players[1].maxHP = 2550L ;
	players[2].currHP = 2550L ;
	players[2].maxHP = 2550L ;
	players[0].dex=50U ;
	players[0].str=50U ;
	players[0].wis=50U ;
	players[0].intel=50U ;
	players[1].dex=50U ;
	players[1].str=50U ;
	players[1].wis=50U ;
	players[1].intel=50U ;
	players[2].dex=50U ;
	players[2].str=50U ;
	players[2].wis=50U ;
	players[2].intel=50U ;
	
	party_specials = 0x0FFFUL ;
	*/
/*
  players[0].food = 9950 ;
  players[0].exp = 2400L ;
  players[0].level = 1 ;
  players[0].gold = 9999L ;
  players[1].gold = 999L ;
  players[2].gold = 99L ;
  players[3].gold = 9L ;
  */
	//players[0].currHP = 3000L ;
	//players[0].markcard=0xFFU ;
	//memset(players[0].armors,2,8L) ;
	//memset(players[0].weapons,2,16L) ;
	//party_specials = 0x0F ;
	/*
	memset(players[1].armors,9,8L) ;
	memset(players[1].weapons,9,16L) ;
	players[0].powders=99 ;
	players[0].gems=99 ;
	players[0].keys=99 ;
	players[0].torches=99 ;
	players[1].powders=9 ;
	players[1].currHP = 150 ;
	players[1].food = 150 ;
	players[0].magic = 99 ;
	players[1].magic = 99 ;
	players[2].magic = 99 ;
	players[3].magic = 99 ;

	players[0].exp = 200L ;
	players[0].level = 1 ;
	players[0].markcard=0x00U ;
	players[1].exp = 700L ;
	players[1].level = 1 ;
	players[1].markcard=0x00U ;
	players[2].exp = 400L ;
	players[2].level = 1 ;
	players[2].markcard=0xFFU ;
	players[3].exp = 3000L ;
	players[3].level = 1 ;
	players[3].markcard=0xFFU ;
  */


//  nummonsters = 1 ;


	leaving = 0 ;
	moonchanges = 0 ;

	fasterflip = 0 ;
	hitship = 0 ;
	numalive = 0 ;

	for ( n=0 ; n < 4 ; n++ )
	{
		if ( (players[n].inparty)&&(players[n].status<2) )
			numalive++ ;
	}

	cheat_xray = 0 ;
	cheat_nofight = 0 ;
	cheat_nohurt = 0 ;
	cheat_noblock = 0 ;
	cheat_fullmp = 0 ;
	cheat_noclass = 0 ;

	omnieye = 0 ;
	filled_delay = 0 ;

	changemusic = calcmusic(peermap) ;

//  for (n=0 ; n < 1 ; n++)
//  {
	//*((unsigned char*)(0xA000))=0x1E ;
	//monsters[n].attribs = 0x12 ;
	//monsters[n].x = n ;
	//monsters[n].y = n ;
	//monsters[n].tile = 0x1e ;
	//}
	//*((unsigned char*)(0xA002))=0x0E ;
	//*((unsigned char*)(0xA001))=0x0C ;

	// *((unsigned char*)(0xA004))=0x0F ;
	//monsters[31].attribs = 0x12 ;
	//monsters[31].x = 4 ;
	//monsters[31].y = 0 ;
	//monsters[31].tile = 0x0F ;

/*
	while(1)
	{
		currROM = 40 ;
		SWITCH_ROM_MBC5(40UL) ;
		shoot_animate1() ;
	
		currROM = 41 ;
		SWITCH_ROM_MBC5(41UL) ;
		shoot_animate2() ;
	
		currROM = 42 ;
		SWITCH_ROM_MBC5(42UL) ;
		shoot_animate3() ;
	}*/


	while ( 1 )	 //main game loop
	{

		mademove = 0 ;
		if ( numalive==0 )
		{
			writegamemessage(alldeaddat) ;
			while ( 1 )	; 
		}


		if ( whirlctr>MAXWHIRL )
			whirlctr = 0 ;
		else
			whirlctr++ ;

		if ( whirlctr==0 )
		{
			currROM = 16 ;
			SWITCH_ROM_MBC5(16L) ;
			dowhirl() ;
			currROM = 5 ;
			SWITCH_ROM_MBC5(5L) ;
		}


		if ( windctr>MAXWIND )
			windctr = 0 ;
		else
			windctr++ ;

		if ( windctr==0 )
		{
			currROM = 16 ;
			SWITCH_ROM_MBC5(16L) ;
			dowinds() ;
			currROM = 5 ;
			SWITCH_ROM_MBC5(5L) ;
		}

		if ( need_refresh!=0 )
		{
			currROM = 5 ;
			SWITCH_ROM_MBC5(5L) ;
			SWITCH_RAM_MBC5(1) ;
			update_screen() ;
			need_refresh = 0 ;
			whirlctr += WHIRLPMOVE;
			windctr += WINDPMOVE;

		}
		joykeys =joypad() ;
		if ( hitship==1 )
		{
			joykeys=0 ;
			mademove = 1;
		}

		if ( joykeys==lastkey )
		{
			if ( filled_delay == 0 )
			{
				joywait-- ;
				if ( joywait!=0 )
				{
					wait_vbl_done() ;
					continue ; 
				}
				else
					filled_delay = 1 ;
			}
		}
		else
		{
			joywait = JOYPADDELAY ;
			filled_delay = 0 ;
		}

		if ( (joykeys&J_UP) )
		{
			if ( validmove(1) )
			{
				disable_interrupts2() ;
				if ( playery==0 )
				{
					playery = 63 ;
					leaving = 1 ;
				}
				else
					playery-- ;
				if ( screeny==0 )
					screeny = 63 ;
				else
					screeny-- ;
				dir = 1 ;
				enable_interrupts2() ;
			}
			else
				dir	= 5 ;

			mademove = 1 ;

		}
		else
			if ( joykeys&J_DOWN )
		{
			if ( validmove(7) )
			{
				disable_interrupts2() ;
				if ( playery==63 )
				{
					playery = 0 ;
					leaving=1 ;
				}
				else
					playery++ ;
				if ( screeny==63 )
					screeny = 0 ;
				else
					screeny++ ;
				dir = 2 ;
				enable_interrupts2() ;
			}
			else
				dir	= 5 ;
			mademove = 1 ;

		}
		else
			if ( joykeys&J_LEFT )
		{
			if ( validmove(3) )
			{
				disable_interrupts2() ;
				if ( playerx==0 )
				{
					playerx = 63 ;
					leaving=1 ;
				}
				else
					playerx-- ;
				if ( screenx==0 )
					screenx = 63 ;
				else
					screenx-- ;
				dir = 4 ;
				enable_interrupts2() ;
			}
			else
				dir	= 5 ;
			mademove = 1 ;

		}
		else
			if ( joykeys&J_RIGHT )
		{
			if ( validmove(5) )
			{
				disable_interrupts2() ;
				if ( playerx==63 )
				{
					playerx = 0 ;
					leaving=1 ;
				}
				else
					playerx++ ;
				if ( screenx==63 )
					screenx = 0 ;
				else
					screenx++ ;
				dir = 3 ;
				enable_interrupts2() ;
			}
			else
				dir	= 5 ;
			mademove = 1 ;

		}

/*
		if ( joykeys&J_SELECT )
		{
			currROM = 26 ;
			SWITCH_ROM_MBC5(26L) ;
			docheat() ;
			currROM = 5 ;
			SWITCH_ROM_MBC5(5L) ;
		}
*/

		if ( joykeys&J_B )
		{
			writegamemessage(passdat2) ;
			mademove = 1 ;
		}

		if ( mademove )
			fasterflip += 0x80U ;

		if ( joykeys&J_A )
		{
			changebank(7) ;

			actioncmd=getmenuselection2(23,mainmenudat,0) ;

			mademove = 1 ;
			if ( actioncmd<23 )
				changebank(menubanksdat[actioncmd]) ;

			switch ( actioncmd )
			{
				case 0 : 
					{
						n=domapattack() ; 
						if ( (n==0)||(n==100) )
							mademove=0 ;
						else
							if ( n==50 )
						{
							changebank(26) ;
							killgenerator() ;
						}
						else
						{
							if ( n!=100 )
							{
								combat(n-1,*((unsigned char*)0xA000+(((UWORD)playery)*64L)+((UWORD)playerx))) ;
								changemusic = calcmusic(peermap) ;
							}
						}

						break ;
					}
				case 1 : leaving = doboard() ; break ;
				case 2 : mademove = docastspell(98) ; break ;
				case 3 : loadnewmap(doenter()) ; break ;
				case 4 : mademove = dofirecannon() ; break ;
				case 5 : mademove=dogetchest(0,0,0,0) ; break ;
				case 6 : mademove=dohand() ; break ;
				case 7 : mademove=dojoin() ; break ;
				case 8 : 
					{


						mademove=dolook() ; 
						if ( mademove & 0x20 )
						{
							currROM = 28 ;
							SWITCH_ROM_MBC5(28L) ;
							mademove = dosecretdoor( mademove, 1 ) ;
						}

						break ;
					}
				case 9 : mademove=domodify() ; break ;
				case 10 : mademove=donegate() ; break ;
				case 11 : {
						mademove = doyellother(0) ; 
						if ( mademove & 0xF0U )
						{
							currROM = 28 ;
							SWITCH_ROM_MBC5(28L) ;
							mademove = doextraother(mademove) ;

							if ( mademove == 0xFFU )
							{
								currROM = 36 ;
								SWITCH_ROM_MBC5(36UL) ;

								shoot_main() ;
							}

						}
						break ;
					}

				case 12 : mademove=dopeergem(0) ; break ;
				case 13 : mademove=doquitsave() ; break ;
				case 14 : mademove=dowearready(0) ; break ;
				case 15 : mademove=dosteal() ; break ;
				case 16 : 
					{
						if ( extragame )
						{
							currROM = 34 ;
							SWITCH_ROM_MBC5(34L) ;
							mademove=dotransact34(peermap) ;
						}
						else
						{
							mademove=dotransact(peermap) ; 
						}


						if ( mademove!=1 )
						{
							if ( extragame != 0 )
							{
								changebank(35) ;
								mademove=dotransact35( peermap, mademove ) ;
							}
							else
							{
								changebank(21) ;
								mademove=dotransact2(peermap,mademove);
							}
						}
						break ;

					}
				case 17 : mademove=dounlock() ; break ;
				case 18 : dovolume() ; break ;
				case 19 : mademove=dowearready(1) ; break ;
				case 20 : doxit() ; break ;
				case 21 : if ( extragame != 0 )	mademove = 0 ;
					else mademove = doyellother(1) ; break ;
				case 22 : mademove=doztats() ; break ;
				default : mademove = 0 ; break ;



			}
			if ( (mademove==0)&&(actioncmd<23) )
				writegamemessage(canceldat4) ;
			if ( mademove )
				fasterflip = 0 ;
			changebank(6) ;
			for ( n=0 ; n<4;n++ )
				charscreen2(&players[n],n) ;
			changebank(5) ;
		}
		if ( mademove )
		{
			if ( omnieye != 0 )
				omnieye-- ;

			if ( leaving )
			{
				if ( inside )
					restoresosaria() ;
				leaving = 0 ;


			}
			postmove() ;
			atile = *((unsigned char*)0xA000+(((UWORD)playery)<<6)+((UWORD)playerx));
			if ( (atile==0x0F)&&(transport==1)&&(inside==0) )  //whirlpool
			{
				currROM = 5 ;
				SWITCH_ROM_MBC5(5L) ;
				SWITCH_RAM_MBC5(1) ;
				update_screen() ;
				hitship = 1 ;
				atile = 0x0F ;
				disable_interrupts2() ;
				set_bkg_tiles2(6,6,1,1,&atile) ;
				enable_interrupts2() ;
				for ( n=0 ; n!=5 ; n++ )
					writegamemessage(whirl1+((UWORD)(n*12))) ;
				whirlpoolsfx(250U) ;
				waitpadup() ;
				waitpad(0xFF) ;
				for ( n=0 ; n!=4 ; n++ )
					writegamemessage(whirl1+60L+((UWORD)(n*12))) ;
				waitpadup() ;
				waitpad(0xFF) ;
				for ( n=0 ; n!=5 ; n++ )
					writegamemessage(whirl2+((UWORD)(n*12))) ;
				memset(screenbuf3,0x5D,11L) ;
				disable_interrupts2() ;
				for ( n=0 ; n!=11 ; n++ )
					set_bkg_tiles2(1,1+n,11,1,screenbuf3) ;
				enable_interrupts2() ;
				//dark screen
				waitpadup() ;
				waitpad(0xFF) ;
				monsters[31].x = 3 ;
				monsters[31].y = (make_rnd(0x38)) + 0x07 ;

				transport = 0 ;
				playerscreentile = 0x5c ;
				*((unsigned char*)0xA000+(((UWORD)playery)<<6)+((UWORD)playerx)) = 0x00 ;
				loadnewmap( extragame ? 15 : 12) ;
				hitship = 0 ;
				currROM = 5 ;
				SWITCH_ROM_MBC5(5L) ;
				SWITCH_RAM_MBC5(1) ;
				update_screen() ;
				for ( n=0 ; n!=5 ; n++ )
					writegamemessage(whirl2+60L+((UWORD)(n*12))) ;
				waitpadup() ;
				waitpad(0xFF) ;
				for ( n=0 ; n!=3 ; n++ )
					writegamemessage(whirl2+120L+((UWORD)(n*12))) ;

			}
			else
				if ( (atile==0x0F)&&(transport==1)&&inside )  //whirlpool
			{
				//whirlsfx
				memset(screenbuf3,0x5D,11L) ;
				disable_interrupts2() ;
				for ( n=0 ; n!=11 ; n++ )
					set_bkg_tiles2(1,1+n,11,1,screenbuf3) ;
				enable_interrupts2() ;
				writegamemessage(whirl3) ;
				whirlpoolsfx(250U) ;
				waitpadup() ;
				waitpad(0xFF) ;

				restoresosaria() ;
				writegamemessage(whirl3+12L) ;
				//repositionwhirlpool() ;
			}

			if ( inexodus )
				stoptime = 0 ;

			if ( stoptime!=0 )
				stoptime-- ;
			else
			{
				changebank(8) ;
				generatemonsters() ;
				changebank(5) ;

				if ( (playerscreentile==0x5C)||((playerscreentile!=0x5C)&&
												(fasterflip==0) ) )
				{
					for ( n=0 ; n < nummonsters ; n++ )
					{
						if ( move_monsters(n) )
						{
							combat(n,*((unsigned char*)0xA000+(((UWORD)playery)*64L)+((UWORD)playerx))) ;
							changemusic = calcmusic(peermap) ;
						}
						if ( numalive==0 )
							break ;



					}
					if ( ingenerator != 0 )
					{
						changebank(8) ;
						generatemonsters() ;
						changebank(5) ;
					}
				}
				//if (inside==0)
				/*
			   if ((move_monsters(31))&&(transport==1))
			   {
				   *((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[31].y))<<6))+(UWORD)(monsters[31].x)) = 0 ;
				   monsters[31].x = 3 ;
				   monsters[31].y = (make_rnd(0x38)) + 0x07 ;
				   *((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[31].y))<<6))+(UWORD)(monsters[31].x)) = 0x0F ;
				   transport = 0 ;
				   atile = 0x0F ;
				   set_bkg_tiles2(6,6,1,1,&atile) ;
				   //whirlpool sfx
				   playerscreentile = 0x5c ;
				  loadnewmap(12) ;
			   }	 */
			}

			currROM = 5 ;
			SWITCH_ROM_MBC5(5L) ;
			SWITCH_RAM_MBC5(1) ;
			update_screen() ;
			whirlctr += WHIRLPMOVE;
			windctr += WINDPMOVE;

			//need_refresh=1 ;
			//wait_vbl_done() ;
			changebank(8) ;
			if ( inexodus )
				doexodus() ;
			for ( n=0 ; n<nummonsters ; n++ )
			{
				if ( (monsters[n].tile==0x15)||(monsters[n].tile==0x23) )
					dragonbreath(n) ;
			}
			changebank(5) ;


		}
		lastkey = joykeys ;
		//wait_vbl_done() ;
	}
}
//ship was destroyed = attempt to access disabled RAM bank
//request - after exodus increase rate of monster generation


/*

extra "others" = climb, sextant, create fire/force - freeze monster, xray

for 9999 GP I will teach you grace and manners = "bow" - new way to talk to king

allow max stats = 99 for all

monsters hit x4 damange, players hit /2 damage

collect 4 pieces of exodus/generating monsters - 
1) room full of monsters around obj - won't regen, but maybe no magic
2) need to freeze npcs on certain spaces - will make monsters stop regenerating
3) monster regenerates around obj = need to use fire to guide them away
4) use xray - freeze will work through 1layer walls - all monsters move randomly until open door

once have all 4 pieces, need to "assemble" them and make time machine - go back in time
and kill mondain/minax before building exodus


have the shooting game in there as end game - save planet from space monsters

start new scenario = gold -> 200 each, strip down to hands/daggers/cloth

- bow
- learn about exodus in 4 pieces
- learn about time machine
- learn about program minax/mondain put in
- learn about abosrb from balrons
- learn about 4 balrons of power
- use castle or dungeon tile for exodus piece and/or balron places

- focus
- climb
- freeze
- make fire/force
- xray/omnieye
- absorb
- assemble
- bow 

focus, climb, absorb, bow - get from other places besides balrons

after get freeze, fire - use both to get climb
buy bow for 9000 gold from somewhere in a town
absorb - get by talking to a balron in olympus
focus - land of confusion - merchant/person

- dawn/dust surrounded by mountains - need climb

each balron will only give you power if you have exodus piece 4 pieces 4 balrons

- castle piece #1 - plain view - no special entry - just fight through - regen. in single line - fight your way towards it
	30,2
- balron #1 - plain view - give freeze ability
	46,7
- castle piece #2 - reachable by boat - walk right in - if don't freeze in pattern, monster regen.
	6,13
- balrom #2 - reachable by boat - give fire ability - freeze npcs in order to open door - use logic puzzle 4x4
	19,57
- castle piece #3 - reachable via climbing - final room surrounded by grass - guide monsters away
	7,44
- balron #3 - give xray ability - reachable via climbing - climb some mountains inside to get to some npcs and freeze them, 
  balrom inside walls inside mountains ; need to freeze npcs that follow you in 4 corners of a room that surrounds the balrom area
	56,6
- castle piece #4 - reachable via climbing - only enter room by xraying and freezing through walls,
  - that will open main doors - then you need to block some regenerated monsters via freezing
  - random-walk npcs through walls in key places - need to see via xray
  - don't have to block all of them - just enough to get to the regenerator
	18,31
- balron #4 - give assemble ability - final battle type dealy - lots of places need to xray to see npcs to freeze
only reach via climb - only enter by xraying/freezing npcs, lots o monsters, 
only reachable via teleport to grass then climb - make sure no monster can be generated there and there will always be grass there!
	49,34

ambrosia = olympus
castle britania
town britain
4 more towns
	
after getting each piece, castle interior disappears and you have to fight your way out- when out, the castle tile becomes grass forever.

guide monsters that follow you via fire to freeze them

hey, for my copy I would like under "race"
an "Other" choice so I could eventually go to the shrines and
get 100 for all 4.
And I want an "overlord" class that is essentially a
Fighter/thief/magician/cleric character.

enter a specific square to bring up cheat menu


AS YOU LEAVE
THE CASTLE
THE GROUND
BEGINS TO
SHAKE...
THE AIR 
AROUND YOU
SEEMS TO
BEAR DOWN
UPON YOUR
SHOULDERS...
ARCS OF
PURPLE FIRE
SHOOT OUT
FROM BEHIND.
YOU TURN
AROUND AND
SEE EXODUS
ENVELOPED IN
A COCOON OF
PULSATING
ENERGY. FOR
A MOMENT,
TIME SEEMS
TO STOP...
SUDDENLY, A
TREMENDOUS
CATACLYSM OF
UNEARTHLY
ENERGY RIPS
APART THE
WORLD AROUND
YOU.  MATTER
SEEMS TO 
DRAIN FROM
YOUR BODIES
AS THE
TUMULTUOUS
PHENOMENON
CONTINUES.
YOU FLOAT
IN AWE AS
A COSMIC
EVOLUTION
UNFOLDS.
EVENTUALLY
FAMILIAR
IMAGES TAKE
SHAPE BEFORE
YOU...
EXODUS...
MONDAIN...
MINOX...
YOU SEE YOUR
SORCEROUS
FOES TOIL
OVER THE
CREATION OF
EXODUS. 
AS THEY SEEM
TO FINISH
THEIR TASK
YOU WITNESS
BOTH OF THEM
LAYING THEIR 
HANDS UPON
THEIR NEWLY
CREATED
INSTRUMENT
OF EVIL.
BOLTS OF
LIGHT STREAM
FORTH FROM
THEIR FORE-
HEADS INTO
EXODUS.  AS
THEY LIFT
THEIR HANDS
FROM THE
MACHINE, YOU
FEEL A SENSE
OF DREAD. IF
THEY INDEED
STORED THEIR
INTELLECT
INTO THE
MEMORY BANKS
OF EXODUS,
THEN THE
ABILITY TO
TRAVEL IN
TIME MIGHT
BE AT ITS
DISPOSAL.
INSTANTLY
YOU REALIZE
THAT YOU 
ARE INDEED
CAUGHT UP
IN A TIME
RIFT WITH
EXODUS AS IT
TRAVELS BACK
TO REJOIN
ITS CREATORS
AND WREAK
HAVOK ONCE 
AGAIN. YOU
STRUGGLE
AGAINST THE
COSMIC CUR-
RENT TOWARDS
EXODUS TO
FINALLY END
ITS MALEVO-
LENT REIGN.
AS YOU SINK
YOUR SWORD
INTO ITS
ELECTRONIC
INNARTS, AN
EERIE NOISE
RISES FROM
ITS BELLOWS.
INSTANTLY 
YOUR VOYAGE
ACROSS TIME
COMES TO A
HALT AND YOU
BECOME AWARE
THAT YOU ARE
BACK IN THE
CASTLE FROM
WHENCE YOU
LEFT. THE
SHOCK WAVE
THAT ERUPTS
FROM EXODUS
AND DESTROYS
THE CASTLE
SENDS YOU
SOARING OUT
OF THE GATES
AND INTO A
STRANGE NEW
WORLD....



todo:

print out exodus text, then reload new sosaria
remap music banks
remap town banks - use diff. bank for town talk stuff
make sure monsters regenerate at desired interval
if in badcastle, do regeneration routine

cast teleport spell will never land you on special square until you are almost finished
and will only teleport you there 5% of the time.
teleport from (14,54) -> island town
teleport from (33,27) -> final baddie


monsters hit harder - more damage to you, less to them, redo dex calc's
 - new monster array of power, HP, etc - new battle calcs

shrines - allow 99 for all

heal spells - more healing - haven't done yet - maybe shouldn't

conditionals for peermap ( if peermap==## then -> need to search for and change for newgame)

new "others":
- focus (sextant)
- climb
- freeze
- make fire/force
- xray/omnieye
- absorb
- assemble
- bow 

make the 16 new maps
 
lcb castle
britain town
castle 2 - freeze
dungeon 2 - freeze
castle 3 - freeze, force
dungeon 3 - freeze, force
castle 4 - freeze, force, xray
dungeon 4 - freeze, force, xray
olympus
dawn/dusk

*/

//ALL OF THE
//SHIPS HAVE
//DISAPPEARED!

//THERE IS BUT
//ONE PLACE TO
//FIND A SHIP

//PIRATES
//STRONGHOLD
//HAS A SHIP

//THE KING 
//FAVORS
//NOBLES

//THE KING
//REWARDS
//COURTESY

//CONFUSION 
//IMPROVES
//YOUR VISION

//4 DUNGEONS
//4 BALRONS
//4 POWERS

//LEARN HOW TO
//ABSORB POWER
//FROM BALRONS

//SECRET OF
//THE BALRONS
//LIES BELOW

//EVIL SPEAKS
//WHEN SPOKEN
//TO

//TALK TO YOUR
//ENEMIES

//SEEK YE THE
//TALKING
//BALRON!

//LOOK AND YE
//SHALL FIND!

//LOOK
//CAREFULLY!

//SOME WALLS
//HOLD SECRETS

//behind secret door in castle (beef)
//VORTEX AT
//14, 54 

//LOOK IN THE
//CASTLE FOR
//BEEF
//25,56

//FOR THE LAST
//TIME WE HAVE
//NO BEEF!

//JESTERS
//SPEAK IN
//CODE

//I LOVE
//CRYPTOGRAMS!

//ONLY WIZARDS
//CAN USE
//VORTEXES

//SPELLS 
//TRIGGER
//VORTEXES



//EXODUS IS
//ONE AS FOUR

//SVEN SAYS
//ENJOYING MY
//GAME?

//confusion to get focus
//learn about teleport to special places
//learn location of teleport to get to pirate island
//learn about balrons/power


//- learn about exodus in 4 pieces
//- learn about time machine
//- learn about program minax/mondain put in
//- learn about abosrb from balrons
//- learn about 4 balrons of power

//make all guards invincible
//stop force/freeze after making special event happen
//kill lord british - make special - open up prison doors and freeze guards

/*
!CLERIC WAS
NOT 4TH
QUEST

!4TH QUEST
WAS IN CAVE

!WIZARD DID
NOT GO TO
DUNGEON

!ORC NOT
KILLED BY
THIEF/CLERIC

!FIGHTER
KILLED DEMON
OR DRAGON

!RANGER
KILLED DEMON
OR DRAGON

!RANGER WAS
NOT FIRST OR
LAST QUEST

!FIGHTER WAS
NOT FIRST
QUEST

!FIELD QUEST
RIGHT AFTER
DEMON QUEST

!CASTLE IMM.
BTWN FIGHTER
AND WIZARD

!GIANT QUEST
RIGHT BEFORE
BALRON QUEST

11 CLUES ARE
ALL YOU NEED
...REALLY!

THERE ARE
EXACTLY
11 CLUES

CLUES ARE
MARKED BY
THE * SIGN

THE PROPER
WORD CAN
OPEN DOORS!

VORTEX AT
33,27
(dungeon4)

1 CLUE IN
EACH TOWN
AND CASTLE

CASTLE AT
18,31

CASTLE AT
7,44

DUNGEON AT
56,6

DUSK FALLS
AT 37,53

ATTACK
EXODUS
PIECES

ONE EXIT IN
MTN DUNGEON
IS NOT EXIT

FREEZE 
THROUGH
WALLS!

LEARN
COURTESY
AT RUDAN

CONFUSION
HOLDS 2
SECRETS!

CLIMB TO
6,21 IN
CONFUSION

MONSTERS
REGENERATE
IN CASTLES!

EXODUS CAN
STILL CREATE
EVIL!

FREEZE ON
SPECIFIC
LOCATIONS

MINOX AND
MONDAIN 
STILL TOIL!

TIME TRAVEL
TO STOP THE
WIZARDS!

EXODUS SPLIT
INTO FOUR
PIECES

EXODUS
BROUGHT BACK
THE WIZARDS!

ODD THINGS
ABOUND IN 
THE SKIES...

THE WIZARDS
WORK IN
THE SKIES

USE EXODUS
TO FIND YOUR
SPACESHIP!

A SPACESHIP
CAN STOP
THE WIZARDS!

THE WIZARDS
WILL DESTROY
THE WORLD!

THE WIZARDS
CAN CONTROL
ALIENS

4 CASTLES
4 PIECES

CASTLES HOLD
PIECES OF
EXODUS

EVIL EXISTS
ON OTHER
WORLDS.

OLYMPUS.
EVER HEARD
OF IT?

CASTLES HOLD
MUCH DANGER.
BEWARE!

CLIMBING IS
A LITTLE
KNOWN SKILL

SOME BALRONS
CAN SEE THRU
WALLS!




learn about secret doors
learn about need absorb, how to get from balron
learn about attack exodus pieces
learn about regenerators in castles
go to confusion - get focus
learn about vortexes
learn location of vortex to pirate
get ship @pirate
go to olympus
talk to balron, get absorb
learn about exits, etc in dungeon1
do castle1, dungeon1
now can do castle2, dungeon2
now learn about confusion having 2 secrets (maybe from dungeon2)
get climb from confusion
learn about location of dungeon3, castle3
do castle3, dungeon3
learn about location of castle4 from dungeon3
do castle4
learn about vortex location in castle4
use vortex, do dungeon4

when start new game, music is battld music

*/

/*



- if you end the ultima III part while riding a horse (entered the exodus
castle thru the moongate), the horse appears in the second game - except
when you save the game and turn off the gb and continue later.. then the
horse has disappeard!

random walk NPCs in town will warp from 0 -> 63


*/
