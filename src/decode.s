; void decode(uint64_t text_segment_size, char *text_segment)
; rdi = text_segment_size, rsi = *text_segment

bits 64
default rel

section .text
global _decode

_decode:
	xor	rcx, rcx; reset counter 0

.loop:
	cmp	rcx, rdi;
	je	.end
	xor	byte [rsi + rcx], 0xff
	inc	rcx
	jmp	.loop

.end:
	ret
