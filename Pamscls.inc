; vim: set syntax=pic ts=4 sts=4 sw=4: last change:2010/06/18 08:04:52.
	LIST	r=dec
;====== Pamscls.inc ===================================
;  Contorl Logic Stracture Macors for MPLAB
;	Ver 1.5i           Last Change:2010/06/18 08:04:52.
;		Copyright (C) 2000-2010 堀野 守克 
	NOLIST
;	このファイルの終わりにMyutility.incをインクルードしてある
;	内部マクロ群はPamscls_sub.incとして独立させた  2010/06/18 
;======================================================
#ifndef	_PAMSCLS_ABS_INC_INCLUDED
#define	_PAMSCLS_ABS_INC_INCLUDED
;====================================================
#ifndef	_PAMSCLS_ABS_HEADER_INC_INCLUDED
#include	<d:\1_PIC\MyLibrary\Pamscls_header_abs.inc>
#endif
;====================================================
;	二分岐
;	Freg1とFreg2の比較
;		if .. c .. else .. endif
;		Freg1,cnd,Freg2,logic	構文A
;
;	Fregと定数の比較
;		ifcnst .. c_cnst .. else .. endif
;		Freg,cnd,CONST,logic	構文A
;
;	Fregのビットテスト
;		ifbit .. c_bit .. else .. endif
;		Freg,bit,cnd,logic		構文B
;	
;   ifの複合条件(c文, [c_cnst, c_bit])指定可能
;
;	if文内でbreak文,continue文を使うとループ構造[for,while,repeat]
;	から脱出できる
;		但し、if文の入れ子は不可(単純なif文のみ)
;--------------------
;	繰り返し
;	forの増分値は定数を使う
;		forinc|fordec .. continue .. break .. endfor
;
;	繰り返し
;	forの境界値に定数を使う場合は forinccnst | fordeccnst文を
;	使う
;		forinccnst|fordeccnst .. endfor
;--------------------
;	繰り返し
;		while .. continue .. break .. endwhile
;
;	繰り返し
;	whileの境界値に定数を使う場合は whilecnst 文を使う
;		whilecnst .. continue .. break .. endwhile
;
;	繰り返し
;	whileの境界値にbit testを使う場合は whilebit 文を使う
;		whilebit .. continue .. break .. endwhile
;--------------------
;	繰り返し
;		repeat .. continue .. break .. until
;
;	繰り返し
;	untilの境界値に定数を使う場合は untilcnst 文を使う
;		repeat .. continue .. break .. untilcnst
;
;	繰り返し
;	untilの境界値にbit testを使う場合は untilbit 文を使う
;		repeat .. continue .. break .. untilbit
;
;	繰り返し[無限ループ]	09/11/10 追加
;	無限ループの場合はuntilの代わりに always 文を使う
;		repeat .. always	引数なし
;		ループからの脱出には goto 文か break 文を使う
;--------------------
;	多分岐
;	Wregと変数|定数の比較による分岐
;		switch .. c_case .. case .. break .. default .. endswitch
;		変数にはc_case, case文を使う 
;		定数にはc_casecnst, casecnst文を使う
;		_?c_case/_?c_casecnst文はORであり、_?case/_?casecnst文はQUITである
;--------------------
;	_?c( freg用 )と_?c_bit( bit test用 ) _?c_cnst( 定数用 )
;	は混在が可能
;====================================================
;	_?temp0を使うのは_?subwlと_?swapff[MyUtility.inc]
;	_?temp1..7を使うのは_?forと_?switch
;====================================================
;	作業変数領域をchip毎に割り当てることは自動で出来るようになった。
;	_?MEMORYを使う
;	作業変数としてを _?temp0..7を使う。(予約変数とする)
;	使用できる bankは各chipにより異なる。
;	16F84/84A.......... bank0, bank1
;	16F627A/628A/648A.. bank0, bank1, bank2, bank3
;	16F87/88...........   ibid
;	12F629/675......... bank0, bank1
;		12F629を追加	07/06/15
;		12F675,16F627A,16F628Aを追加	09/04/21
;		16F87/88を追加 10/01
;	Timer.incでは(_?MEMORY -4)から4byteを使う
;====================================================
#ifndef	_PAMSCLS_INC_INCLUDED
#define	_PAMSCLS_INC_INCLUDED
;====================================================
;;   Macro variable INIT
;;****************************************************
;	variable	_?nstlv	=	0	;Nesting level
;	variable	_?curlb	=	0	;Current label index
;	variable	_?dolv	=	0	;Do nest level
;	variable	_?atrf1	=	0	;Attr 1.
;	variable	_?atrf2	=	0	;Attr 2.
;	variable	_?atrf3	=	0	;Attr 3.
;	variable	_?atrf4	=	0	;Attr 4.
;	variable	_?atrf5	=	0	;Attr 5 forinc(0), fordec(1)の区別
;	variable	_?contc	=	0	;condition continue? 
;	variable	_?cscas	=	0	;case count
;	variable	_?nstcs	=	0	;case group count
;
;	constant	EQ	=	0
;	constant	NE	=	1
;	constant	GE	=	2
;	constant	GT	=	3
;	constant	LE	=	4
;	constant	LT	=	5
;	constant	OR	=	1
;	constant	AND	=	2
;	constant	QUIT=	0
;	constant	CL	=	10	;_?ifbit/_?whilebit/_?untilbitのため
;	constant	ST	=	11
;;****************************************************
;;	作業変数の確保	10/05/25 変更
;;	_?TOPMEMOはPamscls, Timer.incでは使っていない
;;****************************************************
;	ifdef	__16F84
;_?TOPMEMO	equ		0x0c	;GPRの先頭
;_?BTMMEMO	equ		0x4F	;GPR(共通)の終わり
;	endif
;	ifdef	__16F84A
;_?TOPMEMO	equ		0x0c
;_?BTMMEMO	equ		0x4F
;	endif
;	;++++++++++++
;	ifdef	__12F629		;07/06/15
;_?TOPMEMO	equ		0x20	;GPRの先頭
;_?BTMMEMO	equ		0x5F	;GPR(共通)の終わり
;	endif
;	ifdef	__12F675		;09/04/21 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x5F
;	endif
;	ifdef	__12F683		;10/04/02 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	;++++++++++++
;	ifdef	__16F627A		;09/04/21 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	ifdef	__16F628A		;09/04/21 追加
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	ifdef	__16F648A
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	;++++++++++++
;	ifdef	__16F87
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;	ifdef	__16F88
;_?TOPMEMO	equ		0x20
;_?BTMMEMO	equ		0x7F
;	endif
;;****************************************************
;;		GPRの終わりの8byteを作業領域とする
;;****************************************************
;	cblock	(_?BTMMEMO - 8 + 1 )	;09/11/06 修正
;_?temp0,_?temp1,_?temp2,_?temp3,_?temp4,_?temp5,_?temp6,_?temp7
;	endc
;****************************************************
;   IF		freg間の比較	09/05/23
;****************************************************
_?if	macro	_?data1,_?cnd,_?data2,_?logic
	if(_?contc != 0)
		error"Illegal use of macro sequence _?if"
	endif
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?if"
	endif
