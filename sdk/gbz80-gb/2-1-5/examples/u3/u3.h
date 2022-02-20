//#define LIKSANG 1

typedef struct battlemonsters
{
	UBYTE x ;
	UBYTE y ;
	UBYTE hp ;

} BATTLEMONSTERS ;

//typedef struct battleplayers {
//   UBYTE x ;
//   UBYTE y ;
//   UBYTE tile ;
//} BATTLEPLAYERS ;

typedef struct player
{
	unsigned char name[7] ;	 //line 1
	UWORD currHP ; //line 2
	UWORD maxHP ;
	UBYTE status ;	//line 2  good, poisoned, dead, ashes
	UWORD food ;  //line 3
	UWORD gold ;
	UBYTE magic ; //line 4
	UBYTE level ; //ilne 4
	UWORD exp ;	//line5
	UBYTE str ;
	UBYTE dex ;
	UBYTE intel ;
	UBYTE wis ;
	UBYTE gems ;
	UBYTE keys ;
	UBYTE powders ;
	UBYTE torches ;
	UBYTE weapon ;
	UBYTE armor ;
	UBYTE weapons[16] ;
	UBYTE armors[8] ;
	UBYTE sex ;
	UBYTE race ;
	UBYTE skill ; //line2
	UBYTE markcard ; //4 marks, 4 cards
	UBYTE inparty ;
	UBYTE tile ;
	UBYTE x ;
	UBYTE y ;
	UBYTE rosterpos ;
	unsigned char reserved[64] ;
} PLAYER ;

typedef struct monster
{
	UBYTE tile;
	UBYTE x,y ;
	UBYTE attribs ;	 //high nibble : 1=attack char if near, 0=ignore
					 //low nibble  : 0=sessile 2=move randomly, 1=move towards character
	UBYTE whichtalk ;
	// high nibble = which special other,yell
	//EVOCARE
	//INSERT=1
	//BRIBE=2
	//DIG=3
	//PRAY=4
	//SEARCH=5
	//SCORE

} MONSTER ;

#define MONSTERSIZE 5L

//0 - walk on by foot
//1 - walk on by ship
//2 - enterable
//3 - attackable/transactable
//4 - opaque
//5 - boardable
#define CARDDEATH 0x01 
#define CARDLOVE  0x02 
#define CARDSOL   0x04 
#define CARDMOON  0x08 
#define MARKFORCE 0x10 
#define MARKFIRE  0x20 
#define MARKSNAKE 0x40 
#define MARKKING  0x80 
