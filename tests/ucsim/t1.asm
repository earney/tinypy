;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.9.0 #11195 (Linux)
;--------------------------------------------------------
	.module t1
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _prints
	.globl _putchar
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;t1.c:1: int putchar(int c) __naked
;	---------------------------------
; Function putchar
; ---------------------------------
_putchar::
;t1.c:11: __endasm;
	ld	hl, #2
	add	hl, sp
	ld	l, (hl)
	ld	a, #1
	rst	0x08
	ret
;t1.c:12: }
;t1.c:14: void prints(char *s)
;	---------------------------------
; Function prints
; ---------------------------------
_prints::
;t1.c:16: while (*s)
	pop	de
	pop	bc
	push	bc
	push	de
00101$:
	ld	a, (bc)
	or	a, a
	ret	Z
;t1.c:17: putchar(*s++);
	inc	bc
	ld	e, a
	ld	d, #0x00
	push	bc
	push	de
	call	_putchar
	pop	af
	pop	bc
;t1.c:18: }
	jr	00101$
;t1.c:20: void main(void)
;	---------------------------------
; Function main
; ---------------------------------
_main::
;t1.c:22: prints("Start.\n");
	ld	hl, #___str_0
	push	hl
	call	_prints
	pop	af
;t1.c:23: for (int j= 0; j<41; j++)
	ld	bc, #0x0000
00103$:
	ld	a, c
	sub	a, #0x29
	ld	a, b
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	NC,00101$
;t1.c:25: putchar('a');
	push	bc
	ld	hl, #0x0061
	push	hl
	call	_putchar
	pop	af
	pop	bc
;t1.c:23: for (int j= 0; j<41; j++)
	inc	bc
	jr	00103$
00101$:
;t1.c:28: prints("Done.\n");
	ld	hl, #___str_1
	push	hl
	call	_prints
	pop	af
;t1.c:29: }
	ret
___str_0:
	.ascii "Start."
	.db 0x0a
	.db 0x00
___str_1:
	.ascii "Done."
	.db 0x0a
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
