; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2011/03/23 13:01:56.
	LIST
;=== Timer_abs_LCmeter.inc === Ver 1.1b ==========================	
	NOLIST
;	software timer  Timer.inc�Ɠ������̂ł���B
;	�A���ALC_meter.asm��p�Ȃ̂Ń������e�ʂ̊֌W�Ŏg����x�����Ԃ�
;		Delay_10ms, Delay_100us �݂̂Ɍ��肵�Ă���B
;************************************************************
#ifndef	_TIMER_ABS_INC_INCLUDED
#define	_TIMER_ABS_INC_INCLUDED
;************************************************************
;	����subroutine��include����ꏊ�̓v���O�����̈��
;	�I��̕���[ end�s�̒��O ]�Ƃ���
;=====================================================
;	system clock�� _?FREQ �Ŏw�肷��	4, 10, 12.8, 20 MHz
;		#define	_?FREQ	20		main�v���O�����ɂĒ�`����
;	�g�p����N���b�N���ɑΉ������s�𐶂��� [���C���v���O�����ɂ�]
;	_?FREQ��macro variable�ł���
;		_?FREQ	set	4		;clock 4MHz
;		_?FREQ	set	10		;clock 10MHz
;		_?FREQ	set	20		;clock 20MHz
;		_?FREQ	set	128		;clock 12.8MHz
;====== �ϐ���` ===============================
;	_?sCount, _?msCount, _?usCount, _?usCount0����ƕϐ��Ƃ��Ďg��
;	���̗̈��chip���ɈقȂ鎩���ݒ�Ƃ���  10/05/25
;	��ƕϐ����m�ۂ��邽�߂� _?BTMMEMO��Pamscls_abs.inc�Œ�`���Ă���B
;	�]���āA�ȉ���cblock�̓R�����g�A�E�g���Ă���B
;===============================================
;	cblock ( _?BTMMEMO - 0x0f + 5 )		;�����̓}�N���łȂ��Ă悢
;_?sCount		;���̃v���O�����̓����Ŏg��
;_?msCount		;���̃v���O�����̓����Ŏg��
;_?usCount		;���̃v���O�����̓����Ŏg��
;	endc
;==============================================
;	�g����:
;		movlw	D'100'			;1s�̒x��
;		call	Delay_10ms
;			�ő�2.55s�̒x��������
;		movlw	d'20'
;		call	Delay_100us		;2ms[100*20]�̒x��
;	���Ԃ̌덷��1%���x�ł���
;	100us�ȉ��̎��Ԃɂ��Ă͌ʂɍ쐬����K�v������
;		timeDelay50us
;================================================
#ifndef	_?FREQ
	error "_?FREQ  not defined! ---- Timer.inc ----"
#endif
;================================================
Delay_10ms:
	movwf	_?sCount
_?Ltimed1s
	movlw	15
	movwf	_?msCount
_?Ltimed10
	call	_?timeDelay1ms
	decf	_?msCount,f
	btfss	STATUS,2
	goto	_?Ltimed10
	
	decf	_?sCount,f
	btfss	STATUS,2
	goto	_?Ltimed1s
	return
;==============================================
;	------ 1 mSec Time Delay ----- �x�� �獎
;	���̕����͊e�N���b�N���ɂقڐ��m�ł���B
;		�ő�0.5%�̌덷
;	timeDelay1ms
;==============================================
_?timeDelay1ms:
;----- 1ms - clock 20 MHz ------	
	if _?FREQ == 20
		movlw	D'193'
		movwf	_?usCount
_?Ltimed12:		
		goto 	$+1
		goto 	$+1
		goto 	$+1
		goto 	$+1
		decf	_?usCount, F
		bnz 	_?Ltimed12

		movlw 	D'167'
		movwf	_?usCount
_?Ltimed1
		goto 	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1
		goto 	$+1
		goto 	$+1
		goto	$+1
		goto	$+1
		goto	$+1
		return
	endif
;------ 1ms - clock 12.8MHz -----	
	if _?FREQ == 128
		movlw	D'95'
		movwf	_?usCount
_?Ltimed12:		
		goto 	$+1
		goto 	$+1
		goto 	$+1
		decf	_?usCount
		bnz		_?Ltimed12

		movlw	D'117'	
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1

		goto 	$+1
		goto 	$+1
		nop
		return
	endif
