; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2012/04/28 12:22:02.
	LIST
;=== Timer_rel.asm === Ver 1.1b ==========================	
	NOLIST
;		条件アセンブルとなるので、Libraryとすることはできない。従って、
;	Projectにこのファイルを列記して、buildを行う
;	変数はここで定義している。Pamscls_rel_variables.incではextern宣言
;	している。
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	LIST	P=PIC16F648A 
	INCLUDE <P16F648A.INC>
	ERRORLEVEL	-302	;アセンブル時のバンク警告メッセージ抑制

	global	_?sCount
;*********************************************************
#ifndef	_TIMER_REL_ASM_INCLUED
#define	_TIMER_REL_ASM_INCLUED

;****************************************************
;	作業変数の確保	10/05/25 変更
;	_?TOPMEMOはPamscls, Timer.incでは使っていない
;****************************************************
#ifndef	_PAMSCLS_REL_VARIABLE_INC_INCLUDED
#include <c:\users\tora\1_PIC\MyLibrary\Pamscls_rel_variable.inc>
#endif
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
Timer_datgrp	udata_shr	(_?BTMMEMO - 0x0f + d'4')
_?sCount	res	1
_?msCount	res	1
_?usCount	res	1
;	_?sCount,_?msCount,_?usCountを作業変数として使う。
;====================================================
;	global	_?sCount,_?msCount,_?usCount
	global	Delay_10ms, Delay_100us
;====================================================
;	system clockは _?FREQ で指定する	4, 10, 12.8, 20 MHz
;	使用するクロック数に対応した行を生かすため、このアセンブル
;	単位内で_?FREQを定義する 
;	_?FREQはmacro variableである
		_?FREQ	set	4		;clock 4MHz
;		_?FREQ	set	10		;clock 10MHz
;		_?FREQ	set	20		;clock 20MHz
;		_?FREQ	set	128		;clock 12.8MHz
;	このプログラム内で定義する必要がある。メインとは
;	アセンブル単位が異なる。
;=====================================================
;	使い方:
;		movlw	D'100'			;1sの遅延
;		call	Delay_10ms
;			最大2.55sの遅延が作れる
;		movlw	d'20'
;		call	Delay_100us		;2ms[100*20]の遅延
;	時間の誤差は1%程度である
;	100us以下の時間については個別にさくせいする必要がある
;		timeDelay50us
;************************************************************
#ifndef	_?FREQ
	error "_?FREQ  not defined! ---- Timer.inc ----"
#endif
;================================================
Timer_code	code	h'fd6'	;h'fd4'
Delay_10ms:
	movwf	_?sCount
_?Ltimed1s
	movlw	10
	movwf	_?msCount
_?Ltimed10
	pagesel	_?timeDelay1ms
	call	_?timeDelay1ms
	decf	_?msCount,f
	btfss	STATUS,2
	goto	_?Ltimed10

	decf	_?sCount,f
	btfss	STATUS,2
	goto	_?Ltimed1s
	return
;==============================================
;	------ 1 mSec Time Delay ----- 堀野 守克
;	この部分は各クロック毎にほぼ正確である。
;		最大0.5%の誤差
;	timeDelay1ms
;==============================================
_?timeDelay1ms
;----- 1ms - clock 20 MHz ------	
	if _?FREQ == 20
		movlw	D'193'
		movwf	_?usCount
_?Ltimed12:		
		goto 	$+1
		goto 	$+1
		goto 	$+1
		goto 	$+1
		decf	_?usCount, F
		bnz 	_?Ltimed12

		movlw 	D'167'
		movwf	_?usCount
_?Ltimed1
		goto 	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1
		goto 	$+1
		goto 	$+1
		goto	$+1
		goto	$+1
		goto	$+1
		return
	endif
;------ 1ms - clock 12.8MHz -----	
	if _?FREQ == 128
		movlw	D'95'
		movwf	_?usCount
_?Ltimed12:		
		goto 	$+1
		goto 	$+1
		goto 	$+1
		decf	_?usCount
		bnz		_?Ltimed12

		movlw	D'117'	
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1

		goto 	$+1
		goto 	$+1
		nop
		return
	endif
;------ 1ms - clock 10MHz --------
	if _?FREQ == 10
		movlw	166
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1
		return
	endif
;------ 1ms - clock 4MHz --------
	if _?FREQ == 4
		movlw	66
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1
		return
	endif
;;=====================================
Delay_100us:
	movwf	_?sCount
_?Ltimed11s
	pagesel	_?timeDelay100us
	call	_?timeDelay100us
	decf	_?sCount,f
	btfss	STATUS,2
	goto	_?Ltimed11s
	return
;++++++++++++++++++++++++++++++++++++++++++++
_?timeDelay100us:
;------- 100us - clock 20MHz --09/09/13------
	if	_?FREQ == 20
		movlw	8
		movwf	_?usCount
_?Ltim_lp1
		goto	$+1
		nop
		nop
		movlw	201	
		movwf	_?msCount		
_?Ltim_lp2:
		decfsz	_?msCount,F
		goto	_?Ltim_lp2
		decfsz	_?usCount,F
		goto	_?Ltim_lp1

		movlw	d'19'
		movwf	_?usCount
_?Ltimed200
		nop
		decf	_?usCount,F
		bnz		_?Ltimed200

		goto	$+1
		goto	$+1
		goto	$+1
		goto	$+1
		return
	endif
;------- 100us - clock 128MHz --09/09/13------
	if	_?FREQ == 128
		movlw	9
		movwf	_?usCount
_?Ltim_lp1
		movlw	8
		movwf	_?msCount
_?Ltim_lp2:
		decfsz	_?msCount,F
		goto	_?Ltim_lp2
		goto	$+1
		decfsz	_?usCount,F
		goto	_?Ltim_lp1

		movlw	10
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		bnz		_?Ltimed200
		return
	endif
;------- 100us - clock 10MHz --09/09/13------
	if	_?FREQ == 10
		movlw	5
		movwf	_?usCount
_?Ltimed200
		nop
		decf	_?usCount,F
		bnz		_?Ltimed200
		movlw	8
		movwf	_?usCount
_?Ltim_lp1
		goto	$+1		
		nop
		nop
		movlw	5
		movwf	_?msCount		
_?Ltim_lp2:
		decfsz	_?msCount,F
		goto	_?Ltim_lp2
		decfsz	_?usCount,F
		goto	_?Ltim_lp1
		return
	endif
;------- 100us - clock 4MHz --09/09/13------
	if	_?FREQ == 4		;ここはこれで完結
		movlw	7
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		btfss	STATUS,2
		goto _?Ltimed200
		movlw	D'14'	
		movwf	_?usCount
_?Ltim_lp1
		nop
		decfsz	_?usCount,F
		goto	_?Ltim_lp1
		goto	$+1
		goto	$+1
		nop
		return
	endif
;;===========================================
;timeDelay50us
;;------- 50us - clock 20MHz --09/09/13------
;	if	_?FREQ == 20
;		movlw	19	
;		movwf	_?usCount
;_?Ltimed2000
;		decf	_?usCount,F
;		bnz		_?Ltimed2000
;		goto	$+1
;		nop
;		movlw	3
;	endif
;;------- 50us - clock 128MHz --09/09/13------
;	if	_?FREQ == 128
;		movlw	2	
;		movwf	_?usCount
;_?Ltimed2000
;		decf	_?usCount,F
;		bnz		_?Ltimed2000
;		movlw	4
;	endif
;;------ 50us - clock 10MHz --09/09/13------
;	if	_?FREQ == 10
;		goto		$+1
;		movlw	4
;	endif
;;------- 50us - clock 4MHz --09/09/13------
;	if	_?FREQ == 4
;		movlw	3
;		movwf	_?usCount
;_?Ltimed2000
;		decf	_?usCount,F
;		btfss	STATUS,2
;		goto _?Ltimed2000
;		movlw	2
;	endif
;;------- 50us - common -------------
;	movwf	_?usCount
;_?Ltim_lp11
;	call	timeDelay10us
;	decfsz	_?usCount,F
;	goto	_?Ltim_lp11
;	goto	$+1
;	goto	$+1
;	goto	$+1
;	return
;============================================
;	end
	LIST
#endif		;_TIMER_REL_ASM_INCLUDED
	end

