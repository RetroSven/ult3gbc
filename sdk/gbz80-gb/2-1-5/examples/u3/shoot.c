#include <gb.h>

#include "bkg.h"
#include "fore.h"

#define GENOFFSET 0x081F

#define motion_offsets ((UWORD*)(0xA81F-GENOFFSET))
#define motions ((UBYTE*)(0xA837-GENOFFSET))
#define earth1 ((unsigned char*)(0xB0B1-GENOFFSET))
#define hitearth ((UBYTE*)(0xB6B1-GENOFFSET))
#define hittile ((UBYTE*)(0xB721-GENOFFSET))
#define std_data ((unsigned char*)(0xB745-GENOFFSET))
#define powertiles ((unsigned char*)(0xB785-GENOFFSET))
#define enemytiles ((unsigned char*)(0xB8E5-GENOFFSET))
#define shipmotion ((UBYTE*)(0xBEE5-GENOFFSET))
#define enemyframes ((UBYTE*)(0xC127-GENOFFSET))
#define levelStats ((struct Level_stats *)(0xC135-GENOFFSET))
#define powers_to_come ((struct Power_Sequence*)(0xC1A5-GENOFFSET))
#define shipfiredir ((BYTE*)(0xC229-GENOFFSET))
#define ship_frames ((UBYTE*)(0xC2BD-GENOFFSET))
#define shieldmap ((unsigned char*)(0xC329-GENOFFSET))
#define shieldloc ((unsigned char*)(0xC361-GENOFFSET))

/*
#define motion_offsets ((UWORD*)(0xA017))
#define motions ((UBYTE*)(0xA02F))
#define earth1 ((unsigned char*)(0xA8A9))
#define earth1map ((unsigned char*)(0xAEA9))
#define earthcolor ((unsigned char*)(0xAEC9))
#define hitearth ((UBYTE*)(0xAEE9))
#define hittile ((UBYTE*)(0xAF59))
#define std_data ((unsigned char*)(0xAF7D))
#define powertiles ((unsigned char*)(0xAFBD))
#define earthloc ((unsigned char*)(0xB11D))
#define enemytiles ((unsigned char*)(0xB15D))
#define shieldtile ((unsigned char*)(0xB75D))
#define shieldmap ((unsigned char*)(0xB91D))
#define shieldloc ((unsigned char*)(0xB955))
#define starsdat ((unsigned char*)(0xB98D))
#define starsmap ((unsigned char*)(0xBA1D))
#define sprite_colors ((unsigned char*)(0xBB85))
#define ship_shoot ((unsigned char*)(0xBB8D))

*/

//#include "allall3.dat" 

//#define ship_shield ((unsigned char*)(0xBE0D))
//#define ship_reg ((unsigned char*)(0xC08D))
//#define shipmotion ((UBYTE*)(0xC30D))
//#define ship_frames ((UBYTE*)(0xC54F))
//#define twinkle_tile ((unsigned char*)(0xC5BB))
//#define twinkle1_locs ((unsigned char*)(0xC60B))
//#define twinkle2_locs ((unsigned char*)(0xC611))
//#define twinkle1_map ((unsigned char*)(0xC617))
//#define twinkle2_map ((unsigned char*)(0xC61B))
//#define ammotiles ((unsigned char*)(0xC61F))
//#define explosiondata ((unsigned char*)(0xC6DF))
//#define enemyframes ((UBYTE*)(0xC8DF))
//#define levelStats ((struct Level_stats *)(0xC8ED))
//#define enemies_to_come ((struct Enemy_Sequence*)(0xC95D))
//#define powers_to_come ((struct Power_Sequence*)(0xCF53))
//#define shipfiredir ((BYTE*)(0xCFD7))


//numbkgtiles =  32 (3*32) (3 earths)
//             + 28 (earth shield)
//             +  9 stars bkg
//             +  6 animated stars
//             +  4 standard data
//             ----
//               89

//numspritetiles = 40 (regular ship rotating)
//                +40 (shooting ship)
//                +40 (shield ship)
//                +12 (ammo)
//                ---
//                132

//384-(143+132) = 384-275 = 173 left

//need tiles for special power ups, etc
//need tiles for enemies
//need tiles for explosions


//#include "death.dat"
//#include "death.map"


UWORD bkg_p2[] =
{
	bkgCGBPal7c0,bkgCGBPal7c1,bkgCGBPal7c2,bkgCGBPal7c3,
	bkgCGBPal6c0,bkgCGBPal6c1,bkgCGBPal6c2,bkgCGBPal6c3,
	bkgCGBPal5c0,bkgCGBPal5c1,bkgCGBPal5c2,bkgCGBPal5c3,
	bkgCGBPal4c0,bkgCGBPal4c1,bkgCGBPal4c2,bkgCGBPal4c3,
	bkgCGBPal3c0,bkgCGBPal3c1,bkgCGBPal3c2,bkgCGBPal3c3,
	bkgCGBPal2c0,bkgCGBPal2c1,bkgCGBPal2c2,bkgCGBPal2c3,
	bkgCGBPal1c0,bkgCGBPal1c1,bkgCGBPal1c2,bkgCGBPal1c3,
	bkgCGBPal0c0,bkgCGBPal0c1,bkgCGBPal0c2,bkgCGBPal0c3
};

//UWORD bkg_p2[] =
//{
//  bkgCGBPal7c0,bkgCGBPal7c1,bkgCGBPal7c2,bkgCGBPal7c3,
//  bkgCGBPal6c0,bkgCGBPal6c1,bkgCGBPal6c2,bkgCGBPal6c3,
//  bkgCGBPal5c0,bkgCGBPal5c1,bkgCGBPal5c2,bkgCGBPal5c3,
//  bkgCGBPal4c0,bkgCGBPal4c1,bkgCGBPal4c2,bkgCGBPal4c3,
//  bkgCGBPal3c0,bkgCGBPal3c1,bkgCGBPal3c2,bkgCGBPal3c3,
//  bkgCGBPal1c0,bkgCGBPal1c1,bkgCGBPal1c2,bkgCGBPal1c3,
//  bkgCGBPal2c0,bkgCGBPal2c1,bkgCGBPal2c2,bkgCGBPal2c3,
//  bkgCGBPal0c0,bkgCGBPal0c1,bkgCGBPal0c2,bkgCGBPal0c3
//};

UWORD obj_p2[] =
{
	foreCGBPal7c0,foreCGBPal7c1,foreCGBPal7c2,foreCGBPal7c3,
	foreCGBPal6c0,foreCGBPal6c1,foreCGBPal6c2,foreCGBPal6c3,
	foreCGBPal5c0,foreCGBPal5c1,foreCGBPal5c2,foreCGBPal5c3,
	foreCGBPal4c0,foreCGBPal4c1,foreCGBPal4c2,foreCGBPal4c3,
	foreCGBPal3c0,foreCGBPal3c1,foreCGBPal3c2,foreCGBPal3c3,
	foreCGBPal2c0,foreCGBPal2c1,foreCGBPal2c2,foreCGBPal2c3,
	foreCGBPal1c0,foreCGBPal1c1,foreCGBPal1c2,foreCGBPal1c3,
	foreCGBPal0c0,foreCGBPal0c1,foreCGBPal0c2,foreCGBPal0c3
};


UBYTE countdown ;
UWORD enemy_wait ;
UWORD power_wait ;

UBYTE shipframe_offset ;

UBYTE animate_wait ;

UBYTE curr_rand ;

extern UBYTE changemusic ;

UBYTE total_earth_hits ;
UBYTE total_enemies_hit ;

UBYTE numenemyfire ;
UBYTE numplayer1fire ;
UBYTE numplayer2fire ;


struct Enemy_Sequence
{
	UWORD sdelay ;		 //amount of time to wait before next enemy comes on screen
	UBYTE stype ;  // (also holds if it is a boss and it's speed)
	//bits 1-4 = which type of enemy tile to use
	//bit  5   = is_boss?
	//bit  6-8 = speed
	UBYTE spritenum ;	 //0-5 
	UBYTE motion_offsetx ;
	UBYTE motion_offsety ;
	UBYTE motionnum ;  //Which motion number to use
} ;


struct Enemy_Stats
{
	UBYTE in_use ;	   //Is it active?
	UBYTE *curr_frame ;	//current animation frame (0-3)
	UBYTE *curr_loc ;  //pointer into it's motion array
	UBYTE motion_offsetx ;
	UBYTE motion_offsety ;
	UBYTE motionnum ;
	UBYTE speed ;
	UBYTE stype ;
	UBYTE waitfire ;
	UBYTE numhits ;
} ;

struct Enemy_Stats enemies_on_screen[6] ;

struct Power_Stats
{
	UBYTE in_use ;	   //Is it active? also holds type of powerup
	UBYTE *curr_loc ;  //pointer into it's motion array
	UBYTE motion_offsetx ;
	UBYTE motion_offsety ;
	UBYTE speed ;
	UBYTE motionnum ;
} ;

struct Power_Stats power_on_screen ;


struct Power_Sequence
{
	UWORD sdelay ;
	UBYTE stype ; // (also holds speed)
	//bits 1-4 = which type of power tile to use
	//bit  6-8 = speed
	UBYTE motion_offsetx ;
	UBYTE motion_offsety ;
	UBYTE motionnum ;
} ;




struct Level_stats
{
	UWORD enemy1tileoffset ;
	UWORD enemy2tileoffset ;
	UWORD bosstileoffset ;
	UBYTE enemy1firewait ;
	UBYTE enemy2firewait ;
	UBYTE enemy1fire_rate ;
	UBYTE enemy2fire_rate ;
	UBYTE enemy1frameoffset ;
	UBYTE enemy2frameoffset ;
	UBYTE bossframeoffset ;
	UBYTE enemy1hits ;
	UBYTE enemy2hits ;
	UBYTE bosshits ;

};

//0x00 = skull
//0x04 = 2 concentric rings rotating in diff. directions
//0x08 = ball to cube
//0x0C = ball-ring, expand/contract
//0x10 = 3 ball cluster
//0x14 = rotating spiky


struct Enemy_Sequence *enemyptr ;
struct Power_Sequence *powerptr ;

UBYTE twinkle1_frame[3] ;
UBYTE twinkle2_frame[3] ;
UBYTE twinkle ;


