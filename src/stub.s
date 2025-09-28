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
	mov		rbx, rsp
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
	lea rdi, [rel state]
	mov rsi, 256
	call init_state

	; void	ksa(char *key[rdi], unsigned char *state[rsi], size_t len[rdx])
	lea rdi, [r15 + key_offset]
	lea rsi, [rel state]
	mov rdx, 16
	call ksa

	; void	rc4(unsigned char *state, char *str, size_t len)
	lea rdi, [rel state]
	mov rsi, r14
	mov rdx, r13
	call rc4

goto_OEP:
	; greeting
	mov    rax, 1                            ; WRITE
	mov    rdi, 1                            ; STDOUT
	lea    rsi, [rel greetings_data]        ; STR
	mov    rdx, 14                            ; SIZE
	syscall

	mov    rax, [r15 + original_entry_point]		; OEP vaddr
	add    rax, r12									; actual OEP = vaddr + base_addr

	mov rsp, rbx
	;push qword exit_stub
	lea	rdi, [rel exit_stub]
	add rdi, r12
	push rdi
	jmp rax									; jmp to OEP

exit_stub:
	mov	rax, 60								; exit
	xor rdi, rdi							; exit code 0
	syscall

; --- Data used by the greeting function ---
greetings_data:
	db "....WOODY....", 10; 10 = NL
state:
	times 256 db 0

end_of_stub:
