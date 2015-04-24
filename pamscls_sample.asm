;	vim:	set syntax=pic:		ts=4	sts=4	sw=4
;	pamscls_sample.asm		Last Change:2012/03/07 21:07:04.
;	Pamsclsを使ったサンプルプログラム
;------------------------------------
;	if文	比較値1は変数、比較値2は変数
	_?if	sw1_sht,EQ,memo,QUIT	;sw1がshort onである
		bsf		Out_Sound
		goto	exit
	_?endif
;------------------------------------
;	ifcnst文	比較値1は変数、比較値2は定数
#define	ON	1
	_?ifcnst	sw1_sht,EQ,ON,QUIT	;sw1がshort onである
		bsf		Out_Sound
		goto	exit
	_?endif
;------------------------------------
;	ifbit文		判定するレジスターは変数、ビット位置は定数
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
;	ifbit文とwhilecnst文の複合
;	ifbit文		判定するレジスターは変数、ビット位置は定数
		_?ifbit	STATUS,Z,ST,QUIT	;codeが0x00であれば単語の終わり
			_?movlf	2,spc
			call	send_spce		;単語間のspaceを送信
			movf	codes,W
			andlw	b'00000111'
			_?whilecnst	length,GT,0,QUIT
				rlf		codes,F		;codes(MSB) => carry
									;文字のdot/dashを判定して、送信する
				_?ifcnst	STATUS,C,ST,QUIT
					call	send_dot
				_?else
					call	send_dash
				_?endif
				decf	length,F	;次のcodes
			_?endwhile
			_?movlf	1,spc
			nop
			nop	;BBB
		_?else
			call	send_spce ;char間のspaceのための待ち時間
		_?endif
;------------------------------------
;	while文		比較値1、比較値2は変数
	_?while i,LT,memo,QUIT
		bsf	Out_Sound
		bsf	Out_Tx
		call timeDelay1s
		bcf	Out_Sound
		bcf	Out_Tx
		incf	i
	_?endwhile
;------------------------------------
;	whilecnst文		比較値1は変数、比較値2は定数
	_?whilecnst i,LT,D'3',QUIT
		bsf	Out_Sound
		bsf	Out_Tx
		call timeDelay1s
		bcf	Out_Sound
		bcf	Out_Tx
		incf	i
	_?endwhile
;------------------------------------
;	whilebit文		bit test	
	_?whilebit flag,2,ST,QUIT	;flagのbit<2>がset => true
		bsf	Out_Sound
		bsf	Out_Tx
		call timeDelay1s
		bcf	Out_Sound
		bcf	Out_Tx
		incf	i
	_?endwhile
;------------------------------------
;	forinccnst文	初期値は変数, 終了値, 増分値 ともに定数
;		_?endfor に引数をあたえる
	_?forinccnst	i, D'5', 1
		bsf		Out_Sound
		call timeDelay05s
		bcf		Out_Sound
	_?endfor	i
;------------------------------------
;	forinc文	初期値, 終了値 ともに変数, 増分値は定数
;		_?endfor に引数をあたえる
top	movlw	1
	movwf	dat1
	movlw	3
	movwf	dat2
	_?forinc	dat1,dat2,1
		incf	W,W
	_?endfor	dat1
;------------------------------------
;	repeat文	比較値1は変数、比較値2は変数
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
;	repeat文	比較値1は変数、比較値2は定数
	_?repeat
		bsf		Out_Tx
		call	timeDelay05s
		bcf		Out_Tx
		incf	i
	_?untilcnst	i,EQ,D'5',QUIT
;------------------------------------
;	repeat文	bit test
	_?repeat
		bsf		Out_Tx
		call	timeDelay05s
		bcf		Out_Tx
		incf	i
	_?untilbit	flag,0,CL,QUIT
					;flagのbit<0>がclearであると終了
;------------------------------------
;	switch文	
top	movlw	'A'
	movwf	memo1
	movlw	'B'
	movwf	memo3
	movlw	'D'
	movwf	memo4
tp2	movlw	'A'
	_?switch
	_?c_case memo1		;変数
	_?c_casecnst 'A'	;定数
	_?case memo3
		movlw	10		
		_?break
	_?casecnst	4		;定数
		rlf	TMP,F
		rrf	TMP,F
		_?break
	_?default
		movlw	9
	_?endswitch
;------------------------------------

