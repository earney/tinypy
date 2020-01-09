;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.9.0 #11195 (Linux)
;--------------------------------------------------------
	.module test
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _calloc
	.globl ___assert
	.globl _printf
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
;test.c:5: int putchar(int c) __naked
;	---------------------------------
; Function putchar
; ---------------------------------
_putchar::
;test.c:15: __endasm;
	ld	hl, #2
	add	hl, sp
	ld	l, (hl)
	ld	a, #1
	rst	0x08
	ret
;test.c:16: }
;test.c:40: int main(int argc, char * argv[]) {
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
;test.c:42: a=calloc(1, sizeof(struct s3));
	ld	hl, #0x0008
	push	hl
	ld	l, #0x01
	push	hl
	call	_calloc
	pop	af
	pop	af
;test.c:43: a->i=1;
	ld	c,l
	ld	b,h
	ld	(hl), #0x01
	inc	hl
	ld	(hl), #0x00
;test.c:45: a->t=calloc(1, sizeof(struct s1));
	ld	l, c
	ld	h, b
	inc	hl
	inc	hl
	push	hl
	push	bc
	ld	de, #0x0006
	push	de
	ld	de, #0x0001
	push	de
	call	_calloc
	pop	af
	pop	af
	ex	de,hl
	pop	bc
	pop	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
;test.c:47: printf("%d", a->i);
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	bc
	push	de
	ld	hl, #___str_0
	push	hl
	call	_printf
	pop	af
	pop	af
;test.c:48: assert(a->i == 1);
	pop	hl
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, c
	dec	a
	or	a, b
	jr	Z,00104$
	ld	hl, #0x0030
	push	hl
	ld	hl, #___str_3
	push	hl
	ld	hl, #___str_2
	push	hl
	ld	hl, #___str_1
	push	hl
	call	___assert
	ld	hl, #8
	add	hl, sp
	ld	sp, hl
00104$:
;test.c:50: return 0;
	ld	hl, #0x0000
;test.c:51: }
	pop	ix
	ret
___str_0:
	.ascii "%d"
	.db 0x00
___str_1:
	.ascii "a->i == 1"
	.db 0x00
___str_2:
	.ascii "main"
	.db 0x00
___str_3:
	.ascii "test.c"
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
