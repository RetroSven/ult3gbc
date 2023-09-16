echo Compiling for Gameboy Color
echo.
echo.

echo .ANALOGUE_POCKET = 0 > ..\..\lib\pocket.s

echo #ifndef _POCKET_H >  ..\..\include\gb\pocket.h
echo #define _POCKET_H >>  ..\..\include\gb\pocket.h
echo #endif >>  ..\..\include\gb\pocket.h

cd ..\..\lib
call make.bat
cd ..\examples\u3

..\..\bin\lcc -Wa-l  -Wf-bo1 -c -o sosaria.o sosaria.c
..\..\bin\lcc -Wa-l  -Wf-bo2 -c -o u3tiles.o u3tiles.c
..\..\bin\lcc -Wa-l  -Wf-bo3 -c -o intro.o intro.c
..\..\bin\lcc -Wa-l  -Wf-bo4 -c -o u3tiles2.o u3tiles2.c
..\..\bin\lcc -Wa-l  -Wf-bo5 -c -o funcs5.o funcs5.c
..\..\bin\lcc -Wa-l  -Wf-bo6 -c -o battle.o battle.c
..\..\bin\lcc -Wa-l  -Wf-bo7 -c -o battle2.o battle2.c
..\..\bin\lcc -Wa-l  -Wf-bo8 -c -o battle3.o battle3.c
..\..\bin\lcc -Wa-l  -Wf-bo9 -c -o menucmd.o menucmd.c
..\..\bin\lcc -Wa-l  -Wf-bo10 -c -o towns1.o towns1.c
..\..\bin\lcc -Wa-l  -Wf-bo11 -c -o towns2.o towns2.c
..\..\bin\lcc -Wa-l  -Wf-bo12 -c -o towns3.o towns3.c
..\..\bin\lcc -Wa-l  -Wf-bo13 -c -o towns4.o towns4.c
..\..\bin\lcc -Wa-l  -Wf-bo14 -c -o peergem.o peergem.c
..\..\bin\lcc -Wa-l  -Wf-bo15 -c -o menucmd2.o menucmd2.c
..\..\bin\lcc -Wa-l  -Wf-bo16 -c -o menucmd3.o menucmd3.c
..\..\bin\lcc -Wa-l  -Wf-bo17 -c -o dungeon1.o dungeon1.c
..\..\bin\lcc -Wa-l  -Wf-bo18 -c -o dungfunc.o dungfunc.c
..\..\bin\lcc -Wa-l  -Wf-bo19 -c -o dungfun2.o dungfun2.c
..\..\bin\lcc -Wa-l  -Wf-bo20 -c -o talkcmd.o talkcmd.c
..\..\bin\lcc -Wa-l  -Wf-bo21 -c -o talkcmd2.o talkcmd2.c
..\..\bin\lcc -Wa-l  -Wf-bo22 -c -o u3music1.o u3music1.c
..\..\bin\lcc -Wa-l  -Wf-bo23 -c -o u3music2.o u3music2.c
..\..\bin\lcc -Wa-l  -Wf-bo24 -c -o u3music3.o u3music3.c
..\..\bin\lcc -Wa-l  -Wf-bo25 -c -o newsos.o newsos.c
..\..\bin\lcc -Wa-l  -Wf-bo26 -c -o cheat.o cheat.c
..\..\bin\lcc -Wa-l  -Wf-bo27 -c -o u3music4.o u3music4.c
..\..\bin\lcc -Wa-l  -Wf-bo28 -c -o postexo1.o postexo1.c
..\..\bin\lcc -Wa-l  -Wf-bo29 -c -o u4towns1.o u4towns1.c
..\..\bin\lcc -Wa-l  -Wf-bo30 -c -o u4towns2.o u4towns2.c
..\..\bin\lcc -Wa-l  -Wf-bo31 -c -o u4towns3.o u4towns3.c
..\..\bin\lcc -Wa-l  -Wf-bo32 -c -o u4towns4.o u4towns4.c
..\..\bin\lcc -Wa-l  -Wf-bo33 -c -o u4towns5.o u4towns5.c
..\..\bin\lcc -Wa-l  -Wf-bo34 -c -o talkcmd3.o talkcmd3.c
..\..\bin\lcc -Wa-l  -Wf-bo35 -c -o talkcmd4.o talkcmd4.c
..\..\bin\lcc -Wa-l  -Wf-bo37 -c -o shoot2.o shoot2.c
..\..\bin\lcc -Wa-l  -Wf-bo38 -c -o shoot3.o shoot3.c
..\..\bin\lcc -Wa-l  -Wf-bo36 -c -o shoot.o shoot.c
..\..\bin\lcc -Wa-l  -Wf-bo39 -c -o demonfrm.o demonfrm.c
..\..\bin\lcc -Wa-l  -Wf-bo0 -c -o ult3.o ult3.c
..\..\bin\lcc -Wa-l  -Wf-bo40 -c -o explode.o explode.c
..\..\bin\lcc -Wa-l  -Wf-bo41 -c -o explode2.o explode2.c
..\..\bin\lcc -Wa-l  -Wf-bo42 -c -o explode3.o explode3.c
..\..\bin\lcc -Wa-l  -Wf-bo43 -c -o wtitle1.o wtitle1.c
..\..\bin\lcc -Wa-l  -Wf-bo44 -c -o wtitle2.o wtitle2.c
..\..\bin\lcc -Wa-l  -Wf-bo45 -c -o wtitle3.o wtitle3.c
..\..\bin\lcc -Wa-l  -Wf-bo46 -c -o wtitle4.o wtitle4.c
..\..\bin\lcc -Wa-l  -Wf-bo47 -c -o wtitle5.o wtitle5.c
..\..\bin\lcc -Wa-l  -Wf-bo48 -c -o wtitle6.o wtitle6.c
..\..\bin\lcc -Wl-m -Wl-yo64 -Wl-ya4 -Wl-yt0x1B -Wl-yp0x143=0x80 -o ult3.gb *.o
del ..\..\..\..\..\ult3.gb
move ult3.gb ..\..\..\..\..

echo.
echo.
echo Finished compiling for Gameboy Color
