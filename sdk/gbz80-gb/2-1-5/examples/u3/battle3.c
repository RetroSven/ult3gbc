#include <gb.h>
#include "u3.h"

#define u3tiles ((unsigned char*)(0xB000))
#define tile_palettes ((unsigned char*)(0xB930))
#define tile_attribs  ((unsigned char*)(0xB990))
#define check_order ((unsigned char*)(0xB9F0))
#define bkg_p ((UWORD*)(0xBA40))
#define obj_p ((UWORD*)(0xBA80))
#define battlemaps ((UWORD*)(0xBAC0))

extern UBYTE extragame ;
extern UBYTE generatorx ;
extern UBYTE generatory ;
extern UBYTE generatortile ;
extern UBYTE ingenerator ;

extern UBYTE blinkdelay ;
extern UBYTE tileon ;
extern UBYTE currplayer ;
extern UBYTE numbaddies ;

extern UBYTE peermap ;

extern UBYTE screenx ;
extern UBYTE screeny;
extern UBYTE playerx ;
extern UBYTE playery ;
extern UBYTE inside ;

extern UBYTE nummonsters ;

extern UBYTE inexodus ;

extern BATTLEMONSTERS baddies[9] ;
extern PLAYER players[] ;
extern MONSTER monsters[] ;
extern UBYTE monsterattrib ;
extern UBYTE monsterpower ;

extern UBYTE dungx ;
extern UBYTE dungy ;
extern UBYTE dunglevel ;

extern UBYTE numgoodies; 
extern UBYTE numalive ;

extern UBYTE stoptimebattle ;
extern UBYTE monstertile ;

extern unsigned char *vidbase ;

extern UBYTE delayscroll ;
extern UBYTE mode4tiles ;
extern UBYTE mode8tiles ;
extern unsigned char screenbuf3[] ;
extern UBYTE mapnum ;
extern unsigned char *vidbase ;

extern UBYTE cheat_xray ;
extern UBYTE cheat_nofight ;
extern UBYTE cheat_nohurt ;
extern UBYTE cheat_noblock ;
extern UBYTE cheat_fullmp ;
extern UBYTE cheat_noclass ;

#define SCROLLDELAY 20

unsigned char deaddat6[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x82 
} ;
unsigned char chardat4[] = {
	'H'+0x1D,'F'+0x1D,'M'+0x1D  
};
unsigned char charstat4[] = {
	'G'+0x1D,'P'+0x1D,'D'+0x1D,'A'+0x1D
};

unsigned char pdeaddat[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x79,0x5D,'D'+0x1D,'E'+0x1D,'A'+0x1D,'D'+0x1D,0x5D
} ;

unsigned char phitdat[] = {
	'P'+0x1D,'L'+0x1D,'A'+0x1D,'Y'+0x1D,'E'+0x1D,'R'+0x1D,0x79,0x5D,'H'+0x1D,'I'+0x1D,'T'+0x1D,0x5D,0x5D
};

/*
void writegamemessage4(unsigned char *msgdat)
{
   UBYTE q ;
   
   for (q=0 ; q < 4 ; q++)
   {
	  set_data2(vidbase+(32L*(q+13)),vidbase+(32L*(q+14)),12L) ;
   }
	
   set_data2(vidbase+(32L*17),msgdat,12L) ;
   
}
*/
void formatnumber5(UWORD num,UBYTE length)
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

