BITS 64
default rel

; registers rolls
; r12 = base_address of ASLR
; r11 = executable_runtime_address
; rcx = executable_size
; r10 = OEP
; r9 = payload_start_address
; r8 = decrypt key value

; define seciton for offsets
%define executable_addr_offset 0
%define executable_size_offset 8
%define original_entry_point_offset 16
%define stub_vaddr 24
;%define key_addr_offset 32
%define STUB_SIZE (end_of_stub - _start)

global _start

section .text

_start:
	lea	r12, [rel _start] ; runtime address of _start
	lea	r9, [rel _start + STUB_SIZE]; *r9 points to payload*
	mov	rax, [r9 + stub_vaddr]
	sub r12, rax

prepare_decrypt:
	mov	r11, [r9 + executable_addr_offset]
	mov rcx, [r9 + executable_size_offset]
	add	r11, r12

decrypt_loop:
	xor	byte[r11], 0xff
	inc	r11
	dec rcx
	jnz	decrypt_loop

goto_OEP:
	mov	r10, [r9 + original_entry_point_offset]
	add	r10, r12
	; and rsp, -16
	jmp r10

end_of_stub:
