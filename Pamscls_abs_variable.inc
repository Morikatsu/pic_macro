; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2012/04/28 13:22:32.
;	Pamscls_abs_variable.inc
;	このファイルは_?temp0～_?temp7を定義確保する	
	list
; ==== Pamscls_abs_variable.inc ==== ver 1.0e ==== 堀野 守克 ===== 
	nolist
;====================================================
#ifndef	_PAMSCLS_ABS_VARIABLE_INC_INCLUDED
#define	_PAMSCLS_ABS_VARIABLE_INC_INCLUDED
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
;****************************************************
;	作業変数の確保	10/05/25 変更
;	共用領域に配置したので、bankselは不要
;****************************************************
	cblock		(_?BTMMEMO - 0x0f + d'8')	
;	_?romadrsはEeprom_sub_abs.asmで定義する		12/3/7
;	_sCount, _?msCount, _?usCountはTimer_abs.incで定義する　12/3/7
_?temp0	
_?temp1
_?temp2
_?temp3
_?temp4	
_?temp5
_?temp6
_?temp7
	endc
;****************************************************
;	globalはrelativeのときに必要
;	global	_?temp0,_?temp1,_?temp2,_?temp3
;	global	_?temp4,_?temp5,_?temp6,_?temp7
;	extern	_?sCount, _?msCount,_?usCount,_?romadrs
;****************************************************
#endif	;_PAMSCLS_ABS_VARIABLE_INC_INCLUDED
;****************************************************
	list
