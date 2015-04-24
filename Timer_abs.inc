; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2012/04/28 12:24:05.
;	このファイルは_sCount, _?msCount, _?usCount を定義確保する	

;	注意) 4MHz以外は調整がされていない。2012/03/26 

	LIST
;=== Timer_abs.inc === Ver 1.1e === last change:2012/04/28 12:24:05. ====
	NOLIST
;************************************************************
#ifndef	_TIMER_ABS_INC_INCLUDED
#define	_TIMER_ABS_INC_INCLUDED
;************************************************************
;	software timer  Timer.asmと同じものである。
;=====================================================
;	system clockは _?FREQ で指定する	4, 10, 12.8, 20 MHz
;	通常は主プログラムで指定する
;		#define	_?FREQ	20		
;	使用するクロック数に対応した行を生かす 
;	_?FREQはmacro constantである
	ifndef	_?FREQ
#define	_?FREQ	4		;clock 4MHz
;#define	_?FREQ	10		;clock 10MHz
;#define	_?FREQ	20		;clock 20MHz
;#define	_?FREQ	128		;clock 12.8MHz
	endif
;=====================================================
;	このsubroutineをincludeする場所はプログラムの一番
;	終りの部分[ end行の直前 ]とする
;=====================================================
;	使い方:
;		call	Delay_10ms
;		call	Delay_100us
;	時間の誤差は1%程度である
;************************************************************
;	準備してあるエントリーポイント(遅延時間)
;		Delay_1s 	Delay_05s
;		Delay_200ms	Delay_100ms	Delay_50ms
;		Delay_30ms	Delay_20ms	Delay_10ms Delay_1ms
;		Delay_500us	Delay_100us Delay_50us Delay_10us
;****************************************************
;	作業変数の確保	10/05/25 変更
;	_?TOPMEMOはPamscls, Timer.incでは使っていない
;****************************************************
#ifndef	_PAMSCLS_REL_VARIABLE_INC_INCLUDED
#include <c:\users\tora\1_PIC\MyLibrary\Pamscls_rel_variable.inc>
#endif
;************************************************************
;_?timerのための作業変数  _?BTMMEMOはPamscls_abs_variable.incで定義している
;	_?sCount, _?msCount, _?usCount を作業変数として使う
;	この領域はchip毎に異なる自動設定とした  10/05/25
;====== 変数定義 ============================================
;	Timer_abs.incで使う変数はここで定義する		12/3/7
	cblock ( _?BTMMEMO - 0x0f + 5 )		;ここはマクロでなくてよい
_?sCount		;このプログラムの内部で使う
_?msCount		;このプログラムの内部で使う
_?usCount		;このプログラムの内部で使う
	endc
;*******************************************************
#ifndef	_?FREQ
	error "_?FREQ  not defined! ---- Timer.inc ----"
#endif
;================================================
;	Delay_1s, Delay_05s
;==============================================
Delay_1s
	movlw	10		; 1 Sec
	goto	_?Ltimed02
Delay_05s
	movlw	5		; 0.5 Sec
_?Ltimed02
	movwf	_?sCount
_?Ltimed1s				; 2012/03/26 
	call	Delay_100ms
	decfsz	_?sCount,f
	goto	_?Ltimed1s
	return
;==============================================
;	Delay_5ms, Delay_10ms, Delay_15ms, Delay_20ms
;	Delay_30ms, Delay_50ms
;	Delay_100ms, Delay_200ms, Delay_250ms
;==============================================
Delay_250ms:
	movlw	250
	goto _?Ltimed101
Delay_200ms:
	movlw	200
	goto _?Ltimed101
Delay_100ms:
	movlw	100
	goto _?Ltimed101
Delay_50ms:
	movlw	50
	goto _?Ltimed101
Delay_30ms
	movlw	30
	goto _?Ltimed101
Delay_20ms
	movlw	20
	goto _?Ltimed101
Delay_15ms	
	movlw	15
	goto _?Ltimed101
Delay_10ms
	movlw	10
	goto _?Ltimed101
Delay_5ms			; 2012/03/26 
	movlw	5
_?Ltimed101
	movwf	_?msCount
_?Ltimed10
	call	Delay_1ms
	decfsz	_?msCount,f		; 2012/03/26 
	goto	_?Ltimed10
	return
;==============================================
;		最大0.5%の誤差
;	Delay_1ms
;==============================================
Delay_1ms:
;----- 1ms - clock 20 MHz ------	
	if _?FREQ == 20
		movlw	D'193'
		movwf	_?usCount
_?Ltimed12:		
		goto 	$+1
		goto 	$+1
		goto 	$+1
		goto 	$+1
		decfsz	_?usCount, F	; 2012/03/26 
		goto 	_?Ltimed12

		movlw 	D'167'
		movwf	_?usCount
_?Ltimed1
		goto 	$+1
		decfsz	_?usCount,f	; 2012/03/26 
		goto		_?Ltimed1
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
		decfsz	_?usCount	; 2012/03/26 
		goto		_?Ltimed12

		movlw	D'117'	
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decfsz	_?usCount,f	; 2012/03/26 
		goto		_?Ltimed1

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
		decfsz	_?usCount,f	; 2012/03/26 
		goto		_?Ltimed1
		return
	endif
;------ 1ms - clock 4MHz -------- 2012/03/26 
	if _?FREQ == 4
		movlw	99		;12/3/26
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		nop
		decfsz	_?usCount,f	; 2012/03/26 
		goto		_?Ltimed1
		goto	$+1
		goto	$+1
		nop
		return
	endif
;==============================================
;	100us, 10usは12.8MHzでは正確である。
;		07/05/24
;	Delay_500us, Delay_100us,
;	Delay_50us, Delay_10us
;==============================================
Delay_500us:
;------- 500us - clock 20MHz --09/09/13------
	if	_?FREQ == 20
		movlw	D'119'	
		movwf	_?sCount
_?Ltimed500
		decfsz	_?sCount,F	; 2012/03/26 
		goto		_?Ltimed500
		nop
		nop
		movlw	D'4'	
	endif
;------- 500us - clock 4MHz --09/09/13------
	if	_?FREQ == 4
		movlw	D'19'	
		movwf	_?sCount
_?Ltimed500
		decf	_?sCount,F	; 2012/03/26 
		goto		_?Ltimed500
		nop
		nop
		movlw	D'4'	
	endif
;------- 500us - common --------------
	movwf	_?msCount
_?Ltimed300
	call	Delay_100us
	decfsz	_?msCount,F	; 2012/03/26 
	goto	_?Ltimed300
	return
;=====================================
Delay_100us:
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

		movlw	d'44'
		movwf	_?usCount
_?Ltimed200
		nop
		decfsz	_?usCount,F	; 2012/03/26 
		goto	_?Ltimed200

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
		decfsz	_?usCount,F	; 2012/03/26 
		goto	_?Ltimed200
		return
	endif
;------- 100us - clock 10MHz --09/09/13------
	if	_?FREQ == 10
		movlw	5
		movwf	_?usCount
_?Ltimed200
		nop
		decfsz	_?usCount,F	; 2012/03/26 
		goto	_?Ltimed200
		movlw	8
		movwf	_?usCount
_?Ltim_lp1
		goto	$+1		
		nop
		nop
		movlw	5
		movwf	_?msCount		
_?Ltim_lp3:
		decfsz	_?msCount,F
		goto	_?Ltim_lp3
		decfsz	_?usCount,F
		goto	_?Ltim_lp1
		return
	endif
;------- 100us - clock 4MHz --09/09/13------
	if	_?FREQ == 4		;ここはこれで完結
		call Delay_50us
		movlw	D'9'	
		movwf	_?usCount
_?Ltim_lp1
		goto	$+1
		decfsz	_?usCount,F
		goto	_?Ltim_lp1
		return
	endif
;===========================================
Delay_50us:
;------- 50us - clock 20MHz --09/09/13------
	if	_?FREQ == 20
		movlw	19	
		movwf	_?usCount
_?Ltimed2000
		decfsz	_?usCount,F	; 2012/03/26 
		goto	_?Ltimed2000
		goto	$+1
		nop
		movlw	3
	endif
;------- 50us - clock 128MHz --09/09/13------
	if	_?FREQ == 128
		movlw	2	
		movwf	_?usCount
_?Ltimed2000
		decfsz	_?usCount,F	; 2012/03/26 
		goto	_?Ltimed2000
		movlw	4
	endif
;------ 50us - clock 10MHz --09/09/13------
	if	_?FREQ == 10
		goto		$+1
		movlw	5
		movwf	_?usCount
_?Ltimed2000
		decfsz	_?usCount,F	; 2012/03/26 
		goto _?Ltimed2000

		movlw	10
		movwf	_?usCount
_?Ltim_lp11
		decfsz	_?usCount,F
		goto	_?Ltim_lp11
		goto	$+1
		return
	endif
;****************************************************
;------- 50us - clock 4MHz --09/09/13------ 2012/03/26 
	if	_?FREQ == 4
		movlw	4
		movwf	_?usCount
_?Ltimed2000
		decfsz	_?usCount,F	
		goto _?Ltimed2000

		movlw	10
		movwf	_?usCount
_?Ltim_lp11
		decfsz	_?usCount,F
		goto	_?Ltim_lp11
		goto	$+1
		return
	endif
;;============================================
Delay_10us
;------- 10us - clock 12.8MHz -09/09/13------
	if	_?FREQ == 128
		nop
		movlw	8
	endif
;------- 10us - clock 20MHz -09/09/13-------
	if	_?FREQ == 20
		goto	$+1
		goto	$+1
		goto	$+1		
		nop
		movlw	12	
	endif
;------- 10us - clock 10MHz -09/09/13------- 2012/03/26 
	if	_?FREQ == 10
		goto	$+1		
		movlw	1
	endif
;------- 10us - clock 4MHz -09/09/13------- 2012/03/26 
	if	_?FREQ == 4
		goto	$+1		
		movlw	1
	endif
;------- 10us - common(4,10,12.8,20) ------ 2012/03/26 
;	_?sCountは100us,50usでは使用していない
	movwf	_?sCount		
_?Ltim_lp2:
	decfsz	_?sCount,F
	goto	_?Ltim_lp2
	return
;===============================================
#endif		;_TIMER_ABS_INC_INCLUDED
	LIST
