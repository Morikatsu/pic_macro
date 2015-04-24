; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2011/04/16 09:09:05.
;	MyUtility_abs.inc
	LIST
;*** MyUtility_abs.inc Ver 1.03i  堀野 守克	last change:2011/04/16 09:09:05.
	NOLIST
;***********************************************************
;	このマクロ群はPamscls.incと同時につかうことを前提としている
;	作業変数の場所はchip毎に自動で確保する  07/05/24
;	作業変数としてを _?temp0..7を使う。(予約変数とする)
;***********************************************************
;	使用できる bankは各chipにより異なる。
;	16F84.............. bank0, bank1
;	16F627A/628A/648A.. bank0, bank1, bank2, bank3
;	16F87/88...........   ibid
;	12F629/675......... bank0, bank1
;*********************************************************
#ifndef	_MYUTILITY_ABS_INC_INCLUDED
#define	_MYUTILITY_ABS_INC_INCLUDED
;*********************************************************
;	k(定数) + freg==>freg
;	注)	オーバーフローが起こったとき 未確認
;------------------------------------------------
_?addlf	macro	const, freg
	movf	freg,W	;freg==Wreg
	addlw	const	;Wreg+k==>Wreg
	movwf	freg	;Wreg==>freg
	endm
;*********************************************************
;	freg1 + freg2==>freg1|Wreg
;	注)	オーバーフローが起こったとき 未確認
;------------------------------------------------
_?addff1	macro	freg1,freg2,d
	movf	freg2,W
	addwf	freg1,d
	endm
;*********************************************************
;	freg1 + freg2==>freg2|Wreg
;	注)	オーバーフローが起こったとき 未確認
;------------------------------------------------
_?addff2	macro	freg1,freg2,d
	movf	freg1,W
	addwf	freg2,d
	endm
;*********************************************************
;	Wreg - k(定数) ==>Wreg
;	注)	アンダーフローが起こったとき 未確認
;------------------------------------------------
_?subwl	macro	k
	movwf	_?temp0		;W==>_?temp0
	movlw	k			;k==>Wreg
	_?swapwf _?temp0	;k==>_?temp0, W==>W
	subwf	_?temp0,W	;Wreg-k==>Wreg
	endm
;*********************************************************
;	freg - k(定数) ==>freg|Wreg  10/02/22訂正
;	注)	アンダーフローが起こったとき 未確認
;------------------------------------------------
_?subfl	macro	freg,k,d
	movlw	k		;k==>Wreg
	subwf	freg,d	;freg-k ==>freg|Wreg
	endm
;*********************************************************
;	k(定数) - freg==>freg
;	注)	アンダーフローが起こったとき 未確認
;------------------------------------------------
_?sublf	macro	k,freg
	movf	freg,w	;freg==>Wreg
	sublw	k		;k-Wreg ==>Wreg
	movwf	freg	;Wreg==>freg
	endm
;*********************************************************
;	freg1 - freg2==>freg1|Wreg
;	注)	アンダーフローが起こったとき 未確認
;------------------------------------------------
_?subff1	macro	freg1,freg2,d
	movf	freg2,W	;freg2==>Wreg
	subwf	freg1,d	;freg1-freg2==>freg1|Wreg
	endm
;*********************************************************
;	freg1 - freg2==>freg2
;	注)	アンダーフローが起こったとき 未確認
;------------------------------------------------
_?subff2	macro	freg1,freg2
	movf	freg2,W	;freg2==>Wreg
	subwf	freg1,W	;freg1-freg2==>Wreg
	movwf	freg2
	endm
;*********************************************************
;	fregのshift left(without carry)==>freg|Wreg
;------------------------------------------------
_?rlcf	macro	freg,d
	bcf		STATUS,C
	rlf		freg,d
	endm
;*********************************************************
;	fregのshift right(without carry)==>freg|Wreg
;------------------------------------------------
_?rrcf	macro	freg,d
	bcf		STATUS,C
	rrf		freg,d
	endm
;*********************************************************
;	freg1とfreg2の値の入れ替え by VK3BHR
;	Wregは破壊される  [5byte使う] 10/06/12
;------------------------------------------------
_?swapff	macro	freg1, freg2
	movf	freg1,w		; get this
	xorwf	freg2,f		; Swap using Microchip
	xorwf	freg2,w		; Tips'n Tricks
	xorwf	freg2,f		; #18
	movwf	freg1
	endm
;*********************************************************
;	freg1とfreg2の値の入れ替え
;	Wregは保持される  [9byte使う]
;------------------------------------------------
_?swapff2	macro	freg1, freg2
	_?swapwf	freg1
	_?swapwf	freg2
	_?swapwf	freg1
	endm
;*********************************************************
;	WとFregの値の入れ替え
;	Wregは保持される  [3byte使う]
;------------------------------------------------
_?swapwf	macro	freg
	xorwf	freg,F
	xorwf	freg,W
	xorwf	freg,F
	endm
;*********************************************************
;	freg1 --> freg2  [2byte使う]
;	arg1:freg1(variable), arg2:freg2(variable)
;		Wregは破壊される
;------------------------------------------------
_?movff		macro	freg1, freg2
	movf	freg1,W
	movwf	freg2
	endm
;*********************************************************
;	freg1 --> freg2  [4byte使う]
;	arg1:freg1(variable), arg2:freg2(variable)
;	Wregは保持される blog.nshdot.com/search/label/PIC
;------------------------------------------------
_?movff2	macro	freg1, freg2
	xorwf	freg1,w
	movwf	freg2
	xorwf	freg1,w
	xorwf	freg2,F
	endm
;*********************************************************
;	定数 -> freg  [2byte使う]
;	arg1:定数(constant), arg2:freg(variable)
;		Wregは破壊される
;------------------------------------------------
_?movlf	macro	const, reg
	movlw	const
	movwf	reg
	endm
;*********************************************************
;	定数 -> freg  [4byte使う]
;	arg1:定数(constant), arg2:freg(variable)
;	Wregは保持される blog.nshdot.com/search/label/PIC
;------------------------------------------------
_?movlf2	macro	const, reg
	xorlw	const
	movwf	reg
	xorlw	const
	xorwf	reg,F
	endm
;======================================================
;	比較[freg - 定数]	09/12/25 修正
;	結果  freg > 定数  Carry=1, Zero=0
;		  freg = 定数  Carry=1, Zero=1
;		  freg < 定数  Carry=0, Zero=0
;-----------------------------------
_?cpfl	macro freg, cnst	;compare freg with data
	movlw	cnst
	subwf	freg, W
	endm
;======================================================
;	比較[freg - Wreg]	09/12/25 修正
;	結果  freg > Wreg  Carry=1, Zero=0
;		  freg = Wreg  Carry=1, Zero=1
;		  freg < Wreg  Carry=0, Zero=0
;-----------------------------------
_?cpfw	macro freg			;compare freg with Wreg
	subwf	freg, W
	endm
;======================================================
;	比較[freg1 - freg2]	09/12/25 修正
;	結果  freg1 > freg2  Carry=1, Zero=0
;		  freg1 = freg2  Carry=1, Zero=1
;		  freg1 < freg2  Carry=0, Zero=0
;-----------------------------------
_?cpff	macro freg1, freg2	;compare freg1 with greg2
	movf	freg2, W
	subwf	freg1, W
	endm
;*********************************************************
;	2byteの変数の加算  (AH,AL) + (BH,BL) ==> (AH,AL)
;	00/05/16
;	AH,AL,BH,BLは主プログラムで宣言しておく
;	注)	オーバーフローが起こったとき 未確認
;------------------------------------------------
_?add2byte	macro	ah,bl,bh,bl
	movf	bl,w
	addwf	al,f
	movf	bh,w
	btfsc	STATUS,C
	incfsz	bh,w
	addwf	ah,f
	endm
;*********************************************************
;	2byteの変数の減算  (AH,AL) - (BH,BL) ==> (AH,AL)
;	2011/04/14 に修正　但し、未確認
;	AH,AL,BH,BLは主プログラムで宣言しておく
;	注)	アンダーフローが起こったとき 未確認
;------------------------------------------------
_?sub2byte	macro	ah,al,bh,bl

	comf	bl,F	;(bh,bl)の補数をつくる。
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
;	2byteの変数のインクリメント   (AH,AL)+1 ==>(AH,AL)
;	00/05/16
;	AH,ALは主プログラムで宣言しておく	
;	注)	オーバーフローが起こったとき 未確認
;------------------------------------------------
_?inc2byte	macro	ah,al
	incfsz	al,f
	goto	$+2
	incf	ah,f
	endm
;*********************************************************
;	2byteの変数のデクリメント   (AH,AL)-1 ==>(AH,AL)
;	00/05/16
;	AH,ALは主プログラムで宣言しておく	
;	注)	オーバーフローが起こったとき 未確認
;------------------------------------------------
_?dec2byte	macro	ah,al
	decfsz	al,f
	incfsz	al,w
	goto	$+2
	decf	ah,f
	endm
;*********************************************************
;	www.piclist.com/techref/cpus.html
;----------------------------------------------------
;	使い方 : _?WindowTest value, min, max.
;	Carry is set if value is within min-max (wtpass),
;	and cleared if not (wtfail). 
;	範囲内であればcarry set, 範囲外であればcarry clear
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
	bnc	k		;演算結果が負であると kへ飛ぶ
	endm		;	minus
;======================================================
bnneg	macro	k	;Branch on non-negative
	bc	k		;演算結果が非負であると kへ飛ぶ
	endm		;	zero|plus
