; vim:set syntax=pic ts=4 sts=4 sw=4: �x��獎 Last Change:2012/03/18 14:34:41.
;	Lcd_abs.asm		�����absolute�p�ł���
;	http://picbegin.hp.infoseek.co.jp/proj5/p5step80.html
;	hard�̐ݒ�̓w�b�_�[�t�@�C��[Lcd_hd44780.inc]��ύX�����Ƃɂ��\�ł���
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;	list p=16f648A  r=dec, mm=on, st=off ; list directive to define processor
;	#include <p16F648A.inc>     ; processor specific variable definitions
;	errorlevel -302             ; suppress message 302 from list file
;	#include	<d:\1_PIC\MyLibrary\Pamscls_abs.inc>	;absolute
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	#include	<d:\1_PIC\MyLibrary\Lcd_header.inc>
						;Lcd_header.inc��abs, rel����
;***** �ϐ���` **************************************
	cblock
_?lcd_cmode	
_?lcd_dmode
_?lcd_emode
_?lcd_fmode
_?lcd_temp		;command|char
_?lcd_x	
_?lcd_y
_?lcd_src_adrs
	endc
;******************************************************
;				;�v���O�����͂�������n�܂�
;******************************************************
;		Lcd Control Library
;	Lcd_clear, Lcd_home, Lcd_busy, Lcd_init, 
;	Lcd_emode Set entry mode
;	Lcd_dmode Configure display mode
;	Lcd_cmode Configure cursor mode
;	Lcd_fmode Configure function set
;	Lcd_ddram Set DDRAM address
;		�eOption��Wreg�ɓ���Ă���call����
;	Lcd_cmd   Send _?lcd_temp to Lcd
;		���߂�Wreg�ɓ���Ă���call����
;	Lcd_dat   Send a chr to Lcd
;		����f�[�^��Wreg�ɓ���Ă���call����
;	Lcd_out   Send string
;		����f�[�^�̐擪��Wreg�ɓ���Ă���call����
;	Lcd_loc   Send starting loc
;	�w�b�_�[�t�@�C���� PICPORT_UPPER���`���Ă���
;		��`����..bit4~7��LCD�ɐڑ�
;		����`....bit0~3
;	Lcd��DB�͏㑤(4..7)�ڑ��Ƃ���[�Œ�]
;****************************************
;  LCD Clear operation
;  �g����          call    Lcd_Clear
;****************************************
Lcd_clear:
	movlw	0x01
	call	Lcd_cmd
	movlw	1
	call	Delay_10ms	;�ŏ�1.6ms
	return
;****************************************
;  LCD Home operation
;  �g����          call    Lcd_Home
;****************************************
Lcd_home:
	movlw	0x02
	call	Lcd_cmd
	movlw	1
	call	Delay_10ms	;�ŏ�1.6ms
	return
;****************************************
;	Lcd_loc
;	�����n�߂̈ʒu�����߂�
;	_?lcd_x={0..39},  _?lcd_y={0,1}
;****************************************
Lcd_loc:
	clrf	_?lcd_temp
	_?ifcnst	_?lcd_y,EQ,1,QUIT
		_?movlf	0x40,_?lcd_temp
	_?endif
	_?ifcnst	_?lcd_x,GE,0,AND
	_?c_cnst	_?lcd_x,LE,0x39,QUIT
		_?addff1	_?lcd_temp,_?lcd_x,f
		decf	_?lcd_temp,w
	_?else
		movwf	_?lcd_temp
	_?endif
	call	Lcd_ddram
	return
;****************************************
;	Lcd_out
;	lcd�ɕ����������
;	�����n�߂̈ʒu�͌��݂̈ʒu�Ƃ���
;	string => ������̐擪	������̏I����00
;****************************************
Lcd_out:
			movwf	_?lcd_src_adrs
Lcd_out_lp:	_?movff	_?lcd_src_adrs,FSR
			movf	INDF,w		;(_?lcd_src_adrs) => Wreg
			bz	Lcd_out_ext
			call	Lcd_dat
			incf	_?lcd_src_adrs,f
			goto	Lcd_out_lp
Lcd_out_ext:
			return
;****************************************
;  LCD Busy operation
;	LCD��ready�ɂȂ�܂őҋ@���� 
;  �g����          call    Lcd_busy
;****************************************
Lcd_busy:
#ifdef	PICPORT_UPPER		;Set data bus as output
	_?selbank1
	bcf		LCD_DATA_TRIS,4
	bcf		LCD_DATA_TRIS,5
	bcf		LCD_DATA_TRIS,6
	bcf		LCD_DATA_TRIS,7
	_?selbank0
	bcf		LCD_DATA,4
	bcf		LCD_DATA,5
	bcf		LCD_DATA,6
	bcf		LCD_DATA,7
#else		;+++++++ lower case +++++++
	_?selbank1
	bcf		LCD_DATA_TRIS,0
	bcf		LCD_DATA_TRIS,1
	bcf		LCD_DATA_TRIS,2
	bcf		LCD_DATA_TRIS,3
	_?selbank0
	bcf		LCD_DATA,0
	bcf		LCD_DATA,1
	bcf		LCD_DATA,2
	bcf		LCD_DATA,3
#endif
	;++++++++++
	_?selbank1
	bcf		LCD_CTRL_TRIS,LCD_RW	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_EN	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_RS	;Set control bus as output
	_?selbank0
	bcf		LCD_CTRL,LCD_EN	;LCD��disable�Ƃ���
	bcf		LCD_CTRL,LCD_RS	;���䃂�[�h�ɂ���
	bsf		LCD_CTRL,LCD_RW	;�ǂݍ��݃��[�h�ɂ���
	;++++++++++
#ifdef	PICPORT_UPPER	;+++++ upper case +++++
	_?selbank1
	bsf		LCD_DATA_TRIS,4		;�㑤4bit�̂ݓ��͂Ƃ���
	bsf		LCD_DATA_TRIS,5
	bsf		LCD_DATA_TRIS,6
	bsf		LCD_DATA_TRIS,7
	_?selbank0
	bsf		LCD_CTRL,LCD_EN	;LCD�𓮍삳����
	movlw	1
	call	Delay_100us
				;+++++ LCD�̏�Ԃ�4bit�ɕ����ďo�͂����
	_?ifbit	LCD_DATA,7,ST,QUIT	;RB4~7�ɐڑ�����Ă���̂� bit7��LCD��bit�ł���
		movlw	1				;PIC�ł�RB7�ƂȂ�
		call	Delay_100us		;1ms�̑ҋ@
		goto	Lcd_busy			
	_?endif

	bcf		LCD_CTRL,LCD_EN	;LCD�̓����~;
	movlw	1
	call	Delay_100us

	bsf		LCD_CTRL,LCD_EN	;LCD�̉���4bit��ǂ݂Ƃ΂�
	movlw	1
	call	Delay_100us
	_?selbank1
	bcf		LCD_DATA_TRIS,4		;�㑤4bit�̂ݏo�͂Ƃ���
	bcf		LCD_DATA_TRIS,5
	bcf		LCD_DATA_TRIS,6
	bcf		LCD_DATA_TRIS,7
	_?selbank0
#else			;+++++ lower case +++++
	_?selbank1
	bsf		LCD_DATA_TRIS,0		;����4bit�̂ݓ��͂Ƃ���
	bsf		LCD_DATA_TRIS,1
	bsf		LCD_DATA_TRIS,2
	bsf		LCD_DATA_TRIS,3
	_?selbank0
	bsf		LCD_CTRL,LCD_EN	;LCD�𓮍삳����
	movlw	1
	call	Delay_100us
				;+++++ LCD�̏�Ԃ�4bit�ɕ����ďo�͂����
	_?ifbit	LCD_DATA,3,ST,QUIT	;RB0~3�ɐڑ�����Ă���̂� bit7��LCD��bit�ł���
		movlw	1				;PIC�ł�RB3�ƂȂ�
		call	Delay_100us		;1ms�̑ҋ@
		goto	Lcd_busy			
	_?endif

	bcf		LCD_CTRL,LCD_EN		;LCD�̓����~
	movlw	1
	call	Delay_100us

	bsf		LCD_CTRL,LCD_EN	;LCD�̉���4bit��ǂ݂Ƃ΂�
	movlw	1
	call	Delay_100us
	bcf		LCD_CTRL,LCD_EN	;
	_?selbank1
	bcf		LCD_DATA_TRIS,0		;����4bit�̂ݏo�͂Ƃ���
	bcf		LCD_DATA_TRIS,1
	bcf		LCD_DATA_TRIS,2
	bcf		LCD_DATA_TRIS,3
	_?selbank0
#endif
	return
;****************************************
; LCD Initial operation
;	4bit mode, cursor increment, dual line
;	display on,
; �g����          call    Lcd_init
;	�Q�l:spectrum
;****************************************
Lcd_init:
	clrf	_?lcd_cmode	;*mode�̏�Ԃ̕ۑ��ꏊ
	clrf	_?lcd_dmode
	clrf	_?lcd_emode
	clrf	_?lcd_fmode
	;++++++++++
#ifdef	PICPORT_UPPER		;Set data bus as output
	_?selbank1
	bcf		LCD_DATA_TRIS,4
	bcf		LCD_DATA_TRIS,5
	bcf		LCD_DATA_TRIS,6
	bcf		LCD_DATA_TRIS,7
	_?selbank0
	bcf		LCD_DATA,4
	bcf		LCD_DATA,5
	bcf		LCD_DATA,6
	bcf		LCD_DATA,7
#else
	_?selbank1
	bcf		LCD_DATA_TRIS,0
	bcf		LCD_DATA_TRIS,1
	bcf		LCD_DATA_TRIS,2
	bcf		LCD_DATA_TRIS,3
	_?selbank0
	bcf		LCD_DATA,0
	bcf		LCD_DATA,1
	bcf		LCD_DATA,2
	bcf		LCD_DATA,3
#endif
	
	_?selbank1
	bcf		LCD_CTRL_TRIS,LCD_RW	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_EN	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_RS	;Set control bus as output
	_?selbank0
	;+++++++++++++++++++++++++++++++++++++++
#ifdef	PICPORT_UPPER	;++++++ PIC�̃|�[�g�͏㑤�̏ꍇ +++++++++++++++
	MOVLW	h'0F'		;LCD_DATA�̉��ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	h'30'		;��ʂS�r�b�g��'�R'���Z�b�g
		;0011(8bit mode���߂̏�4bit)��RB4..7�ɑ��邽��
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;�t�@���N�V�����Z�b�g�i�P��ځj
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	h'0F'		;LCD_DATA�̉��ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	h'30'		;��ʂS�r�b�g��'�R'���Z�b�g
		;0011(8bit mode���߂̏�4bit)��RB4..7�ɑ��邽��
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;�t�@���N�V�����Z�b�g�i�Q��ځj
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	h'0F'		;LCD_DATA�̉��ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	h'30'		;��ʂS�r�b�g��'�R'���Z�b�g
		;0011(8bit mode���߂̏�4bit)��RB4..7�ɑ��邽��
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;�t�@���N�V�����Z�b�g�i�R��ځj
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	h'0F'		;LCD_DATA�̉��ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	h'20'		;�S�r�b�g���[�h
		;0010(4bit mode���߂̏�4bit)��RB4..7�ɑ��邽��
	MOVWF	LCD_DATA		;
	BSF	LCD_CTRL,LCD_EN		;�ݒ�
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	10
	call	Delay_100us
#else	;++++++++ lower�̏ꍇ ++++++++++++++++++++++++++
	MOVLW	0F0h		;LCD_DATA�̏�ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	03h		;���ʂS�r�b�g��'�R'���Z�b�g
		;0011(8bit mode���߂̏�4bit)��RB0..3�ɑ��邽��
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;�t�@���N�V�����Z�b�g�i�P��ځj
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	0F0h		;LCD_DATA�̏�ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	03h		;���ʂS�r�b�g��'�R'���Z�b�g
		;0011(8bit mode���߂̏�4bit)��RB0..3�ɑ��邽��
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;�t�@���N�V�����Z�b�g�i�Q��ځj
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	0F0h		;LCD_DATA�̏�ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	03h		;���ʂS�r�b�g��'�R'���Z�b�g
		;0011(8bit mode���߂̏�4bit)��RB0..3�ɑ��邽��
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;�t�@���N�V�����Z�b�g�i�R��ځj
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	0F0h		;LCD_DATA�̏�ʂS�r�b�g��
	ANDWF	LCD_DATA,W		;���o���i�ύX���Ȃ��悤�Ɂj
	IORLW	02h		;�S�r�b�g���[�h
		;0010(4bit mode���߂̏�4bit)��RB0..3�ɑ��邽��
	MOVWF	LCD_DATA		;
	BSF	LCD_CTRL,LCD_EN		;�ݒ�
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	10
	call	Delay_100us
#endif	 ;++++++++++++++++++++++++++++++++++++++++

	movlw	1
	call	Delay_10ms	;Wait for more than 30ms

				;**** ����ȍ~��Lcd_busy���g����	

	call	Lcd_clear	;Clear LCD
	
	movlw	INC_CURSOR	;0x02
	call	Lcd_emode	;Set entry mode
				;�J�[�\���E�ړ��Ƃ���
	movlw	IFACE_4BIT	;4bit�ɌŒ肷�� 0x00
	iorlw	DUAL_LINE	;   0x08	==> 0x08
	call	Lcd_fmode	;Select Function Set
				;4bit mode, 2�s�\��, 7dot�Ƃ���	
	movlw	DISPLAY_ON
	iorlw	CURSOR_OFF
	call	Lcd_dmode	;Configure display mode
				;�\��on, cursor off�Ƃ���
	return
;*********************************************
;	Lcd_cmd
;	���߃f�[�^��Lcd�֑���
;		���߂�Wreg�ɓ���Ă���
;  �g����   movlw   _?lcd_temp =>_?lcd_temp��Wreg�ɓ���
;			call    Lcd_cmd
;*********************************************
Lcd_cmd:	
	movwf	_?lcd_temp			;���߂�ۑ�

	call	Lcd_busy	;Lcd��ready�ɂȂ�܂ł����ő҂�

#ifdef	PICPORT_UPPER		;Set data bus as output
	_?selbank1
	bcf		LCD_DATA_TRIS,4
	bcf		LCD_DATA_TRIS,5
	bcf		LCD_DATA_TRIS,6
	bcf		LCD_DATA_TRIS,7
	_?selbank0
#else
	_?selbank1
	bcf		LCD_DATA_TRIS,0
	bcf		LCD_DATA_TRIS,1
	bcf		LCD_DATA_TRIS,2
	bcf		LCD_DATA_TRIS,3
	_?selbank0
#endif

	_?selbank1
	bcf		LCD_CTRL_TRIS,LCD_RW	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_EN	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_RS	;Set control bus as output
	_?selbank0
	bcf	LCD_CTRL,LCD_RW		;�������݃��[�h�ɂ���
	bcf	LCD_CTRL,LCD_RS		;�R�}���h���[�h�ɂ���

#ifdef	PICPORT_UPPER
	call	Lcd_wr_upper_lower
#else
	call	Lcd_wr_lower_upper
#endif
	movlw	1
	call	Delay_100us
	return
;*********************************************
;	Lcd_dat
;	Wreg�ɓ����Ă���f�[�^��Lcd�֑���
;		�ꕶ������
;	8bit���㑤4bit�Ɖ���4bit�ɕ����đ���
;		�� => �� �̏�
; �g����	movlw   _?lcd_temp	=> _?lcd_temp��Wreg�ɓ���
;			call    Lcd_dat
;*********************************************
Lcd_dat:
	movwf	_?lcd_temp			;����ׂ��l��ۑ�����

	call	Lcd_busy	;Lcd��ready�ɂȂ�܂ł����ő҂�

#ifdef	PICPORT_UPPER		;Set data bus as output
	_?selbank1
	bcf		LCD_DATA_TRIS,4
	bcf		LCD_DATA_TRIS,5
	bcf		LCD_DATA_TRIS,6
	bcf		LCD_DATA_TRIS,7
	_?selbank0
#else
	_?selbank1
	bcf		LCD_DATA_TRIS,0
	bcf		LCD_DATA_TRIS,1
	bcf		LCD_DATA_TRIS,2
	bcf		LCD_DATA_TRIS,3
	_?selbank0
#endif

	_?selbank1
	bcf		LCD_CTRL_TRIS,LCD_RW	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_EN	;Set control bus as output
	bcf		LCD_CTRL_TRIS,LCD_RS	;Set control bus as output
	_?selbank0
	bcf	LCD_CTRL,LCD_RW		;�������݃��[�h�ɂ���
	bsf	LCD_CTRL,LCD_RS		;�f�[�^���[�h�Ƃ���

#ifdef	PICPORT_UPPER
	call	Lcd_wr_upper_lower
#else
	call	Lcd_wr_lower_upper
#endif
	return
;*********************************************
Lcd_wr_upper_lower:
	movlw	0x0f
	andwf	LCD_DATA,f	;�f�[�^�o�X�̏㑤���N����

	MOVF    _?lcd_temp,w ;���߂�Wreg�ɓ����
	ANDLW   0xF0            ;���4bit�Ƃ���
	iorwf	LCD_DATA,f	;PORT��upper�ɏo��(PORT��lower�͂��̂܂�)

	BSF     LCD_CTRL,LCD_EN ;LCD�Ƀf�[�^����������
	nop					;Enable�̍ŒZ����450ns
	nop
	BCF     LCD_CTRL,LCD_EN

	movlw	0x0f
	andwf	LCD_DATA,f	;�f�[�^�o�X�̏㑤���N����

	SWAPF   _?lcd_temp,w	;���߂�nibble�����ւ��AWreg�ɓ����
	ANDLW   0xF0        ;���߂̉���4bit��Wreg��upper�ɓ����Ă���
	iorwf	LCD_DATA,f	;PORT��upper�ɏo��(PORT��lower�͂��̂܂�)
	BSF     LCD_CTRL,LCD_EN ;LCD�Ƀf�[�^����������
	nop					;Enable�̍ŒZ����450ns
	nop
	BCF     LCD_CTRL,LCD_EN
	RETURN
;***********************************************
Lcd_wr_lower_upper:
	movlw	0xf0
	andwf	LCD_DATA,f	;�f�[�^�o�X�̉������N����

	SWAPF   _?lcd_temp,w	;���߂�nibble�����ւ��AWreg�ɓ����

	ANDLW   0x0f            ;����4bit�Ƃ���
	iorwf	LCD_DATA,f	;PORT��lower�ɏo��(PORT��upper�͂��̂܂�)
	BSF     LCD_CTRL,LCD_EN ;LCD�Ƀf�[�^����������
	nop					;Enable�̍ŒZ����450ns
	nop
	BCF     LCD_CTRL,LCD_EN

	movlw	0xf0
	andwf	LCD_DATA,f	;�f�[�^�o�X�̉������N����

	movf	_?lcd_temp,w	;���߂�Wreg�֓����
	ANDLW   0x0f            ; Get lower nibble
	iorwf	LCD_DATA,f	;PORT��lower�ɏo��(PORT��upper�͂��̂܂�)
	BSF     LCD_CTRL,LCD_EN ;LCD�Ƀf�[�^����������
	nop					;Enable�̍ŒZ����450ns
	nop
	BCF     LCD_CTRL,LCD_EN
	RETURN
;*********************************************
; * set_cmode - Configure cursor mode
; *
; * Options:
; *  SHIFT_DISP - Shift Display
; *  SHIFT_RIGHT - Move cursor right
; *  SHIFT_LEFT - Move cursor left
;*********************************************
Lcd_cmode:
	andlw	0x0c	;Ensure that only valid range of bits set
	iorwf	_?lcd_cmode,w
	iorlw	0x10	;Set command bit [cursor shift mode]
	movwf	_?lcd_cmode
	call	Lcd_cmd		;Send the command
	return
;*********************************************
; * set_dmode - Configure display mode
; *
; * Options:
; *  DISPLAY_ON - Turn Display on
; *  DISPLAY_OFF - Turn Display off
; *  CURSOR_ON  - Turn Cursor on
; *  BLINK_ON - Blink Cursor on
; *  BLINK_OFF - Blink Cursor off
;*********************************************
Lcd_dmode:
	andlw	0x07	;Ensure that only valid range of bits set
	iorwf	_?lcd_dmode,w
	iorlw	0x08	;Set command bit [display mode]
	movwf	_?lcd_dmode
	call	Lcd_cmd		;Send the command
	return
;*********************************************
; * set_emode - Set entry mode
; *
; * Options:
; *  INC_CURSOR - Incremnt cursor after character written
; *  DEC_CURSOR - Decrement cursor after character written
; *  SHIFT_ON - Switch Cursor shifting on
;*********************************************
Lcd_emode:
	andlw	0x03	;Ensure that only valid range of bits set
	iorwf	_?lcd_emode,w
	iorlw	0x04	;Set command bit [entry mode]
	movwf	_?lcd_emode
	call	Lcd_cmd		;Send the command
	return
;*********************************************
; * set_fmode - Configure function set
; *
; * Options:
; *  4BIT_IFACE - 4-bit interface
; *  8BIT_IFACE - 8-bit interface
; *  DUAL_LINE - 1/16 duty
; *  SNGL_LINE - 1/8 duty
; *  DOTS_5X10 - 5x10 dot characters
; *  DOTS_5X7 - 5x7 dot characters
;*********************************************
Lcd_fmode:
	andlw	0x1f	;Ensure that only valid range of bits set
	iorwf	_?lcd_fmode,w
	iorlw	0x20	;Set command bit [function mode]
	movwf	_?lcd_fmode
	call	Lcd_cmd		;Send the command
	return
;*********************************************
; * set_ddram - Set DDRAM address
; *
; * Options:
;		FIRST_LINE
;		SECONC_LINE
; *  address - 7-bit address
;*********************************************
Lcd_ddram:
	andlw	0x7f	;Ensure that only valid range of bits set
	iorlw	0x80	;Set command bit (Set DDRAM address)
	call	Lcd_cmd		;Send the command
	movlw	1
	call	Delay_100us
	return
;+++++++++++++++++++++++++++++++++++++++++++++++
