; EMPTY9: zero-length, word-aligned code segment (segtable entry 9, 168b:000e) between mazeio and snddrv.
; TLINK still gives it a segment-table slot. Word alignment = an assembler module (BCC code is byte aligned).
EMPTY9_TEXT	segment word public 'CODE'
EMPTY9_TEXT	ends
	end
