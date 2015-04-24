; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2012/06/19 14:32:40.
	LIST
;*** MyUtility_abs.inc Ver 1.03k  �x��獎 last change:2012/06/19 14:32:40.
	NOLIST
;***********************************************************
;	���̃}�N���Q��absolute�p�ł���
;	���̃}�N���Q��Pamscls_abs.inc�Ɠ����ɂ������Ƃ�O��Ƃ��Ă���
;		[Pamscls_abs.inc�̏I����include�����]
;	��ƕϐ��̏ꏊ��chip���Ɏ����Ŋm�ۂ���  07/05/24
;	��ƕϐ��Ƃ��Ă� _?temp0..7���g���B(�\��ϐ��Ƃ���)
;	��ƕϐ���Pamscls_abs_variable.inc�ōs���B
;***********************************************************
;	�g�p�ł��� bank�͊echip�ɂ��قȂ�B
;	16F84/84A.......... bank0, bank1
;	12F683.............	  ibid
;	12F629/675.........	  ibid 
;	16F627A/628A/648A.. bank0, bank1, bank2, bank3
;	16F87/88...........   ibid
;*********************************************************
#ifndef	_MYUTILITY_ABS_INC_INCLUDED
#define	_MYUTILITY_ABS_INC_INCLUDED
;*********************************************************
;	k(�萔) + freg==>freg		[?byte�g��] 10/06/12
;	��)	�I�[�o�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  
;------------------------------------------------
_?addlf	macro	const, freg
	banksel	freg
	movf	freg,W	;freg==Wreg
	addlw	const	;Wreg+k==>Wreg
	movwf	freg	;Wreg==>freg
	endm
;*********************************************************
;	freg1 + freg2==>freg1|Wreg		[?byte�g��] 10/06/12
;	��)	�I�[�o�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  freg2�͕s��
;------------------------------------------------
_?addff1	macro	freg1,freg2,d
	banksel	freg2
	movf	freg2,W		;freg2==>Wreg
	banksel	freg1
	addwf	freg1,d		;Wreg+freg1==>d
	endm
;*********************************************************
;	freg1 + freg2==>freg2|Wreg		[?byte�g��] 10/06/12
;	��)	�I�[�o�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  freg1�͕s��
;------------------------------------------------
_?addff2	macro	freg1,freg2,d
	banksel	freg1
	movf	freg1,W		;freg1==>Wreg
	banksel	freg2
	addwf	freg2,d		;Wreg+freg2==>d
	endm
;*********************************************************
;	Wreg - k(�萔) ==>Wreg		[?byte�g��] 10/06/12
;	��)	�A���_�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  
;------------------------------------------------
_?subwl	macro	k
	movwf	_?temp0		;W==>_?temp0
	movlw	k			;k==>Wreg
	_?swapwf _?temp0	;k==>_?temp0, W==>W
	subwf	_?temp0,W	;Wreg-k==>Wreg
	endm
;*********************************************************
;	freg - k(�萔) ==>freg|Wreg  [?byte�g��] 10/06/12�@10/02/22����
;	��)	�A���_�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  
;------------------------------------------------
_?subfl	macro	freg,k,d
	movlw	k		;k==>Wreg
	banksel	freg
	subwf	freg,d	;freg-k ==>freg|Wreg
	endm
;*********************************************************
;	k(�萔) - freg==>freg		[?byte�g��] 10/06/12
;	��)	�A���_�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  
;------------------------------------------------
_?sublf	macro	k,freg
	banksel	freg
	movf	freg,w	;freg==>Wreg
	sublw	k		;k-Wreg ==>Wreg
	movwf	freg	;Wreg==>freg
	endm
;*********************************************************
;	freg1 - freg2==>freg1|Wreg		[?byte�g��] 10/06/12
;	��)	�A���_�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂�� freg2�͕s��, freg1��d�ɂ�� 
;------------------------------------------------
_?subff1	macro	freg1,freg2,d
	banksel	freg2
	movf	freg2,W	;freg2==>Wreg
	banksel	freg1
	subwf	freg1,d	;freg1-freg2==>freg1|Wreg
	endm
;*********************************************************
;	freg1 - freg2==>freg2		[?byte�g��] 10/06/12
;	��)	�A���_�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  freg1�͕s��
;------------------------------------------------
_?subff2	macro	freg1,freg2
	banksel	freg2
	movf	freg2,W	;freg2==>Wreg
	banksel	freg1
	subwf	freg1,W	;freg1-freg2==>Wreg
	banksel	freg2
	movwf	freg2
	endm
