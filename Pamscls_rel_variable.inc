; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2012/04/28 12:21:29.
;	Pamscls_rel_variable.inc
;====================================================
#ifndef	_PAMSCLS_REL_VARIABLE_INC_INCLUDED
#define	_PAMSCLS_REL_VARIABLE_INC_INCLUDED
;====================================================
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
;	ifdef	__16F84
;_?TOPMEMO	equ		0x0c	;GPRの先頭
;_?BTMMEMO	equ		0x4F	;GPR(共通)の終わり
;	endif
;	ifdef	__16F84A
;_?TOPMEMO	equ		0x0c
;_?BTMMEMO	equ		0x4F
;	endif
;	;++++++++++++
;	ifdef	__12F629		;07/06/15
;_?TOPMEMO	equ		0x20	;GPRの先頭
;_?BTMMEMO	equ		0x5F	;GPR(共通)の終わり
;	endif
;	ifdef	__12F675		;09/04/21 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x5F
;	endif
;	ifdef	__12F683		;10/04/02 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	;++++++++++++
;	ifdef	__16F627A		;09/04/21 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	ifdef	__16F628A		;09/04/21 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	ifdef	__16F648A
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	;++++++++++++
;	ifdef	__16F87
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	ifdef	__16F88
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;****************************************************
;	作業変数の確保	10/05/25 変更
;	共用領域に配置したので、bankselは不要
;****************************************************
Pamscls_datgrp	udata_shr	(_?BTMMEMO - 0x0f + d'8')	;648Aの時 h'78'
_?temp0		res	1
_?temp1		res	1
_?temp2		res	1
_?temp3		res	1
_?temp4		res	1
_?temp5		res	1
_?temp6		res	1
_?temp7		res	1
;****************************************************
	global	_?temp0,_?temp1,_?temp2,_?temp3
	global	_?temp4,_?temp5,_?temp6,_?temp7
	extern	_?sCount, _?msCount,_?usCount	;Timer_rel.asmで定義している
	extern	_?romadrs		;Eeprom_sub_rel.asmで定義いている
;****************************************************
#endif	_PAMSCLS_REL_VARIABLE_INC_INCLUDED