_?curlb++
_?trulb	=	0
_?faulb	=	0
_?atrf1	=	(_?atrf1 << 1)+1
_?atrf2	=	(_?atrf2 << 1)
_?atrf3	=	(_?atrf3 << 1)
_?atrf4	=	(_?atrf4 << 1)
_?atrf5	=	(_?atrf5 << 1)
_?trulb=_?curlb
	_?setbb	#v(_?nstlv),#v(_?trulb);trulbをstack
_?faulb=_?curlb+1
	_?seteb #v(_?nstlv),#v(_?faulb);faulbをstack
_?endlb=_?curlb+2			;09/05/24
	_?setex	#v(_?nstlv),#v(_?endlb)	;if blockの出口ラベルをstack
_?curlb=_?curlb+2
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   IFCNST		fregと定数の比較	09/05/27	
;****************************************************
_?ifcnst	macro	_?data1,_?cnd,_?data2,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?ifcnst"
	endif
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?ifcnst"
	endif
_?curlb++
_?trulb	=	0
_?faulb	=	0
_?atrf1	=	(_?atrf1 << 1)+1
_?atrf2	=	(_?atrf2 << 1)
_?atrf3	=	(_?atrf3 << 1)
_?atrf4	=	(_?atrf4 << 1)
_?atrf5	=	(_?atrf5 << 1)
_?trulb=_?curlb
	_?setbb	#v(_?nstlv),#v(_?trulb);trulbをstack
_?faulb=_?curlb+1
	_?seteb #v(_?nstlv),#v(_?faulb);faulbをstack
_?endlb=_?curlb+2			;09/05/24
	_?setex	#v(_?nstlv),#v(_?endlb)	;if blockの出口ラベルをstack
_?curlb=_?curlb+2
	_?cndck_cnst	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   IFBIT		bit test	09/05/27
;****************************************************
_?ifbit	macro	_?data1,_?data2, _?cnd, _?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?ifbit"
	endif
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?ifbit"
	endif
_?curlb++
_?trulb	=	0
_?faulb	=	0
_?atrf1	=	(_?atrf1 << 1)+1
_?atrf2	=	(_?atrf2 << 1)
_?atrf3	=	(_?atrf3 << 1)
_?atrf4	=	(_?atrf4 << 1)
_?atrf5	=	(_?atrf5 << 1)
_?trulb=_?curlb
	_?setbb	#v(_?nstlv),#v(_?trulb);trulbをstack
_?faulb=_?curlb+1
	_?seteb #v(_?nstlv),#v(_?faulb);faulbをstack
_?endlb=_?curlb+2			;09/05/24
	_?setex	#v(_?nstlv),#v(_?endlb)	;if blockの出口ラベルをstack
_?curlb=_?curlb+2
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   ELSE
;****************************************************
_?else	macro
	if(_?contc != 0)
		error "NO logical operator 'QUIT' "
		error "Illegal use of macro sequence _?else"
	endif
	if((_?atrf1 % 2)==0)
	  error"Can't find _?if/_?ifbit/_?ifcnst statement in this block"
	endif
	if((_?atrf3 % 2)== 1)
	  error "Already have _?else in this block"
	endif
_?curlb++
	_?gexjp	#v(_?nstlv)	;ex[endifの出口ラベル]へ行く09/05/24
	_?exteb	#v(_?nstlv)	;ELSEの入り口ラベルを作る09/05/24
_?atrf3++
	endm
;****************************************************
;   ENDIF	07/07/11
;****************************************************
_?endif	macro
	if(_?contc != 0)
		error "NO logical operator 'QUIT' "
		error "Illegal use of macro sequence _?endif"
	endif
	if((_?atrf1 % 2)==0)
	  error"Can't find _?if/_?ifbit/_?ifcnst  statement in this block"
	endif
_?curlb++
	if((_?atrf3 % 2)==0);else部がない、仮のelseの入り口
	_?gexjp	#v(_?nstlv)	;ex[endifの出口ラベル]へ行く09/05/24
	_?exteb	#v(_?nstlv)	;ELSEの入り口ラベルを作る09/05/24
	endif
	_?extex	#v(_?nstlv)	;出口ラベルを作る09/05/24
_?curlb++;07/07/14
_?atrf1	=(_?atrf1 >> 1)	;Attr 1
_?atrf2	=(_?atrf2 >> 1)	;Attr 2
_?atrf3	=(_?atrf3 >> 1)	;Attr 3
_?atrf4	=(_?atrf4 >> 1)	;Attr 4
_?atrf5	=(_?atrf5 >> 1)	;Attr 5
_?nstlv--
	endm
;**************************************************
;  CNDCK1	10/02/22 untilのバグ
;	_?contcは論理演算子による振り分けフラグ
;	複合条件のbug修正	07/06/23
;**************************************************
_?cndck1 macro  _?data1,_?data2,_?cnd,_?logic
	if(_?logic==OR)	;///// or //////
_?contc	=	OR;1
_?curlb++
	_?genlb	#v(_?curlb);このブロックの入り口ラベルを作る
		_?genjp	#v(_?curlb+2);goto [curlb+1]を作る
	_?genlb	#v(_?curlb+1);このブロックの中間ラべルを作る
		_?genjp #v(_?curlb+4)
	_?genlb #v(_?curlb+2);ラベル[]を作る
_?curlb++
;	messg"End of OR"
	else
	if(_?logic==AND)	;///// and //////////
_?contc	=	AND;2
_?curlb++
	_?genlb	#v(_?curlb);このブロックの入り口ラベルを作る
		_?genjp #v(_?curlb+3)
	_?genlb	#v(_?curlb+1);このブロックの中間ラべルを作る
		_?genjp #v(_?curlb+2);goto (出口)を作る
	_?genlb	#v(_?curlb+2);このブロックの出口ラベルを作る
_?curlb++
;	messg"End of AND"
	else
	if(_?logic==QUIT)	;///// quit ///// AND,ORがないのでこれでおわり
_?contc	=	QUIT;0
;_?curlb++	;@@@@
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==1)&&((_?atrf4 % 2)==1))
						;****ここはuntil:QUITの場合
_?curlb++	;@@@@
		_?genlb	#v(_?curlb);until:QUITの入り口ラベルをつくる[10/02/22 この行を削除]
			_?grbjp #v(_?dolv);goto top
		_?genlb	#v(_?curlb+1);このブロックの中間ラべルを作る
			_?grejp #v(_?dolv);goto end
		_?extre #v(_?dolv);eb(_?nst)ラベルをつくる
_?curlb++
_?nstlv--
_?dolv--
_?atrf1	=	_?atrf1 >> 1;Attr 1;07/07/11ここに移動
_?atrf2	=	_?atrf2 >> 1;Attr 2
_?atrf3	=	_?atrf3 >> 1;Attr 3
_?atrf4	=	_?atrf4 >> 1;Attr 4
_?atrf5	=	_?atrf5 >> 1;Attr 5
;	messg"End until QUIT"
	else	;==3..until
;	endif;==3..until
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==0)&&((_?atrf4 % 2)==1))
						 ;****ここはwhile:QUITの場合
_?curlb++
	_?genlb	#v(_?curlb);while:QUITの入り口ラベルをつくる
		_?gwejp	#v(_?dolv);出口へ行く
	_?genlb	#v(_?curlb+1);このブロックの中間ラべルを作る
		_?gwtjp #v(_?dolv);実行文の入り口に行く
	_?extwt #v(_?dolv);実行文の入り口ラベルを作る
_?curlb++	;@@@@@@10/03/09
;	messg"End while QUIT"
	else	;==3..while
;	endif;==3..while
	if(((_?atrf1 % 2)==1)&&((_?atrf4 % 2)==0))
		                  ;****ここはif:QUITの場合
_?curlb++
	_?genlb #v(_?curlb);if:QUITの入り口ラベルを作る
		_?genjp #v(_?faulb);goto (faulb)を作る
	_?genlb	#v(_?curlb+1);このブロックの中間ラべルを作る
		_?genjp #v(_?trulb);goto (trulb)を作る
	_?genlb #v(_?trulb);trulbラベルを作る
_?curlb++	;@@@@
_?atrf2++
;	messg"End if QUIT"
;	endif;==3..if
	else
		error"Illegal instruction!"
	endif;==2..QUIT
	endif
	endif;
	else
		error"Illegal logical operator!"
	endif;
	endif	;@@@@AND
	endif	;@@@@OR
	endm
;***************************************************
;	CNDCK_vari	for _?if, _?ifbit, _?while, _?whilebit
;					_?until, _?untilbit, _?c, _?c_bit
;	2007/06/23　修正
;***************************************************
_?cndck_vari	macro	_?data1,_?data2,_?cnd,_?logic
	if(_?cnd == ST)
		btfss	_?data1,_?data2	;bit set => skip
	else
	if(_?cnd == CL)
		btfsc	_?data1,_?data2	;bit clear=> skip
	else
		movf	_?data2,W
		subwf	_?data1,W	;data1 - data2
		_?logical	_?cnd
	endif
	endif
	_?cndck1 _?data1,_?data2,_?cnd,_?logic
	endm
;***************************************************
;	CNDCK_cnst	for _?ifcnst, _?whilecnst, _?untilcnst
;					_?c_cnst
;	2007/06/23　修正
;***************************************************
_?cndck_cnst	macro	_?data1,_?data2,_?cnd,_?logic
	if(_?cnd == ST)
		btfss	_?data1,_?data2	;bit set => skip
	else
	if(_?cnd == CL)
		btfsc	_?data1,_?data2	;bit clear=> skip
	else
		movlw	_?data2
		subwf	_?data1,W	;data1 - data2
		_?logical	_?cnd
	endif
	endif
	_?cndck1 _?data1,_?data2,_?cnd,_?logic
	endm
;***************************************************
;	LOGICAL		10/02/23
;***************************************************
_?logical	macro	_?cnd
	if(_?cnd == EQ)
		btfss	STATUS,Z;EQ..skip
	else
	if(_?cnd == NE)
		btfsc	STATUS,Z;NE..skip
	else
	if(_?cnd == GT) 
		btfsc	STATUS,C	;if nega..skip 09/07/15
		btfsc	STATUS,Z	;if posi..skip 6/23
	else
	if(_?cnd == LT)
		btfsc	STATUS,C	;if nega..skip 09/07/15
	else
	if(_?cnd == GE)
		btfss	STATUS,C;if posi|zero..skip	09/07/15
	else
	if(_?cnd == LE)
		btfss	STATUS,C;if posi|zero..skip	09/07/15
			goto $+3	; == nega
		btfss	STATUS,Z; == [posi,zero] if zero..skip
	else
		error "Illegal condtional operator"
	endif
	endif
	endif
	endif
	endif
	endif
	endm
;****************************************************
;   C		07/07/11
;****************************************************
_?c	macro	_?data1,_?cnd,_?data2,_?logic
	if(_?contc == 0)
		error "Illegal use of macro sequence _?c"
	endif
_?curlb++
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   C_BIT		07/07/11
;****************************************************
_?c_bit	macro	_?data1,_?data2,_?cnd,_?logic
	if(_?contc == 0)
		error "Illegal use of macro sequence _?c_bit"
	endif
_?curlb++
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   C_CNST		07/07/11
;****************************************************
_?c_cnst	macro	_?data1,_?cnd,_?data2,_?logic
	if(_?contc == 0)
		error "Illegal use of macro sequence _?c_cnst"
	endif
_?curlb++
	_?cndck_cnst	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   REPEAT		09/11/10
;****************************************************
_?repeat	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?repeat"
	endif
_?curlb++		;Current label index
_?dolv++		;Do nest level
_?nstlv++			;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?repeat"
	endif
_?faulb=_?curlb
	_?setrb #v(_?dolv),#v(_?faulb);入口ラベルをstack
_?trulb=_?curlb+1
	_?setre #v(_?dolv),#v(_?trulb)	;ループ出口をstack
	_?extrb #v(_?dolv);ループ入口作成
_?curlb++
_?atrf1	=(_?atrf1 << 1)+1	;Attr 1 07/07/10
_?atrf2	=(_?atrf2 << 1)	;Attr 2
_?atrf3	=(_?atrf3 << 1)+1	;Attr 3
_?atrf4	=(_?atrf4 << 1)+1	;Attr 4
_?atrf5	=(_?atrf5 << 1)	;Attr 5
	endm
;****************************************************
;   UNTIL	07/07/11
;****************************************************
_?until	macro	_?data1,_?cnd,_?data2,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?until"
	endif
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==1)&&((_?atrf4 % 2)==1))
		_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	else
	  error "Can't find _?repeat statement in this block"
	endif
	endm
;****************************************************
;   UNTILCNST	07/07/11
;****************************************************
_?untilcnst	macro	_?data1,_?cnd,_?data2,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?untilcnst"
	endif
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==1)&&((_?atrf4 % 2)==1))
		_?cndck_cnst	_?data1,_?data2,_?cnd,_?logic
	else
	  error "Can't find _?repeat statement in this block"
	endif
	endm
;****************************************************
;   UNTILBIT	07/07/11
;****************************************************
_?untilbit	macro	_?data1,_?data2,_?cnd,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?untilbit"
	endif
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==1)&&((_?atrf4 % 2)==1))
		_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	else
	  error "Can't find _?repeat statement in this block"
	endif
	endm
;****************************************************
;   ALWAYS	10/02/22
;****************************************************
_?always	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?always"
	endif
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==1)&&((_?atrf4 % 2)==1))
;	_?genlb	#v(_?curlb);until:QUITの入り口ラベルをつくる[10/02/22この行を削除]
		_?grbjp	#v(_?dolv)
	_?genlb	#v(_?curlb+1);このブロックの中間ラべルを作る
		_?grejp #v(_?dolv);goto end
	_?extre #v(_?dolv);re(_?nst)ラベルをつくる
_?curlb++
_?nstlv--
_?dolv--
_?atrf1	=	_?atrf1 >> 1;Attr 1;07/07/11ここに移動
_?atrf2	=	_?atrf2 >> 1;Attr 2
_?atrf3	=	_?atrf3 >> 1;Attr 3
_?atrf4	=	_?atrf4 >> 1;Attr 4
_?atrf5	=	_?atrf5 >> 1;Attr 5
	else
	  error "Can't find _?repeat statement in this block"
	endif
	endm
;****************************************************
;   WHILE	09/11/10
;****************************************************
_?while	macro   _?data1,_?cnd,_?data2,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?while"
	endif
_?dolv++	;Do nest level
_?nstlv++	;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?while"
	endif
_?curlb++	;Current label Ndx
	_?setwb #v(_?dolv),#v(_?curlb);ループ入口ラベルをstack
_?curlb++
_?trulb=_?curlb
	_?setwt #v(_?dolv),#v(_?trulb);実行文入口ラベルをstack
_?curlb++
_?faulb=_?curlb
	_?setwe #v(_?dolv),#v(_?faulb);ループ出口ラベルをstack
	_?extwb	#v(_?dolv);ループ入口ラベルを作成
_?atrf1	=(_?atrf1 << 1)+1	;Attr 1
_?atrf2	=_?atrf2 << 1   ;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=(_?atrf4 << 1)+1	;Attr 4
_?atrf5	=(_?atrf5 << 1);Attr 5
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
        endm
;****************************************************
;   WHILECNST	09/11/10
;****************************************************
_?whilecnst	macro   _?data1,_?cnd,_?data2,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?whilecnst"
	endif
_?dolv++		;Do nest level
_?nstlv++		;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?whilecnst"
	endif
_?curlb++		;Current label Ndx
	_?setwb #v(_?dolv),#v(_?curlb);ループ入口ラベルをstack
_?curlb++
_?trulb=_?curlb
	_?setwt #v(_?dolv),#v(_?trulb);実行文入口ラベルをstack
_?curlb++
_?faulb=_?curlb
	_?setwe #v(_?dolv),#v(_?faulb);ループ出口ラベルをstack
	_?extwb	#v(_?dolv);ループ入口ラベルを作成
_?atrf1	=(_?atrf1 << 1)+1	;Attr 1
_?atrf2	=_?atrf2 << 1   ;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=(_?atrf4 << 1)+1	;Attr 4
_?atrf5	=(_?atrf5 << 1);Attr 5
	_?cndck_cnst	_?data1,_?data2,_?cnd,_?logic
        endm
;****************************************************
;   WHILEBIT	09/11/10
;****************************************************
_?whilebit	macro   _?data1,_?data2,_?cnd,_?logic
	if(_?contc != 0)
		error "Illegal use of macro sequence _?whilebit"
	endif
_?dolv++	;Do nest level
_?nstlv++	;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?whilebit"
	endif
_?curlb++	;Current label Ndx
	_?setwb #v(_?dolv),#v(_?curlb);ループ入口ラベルをstack
_?curlb++
_?trulb=_?curlb
	_?setwt #v(_?dolv),#v(_?trulb);実行文入口ラベルをstack
_?curlb++
_?faulb=_?curlb
	_?setwe #v(_?dolv),#v(_?faulb);ループ出口ラベルをstack
	_?extwb	#v(_?dolv);ループ入口ラベルを作成
_?atrf1	=(_?atrf1 << 1)+1	;Attr 1
_?atrf2	=_?atrf2 << 1   ;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=(_?atrf4 << 1)+1	;Attr 4
_?atrf5	=(_?atrf5 << 1);Attr 5
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
        endm
;****************************************************
;   ENDWHILE	09/11/10	
;****************************************************
_?endwhile	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?endwhile"
	endif
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==0)&&(_?atrf4 % 2)==1)
	_?gwbjp #v(_?dolv);goto ループ入口
	_?extwe #v(_?dolv);出口ラベルを作る
_?nstlv--		;Nesting Level
_?dolv--		;Do nest level
_?atrf1	=_?atrf1 >> 1;Attr 1
_?atrf2	=_?atrf2 >> 1;Attr 2
_?atrf3	=_?atrf3 >> 1;Attr 3
_?atrf4	=_?atrf4 >> 1;Attr 4
_?atrf5	=_?atrf5 >> 1;Attr 5
	else
	  error "Can't find _?while statement in this block"
	endif
	endm
;***************************************************
;  FORINC	09/05/27	
;	_?data2(境界値)は変数を使う
;	_?data3(増分値)は定数を使うことにした。
;	判定をskpc[skip on carry]を使うことにした。
;***************************************************
_?forinc	macro	_?data1,_?data2,_?data3
_?dolv++	;Do nest level
_?nstlv++	;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?forinc"
	endif
_?curlb++	;Current label
	_?movlf _?data3,_?temp#v(_?nstlv)	;堀野 増分値を保存
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)をstack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)をstack
	_?extfb	#v(_?dolv) ;入り口のラベルを作る
	movf	_?data2,w	;data2[var] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnpls	;09/05/27結果が非正(負|zero)であるとforの実行文へ
	_?gfejp #v(_?dolv)	;goto (出口)を作成
_?curlb++
_?trulb =       0
_?faulb =       0
_?atrf1	=_?atrf1 << 1	;Attr 1
_?atrf2	=(_?atrf2 << 1)+1	;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=_?atrf4 << 1	;Attr 4
_?atrf5	=_?atrf5 << 1	;Attr 5
	endm
;***************************************************
;  FORINCCNST	09/05/27	
;	_?data2(境界値)は定数を使う
;	_?data3(増分値)は定数を使うことにした。
;	判定をskpc[skip on carry]を使うことにした。
;***************************************************
_?forinccnst	macro	_?data1,_?data2,_?data3
_?dolv++	;Do nest level
_?nstlv++	;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?forinccnst"
	endif
_?curlb++	;Current label 
	_?movlf _?data3,_?temp#v(_?nstlv)	;堀野 増分値を保存
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)をstack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)をstack
	_?extfb	#v(_?dolv) ;入り口のラベルを作る
	movlw	_?data2		;data2[cnst] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnpls	;09/05/27結果が非正(負|zero)であるとforの実行文へ
	_?gfejp #v(_?dolv)	;goto (出口)を作成
_?curlb++
_?trulb = 0
_?faulb = 0
_?atrf1	=_?atrf1 << 1	;Attr 1
_?atrf2	=(_?atrf2 << 1)+1	;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=_?atrf4 << 1	;Attr 4
_?atrf5	=_?atrf5 << 1	;Attr 5
	endm
;***************************************************
;  FORDEC	09/05/27	
;	_?data2(境界値)は変数を使う
;	_?data3(減分値)は定数を使うことにした。
;***************************************************
_?fordec	macro	_?data1,_?data2,_?data3
_?dolv++	;Do nest level
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?fordec"
	endif
_?curlb++	;Current label Ndx
	_?movlf _?data3,_?temp#v(_?nstlv);増分をstack
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)をstack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)をstack
	_?extfb	#v(_?dolv) ;入り口のラベルを作る
	movf	_?data2		;data2[var] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnneg	;09/05/26結果が非負(正|zero)であるとforの実行文へ
	_?gfejp #v(_?dolv)	;goto (出口)を作成
_?curlb++
_?trulb = 0
_?faulb = 0
_?atrf1	=_?atrf1 << 1	;Attr 1
_?atrf2	=(_?atrf2 << 1)+1	;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=_?atrf4 << 1	;Attr 4
_?atrf5	=(_?atrf5 << 1)+1	;Attr 5
	endm
;***************************************************
;  FORDECCNST	09/05/27	
;	_?data2(境界値)は定数を使う
;	_?data3(減分値)は定数を使うことにした。
;***************************************************
_?fordeccnst	macro	_?data1,_?data2,_?data3
_?dolv++			;Do nest level
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?fordeccnst"
	endif
_?curlb++			;Current label Ndx
	_?movlf _?data3,_?temp#v(_?nstlv);増分をstack
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)をstack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)をstack
	_?extfb	#v(_?dolv) ;入り口のラベルを作る
	movlw	_?data2		;data2[cnst] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnneg	;09/05/26結果が非負(正|zero)であるとforの実行文へ
	_?gfejp #v(_?dolv)	;goto (出口)を作成
_?curlb++
_?trulb = 0
_?faulb = 0
_?atrf1	=_?atrf1 << 1	;Attr 1
_?atrf2	=(_?atrf2 << 1)+1	;Attr 2
_?atrf3	=_?atrf3 << 1	;Attr 3
_?atrf4	=_?atrf4 << 1	;Attr 4
_?atrf5	=(_?atrf5 << 1)+1	;Attr 5
	endm
;***************************************************
;  ENDFOR	09/05/26  fordecの時、バグを修正
;***************************************************
_?endfor	macro	_?data
	if(((_?atrf1 % 2)==1)||((_?atrf4 % 2)==1))
	  error "Can't find _?for* statement in this block"
	endif
 	movf	_?temp#v(_?nstlv),w	;dat3==>Wreg 増分値を復元
	if((_?atrf5 % 2)==0)
		addwf	_?data,f;data1+data3==>data1 forinc
	else
		subwf	_?data,f;data1-data3==>data1 fordec
	endif
	_?gfbjp #v(_?dolv)	;ループ入り口へ飛ぶ
	_?extfe #v(_?dolv)	;出口のラベルを作る
_?nstlv--	;Nesting Level
_?dolv--	;Do nest level
_?atrf1	=	_?atrf1 >> 1	;Attr 1
_?atrf2	=	_?atrf2 >> 1	;Attr 2
_?atrf3	=	_?atrf3 >> 1	;Attr 3
_?atrf4	=	_?atrf4 >> 1	;Attr 4
_?atrf5	=	_?atrf5 >> 1	;Attr 5
	endm
;**************************************************
;   SWITCH		09/08/20
;**************************************************
_?switch	 macro	
	if(_?contc != 0)
		error "Illegal use of macro sequence _?switch"
	endif
_?trulb	=	0
_?faulb	=	0
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?switch"
	endif
_?dolv++
_?cscas=0
	movwf	_?temp#v(_?nstlv)	;04/12/12 Wregを保存
_?curlb++
	_?seteb #v(_?nstlv),#v(_?curlb)	;出口のラベルを準備する
_?curlb++
_?nstcs=_?nstlv*100+_?cscas;10
	_?ssnvb	#v(_?nstcs-1),#v(_?curlb);9,2
	_?savecs #v(_?nstlv),#v(_?nstcs-1)
_?atrf1	=_?atrf1 << 1
_?atrf2	=_?atrf2 << 1
_?atrf3	=_?atrf3 << 1
_?atrf4	=(_?atrf4 << 1)+1
_?atrf5	=_?atrf5 << 1
	endm
;**************************************************
;   CASE	10/02/23 堀野
;**************************************************
_?case	macro	_?vari
	if(_?contc != 0)
		error "Illegal use of macro sequence _?case"
	endif
	if(((_?atrf1 % 2)==0)&&((_?atrf4 % 2)== 0)) ;07/07/02
	  error "Can't find _?switch statement in this block"
	endif
	if((_?atrf2 % 2)==0) 
_?atrf2++
	endif
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;11  14
	_?gsnlb #v(_?svcs#v(_?nstlv))
;	messg"保存してあるWregを復元"
	movf	_?temp#v(_?nstlv),W	;保存してあるWregを復元 10/02/23
	subwf	#v(_?vari),w
	btfss	STATUS,Z
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;12 15
	_?ssnvb	#v(_?nstcs),#v(_?curlb+2);12,5
	_?savecs	#v(_?nstlv),#v(_?nstcs)
	_?gsnjp #v(_?nstcs);goto 5
	_?genlb #v(_?curlb);_?3
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;13
	_?ssnvb	#v(_?nstcs),#v(_?curlb);13,4
	_?gsnjp #v(_?nstcs);goto 
	_?gsnlb #v(_?nstcs);
_?curlb++
_?curlb++
	endm
;*************************************************
;   C_CASE	10/02/23 堀野
;*************************************************
_?c_case	macro	_?vari
	if(_?contc != 0)
		error "Illegal use of macro sequence _?c_case"
	endif
	if(((_?atrf1 % 2)==0)&&((_?atrf4 % 2)== 0)) ;07/07/02
	  error "Can't find _?switch statement in this block"
	endif
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;
	_?gsnlb #v(_?svcs#v(_?nstlv));
;	messg"保存してあるWregを復元"
	movf	_?temp#v(_?nstlv),W	;保存してあるWregを復元 10/02/23
	subwf	#v(_?vari),w
	btfss	STATUS,Z
_?cscas++
_?nstcs=_?nstlv*100+_?cscas
	_?ssnvb	#v(_?nstcs),#v(_?curlb+2)
	_?savecs	#v(_?nstlv),#v(_?nstcs)
	_?gsnjp #v(_?nstcs)
	_?genlb #v(_?curlb)
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas
	_?ssnvb	#v(_?nstcs),#v(_?curlb+2)
	_?gsnjp #v(_?nstcs);次のcase文へ行く
_?curlb++
	endm
;**************************************************
;   CASECNST	10/02/23 堀野
;**************************************************
_?casecnst	macro	_?const
	if(_?contc != 0)
		error "Illegal use of macro sequence _?casecnst"
	endif
	if(((_?atrf1 % 2)==0)&&((_?atrf4 % 2)== 0)) ;07/07/02
	  error "ACan't find _?switch statement in this block"
	endif
	if((_?atrf2 % 2)==0) 
_?atrf2++
	endif
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;11  14
	_?gsnlb #v(_?svcs#v(_?nstlv));_cs(cacas)を作る
;	messg"保存してあるWregを復元"
	movf	_?temp#v(_?nstlv),W	;保存してあるWregを復元 10/02/23
	sublw	#v(_?const)			;
	btfss	STATUS,Z
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;12 15
	_?ssnvb	#v(_?nstcs),#v(_?curlb+2);12,5
	_?savecs	#v(_?nstlv),#v(_?nstcs)
	_?gsnjp #v(_?nstcs);goto 5
	_?genlb #v(_?curlb);_?3
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;13
	_?ssnvb	#v(_?nstcs),#v(_?curlb);13,4
	_?gsnjp #v(_?nstcs);goto 
	_?gsnlb #v(_?nstcs);
_?curlb++
_?curlb++
	endm
;*************************************************
;   C_CASECNST	10/02/23	堀野
;*************************************************
_?c_casecnst	macro	_?const
	if(((_?atrf1 % 2)==0)&&((_?atrf4 % 2)== 0)) ;07/07/02
	  error "Can't find _?switch statement in this block"
	endif
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;11  14
	_?gsnlb #v(_?svcs#v(_?nstlv));_cs(cacas)を作る
;	messg"保存してあるWregを復元"
	movf	_?temp#v(_?nstlv),W	;保存してあるWregを復元 10/02/23
	sublw	#v(_?const)			;
	btfss	STATUS,Z
_?cscas++
_?nstcs=_?nstlv*100+_?cscas
	_?ssnvb	#v(_?nstcs),#v(_?curlb+2)
	_?savecs	#v(_?nstlv),#v(_?nstcs)
	_?gsnjp #v(_?nstcs)
	_?genlb #v(_?curlb)
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas
	_?ssnvb	#v(_?nstcs),#v(_?curlb+2)
	_?gsnjp #v(_?nstcs);次のcase文へ行く
_?curlb++
	endm
;**************************************************
;   CONTINUE  while/repeat/for	10/03/06
;	現在のループ構造[repeat, while, for]の先頭に行く
;	continue文はループ構造内でif文を介して使われる
;		但し、if文の入れ子は不可(単純なif文のみ)
;**************************************************
_?continue	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?continue"
	endif
	if((_?atrf1 % 2)==1)&&((_?atrf4 %2)==0)		;if
;		messg"continue in if statment"
	if((((_?atrf1>>1) % 2)==0)&&(((_?atrf2>>1) % 2)==1))	;for
;		messg"continue to top for" ;continueがforで使われている
		_?gfbjp(_?dolv);for top
	endif
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==0)&&(((_?atrf4>>1) % 2)==1))
;		messg"continue to top while"
		_?gwbjp #v(_?dolv);while入り口へ飛ぶ
	endif
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==1)&&(((_?atrf4>>1) % 2)==1))
;		messg"continue to top repeat"
		_?grbjp #v(_?dolv);until/always入り口へ飛ぶ
	endif
	endif
	endm
;**************************************************
;   BREAK	switch  while/repeat/for	10/03/06
;	現在のループ構造[repeat/always, while, for]を脱出する場合と
;	break文[現在のループ構造を脱出する]はswitch文内で使われる場合がある
;	ループ構造内ではif文を介して使われる
;		但し、if文の入れ子は不可(単純なif文のみ)
;**************************************************
_?break	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?break"
	endif
	if((_?atrf1 % 2)==0)&&((_?atrf4 % 2)==1)	;switch
		if((_?atrf2 % 2)==0)	;07/07/03
			error "Still Continue _?case_c block"
		else
			_?gebjp #v(_?nstlv);endswitch出口へ飛ぶ
		endif
	endif
	if((_?atrf1 % 2)==1)&&((_?atrf4 % 2)==0)	;if
;		messg"break in if statement"
	if((((_?atrf1>>1) % 2)==0)&&(((_?atrf2>>1) % 2)==1))	;for
;		messg"break to exit for" ;10/03/06
		_?gfejp(_?dolv);for
	endif		
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==0)&&(((_?atrf4>>1) % 2)==1))
;		messg"break exit while"		;10/03/06
		_?gwejp #v(_?dolv);while出口へ飛ぶ
	endif
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==1)&&(((_?atrf4>>1) % 2)==1))
;		messg"break exit until/always"	;10/03/06
		_?grejp #v(_?dolv);until/always出口へ飛ぶ
	endif
	endif
	endm
;**************************************************
;   DEFAULT
;**************************************************
_?default	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?default"
	endif
	if((_?atrf1 % 2)==0)&&((_?atrf4 % 2)==1)	;switch
		if((_?atrf2 % 2)==0)	;07/07/03
			error "Still Continue _?case_c block"
		endif
		if(((_?atrf3 % 2)-1)==0)	;07/06/25
		  error "Already have _?default statement in this block"
		endif
	endif
	_?gsnlb #v(_?nstcs-1)	;defaultの入り口ラベルを作成する
_?atrf3++	;default句があるしるし	
	endm
;**************************************************
;   ENDSWITCH
;**************************************************
_?endswitch	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?endswitch"
	endif
	if((_?atrf4 % 2)==0)	;07/07/03
		error "Can't find _?switch statement in this block"
	else
	   if((_?atrf2 % 2)==0)
	     error "Can't find _?case statement in this block"
	   endif
	endif
	if((_?atrf3 % 2)-1!=0)	;default句がない場合 仮の入口を作る
		_?gsnlb #v(_?nstcs-1)	;defaultの入り口ラベルを作成する
	endif
	_?exteb #v(_?nstlv)	;switchの出口ラベルを作る
_?atrf1	=	_?atrf1 >> 1	;Attr 1
_?atrf2	=	_?atrf2 >> 1	;Attr 2
_?atrf3	=	_?atrf3 >> 1	;Attr 3
_?atrf4	=	_?atrf4 >> 1	;Attr 4
_?atrf5	=	_?atrf5 >> 1	;Attr 5
_?nstlv--
_?dolv--
	endm