void charscreen3(PLAYER *player, UBYTE loc)
{
	UBYTE n ;

	memset(screenbuf3,0x5D,11L) ;

	for ( n=0 ; n<4 ; n++ )
		set_bkg_tiles2( 13, n+1+(loc<<2), 7, 1, (unsigned char*)screenbuf3 );

	if ( !(player->inparty) )
		return ;

	set_bkg_tiles2( 13, 2+(loc<<2), 1, 3, chardat4 );

	set_bkg_tiles2( 13, 1+(loc<<2), 7, 1, player->name );
	formatnumber5(player->currHP,4) ;
	set_bkg_tiles2( 14, 2+(loc<<2), 4, 1, (unsigned char*)screenbuf3);

	set_bkg_tiles2( 19, 2+(loc<<2), 1, 1, charstat4+(UWORD)player->status );

	formatnumber5(player->food,4) ;
	set_bkg_tiles2( 14, 3+(loc<<2), 4, 1, (unsigned char*)screenbuf3 );

	formatnumber5(player->magic,2) ;
	set_bkg_tiles2( 14, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	formatnumber5(player->level,2) ;
	set_bkg_tiles2( 18, 4+(loc<<2), 2, 1, (unsigned char*)screenbuf3 );

	*(unsigned char*)screenbuf3 = 'L'+0x1D ;
	set_bkg_tiles2( 17, 4+(loc<<2), 1, 1, (unsigned char*)screenbuf3 );


}

void magiceffect2(UBYTE spellnum)
{
	UBYTE p ;

//   magicsfx1(20+(spellnum*5)) ;
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

void update_screen8()
{

	if ( delayscroll-- == 0 )
	{
		if ( ++mode4tiles==4 )
			mode4tiles=0 ;
		if ( ++mode8tiles==8 )
			mode8tiles=0 ;

		set_bkg_data2(  0x00, 0x01, u3tiles+(UWORD)((UWORD)mode4tiles<<4) );
//      set_bkg_data2(  0x0F, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x0FL)<<4) );
//      set_bkg_data2(  0x26, 0x01, u3tiles+(UWORD)(((UWORD)(mode4tiles)+0x26L)<<4) );
//      set_bkg_data2(  0x2A, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x2AL)<<4) );
//      set_bkg_data2(  0x32, 0x01, u3tiles+(UWORD)(((UWORD)(mode8tiles)+0x32L)<<4) );
		delayscroll = SCROLLDELAY ;
	}
}

UBYTE moveOK2(UBYTE newx, UBYTE newy, UBYTE monstile, UBYTE pnum)
{
	unsigned char newtile ;
	UBYTE p ;

	if ( (newy==players[pnum].y) && (newx==players[pnum].x) )
		return 2 ;

	if ( (monstile==0x04)||(monstile==0x0B) )
		for ( p=0 ; p<numbaddies ; p++ )
			if ( (baddies[p].x==newx)&&(baddies[p].y==newy) )
				return 0 ;

	get_bkg_tiles2(newx+1,newy+1,1,1,&newtile) ;
	if ( (monstile >= 0x0F) && (monstile<=0x15) )
		if ( newtile==0x00 )
			return 1 ;
		else
			return 0 ;
	else
		if ( (tile_attribs[newtile])&0x40 )
		return 1 ;
	else
		return 0 ;
}

void killplayer(pnum)
{
	if ( cheat_nohurt != 0 )
		return ;

	players[pnum].status = 0x02 ;
	players[pnum].currHP = 0L ;  
	numalive-- ;
	set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
			  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
			  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x,1L) ;
	VBK_REG=1 ;
	set_data2(vidbase+(32L*((UWORD)(players[pnum].y)+1L))+(UWORD)players[pnum].x+1L,
			  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
									  (11L*((UWORD)(players[pnum].y)))+(UWORD)players[pnum].x)),1L) ;
	VBK_REG=0 ;
	memcpy(screenbuf3,pdeaddat,12L) ;
	screenbuf3[6] += pnum ;
	writegamemessage(screenbuf3) ;

}

unsigned char playpoisoned[] = {
	'P'+0x1D,'O'+0x1D,'I'+0x1D,'S'+0x1D,'O'+0x1D,'N'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5D,0x5D,0x5D, 
} ;
unsigned char pilfered[] = {
	'P'+0x1D,'I'+0x1D,'L'+0x1D,'F'+0x1D,'E'+0x1D,'R'+0x1D,'E'+0x1D,'D'+0x1D,0x82,0x5D,0x5D,0x5D, 
} ;

