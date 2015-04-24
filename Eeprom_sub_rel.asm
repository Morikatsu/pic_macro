;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2012/04/16 14:20:21.
;	Eeprom_sub_rel.asm		Ver 1.0d	�x�� �獎 JG1DVF
;		Rd_eeprom 	Wr_eeprom
;-------------------------------------------------
;	���̃t�@�C����relocatable�p�ł���B
;	16F84,16F84A,12F629,12F675,12F628A,12F648A,16F87,16F88
	LIST
;== Eeprom_sub_rel.asm Ver 1.0d == �x�� �獎 JG1DVF == Last Change:2012/04/16 14:20:21. ==
	NOLIST
;	��ƕϐ�_?romadrs�͂��̃v���O�������ɂ�	��`(�m��)���Ă���
;	���̃t�@�C���ɂ͔ėp�łȂ�����������
;-------------------------------------------------
;	banksel ���g���A�ėp�Ƃ��� 2010/06/19 
;	�啝�Ȏd�l�ύX	2010/06/28 
;		Rd:	�ǂݏo�����f�[�^��Wreg�ɓ���
;			�ǂݏo���Ԓn��_?romadrs�ɓ���Ă���
;		Wr: �������ރf�[�^��Wreg�ɓ���Ă���
;			�����o���Ԓn��_?romadrs�ɓ���Ă���
;			�߂�ɂ͊��荞�ݕs�Ƃ���
;************************************************************
#ifndef	_EEPROM_SUB_REL_INC_INCLUED
#define	_EEPROM_SUB_REL_INC_INCLUED
;************************************************************
	list p=pic16f648a			;�ȉ�3�s�͔ėp�ł͂Ȃ�
	#include <p16f648a.inc>
 	ERRORLEVEL -302
;====================================================
;	Rd_eeprom,Wr_eeprom�̂��߂̍�ƕϐ�
;	relocatable�Ȃ̂ŕϐ��̈ʒu���Œ肵�Ă��Ȃ�
;	�ϐ��ɃA�N�Z�X����ۂ�banksel���g���΂悢
;====================================================
	ifdef	__16F84
_?TOPMEMO	equ		0x0c	;GPR�̐擪
_?BTMMEMO	equ		0x4F	;GPR(����)�̏I���
	endif
	ifdef	__16F84A
_?TOPMEMO	equ		0x0c
_?BTMMEMO	equ		0x4F
	endif
	;++++++++++++
	ifdef	__12F629		;07/06/15
_?TOPMEMO	equ		0x20	;GPR�̐擪
_?BTMMEMO	equ		0x5F	;GPR(����)�̏I���
	endif
	ifdef	__12F675		;09/04/21 �ǉ�
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x5F
	endif
	ifdef	__12F683		;10/04/02 �ǉ�
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	;++++++++++++
	ifdef	__16F627A		;09/04/21 �ǉ�
_?TOPMEMO	equ		0x20
_?BTMMEMO	equ		0x7F
	endif
	ifdef	__16F628A		;09/04/21 �ǉ�
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
_?romadrs	res	1	;���̃v���O�����̓����Ŏg��
;=====================================================
	global	_?romadrs		;
	global	Rd_eeprom,Wr_eeprom
;=====================================================
eeprom_code	code	h'723'	;h'fa0'		���̍s�͔ėp�ł͂Ȃ��B
;=====================================================
;	Rd_eeprom : eeprom����1byte�ǂݏo��
;		eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;		�ǂݏo�����f�[�^��Wreg�ɓ���
;===================================================================
Rd_eeprom ;eeprom��ǂݏo���A_?romdata�֊i�[����,�ǂݏo��address��_?romadrs
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
;	Wr_eeprom : eeprom��1byte��������
;		�������ރf�[�^��_?romdata�ɓ��ꂨ��
;		�������ݐ��eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;===================================================================
Wr_eeprom ;eeprom �֏������ށ@�������݃f�[�^��_?romdata,��������address��_?romadrs
		banksel	EEDATA
		movwf	EEDATA		;�������ރf�[�^��EEDATA�Ɋi�[

		banksel	_?romadrs
		movf	_?romadrs,w	;�������ޔԒn��Wreg�ɓ����
		banksel	EEADR
		movwf	EEADR		;�������ޔԒn��EEADR�ɓ����

		banksel	EECON1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;�������݃V�[�P���X ���荞�ݒ�~
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
		bsf		INTCON,GIE	;���荞�݉Ƃ���
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
		bcf		INTCON,GIE	;���荞�ݕs�Ƃ���

		RETURN		
;--------- end of Wr_eeprom ----------
	end
#endif		;_EEPROM_SUB_REL_INC_INCLUED
