;	vim:	set syntax=pic:		ts=4	sts=4	sw=4
;	pamscls_sample.asm		Last Change:2012/03/07 21:07:04.
;	Pamscls���g�����T���v���v���O����
;------------------------------------
;	if��	��r�l1�͕ϐ��A��r�l2�͕ϐ�
	_?if	sw1_sht,EQ,memo,QUIT	;sw1��short on�ł���
		bsf		Out_Sound
		goto	exit
	_?endif
;------------------------------------
;	ifcnst��	��r�l1�͕ϐ��A��r�l2�͒萔
#define	ON	1
	_?ifcnst	sw1_sht,EQ,ON,QUIT	;sw1��short on�ł���
		bsf		Out_Sound
		goto	exit
	_?endif
;------------------------------------
;	ifbit��		���肷�郌�W�X�^�[�͕ϐ��A�r�b�g�ʒu�͒萔
		_?movlf	B'00000010', w_temp
		_?ifbit	w_temp,1,CL,AND
		_?c_bit	w_temp,0,ST,QUIT
			nop
			nop
		_?else
			nop
			nop
			nop
		_?endbit
;------------------------------------
;	ifbit����whilecnst���̕���
;	ifbit��		���肷�郌�W�X�^�[�͕ϐ��A�r�b�g�ʒu�͒萔
		_?ifbit	STATUS,Z,ST,QUIT	;code��0x00�ł���ΒP��̏I���
			_?movlf	2,spc
			call	send_spce		;�P��Ԃ�space�𑗐M
			movf	codes,W
			andlw	b'00000111'
			_?whilecnst	length,GT,0,QUIT
				rlf		codes,F		;codes(MSB) => carry
									;������dot/dash�𔻒肵�āA���M����
				_?ifcnst	STATUS,C,ST,QUIT
					call	send_dot
				_?else
					call	send_dash
				_?endif
				decf	length,F	;����codes
			_?endwhile
			_?movlf	1,spc
			nop
			nop	;BBB
		_?else
			call	send_spce ;char�Ԃ�space�̂��߂̑҂�����
		_?endif
;------------------------------------
;	while��		��r�l1�A��r�l2�͕ϐ�
	_?while i,LT,memo,QUIT
		bsf	Out_Sound
		bsf	Out_Tx
		call timeDelay1s
		bcf	Out_Sound
		bcf	Out_Tx
		incf	i
	_?endwhile
;------------------------------------
;	whilecnst��		��r�l1�͕ϐ��A��r�l2�͒萔
	_?whilecnst i,LT,D'3',QUIT
		bsf	Out_Sound
		bsf	Out_Tx
		call timeDelay1s
		bcf	Out_Sound
		bcf	Out_Tx
		incf	i
	_?endwhile
;------------------------------------
;	whilebit��		bit test	
	_?whilebit flag,2,ST,QUIT	;flag��bit<2>��set => true
		bsf	Out_Sound
		bsf	Out_Tx
		call timeDelay1s
		bcf	Out_Sound
		bcf	Out_Tx
		incf	i
	_?endwhile
;------------------------------------
;	forinccnst��	�����l�͕ϐ�, �I���l, �����l �Ƃ��ɒ萔
;		_?endfor �Ɉ�������������
	_?forinccnst	i, D'5', 1
		bsf		Out_Sound
		call timeDelay05s
		bcf		Out_Sound
	_?endfor	i
;------------------------------------
;	forinc��	�����l, �I���l �Ƃ��ɕϐ�, �����l�͒萔
;		_?endfor �Ɉ�������������
top	movlw	1
	movwf	dat1
	movlw	3
	movwf	dat2
	_?forinc	dat1,dat2,1
		incf	W,W
	_?endfor	dat1
;------------------------------------
;	repeat��	��r�l1�͕ϐ��A��r�l2�͕ϐ�
top	movlw	1
	movwf	dat1
	movlw	3
	movwf	dat2
	movlw	-1
	movwf	dat3
	movlw	B'00000111'
tp2	_?repeat
		movwf	PORTA
		clrf	PORTA
		incf	dat1,F
		incf	dat3,F
	_?until	dat1,GE,dat2,QUIT
;------------------------------------
;	repeat��	��r�l1�͕ϐ��A��r�l2�͒萔
	_?repeat
		bsf		Out_Tx
		call	timeDelay05s
		bcf		Out_Tx
		incf	i
	_?untilcnst	i,EQ,D'5',QUIT
;------------------------------------
;	repeat��	bit test
	_?repeat
		bsf		Out_Tx
		call	timeDelay05s
		bcf		Out_Tx
		incf	i
	_?untilbit	flag,0,CL,QUIT
					;flag��bit<0>��clear�ł���ƏI��
;------------------------------------
;	switch��	
top	movlw	'A'
	movwf	memo1
	movlw	'B'
	movwf	memo3
	movlw	'D'
	movwf	memo4
tp2	movlw	'A'
	_?switch
	_?c_case memo1		;�ϐ�
	_?c_casecnst 'A'	;�萔
	_?case memo3
		movlw	10		
		_?break
	_?casecnst	4		;�萔
		rlf	TMP,F
		rrf	TMP,F
		_?break
	_?default
		movlw	9
	_?endswitch
;------------------------------------