void damageplayer(UBYTE pnum, UBYTE dopoison)
{
	UBYTE tohit, damage,armor, damage2, damage3 ;
	UBYTE p,itemnum ;
	UWORD bdamage ;

	if ( cheat_nohurt != 0 )
		return ;

	attackswingsfx(120) ;

	if ( ((monstertile==0x14) || (monstertile==0x22) || (monstertile==0x24)) &&
		 (((make_rnd(0))&0x03)==0) && (players[pnum].status==0) )
	{
		players[pnum].status = 1 ;
		writegamemessage(playpoisoned) ;
		playerhitsfx(170U) ;
	}

	if ( monstertile==0x1D )
	{
		if ( (make_rnd(0))&0x80U )
		{
			itemnum = (make_rnd(0)&0x07) ;
			if ( itemnum && ((players[pnum].armors)[itemnum]) )
			{
				((players[pnum].armors)[itemnum])-- ;
				writegamemessage(pilfered) ;
				attackmisssfx(120U);
			}
		}
		else
		{
			itemnum = (make_rnd(0)&0x0F) ;
			if ( itemnum && ((players[pnum].weapons)[itemnum]) )
			{
				((players[pnum].weapons)[itemnum])-- ;
				writegamemessage(pilfered) ;
				attackmisssfx(120U);
			}


		}


	}

	if ( extragame != 0 )
	{
		damage = ( (players[pnum].dex + ( players[pnum].armor * 5 ) ) / 3 ) + 34 ;
		damage2 = make_rnd(100) ;
		damage = damage2 > damage ;
	}
	else
	{
		damage = ( (inexodus && (players[pnum].armor!=7)) ||
				   (make_rnd(0x10+(players[pnum].armor))<8) ) ;
	}


	if ( damage )
	{
		damage = (UBYTE)  (((players[pnum].maxHP/1000L)<<4)+
						   ((players[pnum].maxHP/100L)%10));
		damage = make_rnd(((monsterpower>>3) + damage) | 0x01) + 1 ;
		if ( extragame != 0 )
		{
			bdamage = ((UWORD)damage)*3UL ;

			damage2 = make_rnd(damage) ;
			damage3 = make_rnd(damage) ;

			if ( damage2 > (255U-damage3) )
				damage = 200 ;
			else
			{
				damage2 += damage3 ;
				damage3 = make_rnd(damage) ;
				if ( damage2 > (255U-damage3) )
					damage = 200 ;
				else
					damage = damage2 + damage3 ;

			}

			damage2 = make_rnd((players[pnum].armor+1) * 5) ;
			if ( (UWORD)damage2 >= bdamage )
				bdamage = 5UL ;
			else
				bdamage	-= (UWORD)damage2 ;
		}
		else
		{
			if ( inside==0x22 )	//dungeon
				damage += 10 ;
			else
				if ( inside==0x20 )
			{
				if ( peermap==12 )
					damage += 30 ;
			}
			else
				if ( (peermap==0)||(peermap==4) )
				damage += 30 ;
			else
				damage += 20 ;
			bdamage = damage ;
		}

		memset(screenbuf3,0x04,7L) ;
		VBK_REG=1 ;
		for ( p=0 ; p<4 ; p++ )
			set_bkg_tiles2(13,p+(pnum<<2)+1,7,1,screenbuf3) ;
		VBK_REG=0 ;
		if ( players[pnum].currHP> bdamage )
		{
			players[pnum].currHP -= bdamage ;
			memcpy(screenbuf3,phitdat,12L) ;
			screenbuf3[6] += pnum ;
			writegamemessage(screenbuf3) ;
		}

		else
		{
			killplayer(pnum) ;
		}
		playerhitsfx(170U) ;
		memset(screenbuf3+7L,0x00,7L) ;
		VBK_REG=1 ;
		for ( p=0 ; p<4 ; p++ )
			set_bkg_tiles2(13,p+(pnum<<2)+1,7,1,screenbuf3+7L) ;
		VBK_REG=0 ;


	}
	else
		attackmisssfx(120U)	;

	charscreen3(&(players[pnum]),pnum) ;

}
/*
void monstermagic(UBYTE mnum, UBYTE whichmagic)
{
   UBYTE thechar ;
   
   while (players[(thechar=make_rnd(4))].status>1)
	  ; //empty loop
	  
   magiceffect2() ;
   damageplayer(thechar,(whichmagic>>4)-1) ;
   
	
	
}
*/
/*
void monsterprojectile(UBYTE mnum, UBYTE pnum) 
{
   UBYTE r, startr ;

   if (baddies[mnum].x==players[pnum].x)
   {
	  if (baddies[mnum].y < players[pnum].y)
		 startr = baddies[mnum].y+1 ;
	  else
		 startr = baddies[mnum].y-1 ;
	  for(r=startr ; r<=players[pnum].y ; r++)
	  {
		 move_sprite( (monsterattrib&0x0F)-1, baddies[mnum].x*8+16,r*8+24 );
		 delay(150) ;
	  }
	
	
   }
   else
   {
	  if (baddies[mnum].x < players[pnum].x)
		 startr = baddies[mnum].x+1 ;
	  else
		 startr = baddies[mnum].x-1 ;
	  for(r=startr ; r<=players[pnum].x ; r++)
	  {
		 move_sprite( (monsterattrib&0x0F)-1, r*8+16,baddies[mnum].y*8+24 );
		 delay(150) ;
	  }
	
	
   }
   move_sprite( (monsterattrib&0x0F)-1, 0,0 );
   
   damageplayer(pnum,0) ;
   
	
}
*/
void trapeffect3(UBYTE pnum)
{
	UBYTE p ;

	memset(screenbuf3,0x04,7L) ;
	memset(screenbuf3+7L,0x00,7L) ;
	disable_interrupts2() ;
	VBK_REG=1 ;      
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1+(pnum<<2),7,1,screenbuf3) ;
	playerhitsfx(170U) ;
	//delay(750) ; //trap sound
	for ( p=0 ; p<4 ; p++ )
		set_bkg_tiles2(13,p+1+(pnum<<2),7,1,screenbuf3+7L) ;
	VBK_REG=0 ;      
	enable_interrupts2() ;


}