;*********************************************************
;	freg��shift left(without carry)==>freg|Wreg
;	lsb�ɂ�0, Carry �t���O�ɂ�msb������
;------------------------------------------------
_?rlcf	macro	freg,d
	bcf		STATUS,C
	banksel	freg
	rlf		freg,d
	endm
;*********************************************************
;	freg��shift right(without carry)==>freg|Wreg
;	msb�ɂ�0, Carry �t���O�ɂ�lsb������
;------------------------------------------------
_?rrcf	macro	freg,d
	bcf		STATUS,C
	banksel	freg
	rrf		freg,d
	endm
;*********************************************************
;	freg1��freg2�̒l�̓���ւ� by VK3BHR
;	Wreg�͔j�󂳂��  [5byte�g��] 10/06/12
;------------------------------------------------
_?swapff	macro	freg1, freg2
	banksel	freg1
	movf	freg1,w		; get this
	banksel	freg2
	xorwf	freg2,f		; Swap using Microchip
	xorwf	freg2,w		; Tips'n Tricks
	xorwf	freg2,f		; #18
	banksel	freg1
	movwf	freg1
	endm
;*********************************************************
;	freg1��freg2�̒l�̓���ւ�
;	Wreg�͕ێ������  [9byte�g��]
;------------------------------------------------
_?swapff2	macro	freg1, freg2
	banksel	freg1
	_?swapwf	freg1
	banksel	freg2
	_?swapwf	freg2
	banksel	freg1
	_?swapwf	freg1
	endm
;*********************************************************
;	W��Freg�̒l�̓���ւ�
;	Wreg�͕ێ������  [3byte�g��]
;------------------------------------------------
_?swapwf	macro	freg
	banksel	freg
	xorwf	freg,F
	xorwf	freg,W
	xorwf	freg,F
	endm
;*********************************************************
;	freg1 --> freg2  [2byte�g��]
;	arg1:freg1(variable), arg2:freg2(variable)
;	Wreg�͔j�󂳂��	freg1�͕s��
;------------------------------------------------
_?movff		macro	freg1, freg2
	banksel	freg1
	movf	freg1,W
	banksel	freg2
	movwf	freg2
	endm
;*********************************************************
;	freg1 --> freg2  [4byte�g��]
;	arg1:freg1(variable), arg2:freg2(variable)
;	Wreg�͕ێ������ blog.nshdot.com/search/label/PIC
;------------------------------------------------
_?movff2	macro	freg1, freg2
	banksel	freg1
	xorwf	freg1,w
	banksel	freg2
	movwf	freg2
	banksel	freg1
	xorwf	freg1,w
	banksel	freg2
	xorwf	freg2,F
	endm
;*********************************************************
;	�萔 -> freg  [2byte�g��]
;	arg1:�萔(constant), arg2:freg(variable)
;	Wreg�͔j�󂳂��
;------------------------------------------------
_?movlf	macro	const, reg
	movlw	const	;const==>Wreg
	banksel	reg			; 2010/07/09 
	movwf	reg		;Wreg==>reg
	endm
;*********************************************************
;	�萔 -> freg  [4byte�g��]
;	arg1:�萔(constant), arg2:freg(variable)
;	Wreg�͕ێ������ blog.nshdot.com/search/label/PIC
;------------------------------------------------
_?movlf2	macro	const, reg
	xorlw	const
	banksel	reg
	movwf	reg
	xorlw	const
	xorwf	reg,F
	endm
;======================================================
;	CLR Memory:   MEM,COUNT		2010/07/02 
;	MEM���N��������	�ȉ���count=4�̏ꍇ
;		clrf	mem
;		clrf	mem+1
;		clrf	mem+2
;		clrf	mem+3
;------------------------------------------------
_?clrfn	MACRO MEM, count
	local index = 0
		banksel	MEM
	WHILE index < count
		clrf	MEM+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
;	MOVE Memory FROM,TO,COUNT	2010/07/02 
;	FROM��TO�֕��ʂ���	�ȉ���count=4�̏ꍇ
;		FROM   => TO
;		FROM+1 => TO+1
;		FROM+2 => TO+2
;		FROM+3 => TO+3
;------------------------------------------------
_?movffn	MACRO FROM, TO, count
	local index = 0
	WHILE index < count
		banksel	FROM
		movfw	FROM+index
		banksel	TO
		movwf	TO+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