struct ammo_stats
{
	UBYTE atype ; //(inuse/type of ammo)
	UBYTE x ;
	UBYTE y ;
	BYTE deltax ;
	BYTE deltay ;
	BYTE movedx ;
	BYTE movedy ;
} ;

struct ammo_stats enemy_ammo[5] ;
struct ammo_stats player1_ammo[4] ;
struct ammo_stats player2_ammo[4] ;

//UBYTE ammo_locs[70] ;   //(x,y,deltax,deltay,movedx,movedy,inuse?|spritetype)
//UBYTE special_locs[6*5] ;  //(startx,starty,motionpattern,motionframe,inuse?|type)
//0 = power up to 2shot (16 wide)
//1 = power up to cross - goes through everything
//2 = power up to circle - flies faster
//3 = power up to star - fast and goes through everything
//4 = bomb = explode everything on screen
//5 = planet restore
//6 = planet shield

UBYTE num_player_shots ; //number of player shots on screen 
UBYTE num_enemy_shots  ; //number of enemy shots on screen
UBYTE num_enemies      ; //number of enemies on screen

UBYTE level ;	//current level the player is on

UBYTE flipflop ;

UBYTE gen1, gen2, gen3 ;

extern UBYTE joykeys ;
extern UBYTE lastkey ;

UBYTE *shippos ;

UBYTE ship_shieldon ;
UBYTE ship_shieldpower ;
UBYTE ship_shieldwait ;

UBYTE ship_isdead, ship_isinvincible ;

UBYTE ship_shooting ;
UBYTE ship_offset ;
UWORD earth_shieldon ;
UBYTE ship_powerup ;
// 0 = regular
// 1 = double shot (x16)
// 0x40 = cross
// 0x80 = star



UBYTE ship_direction, ship_currframe  ;

UBYTE earth_state[36] ;


void earth_shield_on()
{
	UBYTE ii ;

	for ( ii=0 ; ii != 56 ; ii+=2 )
		set_bkg_tiles(shieldloc[ii],shieldloc[ii+1],1,1,shieldmap+(ii>>1)) ;
}

void earth_shield_off()
{
	UBYTE ii ;

	for ( ii=0 ; ii != 56 ; ii+=2 )
		set_bkg_tiles(shieldloc[ii],shieldloc[ii+1],1,1,shieldmap+(ii>>1)+28) ;
}

void ship_fireaway()
{
	UBYTE currx, curry ;
	UBYTE whichammo ;
	BYTE  *aptr ;
	struct ammo_stats *currammo ;

	if ( numplayer1fire!=3 )
	{

		whichammo = 0 ;
		while ( 1 )
		{
			if ( !player1_ammo[whichammo].atype )
				break ;
			whichammo++ ;
		}
		gen1 = *(shippos+2) + shipframe_offset ;
		if ( gen1 > 35 )
			gen1 -= 35 ;

		aptr = shipfiredir+ (gen1<<2) ;
		currammo = player1_ammo+whichammo ;

		currammo->atype = ship_powerup +1 ;
		currammo->x = *(shippos) + *aptr++ ;
		currammo->y = *(shippos+1) + *aptr++ ;
		currammo->deltax = *aptr++ ;
		currammo->deltay = *aptr++ ;
		currammo->movedx = 0 ;
		currammo->movedy = 0 ;
		numplayer1fire++ ;

//      if ship_powerup
	}

}


void levelup() ;






unsigned char colorarray[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07} ;



void fillup() ;
void setupEarth() ;
void init_vars() ;
void put_new_enemy() ;
void put_new_power() ;
void loadtiles() ;
void dotwinkle() ;

void scroll_enemies_power() ;
void scroll_enemy_ammo() ;
void check_enemy_collision() ;
void scroll_player1_ammo() ;
void check_player1_collision() ;
void animate() ;

void shoot_animate1() ;
void shoot_animate2() ;
void shoot_animate3() ;
void demon_animate() ;

extern UBYTE inside ;

extern UBYTE volume_on ;

void endgamebad()
{
	UBYTE spr ;

	for ( spr = 0 ; spr != 40 ; spr++ )
	{
		move_sprite(spr, 0, 0 ) ;
	}

	volume_on = 0 ;
	NR51_REG=0x00 ;

	remoteCall( 36, 40, shoot_animate1 ) ;
	remoteCall( 36, 41, shoot_animate2 ) ;
	remoteCall( 36, 42, shoot_animate3 ) ;

	changemusic = 35 ;
	volume_on = 1 ;

	remoteCall( 36, 39, demon_animate  ) ;
	while ( 1 )	;  
}


