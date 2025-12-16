BITS 64
default rel

; registers roles
; r12 = base_address ASLR
; r13 = executable_size
; r14 = executable_runtime_address
; r15 = payload_start_address

; define seciton for offsets
%define executable_addr 0
%define executable_size 8
%define original_entry_point 16
%define stub_vaddr 24
%define key_offset 32
%define STUB_SIZE (end_of_stub - _start)

section .text
_start:
	lea		r12, [rel _start]					; runtime address of the stub
	lea		r15, [rel _start + STUB_SIZE]		; points to payload
	mov		rax, [r15 + stub_vaddr]				; stub's virtual addr
	sub		r12, rax							; ASLR's base_addr = runtime address - virtual addr
	mov		r14, [r15 + executable_addr]		; vaddr of executable section
	add		r14, r12							; runtime addr of executable section (vaddr + base_address)
	mov		r13, [r15 + executable_size]		; executable_size
	jmp		decrypt

%include "./src/rc4.s"							; location important!

decrypt:
	; void init_state(unsigned char *rdi, size_t rsi)
	PUSH_VOLATILE_REG
	lea rdi, [rel STATE]
	mov rsi, 256
	call init_state
	POP_VOLATILE_REG

	; void	ksa(char *key[rdi], unsigned char *state[rsi], size_t len[rdx])
	PUSH_VOLATILE_REG
	lea rdi, [r15 + key_offset]
	lea rsi, [rel STATE]
	mov rdx, 16
	call ksa
	POP_VOLATILE_REG

	; void	rc4(unsigned char *state, char *str, size_t len)
	PUSH_VOLATILE_REG
	lea rdi, [rel STATE]
	mov rsi, r14
	mov rdx, r13
	call rc4
	POP_VOLATILE_REG

goto_OEP:
	; --- print ....WOODY... ---
	PUSH_VOLATILE_REG
	mov	rax, 1					; WRITE
	mov	rdi, 1					; STDOUT
	lea	rsi, [rel GREETING]		; STRING
	mov	rdx, 14					; SIZE
	syscall
	POP_VOLATILE_REG

	mov    rax, [r15 + original_entry_point]		; OEP vaddr
	add    rax, r12									; actual OEP = vaddr + base_addr
	jmp rax									; jmp to OEP

; --- Data used by the greeting function ---
GREETING:
	db "....WOODY....", 10					; 10 = ascii's new line

; --- STATE used by the RC4 ---
STATE:
	times 256 db 0							; 256 bytes 0

end_of_stub:
