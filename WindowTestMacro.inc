;	vim:  set syntax=pic  ts=4 sts=4 sw=4: –x–ì ŽçŽ  Last Change:2010/02/04 11:11:26.
;	www.piclist.com/techref/cpus.html
;++++++++++++++++++++++++++++++++++++++++++++++++++++
; Call as WindowTest value, min, max.
;	Carry is set if value is within min-max (wtpass),
;	and cleared if not (wtfail). 
;	”ÍˆÍ“à‚Å‚ ‚ê‚Îcarry set, ”ÍˆÍŠO‚Å‚ ‚ê‚Îcarry clear
; The key to this is the subwf instruction. With subwf, the destination=f-w and
; carry =1 if destination=>0 (carry=1 is positive result). So, 
;	carry=1 if f=>w
;	carry=0 if f<w or w>f
;++++++++++++++++++++++++++++++++++++++++++++++++++++
WindowTest macro value, min, max
  local wtexit		; local labels in macro
					; For min, we want value=>min, so we'll put value in f and min in w
 	movfw	min			; Get minimum
	subwf	value,w		; w=f-w , w=value-min. Result positive (carry set) if value=>min
	bnc		wtexit		; If no carry, we're below min. Exit with fail (carry clear)
					; For max, we want max=>value, so we'll put max in f, value in w
	movfw	value		; Get current value in w
	subwf	max,w		; w=f-w = max-value. Result positive (carry set) if max=>value.
						; Exit with carry set
wtexit	
	endm


