; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2010/06/06 06:49:15.
	LIST
;=== Timer.inc === Ver 1.0b ==========================	
	NOLIST
;************************************************************
#ifndef	_TIMER_INC_INCLUED
#define	_TIMER_INC_INCLUED
;************************************************************
;	software timer  Timer.asmと同じものである。
;	system clockは _?CLOCK で指定する	4, 10, 12.8, 20 MHz
;		#define	_?CLOCK	20		mainプログラムにて定義する
;	使用するクロック数に対応した行を生かす [メインプログラムにて]
;	_?freqはmacro variableである
;		_?freq	set	4		;clock 4MHz
;		_?freq	set	10		;clock 10MHz
;		_?freq	set	20		;clock 20MHz
;		_?freq	set	128		;clock 12.8MHz
;=====================================================
;      ******* Subroutines *******
;	このsubroutineをincludeする場所はプログラムの一番
;	終りの部分[ end行の直前 ]とする
;	このsubroutineを使うときには、プログラムの初めの部分で
;	macro variableの　_?CLOCKを定義する必要がある。
;    例  #define	_?CLOCK  128	 (12.8MHzの場合
;	_?sCount, _?msCount, _?usCount, _?usCount0を作業変数として使う
;	この領域はchip毎に異なる自動設定とした  10/05/25
;==============================================
;	準備してあるエントリーポイント(遅延時間)
;		timeDelay1s
;		timeDelay05s
;		timeDelay200ms
;		timeDelay100ms
;		timeDelay50ms
;		timeDelay30ms
;		timeDelay20ms
;		timeDelay10ms
;		timeDelay1ms
;		timeDelay500us
;		timeDelay100us
;		timeDelay50us
;		timeDelay10us
;************************************************************
;_?timerのための作業変数  _?BTMMEMOはPamscls.incで定義している
;====== 変数定義 ===============================
	cblock ( _?BTMMEMO - 0x0f + 4 )		;ここはマクロでなくてよい
_?sCount		;このプログラムの内部で使う
_?msCount		;このプログラムの内部で使う
_?usCount		;このプログラムの内部で使う
_?usCount0		;このプログラムの内部で使う
	endc
;*******************************************************
#ifndef	_?CLOCK
	error "_?CLOCK  not defined! ---- Timer.inc ----"
#else
_?freq	set	_?CLOCK
#endif
;================================================
;	------ 1 & 0.5 Sec Time Delay ------
;	timeDelay1s, timeDelay05s
;==============================================
timeDelay1s
	movlw	10		; 1 Sec
	goto	_?Ltimed02
;==============================================
timeDelay05s
	movlw	5		; 0.5 Sec
_?Ltimed02
	movwf	_?sCount
_?Ltimed1s
	call	timeDelay100ms
	decf	_?sCount,f
	btfss	STATUS,2
	goto	_?Ltimed1s
	return
;==============================================
;	--- 5 10 15 & 20 & 30 & 50 mSec Time Delay ---
;	timeDelay5ms, timeDelay10ms, timeDelay15ms
;	timeDelay20ms
;	timeDelay30ms, timeDelay50ms
;	timeDelay100ms, timeDelay200ms
;==============================================
timeDelay200ms:
	movlw	200
	goto _?Ltimed101
timeDelay100ms:
	movlw	100
	goto _?Ltimed101
timeDelay50ms:
	movlw	50
	goto _?Ltimed101
timeDelay30ms
	movlw	30
	goto _?Ltimed101
timeDelay20ms
	movlw	20
	goto _?Ltimed101
timeDelay15ms	
	movlw	15
	goto _?Ltimed101
timeDelay10ms
	movlw	10
	goto _?Ltimed101
timeDelay5ms
	movlw	5
_?Ltimed101
	movwf	_?msCount
_?Ltimed10
	call	timeDelay1ms
	decf	_?msCount,f
	btfss	STATUS,2
	goto	_?Ltimed10
	return
;==============================================
;	------ 1 mSec Time Delay ------
;	この部分は各クロック毎に正確である。　堀野 守克
;	timeDelay1ms
;==============================================
timeDelay1ms
;----- 1ms - clock 20 MHz ------	
	if _?freq == 20
		movlw 	D'152'
		movwf	_?usCount
		movlw 	D'217'
		movwf	_?usCount0
_?Ltimed12		
		goto 	$+1
		goto 	$+1
		goto 	$+1
		goto 	$+1
		goto 	$+1
		goto 	$+1
		decf	_?usCount0, F
		bnz 	_?Ltimed12
		goto	$+1
	endif
;------ 1ms - clock 12.8MHz -----	
	if _?freq == 128
		movlw	D'255'	
		movwf	_?usCount
		movlw 	D'91'
		movwf	_?usCount0
_?Ltimed12		
		goto 	$+1
		nop
		decf	_?usCount0, F
		bnz 	_?Ltimed12
		goto 	$+1
		goto 	$+1
		goto 	$+1
		nop
	endif
;------ 1ms - clock 10MHz --------
	if _?freq == 10
		movlw	249
		movwf	_?usCount
		goto 	$+1
		goto 	$+1
		nop
	endif
;------ 1ms - clock 4MHz --------
	if _?freq == 4
		movlw	99
		movwf	_?usCount
		goto 	$+1
		goto 	$+1
		nop
	endif
;-----------------------------		
_?Ltimed1
;---- commom (4, 10, 20, 12.8) ---	
	goto	$+1
	goto	$+1
	goto	$+1
	decf	_?usCount,f
	bnz		_?Ltimed1
	return
;==============================================
;	------ 500,100,50,10 uSec Time Delay ------
;	100us, 10usは12.8MHzでは正確である。
;		07/05/24
;	timeDelay500us, timeDelay100us,
;	timeDelay50us, timeDelay10us
;	timeDelay3us =>2.8us
;==============================================
timeDelay500us:
;------- 500us - clock 20MHz --09/09/13------
	if	_?freq == 20
		movlw	D'119'	
		movwf	_?sCount
_?Ltimed500
		decf	_?sCount,F
		bnz		_?Ltimed500
		nop
		nop
		movlw	D'4'	
	endif
;------- 500us - clock 4MHz --09/09/13------
	if	_?freq == 4
		movlw	D'19'	
		movwf	_?sCount
_?Ltimed500
		decf	_?sCount,F
		bnz		_?Ltimed500
		nop
		nop
		movlw	D'4'	
	endif
;------- 500us - common --------------
	movwf	_?msCount
_?Ltimed300
	call	timeDelay100us
	decf	_?msCount,F
	bnz		_?Ltimed300
	return
;=====================================
timeDelay100us
;------- 100us - clock 20MHz --09/09/13------
	if	_?freq == 20
		movlw	4
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		bnz		_?Ltimed200
		nop
		movlw	9
	endif
;------- 100us - clock 128MHz --09/09/13------
	if	_?freq == 128
		movlw	9
	endif
;------- 100us - clock 10MHz --09/09/13------
	if	_?freq == 10
		movlw	5
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		bnz		_?Ltimed200
		movlw	8
	endif
;------- 100us - clock 4MHz --09/09/13------
	if	_?freq == 4
		movlw	4
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		btfss	STATUS,2
		goto _?Ltimed200
		movlw	6
	endif
;------- 100us - common --------------
	movwf	_?usCount
_?Ltim_lp1
	call	timeDelay10us
	decfsz	_?usCount,F
	goto	_?Ltim_lp1
	return
;===========================================
timeDelay50us
;------- 50us - clock 20MHz --09/09/13------
	if	_?freq == 20
		movlw	19	
		movwf	_?usCount
_?Ltimed2000
		decf	_?usCount,F
		bnz		_?Ltimed2000
		goto	$+1
		nop
		movlw	3
	endif
;------- 50us - clock 128MHz --09/09/13------
	if	_?freq == 128
		movlw	2	
		movwf	_?usCount
_?Ltimed2000
		decf	_?usCount,F
		bnz		_?Ltimed2000
		movlw	4
	endif
;------ 50us - clock 10MHz --09/09/13------
	if	_?freq == 10
		goto		$+1
		movlw	4
	endif
;------- 50us - clock 4MHz --09/09/13------
	if	_?freq == 4
		movlw	3
		movwf	_?usCount
_?Ltimed2000
		decf	_?usCount,F
		btfss	STATUS,2
		goto _?Ltimed2000
		movlw	2
	endif
;------- 50us - common -------------
	movwf	_?usCount
_?Ltim_lp11
	call	timeDelay10us
	decfsz	_?usCount,F
	goto	_?Ltim_lp11
	goto	$+1
	goto	$+1
	goto	$+1
	return
;============================================
timeDelay10us
;------- 10us - clock 12.8MHz -09/09/13------
	if	_?freq == 128
		nop
		movlw	8
	endif
;------- 10us - clock 20MHz -09/09/13-------
	if	_?freq == 20
		goto	$+1
		goto	$+1
		goto	$+1		
		nop
		movlw	12	
	endif
;------- 10us - clock 10MHz -09/09/13-------
	if	_?freq == 10
		goto	$+1		
		nop
		movlw	5
	endif
;------- 10us - clock 4MHz -09/09/13-------
	if	_?freq == 4
		movlw	1
	endif
;------- 10us - common(4,10,12.8,20) ------
	movwf	_?usCount0		
_?Ltim_lp2:
	decfsz	_?usCount0,F
	goto	_?Ltim_lp2
	nop
	nop
	return
;===============================================
;	end
	LIST
#endif		;_TIMER_INC_INCLUDED
