#include <gb.h>

#include "music2/towne3.c"
#include "music2/towne4.c"
#include "music2/towne5.c"
#include "music2/legacy_sfx.c"

UWORD frequencies3[] = {
	44, 156, 262, 363, 457, 547, 631, 710, 786, 854, 923, 986,
	1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
	1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
	1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
	1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
	1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015
};

unsigned char u3wander_RAM3[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,
	0x22,0x22,0x22,0x22,0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,0x00,0x00,0x00,0x00,
	0x33,0x33,0x33,0x33,0x00,0x00,0x00,0x00,0x33,0x33,0x33,0x33,0x00,0x00,0x00,0x00,
	0x44,0x44,0x44,0x44,0x00,0x00,0x00,0x00,0x44,0x44,0x44,0x44,0x00,0x00,0x00,0x00,
	0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x00,
	0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,
	0x77,0x77,0x77,0x77,0x00,0x00,0x00,0x00,0x77,0x77,0x77,0x77,0x00,0x00,0x00,0x00,
	0x88,0x88,0x88,0x88,0x00,0x00,0x00,0x00,0x88,0x88,0x88,0x88,0x00,0x00,0x00,0x00,
	0x99,0x99,0x99,0x99,0x00,0x00,0x00,0x00,0x99,0x99,0x99,0x99,0x00,0x00,0x00,0x00,
	0xAA,0xAA,0xAA,0xAA,0x00,0x00,0x00,0x00,0xAA,0xAA,0xAA,0xAA,0x00,0x00,0x00,0x00,
	0xBB,0xBB,0xBB,0xBB,0x00,0x00,0x00,0x00,0xBB,0xBB,0xBB,0xBB,0x00,0x00,0x00,0x00,
	0xCC,0xCC,0xCC,0xCC,0x00,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x00,0x00,0x00,0x00,
	0xDD,0xDD,0xDD,0xDD,0x00,0x00,0x00,0x00,0xDD,0xDD,0xDD,0xDD,0x00,0x00,0x00,0x00,
	0xEE,0xEE,0xEE,0xEE,0x00,0x00,0x00,0x00,0xEE,0xEE,0xEE,0xEE,0x00,0x00,0x00,0x00,
	0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
};

extern unsigned char *musicdat_start ;
extern unsigned char *datasong_ptr ;
extern UBYTE musicnum ;
extern UBYTE musicbank ;
extern UBYTE changemusic ;

UBYTE ooo1, ooo2, ooo3,vvv1,vvv2,vvv3 ;
UBYTE max_att3_step ;
UBYTE curr_att3 ;
UBYTE max_clock_step ;
UBYTE curr_clock ;
unsigned char freqHI3;
unsigned char freqLOW3;

unsigned char *w3_ram ;



void stopmusic()
{
	/* initialise sound output */
	NR52_REG = 0x8FU;
	NR51_REG = 0x00U;
	NR50_REG = 0x77U;

}


void resetmusic()
{
	// initialise sound output 

	NR52_REG = 0x00U;


	NR52_REG = 0x8FU;
	NR51_REG = 0x00U;
	NR50_REG = 0x77U;


}


void voice0(UBYTE thehash)
{

	unsigned char freqLOW;
	unsigned char freqHI;
	UBYTE gb_freq;
	UBYTE action ;

	if ( (thehash & 16) != 0 )
	{
		if ( ( thehash & 32 ) != 0 )
		{
			gb_freq = *datasong_ptr++ ;
			if ( gb_freq >= 12*ooo1 )
			{
				gb_freq -= (12*ooo1);
				freqLOW = frequencies3[gb_freq] & 0x00FF ;
				freqHI = (frequencies3[gb_freq] & 0x0700) >> 8 ;
			}
			else
			{
				freqLOW = 0 ;
				freqHI = 0 ; 
			}

			NR51_REG &= 0xEEU;
//        NR10_REG = snd_swp0 ;
//        NR11_REG = snd_lngh0 ;
//        NR12_REG = snd_env0 ;
			NR12_REG = ((15U-vvv1)<<4)|0x06 ; 
//        NR11_REG = 0xBFU ;
			NR11_REG = 0xBFU ;
			NR10_REG = 0x00U ;

//        NR13_REG = 0x7FU;                       // 8bits of data
//        NR14_REG = snd_cons0 | 0x01U;            // 3bits of data
			NR13_REG = freqLOW;						  // 8bits of data
			NR14_REG = 0x80U | freqHI;			  // 3bits of data

			NR51_REG |= 0x11U;
		}


	}
	else
	{
		NR51_REG &= 0xEEU;
	}

}