unsigned char finishmap[] = {
	0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D,'T'+0x1D,'H'+0x1D,'O'+0x1D,'U'+0x1D,0x5D,'H'+0x1D,'A'+0x1D,'S'+0x1D,'T'+0x1D,0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D,0x5D,0x5D,'S'+0x1D,'A'+0x1D,'V'+0x1D,'E'+0x1D,'D'+0x1D,0x5D,0x5D,0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D,'B'+0x1D,'R'+0x1D,'I'+0x1D,'T'+0x1D,'A'+0x1D,'N'+0x1D,'N'+0x1D,'I'+0x1D,'A'+0x1D,0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D,0x5D,'R'+0x1D,'E'+0x1D,'P'+0x1D,'O'+0x1D,'R'+0x1D,'T'+0x1D,0x5D,0x5D,0x5D,0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D,0x5D,0x5D,'T'+0x1D,'H'+0x1D,'Y'+0x1D,0x5D,0x5D,0x5D,0x5D,0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D,0x5D,'F'+0x1D,'E'+0x1D,'A'+0x1D,'T'+0x1D,0x82U,0x82U,0x5D,0x5D,0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 'E'+0x1D,'N'+0x1D,'T'+0x1D,'E'+0x1D,'R'+0x1D, 0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 122U, 120U, 133U, 121U, 128U, 0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 
	0x5D, 0x5D, 0x5D, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 0x5D, 


};

unsigned char finishcolormap[] = {
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
} ;

struct SPRITE_ATTRIBS
{
	UBYTE x ;
	UBYTE y ;
	BYTE  mx ;
	BYTE  my ;
} ;

struct SPRITE_ATTRIBS BOUNCER_DATA[] = {
	{ 40, 148, 2, 1},
	{ 16, 20, 1, 1},
	{ 150, 80, 1, 2},
	{ 10, 100, -2, 1},
	{ 90, 150, 1, -1},
	{ 160, 16, 1, -2},
	{ 156, 130, -1, -1},
} ;

struct SPRITE_ATTRIBS bouncers[7] ;

unsigned char sintab2[] = {
	128,131,134,137,140,143,146,149,152,155,158,162,165,167,170,173,
	176,179,182,185,188,190,193,196,198,201,203,206,208,211,213,215,
	218,220,222,224,226,228,230,232,234,235,237,238,240,241,243,244,
	245,246,248,249,250,250,251,252,253,253,254,254,254,255,255,255,
	255,255,255,255,254,254,254,253,253,252,251,250,250,249,248,246,
	245,244,243,241,240,238,237,235,234,232,230,228,226,224,222,220,
	218,215,213,211,208,206,203,201,198,196,193,190,188,185,182,179,
	176,173,170,167,165,162,158,155,152,149,146,143,140,137,134,131,
	127,124,121,118,115,112,109,106,103,100,97,93,90,88,85,82,
	79,76,73,70,67,65,62,59,57,54,52,49,47,44,42,40,
	37,35,33,31,29,27,25,23,21,20,18,17,15,14,12,11,
	10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,
	0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,
	10,11,12,14,15,17,18,20,21,23,25,27,29,31,33,35,
	37,40,42,44,47,49,52,54,57,59,62,65,67,70,73,76,
	79,82,85,88,90,93,97,100,103,106,109,112,115,118,121,124
} ;

void bounce_sprites();
void scroll_sprite1() ;

UWORD bouncedelay ;

UBYTE sprite1iter ;

unsigned char spr1_x[120] ;
unsigned char spr1_y[120] ;

UBYTE CIRCLEX, CIRCLEY ;
UBYTE CIRCLEXRAD, CIRCLEYRAD ;

UBYTE xrad, yrad ;

UBYTE sprite1_miscx, sprite1_miscy ;

void fill_sprxy() 
{
	UBYTE quadspacing ;
	UBYTE lastpos, p ;
	UBYTE deltax ;
	unsigned long res, holder1, holder2, nextpos ;
	unsigned long angle ;
	UBYTE arrcnt, arrcnt2, a, b ;
	unsigned long commonpt ;

//(x^2)/a^2 + (y^2)/b^2 = 1  

	for ( p=0 ; p < 100 ; p++ )
	{
		holder1 = ((unsigned long)p*255L)/100UL ;
		holder2 = (UWORD)CIRCLEX+(((UWORD)xrad*(UWORD)sintab2[holder1])/255UL) ;
		spr1_x[p] = holder2 ;

		holder1 = ((unsigned long)p*255L)/100UL ;
		holder2 = (UWORD)CIRCLEY+(((UWORD)yrad*(UWORD)sintab2[holder1])/255UL) ;
		spr1_y[p] = holder2 ;
	}

}

unsigned char newstardat[] = {
	0x10,0x10,0x54,0x54,0x38,0x38,0xFE,0xFE,0x38,0x38,0x54,0x54,0x10,0x10,0x00,0x00
};

void endgamegood()
{
	UBYTE ii ;
	UBYTE spr ;
	UBYTE key ;
	UBYTE tlastkey ;
	UWORD palnum ;
	UWORD speeddelay ;

	disable_interrupts() ;

	OBP0_REG = 0xFF ;
	OBP1_REG = 0xFF ;  //00 10 01 00
	BGP_REG = 0x00 ;

	sprite1iter = 0 ;
	CIRCLEX       =48;
	CIRCLEY       =48;
	CIRCLEXRAD    =45;
	CIRCLEYRAD    =35;

	xrad = CIRCLEXRAD ;
	yrad = CIRCLEYRAD ;

	sprite1_miscx = 8 ;
	sprite1_miscy = 4 ;

	fill_sprxy() ;

//    set_sprite_palette( 0, 1, &bkg_p2[0] );
	//set_sprite_palette( 1, 1, &bkg_p2[4] );
	//set_sprite_palette( 2, 1, &bkg_p2[8] );
	//set_sprite_palette( 3, 1, &bkg_p2[12] );
	//set_sprite_palette( 4, 1, &bkg_p2[16] );
	//set_sprite_palette( 5, 1, &bkg_p2[20] );
	//set_sprite_palette( 6, 1, &bkg_p2[24] );
	//set_sprite_palette( 7, 1, &bkg_p2[28] );

	SPRITES_8x8 ;

	SCX_REG = 0xFC;
	SCY_REG = 0x00 ;

	memcpy( (unsigned char*)bouncers, (unsigned char*)BOUNCER_DATA, 28UL ) ;

	for ( spr = 0 ; spr != 40 ; spr++ )
	{
		move_sprite(spr, 0, 0 ) ;
	}

	volume_on = 0 ;
	NR51_REG=0x00 ;

	loadu3tiles() ;
	set_sprite_data(  7, 0x01, newstardat );

	set_bkg_tiles2( 0, 0, 32, 16, finishmap ) ;

	for ( ii = 16 ; ii < 32 ; ii++ )
		set_bkg_tiles2( 0, ii, 32, 1, finishmap ) ;

	VBK_REG=1 ;
	for ( ii = 0 ; ii < 32 ; ii++ )
		set_bkg_tiles2( 0, ii, 32, 1, finishcolormap ) ;
	VBK_REG=0 ;

	changemusic = 18 ;
	volume_on = 1 ;

	for ( ii = 0 ; ii < 7; ii++ )
	{
		set_sprite_tile( ii,ii ) ;
		set_sprite_prop( ii, 0x01) ;
		move_sprite( ii, bouncers[ii].x, bouncers[ii].y ) ;
	}

	for ( ii = 7 ; ii < 14; ii++ )
	{
		set_sprite_tile( ii, 0x07 ) ;
		set_sprite_prop( ii, 0x06) ;
	}

	enable_interrupts() ;

	SWITCH_RAM_MBC5(1) ;
	inside = 0 ;

	speeddelay = 100UL ;
	bouncedelay = speeddelay ;

	tlastkey = 0 ;
	palnum = 0UL ;

	while ( 1 )
	{
		disable_interrupts() ;
		set_sprite_palette_entry(6, 3, palnum ) ;
		enable_interrupts() ;

		palnum++ ;

		key = joypad() ;

		if ( bouncedelay-- == 0UL )
		{
			bounce_sprites() ;
			scroll_sprite1() ;
			bouncedelay = speeddelay ;
		}


		if ( tlastkey != key )
		{

			if ( key&J_START )
			{
				if ( LCDC_REG & 0x01 )
				{
					LCDC_REG &= 0xFE ;
					SCX_REG = 0xFC;
					SCY_REG = 0x80 ;
				}
				else
				{
					LCDC_REG |= 0x01 ;
					SCX_REG = 0xFC;
					SCY_REG = 0x00 ;
				}

			}


			if ( key&J_A )
			{
				speeddelay -= 10  ;
			}
			if ( key&J_B )
			{
				speeddelay += 10 ;
			}

			if ( key&J_SELECT )
			{
				if ( key&J_DOWN )
				{
					yrad-- ;
					fill_sprxy() ;
				}
				if ( key&J_UP )
				{
					yrad++ ;
					fill_sprxy() ;
				}
				if ( key&J_RIGHT )
				{
					xrad++ ;
					fill_sprxy() ;
				}
				if ( key&J_LEFT )
				{
					xrad-- ;
					fill_sprxy() ;
				}
			}
			else
			{
				if ( key&J_DOWN )
					if ( sprite1_miscy==0 )
						sprite1_miscy = 99 ;
					else
						sprite1_miscy--	;

				if ( key&J_UP )
					if ( sprite1_miscy == 99 )
						sprite1_miscy = 0 ;
					else
						sprite1_miscy++	;

				if ( key&J_RIGHT )
					if ( sprite1_miscx == 99 )
						sprite1_miscx = 0 ;
					else
						sprite1_miscx++	;

				if ( key&J_LEFT )
					if ( sprite1_miscx==0 )
						sprite1_miscx = 99 ;
					else
						sprite1_miscx--	;
			}
		}

		tlastkey = key ;
	}

}

void bounce_sprites()
{
	UBYTE spr ;

	for ( spr = 0 ; spr < 7 ; spr++ )
	{
		if ( (long)bouncers[spr].x + bouncers[spr].mx < 8 )
		{
			bouncers[spr].x = 8 ; 
			bouncers[spr].mx *= -1 ;
		}
		else
			if ( (long)bouncers[spr].x + bouncers[spr].mx > 160 )
		{
			bouncers[spr].x = 160 ;
			bouncers[spr].mx *= -1 ;
		}
		else
			if ( ((long)bouncers[spr].x + bouncers[spr].mx > 28) &&
				 ((long)bouncers[spr].x + bouncers[spr].mx < 42) &&
				 ((long)bouncers[spr].y > 24 ) &&
				 ((long)bouncers[spr].y < 144 ) )
		{
			bouncers[spr].x = 28 ;
			bouncers[spr].mx *= -1 ;
		}
		else
			if ( ((long)bouncers[spr].x + bouncers[spr].mx < 140) &&
				 ((long)bouncers[spr].x + bouncers[spr].mx > 100) &&
				 ((long)bouncers[spr].y > 24 ) &&
				 ((long)bouncers[spr].y < 144 ) )
		{
			bouncers[spr].x = 140 ;
			bouncers[spr].mx *= -1 ;
		}
		else
			bouncers[spr].x	+= bouncers[spr].mx ;

		if ( (long)bouncers[spr].y + bouncers[spr].my < 16 )
		{
			bouncers[spr].y = 16 ; 
			bouncers[spr].my *= -1 ;
		}
		else
			if ( (long)bouncers[spr].y + bouncers[spr].my > 152 )
		{
			bouncers[spr].y = 152 ;
			bouncers[spr].my *= -1 ;
		}
		else
			if ( ((long)bouncers[spr].y + bouncers[spr].my > 24) &&
				 ((long)bouncers[spr].y + bouncers[spr].my < 48) &&
				 ((long)bouncers[spr].x > 28 ) &&
				 ((long)bouncers[spr].x < 140 ) )
		{
			bouncers[spr].y = 24 ;
			bouncers[spr].my *= -1 ;
		}
		else
			if ( ((long)bouncers[spr].y + bouncers[spr].my < 144) &&
				 ((long)bouncers[spr].y + bouncers[spr].my > 104) &&
				 ((long)bouncers[spr].x > 28 ) &&
				 ((long)bouncers[spr].x < 140 ) )
		{
			bouncers[spr].y = 144 ;
			bouncers[spr].my *= -1 ;
		}
		else
			bouncers[spr].y	+= bouncers[spr].my ;

		move_sprite(spr,bouncers[spr].x,bouncers[spr].y);
	}
}


void scroll_sprite1()
{
	UBYTE n ;
	UBYTE nmul ;
	UWORD r,p, xmul, ymul ;

	sprite1iter++ ;
	if ( sprite1iter == 100U )
		sprite1iter = 0 ;

	xmul = 25UL+sprite1iter ;
	while ( xmul > 99 )
		xmul -= 100 ;

	ymul = 0+sprite1iter ;
	while ( ymul > 99 )
		ymul -= 100 ;

	nmul = 0 ;

	for ( n=0 ; n != 7 ; n++ )
	{
		r = xmul ;
		p = ymul ;
		move_sprite(7+n,nmul+spr1_x[r], nmul+spr1_y[p]) ;

		xmul += sprite1_miscx ;
		while ( xmul > 99 )
			xmul -= 100 ;

		ymul += sprite1_miscy ;
		while ( ymul > 99 )
			ymul -= 100 ;
		nmul += 5 ;
	}


}

unsigned char wordsmap38[] = {
	'S'+0x1D, 'H'+0x1D, 'I'+0x1D, 'E'+0x1D, 'L'+0x1D, 'D'+0x1D, 0x5D, 'D'+0x1D, 'A'+0x1D, 'M'+0x1D, 'A'+0x1D, 'G'+0x1D, 'E'+0x1D, 0x5D, 'H'+0x1D, 'I'+0x1D, 'T'+0x1D, 'S'+0x1D  

} ;

void loadit() ;

void write_shoot_stats()
{
	unsigned char shootstats[18] ;
	UBYTE snum, tnum ;

	memset( shootstats, 0x5D, 18UL ) ;

	tnum = ship_shieldpower ;

	snum = tnum / 100 ;

	shootstats[3] = snum + (0x5D + 27) ;

	tnum = tnum - ( snum * 100 ) ;

	snum = tnum / 10 ;

	shootstats[4] = snum + (0x5D + 27) ;

	snum = tnum - ( snum * 10 ) ;

	shootstats[5] = snum + (0x5D + 27) ;


	tnum =  total_earth_hits ;

	snum = tnum / 100 ;

	shootstats[10] = snum + (0x5D + 27) ;

	tnum = tnum - ( snum * 100 ) ;

	snum = tnum / 10 ;

	shootstats[11] = snum + (0x5D + 27) ;

	snum = tnum - ( snum * 10 ) ;

	shootstats[12] = snum + (0x5D + 27) ;

	tnum =  total_enemies_hit ;

	snum = tnum / 100 ;

	shootstats[15] = snum + (0x5D + 27) ;

	tnum = tnum - ( snum * 100 ) ;

	snum = tnum / 10 ;

	shootstats[16] = snum + (0x5D + 27) ;

	snum = tnum - ( snum * 10 ) ;

	shootstats[17] = snum + (0x5D + 27) ;


	set_bkg_tiles( 19, 0, 1, 18, shootstats) ;


}

