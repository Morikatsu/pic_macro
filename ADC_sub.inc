; vim:	set syntax=pic	ts=4 sts=4 sw=4: last change:2010/01/28 08:28:45.
;	ADC_sub.inc		メインプログラムでつぎの4項目を行っておく
;	・コンパレータをoff	[CMCON]	.................. 初期化
;	・ADCに使うportを入力とする [TRIS*] .......... 初期化
;	・ADCに使うportと変換クロックを設定 [ANSEL] .. 初期化
;	・ADCON0に設定するADCのch, Vref, data formatはWregに入っていることが前提
;	結果はWregに入る [本来はADRESH, ADRESLに入る]
;************************************************************************
ADC		;ADCを開始し、結果をWreg(upperのみ)に入れる
;	movlw	H'03'		;ch1, 基準電圧=Vdd, 左詰
;	MOVWF		ADCON0	;充電開始[ADC準備]
	MOVWF		ADCON0	;充電開始[ADC準備]
	call	timeDelay50us	;50us 充電時間 本来は20usで可
	BSF		ADCON0,GO
Wait_ADC	;
	BTFSC		ADCON0,GO	;ADC完了でskip
	GOTO		Wait_ADC
;		bsf		STATUS,RP0	;bank1
;	MOVF		ADRESL,W	;
;		bcf		STATUS,RP0	;bank0
	MOVF		ADRESH,W	;結果は0..255の範囲で得られる
	RETURN		
;********* end of ADC ************************************
