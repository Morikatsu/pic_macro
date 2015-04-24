;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2012/04/28 12:28:10.
;	Eeprom_sub_abs.inc		Ver 1.0e	堀野 守克 JG1DVF
;	このファイルは _?romadrsを定義確保する	
;-------------------------------------------------
;	このファイルはabsolute
;************************************************************
;	16F84,16F84A,12F629,12F675,12F628A,12F648A,16F87,16F88
;	修正	_?selbank* を使い、汎用とする
;	16F84と12F629/675|16F628/648と16F87/88では
;			{EEDATA,EEADR}と{EECON1,EECON2}のbankが異なる
;					EEDATA		EECON1		EEDATH
;					EEADR		EECON2		EEADRH
; 16F84				bank0		bank1		 -		__TypeA
; 12F629/675		bank1		bank1		 -		__TypeB
; 16F628/648		bank1		bank1		 -		__TypeB
; 16F87/88			bank2		bank3		bank2	__TypeC
;	16F87/88に関しては検討不十分
;************************************************************
	LIST
;== Eeprom_sub_abs.inc Ver 1.0e == 堀野 守克 JG1DVF == Last Change:2012/04/28 12:28:10. ==
	NOLIST
;-------------------------------------------------
;	banksel を使い、汎用とする
;	大幅な仕様変更	2010/06/28 2012/04/21 
;		Rd:	読み出したデータはWregに入る
;			読み出す番地は_?romadrsに入れておく
;		Wr: 書き込むデータはWregに入れておく
;			書き出す番地は_?romadrsに入れておく
;			戻りには割り込み不可とする
;************************************************************
#ifndef	_EEPROM_SUB_ABS_INC_INCLUED
#define	_EEPROM_SUB_ABS_INC_INCLUED
;===================================================================
;	Eeprom_sub.asm のための作業変数
;		Eeprom_sub_abs.incで使う変数はここで定義する		12/3/8
;		_?BTMMEMOはPamscls_abs_variable.incで定義している
;		_?romdataは不要 Wregを使う
;		_?romadrsは共通領域に置かれるので、bankの指定はいらない。
	cblock ( _?BTMMEMO - 0x0f + 4 )
_?romadrs		;このプログラムの内部で使う
	endc
;************************************************************
	ifdef	(__16F84)||(__16F84A)
#define	__TypeA
	endif
	;+++++++++++
	ifdef	(__12F629)||(__12F675)||(_16F628A)||(__16F648A)
#define	__TypeB
	endif
	;+++++++++++
	ifdef	(__16F87)||(_16F88)
#define	__TypeC
	endif
;===================================================================
;	Rd_eeprom : eepromから1byte読み出す
;		eepromのアドレスは_?romadrsに入れておく
;		読み出したデータはWregに入る
;===================================================================
Rd_eeprom ;eepromのaddress:_?romadrsから読み出し、Wregへ格納する
	;++++++++++++++++++++++++++++++++++++
	ifdef	__TypeA
		movf	_?romadrs,W	;
		movwf	EEADR		;bank0
		_?selbank1
		bsf		EECON1,RD	;bank1	
		_?selbank0
		movf	EEDATA,W	;bank0	
		RETURN		
	endif
	;++++++++++++++++++++++++++++++++++++
	ifdef	__TypeB
		movf	_?romadrs,W	;
		_?selbank1
		movwf	EEADR		;bank1
		bsf		EECON1,RD	;bank1	
		movf	EEDATA,W	;bank1
		_?selbank0
		RETURN		
	endif
	;++++++++++++++++++++++++++++++++++++
	ifdef	__TypeC
		movf	_?romadrs,W	;
		_?selbank2
		movwf	EEADR		;bank2
		_?selbank3
		bsf		EECON1,RD	;bank3	
		_?selbank2
		movf	EEDATA,W	;bank2
		_?selbank0
		RETURN		
	endif
;===================================================================
;	Wr_eeprom : eepromへ1byte書き込む	2011/04/21 修正
;		書き込むデータはWregに入れおく
;		書き込み先のeepromのアドレスは_?romadrsに入れておく
;===================================================================
Wr_eeprom ;eeprom へ書き込む　書き込みデータはWreg,書き込むaddressは_?romadrs
	;***********************************
	ifdef	__TypeA			; 2012/04/20 
		_?selbank0
		movwf	EEDATA
		movf	_?romadrs,W
		movwf	EEADR		;bank0
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
		bcf		INTCON,GIE	;割り込み不可とする
		RETURN		
	endif
	;++++++++++++++++++++++++++++++++++++
	ifdef	__TypeB		; 2012/04/20 
		_?selbank1
		movwf	EEDATA		;bank1
		movf	_?romadrs,W
		movwf	EEADR		;bank1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;
		movwf	EECON2		;
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		;-------- verify -------------
		movf	EEDATA,w
		bsf		EECON1,RD
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		_?selbank0
		bcf		INTCON,GIE	;割り込み不可とする
		RETURN		
	endif
	;++++++++++++++++++++++++++++++++++++
	ifdef	__TypeC
		_?selbank2
		movwf	EEDATA
		movwf	EEADR		;bank1
		movf	_?romadrs,w
		movwf	EEDATA
		_?selbank3
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;この行が抜けていた
		movwf	EECON2		;この行がぬけていた
		bsf		EECON1,WR	;Start the write
Wr_lp:	
		btfsc	EECON1,WR
			goto	Wr_lp
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
		bcf		INTCON,GIE	;割り込み不可とする
		RETURN		
	endif
;--------- end of Wr_eeprom ----------
#endif		;_EEPROM_SUB_ABS_INC_INCLUED