;	SWAP Memory FROM,TO,COUNT	10/05/27
;	FROM��TO�����ւ���  �ȉ���count=4�̏ꍇ
;		FROM   <=> TO
;		FROM+1 <=> TO+1
;		FROM+2 <=> TO+2
;		FROM+3 <=> TO+3
;	Wreg�͕ێ������  [?byte�g��]
;------------------------------------------------
_?swapffn	MACRO FROM, TO, count
	local index = 0
	WHILE index < count
	_?swapff FROM+index, TO+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
;	��r[freg - �萔]	[?byte�g��] 10/06/12�@09/12/25 �C��
;	����  freg > �萔  Carry=1, Zero=0
;		  freg = �萔  Carry=1, Zero=1
;		  freg < �萔  Carry=0, Zero=0
;	Wreg�͔j�󂳂��  freg�͕s��
;-----------------------------------
_?cpfl	macro freg, cnst	;compare freg with data
	movlw	cnst		;cnst==>Wreg
	banksel	freg
	subwf	freg, W		;freg-Wreg==>Wreg
	endm
;======================================================
;	��r[freg - Wreg]	[?byte�g��] 10/06/12�@09/12/25 �C��
;	����  freg > Wreg  Carry=1, Zero=0
;		  freg = Wreg  Carry=1, Zero=1
;		  freg < Wreg  Carry=0, Zero=0
;	Wreg�͔j�󂳂��  freg�͕s��
;-----------------------------------
_?cpfw	macro freg			;compare freg with Wreg
	banksel	freg
	subwf	freg, W		;freg-Wreg==>Wreg
	endm
;======================================================
;	��r[freg1 - freg2]	[?byte�g��] 10/06/12 09/12/25 �C��
;	����  freg1 > freg2  Carry=1, Zero=0
;		  freg1 = freg2  Carry=1, Zero=1
;		  freg1 < freg2  Carry=0, Zero=0
;	Wreg�͔j�󂳂��  freg1,freg2�͂Ƃ��ɕs��
;-----------------------------------
_?cpff	macro freg1, freg2	;compare freg1 with greg2
	banksel	freg2
	movf	freg2, W	;freg2==>Wreg
	banksel	freg1
	subwf	freg1, W	;freg1-Wreg==>Wreg
	endm
