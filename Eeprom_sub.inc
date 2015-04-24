;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2010/05/31 22:48:30.
;	Eeprom_sub.inc 堀野 守克 JG1DVF
;-------------------------------------------------
;	_?romadrs,_?romdataはメイン側で宣言しておく
;-------------------------------------------------
;	修正	_?selbank* を使い、汎用とする
;	16F84と12F620/675|16F628/648と16F87/88では
;			{EEDATA,EEADR}と{EECON1,EECON2}のbankが異なる
;				16F84	12F675|16F648	16F88
; EEDATA,EEADR	bank0		bank1		bank2
; EECON1,EECON2	bank1		bank1		bank3
;************************************************************
#ifndef	_PAMSCLS_INC_INCLUDED
	include	<d:\1_PIC\MyLibrary\Pamscls.inc>
#endif
#ifndef	_EEPROM_SUB_INC_INCLUED
#define	_EEPROM_SUB_INC_INCLUED
;************************************************************
;	Eeprom_sub.asm のための作業変数  _?BTMMEMOはPamscls.incで定義している
;====== 変数定義 ===============================
	cblock ( _?BTMMEMO - 0x0f + 6 )		;ここはマクロでなくてよい
_?romadrs		;このプログラムの内部で使う
_?romdata		;このプログラムの内部で使う
	endc
;===================================================================
;	Rd_eeprom : eepromから1byte読み出す
;		eepromのアドレスは_?romadrsに入れておく
;		読み出したデータは_?romdataに入る
;===================================================================
Rd_eeprom ;eepromを読み出し、_?romdataへ格納する,読み出すaddressは_?romadrs
		movf	_?romadrs,W	;bank0

	ifdef	__16F84
		movwf	EEADR		;bank0
		_?selbank1
		bsf		EECON1,RD	;bank1	
		_?selbank0
		movf	EEDATA,W	;bank0	
		movwf		_?romdata
	endif
	ifdef	__16F84A
		movwf	EEADR		;bank0
		_?selbank1
		bsf		EECON1,RD	;bank1	
		_?selbank0
		movf	EEDATA,W	;bank0	
		movwf		_?romdata
	endif
	ifdef	__12F629
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
		movwf		_?romdata
	endif
	ifdef	__12F675
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
		movwf		_?romdata
	endif
	ifdef	__16F628A
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
		movwf		_?romdata
	endif
	ifdef	__16F648A
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
		movwf		_?romdata
	endif
	ifdef	__16F87
		_?selbank2
		movwf	EEADR		;bank2
		_?selbank3
		bsf		EECON1,RD	;bank3	
		_?selbank2
		movf	EEDATA,W	;bank2
		_?selbank0
		movwf		_?romdata
	endif
	ifdef	__16F88
		_?selbank2
		movwf	EEADR		;bank2
		_?selbank3
		bsf		EECON1,RD	;bank3	
		_?selbank2
		movf	EEDATA,W	;bank2
		_?selbank0
		movwf		_?romdata
	endif
		
		RETURN		
;===================================================================
;	Wr_eeprom : eepromへ1byte書き込む
;		書き込むデータは_?romdataに入れおく
;		書き込み先のeepromのアドレスは_?romadrsに入れておく
;===================================================================
Wr_eeprom ;eeprom へ書き込む　書き込みデータは_?romdata,書き込むaddressは_?romadrs
		movf		_?romadrs,w

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
#endif		;_EEPROM_SUB_INC_INCLUED