void shoot_main()
{
	UBYTE i ;

	inside=10 ;


	disable_interrupts2();
	changemusic = 23 ;
	DISPLAY_OFF;


	LCDC_REG = 0x47;
	SPRITES_8x16 ;
	BGP_REG = 0xE4U;
	OBP0_REG = OBP1_REG = 0x24 ;

//  set_bkg_data(0x00, sizeof(deathtiles)/16, deathtiles);
//  set_bkg_tiles(0,0,20,18,deathmap) ;

	SCX_REG=0 ;
	SCY_REG=0 ;

	WX_REG = MAXWNDPOSX;
	WY_REG = MAXWNDPOSY;



//  waitpad(J_START) ;
//  waitpadup() ;  

	SWITCH_RAM_MBC5(3) ;
	remoteCall( 36, 38, fillup ) ;


	remoteCall( 36, 37, init_vars ) ;


	//init_vars() ;


	set_bkg_palette( 7, 1, &bkg_p2[28] );
	set_bkg_palette( 6, 1, &bkg_p2[24] );
	set_bkg_palette( 5, 1, &bkg_p2[20] );
	set_bkg_palette( 4, 1, &bkg_p2[16] );
	set_bkg_palette( 3, 1, &bkg_p2[12] );
	set_bkg_palette( 2, 1, &bkg_p2[8] );
	set_bkg_palette( 1, 1, &bkg_p2[4] );
	set_bkg_palette( 0, 1, &bkg_p2[0] );
	set_sprite_palette( 0, 1, &obj_p2[0] );
	set_sprite_palette( 1, 1, &obj_p2[4] );
	set_sprite_palette( 2, 1, &obj_p2[8] );
	set_sprite_palette( 3, 1, &obj_p2[12] );
	set_sprite_palette( 4, 1, &obj_p2[16] );
	set_sprite_palette( 5, 1, &obj_p2[20] );
	set_sprite_palette( 6, 1, &obj_p2[24] );
	set_sprite_palette( 7, 1, &obj_p2[28] );



	remoteCall( 36, 38, loadtiles ) ;


	loadit() ;
	set_bkg_tiles( 18, 0, 1, 18, wordsmap38 ) ;


	twinkle1_frame[0] = 0 ;
	twinkle1_frame[1] = 1 ;
	twinkle1_frame[2] = 2 ;
	twinkle2_frame[0] = 0 ;
	twinkle2_frame[1] = 1 ;
	twinkle2_frame[2] = 2 ;
	twinkle = 0 ;



	DISPLAY_ON;
	enable_interrupts2();



	move_sprite(0,*shippos,*(shippos+1)) ;
	move_sprite(1,(*shippos)+8,*(shippos+1)) ;
	gen1 = *(shippos+2)*3 ;
	set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
	set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
	set_sprite_prop(0,ship_frames[gen1+2]|S_PALETTE) ;
	set_sprite_prop(1,ship_frames[gen1+2]|S_PALETTE) ;



//  ship_isinvincible = 0x02 ;
//	remoteCall( 36, 37, put_new_power ) ;

	//endgamegood() ;

	while ( 1 )
	{
		if ( ship_isdead )
		{
			switch ( ship_isdead )
			{
				case 0x80 : 
					{
						set_sprite_tile(0,0xE8) ;
						set_sprite_tile(1,0xEA) ;
						set_sprite_prop(0,0) ;
						set_sprite_prop(1,0) ;
						break ;
					}
				case 0x70 : 
					{
						set_sprite_tile(0,0xEC) ;
						set_sprite_tile(1,0xEE) ;
						break ;
					}
				case 0x60 : 
					{
						set_sprite_tile(0,0xF0) ;
						set_sprite_tile(1,0xF2) ;
						break ;
					}
				case 0x50 : 
					{
						set_sprite_tile(0,0xF4) ;
						set_sprite_tile(1,0xF6) ;
						break ;
					}
				case 0x40 : 
					{
						set_sprite_tile(0,0xFE) ;
						set_sprite_tile(1,0xFE) ;
						break ;
					}
				case 0x01 : 
					{
						gen1 = *(shippos+2)*3 ;
						set_sprite_prop(0,ship_frames[gen1+2]|S_PALETTE) ;
						set_sprite_prop(1,ship_frames[gen1+2]|S_PALETTE) ;
						ship_isinvincible = 0x80 ;
						ship_shieldpower = 0xFF ;
						break ;
					}
			}
			ship_isdead-- ;


		}


		if ( enemy_wait-- == 0 )
			remoteCall( 36, 37, put_new_enemy ) ;

//	power_wait=0UL ;
		if ( power_wait-- == 0 )
		{
			//while(1) ; 
			remoteCall( 36, 37, put_new_power ) ;
		}


		if ( earth_shieldon )
		{
			earth_shieldon-- ;
			if ( !earth_shieldon )
				earth_shield_off() ;
		}

		if ( twinkle--==0 )
		{
			remoteCall( 36, 38, dotwinkle ) ;
			twinkle = 4 ;
		}


		remoteCall( 36, 37, scroll_enemies_power ) ;


		if ( flipflop==0 )
			remoteCall( 36, 37, scroll_enemy_ammo ) ;
		else
			if ( flipflop==1 )
			remoteCall( 36, 37, check_enemy_collision ) ;
		else
			if ( flipflop==2 )
		{
			remoteCall( 36, 37, scroll_player1_ammo ) ;
			remoteCall( 36, 37, scroll_player1_ammo ) ;
			remoteCall( 36, 37, scroll_player1_ammo ) ;
			remoteCall( 36, 37, scroll_player1_ammo ) ;
		}
		else
			remoteCall( 36, 37, check_player1_collision ) ;



		//   remoteCall( 36, 37, scroll_enemy_ammo ) ;
		//    remoteCall( 36, 37, check_enemy_collision ) ;
		//     remoteCall( 36, 37, scroll_player1_ammo ) ;
		//   remoteCall( 36, 37, check_player1_collision ) ;


		//if ( total_earth_hits & 0x10 )
		//{
		//endgamebad() ;

		//}

		if ( !(joykeys&J_A) )
			if ( ship_shieldwait==0 )
			{
				if ( ship_shieldpower!=0xFF )
					ship_shieldpower++ ;
				ship_shieldwait = 3 ;
			}
			else
				ship_shieldwait-- ;

		if ( animate_wait==0 )
		{
			remoteCall( 36, 37, animate ) ;
			animate_wait = 10 ;
		}
		else
			animate_wait-- ;
		if ( !flipflop )
		{
			flipflop=3 ;
			OBP1_REG = 0xA4 ; 
		}
		else
		{
			flipflop-=1 ;
			OBP1_REG = 0x24 ;
		}

		write_shoot_stats() ;

		joykeys =joypad() ;



		if ( !ship_isdead )
		{
			if ( (joykeys&J_START) && (joykeys&J_LEFT) )
			{
				if ( lastkey==joykeys )
				{
					wait_vbl_done() ;
					continue ;
				}
				if ( shipframe_offset==35 )
					shipframe_offset = 0 ;
				else
					shipframe_offset++; 
				gen1 = *(shippos+2) + shipframe_offset ;
				if ( gen1 > 35 )
					gen1 -= 35 ;
				gen1 = gen1 + gen1 + gen1 ;
				set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
				set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
				set_sprite_prop(0,ship_frames[gen1+2]|S_PALETTE) ;
				set_sprite_prop(1,ship_frames[gen1+2]|S_PALETTE) ;


				lastkey = joykeys ;
				wait_vbl_done() ;
				continue ; 
			}
			if ( (joykeys&J_START) && (joykeys&J_RIGHT) )
			{
				if ( lastkey==joykeys )
				{
					wait_vbl_done() ;
					continue ;
				}
				if ( shipframe_offset==0 )
					shipframe_offset = 35 ;
				else
					shipframe_offset--; 

				gen1 = *(shippos+2) + shipframe_offset ;
				if ( gen1 > 35 )
					gen1 -= 35 ;
				gen1 = gen1 + gen1 + gen1 ;
				set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
				set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
				set_sprite_prop(0,ship_frames[gen1+2]|S_PALETTE) ;
				set_sprite_prop(1,ship_frames[gen1+2]|S_PALETTE) ;


				lastkey = joykeys ;
				wait_vbl_done() ;
				continue ;
			}
			if ( joykeys&J_LEFT )
				ship_direction = 0 ;
			else
				if ( joykeys&J_RIGHT )
				ship_direction = 1 ;
			else
				ship_direction = 2 ;
			if ( ship_direction==0 )
			{
				shippos+=3 ;
				if ( *shippos==0 )
					shippos = shipmotion ;
			}
			else
				if ( ship_direction==1 )
			{
				if ( shippos==shipmotion )
					shippos=shipmotion+570 ;
				else
					shippos-=3 ;
			}

			gen1 = *(shippos+2) + shipframe_offset ;
			if ( gen1 > 35 )
				gen1 -= 35 ;
			gen1 = gen1 + gen1 + gen1 ;
//        gen1 = *(shippos+2)*3 ;
			if ( (joykeys&J_LEFT) || (joykeys&J_RIGHT) )
			{
				move_sprite(0,*shippos,*(shippos+1)) ;
				move_sprite(1,(*shippos)+8,*(shippos+1)) ;
				set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
				set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
				set_sprite_prop(0,ship_frames[gen1+2]|S_PALETTE) ;
				set_sprite_prop(1,ship_frames[gen1+2]|S_PALETTE) ;
			}

			if ( joykeys&J_B )
			{
				ship_shooting = 1 ;
				ship_shieldon = 0 ;
				ship_offset = 40 ;
				set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
				set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
			}
			else
				if ( joykeys&J_A && ship_shieldpower )
			{
				if ( ship_shooting )
					ship_fireaway() ;
				ship_shooting = 0 ;
				ship_shieldon = 1 ;
				ship_offset = 80 ;
				set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
				set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
				ship_shieldpower-- ;
			}
			else
			{
				if ( ship_shooting )
					ship_fireaway() ;
				ship_shooting = 0 ;
				ship_shieldon = 0 ;
				ship_offset = 0 ;
				set_sprite_tile(0,ship_frames[gen1]+ship_offset) ;
				set_sprite_tile(1,ship_frames[gen1+1]+ship_offset) ;
			}
		}
		if ( ship_isinvincible )
		{
			if ( ship_isinvincible &0x01 )
			{
				set_sprite_tile(0,0xFE) ;
				set_sprite_tile(1,0xFE) ;
			}
			ship_isinvincible-- ;
		}

		if ( (joykeys&J_SELECT) && (!(lastkey&J_SELECT)) )
		{

		}
		lastkey = joykeys ;
//       delay(3) ;
		wait_vbl_done() ;
//     wait_vbl_done() ;
	}

}
