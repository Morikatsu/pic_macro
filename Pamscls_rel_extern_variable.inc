; vim:set syntax=pic ts=4 sts=4 sw=4: 堀野守克 Last Change:2012/03/08 10:59:06.
;	Pamscls_rel_extern_variable.inc
;		main以外のアセンブル単位でPamsclsを使う場合あるいはeepromのI/Oを行う
;		場合にはPamscls_rel_variable.incの代わりにこのファイルをincludeする

#ifndef	_PAMSCLS_REL_EXTERN_VARIABLE_INC_INCLUDED
#define	_PAMSCLS_REL_EXTERN_VARIABLE_INC_INCLUDED

	extern	_?temp0,_?temp1,_?temp2,_?temp3
	extern	_?temp4,_?temp5,_?temp6,_?temp7
	extern	_?romadrs,_?sCount,_?msCount,_?usCount
#endif	;	_PAMSCLS_REL_EXTERN_VARIABLE_INC_INCLUDED
