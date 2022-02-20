#include <gb.h>


//#include "allall2.dat" 


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

#define ship_shield ship_shield2
#define ship_reg ship_reg2
#define shipmotion shipmotion2
#define ship_frames ship_frames2
#define twinkle_tile twinkle_tile2
#define twinkle1_locs twinkle1_locs2
#define twinkle2_locs twinkle2_locs2
#define twinkle1_map twinkle1_map2
#define twinkle2_map twinkle2_map2
#define ammotiles ammotiles2
#define explosiondata explosiondata2
#define enemyframes enemyframes2
#define levelStats levelStats2
#define enemies_to_come enemies_to_come2
#define powers_to_come powers_to_come2
#define shipfiredir shipfiredir2
*/
/*
#define ship_shield ((unsigned char*)(0xBE0D))
#define ship_reg ((unsigned char*)(0xC08D))
#define shipmotion ((UBYTE*)(0xC30D))
#define ship_frames ((UBYTE*)(0xC54F))
#define twinkle_tile ((unsigned char*)(0xC5BB))
#define twinkle1_locs ((unsigned char*)(0xC60B))
#define twinkle2_locs ((unsigned char*)(0xC611))
#define twinkle1_map ((unsigned char*)(0xC617))
#define twinkle2_map ((unsigned char*)(0xC61B))
#define ammotiles ((unsigned char*)(0xC61F))
#define explosiondata ((unsigned char*)(0xC6DF))
#define enemyframes ((UBYTE*)(0xC8DF))
#define levelStats ((struct Level_stats *)(0xC8ED))
#define enemies_to_come ((struct Enemy_Sequence*)(0xC95D))
#define powers_to_come ((struct Power_Sequence*)(0xCF53))
#define shipfiredir ((BYTE*)(0xCFD7))
*/

extern UBYTE gen1 ;
extern UBYTE gen2 ;
extern UBYTE gen3 ;


extern UBYTE curr_rand ;

extern UBYTE numenemyfire ;
extern UBYTE numplayer1fire ;
extern UBYTE numplayer2fire ;

extern UBYTE total_earth_hits ;

extern UBYTE total_enemies_hit ;

extern UBYTE countdown ;
extern UWORD enemy_wait ;
extern UWORD power_wait ;

extern UBYTE shipframe_offset ;
extern UBYTE animate_wait ;

extern UBYTE curr_rand ;

extern UBYTE numenemyfire ;
extern UBYTE numplayer1fire ;
extern UBYTE numplayer2fire ;


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

struct Power_Stats
{
	UBYTE in_use ;	   //Is it active? also holds type of powerup
	UBYTE *curr_loc ;  //pointer into it's motion array
	UBYTE motion_offsetx ;
	UBYTE motion_offsety ;
	UBYTE speed ;
	UBYTE motionnum ;
} ;

extern struct Enemy_Stats enemies_on_screen[6] ;

extern struct Power_Stats power_on_screen ;


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

//motionnum :  0x80 = flip x, y coords     (origmotion&0x40)+1 = reverse course


struct Enemy_Sequence enemies_to_come[] = {




	{0x150, 0x00, 0, 0, 8, 0x0},  //left to right line on top
	{0x010, 0x00, 1, 0, 8, 0x0},
	{0x010, 0x00, 2, 0, 8, 0x0},
	{0x010, 0x00, 3, 0, 8, 0x0},
// {0x010, 0x00, 4, 0, 8, 0x0 },
// {0x010, 0x00, 5, 0, 8, 0x0 },


	{0x180, 0x00, 0, 0, 138, 0x41},	 //right to left bottom
	{0x010, 0x00, 1, 0, 138, 0x41},
	{0x010, 0x00, 2, 0, 138, 0x41},
	{0x010, 0x00, 3, 0, 138, 0x41},
	{0x010, 0x00, 4, 0, 138, 0x41},
// {0x010, 0x00, 5, 0, 138, 0x41 },

	{0x180, 0x01, 0, 0, 0, 0x80},  //top to bottom left
	{0x010, 0x01, 1, 0, 0, 0x80},
	{0x010, 0x01, 2, 0, 0, 0x80},
	{0x010, 0x01, 3, 0, 0, 0x80},
	{0x010, 0x01, 4, 0, 0, 0x80},
	{0x010, 0x01, 5, 0, 0, 0x80},

	{0x180, 0x01, 0, 0, 130, 0xC1},	//bottom to top right
	{0x010, 0x01, 1, 0, 130, 0xC1},
	{0x010, 0x01, 2, 0, 130, 0xC1},
	{0x010, 0x01, 3, 0, 130, 0xC1},
	{0x010, 0x01, 4, 0, 130, 0xC1},
	{0x010, 0x01, 5, 0, 130, 0xC1},

	{0x180, 0x01, 0, 0, 8, 0x0},  //straight line from all 4 corners
	{0x1, 0x01, 1, 0, 138, 0x41},
	{0x1, 0x00, 2, 0, 0, 0x80},
	{0x1, 0x00, 3, 0, 130, 0xC1},

	{0x180, 0x01, 0, 0, 0, 0x80},  //3 up 3 down line on left
	{0x01, 0x01, 1, 0, 0, 0xC1},
	{0x010, 0x01, 2, 0, 0, 0x80},
	{0x01, 0x01, 3, 0, 0, 0xC1},
	{0x010, 0x01, 4, 0, 0, 0x80},
	{0x01, 0x01, 5, 0, 0, 0xC1},

	{0x180, 0x01, 0, 0, 130, 0xC1},	 //3 up/down on right
	{0x01, 0x01, 1, 0, 130, 0x80},
	{0x010, 0x01, 2, 0, 130, 0xC1},
	{0x01, 0x01, 3, 0, 130, 0x80},
	{0x010, 0x01, 4, 0, 130, 0xC1},
	{0x01, 0x01, 5, 0, 130, 0x80},

// {0x180, 0x01, 0, 0, 8, 0x41 },  //3 r->l/top, t->b/left upperright corner
// {0x01, 0x00, 1, 0, 130, 0x80 },
// {0x010, 0x01, 2, 0, 8, 0x41 },
// {0x01, 0x00, 3, 0, 130, 0x80 },
// {0x010, 0x01, 4, 0, 8, 0x41 },
// {0x01, 0x00, 5, 0, 130, 0x80 },

// {0x180, 0x01, 0, 0, 0, 0xC1 },  // opposite of previous
	//{0x01, 0x00, 1, 0, 138, 0x0 },
	//{0x010, 0x01, 2, 0, 0, 0xC1 },
	//{0x01, 0x00, 3, 0, 138, 0x0 },
	//{0x010, 0x01, 4, 0, 0, 0xC1 },
	//{0x01, 0x00, 5, 0, 138, 0x0 },