void damageplayer3(UBYTE pnum, UBYTE damage)
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
		writegamemessage(deaddat6) ;

	}
	formatnumber5( (UWORD)(players[pnum].currHP),4) ;
	set_data2((unsigned char*)0x9800+14L+(32L*(2+(pnum<<2))),(unsigned char*)screenbuf3,4L) ;
	set_data2((unsigned char*)0x9C00+14L+(32L*(2+(pnum<<2))),(unsigned char*)screenbuf3,4L) ;

}

void cannonfire3()
{
	UBYTE n ;
	UBYTE damage ;

	for ( n=0 ; n!=4 ; n++ )
	{
		if ( (players[n].inparty)&&(players[n].status<2) )
		{
			damage = (make_rnd(0)) & 0x77 ;
			damage = ((damage>>4)*10) + (damage&0x0F) ;
			damageplayer3(n,damage) ;
			trapeffect3(n) ;
		}
	}
}

void dragonbreath(UBYTE mnum) 
{

	UBYTE mx, my, dnum ;
	BYTE dx,dy ;
	UBYTE cx,cy ;
	unsigned char ftile ;

	if ( (make_rnd(0))&0x80U )
		return ;


	mx = (monsters[mnum].x-screenx)&0x3f ;
	my = (monsters[mnum].y-screeny)&0x3f ;

	if ( (mx>10)||(my>10) )
		return ;

	if ( mx==5 )
		dx = 0 ;
	else
		if ( mx>5 )
		dx = -1 ;
	else
		dx = 1 ;

	if ( my==5 )
		dy = 0 ;
	else
		if ( my>5 )
		dy = -1 ;
	else
		dy = 1 ;

	dnum = 0 ;

	cx = mx ;
	cy = my ;

	firecannonsfx(170U) ;
	while ( dnum<3 )
	{
		cx += dx ;
		cy += dy ;
		get_bkg_tiles2(cx+1,cy+1,1,1,&ftile) ;
		if ( (ftile==0x07)||(ftile==0x3a)||(ftile==0x3b)||(ftile==0x5d) )
			break ;

		move_sprite(0,cx*8+16,cy*8+24) ;
		if ( (cx==5)&&(cy==5) )
		{
			cannonfire3() ;
			break ;
		}
		dnum++ ;
		delay(550) ;

	}
	move_sprite(0,0,0);



}

void dragonbreathbattle(UBYTE mnum) 
{

	UBYTE mx, my, dnum, damage ;
	BYTE dx,dy ;
	UBYTE lenx,leny, n, fireatplayer ;
	UBYTE cx,cy ;
	unsigned char ftile ;


	fireatplayer = 99 ;

	for ( n=0 ; (n!=numgoodies) ; n++ )
	{
		if ( players[n].status<2 )
		{

			if ( players[n].x > baddies[mnum].x )
				lenx = players[n].x - baddies[mnum].x ;
			else
				lenx = baddies[mnum].x - players[n].x ;

			if ( players[n].y > baddies[mnum].y )
				leny = players[n].y - baddies[mnum].y ;
			else
				leny = baddies[mnum].y - players[n].y ;


			if ( ( lenx == leny ) || ( lenx == 0 ) || ( leny == 0 ) )
			{
				fireatplayer = n ;
				break ;
			}

		}


	}


	if ( fireatplayer == 99 )
	{
		while ( ( fireatplayer >= numgoodies ) || ( players[fireatplayer].status > 1 ) )
			fireatplayer = (make_rnd(0))&0x03 ;

		n = fireatplayer ;

		if ( players[n].x > baddies[mnum].x )
			lenx = players[n].x - baddies[mnum].x ;
		else
			lenx = baddies[mnum].x - players[n].x ;

		if ( players[n].y > baddies[mnum].y )
			leny = players[n].y - baddies[mnum].y ;
		else
			leny = baddies[mnum].y - players[n].y ;

	}

	if ( lenx == 0 )
	{
		dx = 0 ;

		if ( baddies[mnum].y > players[fireatplayer].y )
			dy = -1 ;
		else
			dy = 1 ;
	}
	else if ( leny == 0 )
	{
		dy = 0 ;

		if ( baddies[mnum].x > players[fireatplayer].x )
			dx = -1 ;
		else
			dx = 1 ;
	}
	else
	{
		if ( baddies[mnum].y > players[fireatplayer].y )
			dy = -1 ;
		else
			dy = 1 ;

		if ( baddies[mnum].x > players[fireatplayer].x )
			dx = -1 ;
		else
			dx = 1 ;

	}

	cx = baddies[mnum].x ;
	cy = baddies[mnum].y ;

	fireatplayer = 99 ;

	firecannonsfx(170U) ;
	while ( 1 )
	{
		cx += dx ;
		cy += dy ;

		if ( ( cx == 255 ) || ( cx == 11 ) || ( cy == 255 ) || ( cy == 11 ) )
			break ;

		get_bkg_tiles2(cx+1,cy+1,1,1,&ftile) ;
		if ( (ftile==0x07)||(ftile==0x3a)||(ftile==0x3b)||(ftile==0x5d) )
			break ;

		move_sprite(0,(cx)*8+16,(cy)*8+24) ;

		for ( n=0 ; (n!=numgoodies) ; n++ )
		{
			if ( players[n].status<2 )
			{
				if ( ( players[n].x == cx ) && ( players[n].y == cy ) )
				{
					fireatplayer = n ;
					break ;
				}

			}

		}

		if ( fireatplayer != 99 )
		{
			damage = (make_rnd(0)) & 0x77 ;
			damage = ((damage>>4)*10) + (damage&0x0F) ;
			damageplayer3(fireatplayer,damage) ;
			trapeffect3(fireatplayer) ;
			break ;
		}

		delay(150) ;

	}
	move_sprite(0,0,0);



}