void voice1(UBYTE thehash)
{
	unsigned char freqLOW;
	unsigned char freqHI;
	UBYTE gb_freq;
	UBYTE action ;


	if ( (thehash & 4) != 0 )
	{
		if ( ( thehash & 8 ) != 0 )
		{
			gb_freq = *datasong_ptr++ ;

			if ( gb_freq >= 12*ooo2 )
			{
				gb_freq -= (12*ooo2);
				freqLOW = frequencies3[gb_freq] & 0x00FF ;
				freqHI = (frequencies3[gb_freq] & 0x0700) >> 8 ;
			}
			else
			{
				freqLOW = 0 ;
				freqHI = 0 ; 
			}

			NR51_REG &= 0xDDU;

			//NR22_REG = snd_env1 ;
			NR22_REG = ((15U-vvv2)<<4)|0x06 ; 
			NR21_REG = 0xBFU ;		//  0x01
//        NR21_REG = snd_lngh1 ;      //  0x01
			NR23_REG = freqLOW ;
			NR24_REG = 0x80U | freqHI;

			NR51_REG |= 0x22U;
		}


	}
	else
	{
		NR51_REG &= 0xDDU;
	}

}


void voice2(UBYTE thehash)
{
	UBYTE gb_freq;
	UBYTE action ;
	unsigned char *mp ;

	if ( (thehash & 1) != 0 )
	{
		if ( ( thehash & 2 ) != 0 )
		{
			gb_freq = *datasong_ptr++ ;

			curr_att3 = max_att3_step ;
			w3_ram = u3wander_RAM3+0x100UL ;

			if ( gb_freq >= 12*ooo3 )
			{
				gb_freq -= (12*ooo3);
				freqLOW3 = frequencies3[gb_freq] & 0x00FF ;
				freqHI3 = (frequencies3[gb_freq] & 0x0700) >> 8 ;
			}
			else
			{
				freqLOW3 = 0 ;
				freqHI3 = 0 ; 
			}

			NR51_REG &= 0xBBU;

			NR30_REG = 0x00U;    
			memcpy((unsigned char*)0xFF30,w3_ram, 0x10L) ;

			NR32_REG = 0x20U;
			NR31_REG = 0xFFU;
			NR30_REG = 0x80U;    
			NR33_REG = freqLOW3 ;
			NR34_REG = 0x80U | freqHI3;

			NR51_REG |= 0x44U;
		}
		else
		{
			if ( curr_att3==0 )
			{
				if ( w3_ram > u3wander_RAM3 )
				{
					w3_ram -= 32L ;
					mp = w3_ram ;
					NR30_REG = 0x00U;    
					memcpy((unsigned char*)0xFF30,w3_ram, 0x10L) ;
					NR30_REG = 0x80U;    
					NR34_REG = 0x80U | freqHI3;
				}
				curr_att3 = max_att3_step ;
			}
			else
				curr_att3--	;
		}


	}
	else
	{
		NR51_REG &= 0xBBU;
	}

}


void music()
{

	UBYTE join_music ;

	if ( curr_clock == 0 )
	{
		if ( (*datasong_ptr)==0xFFU )
		{
			if ( (musicbank==22)&&(musicnum==1) )
			{
				changemusic=4 ;
				return ;
			}
			if ( (musicbank==22)&&(musicnum==12) )
			{
				changemusic=19 ;
				return ;
			}
			datasong_ptr = musicdat_start ;
		}

		join_music = *datasong_ptr++ ;

		voice0(join_music);
		voice1(join_music);
		voice2(join_music);
		curr_clock = max_clock_step ;
	}
	else
	{
		curr_clock-- ;
	}



}

void init_music()
{

	memcpy((unsigned char*)0xFF30,u3wander_RAM3+0x100UL, 0x10L) ;
	w3_ram = u3wander_RAM3+0x100UL ;

	vvv1 = 0 ;
	vvv2 = 0 ;
	vvv3 = 0 ;

	switch ( musicnum )
	{
		case 0: 
			{
				musicdat_start = towne3music ;
				datasong_ptr = towne3music ;
				ooo1 = 4 ;
				ooo2 = 4 ;
				ooo3 = 4 ;
				max_att3_step = 3 ;
				max_clock_step = 130 ;
				break ;

			}
		case 1: 
			{
				musicdat_start = towne4music ;
				datasong_ptr = towne4music ;
				ooo1 = 4 ;
				ooo2 = 4 ;
				ooo3 = 4 ;
				max_att3_step = 3 ;
				max_clock_step = 130 ; 
				break ;

			}
		case 2: 
			{
				musicdat_start = towne5music ;
				datasong_ptr = towne5music ;
				ooo1 = 4 ;
				ooo2 = 4 ;
				ooo3 = 4 ;
				max_att3_step = 3 ;
				max_clock_step = 45 ; 
				break ;

			}
		case 3: 
			{
				musicdat_start = legacy_sfx ;
				datasong_ptr = legacy_sfx ;
				ooo1 = 4 ;
				ooo2 = 4 ;
				ooo3 = 4 ;
				max_att3_step = 10 ;
				max_clock_step = 15 ; 
				break ;

			}
		default: 
			{
				break ;

			}

	}

	curr_att3 = max_att3_step ;
	curr_clock = 0 ;

}
