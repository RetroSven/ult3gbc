	.include	"global.s"

	.area	_CODE

	;; Copy part (size = DE) of the VRAM from (BC) to (HL)
.copy_vram::
1$:
	LDH	A,(.STAT)
.if .ANALOGUE_POCKET
	AND	#0x40
.else
	AND	#0x02
.endif
	JR	NZ,1$

	LD	A,(BC)
	LD	(HL+),A
	INC	BC
	DEC	DE
	LD	A,D
	OR	E
	JR	NZ,1$
	RET

_set_data::
_get_data::
	PUSH	BC

	LDA	HL,9(SP)	; Skip return address and registers
	LD	D,(HL)		; DE = len
	DEC	HL
	LD	E,(HL)
	DEC	HL
	LD	B,(HL)		; BC = src
	DEC	HL
	LD	C,(HL)
	DEC	HL
	LD	A,(HL-)		; HL = dst
	LD	L,(HL)
	LD	H,A

	CALL	.copy_vram

	POP	BC
	RET
