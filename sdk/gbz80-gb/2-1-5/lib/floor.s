
	; INCLUDE	"macros.ms"
	.include	"math.s"
	.module	floor_ms
	.area	_CODE
.floor::
	ld	b,h
	ld	a,h
	and	#0x7f
	cp	#64
	jr	nc,floor_gteqone
	ld	h,#0
	ld	l,h
	ld	d,h
	ld	e,h
	ret	
floor_gteqone:
	or	a
	rr	l
	rr	d
	rr	e
	inc	a
	cp	#64+24
	jr	c,floor_gteqone
	ld	h,a
	ld	a,b
	and	#0x80
	or	h
	ld	h,a
	call	fpnorm
	ret	
.dec::
	ld	b,h
	ld	a,h
	and	#0x7f
	cp	#65
	ret	c
	cp	#64+24
	jr	c,1$
	ld	hl,#0
	ld	d,h
	ld	e,h
	ret	
1$:
	or	a
	rl	e
	rl	d
	rl	l
	dec	a
	cp	#64
	jr	nz,1$
	ld	h,a
	ld	a,b
	and	#0x80
	or	h
	ld	h,a
	call	fpnorm
	ret	
