;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2012/04/28 12:28:10.
;	Eeprom_sub_abs.inc		Ver 1.0e	�x�� �獎 JG1DVF
;	���̃t�@�C���� _?romadrs���`�m�ۂ���	
;-------------------------------------------------
;	���̃t�@�C����absolute
;************************************************************
;	16F84,16F84A,12F629,12F675,12F628A,12F648A,16F87,16F88
;	�C��	_?selbank* ���g���A�ėp�Ƃ���
;	16F84��12F629/675|16F628/648��16F87/88�ł�
;			{EEDATA,EEADR}��{EECON1,EECON2}��bank���قȂ�
;					EEDATA		EECON1		EEDATH
;					EEADR		EECON2		EEADRH
; 16F84				bank0		bank1		 -		__TypeA
; 12F629/675		bank1		bank1		 -		__TypeB
; 16F628/648		bank1		bank1		 -		__TypeB
; 16F87/88			bank2		bank3		bank2	__TypeC
;	16F87/88�Ɋւ��Ă͌����s�\��
;************************************************************
	LIST
;== Eeprom_sub_abs.inc Ver 1.0e == �x�� �獎 JG1DVF == Last Change:2012/04/28 12:28:10. ==
	NOLIST
;-------------------------------------------------
;	banksel ���g���A�ėp�Ƃ���
;	�啝�Ȏd�l�ύX	2010/06/28 2012/04/21 
;		Rd:	�ǂݏo�����f�[�^��Wreg�ɓ���
;			�ǂݏo���Ԓn��_?romadrs�ɓ���Ă���
;		Wr: �������ރf�[�^��Wreg�ɓ���Ă���
;			�����o���Ԓn��_?romadrs�ɓ���Ă���
;			�߂�ɂ͊��荞�ݕs�Ƃ���
;************************************************************
#ifndef	_EEPROM_SUB_ABS_INC_INCLUED
#define	_EEPROM_SUB_ABS_INC_INCLUED
;===================================================================
;	Eeprom_sub.asm �̂��߂̍�ƕϐ�
;		Eeprom_sub_abs.inc�Ŏg���ϐ��͂����Œ�`����		12/3/8
;		_?BTMMEMO��Pamscls_abs_variable.inc�Œ�`���Ă���
;		_?romdata�͕s�v Wreg���g��
;		_?romadrs�͋��ʗ̈�ɒu�����̂ŁAbank�̎w��͂���Ȃ��B
	cblock ( _?BTMMEMO - 0x0f + 4 )
_?romadrs		;���̃v���O�����̓����Ŏg��
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
;	Rd_eeprom : eeprom����1byte�ǂݏo��
;		eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;		�ǂݏo�����f�[�^��Wreg�ɓ���
;===================================================================
Rd_eeprom ;eeprom��address:_?romadrs����ǂݏo���AWreg�֊i�[����
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
;	Wr_eeprom : eeprom��1byte��������	2011/04/21 �C��
;		�������ރf�[�^��Wreg�ɓ��ꂨ��
;		�������ݐ��eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;===================================================================
Wr_eeprom ;eeprom �֏������ށ@�������݃f�[�^��Wreg,��������address��_?romadrs
	;***********************************
	ifdef	__TypeA			; 2012/04/20 
		_?selbank0
		movwf	EEDATA
		movf	_?romadrs,W
		movwf	EEADR		;bank0
		_?selbank1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;�������݃V�[�P���X ���荞�ݒ�~
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;���̍s�������Ă���
		movwf	EECON2		;���̍s���ʂ��Ă���
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;���荞�݉Ƃ���
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
		bcf		INTCON,GIE	;���荞�ݕs�Ƃ���
		RETURN		
	endif
	;++++++++++++++++++++++++++++++++++++
	ifdef	__TypeB		; 2012/04/20 
		_?selbank1
		movwf	EEDATA		;bank1
		movf	_?romadrs,W
		movwf	EEADR		;bank1
		bsf		EECON1,WREN		;Enable write
		bcf		INTCON,GIE	;�������݃V�[�P���X ���荞�ݒ�~
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;
		movwf	EECON2		;
		bsf		EECON1,WR	;Start the write
Wr_lp	;
		btfsc	EECON1,WR
		goto		Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;���荞�݉Ƃ���
		;-------- verify -------------
		movf	EEDATA,w
		bsf		EECON1,RD
		xorwf	EEDATA,w

		btfss	STATUS,Z
			goto Wr_eeprom
		_?selbank0
		bcf		INTCON,GIE	;���荞�ݕs�Ƃ���
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
		bcf		INTCON,GIE	;�������݃V�[�P���X ���荞�ݒ�~
		movlw	H'0055'
		movwf	EECON2
		movlw	H'00AA'		;���̍s�������Ă���
		movwf	EECON2		;���̍s���ʂ��Ă���
		bsf		EECON1,WR	;Start the write
Wr_lp:	
		btfsc	EECON1,WR
			goto	Wr_lp
		bcf		EECON1,WREN
		bsf		INTCON,GIE	;���荞�݉Ƃ���
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
		bcf		INTCON,GIE	;���荞�ݕs�Ƃ���
		RETURN		
	endif
;--------- end of Wr_eeprom ----------
#endif		;_EEPROM_SUB_ABS_INC_INCLUED
