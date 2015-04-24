; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2012/06/18 13:47:44.
	NOLIST
;**********************************************************
;	MyWaku.inc		Last Change:2012/06/18 13:47:44.
;	Include file for my Project
;**********************************************************
	LIST	p=12f675
	include <p12f675.inc>
	errorlevel -302
	LIST r=DEC
	include <c:\Users\Tora\1_pic\MyLibrary\Pamscls_abs.inc>
CB	=	_BODEN_ON		;ブラウンアウト リセットを使う
CB &=	_MCLRE_OFF		;MCLR リセットは使わない　GP3はDI(key dot)として使う
CB &=	_INTRC_OSC_NOCLKOUT;内部発振(4MHz)を使う 3番pinはGP4として使う
CB &=	_WDT_OFF		;ウォッチドック タイマは使わない
CB &=	_PWRTE_ON		;パワーアップ タイマを使う
CB &=	_CP_OFF			;コードプロテクトは使わない
CB &=	_CPD_OFF		;EEPROMデータのプロテクトは使わない
	__CONFIG  CB 
;***** VARIABLE DEFINITIONS
	cblock _?TOPMEMO	;0x20
w_temp		;Wregの保存用
s_temp		;STATUSの保存用
	endc
;************************************************************
#define	_?FREQ	4		;clock 4MHz
;************************************************************
	ORG     0x000       ; processor reset vector
	goto    main        ; go to beginning of program
;************************************************************
;	ORG     0x004		;TMR0,TMR1の割り込み
;************************************************************
main:
;*********************************************************
	#include	"d:\1_PIC\MyLibrary\Eeprom_sub.inc"
	#include	"d:\1_PIC\MyLibrary\Timer.inc"
;***********************************************
	END
