;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2012/03/18 14:04:42.
;	���̃t�@�C���� _?romadrs���`�m�ۂ���	
;	���̃t�@�C����absolute
	LIST
; ==== Eeprom_sub_abs.inc ==== Ver 1.0d	====== �x�� �獎 JG1DVF =========
	NOLIST
;-------------------------------------------------
;	���̃t�@�C����absolute
;	16F84,16F84A,12F629,12F675,12F628A,12F648A,16F87,16F88
;-------------------------------------------------
;	banksel ���g���A�ėp�Ƃ���
;	�啝�Ȏd�l�ύX	2010/06/28 
;		Rd:	�ǂݏo�����f�[�^��Wreg�ɓ���
;			�ǂݏo���Ԓn��_?romadrs�ɓ���Ă���
;		Wr: �������ރf�[�^��Wreg�ɓ���Ă���
;			�����o���Ԓn��_?romadrs�ɓ���Ă���
;************************************************************
#ifndef	_EEPROM_SUB_ABS_INC_INCLUED
#define	_EEPROM_SUB_ABS_INC_INCLUED
;************************************************************
;===================================================================
;	Eeprom_sub.asm �̂��߂̍�ƕϐ�
;		Eeprom_sub_abs.inc�Ŏg���ϐ��͂����Œ�`����		12/3/8
;		_?BTMMEMO��Pamscls_abs_variable.inc�Œ�`���Ă���
;		_?romdata�͕s�v Wreg���g��
	cblock ( _?BTMMEMO - 0x0f + 4 )
_?romadrs		;���̃v���O�����̓����Ŏg��
	endc
;===================================================================
;	Rd_eeprom : eeprom����1byte�ǂݏo��
;		eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;		�ǂݏo�����f�[�^��Wreg�ɓ���
;************************************************************
#ifndef	_EEPROM_SUB_ABS_ASM_INCLUED
#define	_EEPROM_SUB_ABS_ASM_INCLUED
;************************************************************
Rd_eeprom ;eeprom��address:_?romadrs����ǂݏo���AWreg�֊i�[����
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
;	Wr_eeprom : eeprom��1byte��������	2011/04/09 �C��
;		�������ރf�[�^��Wreg�ɓ��ꂨ��
;		�������ݐ��eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;===================================================================
Wr_eeprom ;eeprom �֏������ށ@�������݃f�[�^��Wreg,��������address��_?romadrs
		movwf	_?romdata
		movf	_?romadrs,W

	ifdef	__16F84
		movwf	EEADR		;bank0
		movf	_?romdata,w
		movwf	EEDATA
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
		BANKSEL	_?romdata	;bank0
		RETURN		
	endif
	ifdef	__16F84A
		movwf	EEADR		;bank0
		movf	_?romdata,w
		movwf	EEDATA
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