UBYTE monsterturn(UBYTE mnum)
{
	UBYTE smallestplayer,smallestlen ;
	UBYTE canhit ;
	UBYTE mx,my ;
	UBYTE randplayer ;

	struct PLENS
	{
		UBYTE xd ;
		UBYTE yd ;
		UBYTE totd ;
		UBYTE linear ;
	} plen[4] ;
	UBYTE n, lenx, leny ;
	UBYTE smallest, newposx, newposy, retval,didit ;
	UBYTE foundvalidmove ;
	/*
   loop through goodies
		if (distx|disty<=1) then can attack
		if distx+disty>bestvalidmove then update
			check distx+1, disty+1 if valid, continue
			check distx, disty+1 if valid, continue
			check distx+1, disty if valid, continue
			else novalidmovestowardthatplayer
	  */
//   monsterattrib = 0x20 ;

	foundvalidmove = 0 ;
	smallestplayer = 0 ;
	smallestlen = 99 ;
	canhit = 0 ;
	mx = 0 ;
	my = 0 ;


	for ( n=0 ; (n!=numgoodies)&&(foundvalidmove==0) ; n++ )
	{
		if ( players[n].status<2 )
		{

			if ( players[n].x > baddies[mnum].x )
				lenx = players[n].x - baddies[mnum].x ;
			else
				lenx = baddies[mnum].x - players[n].x ;

			if ( players[n].y > baddies[mnum].y )
				leny = players[n].y - baddies[mnum].y ;
			else
				leny = baddies[mnum].y - players[n].y ;

			if ( (lenx|leny)==0x01 )
			{
				canhit=1 ;
				smallestplayer=n ;
				foundvalidmove=1 ;
				break ;
			}
			if ( (lenx+leny)<=smallestlen )
			{
				if ( lenx )
					if ( players[n].x > baddies[mnum].x )
						newposx = (baddies[mnum].x)+1 ;
					else
						newposx	= (baddies[mnum].x)-1 ;
				else
					newposx	= baddies[mnum].x ;

				if ( leny )
					if ( players[n].y > baddies[mnum].y )
						newposy = (baddies[mnum].y)+1 ;
					else
						newposy	= (baddies[mnum].y)-1 ;
				else
					newposy	= baddies[mnum].y ;

				if ( moveOK2(newposx, newposy, monstertile,n) )
				{
					smallestplayer =n ;
					smallestlen = lenx+leny ;
					mx = newposx ;
					my = newposy ;
					continue ;
				}

				newposx = baddies[mnum].x ;
				if ( moveOK2(newposx, newposy, monstertile,n) )
				{
					smallestplayer =n ;
					smallestlen = lenx+leny ;
					mx = newposx ;
					my = newposy ;
					continue ;
				}
				newposy = baddies[mnum].y ;
				if ( lenx )
					if ( players[n].x > baddies[mnum].x )
						newposx = (baddies[mnum].x)+1 ;
					else
						newposx	= (baddies[mnum].x)-1 ;
				else
					newposx	= baddies[mnum].x ;

				if ( moveOK2(newposx, newposy, monstertile,n) )
				{
					smallestplayer =n ;
					smallestlen = lenx+leny ;
					mx = newposx ;
					my = newposy ;
					continue ;
				}

			}


		}

	}


	if ( canhit )
	{
		damageplayer(smallestplayer,0) ;

	}
	else
	{
		if ( (smallestlen!=99) && (monstertile==0x23)&&((make_rnd(0))&0x80U) )
		{
			dragonbreathbattle(mnum);


		}
		else
		{
			randplayer = (make_rnd(0))&0x03 ;
			if ( ((make_rnd(0xC1U))&0x80U) && ( (monstertile==0x14) ||
												(monstertile==0x13) || (monstertile==0x1C) || (monstertile==0x23) ||
												(monstertile==0x21) || (monstertile==0x24) ) &&
				 (players[randplayer].inparty) && (players[randplayer].status==0) )
			{
				magiceffect2(3) ;
				damageplayer(randplayer,0);


			}
			else
				if ( smallestlen!=99 ) //monster can move
			{
				set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
						  (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
						  (11L*((UWORD)(baddies[mnum].y)))+(UWORD)baddies[mnum].x,1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
						  tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
												  (11L*((UWORD)(baddies[mnum].y)))+(UWORD)baddies[mnum].x)),1L) ;
				VBK_REG=0 ;
				baddies[mnum].x = mx ;
				baddies[mnum].y = my ;
				set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
						  (unsigned char*)&(monstertile),1L) ;
				VBK_REG=1 ;
				set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
						  tile_palettes+(UWORD)(monstertile),1L) ;
				VBK_REG=0 ;
			}


		}
	}
/*
   for (n=0 ; (n!=numgoodies)&&(foundvalidmove==0) ; n++)
   {
	  if (players[n].status <2)
	  {
		 plen[n].linear = 0 ;
		 if (players[n].x > baddies[mnum].x)
			plen[n].xd = players[n].x - baddies[mnum].x ;
		 else
			plen[n].xd = baddies[mnum].x - players[n].x ;
		 
		 if (players[n].y > baddies[mnum].y)
			plen[n].yd = players[n].y - baddies[mnum].y ;
		 else
			plen[n].yd = baddies[mnum].y - players[n].y ;
		 
		 if (players[n].x==baddies[mnum].x)
			plen[n].linear = 1 ;
		 
		 if (players[n].y==baddies[mnum].y)
			plen[n].linear = 1 ;
		 
		 lenx = plen[n].xd ;
		 leny = plen[n].yd ;
		 plen[n].totd = 0 ;
		 if (lenx || leny)
			(plen[n].totd)++ ;
		 while (lenx && leny)
		 {
			(plen[n].totd)++ ;
			lenx-- ;
			leny-- ;
		 }
	  
		 if (lenx) 
			plen[n].totd += lenx ;
		 if (leny) 
			plen[n].totd += leny ;
	  }
   }
   
   smallest = 0 ;
   while (((players[smallest].status)>1) && (smallest<numgoodies))
	  smallest++ ;
	  
   if (smallest==4)
	  return 2 ;
	  
   for (n=0 ; n<numgoodies ; n++)
   {
	  if (players[n].status <2)
	  {
		 if (plen[n].totd<plen[smallest].totd)
			smallest = n ;
		 
		 if ((plen[n].totd==plen[smallest].totd) && (plen[n].linear))
			smallest = n ;
	  }
   }   
   
   newposx = baddies[mnum].x ;
   newposy = baddies[mnum].y ;
   if (baddies[mnum].x>players[smallest].x)
	  newposx = baddies[mnum].x - 1 ;
   if (baddies[mnum].x<players[smallest].x)
	  newposx = baddies[mnum].x + 1 ;
   if (baddies[mnum].y>players[smallest].y)
	  newposy = baddies[mnum].y - 1 ;
   if (baddies[mnum].y<players[smallest].y)
	  newposy = baddies[mnum].y + 1 ;


		 if ( (retval=(moveOK2(newposx, newposy, monstertile,smallest)))!=2)
			if (retval==0)
			{
				  if ( (retval=(moveOK2(baddies[mnum].x, newposy, monstertile,smallest)))!=2)
				  {
					 if (retval==0)
					 {
						if ( (retval=(moveOK2(newposx, baddies[mnum].y, monstertile,smallest)))!=2)
						   if (retval!=0)
							  newposy = baddies[mnum].y ;
					 }
					 else
						newposx = baddies[mnum].x ;
				   }
				
				
			}
		 if (retval==0) //can't move anywhere
		 {
			if (monsterattrib & 0xF0)
			   if (  ((((UWORD)arand()&0x00FF)*100UL)/255UL)   <= 50UL)	
				  monstermagic(mnum,monsterattrib&0x10) ;
				  
			if (monsterattrib & 0x0F)
			   if ((  ((((UWORD)arand()&0x00FF)*100UL)/255UL)   <= 50UL) &&
					(plen[smallest].linear))
				  monsterprojectile(mnum,smallest) ;
			
			
		 }
		 if (retval==2)  //attack
		 {
			damageplayer(smallest,0) ;

			
		 }
		 if (retval==1)  //makemove
		 {
			didit = 0 ;
			
			if (monsterattrib & 0xF0U)
			   if (  ((((UWORD)arand()&0x00FF)*100UL)/255UL)   <= 50UL)	
			   {
				  monstermagic(mnum,monsterattrib&0x10U) ;
				  didit = 1 ;
			   }
				  
			if (monsterattrib & 0x0FU)
			   if ((  ((((UWORD)arand()&0x00FF)*100UL)/255UL)   <= 50UL) &&
					(plen[smallest].linear))
			   {
				  monsterprojectile(mnum,smallest) ;
				  didit = 1 ;
			   }

			if (didit==0)
			{                  
			   set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
							   (unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
								 (11L*((UWORD)(baddies[mnum].y)))+(UWORD)baddies[mnum].x,1L) ;
			   VBK_REG=1 ;
			   set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
							   tile_palettes+(UWORD)(*((unsigned char*)battlemaps+((UWORD)mapnum*121UL)+
								 (11L*((UWORD)(baddies[mnum].y)))+(UWORD)baddies[mnum].x)),1L) ;
			   VBK_REG=0 ;
			   baddies[mnum].x = newposx ;
			   baddies[mnum].y = newposy ;
			   set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
							   (unsigned char*)&(monstertile),1L) ;
			   VBK_REG=1 ;
			   set_data2(vidbase+(32L*((UWORD)(baddies[mnum].y)+1L))+(UWORD)baddies[mnum].x+1L,
							   tile_palettes+(UWORD)(monstertile),1L) ;
			   VBK_REG=0 ;
			}
		 }

  */
	if ( numalive==0 )
		return 2 ;
	else
		return 0 ;
}