;======================================================
bpls	macro	k	;Branch on plus
	skpnpls		;演算結果が正であると kへ飛ぶ
	goto	k	;	plus
	endm
;======================================================
bnpls	macro	k	;Branch on non-plus
	skppls		;演算結果が非正であると kへ飛ぶ
	goto	k	;	zero|minus
	endm
;======================================================
skpneg	macro	;Skip on negative
	btfsc	STATUS,C	;演算結果が負であるとスキップ 
	endm		;	minus
;======================================================
skpnneg	macro	;Skip on non-negative
	btfss	STATUS,C	;演算結果が非負であるとスキップ 
	endm		;	zero|plus
;======================================================
skppls	macro	;Skip on plus
	btfss	STATUS,C;演算結果が正|zeroであるとスキップ 
	goto	$+2	;	minus
	btfsc	STATUS,Z;non zero(plus)であるとskip
	endm		;minus
;======================================================
skpnpls	macro	;Skip on non-plus	09/09/07
	btfsc	STATUS,C;演算結果が正|zeroであるとスキップ 
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
;	CLR Memory:   MEM,COUNT		10/05/29
;	MEMをクリヤする	以下はcount=4の場合
;		clrf	mem
;		clrf	mem+1
;		clrf	mem+2
;		clrf	mem+3
;------------------------------------------------
_?clrfn	MACRO MEM, count
	local index = 0
	WHILE index < count
	clrf	MEM+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
;	MOVE Memory FROM,TO,COUNT	10/05/27
;	FROMをTOへ複写する	以下はcount=4の場合
;		FROM   => TO
;		FROM+1 => TO+1
;		FROM+2 => TO+2
;		FROM+3 => TO+3
;------------------------------------------------
_?movffn	MACRO FROM, TO, count
	local index = 0
	WHILE index < count
	_?movff	FROM+index, TO+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
;	SWAP Memory FROM,TO,COUNT	10/05/27
;	FROMとTOを入れ替える  以下はcount=4の場合
;		FROM   <=> TO
;		FROM+1 <=> TO+1
;		FROM+2 <=> TO+2
;		FROM+3 <=> TO+3
;------------------------------------------------
_?swapffn	MACRO FROM, TO, count
	local index = 0
	WHILE index < count
	_?swapff FROM+index, TO+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
_?selbank0	macro				;bank 0 select
	ifdef	__16F84
			bcf		STATUS, RP0
	endif
	ifdef	__16F84A
			bcf		STATUS, RP0
	endif
	ifdef	__12F629
			bcf		STATUS, RP0
	endif
	ifdef	__12F675
			bcf		STATUS, RP0
	endif
	ifdef	__16F627A
			bcf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F628A
			bcf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F648A
			bcf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F683			;10/04/02
			bcf		STATUS, RP0
			bcf		STATUS, RP1
	endif

	ifdef	__16F87
			bcf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F88
			bcf		STATUS, RP0
			bcf		STATUS, RP1
	endif
			endm
;-----------------------------------
_?selbank1	macro				;bank 1 select
	ifdef	__16F84
			bsf		STATUS, RP0
	endif
	ifdef	__16F84A
			bsf		STATUS, RP0
	endif
	ifdef	__12F629
			bsf		STATUS, RP0
	endif
	ifdef	__12F675
			bsf		STATUS, RP0
	endif
	ifdef	__16F627A
			bsf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F628A
			bsf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F648A
			bsf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F683			;10/04/02
			bsf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F87
			bsf		STATUS, RP0
			bcf		STATUS, RP1
	endif
	ifdef	__16F88
			bsf		STATUS, RP0
			bcf		STATUS, RP1
	endif
			endm
;-----------------------------------
_?selbank2	macro				;bank 2 select
	ifdef	__16F627A
			bcf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F628A
			bcf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F648A
			bcf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F87
			bcf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F88
			bcf		STATUS, RP0
			bsf		STATUS, RP1
	endif
			endm
;-----------------------------------
_?selbank3	macro				;bank 3 select
	ifdef	__16F627A
			bsf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F628A
			bsf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F648A
			bsf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F87
			bsf		STATUS, RP0
			bsf		STATUS, RP1
	endif
	ifdef	__16F88
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
;	このマクロはページ(2k byte)を超えてcallした後、元の
;	pageに戻る
fcall	macro subroutine_name
	local here
	lcall subroutine_name
	pagesel here
here:
	endm
;++++++++++++++++++++++++++++++++++++++++++
;	このマクロはpage0からpage1へ、
;	あるいはpage0からpage1へ移動するものである。
;		lcallと対で使うと、page間の移動を意識しないで済む。
;
_?setpch	macro
			if	( $ >= 0 ) && ( $ < H'800' )
				bcf		PCLATH, 3
			else
				bsf		PCLATH, 3
			endif
			endm
;********* EOF : MyUtility.inc *************************
#endif		;_MYUTILITY_ABS_INC_INCLUDED
