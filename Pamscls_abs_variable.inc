; vim:set syntax=pic ts=4 sts=4 sw=4: �x��獎 Last Change:2012/04/28 13:22:32.
;	Pamscls_abs_variable.inc
;	���̃t�@�C����_?temp0�`_?temp7���`�m�ۂ���	
	list
; ==== Pamscls_abs_variable.inc ==== ver 1.0e ==== �x�� �獎 ===== 
	nolist
;====================================================
#ifndef	_PAMSCLS_ABS_VARIABLE_INC_INCLUDED
#define	_PAMSCLS_ABS_VARIABLE_INC_INCLUDED
;====================================================
;****************************************************
;	��ƕϐ��̊m��	10/05/25 �ύX
;	_?TOPMEMO��Pamscls, Timer.inc�ł͎g���Ă��Ȃ�
;****************************************************
	ifdef	(__16F84)||(__16F84A)||(__12F629)||(__12F675)
_?TOPMEMO	equ		0x0c	;GPR�̐擪
_?BTMMEMO	equ		0x4F	;GPR(����)�̏I���
	endif
	;++++++++++++
	ifdef	(__12F629)||(__12F675)
_?TOPMEMO	equ		0x20	;GPR�̐擪
_?BTMMEMO	equ		0x5F	;GPR(����)�̏I���
	endif
	;++++++++++++
	ifdef	(__12F683)||(__12F627A)||(__16F628A)||(__16F648A)||(__16F87)||(__16F88)
_?TOPMEMO	equ		0x20	;GPR�̐擪
_?BTMMEMO	equ		0x7F	;GPR(����)�̏I���
	endif
;****************************************************
;	��ƕϐ��̊m��	10/05/25 �ύX
;	���p�̈�ɔz�u�����̂ŁAbanksel�͕s�v
;****************************************************
	cblock		(_?BTMMEMO - 0x0f + d'8')	
;	_?romadrs��Eeprom_sub_abs.asm�Œ�`����		12/3/7
;	_sCount, _?msCount, _?usCount��Timer_abs.inc�Œ�`����@12/3/7
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
;	global��relative�̂Ƃ��ɕK�v
;	global	_?temp0,_?temp1,_?temp2,_?temp3
;	global	_?temp4,_?temp5,_?temp6,_?temp7
;	extern	_?sCount, _?msCount,_?usCount,_?romadrs
;****************************************************
#endif	;_PAMSCLS_ABS_VARIABLE_INC_INCLUDED
;****************************************************
	list