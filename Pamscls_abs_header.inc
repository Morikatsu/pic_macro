; vim: set syntax=pic ts=4 sts=4 sw=4: last change:2012/04/28 13:22:39.
;	Pamscls_abs_header.inc		Ver 1.0
;	このファイルはPamscls_abs.inc用である
;====================================================
#ifndef	_PAMSCLS_ABS_HEADER_INC_INCLUDED
#define	_PAMSCLS_ABS_HEADER_INC_INCLUDED
;====================================================
;   Macro variable INIT
;****************************************************
	variable	_?nstlv	=	0	;Nesting level
	variable	_?curlb	=	0	;Current label index
	variable	_?dolv	=	0	;Do nest level
	variable	_?atrf1	=	0	;Attr 1.
	variable	_?atrf2	=	0	;Attr 2.
	variable	_?atrf3	=	0	;Attr 3.
	variable	_?atrf4	=	0	;Attr 4.
	variable	_?atrf5	=	0	;Attr 5 forinc(0), fordec(1)の区別
	variable	_?contc	=	0	;condition continue? 
	variable	_?cscas	=	0	;case count
	variable	_?nstcs	=	0	;case group count

	constant	EQ	=	0
	constant	NE	=	1
	constant	GE	=	2
	constant	GT	=	3
	constant	LE	=	4
	constant	LT	=	5
	constant	OR	=	1
	constant	AND	=	2
	constant	QUIT=	0
	constant	CL	=	10	;_?ifbit/_?whilebit/_?untilbitのため
	constant	ST	=	11
;****************************************************
;	作業変数の確保	10/05/25 変更
;	_?TOPMEMOはPamscls, Timer.incでは使っていない
;****************************************************
	ifdef	(__16F84)||(__16F84A)||(__12F629)||(__12F675)
_?TOPMEMO	equ		0x0c	;GPRの先頭
_?BTMMEMO	equ		0x4F	;GPR(共通)の終わり
	endif
	;++++++++++++
	ifdef	(__12F629)||(__12F675)
_?TOPMEMO	equ		0x20	;GPRの先頭
_?BTMMEMO	equ		0x5F	;GPR(共通)の終わり
	endif
	;++++++++++++
	ifdef	(__12F683)||(__12F627A)||(__16F628A)||(__16F648A)||(__16F87)||(__16F88)
_?TOPMEMO	equ		0x20	;GPRの先頭
_?BTMMEMO	equ		0x7F	;GPR(共通)の終わり
	endif
;****************************************************
;		GPRの終わりの8byteを作業領域とする
;****************************************************
	cblock	(_?BTMMEMO - 8 + 1 )	;09/11/06 修正
_?temp0,_?temp1,_?temp2,_?temp3,_?temp4,_?temp5,_?temp6,_?temp7
	endc
;****************************************************
#endif		;	_PAMSCLS_ABS_HEADER_INC_INCLUDED