unsigned char victorydat[] = {
	'V'+0x1D,'I'+0x1D,'C'+0x1D,'T'+0x1D,'O'+0x1D,'R'+0x1D,'Y'+0x1D,0x82,0x5D,0x5D,0x5D,0x5D, 
} ;

void dovictory(mnum)
{
	UBYTE r ;
	unsigned char atile ;

	writegamemessage(victorydat) ;

	if ( inside==2 )
	{
		*((unsigned char*)(0xA000+(((UWORD)dunglevel)*0x100L)+(UWORD)(dungy<<4U)+(UWORD)dungx)) = 0x40U ;


	}
	else
	{
		if ( monsters[mnum].tile==0x15 )
			*((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[mnum].y))<<6))+(UWORD)(monsters[mnum].x)) = 0x0E ;
		else
			if ( (monsters[mnum].tile!=0x13)&&(monsters[mnum].tile!=0x14) )
		{
			if ( ingenerator==0 )
			{
				*((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[mnum].y))<<6))+(UWORD)(monsters[mnum].x)) = 0x0C ;
			}
			else
			{
				disable_interrupts2() ;
				SWITCH_RAM_MBC5(3) ;
				atile = *((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[mnum].y))<<6))+(UWORD)(monsters[mnum].x)) ;
				SWITCH_RAM_MBC5(1) ;
				enable_interrupts2() ;
				//set_bkg_tiles2(6,6,1,1,&atile) ;
				*((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[mnum].y))<<6))+(UWORD)(monsters[mnum].x)) = atile ;
			}
		}
		else
			*((unsigned char*)0xA000+((UWORD)(((UWORD)(monsters[mnum].y))<<6))+(UWORD)(monsters[mnum].x)) = 0 ;

		for ( r=mnum ; r<nummonsters-1 ; r++ )
			memcpy((unsigned char*)&(monsters[r]),(unsigned char*)&(monsters[r+1]),MONSTERSIZE) ;
		nummonsters-- ;
	}

}

void doalldead()
{
	while ( 1 )
		;  
}

UBYTE montilearr[] = {
	0x1e,
	0x1d,
	0x1f,
	0x1a,
	0x20,
	0x21,
	0x13,
	0x22,
	0x1c,
	0x14,
	0x15,
	0x23,
	0x24
} ;

UBYTE checkgentile( UBYTE mx, UBYTE my )
{
	UBYTE replacetile ;

	if ( mx==playerx && my==playery )
		return 0 ;

	replacetile = *((unsigned char*)0xA000+(((UWORD)my)*64L)+((UWORD)mx));
	return(( ((generatortile<0x16)&&(replacetile==0)) ||
			 ((generatortile>0x16)&&((replacetile==4)||(replacetile==0x0B)||(replacetile==0x05)) ) ) ) ;
}