;------ 1ms - clock 10MHz --------
	if _?FREQ == 10
		movlw	166
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1
		return
	endif
;------ 1ms - clock 4MHz --------
	if _?FREQ == 4
		movlw	66
		movwf	_?usCount
_?Ltimed1
		goto	$+1
		goto	$+1
		goto	$+1
		decf	_?usCount,f
		bnz		_?Ltimed1
		return
	endif
;;==========================================
Delay_100us:
	movwf	_?sCount
_?Ltimed11s
	call	_?timeDelay100us
	decf	_?sCount,f
	btfss	STATUS,2
	goto	_?Ltimed11s
	return
;++++++++++++++++++++++++++++++++++++++++++++
_?timeDelay100us:
;------- 100us - clock 20MHz --09/09/13------
	if	_?FREQ == 20
		movlw	8
		movwf	_?usCount
_?Ltim_lp1
		goto	$+1
		nop
		nop
		movlw	201	
		movwf	_?msCount		
_?Ltim_lp2:
		decfsz	_?msCount,F
		goto	_?Ltim_lp2
		decfsz	_?usCount,F
		goto	_?Ltim_lp1

		movlw	d'19'
		movwf	_?usCount
_?Ltimed200
		nop
		decf	_?usCount,F
		bnz		_?Ltimed200

		goto	$+1
		goto	$+1
		goto	$+1
		goto	$+1
		return
	endif
;------- 100us - clock 128MHz --09/09/13------
	if	_?FREQ == 128
		movlw	9
		movwf	_?usCount
_?Ltim_lp1
		movlw	8
		movwf	_?msCount
_?Ltim_lp2:
		decfsz	_?msCount,F
		goto	_?Ltim_lp2
		goto	$+1
		decfsz	_?usCount,F
		goto	_?Ltim_lp1

		movlw	10
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		bnz		_?Ltimed200
		return
	endif
;------- 100us - clock 10MHz --09/09/13------
	if	_?FREQ == 10
		movlw	5
		movwf	_?usCount
_?Ltimed200
		nop
		decf	_?usCount,F
		bnz		_?Ltimed200
		movlw	8
		movwf	_?usCount
_?Ltim_lp1
		goto	$+1		
		nop
		nop
		movlw	5
		movwf	_?msCount		
_?Ltim_lp2:
		decfsz	_?msCount,F
		goto	_?Ltim_lp2
		decfsz	_?usCount,F
		goto	_?Ltim_lp1
		return
	endif
;------- 100us - clock 4MHz --09/09/13------
	if	_?FREQ == 4		;�����͂���Ŋ���
		movlw	7
		movwf	_?usCount
_?Ltimed200
		decf	_?usCount,F
		btfss	STATUS,2
		goto _?Ltimed200
		movlw	D'14'	
		movwf	_?usCount
_?Ltim_lp1
		nop
		decfsz	_?usCount,F
		goto	_?Ltim_lp1
		goto	$+1
		goto	$+1
		nop
		return
	endif
;;===========================================
;timeDelay50us
;;------- 50us - clock 20MHz --09/09/13------
;	if	_?FREQ == 20
;		movlw	19	
;		movwf	_?usCount
;_?Ltimed2000
;		decf	_?usCount,F
;		bnz		_?Ltimed2000
;		goto	$+1
;		nop
;		movlw	3
;	endif
;;------- 50us - clock 128MHz --09/09/13------
;	if	_?FREQ == 128
;		movlw	2	
;		movwf	_?usCount
;_?Ltimed2000
;		decf	_?usCount,F
;		bnz		_?Ltimed2000
;		movlw	4
;	endif
;;------ 50us - clock 10MHz --09/09/13------
;	if	_?FREQ == 10
;		goto		$+1
;		movlw	4
;	endif
;;------- 50us - clock 4MHz --09/09/13------
;	if	_?FREQ == 4
;		movlw	3
;		movwf	_?usCount
;_?Ltimed2000
;		decf	_?usCount,F
;		btfss	STATUS,2
;		goto _?Ltimed2000
;		movlw	2
;	endif
;;------- 50us - common -------------
;	movwf	_?usCount
;_?Ltim_lp11
;	call	timeDelay10us
;	decfsz	_?usCount,F
;	goto	_?Ltim_lp11
;	goto	$+1
;	goto	$+1
;	goto	$+1
;	return
;============================================
;	end
#endif		;_TIMER_ABS_INC_INCLUDED
	LIST