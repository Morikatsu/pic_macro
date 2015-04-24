; vim:set syntax=c ts=4 sts=4 sw=4: �x��獎 Last Change:2010/06/27 22:32:15.
;	LCD Library.	Lcd_hd44780.inc
;	Header file for HITACHI HD44780 based and compatible displays
#ifndef	_LCD_HD44780_INC_INCLUDED
#define	_LCD_HD44780_INC_INCLUDED
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define LCD_DATA PORTB	;PORTB��LCD�̃f�[�^�ɐڑ�����Ă���
#define LCD_DATA_TRIS TRISB
#define	PICPORT_UPPER		;LCD�ւ̖���|�f�[�^�̏������݂Ɋ֌W����
;	PIC RB4		LCD DB4
;	PIC RB5		LCD DB5
;	PIC RB6		LCD DB6
;	PIC RB7		LCD DB7
;		��`����..PIC�̃|�[�gbit4~7��LCD�ɐڑ�
;		����`....PIC�̃|�[�gbit0~3
;		LCD�̃|�[�g�͏㑤[DB4~7]�ɌŒ�
	;+++++++++++++
#define	LCD_CTRL PORTB		;�x��
#define	LCD_CTRL_TRIS TRISB	;�x��
#define LCD_RW 1		;LCD_RW ��RB1
#define LCD_RS 2		;LCD_RS ��RB2
#define LCD_EN 3		;LCD_EN	��RB3
#define	BUSY	0x7		;Lcd DB7��busy
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

#endif
;////// eof ////////////////////////