;*********************************************************
;	2byte�̕ϐ��̉��Z  (AH,AL) + (BH,BL) ==> (AH,AL)
;	00/05/16
;	AH,AL,BH,BL�͎�v���O�����Ő錾���Ă���
;	��)	�I�[�o�[�t���[���N�������Ƃ� ���m�F
;	Wreg�͔j�󂳂��  [?byte�g��] 10/06/12
;------------------------------------------------
_?add2byte	macro	ah,bl,bh,bl
	movf	bl,w		;bl==>Wreg
	addwf	al,f		;Wreg+al==>al
	movf	bh,w		;bh==>Wreg
	btfsc	STATUS,C	
	incfsz	bh,w
	addwf	ah,f
	endm
;*********************************************************
;	2byte�̕ϐ��̌��Z  (AH,AL) - (BH,BL) ==> (AH,AL)
;	2011/04/14 �ɏC���@�A���A���m�F
;	AH,AL,BH,BL�͎�v���O�����Ő錾���Ă���
;	��)	�A���_�[�t���[���N�������Ƃ� ���m�F
;------------------------------------------------
_?sub2byte	macro	ah,al,bh,bl

	comf	bl,F	;(bh,bl)�̕␔������B
	incf	bl,F
	btfsc	STATUS,Z
	decf	bh,F
	comf	bh,F

	movf	bl,W
	addwf	al,F
	btfsc	STATUS,C
	incf	ah,F
	movf	bl,W
	addwf	al,F

	endm
;*********************************************************
;	2byte�̕ϐ��̃C���N�������g   (AH,AL)+1 ==>(AH,AL)
;	00/05/16
;	AH,AL�͎�v���O�����Ő錾���Ă���	
;	��)	�I�[�o�[�t���[���N�������Ƃ� ���m�F
;------------------------------------------------
_?inc2byte	macro	ah,al
	incfsz	al,f
	goto	$+2
	incf	ah,f
	endm
;*********************************************************
;	2byte�̕ϐ��̃f�N�������g   (AH,AL)-1 ==>(AH,AL)
;	00/05/16
;	AH,AL�͎�v���O�����Ő錾���Ă���	
;	��)	�I�[�o�[�t���[���N�������Ƃ� ���m�F
;------------------------------------------------
_?dec2byte	macro	ah,al
	decfsz	al,f
	incfsz	al,w
	goto	$+2
	decf	ah,f
	endm
;*********************************************************
;	���W�X�^�̑ޔ�		2012/06/19 
;	 Ҳ�ٰ�݂Ɗ��荞��ٰ�݂̗����Ŏg�p���Ă���ڼ޽���ޔ�������
;	�ϐ� w_temp, status_temp, fsr_temp, pclath_temp�͎僋�[�`��
;	�ɂĊm�ۂ��邱��
;------------------------------------------------
_?push    macro
        movwf   w_temp                  ; Ҳ�ٰ�݂Ɗ��荞��ٰ�݂̗�����
        swapf   STATUS,W                ; �g�p���Ă���ڼ޽���ޔ�������
        bcf     STATUS,RP0              ; 
        movwf   status_temp             ; w_temp      <- W
        movf    FSR,W                   ; status_temp <- STATUS
        movwf   fsr_temp                ; fsr_temp    <- FSR
        movf    PCLATH,W                ; pclath_temp <- PCLATH
        movwf   pclath_temp             ; 
        clrf    PCLATH                  ; 
        endm
;*********************************************************
;	���W�X�^�̕���		2012/06/19 
;	 Ҳ�ٰ�݂Ɗ��荞��ٰ�݂̗����Ŏg�p���Ă���ڼ޽��𕜌�������
;	�ϐ� w_temp, status_temp, fsr_temp, pclath_temp�͎僋�[�`��
;	�ɂĊm�ۂ��邱��
;------------------------------------------------
_?pop     macro
        movf    pclath_temp,W           ; push�őޔ�������ڼ޽��̕���
        movwf   PCLATH                  ;
        movf    fsr_temp,W              ;
        movwf   FSR                     ; W      <- w_temp
        swapf   status_temp,W           ; STATUS <- status_temp
        movwf   STATUS                  ; FSR    <- fsr_temp
        swapf   w_temp,F                ; PCLATH <- pclath_temp
        swapf   w_temp,W                ;
        endm
;*********************************************************
;	www.piclist.com/techref/cpus.html
;----------------------------------------------------
;	�g���� : _?WindowTest value, min, max.
;	Carry is set if value is within min-max (wtpass),
;	and cleared if not (wtfail). 
;	�͈͓��ł����carry set, �͈͊O�ł����carry clear
;	The key to this is the subwf instruction.
;	With subwf, the destination=f-w and
; carry =1 if destination=>0 (carry=1 is positive result). So, 
;	carry=1 if f=>w
;	carry=0 if f<w or w>f
;++++++++++++++++++++++++++++++++++++++++++++++++++++
_?WindowTest macro value, min, max
  local wtexit		; local labels in macro
					; For min, we want value=>min, so we'll put value in f and min in w
 	movfw	min			; Get minimum
	subwf	value,w		; w=f-w , w=value-min. Result positive (carry set) if value=>min
	bnc		wtexit		; If no carry, we're below min. Exit with fail (carry clear)
					; For max, we want max=>value, so we'll put max in f, value in w
	movfw	value		; Get current value in w
	subwf	max,w		; w=f-w = max-value. Result positive (carry set) if max=>value.
						; Exit with carry set
wtexit	
	endm
;======================================================
bneg	macro	k	;Branch on negative
	bnc	k		;���Z���ʂ����ł���� k�֔��
	endm		;	minus
;======================================================
bnneg	macro	k	;Branch on non-negative
	bc	k		;���Z���ʂ��񕉂ł���� k�֔��
	endm		;	zero|plus
;======================================================
bpls	macro	k	;Branch on plus
	skpnpls		;���Z���ʂ����ł���� k�֔��
	goto	k	;	plus
	endm
;======================================================
bnpls	macro	k	;Branch on non-plus
	skppls		;���Z���ʂ��񐳂ł���� k�֔��
	goto	k	;	zero|minus
	endm
;======================================================
skpneg	macro	;Skip on negative
	btfsc	STATUS,C	;���Z���ʂ����ł���ƃX�L�b�v 
	endm		;	minus
;======================================================
skpnneg	macro	;Skip on non-negative
	btfss	STATUS,C	;���Z���ʂ��񕉂ł���ƃX�L�b�v 
	endm		;	zero|plus
;======================================================
skppls	macro	;Skip on plus
	btfss	STATUS,C;���Z���ʂ���|zero�ł���ƃX�L�b�v 
	goto	$+2	;	minus
	btfsc	STATUS,Z;non zero(plus)�ł����skip
	endm		;minus
;======================================================
skpnpls	macro	;Skip on non-plus	09/09/07
	btfsc	STATUS,C;���Z���ʂ���|zero�ł���ƃX�L�b�v 
	btfsc	STATUS,Z
	goto	$+2	;
	endm
;======================================================
skip_bset	macro	memo, bit	;Skip Bit Set 10/05/27 
	btfss	memo,bit;
	endm
;======================================================
skip_bclr	macro	memo, bit	;Skip Bit Clear 10/05/27 
	btfsc	memo,bit;
	endm
;======================================================
_?selbank0	macro				;bank 0 select
	ifdef	(__16F84)||(__16F84A)||(__12F629)||(__12F675)||(__12F683)
		bcf		STATUS, RP0
	endif
	ifdef	(__16F627A)||(__16F628A)||(__16F648A)||(__16F87)||(__16F88)
		bcf		STATUS, RP0
		bcf		STATUS, RP1
	endif
			endm
;-----------------------------------
_?selbank1	macro				;bank 1 select
	ifdef	(__16F84)||(__16F84A)||(__12F629)||(__12F675)||(__12F683)
		bsf		STATUS, RP0
	endif
	ifdef	(__16F627A)||(__16F628A)||(__16F648A)||(__16F87)||(__16F88)
		bsf		STATUS, RP0
		bcf		STATUS, RP1
	endif
			endm
;-----------------------------------
_?selbank2	macro				;bank 2 select
	ifdef	(__16F627A)||(__16F628A)||(__16F648A)||(__16F87)||(__16F88)
		bcf		STATUS, RP0
		bsf		STATUS, RP1
	endif
			endm
;-----------------------------------
_?selbank3	macro				;bank 3 select
	ifdef	(__16F627A)||(__16F628A)||(__16F648A)||(__16F87)||(__16F88)
		bsf		STATUS, RP0
		bsf		STATUS, RP1
	endif
			endm
;======================================================
_?djnz		macro freg, entry	;decrement jump if not zero
		decfsz	freg,F
		goto entry
			endm
;======================================================
;	���̃}�N���̓y�[�W(2k byte)�𒴂���call������A����
;	page�ɖ߂�
;--------------------------------------------
fcall	macro subroutine_name
	local here
	lcall subroutine_name
	pagesel here
here:
	endm
;======================================================
;	���̃}�N����page0����page1�ցA
;	���邢��page0����page1�ֈړ�������̂ł���B
;		lcall�Ƒ΂Ŏg���ƁApage�Ԃ̈ړ����ӎ����Ȃ��ōςށB
;	2page�܂�(page0,page1) �������T�C�Y4K �܂ł�PIC��\�肵�Ă���
;--------------------------------------------
_?setpch	macro
			if	( $ >= 0 ) && ( $ < H'800' )
				bcf		PCLATH, 3
			else
				bsf		PCLATH, 3
			endif
			endm
;++++++++++++++++++++++++++++++++++++++++++
;XGOTO MACRO label
;  if label & 0x800
;	bsf     PCLATH, 3
;  else
;	bcf     PCLATH, 3
;  endif
;	goto    label
;  ENDM
;;++++++++++++++++++++++++++++++++++++++++++
;XCALL MACRO label
;	LOCAL   testlabel
;testlabel:
;  if label & 0x800
;	bsf     PCLATH, 3
;  else
;	bcf     PCLATH, 3
;  endif
;	call    label
;  if testlabel & 0x800
;	bsf     PCLATH, 3
;  else
;	bcf     PCLATH, 3
;  endif
;	ENDM
;********* EOF : MyUtility.inc *************************
#endif		;_MYUTILITY_ABS_INC_INCLUDED