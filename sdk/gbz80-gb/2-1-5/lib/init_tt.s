	.include	"global.s"

	.area	_CODE

	;; Initialize part (size = DE) of the VRAM at (HL) with B
.init_vram::
1$:
	LDH	A,(.STAT)
.if .ANALOGUE_POCKET
	AND	#0x40
.else
	AND	#0x02
.endif
	JR	NZ,1$

	LD	(HL),B
	INC	HL
	DEC	DE
	LD	A,D
	OR	E
	JR	NZ,1$
	RET
	;; Initialize window tile table with B
.init_wtt::
	LDH	A,(.LCDC)
.if .ANALOGUE_POCKET
	BIT	1,A
.else
	BIT	6,A
.endif
	JR	NZ,1$
	LD	HL,#0x9800	; HL = origin
	JR	.init_tt
1$:
	LD	HL,#0x9C00	; HL = origin
	JR	.init_tt
	;; Initialize background tile table with B
.init_btt::
	LDH	A,(.LCDC)
.if .ANALOGUE_POCKET
	BIT	4,A
.else
	BIT	3,A
.endif
	JR	NZ,1$
	LD	HL,#0x9800	; HL = origin
	JR	.init_tt
1$:
	LD	HL,#0x9C00	; HL = origin
;	JR	.init_tt
.init_tt::
	LD	DE,#0x0400	; One whole GB Screen
	JP	.init_vram
