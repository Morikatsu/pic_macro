; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2010/01/28 08:28:45.
;	ADC_sub.inc		���C���v���O�����ł���4���ڂ��s���Ă���
;	�E�R���p���[�^��off	[CMCON]	.................. ������
;	�EADC�Ɏg��port����͂Ƃ��� [TRIS*] .......... ������
;	�EADC�Ɏg��port�ƕϊ��N���b�N��ݒ� [ANSEL] .. ������
;	�EADCON0�ɐݒ肷��ADC��ch, Vref, data format��Wreg�ɓ����Ă��邱�Ƃ��O��
;	���ʂ�Wreg�ɓ��� [�{����ADRESH, ADRESL�ɓ���]
;************************************************************************
ADC		;ADC���J�n���A���ʂ�Wreg(upper�̂�)�ɓ����
;	movlw	H'03'		;ch1, ��d��=Vdd, ���l
;	MOVWF		ADCON0	;�[�d�J�n[ADC����]
	MOVWF		ADCON0	;�[�d�J�n[ADC����]
	call	timeDelay50us	;50us �[�d���� �{����20us�ŉ�
	BSF		ADCON0,GO
Wait_ADC	;
	BTFSC		ADCON0,GO	;ADC������skip
	GOTO		Wait_ADC
;		bsf		STATUS,RP0	;bank1
;	MOVF		ADRESL,W	;
;		bcf		STATUS,RP0	;bank0
	MOVF		ADRESH,W	;���ʂ�0..255�͈̔͂œ�����
	RETURN		
;********* end of ADC ************************************