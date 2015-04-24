; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2012/03/18 14:34:41.
;	Lcd_abs.asm		これはabsolute用である
;	http://picbegin.hp.infoseek.co.jp/proj5/p5step80.html
;	hardの設定はヘッダーファイル[Lcd_hd44780.inc]を変更すことにより可能である
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;	list p=16f648A  r=dec, mm=on, st=off ; list directive to define processor
;	#include <p16F648A.inc>     ; processor specific variable definitions
;	errorlevel -302             ; suppress message 302 from list file
;	#include	<d:\1_PIC\MyLibrary\Pamscls_abs.inc>	;absolute
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	#include	<d:\1_PIC\MyLibrary\Lcd_header.inc>
						;Lcd_header.incはabs, rel共通
;***** 変数定義 **************************************
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
;				;プログラムはここから始まる
;******************************************************
;		Lcd Control Library
;	Lcd_clear, Lcd_home, Lcd_busy, Lcd_init, 
;	Lcd_emode Set entry mode
;	Lcd_dmode Configure display mode
;	Lcd_cmode Configure cursor mode
;	Lcd_fmode Configure function set
;	Lcd_ddram Set DDRAM address
;		各OptionはWregに入れてからcallする
;	Lcd_cmd   Send _?lcd_temp to Lcd
;		命令はWregに入れてからcallする
;	Lcd_dat   Send a chr to Lcd
;		送るデータはWregに入れてからcallする
;	Lcd_out   Send string
;		送るデータの先頭はWregに入れてからcallする
;	Lcd_loc   Send starting loc
;	ヘッダーファイルで PICPORT_UPPERを定義しておく
;		定義した..bit4~7がLCDに接続
;		未定義....bit0~3
;	LcdのDBは上側(4..7)接続とする[固定]
;****************************************
;  LCD Clear operation
;  使い方          call    Lcd_Clear
;****************************************
Lcd_clear:
	movlw	0x01
	call	Lcd_cmd
	movlw	1
	call	Delay_10ms	;最小1.6ms
	return
;****************************************
;  LCD Home operation
;  使い方          call    Lcd_Home
;****************************************
Lcd_home:
	movlw	0x02
	call	Lcd_cmd
	movlw	1
	call	Delay_10ms	;最小1.6ms
	return
;****************************************
;	Lcd_loc
;	書き始めの位置を決める
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
;	lcdに文字列を書く
;	書き始めの位置は現在の位置とする
;	string => 文字列の先頭	文字列の終わりは00
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
;	LCDがreadyになるまで待機する 
;  使い方          call    Lcd_busy
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
	bcf		LCD_CTRL,LCD_EN	;LCDをdisableとする
	bcf		LCD_CTRL,LCD_RS	;制御モードにする
	bsf		LCD_CTRL,LCD_RW	;読み込みモードにする
	;++++++++++
#ifdef	PICPORT_UPPER	;+++++ upper case +++++
	_?selbank1
	bsf		LCD_DATA_TRIS,4		;上側4bitのみ入力とする
	bsf		LCD_DATA_TRIS,5
	bsf		LCD_DATA_TRIS,6
	bsf		LCD_DATA_TRIS,7
	_?selbank0
	bsf		LCD_CTRL,LCD_EN	;LCDを動作させる
	movlw	1
	call	Delay_100us
				;+++++ LCDの状態が4bitに分けて出力される
	_?ifbit	LCD_DATA,7,ST,QUIT	;RB4~7に接続されているので bit7はLCDのbitであり
		movlw	1				;PICではRB7となる
		call	Delay_100us		;1msの待機
		goto	Lcd_busy			
	_?endif

	bcf		LCD_CTRL,LCD_EN	;LCDの動作停止;
	movlw	1
	call	Delay_100us

	bsf		LCD_CTRL,LCD_EN	;LCDの下側4bitを読みとばす
	movlw	1
	call	Delay_100us
	_?selbank1
	bcf		LCD_DATA_TRIS,4		;上側4bitのみ出力とする
	bcf		LCD_DATA_TRIS,5
	bcf		LCD_DATA_TRIS,6
	bcf		LCD_DATA_TRIS,7
	_?selbank0
