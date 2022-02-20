
	; INCLUDE	"macros.ms"
	.include	"math.s"
	.area	_BSS
tmp:
x:
	.ds	4
og:
	.ds	4
niter:
	.ds	1
	.area	_CODE
.sqrt::
	ld	a,h
	ld	(x+3),a
	ld	a,l
	ld	(x+2),a
	ld	a,d
	ld	(x+1),a
	ld	a,e
	ld	(x+0),a
	ld	a,h
	ld	(og+3),a
	ld	a,l
	ld	(og+2),a
	ld	a,d
	ld	(og+1),a
	ld	a,e
	ld	(og+0),a
	ld	a,h
	sub	#64
	rr	a
	add	#64
	ld	h,a
	ld	a,#5
	ld	(niter),a
start_for:
	ld	a,(og+3)
	ld	b,a
	ld	a,(og+2)
	ld	c,a
	push	bc
	ld	a,(og+1)
	ld	b,a
	ld	a,(og+0)
	ld	c,a
	push	bc
	ld	hl,#x
	ld	a,(hl+)	
	ld	e,a
	ld	a,(hl+)
	ld	d,a
	ld	a,(hl+)
	ld	h,(hl)
	ld	l,a
	call	.fdiv32
	ld	a,(og+3)
	ld	b,a
	ld	a,(og+2)
	ld	c,a
	push	bc
	ld	a,(og+1)
	ld	b,a
	ld	a,(og+0)
	ld	c,a
	push	bc
	call	.fadd32
	dec	h
	ld	a,(og+1)
	cp	d
	jr	nz,exit_for
	ld	a,(og+2)
	cp	l
	jr	nz,exit_for
	ld	a,(og+3)
	cp	h
	jr	nz,exit_for
	ret	
exit_for:
	ld	a,h
	ld	(og+3),a
	ld	a,l
	ld	(og+2),a
	ld	a,d
	ld	(og+1),a
	ld	a,e
	ld	(og+0),a
	ld	a,(niter)
	dec	a
	ld	(niter),a
	jr	nz,start_for
	ret	
