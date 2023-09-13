
	.include	"global.s"
	; INCLUDE	"wait_hbl.mh"
	.globl	.cr_curs
	.globl	.adv_curs
	.globl	.cury,.curx
	.globl	.display_off
	sfont_handle_sizeof	=	3
	sfont_handle_font	=	1
	sfont_handle_first_tile	=	0
	FONT_256ENCODING	=	0
	FONT_128ENCODING	=	1
	FONT_NOENCODING	=	2
	FONT_BCOMPRESSED	=	2
	.CR	=  0x0A
	.SPACE	=	0x00
	.MAX_FONTS	=  6
	.area	_HEADER(ABS)
	.org	.MODE_TABLE+4*.T_MODE
	JP	.tmode
	.module	font.ms
	.globl	.fg_colour
	.globl	.bg_colour
	.area	_BSS
font_current::
	.ds	sfont_handle_sizeof
font_first_free_tile::
	.ds	1
font_table::
	.ds	sfont_handle_sizeof*.MAX_FONTS
	.area	_CODE
font_copy_uncompressed::
	ld	a,d
	or	e
	ret	z
	ld	a,h
	cp	#0x98
	jr	c,4$
	sub	#0x98-0x88
	ld	h,a
4$:
	xor	a
	cp	e
	jr	nz,1$
	dec	d
1$:
	ldh	a,(.STAT)
	bit	6,a
	jr	nz,#.-4
	ld	a,(bc)
	ld	(hl+),a
	inc	bc
	ldh	a,(.STAT)
	bit	6,a
	jr	nz,#.-4
	ld	a,(bc)
	ld	(hl),a
	inc	bc
	inc	l
	jr	nz,2$
	inc	h
	ld	a,h
	cp	#0x98
	jr	nz,2$
	ld	h,#0x88
2$:
	dec	e
	jr	nz,1$
	dec	d
	bit	7,d
	jr	z,1$
	ret	
font_copy_compressed::
	ld	a,d
	or	e
	ret	z
	ld	a,h
	cp	#0x98
	jr	c,font_copy_compressed_loop
	sub	#0x98-0x88
	ld	h,a
font_copy_compressed_loop:
	push	de
	ld	a,(bc)
	ld	e,a
	inc	bc
	push	bc
	ld	bc,#0
	ld	a,(.bg_colour)
	bit	0,a
	jr	z,font_copy_compressed_bg_grey1
	ld	b,#0xFF
font_copy_compressed_bg_grey1:
	bit	1,a
	jr	z,font_copy_compressed_bg_grey2
	ld	c,#0xFF
font_copy_compressed_bg_grey2:
	ld	d,a
	ld	a,(.fg_colour)
	xor	d
	ld	d,a
	bit	0,d
	jr	z,font_copy_compressed_grey1
	ld	a,e
	xor	b
	ld	b,a
font_copy_compressed_grey1:
	bit	1,d
	jr	z,font_copy_compressed_grey2
	ld	a,e
	xor	c
	ld	c,a
font_copy_compressed_grey2:
	ldh	a,(.STAT)
	bit	6,a
	jr	nz,#.-4
	ld	(hl),b
	inc	hl
	ldh	a,(.STAT)
	bit	6,a
	jr	nz,#.-4
	ld	(hl),c
	inc	hl
	ld	a,h
	cp	#0x98
	jr	nz,1$
	ld	h,#0x88
1$:
	pop	bc
	pop	de
	dec	de
	ld	a,d
	or	e
	jr	nz,font_copy_compressed_loop
	ret	
font_load::
	call	.display_off
	push	hl
	ld	hl,#font_table+sfont_handle_font
	ld	b,#.MAX_FONTS
font_load_find_slot:
	ld	a,(hl)	
	inc	hl
	or	(hl)
	cp	#0
	jr	z,font_load_found
	inc	hl
	inc	hl
	dec	b
	jr	nz,font_load_find_slot
	pop	hl
	ld	hl,#0
	jr	font_load_exit
font_load_found:
	pop	de
	ld	(hl),d
	dec	hl
	ld	(hl),e
	ld	a,(font_first_free_tile)
	dec	hl
	ld	(hl),a
	push	hl
	call	font_set
	ld	a,(.mode)
	and	#.T_MODE
	call	nz,font_copy_current
	ld	hl,#font_current+sfont_handle_font
	ld	a,(hl+)
	ld	h,(hl)
	ld	l,a
	inc	hl
	ld	a,(font_first_free_tile)
	add	a,(hl)
	ld	(font_first_free_tile),a
	pop	hl
font_load_exit:
	LDH	A,(.LCDC)
	OR	#0b10000001
	AND	#0b11100111
	LDH	(.LCDC),A
	RET	
font_copy_current::
	ld	hl,#font_current+sfont_handle_font
	ld	a,(hl+)
	ld	h,(hl)
	ld	l,a
	inc	hl
	ld	e,(hl)
	ld	d,#0
	rl	e
	rl	d
	rl	e
	rl	d
	rl	e
	rl	d
	dec	hl
	ld	a,(hl)	
	push	af
	and	#3
	ld	bc,#128
	cp	#FONT_128ENCODING
	jr	z,font_copy_current_copy
	ld	bc,#0
	cp	#FONT_NOENCODING
	jr	z,font_copy_current_copy
	ld	bc,#256
font_copy_current_copy:
	inc	hl
	inc	hl
	add	hl,bc
	ld	c,l
	ld	b,h
	ld	a,(font_current+sfont_handle_first_tile)	
	ld	l,a
	ld	h,#0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	a,#0x90
	add	a,h
	ld	h,a
	pop	af
	bit	FONT_BCOMPRESSED,a
	jp	z,font_copy_uncompressed
	jp	font_copy_compressed
font_set::
	ld	a,(hl+)
	ld	(font_current),a
	ld	a,(hl+)
	ld	(font_current+1),a
	ld	a,(hl+)
	ld	(font_current+2),a
	ret	
.put_char::
	cp	#.CR
	jr	nz,1$
	push	af
	ld	a,(.mode)
	and	#.M_NO_INTERP
	jr	nz,2$
	call	.cr_curs
	pop	af
	ret	
2$:
	pop	af
1$:
	CALL	.set_char
	CALL	.adv_curs
	RET	
.out_char::
	CALL	.set_char
	CALL	.adv_curs
	RET	
.del_char::
	CALL	.rew_curs
	LD	A,#.SPACE
	CALL	.set_char
	RET	
.set_char:
	push	af
	ld	a,(font_current+2)
	or	a
	jr	nz,3$
	call	_font_init
	xor	a
	ld	(font_first_free_tile),a
	.globl	_font_ibm_fixed
	ld	hl,#_font_ibm_fixed
	call	font_load
3$:
	pop	af
	push	bc
	push	de
	push	hl
	ld	e,a
	ld	hl,#font_current+sfont_handle_font
	ld	a,(hl+)
	ld	h,(hl)
	ld	l,a
	ld	a,(hl+)
	and	#3
	cp	#FONT_NOENCODING
	jr	z,set_char_no_encoding
	inc	hl
	ld	d,#0
	add	hl,de
	ld	e,(hl)	
set_char_no_encoding:
	ld	a,(font_current+0)
	add	a,e
	ld	e,a
	LD	A,(.cury) 
	LD	L,A
	LD	H,#0x00
	ADD	HL,HL
	ADD	HL,HL
	ADD	HL,HL
	ADD	HL,HL
	ADD	HL,HL
	LD	A,(.curx) 
	LD	C,A
	LD	B,#0x00
	ADD	HL,BC
	LD	BC,#0x9800
	ADD	HL,BC
	ldh	a,(.STAT)
	bit	6,a
	jr	nz,#.-4
	LD	(HL),E
	POP	HL
	POP	DE
	POP	BC
	RET	
_putchar::
	LDA	HL,2(SP) 
	LD	A,(HL) 
	CALL	.put_char
	RET	
_setchar::
	push	bc
	LDA	HL,4(SP) 
	LD	A,(HL) 
	CALL	.set_char
	pop	bc
	RET	
_font_load::
	push	bc
	LDA	HL,4(SP) 
	LD	A,(HL) 
	inc	hl
	ld	h,(hl)
	ld	l,a
	call	font_load
	push	hl
	pop	de
	pop	bc
	RET	
_font_set::
	push	bc
	LDA	HL,4(SP) 
	LD	A,(HL) 
	inc	hl
	ld	h,(hl)
	ld	l,a
	call	font_set
	pop	bc
	ld	de,#0
	RET	
_font_init::
	push	bc
	.globl	.tmode
	call	.tmode
	ld	a,#1
	ld	(font_first_free_tile),a
	xor	a
	ld	hl,#font_table
	ld	b,#sfont_handle_sizeof*.MAX_FONTS
1$:
	ld	(hl+),a
	dec	b
	jr	nz,1$
	ld	a,#3
	ld	(.fg_colour),a
	ld	a,#0
	ld	(.bg_colour),a
	call	.cls
	pop	bc
	ret	
_print_repeat::
	push	bc
	lda	hl,4(sp)
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	xor	a
	cp	d
	jr	nz,_print_repeat_go
	pop	bc
	ret	
_print_repeat_go:
	ld	a,e
	push	de
	call	.put_char
	pop	de
	dec	d
	jr	nz,_print_repeat_go
	pop	bc
	ret	
_gotoxy::
	lda	hl,2(sp)
	ld	a,(hl+)
	ld	(.curx),a
	ld	a,(hl)
	ld	(.cury),a
	ret	
_cls::
.cls::
	PUSH	DE
	PUSH	HL
	LD	HL,#0x9800
	LD	E,#0x20
1$:
	LD	D,#0x20
2$:
	ldh	a,(.STAT)
	bit	6,a
	jr	nz,#.-4
	LD	(HL),#.SPACE
	INC	HL
	DEC	D
	JR	NZ,2$
	DEC	E
	JR	NZ,1$
	POP	HL
	POP	DE
	RET	
_posx::
	LD	A,(.mode)
	AND	#.T_MODE
	JR	NZ,1$
	PUSH	BC
	CALL	.tmode
	POP	BC
1$:
	LD	A,(.curx)
	LD	E,A
	RET	
_posy::
	LD	A,(.mode)
	AND	#.T_MODE
	JR	NZ,1$
	PUSH	BC
	CALL	.tmode
	POP	BC
1$:
	LD	A,(.cury)
	LD	E,A
	RET	
.rew_curs:
	PUSH	HL
	LD	HL,#.curx
	XOR	A
	CP	(HL)
	JR	Z,1$
	DEC	(HL)
	JR	99$
1$:
	LD	(HL),#.MAXCURSPOSX
	LD	HL,#.cury
	XOR	A
	CP	(HL)
	JR	Z,99$
	DEC	(HL)
99$:
	POP	HL
	RET	
.cr_curs::
	PUSH	HL
	XOR	A
	LD	(.curx),A
	LD	HL,#.cury
	LD	A,#.MAXCURSPOSY
	CP	(HL)
	JR	Z,2$
	INC	(HL)
	JR	99$
2$:
	CALL	.scroll
99$:
	POP	HL
	RET	
.adv_curs::
	PUSH	HL
	LD	HL,#.curx
	LD	A,#.MAXCURSPOSX
	CP	(HL)
	JR	Z,1$
	INC	(HL)
	JR	99$
1$:
	LD	(HL),#0x00
	LD	HL,#.cury
	LD	A,#.MAXCURSPOSY
	CP	(HL)
	JR	Z,2$
	INC	(HL)
	JR	99$
2$:
	LD	A,(.mode)
	AND	#.M_NO_SCROLL
	JR	Z,3$
	XOR	A
	LD	(.cury),A
	LD	(.curx),A
	JR	99$
3$:
	CALL	.scroll
99$:
	POP	HL
	RET	
.scroll:
	PUSH	BC
	PUSH	DE
	PUSH	HL
	LD	HL,#0x9800
	LD	BC,#0x9800+0x20
	LD	E,#0x20-0x01
1$:
	LD	D,#0x20
2$:
	LDH	A,(.STAT)
	AND	#0x40
	JR	NZ,2$
	LD	A,(BC)
	LD	(HL+),A
	INC	BC
	DEC	D
	JR	NZ,2$
	DEC	E
	JR	NZ,1$
	LD	D,#0x20
3$:
	LDH	A,(.STAT)
	AND	#0x40
	JR	NZ,3$
	LD	A,#.SPACE
	LD	(HL+),A
	DEC	D
	JR	NZ,3$
	POP	HL
	POP	DE
	POP	BC
	RET	
	.area	_BSS
.curx::
	.ds	0x01
.cury::
	.ds	0x01
	.area	_CODE
	.globl	.vbl
	.globl	.lcd
	.globl	.int_0x40
	.globl	.int_0x48
	.globl	.remove_int
.tmode::
	DI	
	LDH	A,(.LCDC)
	BIT	0,A
	JR	Z,1$
	CALL	.display_off
	LD	BC,#.vbl
	LD	HL,#.int_0x40
	CALL	.remove_int
	LD	BC,#.lcd
	LD	HL,#.int_0x48
	CALL	.remove_int
1$:
	CALL	.tmode_out
	LDH	A,(.LCDC)
	OR	#0b10000001
	AND	#0b11100111
	LDH	(.LCDC),A
	EI	
	RET	
.tmode_out::
	XOR	A
	LD	(.curx),A
	LD	(.cury),A
	CALL	.cls
	LD	A,#.T_MODE
	LD	(.mode),A
	RET	