#else			;+++++ lower case +++++
	_?selbank1
	bsf		LCD_DATA_TRIS,0		;下側4bitのみ入力とする
	bsf		LCD_DATA_TRIS,1
	bsf		LCD_DATA_TRIS,2
	bsf		LCD_DATA_TRIS,3
	_?selbank0
	bsf		LCD_CTRL,LCD_EN	;LCDを動作させる
	movlw	1
	call	Delay_100us
				;+++++ LCDの状態が4bitに分けて出力される
	_?ifbit	LCD_DATA,3,ST,QUIT	;RB0~3に接続されているので bit7はLCDのbitであり
		movlw	1				;PICではRB3となる
		call	Delay_100us		;1msの待機
		goto	Lcd_busy			
	_?endif

	bcf		LCD_CTRL,LCD_EN		;LCDの動作停止
	movlw	1
	call	Delay_100us

	bsf		LCD_CTRL,LCD_EN	;LCDの下側4bitを読みとばす
	movlw	1
	call	Delay_100us
	bcf		LCD_CTRL,LCD_EN	;
	_?selbank1
	bcf		LCD_DATA_TRIS,0		;下側4bitのみ出力とする
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
; 使い方          call    Lcd_init
;	参考:spectrum
;****************************************
Lcd_init:
	clrf	_?lcd_cmode	;*modeの状態の保存場所
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
#ifdef	PICPORT_UPPER	;++++++ PICのポートは上側の場合 +++++++++++++++
	MOVLW	h'0F'		;LCD_DATAの下位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	h'30'		;上位４ビットに'３'をセット
		;0011(8bit mode命令の上4bit)をRB4..7に送るため
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;ファンクションセット（１回目）
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	h'0F'		;LCD_DATAの下位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	h'30'		;上位４ビットに'３'をセット
		;0011(8bit mode命令の上4bit)をRB4..7に送るため
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;ファンクションセット（２回目）
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	h'0F'		;LCD_DATAの下位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	h'30'		;上位４ビットに'３'をセット
		;0011(8bit mode命令の上4bit)をRB4..7に送るため
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;ファンクションセット（３回目）
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	h'0F'		;LCD_DATAの下位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	h'20'		;４ビットモード
		;0010(4bit mode命令の上4bit)をRB4..7に送るため
	MOVWF	LCD_DATA		;
	BSF	LCD_CTRL,LCD_EN		;設定
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	10
	call	Delay_100us
#else	;++++++++ lowerの場合 ++++++++++++++++++++++++++
	MOVLW	0F0h		;LCD_DATAの上位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	03h		;下位４ビットに'３'をセット
		;0011(8bit mode命令の上4bit)をRB0..3に送るため
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;ファンクションセット（１回目）
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	0F0h		;LCD_DATAの上位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	03h		;下位４ビットに'３'をセット
		;0011(8bit mode命令の上4bit)をRB0..3に送るため
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;ファンクションセット（２回目）
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	0F0h		;LCD_DATAの上位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	03h		;下位４ビットに'３'をセット
		;0011(8bit mode命令の上4bit)をRB0..3に送るため
	MOVWF	LCD_DATA
	BSF	LCD_CTRL,LCD_EN		;ファンクションセット（３回目）
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	50
	call	Delay_100us

	MOVLW	0F0h		;LCD_DATAの上位４ビットを
	ANDWF	LCD_DATA,W		;取り出す（変更しないように）
	IORLW	02h		;４ビットモード
		;0010(4bit mode命令の上4bit)をRB0..3に送るため
	MOVWF	LCD_DATA		;
	BSF	LCD_CTRL,LCD_EN		;設定
	NOP
	BCF	LCD_CTRL,LCD_EN
	movlw	10
	call	Delay_100us
