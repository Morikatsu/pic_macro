; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2011/04/06 11:36:06.
;	Pamscls_internal_macro.inc		Ver 1.0
	NOLIST
;	このファイルはPamscls_abs.inc|Pamscls_rel.incにincludeされる
;====================================================
#ifndef	_PAMSCLS_INTERNAL_MACRO_INC_INCLUDED
#define	_PAMSCLS_INTERNAL_MACRO_INC_INCLUDED
;====================================================
;===== INTERNAL MACROS ===========
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
;end of Pamscls_internal_macro.inc
;================================
#endif		;	_PAMSCLS_INTERNAL_MACRO_INC_INCLUDED
	LIST