	{0x180, 0x01, 0, 0, 0, 0x4},  //12 lower left corner arc/dent
	{0x20, 0x01, 1, 0, 0, 0x4},
	{0x20, 0x01, 2, 0, 0, 0x4},
	{0x20, 0x01, 3, 0, 0, 0x4},
	{0x20, 0x01, 4, 0, 0, 0x4},
	{0x20, 0x01, 5, 0, 0, 0x4},
	{0x20, 0x01, 0, 0, 0, 0x4},
	{0x20, 0x01, 1, 0, 0, 0x4},
	{0x20, 0x01, 2, 0, 0, 0x4},
	{0x20, 0x01, 3, 0, 0, 0x4},
	{0x20, 0x01, 4, 0, 0, 0x4},
	{0x20, 0x01, 5, 0, 0, 0x4},

	{0x70, 0x00, 0, 8, 252, 0x84},	//12 upper right corner arc/dent
	{0x20, 0x00, 1, 8, 252, 0x84},
	{0x20, 0x00, 2, 8, 252, 0x84},
	{0x20, 0x00, 3, 8, 252, 0x84},
	{0x20, 0x00, 4, 8, 252, 0x84},
	{0x20, 0x00, 5, 8, 252, 0x84},
	{0x20, 0x00, 0, 8, 252, 0x84},
	{0x20, 0x00, 1, 8, 252, 0x84},
	{0x20, 0x00, 2, 8, 252, 0x84},
	{0x20, 0x00, 3, 8, 252, 0x84},
	{0x20, 0x00, 4, 8, 252, 0x84},
	{0x20, 0x00, 5, 8, 252, 0x84},

	{0x080, 0x00, 0, 0, 8, 0x0},	//square around screen twice
	{0x010, 0x00, 1, 0, 8, 0x0},	//square around screen twice
	{0x080, 0x00, 2, 0, 130, 0x80},
	{0x010, 0x00, 3, 0, 130, 0x80},
	{0x080, 0x00, 0, 0, 138, 0x41},
	{0x010, 0x00, 1, 0, 138, 0x41},
	{0x080, 0x00, 2, 0, 0, 0xC1},
	{0x010, 0x00, 3, 0, 0, 0xC1},
// {0x080, 0x00, 0, 0, 8, 0x0 },
	//{0x010, 0x00, 1, 0, 8, 0x0 },
	//{0x080, 0x00, 2, 0, 130, 0x80 },
	//{0x010, 0x00, 3, 0, 130, 0x80 },
	//{0x080, 0x00, 0, 0, 138, 0x41 },
	//{0x010, 0x00, 1, 0, 138, 0x41 },
	//{0x080, 0x00, 2, 0, 0, 0xC1 },
	//{0x010, 0x00, 3, 0, 0, 0xC1 },

	{0x080, 0x00, 0, 0, 0, 0x80},  //square around screen twice other direction
	{0x010, 0x00, 1, 0, 0, 0x80},  //square around screen twice other direction
	{0x080, 0x00, 2, 0, 138, 0x0},
	{0x010, 0x00, 3, 0, 138, 0x0},
	{0x080, 0x00, 0, 0, 130, 0xC1},
	{0x010, 0x00, 1, 0, 130, 0xC1},
	{0x080, 0x00, 2, 0, 8, 0x41},
	{0x010, 0x00, 3, 0, 8, 0x41},
	//{0x080, 0x00, 0, 0, 0, 0x80 },
	//{0x010, 0x00, 1, 0, 0, 0x80 },
	//{0x080, 0x00, 2, 0, 138, 0x0 },
	//{0x010, 0x00, 3, 0, 138, 0x0 },
	//{0x080, 0x00, 0, 0, 130, 0xC1 },
	//{0x010, 0x00, 1, 0, 130, 0xC1 },
	//{0x080, 0x00, 2, 0, 8, 0x41 },
	//{0x010, 0x00, 3, 0, 8, 0x41 },

	{0x200, 0xFF, 0, 0, 0, 0x0},
	{0, 0, 0, 0, 0, 0},	 // all zeroes indicate end of level

	{0x010, 0x00, 0, 0, 8, 0x0A},	 //move out, pausers
	{0x01,  0x00, 1, 0, 130, 0x0A},
	{0x180,  0x01, 2, 0, 0, 0x8A},
	{0x01,  0x01, 3, 0, 130, 0x8A},

	//{0x0160, 0x00, 0, 128, 0, 0x6 },  //wavy lines 3 left, 3 right
	//{0x1,  0x00, 1, 0, 0, 0x47 },
	//{0x10,  0x00, 2, 128, 0, 0x6 },
	//{0x1,  0x00, 3, 0, 0, 0x47 },
	//{0x10,  0x00, 4, 128, 0, 0x6 },
	//{0x1,  0x00, 5, 0, 0, 0x47 },

	//{0x150, 0x01, 0, 135, 0, 0x86 }, //wavy lines 3 top 3 bottom
	//{0x1,  0x01, 1, 0, 0, 0xC7 },
	//{0x10,  0x01, 2, 135, 0, 0x86 },
	//{0x1,  0x01, 3, 0, 0, 0xC7 },
	//{0x10,  0x01, 4, 135, 0, 0x86 },
	//{0x1,  0x01, 5, 0, 0, 0xC7 },

	{0x160, 0x00, 0, 8, 252, 0x84},	 //12 upper right corner arc/dent
	{0x20, 0x00, 1, 8, 252, 0x84},
	{0x20, 0x00, 2, 8, 252, 0x84},
	{0x20, 0x00, 3, 8, 252, 0x84},
	{0x01,  0x01, 5, 0, 130, 0xA},
	{0x20, 0x00, 4, 8, 252, 0x84},
	{0x20, 0x00, 0, 8, 252, 0x84},
	{0x20, 0x00, 1, 8, 252, 0x84},
	{0x20, 0x00, 2, 8, 252, 0x84},
	{0x20, 0x00, 3, 8, 252, 0x84},
	{0x20, 0x00, 4, 8, 252, 0x84},
	{0x20, 0x00, 0, 8, 252, 0x84},
	{0x20, 0x00, 1, 8, 252, 0x84},
	{0x20, 0x00, 2, 8, 252, 0x84},
	{0x20, 0x00, 3, 8, 252, 0x84},
	{0x20, 0x00, 4, 8, 252, 0x84},

