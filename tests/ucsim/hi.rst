                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.9.0 #11195 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module hi
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _tx_str
                                     13 	.globl _tx_char
                                     14 	.globl _TF2
                                     15 	.globl _EXF2
                                     16 	.globl _RCLK
                                     17 	.globl _TCLK
                                     18 	.globl _EXEN2
                                     19 	.globl _TR2
                                     20 	.globl _C_T2
                                     21 	.globl _CP_RL2
                                     22 	.globl _T2CON_7
                                     23 	.globl _T2CON_6
                                     24 	.globl _T2CON_5
                                     25 	.globl _T2CON_4
                                     26 	.globl _T2CON_3
                                     27 	.globl _T2CON_2
                                     28 	.globl _T2CON_1
                                     29 	.globl _T2CON_0
                                     30 	.globl _PT2
                                     31 	.globl _ET2
                                     32 	.globl _CY
                                     33 	.globl _AC
                                     34 	.globl _F0
                                     35 	.globl _RS1
                                     36 	.globl _RS0
                                     37 	.globl _OV
                                     38 	.globl _F1
                                     39 	.globl _P
                                     40 	.globl _PS
                                     41 	.globl _PT1
                                     42 	.globl _PX1
                                     43 	.globl _PT0
                                     44 	.globl _PX0
                                     45 	.globl _RD
                                     46 	.globl _WR
                                     47 	.globl _T1
                                     48 	.globl _T0
                                     49 	.globl _INT1
                                     50 	.globl _INT0
                                     51 	.globl _TXD
                                     52 	.globl _RXD
                                     53 	.globl _P3_7
                                     54 	.globl _P3_6
                                     55 	.globl _P3_5
                                     56 	.globl _P3_4
                                     57 	.globl _P3_3
                                     58 	.globl _P3_2
                                     59 	.globl _P3_1
                                     60 	.globl _P3_0
                                     61 	.globl _EA
                                     62 	.globl _ES
                                     63 	.globl _ET1
                                     64 	.globl _EX1
                                     65 	.globl _ET0
                                     66 	.globl _EX0
                                     67 	.globl _P2_7
                                     68 	.globl _P2_6
                                     69 	.globl _P2_5
                                     70 	.globl _P2_4
                                     71 	.globl _P2_3
                                     72 	.globl _P2_2
                                     73 	.globl _P2_1
                                     74 	.globl _P2_0
                                     75 	.globl _SM0
                                     76 	.globl _SM1
                                     77 	.globl _SM2
                                     78 	.globl _REN
                                     79 	.globl _TB8
                                     80 	.globl _RB8
                                     81 	.globl _TI
                                     82 	.globl _RI
                                     83 	.globl _P1_7
                                     84 	.globl _P1_6
                                     85 	.globl _P1_5
                                     86 	.globl _P1_4
                                     87 	.globl _P1_3
                                     88 	.globl _P1_2
                                     89 	.globl _P1_1
                                     90 	.globl _P1_0
                                     91 	.globl _TF1
                                     92 	.globl _TR1
                                     93 	.globl _TF0
                                     94 	.globl _TR0
                                     95 	.globl _IE1
                                     96 	.globl _IT1
                                     97 	.globl _IE0
                                     98 	.globl _IT0
                                     99 	.globl _P0_7
                                    100 	.globl _P0_6
                                    101 	.globl _P0_5
                                    102 	.globl _P0_4
                                    103 	.globl _P0_3
                                    104 	.globl _P0_2
                                    105 	.globl _P0_1
                                    106 	.globl _P0_0
                                    107 	.globl _TH2
                                    108 	.globl _TL2
                                    109 	.globl _RCAP2H
                                    110 	.globl _RCAP2L
                                    111 	.globl _T2CON
                                    112 	.globl _B
                                    113 	.globl _ACC
                                    114 	.globl _PSW
                                    115 	.globl _IP
                                    116 	.globl _P3
                                    117 	.globl _IE
                                    118 	.globl _P2
                                    119 	.globl _SBUF
                                    120 	.globl _SCON
                                    121 	.globl _P1
                                    122 	.globl _TH1
                                    123 	.globl _TH0
                                    124 	.globl _TL1
                                    125 	.globl _TL0
                                    126 	.globl _TMOD
                                    127 	.globl _TCON
                                    128 	.globl _PCON
                                    129 	.globl _DPH
                                    130 	.globl _DPL
                                    131 	.globl _SP
                                    132 	.globl _P0
                                    133 	.globl _lbuf
                                    134 	.globl _g_dc
                                    135 	.globl _li
                                    136 ;--------------------------------------------------------
                                    137 ; special function registers
                                    138 ;--------------------------------------------------------
                                    139 	.area RSEG    (ABS,DATA)
      000000                        140 	.org 0x0000
                           000080   141 _P0	=	0x0080
                           000081   142 _SP	=	0x0081
                           000082   143 _DPL	=	0x0082
                           000083   144 _DPH	=	0x0083
                           000087   145 _PCON	=	0x0087
                           000088   146 _TCON	=	0x0088
                           000089   147 _TMOD	=	0x0089
                           00008A   148 _TL0	=	0x008a
                           00008B   149 _TL1	=	0x008b
                           00008C   150 _TH0	=	0x008c
                           00008D   151 _TH1	=	0x008d
                           000090   152 _P1	=	0x0090
                           000098   153 _SCON	=	0x0098
                           000099   154 _SBUF	=	0x0099
                           0000A0   155 _P2	=	0x00a0
                           0000A8   156 _IE	=	0x00a8
                           0000B0   157 _P3	=	0x00b0
                           0000B8   158 _IP	=	0x00b8
                           0000D0   159 _PSW	=	0x00d0
                           0000E0   160 _ACC	=	0x00e0
                           0000F0   161 _B	=	0x00f0
                           0000C8   162 _T2CON	=	0x00c8
                           0000CA   163 _RCAP2L	=	0x00ca
                           0000CB   164 _RCAP2H	=	0x00cb
                           0000CC   165 _TL2	=	0x00cc
                           0000CD   166 _TH2	=	0x00cd
                                    167 ;--------------------------------------------------------
                                    168 ; special function bits
                                    169 ;--------------------------------------------------------
                                    170 	.area RSEG    (ABS,DATA)
      000000                        171 	.org 0x0000
                           000080   172 _P0_0	=	0x0080
                           000081   173 _P0_1	=	0x0081
                           000082   174 _P0_2	=	0x0082
                           000083   175 _P0_3	=	0x0083
                           000084   176 _P0_4	=	0x0084
                           000085   177 _P0_5	=	0x0085
                           000086   178 _P0_6	=	0x0086
                           000087   179 _P0_7	=	0x0087
                           000088   180 _IT0	=	0x0088
                           000089   181 _IE0	=	0x0089
                           00008A   182 _IT1	=	0x008a
                           00008B   183 _IE1	=	0x008b
                           00008C   184 _TR0	=	0x008c
                           00008D   185 _TF0	=	0x008d
                           00008E   186 _TR1	=	0x008e
                           00008F   187 _TF1	=	0x008f
                           000090   188 _P1_0	=	0x0090
                           000091   189 _P1_1	=	0x0091
                           000092   190 _P1_2	=	0x0092
                           000093   191 _P1_3	=	0x0093
                           000094   192 _P1_4	=	0x0094
                           000095   193 _P1_5	=	0x0095
                           000096   194 _P1_6	=	0x0096
                           000097   195 _P1_7	=	0x0097
                           000098   196 _RI	=	0x0098
                           000099   197 _TI	=	0x0099
                           00009A   198 _RB8	=	0x009a
                           00009B   199 _TB8	=	0x009b
                           00009C   200 _REN	=	0x009c
                           00009D   201 _SM2	=	0x009d
                           00009E   202 _SM1	=	0x009e
                           00009F   203 _SM0	=	0x009f
                           0000A0   204 _P2_0	=	0x00a0
                           0000A1   205 _P2_1	=	0x00a1
                           0000A2   206 _P2_2	=	0x00a2
                           0000A3   207 _P2_3	=	0x00a3
                           0000A4   208 _P2_4	=	0x00a4
                           0000A5   209 _P2_5	=	0x00a5
                           0000A6   210 _P2_6	=	0x00a6
                           0000A7   211 _P2_7	=	0x00a7
                           0000A8   212 _EX0	=	0x00a8
                           0000A9   213 _ET0	=	0x00a9
                           0000AA   214 _EX1	=	0x00aa
                           0000AB   215 _ET1	=	0x00ab
                           0000AC   216 _ES	=	0x00ac
                           0000AF   217 _EA	=	0x00af
                           0000B0   218 _P3_0	=	0x00b0
                           0000B1   219 _P3_1	=	0x00b1
                           0000B2   220 _P3_2	=	0x00b2
                           0000B3   221 _P3_3	=	0x00b3
                           0000B4   222 _P3_4	=	0x00b4
                           0000B5   223 _P3_5	=	0x00b5
                           0000B6   224 _P3_6	=	0x00b6
                           0000B7   225 _P3_7	=	0x00b7
                           0000B0   226 _RXD	=	0x00b0
                           0000B1   227 _TXD	=	0x00b1
                           0000B2   228 _INT0	=	0x00b2
                           0000B3   229 _INT1	=	0x00b3
                           0000B4   230 _T0	=	0x00b4
                           0000B5   231 _T1	=	0x00b5
                           0000B6   232 _WR	=	0x00b6
                           0000B7   233 _RD	=	0x00b7
                           0000B8   234 _PX0	=	0x00b8
                           0000B9   235 _PT0	=	0x00b9
                           0000BA   236 _PX1	=	0x00ba
                           0000BB   237 _PT1	=	0x00bb
                           0000BC   238 _PS	=	0x00bc
                           0000D0   239 _P	=	0x00d0
                           0000D1   240 _F1	=	0x00d1
                           0000D2   241 _OV	=	0x00d2
                           0000D3   242 _RS0	=	0x00d3
                           0000D4   243 _RS1	=	0x00d4
                           0000D5   244 _F0	=	0x00d5
                           0000D6   245 _AC	=	0x00d6
                           0000D7   246 _CY	=	0x00d7
                           0000AD   247 _ET2	=	0x00ad
                           0000BD   248 _PT2	=	0x00bd
                           0000C8   249 _T2CON_0	=	0x00c8
                           0000C9   250 _T2CON_1	=	0x00c9
                           0000CA   251 _T2CON_2	=	0x00ca
                           0000CB   252 _T2CON_3	=	0x00cb
                           0000CC   253 _T2CON_4	=	0x00cc
                           0000CD   254 _T2CON_5	=	0x00cd
                           0000CE   255 _T2CON_6	=	0x00ce
                           0000CF   256 _T2CON_7	=	0x00cf
                           0000C8   257 _CP_RL2	=	0x00c8
                           0000C9   258 _C_T2	=	0x00c9
                           0000CA   259 _TR2	=	0x00ca
                           0000CB   260 _EXEN2	=	0x00cb
                           0000CC   261 _TCLK	=	0x00cc
                           0000CD   262 _RCLK	=	0x00cd
                           0000CE   263 _EXF2	=	0x00ce
                           0000CF   264 _TF2	=	0x00cf
                                    265 ;--------------------------------------------------------
                                    266 ; overlayable register banks
                                    267 ;--------------------------------------------------------
                                    268 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        269 	.ds 8
                                    270 ;--------------------------------------------------------
                                    271 ; internal ram data
                                    272 ;--------------------------------------------------------
                                    273 	.area DSEG    (DATA)
      000008                        274 _li::
      000008                        275 	.ds 1
      000009                        276 _g_dc::
      000009                        277 	.ds 1
      00000A                        278 _lbuf::
      00000A                        279 	.ds 12
                                    280 ;--------------------------------------------------------
                                    281 ; overlayable items in internal ram 
                                    282 ;--------------------------------------------------------
                                    283 	.area	OSEG    (OVR,DATA)
                                    284 ;--------------------------------------------------------
                                    285 ; Stack segment in internal ram 
                                    286 ;--------------------------------------------------------
                                    287 	.area	SSEG
      000016                        288 __start__stack:
      000016                        289 	.ds	1
                                    290 
                                    291 ;--------------------------------------------------------
                                    292 ; indirectly addressable internal ram data
                                    293 ;--------------------------------------------------------
                                    294 	.area ISEG    (DATA)
                                    295 ;--------------------------------------------------------
                                    296 ; absolute internal ram data
                                    297 ;--------------------------------------------------------
                                    298 	.area IABS    (ABS,DATA)
                                    299 	.area IABS    (ABS,DATA)
                                    300 ;--------------------------------------------------------
                                    301 ; bit data
                                    302 ;--------------------------------------------------------
                                    303 	.area BSEG    (BIT)
                                    304 ;--------------------------------------------------------
                                    305 ; paged external ram data
                                    306 ;--------------------------------------------------------
                                    307 	.area PSEG    (PAG,XDATA)
                                    308 ;--------------------------------------------------------
                                    309 ; external ram data
                                    310 ;--------------------------------------------------------
                                    311 	.area XSEG    (XDATA)
                                    312 ;--------------------------------------------------------
                                    313 ; absolute external ram data
                                    314 ;--------------------------------------------------------
                                    315 	.area XABS    (ABS,XDATA)
                                    316 ;--------------------------------------------------------
                                    317 ; external initialized ram data
                                    318 ;--------------------------------------------------------
                                    319 	.area XISEG   (XDATA)
                                    320 	.area HOME    (CODE)
                                    321 	.area GSINIT0 (CODE)
                                    322 	.area GSINIT1 (CODE)
                                    323 	.area GSINIT2 (CODE)
                                    324 	.area GSINIT3 (CODE)
                                    325 	.area GSINIT4 (CODE)
                                    326 	.area GSINIT5 (CODE)
                                    327 	.area GSINIT  (CODE)
                                    328 	.area GSFINAL (CODE)
                                    329 	.area CSEG    (CODE)
                                    330 ;--------------------------------------------------------
                                    331 ; interrupt vector 
                                    332 ;--------------------------------------------------------
                                    333 	.area HOME    (CODE)
      000000                        334 __interrupt_vect:
      000000 02 00 06         [24]  335 	ljmp	__sdcc_gsinit_startup
                                    336 ;--------------------------------------------------------
                                    337 ; global & static initialisations
                                    338 ;--------------------------------------------------------
                                    339 	.area HOME    (CODE)
                                    340 	.area GSINIT  (CODE)
                                    341 	.area GSFINAL (CODE)
                                    342 	.area GSINIT  (CODE)
                                    343 	.globl __sdcc_gsinit_startup
                                    344 	.globl __sdcc_program_startup
                                    345 	.globl __start__stack
                                    346 	.globl __mcs51_genXINIT
                                    347 	.globl __mcs51_genXRAMCLEAR
                                    348 	.globl __mcs51_genRAMCLEAR
                                    349 ;	hi.c:24: byte li = 0;  // index into lbuf
      00005F 75 08 00         [24]  350 	mov	_li,#0x00
                                    351 	.area GSFINAL (CODE)
      000062 02 00 03         [24]  352 	ljmp	__sdcc_program_startup
                                    353 ;--------------------------------------------------------
                                    354 ; Home
                                    355 ;--------------------------------------------------------
                                    356 	.area HOME    (CODE)
                                    357 	.area HOME    (CODE)
      000003                        358 __sdcc_program_startup:
      000003 02 00 99         [24]  359 	ljmp	_main
                                    360 ;	return from main will return to caller
                                    361 ;--------------------------------------------------------
                                    362 ; code
                                    363 ;--------------------------------------------------------
                                    364 	.area CSEG    (CODE)
                                    365 ;------------------------------------------------------------
                                    366 ;Allocation info for local variables in function 'tx_char'
                                    367 ;------------------------------------------------------------
                                    368 ;c                         Allocated to registers 
                                    369 ;------------------------------------------------------------
                                    370 ;	hi.c:31: void tx_char(char c)
                                    371 ;	-----------------------------------------
                                    372 ;	 function tx_char
                                    373 ;	-----------------------------------------
      000065                        374 _tx_char:
                           000007   375 	ar7 = 0x07
                           000006   376 	ar6 = 0x06
                           000005   377 	ar5 = 0x05
                           000004   378 	ar4 = 0x04
                           000003   379 	ar3 = 0x03
                           000002   380 	ar2 = 0x02
                           000001   381 	ar1 = 0x01
                           000000   382 	ar0 = 0x00
      000065 85 82 99         [24]  383 	mov	_SBUF,dpl
                                    384 ;	hi.c:34: while (!TI)
      000068                        385 00101$:
                                    386 ;	hi.c:36: TI = 0;
                                    387 ;	assignBit
      000068 10 99 02         [24]  388 	jbc	_TI,00114$
      00006B 80 FB            [24]  389 	sjmp	00101$
      00006D                        390 00114$:
                                    391 ;	hi.c:37: }
      00006D 22               [24]  392 	ret
                                    393 ;------------------------------------------------------------
                                    394 ;Allocation info for local variables in function 'tx_str'
                                    395 ;------------------------------------------------------------
                                    396 ;str                       Allocated to registers 
                                    397 ;------------------------------------------------------------
                                    398 ;	hi.c:42: void tx_str(char *str)
                                    399 ;	-----------------------------------------
                                    400 ;	 function tx_str
                                    401 ;	-----------------------------------------
      00006E                        402 _tx_str:
      00006E AD 82            [24]  403 	mov	r5,dpl
      000070 AE 83            [24]  404 	mov	r6,dph
      000072 AF F0            [24]  405 	mov	r7,b
                                    406 ;	hi.c:45: while (*str)
      000074                        407 00101$:
      000074 8D 82            [24]  408 	mov	dpl,r5
      000076 8E 83            [24]  409 	mov	dph,r6
      000078 8F F0            [24]  410 	mov	b,r7
      00007A 12 01 24         [24]  411 	lcall	__gptrget
      00007D FC               [12]  412 	mov	r4,a
      00007E 60 18            [24]  413 	jz	00104$
                                    414 ;	hi.c:46: tx_char(*str++);
      000080 8C 82            [24]  415 	mov	dpl,r4
      000082 0D               [12]  416 	inc	r5
      000083 BD 00 01         [24]  417 	cjne	r5,#0x00,00116$
      000086 0E               [12]  418 	inc	r6
      000087                        419 00116$:
      000087 C0 07            [24]  420 	push	ar7
      000089 C0 06            [24]  421 	push	ar6
      00008B C0 05            [24]  422 	push	ar5
      00008D 12 00 65         [24]  423 	lcall	_tx_char
      000090 D0 05            [24]  424 	pop	ar5
      000092 D0 06            [24]  425 	pop	ar6
      000094 D0 07            [24]  426 	pop	ar7
      000096 80 DC            [24]  427 	sjmp	00101$
      000098                        428 00104$:
                                    429 ;	hi.c:47: }
      000098 22               [24]  430 	ret
                                    431 ;------------------------------------------------------------
                                    432 ;Allocation info for local variables in function 'main'
                                    433 ;------------------------------------------------------------
                                    434 ;	hi.c:52: void main(void)
                                    435 ;	-----------------------------------------
                                    436 ;	 function main
                                    437 ;	-----------------------------------------
      000099                        438 _main:
                                    439 ;	hi.c:54: PCON = 0x80;  /* power control byte, set SMOD bit for serial port */
      000099 75 87 80         [24]  440 	mov	_PCON,#0x80
                                    441 ;	hi.c:55: SCON = 0x50;  /* serial control byte, mode 1, RI active */
      00009C 75 98 50         [24]  442 	mov	_SCON,#0x50
                                    443 ;	hi.c:56: TMOD = 0x21;  /* timer control mode, byte operation */
      00009F 75 89 21         [24]  444 	mov	_TMOD,#0x21
                                    445 ;	hi.c:57: TCON = 0;     /* timer control register, byte operation */
      0000A2 75 88 00         [24]  446 	mov	_TCON,#0x00
                                    447 ;	hi.c:59: TH1 = 0xFA;   /* serial reload value, 9,600 baud at 11.0952Mhz */
      0000A5 75 8D FA         [24]  448 	mov	_TH1,#0xfa
                                    449 ;	hi.c:60: TR1 = 1;      /* start serial timer */
                                    450 ;	assignBit
      0000A8 D2 8E            [12]  451 	setb	_TR1
                                    452 ;	hi.c:62: EA = 1;       /* Enable Interrupts */
                                    453 ;	assignBit
      0000AA D2 AF            [12]  454 	setb	_EA
                                    455 ;	hi.c:64: TI = 0;       /* clear this out */
                                    456 ;	assignBit
      0000AC C2 99            [12]  457 	clr	_TI
                                    458 ;	hi.c:65: SBUF = '.';   /* send an initial '.' out serial port */
      0000AE 75 99 2E         [24]  459 	mov	_SBUF,#0x2e
                                    460 ;	hi.c:68: tx_str("Hello World\n");
      0000B1 90 01 44         [24]  461 	mov	dptr,#___str_0
      0000B4 75 F0 80         [24]  462 	mov	b,#0x80
      0000B7 12 00 6E         [24]  463 	lcall	_tx_str
                                    464 ;	hi.c:70: RI = 0;
                                    465 ;	assignBit
      0000BA C2 98            [12]  466 	clr	_RI
                                    467 ;	hi.c:71: g_dc = 0;
      0000BC 75 09 00         [24]  468 	mov	_g_dc,#0x00
      0000BF                        469 00111$:
                                    470 ;	hi.c:74: if (RI)  // we have new serial rx data
      0000BF 30 98 FD         [24]  471 	jnb	_RI,00111$
                                    472 ;	hi.c:76: g_dc = SBUF;  // read the serial char
      0000C2 85 99 09         [24]  473 	mov	_g_dc,_SBUF
                                    474 ;	hi.c:77: RI = 0;  // reset serial rx flag
                                    475 ;	assignBit
      0000C5 C2 98            [12]  476 	clr	_RI
                                    477 ;	hi.c:79: tx_char(g_dc);   // echo back out as serial tx data
      0000C7 85 09 82         [24]  478 	mov	dpl,_g_dc
      0000CA 12 00 65         [24]  479 	lcall	_tx_char
                                    480 ;	hi.c:80: if ((g_dc == 0x0d) || (g_dc == '.') || (g_dc == 0x0a)) // if CR, then end of line
      0000CD 74 0D            [12]  481 	mov	a,#0x0d
      0000CF B5 09 02         [24]  482 	cjne	a,_g_dc,00136$
      0000D2 80 0C            [24]  483 	sjmp	00103$
      0000D4                        484 00136$:
      0000D4 74 2E            [12]  485 	mov	a,#0x2e
      0000D6 B5 09 02         [24]  486 	cjne	a,_g_dc,00137$
      0000D9 80 05            [24]  487 	sjmp	00103$
      0000DB                        488 00137$:
      0000DB 74 0A            [12]  489 	mov	a,#0x0a
      0000DD B5 09 33         [24]  490 	cjne	a,_g_dc,00104$
      0000E0                        491 00103$:
                                    492 ;	hi.c:82: tx_char(0xd);  // CR
      0000E0 75 82 0D         [24]  493 	mov	dpl,#0x0d
      0000E3 12 00 65         [24]  494 	lcall	_tx_char
                                    495 ;	hi.c:83: tx_char(0xa);  // LF
      0000E6 75 82 0A         [24]  496 	mov	dpl,#0x0a
      0000E9 12 00 65         [24]  497 	lcall	_tx_char
                                    498 ;	hi.c:84: lbuf[li] = 0;
      0000EC E5 08            [12]  499 	mov	a,_li
      0000EE 24 0A            [12]  500 	add	a,#_lbuf
      0000F0 F8               [12]  501 	mov	r0,a
      0000F1 76 00            [12]  502 	mov	@r0,#0x00
                                    503 ;	hi.c:85: li = 0;
      0000F3 75 08 00         [24]  504 	mov	_li,#0x00
                                    505 ;	hi.c:86: tx_str("You typed in this[");
      0000F6 90 01 51         [24]  506 	mov	dptr,#___str_1
      0000F9 75 F0 80         [24]  507 	mov	b,#0x80
      0000FC 12 00 6E         [24]  508 	lcall	_tx_str
                                    509 ;	hi.c:87: tx_str(lbuf);
      0000FF 90 00 0A         [24]  510 	mov	dptr,#_lbuf
      000102 75 F0 40         [24]  511 	mov	b,#0x40
      000105 12 00 6E         [24]  512 	lcall	_tx_str
                                    513 ;	hi.c:88: tx_str("]\n");
      000108 90 01 64         [24]  514 	mov	dptr,#___str_2
      00010B 75 F0 80         [24]  515 	mov	b,#0x80
      00010E 12 00 6E         [24]  516 	lcall	_tx_str
      000111 80 AC            [24]  517 	sjmp	00111$
      000113                        518 00104$:
                                    519 ;	hi.c:92: lbuf[li] = g_dc;
      000113 E5 08            [12]  520 	mov	a,_li
      000115 24 0A            [12]  521 	add	a,#_lbuf
      000117 F8               [12]  522 	mov	r0,a
      000118 A6 09            [24]  523 	mov	@r0,_g_dc
                                    524 ;	hi.c:93: if (li < 11)
      00011A 74 F5            [12]  525 	mov	a,#0x100 - 0x0b
      00011C 25 08            [12]  526 	add	a,_li
      00011E 40 9F            [24]  527 	jc	00111$
                                    528 ;	hi.c:94: ++li;
      000120 05 08            [12]  529 	inc	_li
                                    530 ;	hi.c:98: }
      000122 80 9B            [24]  531 	sjmp	00111$
                                    532 	.area CSEG    (CODE)
                                    533 	.area CONST   (CODE)
                                    534 	.area CONST   (CODE)
      000144                        535 ___str_0:
      000144 48 65 6C 6C 6F 20 57   536 	.ascii "Hello World"
             6F 72 6C 64
      00014F 0A                     537 	.db 0x0a
      000150 00                     538 	.db 0x00
                                    539 	.area CSEG    (CODE)
                                    540 	.area CONST   (CODE)
      000151                        541 ___str_1:
      000151 59 6F 75 20 74 79 70   542 	.ascii "You typed in this["
             65 64 20 69 6E 20 74
             68 69 73 5B
      000163 00                     543 	.db 0x00
                                    544 	.area CSEG    (CODE)
                                    545 	.area CONST   (CODE)
      000164                        546 ___str_2:
      000164 5D                     547 	.ascii "]"
      000165 0A                     548 	.db 0x0a
      000166 00                     549 	.db 0x00
                                    550 	.area CSEG    (CODE)
                                    551 	.area XINIT   (CODE)
                                    552 	.area CABS    (ABS,CODE)
