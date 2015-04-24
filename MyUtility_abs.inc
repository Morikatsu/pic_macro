; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2012/06/19 14:32:40.
	LIST
;*** MyUtility_abs.inc Ver 1.03k  堀野守克 last change:2012/06/19 14:32:40.
	NOLIST
;***********************************************************
;	このマクロ群はabsolute用である
;	このマクロ群はPamscls_abs.incと同時につかうことを前提としている
;		[Pamscls_abs.incの終わりでincludeされる]
;	作業変数の場所はchip毎に自動で確保する  07/05/24
;	作業変数としてを _?temp0..7を使う。(予約変数とする)
;	作業変数はPamscls_abs_variable.incで行う。
;***********************************************************
;	使用できる bankは各chipにより異なる。
;	16F84/84A.......... bank0, bank1
;	12F683.............	  ibid
;	12F629/675.........	  ibid 
;	16F627A/628A/648A.. bank0, bank1, bank2, bank3
;	16F87/88...........   ibid
;*********************************************************
#ifndef	_MYUTILITY_ABS_INC_INCLUDED
#define	_MYUTILITY_ABS_INC_INCLUDED
;*********************************************************
;	k(定数) + freg==>freg		[?byte使う] 10/06/12
;	注)	オーバーフローが起こったとき 未確認
;	Wregは破壊される  
;------------------------------------------------
_?addlf	macro	const, freg
	banksel	freg
	movf	freg,W	;freg==Wreg
	addlw	const	;Wreg+k==>Wreg
	movwf	freg	;Wreg==>freg
	endm
;*********************************************************
;	freg1 + freg2==>freg1|Wreg		[?byte使う] 10/06/12
;	注)	オーバーフローが起こったとき 未確認
;	Wregは破壊される  freg2は不変
;------------------------------------------------
_?addff1	macro	freg1,freg2,d
	banksel	freg2
	movf	freg2,W		;freg2==>Wreg
	banksel	freg1
	addwf	freg1,d		;Wreg+freg1==>d
	endm
;*********************************************************
;	freg1 + freg2==>freg2|Wreg		[?byte使う] 10/06/12
;	注)	オーバーフローが起こったとき 未確認
;	Wregは破壊される  freg1は不変
;------------------------------------------------
_?addff2	macro	freg1,freg2,d
	banksel	freg1
	movf	freg1,W		;freg1==>Wreg
	banksel	freg2
	addwf	freg2,d		;Wreg+freg2==>d
	endm
;*********************************************************
;	Wreg - k(定数) ==>Wreg		[?byte使う] 10/06/12
;	注)	アンダーフローが起こったとき 未確認
;	Wregは破壊される  
;------------------------------------------------
_?subwl	macro	k
	movwf	_?temp0		;W==>_?temp0
	movlw	k			;k==>Wreg
	_?swapwf _?temp0	;k==>_?temp0, W==>W
	subwf	_?temp0,W	;Wreg-k==>Wreg
	endm
;*********************************************************
;	freg - k(定数) ==>freg|Wreg  [?byte使う] 10/06/12　10/02/22訂正
;	注)	アンダーフローが起こったとき 未確認
;	Wregは破壊される  
;------------------------------------------------
_?subfl	macro	freg,k,d
	movlw	k		;k==>Wreg
	banksel	freg
	subwf	freg,d	;freg-k ==>freg|Wreg
	endm
;*********************************************************
;	k(定数) - freg==>freg		[?byte使う] 10/06/12
;	注)	アンダーフローが起こったとき 未確認
;	Wregは破壊される  
;------------------------------------------------
_?sublf	macro	k,freg
	banksel	freg
	movf	freg,w	;freg==>Wreg
	sublw	k		;k-Wreg ==>Wreg
	movwf	freg	;Wreg==>freg
	endm
;*********************************************************
;	freg1 - freg2==>freg1|Wreg		[?byte使う] 10/06/12
;	注)	アンダーフローが起こったとき 未確認
;	Wregは破壊される freg2は不変, freg1はdによる 
;------------------------------------------------
_?subff1	macro	freg1,freg2,d
	banksel	freg2
	movf	freg2,W	;freg2==>Wreg
	banksel	freg1
	subwf	freg1,d	;freg1-freg2==>freg1|Wreg
	endm
;*********************************************************
;	freg1 - freg2==>freg2		[?byte使う] 10/06/12
;	注)	アンダーフローが起こったとき 未確認
;	Wregは破壊される  freg1は不変
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
;	fregのshift left(without carry)==>freg|Wreg
;	lsbには0, Carry フラグにはmsbが入る
;------------------------------------------------
_?rlcf	macro	freg,d
	bcf		STATUS,C
	banksel	freg
	rlf		freg,d
	endm
;*********************************************************
;	fregのshift right(without carry)==>freg|Wreg
;	msbには0, Carry フラグにはlsbが入る
;------------------------------------------------
_?rrcf	macro	freg,d
	bcf		STATUS,C
	banksel	freg
	rrf		freg,d
	endm
;*********************************************************
;	freg1とfreg2の値の入れ替え by VK3BHR
;	Wregは破壊される  [5byte使う] 10/06/12
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
;	freg1とfreg2の値の入れ替え
;	Wregは保持される  [9byte使う]
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
;	WとFregの値の入れ替え
;	Wregは保持される  [3byte使う]
;------------------------------------------------
_?swapwf	macro	freg
	banksel	freg
	xorwf	freg,F
	xorwf	freg,W
	xorwf	freg,F
	endm
;*********************************************************
;	freg1 --> freg2  [2byte使う]
;	arg1:freg1(variable), arg2:freg2(variable)
;	Wregは破壊される	freg1は不変
;------------------------------------------------
_?movff		macro	freg1, freg2
	banksel	freg1
	movf	freg1,W
	banksel	freg2
	movwf	freg2
	endm
;*********************************************************
;	freg1 --> freg2  [4byte使う]
;	arg1:freg1(variable), arg2:freg2(variable)
;	Wregは保持される blog.nshdot.com/search/label/PIC
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
;	定数 -> freg  [2byte使う]
;	arg1:定数(constant), arg2:freg(variable)
;	Wregは破壊される
;------------------------------------------------
_?movlf	macro	const, reg
	movlw	const	;const==>Wreg
	banksel	reg			; 2010/07/09 
	movwf	reg		;Wreg==>reg
	endm
;*********************************************************
;	定数 -> freg  [4byte使う]
;	arg1:定数(constant), arg2:freg(variable)
;	Wregは保持される blog.nshdot.com/search/label/PIC
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
;	MEMをクリヤする	以下はcount=4の場合
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
;	FROMをTOへ複写する	以下はcount=4の場合
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
;	FROMとTOを入れ替える  以下はcount=4の場合
;		FROM   <=> TO
;		FROM+1 <=> TO+1
;		FROM+2 <=> TO+2
;		FROM+3 <=> TO+3
;	Wregは保持される  [?byte使う]
;------------------------------------------------
_?swapffn	MACRO FROM, TO, count
	local index = 0
	WHILE index < count
	_?swapff FROM+index, TO+index
index	= index + 1 
	ENDW
	ENDM
;======================================================
;	比較[freg - 定数]	[?byte使う] 10/06/12　09/12/25 修正
;	結果  freg > 定数  Carry=1, Zero=0
;		  freg = 定数  Carry=1, Zero=1
;		  freg < 定数  Carry=0, Zero=0
;	Wregは破壊される  fregは不変
;-----------------------------------
_?cpfl	macro freg, cnst	;compare freg with data
	movlw	cnst		;cnst==>Wreg
	banksel	freg
	subwf	freg, W		;freg-Wreg==>Wreg
	endm
;======================================================
;	比較[freg - Wreg]	[?byte使う] 10/06/12　09/12/25 修正
;	結果  freg > Wreg  Carry=1, Zero=0
;		  freg = Wreg  Carry=1, Zero=1
;		  freg < Wreg  Carry=0, Zero=0
;	Wregは破壊される  fregは不変
;-----------------------------------
_?cpfw	macro freg			;compare freg with Wreg
	banksel	freg
	subwf	freg, W		;freg-Wreg==>Wreg
	endm
;======================================================
;	比較[freg1 - freg2]	[?byte使う] 10/06/12 09/12/25 修正
;	結果  freg1 > freg2  Carry=1, Zero=0
;		  freg1 = freg2  Carry=1, Zero=1
;		  freg1 < freg2  Carry=0, Zero=0
;	Wregは破壊される  freg1,freg2はともに不変
;-----------------------------------
_?cpff	macro freg1, freg2	;compare freg1 with greg2
	banksel	freg2
	movf	freg2, W	;freg2==>Wreg
	banksel	freg1
	subwf	freg1, W	;freg1-Wreg==>Wreg
	endm
;*********************************************************
;	2byteの変数の加算  (AH,AL) + (BH,BL) ==> (AH,AL)
;	00/05/16
;	AH,AL,BH,BLは主プログラムで宣言しておく
;	注)	オーバーフローが起こったとき 未確認
;	Wregは破壊される  [?byte使う] 10/06/12
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
;	レジスタの退避		2012/06/19 
;	 ﾒｲﾝﾙｰﾁﾝと割り込みﾙｰﾁﾝの両方で使用しているﾚｼﾞｽﾀを退避させる
;	変数 w_temp, status_temp, fsr_temp, pclath_tempは主ルーチン
;	にて確保すること
;------------------------------------------------
_?push    macro
        movwf   w_temp                  ; ﾒｲﾝﾙｰﾁﾝと割り込みﾙｰﾁﾝの両方で
        swapf   STATUS,W                ; 使用しているﾚｼﾞｽﾀを退避させる
        bcf     STATUS,RP0              ; 
        movwf   status_temp             ; w_temp      <- W
        movf    FSR,W                   ; status_temp <- STATUS
        movwf   fsr_temp                ; fsr_temp    <- FSR
        movf    PCLATH,W                ; pclath_temp <- PCLATH
        movwf   pclath_temp             ; 
        clrf    PCLATH                  ; 
        endm
;*********************************************************
;	レジスタの復元		2012/06/19 
;	 ﾒｲﾝﾙｰﾁﾝと割り込みﾙｰﾁﾝの両方で使用しているﾚｼﾞｽﾀを復元させる
;	変数 w_temp, status_temp, fsr_temp, pclath_tempは主ルーチン
;	にて確保すること
;------------------------------------------------
_?pop     macro
        movf    pclath_temp,W           ; pushで退避させたﾚｼﾞｽﾀの復元
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
;	このマクロはページ(2k byte)を超えてcallした後、元の
;	pageに戻る
;--------------------------------------------
fcall	macro subroutine_name
	local here
	lcall subroutine_name
	pagesel here
here:
	endm
;======================================================
;	このマクロはpage0からpage1へ、
;	あるいはpage0からpage1へ移動するものである。
;		lcallと対で使うと、page間の移動を意識しないで済む。
;	2pageまで(page0,page1) メモリサイズ4K までのPICを予定している
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