	//{0x70, 0x01, 0, 0, 0, 0x4 },  //12 lower left corner arc/dent
	//{0x20, 0x01, 1, 0, 0, 0x4 },
	//{0x20, 0x01, 2, 0, 0, 0x4 },
	//{0x20, 0x01, 3, 0, 0, 0x4 },
	//{0x01,  0x00, 5, 0, 130, 0x8A },
	//{0x20, 0x01, 4, 0, 0, 0x4 },
	//{0x20, 0x01, 0, 0, 0, 0x4 },
	//{0x20, 0x01, 1, 0, 0, 0x4 },
	//{0x20, 0x01, 2, 0, 0, 0x4 },
	//{0x20, 0x01, 3, 0, 0, 0x4 },
	//{0x20, 0x01, 4, 0, 0, 0x4 },
	//{0x20, 0x01, 0, 0, 0, 0x4 },
	//{0x20, 0x01, 1, 0, 0, 0x4 },
	//{0x20, 0x01, 2, 0, 0, 0x4 },
	//{0x20, 0x01, 3, 0, 0, 0x4 },
	//{0x20, 0x01, 4, 0, 0, 0x4 },

	{0x080, 0x00, 0, 0, 0, 0x08},  //right orbit
	{0x010, 0x00, 1, 0, 0, 0x08},  
	{0x010, 0x00, 2, 0, 0, 0x08},  
	{0x010, 0x00, 3, 0, 0, 0x08},  
	{0x010, 0x00, 4, 0, 0, 0x08},  

	{0x0B0, 0x01, 0, 0, 0, 0x02},  //left orbit
	{0x010, 0x01, 1, 0, 0, 0x02},  
	{0x010, 0x01, 2, 0, 0, 0x02},  
	{0x010, 0x01, 3, 0, 0, 0x02},  
	{0x010, 0x01, 4, 0, 0, 0x02},  

	{0x0B0, 0x00, 0, 0, 0, 0x88},  //bottom orbit
	{0x010, 0x00, 1, 0, 0, 0x88},  
	{0x010, 0x00, 2, 0, 0, 0x88},  
	{0x010, 0x00, 3, 0, 0, 0x88},  
	{0x010, 0x00, 4, 0, 0, 0x88},  

	{0x0B0, 0x01, 0, 0, 0, 0x82},  //top orbit
	{0x010, 0x01, 1, 0, 0, 0x82},  
	{0x010, 0x01, 2, 0, 0, 0x82},  
	{0x010, 0x01, 3, 0, 0, 0x82},  
	{0x010, 0x01, 4, 0, 0, 0x82},  


	{0x0B0, 0x00, 0, 0, 0, 0x08},  
	{0x01, 0x00, 1, 0, 0, 0x02},  
	{0x010, 0x00, 2, 0, 0, 0x08},  
	{0x01, 0x01, 3, 0, 0, 0x02},  
	{0x010, 0x01, 4, 0, 0, 0x08},  
	{0x01, 0x01, 5, 0, 0, 0x02},  

	{0x0B0, 0x00, 0, 0, 0, 0x88},  
	{0x01, 0x00, 1, 0, 0, 0x82},  
	{0x010, 0x00, 2, 0, 0, 0x88},  
	{0x01, 0x01, 3, 0, 0, 0x82},  
	{0x010, 0x01, 4, 0, 0, 0x88},  
	{0x01, 0x01, 5, 0, 0, 0x82},  


// {0x0F0, 0x00, 0, 0, 0, 0x08 },  //orbit from all 4 corners
// {0x01, 0x00, 1, 0, 0, 0x88 },
// {0x01, 0x00, 2, 0, 0, 0x02 },
// {0x01, 0x00, 3, 0, 0, 0x82 },


	{0x0F0, 0x00, 0, 0, 8, 0x0},  //left to right line on top
	{0x010, 0x00, 1, 0, 8, 0x0},
	{0x010, 0x00, 2, 0, 8, 0x0},

	{0x020, 0x00, 3, 0, 8, 0x41},  //right to left on top
	{0x010, 0x00, 4, 0, 8, 0x41},
	{0x010, 0x00, 5, 0, 8, 0x41},

	{0x110, 0x00, 0, 0, 138, 0x41},	 //right to left bottom
	{0x010, 0x00, 1, 0, 138, 0x41},
	{0x010, 0x00, 2, 0, 138, 0x41},
	{0x010, 0x01, 3, 0, 0, 0x80},  //top to bottom left
	{0x010, 0x01, 4, 0, 0, 0x80},
	{0x010, 0x01, 5, 0, 0, 0x80},

	{0x110, 0x00, 0, 0, 8, 0x0},  //left to right line on top
	{0x010, 0x00, 1, 0, 8, 0x0},
	{0x010, 0x00, 2, 0, 8, 0x0},
	{0x010, 0x01, 3, 0, 130, 0xC1},	//bottom to top right
	{0x010, 0x01, 4, 0, 130, 0xC1},
	{0x010, 0x01, 5, 0, 130, 0xC1},


	{0x0F0, 0x00, 0, 0, 8, 0x00}, 
	{0x010, 0x01, 1, 0, 0, 0x02}, 
	{0x010, 0x00, 2, 0, 0, 0x04}, 
	{0x010, 0x01, 3, 0, 0, 0x06}, 
	{0x010, 0x00, 4, 0, 0, 0x08}, 
	{0x010, 0x01, 5, 0, 8, 0x0A}, 



	{0x190, 0xFF, 0, 0, 0, 0x0},
	{0, 0, 0, 0, 0, 0},	 // all zeroes indicate end of level

	{0x180,  0x00, 0, 0, 0, 0x08},  
	{0x1, 0x00, 1, 0, 0, 0x49},	   //reverse course of 0x08 - right orbit
	{0x038, 0x00, 2, 0, 0, 0x08},  
	{0x01, 0x00, 3, 0, 0, 0x49},  
	{0x038, 0x00, 4, 0, 0, 0x08},  
	{0x01, 0x00, 5, 0, 0, 0x49},  
	{0x038, 0x00, 0, 0, 0, 0x08},  
	{0x01, 0x00, 1, 0, 0, 0x49},  
	{0x038, 0x00, 2, 0, 0, 0x08},  
	{0x01, 0x00, 3, 0, 0, 0x49},  
	{0x038, 0x00, 4, 0, 0, 0x08},  
	{0x01, 0x00, 5, 0, 0, 0x49},  
	{0x038, 0x00, 0, 0, 0, 0x08},  
	{0x01, 0x00, 1, 0, 0, 0x49},  

