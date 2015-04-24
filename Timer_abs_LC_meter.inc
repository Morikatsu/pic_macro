; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2011/03/23 13:01:56.
	LIST
;=== Timer_abs_LCmeter.inc === Ver 1.1b ==========================	
	NOLIST
;	software timer  Timer.incと同じものである。
;	但し、LC_meter.asm専用なのでメモリ容量の関係で使える遅延時間は
;		Delay_10ms, Delay_100us のみに限定してある。
;************************************************************
#ifndef	_TIMER_ABS_INC_INCLUDED
#define	_TIMER_ABS_INC_INCLUDED
;************************************************************
;	このsubroutineをincludeする場所はプログラムの一番
;	終りの部分[ end行の直前 ]とする
;=====================================================
;	system clockは _?FREQ で指定する	4, 10, 12.8, 20 MHz
;		#define	_?FREQ	20		mainプログラムにて定義する
;	使用するクロック数に対応した行を生かす [メインプログラムにて]
;	_?FREQはmacro variableである
;		_?FREQ	set	4		;clock 4MHz
;		_?FREQ	set	10		;clock 10MHz
;		_?FREQ	set	20		;clock 20MHz
;		_?FREQ	set	128		;clock 12.8MHz
;====== 変数定義 ===============================
;	_?sCount, _?msCount, _?usCount, _?usCount0を作業変数として使う
;	この領域はchip毎に異なる自動設定とした  10/05/25
;	作業変数を確保するための _?BTMMEMOはPamscls_abs.incで定義している。
;	従って、以下のcblockはコメントアウトしてある。
;===============================================
;	cblock ( _?BTMMEMO - 0x0f + 5 )		;ここはマクロでなくてよい
;_?sCount		;このプログラムの内部で使う
;_?msCount		;このプログラムの内部で使う
;_?usCount		;このプログラムの内部で使う
;	endc
;==============================================
;	使い方:
;		movlw	D'100'			;1sの遅延
;		call	Delay_10ms
;			最大2.55sの遅延が作れる
;		movlw	d'20'
;		call	Delay_100us		;2ms[100*20]の遅延
;	時間の誤差は1%程度である
;	100us以下の時間については個別に作成する必要がある
;		timeDelay50us
;================================================
#ifndef	_?FREQ
	error "_?FREQ  not defined! ---- Timer.inc ----"
#endif
;================================================
Delay_10ms:
	movwf	_?sCount
_?Ltimed1s
	movlw	15
	movwf	_?msCount
_?Ltimed10
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
_?timeDelay1ms:
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
;;==========================================
Delay_100us:
	movwf	_?sCount
_?Ltimed11s
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
#endif		;_TIMER_ABS_INC_INCLUDED
	LIST
