; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2012/03/18 14:26:11.
;	LCD Library.	Lcd_header.inc
;	このファイルはabs, rel共通
;	Header file for HITACHI HD44780 based and compatible displays
#ifndef	_LCD_HEADER_INC_INCLUDED
#define	_LCD_HEADER_INC_INCLUDED
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define LCD_DATA PORTB		;PORTBがLCDのデータに接続されている
#define LCD_DATA_TRIS TRISB
#define	PICPORT_UPPER		;LCDへの命令|データの書き込みに関係する
;	PIC RB4		LCD DB4
;	PIC RB5		LCD DB5
;	PIC RB6		LCD DB6
;	PIC RB7		LCD DB7
;		定義した..PICのポートbit4~7がLCDに接続
;		未定義....PICのポートbit0~3
;		LCDのポートは上側[DB4~7]に固定
	;+++++++++++++
#define	LCD_CTRL PORTB		;堀野
#define	LCD_CTRL_TRIS TRISB	;堀野
#define LCD_RW 1		;LCD_RW はRB1
#define LCD_RS 2		;LCD_RS はRB2
#define LCD_EN 3		;LCD_EN	はRB3
#define	BUSY	0x7		;Lcd DB7はbusy
;+++++ Entry mode variables
#define INC_CURSOR 0x02
#define DEC_CURSOR 0x00
#define SHIFT_ON 0x01

;+++++ Display control variables
#define DISPLAY_ON 0x04
#define DISPLAY_OFF 0x00
#define CURSOR_ON 0x02
#define CURSOR_OFF 0x00
#define BLINK_ON 0x01
#define	BLINK_OFF	0x00

;+++++ Cursor move variables
#define SHIFT_DISP 0x08
#define SHIFT_RIGHT 0x04
#define SHIFT_LEFT 0x00

;+++++ Function set variables
#define IFACE_8BIT 0x10
#define IFACE_4BIT 0x00
#define DUAL_LINE 0x08
#define	SNGL_LINE 0x00
#define DOTS_5X10 0x04
#define DOTS_5X7 0x00

;+++++ DDRAM locations
#define FIRST_LINE 0x00
#define SECOND_LINE 0x40

#endif ;////// eof ////////////////////////
#endif	_LCD_HEADER_INC_INCLUDED