	{0x180,  0x01, 0, 0, 0, 0x02},  
	{0x1, 0x01, 1, 0, 0, 0x43},	 //reverse course of 0x02 - left orbit
	{0x038, 0x01, 2, 0, 0, 0x02},  
	{0x01, 0x01, 3, 0, 0, 0x43},  
	{0x038, 0x01, 4, 0, 0, 0x02},  
	{0x01, 0x01, 5, 0, 0, 0x43},  
	{0x038, 0x01, 0, 0, 0, 0x02},  
	{0x01, 0x01, 1, 0, 0, 0x43},  
	{0x038, 0x01, 2, 0, 0, 0x02},  
	{0x01, 0x01, 3, 0, 0, 0x43},  
	{0x038, 0x01, 4, 0, 0, 0x02},  
	{0x01, 0x01, 5, 0, 0, 0x43},  
	{0x038, 0x01, 0, 0, 0, 0x02},  
	{0x01, 0x01, 1, 0, 0, 0x43},  

	{0x180, 0x00, 0, 0, 8, 0x0A},	 //move out, pausers
	{0x01,  0x00, 1, 0, 130, 0x0A},
	{0x180,  0x01, 2, 0, 0, 0x8A},
	{0x01,  0x01, 3, 0, 130, 0x8A},

	{0x180, 0x00, 0, 0, 4, 0x0},  //left to right line on top
	{0x001, 0x01, 1, 0, 20, 0x0},
	{0x010, 0x00, 2, 0, 4, 0x0},
	{0x001, 0x01, 3, 0, 20, 0x0},  //left to right line on top
	{0x010, 0x00, 4, 0, 4, 0x0},
	{0x001, 0x01, 5, 0, 20, 0x0},




	{0x110, 0x00, 0, 0, 0, 0x08},  //right orbit
	{0x01A, 0x01, 1, 0, 130, 0xC1},	//bottom to top right
	{0x01A, 0x00, 2, 0, 0, 0x08},  
	{0x01A, 0x01, 3, 0, 130, 0xC1},
	{0x01A, 0x00, 4, 0, 0, 0x08},  
	{0x01A, 0x01, 5, 0, 130, 0xC1},
	{0x01A, 0x00, 0, 0, 0, 0x08},  //right orbit
	{0x01A, 0x01, 1, 0, 130, 0xC1},	//bottom to top right
	{0x01A, 0x00, 2, 0, 0, 0x08},  
	{0x01A, 0x01, 3, 0, 130, 0xC1},
	{0x01A, 0x00, 4, 0, 0, 0x08},  
	{0x01A, 0x01, 5, 0, 130, 0xC1},



	{0x110, 0x00, 0, 0, 0, 0x43},  //right orbit
	{0x01A, 0x01, 1, 0, 0, 0x80}, //bottom to top right
	{0x01A, 0x00, 2, 0, 0, 0x43},  
	{0x01A, 0x01, 3, 0, 0, 0x80},
	{0x01A, 0x00, 4, 0, 0, 0x43},  
	{0x01A, 0x01, 5, 0, 0, 0x80},
	{0x01A, 0x00, 0, 0, 0, 0x43},  //right orbit
	{0x01A, 0x01, 1, 0, 0, 0x80}, //bottom to top right
	{0x01A, 0x00, 2, 0, 0, 0x43},  
	{0x01A, 0x01, 3, 0, 0, 0x80},
	{0x01A, 0x00, 4, 0, 0, 0x43},  
	{0x01A, 0x01, 5, 0, 0, 0x80},



	{0x110, 0x00, 0, 0, 8, 0x0},	//square around screen 
	{0x010, 0x00, 1, 0, 8, 0x0},    
	{0x010, 0x00, 2, 0, 8, 0x0},    
	{0x028, 0x01, 3, 0, 130, 0x80},
	{0x010, 0x01, 4, 0, 130, 0x80},
	{0x010, 0x01, 5, 0, 130, 0x80},
	{0x028, 0x00, 0, 0, 138, 0x41},
	{0x010, 0x00, 1, 0, 138, 0x41},
	{0x010, 0x00, 2, 0, 138, 0x41},
	{0x028, 0x01, 3, 0, 0, 0xC1},
	{0x010, 0x01, 4, 0, 0, 0xC1},
	{0x010, 0x01, 5, 0, 0, 0xC1},



	{0x110, 0xFF, 0, 0, 0, 0x0},
	{0, 0, 0, 0, 0, 0},	 // all zeroes indicate end of level
	{0x010, 0x00, 0, 0, 8, 0x0},
	{0x090, 0xFF, 0, 0, 0, 0x0},
	{0, 0, 0, 0, 0, 0},	 // all zeroes indicate end of level
	{0x010, 0x00, 0, 0, 8, 0x0},
	{0x090, 0xFF, 0, 0, 0, 0x0},
	{0, 0, 0, 0, 0, 0},	 // all zeroes indicate end of level
	{0, 0, 0, 0, 0, 0},	 // all zeroes indicate end of level
	{0, 0, 0, 0, 0, 0}	// all zeroes as first entry in level means end of all levels
} ;

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

extern struct Enemy_Sequence *enemyptr ;
extern struct Power_Sequence *powerptr ;


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


extern struct ammo_stats enemy_ammo[] ;
extern struct ammo_stats player1_ammo[] ;
extern struct ammo_stats player2_ammo[] ;

//UBYTE ammo_locs[70] ;   //(x,y,deltax,deltay,movedx,movedy,inuse?|spritetype)
//UBYTE special_locs[6*5] ;  //(startx,starty,motionpattern,motionframe,inuse?|type)
//0 = power up to 2shot (16 wide)
//1 = power up to cross - goes through everything
//2 = power up to circle - flies faster
//3 = power up to star - fast and goes through everything
//4 = bomb = explode everything on screen
//5 = planet restore
//6 = planet shield

extern UBYTE num_player_shots ;	//number of player shots on screen 
extern UBYTE num_enemy_shots  ;	//number of enemy shots on screen
extern UBYTE num_enemies      ;	//number of enemies on screen

extern UBYTE level ;   //current level the player is on

extern UBYTE flipflop ;

extern UBYTE joykeys ;
extern UBYTE lastkey ;

extern UBYTE *shippos ;

extern UBYTE ship_shieldon ;
extern UBYTE ship_shieldpower ;
extern UBYTE ship_shieldwait ;

extern UBYTE ship_isdead ; 
extern UBYTE ship_isinvincible ;

extern UBYTE ship_shooting ;
extern UBYTE ship_offset ;
extern UWORD earth_shieldon ;
extern UBYTE ship_powerup ;
// 0 = regular
// 1 = double shot (x16)
// 0x40 = cross
// 0x80 = star



extern UBYTE ship_direction ;
extern UBYTE ship_currframe  ;

extern UBYTE earth_state[] ;


