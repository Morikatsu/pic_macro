;	vim: set syntax=pic ts=4 sts=4 sw=4: Last Change:2010/05/31 22:48:30.
;	Eeprom_sub.inc �x�� �獎 JG1DVF
;-------------------------------------------------
;	_?romadrs,_?romdata�̓��C�����Ő錾���Ă���
;-------------------------------------------------
;	�C��	_?selbank* ���g���A�ėp�Ƃ���
;	16F84��12F620/675|16F628/648��16F87/88�ł�
;			{EEDATA,EEADR}��{EECON1,EECON2}��bank���قȂ�
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
;	Eeprom_sub.asm �̂��߂̍�ƕϐ�  _?BTMMEMO��Pamscls.inc�Œ�`���Ă���
;====== �ϐ���` ===============================
	cblock ( _?BTMMEMO - 0x0f + 6 )		;�����̓}�N���łȂ��Ă悢
_?romadrs		;���̃v���O�����̓����Ŏg��
_?romdata		;���̃v���O�����̓����Ŏg��
	endc
;===================================================================
;	Rd_eeprom : eeprom����1byte�ǂݏo��
;		eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;		�ǂݏo�����f�[�^��_?romdata�ɓ���
;===================================================================
Rd_eeprom ;eeprom��ǂݏo���A_?romdata�֊i�[����,�ǂݏo��address��_?romadrs
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
;	Wr_eeprom : eeprom��1byte��������
;		�������ރf�[�^��_?romdata�ɓ��ꂨ��
;		�������ݐ��eeprom�̃A�h���X��_?romadrs�ɓ���Ă���
;===================================================================
Wr_eeprom ;eeprom �֏������ށ@�������݃f�[�^��_?romdata,��������address��_?romadrs
		movf		_?romadrs,w

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
#endif		;_EEPROM_SUB_INC_INCLUED