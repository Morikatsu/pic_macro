;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2012/04/16 14:20:21.
;	Eeprom_sub_rel.asm		Ver 1.0d	堀野 守克 JG1DVF
;		Rd_eeprom 	Wr_eeprom
;-------------------------------------------------
;	このファイルはrelocatable用である。
;	16F84,16F84A,12F629,12F675,12F628A,12F648A,16F87,16F88
	LIST
;== Eeprom_sub_rel.asm Ver 1.0d == 堀野 守克 JG1DVF == Last Change:2012/04/16 14:20:21. ==
	NOLIST
;	作業変数_?romadrsはこのプログラム内にて	定義(確保)している
;	このファイルには汎用でない部分がある
;-------------------------------------------------
;	banksel を使い、汎用とする 2010/06/19 
;	大幅な仕様変更	2010/06/28 
;		Rd:	読み出したデータはWregに入る
;			読み出す番地は_?romadrsに入れておく
;		Wr: 書き込むデータはWregに入れておく
;			書き出す番地は_?romadrsに入れておく
;			戻りには割り込み不可とする
;************************************************************
#ifndef	_EEPROM_SUB_REL_INC_INCLUED
#define	_EEPROM_SUB_REL_INC_INCLUED
;************************************************************
	list p=pic16f648a			;以下3行は汎用ではない
	#include <p16f648a.inc>
 	ERRORLEVEL -302
;====================================================
;	Rd_eeprom,Wr_eepromのための作業変数
;	relocatableなので変数の位置を固定していない
;	変数にアクセスする際にbankselを使えばよい
;====================================================
	ifdef	__16F84
_?TOPMEMO	equ		0x0c	;GPRの先頭
_?BTMMEMO	equ		0x4F	;GPR(共通)の終わり
	endif
	ifdef	__16F84A
_?TOPMEMO	equ		0x0c
_?BTMMEMO	equ		0x4F
	endif
	;++++++++++++
	ifdef	__12F629		;07/06/15
_?TOPMEMO	equ		0x20	;GPRの先頭
_?BTMMEMO	equ		0x5F	;GPR(共通)の終わり
	endif
	ifdef	__12F675		;09/04/21 追加
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x5F
	endif
	ifdef	__12F683		;10/04/02 追加
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	;++++++++++++
	ifdef	__16F627A		;09/04/21 追加
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	ifdef	__16F628A		;09/04/21 追加
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	ifdef	__16F648A
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	;++++++++++++
	ifdef	__16F87
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	ifdef	__16F88
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
;=====================================================
Eeprom_datgrp	udata_shr (_?BTMMEMO - 0x0f + d'7')
_?romadrs	res	1	;このプログラムの内部で使う
;=====================================================
	global	_?romadrs		;
	global	Rd_eeprom,Wr_eeprom
;=====================================================
eeprom_code	code	h'723'	;h'fa0'		この行は汎用ではない。
;=====================================================
;	Rd_eeprom : eepromから1byte読み出す
;		eepromのアドレスは_?romadrsに入れておく
;		読み出したデータはWregに入る
;===================================================================
Rd_eeprom ;eepromを読み出し、_?romdataへ格納する,読み出すaddressは_?romadrs
		banksel	_?romadrs
		movf	_?romadrs,W	;bank0

		banksel	EEADR
		movwf	EEADR		;bank2
		banksel	EECON1
		bsf		EECON1,RD	;bank3	
		banksel	EEDATA
		movf	EEDATA,W	;bank2
		
		RETURN		
;===================================================================
;	Wr_eeprom : eepromへ1byte書き込む
;		書き込むデータは_?romdataに入れおく
;		書き込み先のeepromのアドレスは_?romadrsに入れておく
;===================================================================
Wr_eeprom ;eeprom へ書き込む　書き込みデータは_?romdata,書き込むaddressは_?romadrs
		banksel	EEDATA
		movwf	EEDATA		;書き込むデータをEEDATAに格納

		banksel	_?romadrs
		movf	_?romadrs,w	;書き込む番地をWregに入れる
		banksel	EEADR
		movwf	EEADR		;書き込む番地をEEADRに入れる

		banksel	EECON1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;書き込みシーケンス 割り込み停止
		banksel	EECON2
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;
		movwf	EECON2		;
		banksel	EECON1
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;割り込み可とする
		bcf		STATUS,RP0    ;bank0
		;-------- verify -------------
		banksel	EEDATA
		movf	EEDATA,w
		banksel	EECON1
		bsf		EECON1,RD
		banksel	EEDATA
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		bcf		INTCON,GIE	;割り込み不可とする

		RETURN		
;--------- end of Wr_eeprom ----------
	end
#endif		;_EEPROM_SUB_REL_INC_INCLUED
