; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2010/05/28 16:56:39.
	NOLIST
;**********************************************************
;	MyHeader.inc		Last Change:2010/05/28 16:56:39.
;	Include file for my Project
;**********************************************************
	LIST	p=12f675
	include <p12f675.inc>
	errorlevel -302
	LIST r=DEC
	include <d:\1_pic\MyLibrary\MyUtility.inc>
	include <d:\1_pic\MyLibrary\Pamscls.inc>
CB	=	_BODEN_ON		;�u���E���A�E�g ���Z�b�g���g��
CB &=	_MCLRE_OFF		;MCLR ���Z�b�g�͎g��Ȃ��@GP3��DI(key dot)�Ƃ��Ďg��
CB &=	_INTRC_OSC_NOCLKOUT;�������U(4MHz)���g�� 3��pin��GP4�Ƃ��Ďg��
CB &=	_WDT_OFF		;�E�H�b�`�h�b�N �^�C�}�͎g��Ȃ�
CB &=	_PWRTE_ON		;�p���[�A�b�v �^�C�}���g��
CB &=	_CP_OFF			;�R�[�h�v���e�N�g�͎g��Ȃ�
CB &=	_CPD_OFF		;EEPROM�f�[�^�̃v���e�N�g�͎g��Ȃ�
	__CONFIG  CB 
;***** VARIABLE DEFINITIONS
	cblock _?TOPMEMO	;0x20
w_temp		;Wreg�̕ۑ��p
s_temp		;STATUS�̕ۑ��p
	endc
;************************************************************
	ORG     0x000         ; processor reset vector
	goto    main          ; go to beginning of program
;************************************************************
;	ORG     0x004		;TMR0,TMR1�̊��荞��
;************************************************************
main:
;*********************************************************
	#include	"d:\1_PIC\MyLibrary\Eeprom_sub.inc"
	#include	"d:\1_PIC\MyLibrary\Timer.inc"
;***********************************************
	END