void generatemonsters()
{
	UBYTE montile,mx,my ;
	UBYTE replacetile ;
	UBYTE found ;
	UBYTE n ;

	if ( extragame )
	{
		if ( inside==0 )
		{
			if ( ((make_rnd(0xA5U))&0x80U)&&(nummonsters<31) )
			{
				montile = montilearr[make_rnd(13)&make_rnd(13)] ;

				if ( montile == 0x15 )
					return ;

				mx = make_rnd(64) ;
				my = make_rnd(64) ;
				replacetile = *((unsigned char*)0xA000+(((UWORD)my)*64L)+((UWORD)mx));
				if ( (mx!=playerx)&&(my!=playery)&&
					 ( ((montile<0x16)&&(replacetile==0)) ||
					   ((montile>0x16)&&(replacetile==4) ) ) )
				{
					*((unsigned char*)0xA000+((UWORD)(((UWORD)(my))<<6))+(UWORD)(mx)) = montile ;
					monsters[nummonsters].tile=montile ;
					monsters[nummonsters].x=mx ;
					monsters[nummonsters].y=my ;
					monsters[nummonsters].attribs=0x11 ;
					monsters[nummonsters].whichtalk=0x00 ;
					nummonsters++ ;

				}
			}



		}
		else if ( ingenerator )
		{
			found = 0 ;
			if ( nummonsters < 31 )
			{
				while ( 1 )
				{
					mx = generatorx - 1 ;
					my = generatory - 1 ;
					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}

					mx++ ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}

					mx++ ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}

					my++ ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}

					my++ ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}

					mx-- ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}

					mx-- ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}
					my-- ;

					if ( checkgentile( mx, my ) )
					{
						found = 1 ;
						break ;
					}
					break ;
				}

				if ( found )
				{
					*((unsigned char*)0xA000+((UWORD)(((UWORD)(my))<<6))+(UWORD)(mx)) = generatortile ;
					monsters[nummonsters].tile=generatortile ;
					monsters[nummonsters].x=mx ;
					monsters[nummonsters].y=my ;
					monsters[nummonsters].attribs=0x11 ;
					monsters[nummonsters].whichtalk=0x01 ;
					nummonsters++ ;
				}

			}

		}
	}
	else
	{
		if ( (inside==0)&&((make_rnd(0x89U))&0x80U)&&(nummonsters<31) )
		{
			montile = montilearr[make_rnd(13)&make_rnd(13)] ;
			mx = make_rnd(64) ;
			my = make_rnd(64) ;
			replacetile = *((unsigned char*)0xA000+(((UWORD)my)*64L)+((UWORD)mx));
			if ( (mx!=playerx)&&(my!=playery)&&
				 ( ((montile<0x16)&&(replacetile==0)) ||
				   ((montile>0x16)&&(replacetile==4) ) ) )
			{
				*((unsigned char*)0xA000+((UWORD)(((UWORD)(my))<<6))+(UWORD)(mx)) = montile ;
				monsters[nummonsters].tile=montile ;
				monsters[nummonsters].x=mx ;
				monsters[nummonsters].y=my ;
				monsters[nummonsters].attribs=0x11 ;
				monsters[nummonsters].whichtalk=0x00 ;
				nummonsters++ ;

			}



		}
	}
}


void doexodus()
{
	UBYTE cx, cy ;
	unsigned char atile ;
	unsigned char apal ;
	unsigned char ftile ;
	unsigned char fpal ;

	cx = make_rnd(11) ;
	cy = make_rnd(11) ;

	disable_interrupts2() ;
	get_bkg_tiles2(cx+1,cy+1,1,1,&atile) ;
	VBK_REG=1 ;
	get_bkg_tiles2(cx+1,cy+1,1,1,&apal) ;
	VBK_REG=0 ;
	ftile = 0x59 ;
	fpal = 0x00 ;
	set_bkg_tiles2(cx+1,cy+1,1,1,&ftile) ;
	VBK_REG=1 ;
	set_bkg_tiles2(cx+1,cy+1,1,1,&fpal) ;
	VBK_REG=0 ;
	enable_interrupts2() ;
	playerhitsfx(120U);
	//sfx(0) ;
	//delay(120) ;
	if ( (cx==5)&&(cy==5) )
		cannonfire3() ;
	disable_interrupts2() ;
	set_bkg_tiles2(cx+1,cy+1,1,1,&atile) ;
	VBK_REG=1 ;
	set_bkg_tiles2(cx+1,cy+1,1,1,&apal) ;
	VBK_REG=0 ;
	enable_interrupts2() ;


}