;===== INTERNAL MACROS ====ラベルを作る=======
;*******************************
;   EXTFB (internal macro) 07/07/11
;	fb (for begin block) ラベルを作る
;********************************
_?extfb macro   _?lvl
    _?genlb (_?fb#v(_?lvl))
	endm
;*******************************
;   EXTFE (internal macro) 07/07/11
;	fe (for end block) ラベルを作る
;********************************
_?extfe macro   _?lvl
    _?genlb (_?fe#v(_?lvl))
	endm
;*******************************
;   EXTLB (internal macro)
;	lb  ラベルを作る
;********************************
_?extlb macro   _?lvl
    _?genlb (_?lb#v(_?lvl))
	endm
;********************************
;	EXTBB  07/06/25
;	bb  ラベルを作る
;********************************
_?extbb	macro	_?lvl
	_?genlb	(_?bb#v(_?lvl))
	endm
;********************************
;   EXTEB (internal macro)
;	eb  ラベルを作る
;********************************
_?exteb    macro   _?lvl
    _?genlb (_?eb#v(_?lvl))
	endm
;********************************
;   EXTEX (internal macro)
;	ex  ラベルを作る	09/05/24
;********************************
_?extex    macro   _?lvl
    _?genlb (_?ex#v(_?lvl))
	endm
;********************************
;   EXTWB (internal macro)
;	wb  ラベルを作る	09/11/10
;	while用
;********************************
_?extwb    macro   _?lvl
    _?genlb (_?wb#v(_?lvl))
	endm
;********************************
;   EXTWE (internal macro)
;	we  ラベルを作る	09/11/10
;	while用
;********************************
_?extwe    macro   _?lvl
    _?genlb (_?we#v(_?lvl))
	endm
;********************************
;   EXTWT (internal macro)
;	wt  ラベルを作る	09/11/10
;	while用
;********************************
_?extwt    macro   _?lvl
    _?genlb (_?wt#v(_?lvl))
	endm
;********************************
;   EXTRB (internal macro)
;	rb  ラベルを作る	09/11/10
;	repeat用
;********************************
_?extrb    macro   _?lvl
    _?genlb (_?rb#v(_?lvl))
	endm
;********************************
;   EXTRE (internal macro)
;	re  ラベルを作る	09/11/10
;	repeat用
;********************************
_?extre    macro   _?lvl
    _?genlb (_?re#v(_?lvl))
	endm
;********************************
;   EXTRF (internal macro)
;	rf  ラベルを作る	09/11/10
;	repeat用
;********************************
;_?extrf    macro   _?lvl
;    _?genlb (_?rf#v(_?lvl))
;	endm
;=========================ラベルへ飛ぶ=========
;********************************
;   GFEJP (internal macro) 堀野
;	fb (for block) ラベルへ飛ぶ準備 07/07/11
;********************************
_?gfejp macro   _?lbl
	_?genjp (_?fe#v(_?lbl))
	endm
;********************************
;   GFBJP (internal macro) 堀野
;	fb (for block) ラベルへ飛ぶ準備 07/07/11
;********************************
_?gfbjp macro   _?lbl
	_?genjp (_?fb#v(_?lbl))
	endm
;********************************
;   GLBJP (internal macro) 堀野
;	lb ラベルへ飛ぶ準備
;********************************
_?glbjp macro   _?lbl
	_?genjp (_?lb#v(_?lbl))
	endm
;********************************
;   GBBJP (internal macro)
;	bb ラベルへ飛ぶ準備
;********************************
_?gbbjp	macro	_?lvl
	_?genjp (_?bb#v(_?lvl))
	endm
;********************************
;   GEBJP (internal macro)
;	eb ラベルへ飛ぶ準備
;********************************
_?gebjp        macro   _?lvl
    _?genjp (_?eb#v(_?lvl))
	endm
;********************************
;   GEXJP (internal macro)
;	ex ラベルへ飛ぶ準備		09/05/24
;********************************
_?gexjp        macro   _?lvl
    _?genjp (_?ex#v(_?lvl))
	endm
;********************************
;   GWBJP (internal macro)
;	wb ラベルへ飛ぶ準備		09/11/10
;	while用
;********************************
_?gwbjp        macro   _?lvl
    _?genjp (_?wb#v(_?lvl))
	endm
;********************************
;   GWEJP (internal macro)
;	we ラベルへ飛ぶ準備		09/11/10
;	while用
;********************************
_?gwejp        macro   _?lvl
    _?genjp (_?we#v(_?lvl))
	endm
;********************************
;   GWTJP (internal macro)
;	wt ラベルへ飛ぶ準備		09/11/10
;	while用
;********************************
_?gwtjp        macro   _?lvl
    _?genjp (_?wt#v(_?lvl))
	endm
;********************************
;   GRBJP (internal macro)
;	rb ラベルへ飛ぶ準備		09/11/10
;	repeat用
;********************************
_?grbjp        macro   _?lvl
    _?genjp (_?rb#v(_?lvl))
	endm
;********************************
;   GREJP (internal macro)
;	re ラベルへ飛ぶ準備		09/11/10
;	repeat用
;********************************
_?grejp        macro   _?lvl
    _?genjp (_?re#v(_?lvl))
	endm
;********************************
;   GRFJP (internal macro)
;	rf ラベルへ飛ぶ準備		09/11/10
;	repeat用
;;********************************
;_?grfjp        macro   _?lvl
;    _?genjp (_?rf#v(_?lvl))
;	endm
;==========================直接実行==============
;********************************
;   GENJP (internal macro)
;	ラベルに飛ぶ  実行体
;********************************
_?genjp macro   _?lbl
	goto _?#v(_?lbl)
	endm
;********************************
;   GENLB (internal macro)
;	ラベルをつくる　実行体
;********************************
_?genlb macro   _?lbl
_?#v(_?lbl)
    endm
;============== ラベル作成準備 (stack) =========
;********************************
;   SETFB (internal macro)
;	fb (for begin block) ラベル作成準備 (stack)
;********************************
_?setfb macro   _?lvl,_?lbl
_?fb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETFE (internal macro)
;	fe (for end block) ラベル作成準備 (stack)
;********************************
_?setfe macro   _?lvl,_?lbl
_?fe#v(_?lvl) = _?lbl
	endm
;********************************
;   SETLB (internal macro)
;	lb ラベル作成準備 (stack)
;********************************
_?setlb macro   _?lvl,_?lbl
_?lb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETBB (internal macro)
;	bb ラベル作成準備 (stack)
;********************************
_?setbb macro   _?lvl,_?lbl
_?bb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETEB (internal macro)
;	eb ラベル作成準備 (stack)
;********************************
_?seteb macro   _?lvl,_?lbl
_?eb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETEX (internal macro)
;	ex ラベル作成準備 (stack)	09/05/24
;********************************
_?setex macro   _?lvl,_?lbl
_?ex#v(_?lvl) = _?lbl
	endm
;********************************
;   SETWB (internal macro)
;	wb ラベル作成準備 (stack)	09/11/10
;	while用
;********************************
_?setwb macro   _?lvl,_?lbl
_?wb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETWE (internal macro)
;	we ラベル作成準備 (stack)	09/11/10
;	while用
;********************************
_?setwe macro   _?lvl,_?lbl
_?we#v(_?lvl) = _?lbl
	endm
;********************************
;   SETWT (internal macro)
;	wt ラベル作成準備 (stack)	09/11/10
;	while用
;********************************
_?setwt macro   _?lvl,_?lbl
_?wt#v(_?lvl) = _?lbl
	endm
;********************************
;   SETRB (internal macro)
;	rb ラベル作成準備 (stack)	09/11/10
;	repeat用
;********************************
_?setrb macro   _?lvl,_?lbl
_?rb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETRE (internal macro)
;	re ラベル作成準備 (stack)	09/11/10
;	repeat用
;********************************
_?setre macro   _?lvl,_?lbl
_?re#v(_?lvl) = _?lbl
	endm
;********************************
;   SETRF (internal macro)
;	rf ラベル作成準備 (stack)	09/11/10
;	repeat用
;********************************
;_?setrf macro   _?lvl,_?lbl
;_?rf#v(_?lvl) = _?lbl
;	endm
;========================= switch文用 ==========
;********************************
;   GSNJP (internal macro)
;********************************
_?gsnjp        macro _?casx
    _?genjp (_?cs#v(_?casx))
    endm
;********************************
;   GSNLB (internal macro)
;********************************
_?gsnlb macro   _?lvl
    _?genlb (_?cs#v(_?lvl))
    endm
;********************************
;   SSNVB (internal macro)
;********************************
_?ssnvb macro   _?lvl,_?lbl
_?cs#v(_?lvl) =	_?lbl
    endm
;********************************
;   SAVECS (internal macro)
;********************************
_?savecs macro   _?lvl,_?lbl
_?svcs#v(_?lvl) =	_?lbl
    endm
;********************************
;end of Pamscls.inc
;*********************************************************
	include	<d:\1_PIC\Mylibrary\Pamscls_sub.inc>
	include	<d:\1_PIC\MyLibrary\MyUtility_abs.inc>
;*********************************************************
#endif		;_PAMSCLS_ABS_INC_INCLUED
;*********************************************************
