;	vim:  set syntax=pic  ts=4 sts=4 sw=4: –x–ì ŽçŽ  Last Change:2011/04/07 11:44:59.
;	compare_swap.inc
;From http://www.myke.com/basic.htm

    Here's a compare and swap

       movf    X, w                 
       subwf   Y, w                 ;  Is Y >= X?
       btfsc   STATUS, C            ;  If Carry Set, Yes
         goto   $ + 2                ;   Don't Swap
       addwf   X, f                 ;  Else, X = X + (Y - X)
       subwf   Y, f                 ;        Y = Y - (Y - X)

