;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2012/03/18 14:04:42.
;	このファイルは _?romadrsを定義確保する	
;	このファイルはabsolute
	LIST
; ==== Eeprom_sub_abs.inc ==== Ver 1.0d	====== 堀野 守克 JG1DVF =========
	NOLIST
;-------------------------------------------------
;	このファイルはabsolute
;	16F84,16F84A,12F629,12F675,12F628A,12F648A,16F87,16F88
;-------------------------------------------------
;	banksel を使い、汎用とする
;	大幅な仕様変更	2010/06/28 
;		Rd:	読み出したデータはWregに入る
;			読み出す番地は_?romadrsに入れておく
;		Wr: 書き込むデータはWregに入れておく
;			書き出す番地は_?romadrsに入れておく
;************************************************************
#ifndef	_EEPROM_SUB_ABS_INC_INCLUED
#define	_EEPROM_SUB_ABS_INC_INCLUED
;************************************************************
;===================================================================
;	Eeprom_sub.asm のための作業変数
;		Eeprom_sub_abs.incで使う変数はここで定義する		12/3/8
;		_?BTMMEMOはPamscls_abs_variable.incで定義している
;		_?romdataは不要 Wregを使う
	cblock ( _?BTMMEMO - 0x0f + 4 )
_?romadrs		;このプログラムの内部で使う
	endc
;===================================================================
;	Rd_eeprom : eepromから1byte読み出す
;		eepromのアドレスは_?romadrsに入れておく
;		読み出したデータはWregに入る
;************************************************************
#ifndef	_EEPROM_SUB_ABS_ASM_INCLUED
#define	_EEPROM_SUB_ABS_ASM_INCLUED
;************************************************************
Rd_eeprom ;eepromのaddress:_?romadrsから読み出し、Wregへ格納する
		movf	_?romadrs,W	;bank0

	ifdef	__16F84
		movwf	EEADR		;bank0
		_?selbank1
		bsf		EECON1,RD	;bank1	
		_?selbank0
		movf	EEDATA,W	;bank0	
;		movwf		_?romdata
	endif
	ifdef	__16F84A
		movwf	EEADR		;bank0
		_?selbank1
		bsf		EECON1,RD	;bank1	
		_?selbank0
		movf	EEDATA,W	;bank0	
;		movwf		_?romdata
	endif
	ifdef	__12F629
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
;		movwf		_?romdata
	endif
	ifdef	__12F675
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
;		movwf		_?romdata
	endif
	ifdef	__16F628A
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
;		movwf		_?romdata
	endif
	ifdef	__16F648A
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
;		movwf		_?romdata
	endif
	ifdef	__16F87
		_?selbank2
		movwf	EEADR		;bank2
		_?selbank3
		bsf		EECON1,RD	;bank3	
		_?selbank2
		movf	EEDATA,W	;bank2
		_?selbank0
;		movwf		_?romdata
	endif
	ifdef	__16F88
		_?selbank2
		movwf	EEADR		;bank2
		_?selbank3
		bsf		EECON1,RD	;bank3	
		_?selbank2
		movf	EEDATA,W	;bank2
		_?selbank0
;		movwf		_?romdata
	endif
		RETURN		
;===================================================================
;	Wr_eeprom : eepromへ1byte書き込む	2011/04/09 修正
;		書き込むデータはWregに入れおく
;		書き込み先のeepromのアドレスは_?romadrsに入れておく
;===================================================================
Wr_eeprom ;eeprom へ書き込む　書き込みデータはWreg,書き込むaddressは_?romadrs
		movwf	_?romdata
		movf	_?romadrs,W

	ifdef	__16F84
		movwf	EEADR		;bank0
		movf	_?romdata,w
		movwf	EEDATA
		_?selbank1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		_?selbank0
		movf	EEDATA,w
		_?selbank1
		bsf		EECON1,RD
		_?selbank0
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__16F84A
		movwf	EEADR		;bank0
		movf	_?romdata,w
		movwf	EEDATA
		_?selbank1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		_?selbank0
		movf	EEDATA,w
		_?selbank1
		bsf		EECON1,RD
		_?selbank0
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__12F629
		_?selbank1
		movwf	EEADR		;bank1
			BANKSEL	_?romdata
		movf	_?romdata,w
		_?selbank1
		movwf	EEDATA
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		movf	EEDATA,w
		bsf		EECON1,RD
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__12F675
		_?selbank1
		movwf	EEADR		;bank1
			BANKSEL	_?romdata
		movf	_?romdata,w
		_?selbank1
		movwf	EEDATA
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		movf	EEDATA,w
		bsf		EECON1,RD
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__16F628A
		_?selbank1
		movwf	EEADR		;bank1
			BANKSEL	_?romdata
		movf	_?romdata,w
		_?selbank1
		movwf	EEDATA
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		movf	EEDATA,w
		bsf		EECON1,RD
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__16F648A
		_?selbank1
		movwf	EEADR		;bank1
			BANKSEL	_?romdata
		movf	_?romdata,w
		_?selbank1
		movwf	EEDATA
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		movf	EEDATA,w
		bsf		EECON1,RD
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__16F87
		_?selbank2
		movwf	EEADR		;bank1
			BANKSEL	_?romdata
		movf	_?romdata,w
		_?selbank2
		movwf	EEDATA
		_?selbank3
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		_?selbank2
		movf	EEDATA,w
		_?selbank3
		bsf		EECON1,RD
		_?selbank2
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__16F88
		_?selbank2
		movwf	EEADR		;bank1
			BANKSEL	_?romdata
		movf	_?romdata,w
		_?selbank2
		movwf	EEDATA
		_?selbank3
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		_?selbank2
		movf	EEDATA,w
		_?selbank3
		bsf		EECON1,RD
		_?selbank2
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
;--------- end of Wr_eeprom ----------
#endif		;_EEPROM_SUB_ABS_INC_INCLUED
