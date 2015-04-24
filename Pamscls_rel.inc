; vim: set syntax=pic ts=4 sts=4 sw=4: last change:2012/03/18 12:09:09.
	LIST	r=dec
;=== Pamscls_rel.inc == Ver 1.5i == last change:2012/03/18 12:09:09.
	NOLIST
;	�����}�N���Q��Pamscls_internal_macro.inc�Ƃ��ēƗ������� 2010/06/18 
;		_?table��p�~�����B	11/10/05  12/3/18 ���m�F
;	���̃t�@�C���̏I����
;		Pamscls_internal_macro.inc
;		Pamscls_rel_variable.inc
;		MyUtility_rel.inc
;	���C���N���[�h���Ă���
;****************************************************
;	��ƕϐ��̊m��	 �ύX	2011/03/23 
;****************************************************
;	Pamscls���g���ꍇ���邢��eeprom��I/O���s���ꍇ�ɂ͎��̂悤�ɂ���B
;	main�̃A�Z���u���P�ʂł͈ȉ��̍s��t�������邱��
;		#include	<d:\1_PIC\MyLibrary\Pamscls_rel_variable.inc>
;	main�ȊO�̂̃A�Z���u���P�ʂł͈ȉ��̍s��t�������邱��
;		#include	<d:\1_PIC\MyLibrary\Pamscls_rel_extern_variable.inc>
;	�ǂ��炩���K���K�v�ł���B
;====================================================
#ifndef	_PAMSCLS_REL_INC_INCLUDED
#define	_PAMSCLS_REL_INC_INCLUDED
;====================================================
;	�񕪊�
;	Freg1��Freg2�̔�r
;		if .. c .. else .. endif
;		Freg1,cnd,Freg2,logic	�\��A
;
;	Freg�ƒ萔�̔�r
;		ifcnst .. c_cnst .. else .. endif
;		Freg,cnd,CONST,logic	�\��A
;
;	Freg�̃r�b�g�e�X�g
;		ifbit .. c_bit .. else .. endif
;		Freg,bit,cnd,logic		�\��B
;	
;   if�̕�������(c��, [c_cnst, c_bit])�w��\
;
;	if������break��,continue�����g���ƃ��[�v�\��[for,while,repeat]
;	����E�o�ł���
;		�A���Aif���̓���q�͕s��(�P����if���̂�)
;--------------------
;	�J��Ԃ�
;	for�̑����l�͒萔���g��
;		forinc|fordec .. continue .. break .. endfor
;
;	�J��Ԃ�
;	for�̋��E�l�ɒ萔���g���ꍇ�� forinccnst | fordeccnst����
;	�g��
;		forinccnst|fordeccnst .. endfor
;--------------------
;	�J��Ԃ�
;		while .. continue .. break .. endwhile
;
;	�J��Ԃ�
;	while�̋��E�l�ɒ萔���g���ꍇ�� whilecnst �����g��
;		whilecnst .. continue .. break .. endwhile
;
;	�J��Ԃ�
;	while�̋��E�l��bit test���g���ꍇ�� whilebit �����g��
;		whilebit .. continue .. break .. endwhile
;--------------------
;	�J��Ԃ�
;		repeat .. continue .. break .. until
;
;	�J��Ԃ�
;	until�̋��E�l�ɒ萔���g���ꍇ�� untilcnst �����g��
;		repeat .. continue .. break .. untilcnst
;
;	�J��Ԃ�
;	until�̋��E�l��bit test���g���ꍇ�� untilbit �����g��
;		repeat .. continue .. break .. untilbit
;
;	�J��Ԃ�[�������[�v]	09/11/10 �ǉ�
;	�������[�v�̏ꍇ��until�̑���� always �����g��
;		repeat .. always	�����Ȃ�
;		���[�v����̒E�o�ɂ� goto ���� break �����g��
;--------------------
;	������
;	Wreg�ƕϐ�|�萔�̔�r�ɂ�镪��
;		switch .. c_case .. case .. break .. default .. endswitch
;		�ϐ��ɂ�c_case, case�����g�� 
;		�萔�ɂ�c_casecnst, casecnst�����g��
;		_?c_case/_?c_casecnst����OR�ł���A_?case/_?casecnst����QUIT�ł���
;--------------------
;	_?c( freg�p )��_?c_bit( bit test�p ) _?c_cnst( �萔�p )
;	�͍��݂��\
;====================================================
;	��ƕϐ��̊m��	 �ύX
;
;	��ƕϐ��Ƃ��� _?temp1�`7���g��[for��,switch�� Pamscls.inc]
;	��ƕϐ��Ƃ��� _?temp0���g��[subwl��,swapff�� MyUtility.inc]
;	relocatable�Ȃ̂ŕϐ��̈ʒu���Œ肵�Ă��Ȃ�
;	�ϐ��ɃA�N�Z�X����ۂ�banksel���g���΂悢
;
;	�g�p�ł��� bank�͊echip�ɂ��قȂ�B
;	12F629/675......... bank0, bank1
;	16F627A/628A/648A.. bank0, bank1, bank2, bank3
;	16F84/84A.......... bank0, bank1
;	16F87/88...........   ibid
;		=============================================
;	Timer_rel.asm���g���Ƃ����� #define	_?FREQ XX ���K�v�ł���
;		Timer�p�ϐ���(_?BTMMEMO - 0x0f + d'4' )����3byte���g��
;		Timer_rel.asm�Œ�`���Ă���B
;	Eeprom���g���Ƃ��Ɏg�p����ϐ�_?romadrs��
;		Eeprom_rel.asm���Œ�`���Ă���B
;====================================================
;   Macro variable INIT
;====================================================
	variable	_?nstlv	=	0	;Nesting level
	variable	_?curlb	=	0	;Current label index
	variable	_?dolv	=	0	;Do nest level
	variable	_?atrf1	=	0	;Attr 1.
	variable	_?atrf2	=	0	;Attr 2.
	variable	_?atrf3	=	0	;Attr 3.
	variable	_?atrf4	=	0	;Attr 4.
	variable	_?atrf5	=	0	;Attr 5 forinc(0), fordec(1)�̋��
	variable	_?contc	=	0	;condition continue? 
	variable	_?cscas	=	0	;case count
	variable	_?nstcs	=	0	;case group count

	constant	EQ	=	0
	constant	NE	=	1
	constant	GE	=	2
	constant	GT	=	3
	constant	LE	=	4
	constant	LT	=	5
	constant	OR	=	1
	constant	AND	=	2
	constant	QUIT=	0
	constant	CL	=	10	;_?ifbit/_?whilebit/_?untilbit�̂���
	constant	ST	=	11
;****************************************************
;   IF		freg�Ԃ̔�r	09/05/23
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
	_?setbb	#v(_?nstlv),#v(_?trulb);trulb��stack
_?faulb=_?curlb+1
	_?seteb #v(_?nstlv),#v(_?faulb);faulb��stack
_?endlb=_?curlb+2			;09/05/24
	_?setex	#v(_?nstlv),#v(_?endlb)	;if block�̏o�����x����stack
_?curlb=_?curlb+2
	_?cndck_vari	_?data1,_?data2,_?cnd,_?logic
	endm
;****************************************************
;   IFCNST		freg�ƒ萔�̔�r	09/05/27	
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
	_?setbb	#v(_?nstlv),#v(_?trulb);trulb��stack
_?faulb=_?curlb+1
	_?seteb #v(_?nstlv),#v(_?faulb);faulb��stack
_?endlb=_?curlb+2			;09/05/24
	_?setex	#v(_?nstlv),#v(_?endlb)	;if block�̏o�����x����stack
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
	_?setbb	#v(_?nstlv),#v(_?trulb);trulb��stack
_?faulb=_?curlb+1
	_?seteb #v(_?nstlv),#v(_?faulb);faulb��stack
_?endlb=_?curlb+2			;09/05/24
	_?setex	#v(_?nstlv),#v(_?endlb)	;if block�̏o�����x����stack
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
	_?gexjp	#v(_?nstlv)	;ex[endif�̏o�����x��]�֍s��09/05/24
	_?exteb	#v(_?nstlv)	;ELSE�̓�������x�������09/05/24
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
	if((_?atrf3 % 2)==0);else�����Ȃ��A����else�̓����
	_?gexjp	#v(_?nstlv)	;ex[endif�̏o�����x��]�֍s��09/05/24
	_?exteb	#v(_?nstlv)	;ELSE�̓�������x�������09/05/24
	endif
	_?extex	#v(_?nstlv)	;�o�����x�������09/05/24
_?curlb++;07/07/14
_?atrf1	=(_?atrf1 >> 1)	;Attr 1
_?atrf2	=(_?atrf2 >> 1)	;Attr 2
_?atrf3	=(_?atrf3 >> 1)	;Attr 3
_?atrf4	=(_?atrf4 >> 1)	;Attr 4
_?atrf5	=(_?atrf5 >> 1)	;Attr 5
_?nstlv--
	endm
;**************************************************
;  CNDCK1	10/02/22 until�̃o�O
;	_?contc�͘_�����Z�q�ɂ��U�蕪���t���O
;	����������bug�C��	07/06/23
;**************************************************
_?cndck1 macro  _?data1,_?data2,_?cnd,_?logic
	if(_?logic==OR)	;///// or //////
_?contc	=	OR;1
_?curlb++
	_?genlb	#v(_?curlb);���̃u���b�N�̓�������x�������
		_?genjp	#v(_?curlb+2);goto [curlb+1]�����
	_?genlb	#v(_?curlb+1);���̃u���b�N�̒��ԃ��׃������
		_?genjp #v(_?curlb+4)
	_?genlb #v(_?curlb+2);���x��[]�����
_?curlb++
;	messg"End of OR"
	else
	if(_?logic==AND)	;///// and //////////
_?contc	=	AND;2
_?curlb++
	_?genlb	#v(_?curlb);���̃u���b�N�̓�������x�������
		_?genjp #v(_?curlb+3)
	_?genlb	#v(_?curlb+1);���̃u���b�N�̒��ԃ��׃������
		_?genjp #v(_?curlb+2);goto (�o��)�����
	_?genlb	#v(_?curlb+2);���̃u���b�N�̏o�����x�������
_?curlb++
;	messg"End of AND"
	else
	if(_?logic==QUIT)	;///// quit ///// AND,OR���Ȃ��̂ł���ł����
_?contc	=	QUIT;0
;_?curlb++	;@@@@
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==1)&&((_?atrf4 % 2)==1))
						;****������until:QUIT�̏ꍇ
_?curlb++	;@@@@
		_?genlb	#v(_?curlb);until:QUIT�̓�������x��������[10/02/22 ���̍s���폜]
			_?grbjp #v(_?dolv);goto top
		_?genlb	#v(_?curlb+1);���̃u���b�N�̒��ԃ��׃������
			_?grejp #v(_?dolv);goto end
		_?extre #v(_?dolv);eb(_?nst)���x��������
_?curlb++
_?nstlv--
_?dolv--
_?atrf1	=	_?atrf1 >> 1;Attr 1;07/07/11�����Ɉړ�
_?atrf2	=	_?atrf2 >> 1;Attr 2
_?atrf3	=	_?atrf3 >> 1;Attr 3
_?atrf4	=	_?atrf4 >> 1;Attr 4
_?atrf5	=	_?atrf5 >> 1;Attr 5
;	messg"End until QUIT"
	else	;==3..until
;	endif;==3..until
	if(((_?atrf1 % 2)==1)&&((_?atrf3 % 2)==0)&&((_?atrf4 % 2)==1))
						 ;****������while:QUIT�̏ꍇ
_?curlb++
	_?genlb	#v(_?curlb);while:QUIT�̓�������x��������
		_?gwejp	#v(_?dolv);�o���֍s��
	_?genlb	#v(_?curlb+1);���̃u���b�N�̒��ԃ��׃������
		_?gwtjp #v(_?dolv);���s���̓�����ɍs��
	_?extwt #v(_?dolv);���s���̓�������x�������
_?curlb++	;@@@@@@10/03/09
;	messg"End while QUIT"
	else	;==3..while
;	endif;==3..while
	if(((_?atrf1 % 2)==1)&&((_?atrf4 % 2)==0))
		                  ;****������if:QUIT�̏ꍇ
_?curlb++
	_?genlb #v(_?curlb);if:QUIT�̓�������x�������
		_?genjp #v(_?faulb);goto (faulb)�����
	_?genlb	#v(_?curlb+1);���̃u���b�N�̒��ԃ��׃������
		_?genjp #v(_?trulb);goto (trulb)�����
	_?genlb #v(_?trulb);trulb���x�������
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
;	2007/06/23�@�C��
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
;	2007/06/23�@�C��
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
	_?setrb #v(_?dolv),#v(_?faulb);�������x����stack
_?trulb=_?curlb+1
	_?setre #v(_?dolv),#v(_?trulb)	;���[�v�o����stack
	_?extrb #v(_?dolv);���[�v�����쐬
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
;	_?genlb	#v(_?curlb);until:QUIT�̓�������x��������[10/02/22���̍s���폜]
		_?grbjp	#v(_?dolv)
	_?genlb	#v(_?curlb+1);���̃u���b�N�̒��ԃ��׃������
		_?grejp #v(_?dolv);goto end
	_?extre #v(_?dolv);re(_?nst)���x��������
_?curlb++
_?nstlv--
_?dolv--
_?atrf1	=	_?atrf1 >> 1;Attr 1;07/07/11�����Ɉړ�
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
	_?setwb #v(_?dolv),#v(_?curlb);���[�v�������x����stack
_?curlb++
_?trulb=_?curlb
	_?setwt #v(_?dolv),#v(_?trulb);���s���������x����stack
_?curlb++
_?faulb=_?curlb
	_?setwe #v(_?dolv),#v(_?faulb);���[�v�o�����x����stack
	_?extwb	#v(_?dolv);���[�v�������x�����쐬
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
	_?setwb #v(_?dolv),#v(_?curlb);���[�v�������x����stack
_?curlb++
_?trulb=_?curlb
	_?setwt #v(_?dolv),#v(_?trulb);���s���������x����stack
_?curlb++
_?faulb=_?curlb
	_?setwe #v(_?dolv),#v(_?faulb);���[�v�o�����x����stack
	_?extwb	#v(_?dolv);���[�v�������x�����쐬
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
	_?setwb #v(_?dolv),#v(_?curlb);���[�v�������x����stack
_?curlb++
_?trulb=_?curlb
	_?setwt #v(_?dolv),#v(_?trulb);���s���������x����stack
_?curlb++
_?faulb=_?curlb
	_?setwe #v(_?dolv),#v(_?faulb);���[�v�o�����x����stack
	_?extwb	#v(_?dolv);���[�v�������x�����쐬
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
	_?gwbjp #v(_?dolv);goto ���[�v����
	_?extwe #v(_?dolv);�o�����x�������
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
;	_?data2(���E�l)�͕ϐ����g��
;	_?data3(�����l)�͒萔���g�����Ƃɂ����B
;	�����skpc[skip on carry]���g�����Ƃɂ����B
;***************************************************
_?forinc	macro	_?data1,_?data2,_?data3
_?dolv++	;Do nest level
_?nstlv++	;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?forinc"
	endif
_?curlb++	;Current label
	banksel	_?temp#v(_?nstlv)
	_?movlf _?data3,_?temp#v(_?nstlv)	;�x�� �����l��ۑ�
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)��stack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)��stack
	_?extfb	#v(_?dolv) ;������̃��x�������
	movf	_?data2,w	;data2[var] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnpls	;09/05/27���ʂ���(��|zero)�ł����for�̎��s����
	_?gfejp #v(_?dolv)	;goto (�o��)���쐬
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
;	_?data2(���E�l)�͒萔���g��
;	_?data3(�����l)�͒萔���g�����Ƃɂ����B
;	�����skpc[skip on carry]���g�����Ƃɂ����B
;***************************************************
_?forinccnst	macro	_?data1,_?data2,_?data3
_?dolv++	;Do nest level
_?nstlv++	;Nesting level
	if(_?nstlv > 7)
		error "Nest level too deep! _?forinccnst"
	endif
_?curlb++	;Current label 
	banksel	_?temp#v(_?nstlv)
	_?movlf _?data3,_?temp#v(_?nstlv)	;�x�� �����l��ۑ�
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)��stack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)��stack
	_?extfb	#v(_?dolv) ;������̃��x�������
	movlw	_?data2		;data2[cnst] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnpls	;09/05/27���ʂ���(��|zero)�ł����for�̎��s����
	_?gfejp #v(_?dolv)	;goto (�o��)���쐬
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
;	_?data2(���E�l)�͕ϐ����g��
;	_?data3(�����l)�͒萔���g�����Ƃɂ����B
;***************************************************
_?fordec	macro	_?data1,_?data2,_?data3
_?dolv++	;Do nest level
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?fordec"
	endif
_?curlb++	;Current label Ndx
	banksel	_?temp#v(_?nstlv)
	_?movlf _?data3,_?temp#v(_?nstlv);������stack
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)��stack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)��stack
	_?extfb	#v(_?dolv) ;������̃��x�������
	movf	_?data2		;data2[var] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnneg	;09/05/26���ʂ���(��|zero)�ł����for�̎��s����
	_?gfejp #v(_?dolv)	;goto (�o��)���쐬
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
;	_?data2(���E�l)�͒萔���g��
;	_?data3(�����l)�͒萔���g�����Ƃɂ����B
;***************************************************
_?fordeccnst	macro	_?data1,_?data2,_?data3
_?dolv++			;Do nest level
_?nstlv++
	if(_?nstlv > 7)
		error "Nest level too deep! _?fordeccnst"
	endif
_?curlb++			;Current label Ndx
	banksel	_?temp#v(_?nstlv)
	_?movlf _?data3,_?temp#v(_?nstlv);������stack
	_?setfb #v(_?dolv),#v(_?curlb);fb(nst)��stack
_?curlb++
	_?setfe #v(_?dolv),#v(_?curlb);fe(nst)��stack
	_?extfb	#v(_?dolv) ;������̃��x�������
	movlw	_?data2		;data2[cnst] => Wreg
	subwf	_?data1,w	;data1-data2
	skpnneg	;09/05/26���ʂ���(��|zero)�ł����for�̎��s����
	_?gfejp #v(_?dolv)	;goto (�o��)���쐬
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
;  ENDFOR	09/05/26  fordec�̎��A�o�O���C��
;***************************************************
_?endfor	macro	_?data
	if(((_?atrf1 % 2)==1)||((_?atrf4 % 2)==1))
	  error "Can't find _?for* statement in this block"
	endif
	banksel	_?temp#v(_?nstlv)
 	movf	_?temp#v(_?nstlv),w	;dat3==>Wreg �����l�𕜌�
	if((_?atrf5 % 2)==0)
		addwf	_?data,f;data1+data3==>data1 forinc
	else
		subwf	_?data,f;data1-data3==>data1 fordec
	endif
	_?gfbjp #v(_?dolv)	;���[�v������֔��
	_?extfe #v(_?dolv)	;�o���̃��x�������
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
	banksel	_?temp#v(_?nstlv)
	movwf	_?temp#v(_?nstlv)	;04/12/12 Wreg��ۑ�
_?curlb++
	_?seteb #v(_?nstlv),#v(_?curlb)	;�o���̃��x������������
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
;   CASE	10/02/23 �x��
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
;	messg"�ۑ����Ă���Wreg�𕜌�"
	banksel	_?temp#v(_?nstlv)
	movf	_?temp#v(_?nstlv),W	;�ۑ����Ă���Wreg�𕜌� 10/02/23
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
;   C_CASE	10/02/23 �x��
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
;	messg"�ۑ����Ă���Wreg�𕜌�"
	banksel	_?temp#v(_?nstlv)
	movf	_?temp#v(_?nstlv),W	;�ۑ����Ă���Wreg�𕜌� 10/02/23
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
	_?gsnjp #v(_?nstcs);����case���֍s��
_?curlb++
	endm
;**************************************************
;   CASECNST	10/02/23 �x��
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
	_?gsnlb #v(_?svcs#v(_?nstlv));_cs(cacas)�����
;	messg"�ۑ����Ă���Wreg�𕜌�"
	banksel	_?temp#v(_?nstlv)
	movf	_?temp#v(_?nstlv),W	;�ۑ����Ă���Wreg�𕜌� 10/02/23
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
;   C_CASECNST	10/02/23	�x��
;*************************************************
_?c_casecnst	macro	_?const
	if(((_?atrf1 % 2)==0)&&((_?atrf4 % 2)== 0)) ;07/07/02
	  error "Can't find _?switch statement in this block"
	endif
_?curlb++
_?cscas++
_?nstcs=_?nstlv*100+_?cscas;11  14
	_?gsnlb #v(_?svcs#v(_?nstlv));_cs(cacas)�����
;	messg"�ۑ����Ă���Wreg�𕜌�"
	banksel	_?temp#v(_?nstlv)
	movf	_?temp#v(_?nstlv),W	;�ۑ����Ă���Wreg�𕜌� 10/02/23
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
	_?gsnjp #v(_?nstcs);����case���֍s��
_?curlb++
	endm
;**************************************************
;   CONTINUE  while/repeat/for	10/03/06
;	���݂̃��[�v�\��[repeat, while, for]�̐擪�ɍs��
;	continue���̓��[�v�\������if������Ďg����
;		�A���Aif���̓���q�͕s��(�P����if���̂�)
;**************************************************
_?continue	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?continue"
	endif
	if((_?atrf1 % 2)==1)&&((_?atrf4 %2)==0)		;if
;		messg"continue in if statment"
	if((((_?atrf1>>1) % 2)==0)&&(((_?atrf2>>1) % 2)==1))	;for
;		messg"continue to top for" ;continue��for�Ŏg���Ă���
		_?gfbjp(_?dolv);for top
	endif
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==0)&&(((_?atrf4>>1) % 2)==1))
;		messg"continue to top while"
		_?gwbjp #v(_?dolv);while������֔��
	endif
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==1)&&(((_?atrf4>>1) % 2)==1))
;		messg"continue to top repeat"
		_?grbjp #v(_?dolv);until/always������֔��
	endif
	endif
	endm
;**************************************************
;   BREAK	switch  while/repeat/for	10/03/06
;	���݂̃��[�v�\��[repeat/always, while, for]��E�o����ꍇ��
;	break��[���݂̃��[�v�\����E�o����]��switch�����Ŏg����ꍇ������
;	���[�v�\�����ł�if������Ďg����
;		�A���Aif���̓���q�͕s��(�P����if���̂�)
;**************************************************
_?break	macro
	if(_?contc != 0)
		error "Illegal use of macro sequence _?break"
	endif
	if((_?atrf1 % 2)==0)&&((_?atrf4 % 2)==1)	;switch
		if((_?atrf2 % 2)==0)	;07/07/03
			error "Still Continue _?case_c block"
		else
			_?gebjp #v(_?nstlv);endswitch�o���֔��
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
		_?gwejp #v(_?dolv);while�o���֔��
	endif
	if((((_?atrf1>>1) % 2)==1)&&(((_?atrf3>>1) % 2)==1)&&(((_?atrf4>>1) % 2)==1))
;		messg"break exit until/always"	;10/03/06
		_?grejp #v(_?dolv);until/always�o���֔��
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
	_?gsnlb #v(_?nstcs-1)	;default�̓�������x�����쐬����
_?atrf3++	;default�傪���邵�邵	
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
	if((_?atrf3 % 2)-1!=0)	;default�傪�Ȃ��ꍇ ���̓��������
		_?gsnlb #v(_?nstcs-1)	;default�̓�������x�����쐬����
	endif
	_?exteb #v(_?nstlv)	;switch�̏o�����x�������
_?atrf1	=	_?atrf1 >> 1	;Attr 1
_?atrf2	=	_?atrf2 >> 1	;Attr 2
_?atrf3	=	_?atrf3 >> 1	;Attr 3
_?atrf4	=	_?atrf4 >> 1	;Attr 4
_?atrf5	=	_?atrf5 >> 1	;Attr 5
_?nstlv--
_?dolv--
	endm
;*********************************************************
	include	<c:\Users\Tora\1_PIC\Mylibrary\Pamscls_internal_macro.inc> ;�����}�N���Q
	include	<c:\Users\Tora\1_PIC\Mylibrary\Pamscls_rel_variable.inc> ;��ƕϐ��̊m��
	include	<c:\Users\Tora\1_PIC\MyLibrary\MyUtility_rel.inc>
;*********************************************************
#endif		;_PAMSCLS_REL_INC_INCLUED
;*********************************************************
	LIST