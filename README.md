# ult3gbc
Ultima 3 port to the Gameboy Color

Graphics were lifted from the C64 16x16 tiles and shrunk to 8x8.

Music was converted from the C64 SIDs.

Game logic, text, etc were taken from the MSDOS version.  In order to achieve the highest fidelity, the MSDOS version was decompiled and portions were converted to C.  Things like when a ship a generated, to-hit/damage battle calculations, whirlpool movement, etc are all maintained.  Therefore this version should play exactly like the MSDOS version.

This was done back in 2001.  The code is a frightful mess and I know it, so don't judge.  :)  I wish I had documented some more portions because as I looked through it again 20 years later it's hard to determine how certain things work (GBC idiosyncrasies).

How to play:

Press Start at both of the intro screens.

Press the A button to bring up the menu and to make selections 
Press the B button to pass or to cancel out of menus 
Press the D-Pad to move around 

Instructions for the original ultima 3 game can be found here:
	http://www.uo.com/archive/ultima3/u3encore.html

The one thing that seems to cause confusion is the menu.
When you press the "A" button, you will be presented with a menu of options
(Attack, Board, etc...). If you press the D-Pad left or right, you will get
the 2nd set of options (Transact, Unlock, etc.) 


There are two savegame files included in this repository:

U3START.SAV - Use this to "quick-start" the Ultima 3 game.  It includes a 
              preconstructed party that will start off at the very beginning 
              of the original Ultima 3 game.

U4START.SAV - Use this to "quick-start" the additional adventure that 
              immediately follows the original Ultima 3 game.  You will
              start off exactly as you would when you finish the original
              Ultima 3 game.  

IMPORTANT NOTE

When you finish Ultima 3 and start the new adventure, do not disperse your
party and form another one.  If you do this, you will start at the
beginning of Ultima 3 - you will not continue the post-Ultima 3 adventure
with the new players.

The 11 clues in the second adventure are a logic puzzle.  Here is an online resource to help solve it:

https://www.jsingler.de/apps/logikloeser/?language=en#(at:s,items:!(!(cleric,ranger,wizard,fighter,thief),!(orc,giant,balron,demon,dragon),!(cave,dungeon,field,castle,other),!(first,second,third,fourth,fifth)),ms:t,n:!(),nc:4,ni:5,p:!(),v:0)


Here's my old webpage with more details about this project and others that I've done:

https://web.archive.org/web/20170522203625/http://sven.50webs.org/ultima3.html