#endif	 ;++++++++++++++++++++++++++++++++++++++++

	movlw	1
	call	Delay_10ms	;Wait for more than 30ms

				;**** これ以降でLcd_busyが使える	

	call	Lcd_clear	;Clear LCD
	
	movlw	INC_CURSOR	;0x02
	call	Lcd_emode	;Set entry mode
				;カーソル右移動とする
	movlw	IFACE_4BIT	;4bitに固定する 0x00
	iorlw	DUAL_LINE	;   0x08	==> 0x08
	call	Lcd_fmode	;Select Function Set
				;4bit mode, 2行表示, 7dotとする	
	movlw	DISPLAY_ON
	iorlw	CURSOR_OFF
	call	Lcd_dmode	;Configure display mode
				;表示on, cursor offとする
	return
;*********************************************
;	Lcd_cmd
;	命令データをLcdへ送る
;		命令はWregに入れておく
;  使い方   movlw   _?lcd_temp =>_?lcd_tempがWregに入る
;			call    Lcd_cmd
;*********************************************
Lcd_cmd:	
	movwf	_?lcd_temp			;命令を保存

	call	Lcd_busy	;Lcdがreadyになるまでここで待つ

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
	bcf	LCD_CTRL,LCD_RW		;書き込みモードにする
	bcf	LCD_CTRL,LCD_RS		;コマンドモードにする

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
;	Wregに入っているデータをLcdへ送る
;		一文字だけ
;	8bitを上側4bitと下側4bitに分けて送る
;		上 => 下 の順
; 使い方	movlw   _?lcd_temp	=> _?lcd_tempがWregに入る
;			call    Lcd_dat
;*********************************************
Lcd_dat:
	movwf	_?lcd_temp			;送るべき値を保存する

	call	Lcd_busy	;Lcdがreadyになるまでここで待つ

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
	bcf	LCD_CTRL,LCD_RW		;書き込みモードにする
	bsf	LCD_CTRL,LCD_RS		;データモードとする

#ifdef	PICPORT_UPPER
	call	Lcd_wr_upper_lower
#else
	call	Lcd_wr_lower_upper
#endif
	return
;*********************************************
Lcd_wr_upper_lower:
	movlw	0x0f
	andwf	LCD_DATA,f	;データバスの上側をクリヤ

	MOVF    _?lcd_temp,w ;命令をWregに入れる
	ANDLW   0xF0            ;上位4bitとする
	iorwf	LCD_DATA,f	;PORTのupperに出力(PORTのlowerはそのまま)

	BSF     LCD_CTRL,LCD_EN ;LCDにデータを書き込む
	nop					;Enableの最短時間450ns
	nop
	BCF     LCD_CTRL,LCD_EN

	movlw	0x0f
	andwf	LCD_DATA,f	;データバスの上側をクリヤ

	SWAPF   _?lcd_temp,w	;命令のnibbleを入れ替え、Wregに入れる
	ANDLW   0xF0        ;命令の下位4bitがWregのupperに入っている
	iorwf	LCD_DATA,f	;PORTのupperに出力(PORTのlowerはそのまま)
	BSF     LCD_CTRL,LCD_EN ;LCDにデータを書き込む
	nop					;Enableの最短時間450ns
	nop
	BCF     LCD_CTRL,LCD_EN
	RETURN
;***********************************************
Lcd_wr_lower_upper:
	movlw	0xf0
	andwf	LCD_DATA,f	;データバスの下側をクリヤ

	SWAPF   _?lcd_temp,w	;命令のnibbleを入れ替え、Wregに入れる

	ANDLW   0x0f            ;下位4bitとする
	iorwf	LCD_DATA,f	;PORTのlowerに出力(PORTのupperはそのまま)
	BSF     LCD_CTRL,LCD_EN ;LCDにデータを書き込む
	nop					;Enableの最短時間450ns
	nop
	BCF     LCD_CTRL,LCD_EN

	movlw	0xf0
	andwf	LCD_DATA,f	;データバスの下側をクリヤ

	movf	_?lcd_temp,w	;命令をWregへ入れる
	ANDLW   0x0f            ; Get lower nibble
	iorwf	LCD_DATA,f	;PORTのlowerに出力(PORTのupperはそのまま)
	BSF     LCD_CTRL,LCD_EN ;LCDにデータを書き込む
	nop					;Enableの最短時間450ns
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