void destroy_all_enemies()
{
	struct Enemy_Stats *currenemy ;
	struct ammo_stats *ammo ;

	for ( gen3 = 0 ; gen3 != 6 ; gen3++ )
	{
		currenemy = enemies_on_screen+gen3 ;
		if ( currenemy->in_use==1 )
		{
			total_enemies_hit++ ;
			currenemy->in_use = 2 ;
			currenemy->curr_frame = enemyframes ;
			set_sprite_tile(28+gen3+gen3,0xE8) ;
			set_sprite_tile(29+gen3+gen3,0xEA) ;
//        currenemy->in_use = 0 ;
//        move_sprite(28+gen3+gen3,0,0) ;
//        move_sprite(29+gen3+gen3,0,0) ;
		}
	}


	for ( gen3=0 ; gen3 != 3 ; gen3++ )	 //enemy firepower
	{
		ammo = player1_ammo+gen3 ;
		if ( ammo->atype )
		{
			ammo->atype = 0 ;
			move_sprite(7+gen3,0,0) ;
			numplayer1fire-- ;
		}
	}
	for ( gen3=0 ; gen3 != 5 ; gen3++ )	 //enemy firepower
	{
		ammo = enemy_ammo+gen3 ;
		if ( ammo->atype )
		{
			ammo->atype = 0 ;
			move_sprite(23+gen3,0,0) ;
			numenemyfire-- ;
		}
	}

}

void earth_shield_on() ;

void check_player1_collision()
{
	struct ammo_stats *currammo ;
	struct Enemy_Stats *currenemy ;
	UBYTE upperx, lowerx, uppery, lowery ;
	UBYTE *locptr ;

	gen1 = 0 ;
	while ( gen1!=3 )
	{
		currammo = player1_ammo + gen1 ;
		if ( currammo->atype )
		{
			gen2 = 0 ;
			while ( gen2!=6 )
			{
				currenemy = enemies_on_screen+gen2 ;
				if ( currenemy->in_use==1 )
				{
					locptr = currenemy->curr_loc ;
					if ( currenemy->motionnum&0x80 )
					{
						lowery = *locptr-7+currenemy->motion_offsetx ;
						lowerx = *(locptr+1)-7+currenemy->motion_offsety ;
					}
					else
					{
						lowerx = *locptr-7+currenemy->motion_offsetx ;
						lowery = *(locptr+1)-7+currenemy->motion_offsety ;
					}

					upperx = lowerx+26 ;
					uppery = lowery+26 ;

					if ( (currammo->x > lowerx) && 
						 (currammo->x < upperx) &&
						 (currammo->y > lowery) &&
						 (currammo->y < uppery) )
					{
						currammo->atype = 0 ;
						move_sprite(7+gen1,0,0) ;
						numplayer1fire-- ;
						if ( --(currenemy->numhits) ==0 )
						{
							total_enemies_hit++ ;
							currenemy->in_use = 2 ;
							currenemy->curr_frame = enemyframes ;
							set_sprite_tile(28+gen2+gen2,0xE8) ;
							set_sprite_tile(29+gen2+gen2,0xEA) ;
						}
						gen2 = 4 ; 
					}

				}
				gen2++ ;
			}
			if ( power_on_screen.in_use )
			{
				locptr = power_on_screen.curr_loc ;
				if ( power_on_screen.motionnum&0x80 )
				{
					lowery = *locptr-7+power_on_screen.motion_offsetx ;
					lowerx = *(locptr+1)-7+power_on_screen.motion_offsety ;
				}
				else
				{
					lowerx = *locptr-7+power_on_screen.motion_offsetx ;
					lowery = *(locptr+1)-7+power_on_screen.motion_offsety ;
				}
				upperx = lowerx+22 ;
				uppery = lowery+22 ;

				if ( (currammo->x > lowerx) && 
					 (currammo->x < upperx) &&
					 (currammo->y > lowery) &&
					 (currammo->y < uppery) )
				{
					move_sprite(6,0,0) ;
					move_sprite(5,0,0) ;
					currammo->atype = 0 ;
					move_sprite(7+gen1,0,0) ;
					numplayer1fire-- ;
					if ( power_on_screen.in_use == 0x02 )
						destroy_all_enemies() ;
					else
						if ( power_on_screen.in_use == 0x03 )
					{
						earth_shieldon = 1524 ;
						remoteCall( 37, 36, earth_shield_on ) ;
					}
					power_on_screen.in_use = 0 ;
				}

			}


		}
		gen1++ ;
	}
}

void check_enemy_collision()
{
	struct ammo_stats *currammo ;
	struct Enemy_Stats *currenemy ;
	UBYTE upperx, lowerx, uppery, lowery ;
	UBYTE *locptr ;

	if ( ship_isdead )
	{
		for ( gen1=0 ; gen1 != 5 ; gen1++ )
		{
			currammo = enemy_ammo + gen1 ;
			currammo->atype = 0 ;
			move_sprite(23+gen1,0,0) ;
		}
		numenemyfire=0 ;
		return ;
	}

	lowerx = *shippos-4;
	lowery = *(shippos+1)-4 ;
	upperx = lowerx+19 ;
	uppery = lowery+19 ;

	for ( gen1=0 ; gen1 != 5 ; gen1++ )
	{
		currammo = enemy_ammo + gen1 ;
		if ( currammo->atype )
		{
			if ( (currammo->x > lowerx) && 
				 (currammo->x < upperx) &&
				 (currammo->y > lowery) &&
				 (currammo->y < uppery) )
			{
				numenemyfire-- ;
				currammo->atype = 0 ;
				move_sprite(23+gen1,0,0) ;
				if ( (!ship_shieldon) && (!ship_isinvincible) &&(!ship_isdead) && (!earth_shieldon) )
				{
					ship_isdead = 0x80 ;
					gen1 = 4 ;
				}


			}
		}
	}


	for ( gen1=0 ; gen1 != 5 ; gen1++ )
	{
		currammo = enemy_ammo + gen1 ;
		if ( currammo->atype )
		{
			if ( earth_shieldon )
				if ( ((currammo->x > 48) && 
					  (currammo->x < 96) &&
					  (currammo->y > 48) &&
					  (currammo->y < 120) ) ||
					 ((currammo->x > 40) && 
					  (currammo->x < 112) &&
					  (currammo->y > 56) &&
					  (currammo->y < 104) ) )
				{
					numenemyfire-- ;
					currammo->atype = 0 ;
					move_sprite(23+gen1,0,0) ;
					continue ;
				}

			if ( ((currammo->x > 56) && 
				  (currammo->x < 96) &&
				  (currammo->y > 56) &&
				  (currammo->y < 112) ) ||
				 ((currammo->x > 48) && 
				  (currammo->x < 104) &&
				  (currammo->y > 64) &&
				  (currammo->y < 104) ) )
			{
				lowerx = hitearth[(currammo->x-49)<<1] ;
				upperx = hitearth[((currammo->x-49)<<1)+1] ;
				lowery = hitearth[(currammo->y-57)<<1] ;
				uppery = hitearth[((currammo->y-57)<<1)+1] ;

				gen2 = (lowery<<2)+(lowery<<1)+lowerx ;
				if ( earth_state[gen2] )
				{
					earth_state[gen2]-- ;
					if ( earth_state[gen2] )
						set_bkg_data(0x09+hittile[gen2], 0x01, earth1+((3L-(UWORD)earth_state[gen2])<<9L)+((UWORD)hittile[gen2]<<4L) );
					else
						set_bkg_data(0x09+hittile[gen2], 0x01, std_data);

					numenemyfire-- ;
					currammo->atype = 0 ;
					move_sprite(23+gen1,0,0) ;
					total_earth_hits++ ;
					continue ;
				}
				else
				{
					gen2 = (lowery<<2)+(lowery<<1)+upperx ;
					if ( earth_state[gen2] )
					{
						earth_state[gen2]-- ;
						if ( earth_state[gen2] )
							set_bkg_data(0x09+hittile[gen2], 0x01, earth1+((3L-(UWORD)earth_state[gen2])<<9L)+((UWORD)hittile[gen2]<<4L) );
						else
							set_bkg_data(0x09+hittile[gen2], 0x01, std_data);
						numenemyfire-- ;
						currammo->atype = 0 ;
						move_sprite(23+gen1,0,0) ;
						total_earth_hits++ ;
						continue ;
					}
					else
					{
						gen2 = (uppery<<2)+(uppery<<1)+lowerx ;
						if ( earth_state[gen2] )
						{
							earth_state[gen2]-- ;
							if ( earth_state[gen2] )
								set_bkg_data(0x09+hittile[gen2], 0x01, earth1+((3L-(UWORD)earth_state[gen2])<<9L)+((UWORD)hittile[gen2]<<4L) );
							else
								set_bkg_data(0x09+hittile[gen2], 0x01, std_data);
							numenemyfire-- ;
							currammo->atype = 0 ;
							move_sprite(23+gen1,0,0) ;
							total_earth_hits++ ;
							continue ;
						}
						else
						{
							gen2 = (uppery<<2)+(uppery<<1)+upperx ;
							if ( earth_state[gen2] )
							{
								earth_state[gen2]-- ;
								if ( earth_state[gen2] )
									set_bkg_data(0x09+hittile[gen2], 0x01, earth1+((3L-(UWORD)earth_state[gen2])<<9L)+((UWORD)hittile[gen2]<<4L) );
								else
									set_bkg_data(0x09+hittile[gen2], 0x01, std_data);
								numenemyfire-- ;
								currammo->atype = 0 ;
								move_sprite(23+gen1,0,0) ;
								total_earth_hits++ ;
								continue ;
							}
							else
							{
							}
						}
					}
				}


			}
		}
	}

}

void scroll_enemy_ammo()
{
	UBYTE donex, doney ;
	struct ammo_stats *ammo ;

	for ( gen1=0 ; gen1 != 5 ; gen1++ )	 //enemy firepower
	{
		ammo = enemy_ammo+gen1 ;
		if ( ammo->atype )
		{
			donex = doney =0 ;
			if ( ammo->deltax != ammo->movedx )
				if ( ammo->deltax < ammo->movedx )
				{
					ammo->movedx-- ;
					ammo->x-- ;
				}
				else
				{
					ammo->movedx++ ;
					ammo->x++ ;
				}
			else
				donex = 1 ;

			if ( ammo->deltay != ammo->movedy )
				if ( ammo->deltay < ammo->movedy )
				{
					ammo->movedy-- ;
					ammo->y-- ;
				}
				else
				{
					ammo->movedy++ ;
					ammo->y++ ;
				}
			else
				doney = 1 ;

			if ( donex && doney )
			{
				ammo->movedx = 0 ;
				ammo->movedy = 0 ;
			}
			if ( (ammo->x ==0) || (ammo->x==143) ||
				 (ammo->y ==0) || (ammo->y==151) )
			{
				ammo->atype = 0 ;
				move_sprite(23+gen1,0,0) ;
				numenemyfire-- ;
			}
			else
				move_sprite(23+gen1,ammo->x,ammo->y) ;
		}
	}
}

void scroll_player1_ammo()
{
	UBYTE donex, doney ;
	struct ammo_stats *ammo ;

	for ( gen1=0 ; gen1 != 3 ; gen1++ )	 //enemy firepower
	{
		ammo = player1_ammo+gen1 ;
		if ( ammo->atype )
		{
			donex = doney =0 ;
			if ( ammo->deltax != ammo->movedx )
				if ( ammo->deltax < ammo->movedx )
				{
					ammo->movedx-- ;
					ammo->x-- ;
				}
				else
				{
					ammo->movedx++ ;
					ammo->x++ ;
				}
			else
				donex = 1 ;

			if ( ammo->deltay != ammo->movedy )
				if ( ammo->deltay < ammo->movedy )
				{
					ammo->movedy-- ;
					ammo->y-- ;
				}
				else
				{
					ammo->movedy++ ;
					ammo->y++ ;
				}
			else
				doney = 1 ;

			if ( donex && doney )
			{
				ammo->movedx = 0 ;
				ammo->movedy = 0 ;
			}
			if ( (ammo->x ==0) || (ammo->x==143) ||
				 (ammo->y ==0) || (ammo->y==151) )
			{
				ammo->atype = 0 ;
				move_sprite(7+gen1,0,0) ;
				numplayer1fire-- ;
			}
			else
				move_sprite(7+gen1,ammo->x,ammo->y)	;
		}
	}

}

void enemy_fire(UBYTE enemynum)
{
	UBYTE currx, curry ;
	UBYTE whichammo ;
	BYTE  aval ;
	struct Enemy_Stats *whichenemy ;

	whichammo = 0 ;
	while ( 1 )
	{
		if ( !enemy_ammo[whichammo].atype )
			break ;
		whichammo++ ;
	}

	whichenemy = enemies_on_screen+enemynum ;
	if ( whichenemy->motionnum&0x80 )
	{
		curry = *(whichenemy->curr_loc)+whichenemy->motion_offsetx ;
		currx = *(whichenemy->curr_loc+1)+whichenemy->motion_offsety ;
	}
	else
	{
		currx = *(whichenemy->curr_loc)+whichenemy->motion_offsetx ;
		curry = *(whichenemy->curr_loc+1)+whichenemy->motion_offsety ;
	}


	if ( currx < 80 )
		currx += 8 ;
	else
		currx -= 8 ;

	if ( curry < 88 )
		curry += 8 ;
	else
		curry -= 8 ;

	enemy_ammo[whichammo].atype++ ;
	enemy_ammo[whichammo].x = currx ;
	enemy_ammo[whichammo].y = curry ;

	aval = 80-currx ;
	if ( aval < -60 )
		enemy_ammo[whichammo].deltax = -3 ;
	else
		if ( aval < -36 )
		enemy_ammo[whichammo].deltax = -2 ;
	else
		if ( aval < -12 )
		enemy_ammo[whichammo].deltax = -1 ;
	else
		if ( aval < 12 )
		enemy_ammo[whichammo].deltax = 0 ;
	else
		if ( aval < 36 )
		enemy_ammo[whichammo].deltax = 1 ;
	else
		if ( aval < 60 )
		enemy_ammo[whichammo].deltax = 2 ;
	else
		enemy_ammo[whichammo].deltax = 3 ;

	aval = 88-curry ;
	if ( aval < -60 )
		enemy_ammo[whichammo].deltay = -3 ;
	else
		if ( aval < -36 )
		enemy_ammo[whichammo].deltay = -2 ;
	else
		if ( aval < -12 )
		enemy_ammo[whichammo].deltay = -1 ;
	else
		if ( aval < 12 )
		enemy_ammo[whichammo].deltay = 0 ;
	else
		if ( aval < 36 )
		enemy_ammo[whichammo].deltay = 1 ;
	else
		if ( aval < 60 )
		enemy_ammo[whichammo].deltay = 2 ;
	else
		enemy_ammo[whichammo].deltay = 3 ;


	enemy_ammo[whichammo].movedx = 0 ;
	enemy_ammo[whichammo].movedy = 0 ;
	numenemyfire++ ;
}

void scroll_enemies_power()
{
	UBYTE *locptr ;
	UBYTE whichtile ;
	struct Enemy_Stats *currenemy ;

	for ( gen1 = 0 ; gen1 != 6 ; gen1++ )
	{
		currenemy = enemies_on_screen+gen1 ;
		if ( currenemy->in_use==1 )
		{
			if ( currenemy->waitfire )
			{
				(currenemy->waitfire)-- ;
			}
			else
			{
				if ( currenemy->stype )
					currenemy->waitfire = levelStats[level].enemy2firewait ;
				else
					currenemy->waitfire	= levelStats[level].enemy1firewait ;
			}

			locptr = currenemy->curr_loc ;
			if ( *locptr==0xFF )
			{
				currenemy->in_use = 0 ;
				move_sprite(28+gen1+gen1,0,0) ;
				move_sprite(29+gen1+gen1,0,0) ;
			}
			else
			{
				if ( currenemy->motionnum&0x80 )
				{
					move_sprite(28+gen1+gen1,*(locptr+1)+currenemy->motion_offsety,*locptr+currenemy->motion_offsetx) ;
					move_sprite(29+gen1+gen1,*(locptr+1)+8+currenemy->motion_offsety,*locptr+currenemy->motion_offsetx) ;
				}
				else
				{
					move_sprite(28+gen1+gen1,*locptr+currenemy->motion_offsetx,*(locptr+1)+currenemy->motion_offsety) ;
					move_sprite(29+gen1+gen1,(*locptr)+8+currenemy->motion_offsetx,*(locptr+1)+currenemy->motion_offsety) ;
				}

				if ( currenemy->motionnum&0x40 )
					currenemy->curr_loc -= 2+currenemy->speed+currenemy->speed ;
				else
					currenemy->curr_loc	+= 2+currenemy->speed+currenemy->speed ;

				if ( (numenemyfire!=5) && (!currenemy->waitfire) && (!ship_isdead) )
					if ( currenemy->stype )
					{
						if ( (UBYTE)rand() < levelStats[level].enemy2fire_rate )
							enemy_fire(gen1) ;
					}
					else
						if ( (UBYTE)rand() < levelStats[level].enemy1fire_rate )
						enemy_fire(gen1) ;



			}
		}
	}

	if ( power_on_screen.in_use )
	{
		locptr = power_on_screen.curr_loc ;
		if ( *locptr==0xFF )
		{
			power_on_screen.in_use = 0 ;
			move_sprite(5,0,0) ;
			move_sprite(6,0,0) ;
		}
		else
		{
			move_sprite(5,*locptr+power_on_screen.motion_offsetx,*(locptr+1)+power_on_screen.motion_offsety) ;
			move_sprite(6,*locptr+8+power_on_screen.motion_offsetx,*(locptr+1)+power_on_screen.motion_offsety) ;
			power_on_screen.curr_loc += 2+(power_on_screen.speed<<1) ;
		}
	}
}



void animate()
{
	struct Enemy_Stats *currenemy ;
	UBYTE whichtile ;

	for ( gen1 = 0 ; gen1 != 6 ; gen1++ )
	{

		currenemy = enemies_on_screen+gen1 ;
		if ( currenemy->in_use==1 )
		{
			whichtile = ((*(currenemy->curr_frame)<<2) + 0x84)+ 
						(currenemy->stype<<4);

			set_sprite_tile(28+gen1+gen1,whichtile) ;
			set_sprite_tile(29+gen1+gen1,whichtile+2) ;

			if ( *(++currenemy->curr_frame)==0xFF )
				currenemy->curr_frame -= *(currenemy->curr_frame+1) ;
		}
		else
			if ( currenemy->in_use==2 )
		{
			if ( *(currenemy->curr_frame)==0x03 )
			{
				currenemy->in_use = 0 ;
				move_sprite(28+gen1+gen1,0,0) ;
				move_sprite(29+gen1+gen1,0,0) ;

			}
			else
			{
				set_sprite_tile(28+gen1+gen1,0xE8+(*(currenemy->curr_frame)<<2)) ;
				set_sprite_tile(29+gen1+gen1,0xEA+(*(currenemy->curr_frame)<<2)) ;
				currenemy->curr_frame++ ;
			}
		}
	}

}

void endgamegood() ;
void endgamebad() ;

void levelup()
{
	if ( level==2 )
	{


		if ( ( total_enemies_hit > 99 ) && ( total_earth_hits < 21 ) )
			remoteCall( 37, 36, endgamegood ) ;
		else
			remoteCall( 37, 36, endgamebad ) ;

		level = 0 ;
		enemyptr = enemies_to_come;
		powerptr = powers_to_come ;
	}
	else
	{
		level++ ;
		enemyptr++ ;
		powerptr++ ;
	}
	set_sprite_data(0x84, 16, enemytiles+(((UWORD)levelStats[level].enemy1tileoffset)<<6));
	set_sprite_data(0x94, 16, enemytiles+(((UWORD)levelStats[level].enemy2tileoffset)<<6));
	set_sprite_data(0xA4, 64, enemytiles+(levelStats[level].bosstileoffset));
	enemy_wait = enemyptr->sdelay ;


}

void put_new_enemy()
{
	UBYTE whichsprite ;
	struct Enemy_Stats *whichenemy ;
	UBYTE whichtile ;

	if ( enemyptr->sdelay )
	{
		if ( enemyptr->stype==0xFF )
		{
			enemyptr++ ;
			enemy_wait = enemyptr->sdelay ;
			return ;
		}

		whichsprite = enemyptr->spritenum ;
		whichenemy = enemies_on_screen+whichsprite ;
		whichenemy->in_use = 1;     
		whichenemy->curr_loc = motions+motion_offsets[enemyptr->motionnum&0x3F];  
		whichenemy->motion_offsetx = enemyptr->motion_offsetx ;
		whichenemy->motion_offsety = enemyptr->motion_offsety ;
		whichenemy->motionnum = enemyptr->motionnum;
		whichenemy->speed = (enemyptr->stype)>>5 ;
		if ( ((enemyptr->stype)>>4)&0x01 )
		{
			whichenemy->stype = 2 ;
			set_sprite_tile(32,0xA4) ;
			set_sprite_tile(33,0xA6) ;
			set_sprite_tile(34,0xA8) ;
			set_sprite_tile(35,0xAA) ;
			set_sprite_tile(36,0xAC) ;
			set_sprite_tile(37,0xAE) ;
			set_sprite_tile(38,0xB0) ;
			set_sprite_tile(39,0xB2) ;
			whichenemy->curr_frame = enemyframes + levelStats[level].bossframeoffset; 
		}
		else
		{
			whichtile = (enemyptr->stype)&0x01 ;
			whichenemy->stype = whichtile ;
			set_sprite_tile(28+whichsprite+whichsprite,0x84+(whichtile<<4)) ;
			set_sprite_tile(29+whichsprite+whichsprite,0x86+(whichtile<<4)) ;
			if ( whichtile )
			{
				whichenemy->waitfire = levelStats[level].enemy2firewait ;
				whichenemy->curr_frame = enemyframes + levelStats[level].enemy2frameoffset; 
				whichenemy->numhits = levelStats[level].enemy2hits; 
			}
			else
			{
				whichenemy->waitfire = levelStats[level].enemy1firewait ;
				whichenemy->curr_frame = enemyframes + levelStats[level].enemy1frameoffset; 
				whichenemy->numhits = levelStats[level].enemy1hits; 
			}
		}

		enemyptr++ ;
		enemy_wait = enemyptr->sdelay ;
	}
	else
		levelup() ;

//     enemy_wait = 0xFFFF ;

}

void put_new_power()
{
	UWORD whichtile ;

	if ( powerptr->sdelay )
	{
		power_on_screen.in_use = powerptr->stype+1;     
		power_on_screen.curr_loc = motions+motion_offsets[powerptr->motionnum&0x3F];  
		power_on_screen.motion_offsetx = powerptr->motion_offsetx ;
		power_on_screen.motion_offsety = powerptr->motion_offsety ;
		power_on_screen.motionnum = powerptr->motionnum ;
		power_on_screen.speed = (powerptr->stype)>>5 ;

		whichtile = ((powerptr->stype)&0x0F)<<2 ;

		set_sprite_data(0xE4, 4, powertiles+(UWORD)(((UWORD)(powerptr->stype)&0x0FL)<<6L));

		set_sprite_tile(5,0xE4) ;
		set_sprite_tile(6,0xE6) ;

		powerptr++ ;
		power_wait = powerptr->sdelay ;
//     while(1) ;

	}
	else
		power_wait = 0xFFFF ;

}

void setupEarth()
{

//  UBYTE i ;

//  set_bkg_data(0x09, 0x20, earth1 );
//  set_bkg_data(0xFC, 0x04, std_data);

//  for (i=0 ; i != 64 ; i+=2)
	//set_bkg_tiles(earthloc[i],earthloc[i+1],1,1,earth1map+(i>>1)) ;

//  set_sprite_data(0xE4, 4, powertiles);
//  set_sprite_data(0x84, 16, enemytiles+(((UWORD)levelStats[level].enemy1tileoffset)<<6));
//  set_sprite_data(0x94, 16, enemytiles+(((UWORD)levelStats[level].enemy2tileoffset)<<6));
//  set_sprite_data(0xA4, 64, enemytiles+(levelStats[level].bosstileoffset));

}


void init_vars()
{
	flipflop = 0 ;
	joykeys = 0 ;
	ship_direction = 2 ;  //ship is stopped
	ship_currframe = 0 ;
	shippos = shipmotion+(95UL*3UL) ;
	level = 0 ;
	num_player_shots = 0 ;
	num_enemy_shots = 0 ;
	num_enemies = 0 ;
	enemyptr = enemies_to_come;
	powerptr = powers_to_come ;
	ship_shieldon = 0 ;
	earth_shieldon = 0 ;
	ship_shooting = 0 ;
	ship_shieldpower = 0xFF ;
	ship_shieldwait = 5 ;

	ship_isdead = 0 ;
	ship_isinvincible = 0 ;
	shipframe_offset = 0 ;

	power_on_screen.in_use = 0 ; 
	for ( gen1 = 0 ; gen1 != 6 ; gen1++ )
		enemies_on_screen[gen1].in_use = 0 ;

	for ( gen1 = 0 ; gen1 != 5 ; gen1++ )
		enemy_ammo[gen1].atype = 0 ;

	for ( gen1 = 0 ; gen1 != 4 ; gen1++ )
		player1_ammo[gen1].atype = 0 ;

	for ( gen1 = 0 ; gen1 != 4 ; gen1++ )
		player2_ammo[gen1].atype = 0 ;

	for ( gen1 = 0 ; gen1 != 36 ; gen1++ )
		earth_state[gen1] = 3 ;

	enemy_wait = enemyptr->sdelay ;
	power_wait = powerptr->sdelay ;


	curr_rand = 0 ;
	numenemyfire = 0;
	numplayer1fire = 0;
	numplayer2fire = 0;
	countdown = 0 ;
	ship_powerup = 0 ;

	animate_wait = 10 ;

	lastkey =0 ;

	total_earth_hits = 0 ;
	total_enemies_hit = 0 ;
}
