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
%define executable_addr 0
%define executable_size 8
%define original_entry_point 16
%define stub_vaddr 24
;%define key_addr_offset 32
%define STUB_SIZE (end_of_stub - _start)

global _start

section .text

_start:
	lea	r12, [rel _start]				; runtime address of the stub
	lea	r9, [rel _start + STUB_SIZE]	; r9 points to payload
	mov	rax, [r9 + stub_vaddr]			; stub's virtual addr
	sub r12, rax						; ASLR's base_addr = runtime address - virtual addr

prepare_decrypt:
	mov	r11, [r9 + executable_addr]		; vaddr of executable section
	mov rcx, [r9 + executable_size]
	add	r11, r12						; runtime addr of executable section (base_addr + vaddr)

decrypt_loop:
	xor	byte[r11], 0xff
	inc	r11
	dec rcx
	jnz	decrypt_loop

goto_OEP:
	mov	r10, [r9 + original_entry_point]		; OEP vaddr
	add	r10, r12								; actual OEP = vaddr + base_addr
	call greeting
	jmp r10									; jmp to OEP

; --- Function to print a greeting ---
greeting:
	push rax
	push rdi
	push rsi
	push rdx
	push rcx
	push r11

	mov	rax, 1							; WRITE
	mov	rdi, 1							; STDOUT
	lea	rsi, [rel greetings_data]		; STR
	mov	rdx, 14							; SIZE
	syscall

	pop r11
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rax
	ret

; --- Data used by the greeting function ---
greetings_data: db "....WOODY....", 10; 10 = NL

end_of_stub:
