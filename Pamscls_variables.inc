; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2010/07/03 18:41:39.
;	Pamscls_variables.inc
#ifndef	_PAMSCLS_VARIABLE_INC_INCLUDED
#define	_PAMSCLS_VARIABLE_INC_INCLUDED
;****************************************************
;	作業変数の確保	10/05/25 変更
;	relocatableなので変数の位置を固定していない
;	変数にアクセスする際にbankselを使えばよい
;****************************************************
Pamscls_datgrp	udata_shr;	(_?BTMMEMO - 0x0f + d'5')
_?romadrs	res	1
_?sCount	res	1
_?msCount	res	1
_?usCount	res	1

_?temp0		res	1
_?temp1		res	1
_?temp2		res	1
_?temp3		res	1
_?temp4		res	1
_?temp5		res	1
_?temp6		res	1
_?temp7		res	1
;****************************************************
	global	_?temp0,_?temp1,_?temp2,_?temp3
	global	_?temp4,_?temp5,_?temp6,_?temp7
	global	_?romadrs,_?sCount,_?msCount,_?usCount
;****************************************************
#endif		;	_PAMSCLS_VARIABLE_INC_INCLUDED
