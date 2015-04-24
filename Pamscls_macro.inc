; vim:set syntax=pic ts=4 sts=4 sw=4: �x��獎 Last Change:2010/06/18 08:35:35.
;	Pamscls_sub.inc		Ver 1.0
;	���̃t�@�C����Pamscls_abs.inc|Pamscls_rel.inc��include�����
;====================================================
#ifndef	_PAMSCLS_SUB_INC_INCLUDED
#define	_PAMSCLS_SUB_INC_INCLUDED
;====================================================
;===== INTERNAL MACROS ===========
;*******************************
;   EXTFB (internal macro) 07/07/11
;	fb (for begin block) ���x�������
;********************************
_?extfb macro   _?lvl
    _?genlb (_?fb#v(_?lvl))
	endm
;*******************************
;   EXTFE (internal macro) 07/07/11
;	fe (for end block) ���x�������
;********************************
_?extfe macro   _?lvl
    _?genlb (_?fe#v(_?lvl))
	endm
;*******************************
;   EXTLB (internal macro)
;	lb  ���x�������
;********************************
_?extlb macro   _?lvl
    _?genlb (_?lb#v(_?lvl))
	endm
;********************************
;	EXTBB  07/06/25
;	bb  ���x�������
;********************************
_?extbb	macro	_?lvl
	_?genlb	(_?bb#v(_?lvl))
	endm
;********************************
;   EXTEB (internal macro)
;	eb  ���x�������
;********************************
_?exteb    macro   _?lvl
    _?genlb (_?eb#v(_?lvl))
	endm
;********************************
;   EXTEX (internal macro)
;	ex  ���x�������	09/05/24
;********************************
_?extex    macro   _?lvl
    _?genlb (_?ex#v(_?lvl))
	endm
;********************************
;   EXTWB (internal macro)
;	wb  ���x�������	09/11/10
;	while�p
;********************************
_?extwb    macro   _?lvl
    _?genlb (_?wb#v(_?lvl))
	endm
;********************************
;   EXTWE (internal macro)
;	we  ���x�������	09/11/10
;	while�p
;********************************
_?extwe    macro   _?lvl
    _?genlb (_?we#v(_?lvl))
	endm
;********************************
;   EXTWT (internal macro)
;	wt  ���x�������	09/11/10
;	while�p
;********************************
_?extwt    macro   _?lvl
    _?genlb (_?wt#v(_?lvl))
	endm
;********************************
;   EXTRB (internal macro)
;	rb  ���x�������	09/11/10
;	repeat�p
;********************************
_?extrb    macro   _?lvl
    _?genlb (_?rb#v(_?lvl))
	endm
;********************************
;   EXTRE (internal macro)
;	re  ���x�������	09/11/10
;	repeat�p
;********************************
_?extre    macro   _?lvl
    _?genlb (_?re#v(_?lvl))
	endm
;********************************
;   EXTRF (internal macro)
;	rf  ���x�������	09/11/10
;	repeat�p
;********************************
;_?extrf    macro   _?lvl
;    _?genlb (_?rf#v(_?lvl))
;	endm
;=========================���x���֔��=========
;********************************
;   GFEJP (internal macro) �x��
;	fb (for block) ���x���֔�ԏ��� 07/07/11
;********************************
_?gfejp macro   _?lbl
	_?genjp (_?fe#v(_?lbl))
	endm
;********************************
;   GFBJP (internal macro) �x��
;	fb (for block) ���x���֔�ԏ��� 07/07/11
;********************************
_?gfbjp macro   _?lbl
	_?genjp (_?fb#v(_?lbl))
	endm
;********************************
;   GLBJP (internal macro) �x��
;	lb ���x���֔�ԏ���
;********************************
_?glbjp macro   _?lbl
	_?genjp (_?lb#v(_?lbl))
	endm
;********************************
;   GBBJP (internal macro)
;	bb ���x���֔�ԏ���
;********************************
_?gbbjp	macro	_?lvl
	_?genjp (_?bb#v(_?lvl))
	endm
;********************************
;   GEBJP (internal macro)
;	eb ���x���֔�ԏ���
;********************************
_?gebjp        macro   _?lvl
    _?genjp (_?eb#v(_?lvl))
	endm
;********************************
;   GEXJP (internal macro)
;	ex ���x���֔�ԏ���		09/05/24
;********************************
_?gexjp        macro   _?lvl
    _?genjp (_?ex#v(_?lvl))
	endm
;********************************
;   GWBJP (internal macro)
;	wb ���x���֔�ԏ���		09/11/10
;	while�p
;********************************
_?gwbjp        macro   _?lvl
    _?genjp (_?wb#v(_?lvl))
	endm
;********************************
;   GWEJP (internal macro)
;	we ���x���֔�ԏ���		09/11/10
;	while�p
;********************************
_?gwejp        macro   _?lvl
    _?genjp (_?we#v(_?lvl))
	endm
;********************************
;   GWTJP (internal macro)
;	wt ���x���֔�ԏ���		09/11/10
;	while�p
;********************************
_?gwtjp        macro   _?lvl
    _?genjp (_?wt#v(_?lvl))
	endm
;********************************
;   GRBJP (internal macro)
;	rb ���x���֔�ԏ���		09/11/10
;	repeat�p
;********************************
_?grbjp        macro   _?lvl
    _?genjp (_?rb#v(_?lvl))
	endm
;********************************
;   GREJP (internal macro)
;	re ���x���֔�ԏ���		09/11/10
;	repeat�p
;********************************
_?grejp        macro   _?lvl
    _?genjp (_?re#v(_?lvl))
	endm
;********************************
;   GRFJP (internal macro)
;	rf ���x���֔�ԏ���		09/11/10
;	repeat�p
;;********************************
;_?grfjp        macro   _?lvl
;    _?genjp (_?rf#v(_?lvl))
;	endm
;==========================���ڎ��s==============
;********************************
;   GENJP (internal macro)
;	���x���ɔ��  ���s��
;********************************
_?genjp macro   _?lbl
	goto _?#v(_?lbl)
	endm
;********************************
;   GENLB (internal macro)
;	���x��������@���s��
;********************************
_?genlb macro   _?lbl
_?#v(_?lbl)
    endm
;============== ���x���쐬���� (stack) =========
;********************************
;   SETFB (internal macro)
;	fb (for begin block) ���x���쐬���� (stack)
;********************************
_?setfb macro   _?lvl,_?lbl
_?fb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETFE (internal macro)
;	fe (for end block) ���x���쐬���� (stack)
;********************************
_?setfe macro   _?lvl,_?lbl
_?fe#v(_?lvl) = _?lbl
	endm
;********************************
;   SETLB (internal macro)
;	lb ���x���쐬���� (stack)
;********************************
_?setlb macro   _?lvl,_?lbl
_?lb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETBB (internal macro)
;	bb ���x���쐬���� (stack)
;********************************
_?setbb macro   _?lvl,_?lbl
_?bb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETEB (internal macro)
;	eb ���x���쐬���� (stack)
;********************************
_?seteb macro   _?lvl,_?lbl
_?eb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETEX (internal macro)
;	ex ���x���쐬���� (stack)	09/05/24
;********************************
_?setex macro   _?lvl,_?lbl
_?ex#v(_?lvl) = _?lbl
	endm
;********************************
;   SETWB (internal macro)
;	wb ���x���쐬���� (stack)	09/11/10
;	while�p
;********************************
_?setwb macro   _?lvl,_?lbl
_?wb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETWE (internal macro)
;	we ���x���쐬���� (stack)	09/11/10
;	while�p
;********************************
_?setwe macro   _?lvl,_?lbl
_?we#v(_?lvl) = _?lbl
	endm
;********************************
;   SETWT (internal macro)
;	wt ���x���쐬���� (stack)	09/11/10
;	while�p
;********************************
_?setwt macro   _?lvl,_?lbl
_?wt#v(_?lvl) = _?lbl
	endm
;********************************
;   SETRB (internal macro)
;	rb ���x���쐬���� (stack)	09/11/10
;	repeat�p
;********************************
_?setrb macro   _?lvl,_?lbl
_?rb#v(_?lvl) = _?lbl
	endm
;********************************
;   SETRE (internal macro)
;	re ���x���쐬���� (stack)	09/11/10
;	repeat�p
;********************************
_?setre macro   _?lvl,_?lbl
_?re#v(_?lvl) = _?lbl
	endm
;********************************
;   SETRF (internal macro)
;	rf ���x���쐬���� (stack)	09/11/10
;	repeat�p
;********************************
;_?setrf macro   _?lvl,_?lbl
;_?rf#v(_?lvl) = _?lbl
;	endm
;========================= switch���p ==========
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
;end of Pamscls_sub.inc
;================================
#endif		;	_PAMSCLS_SUB_INC_INCLUDED
