BITS 64
default rel

; prologue
%macro PROLOGUE 0
	push rbp
	mov rbp, rsp
%endmacro

; epilogue
%macro EPILOGUE 0
	mov rsp, rbp
	pop rbp
%endmacro

; push callee-saved non volative registers
%macro PUSH_CALLEE_SAVED 0
	push rbx
	push r12
	push r13
	push r14
	push r15
	sub	rsp, 8
%endmacro

; pop callee-saved non volative registers
%macro POP_CALLEE_SAVED 0
	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
%endmacro

; push volatile registers
%macro PUSH_VOLATILE_REG 0
	push	rax
	push	rcx
	push	rdx
	push	rsi
	push	rdi
	push	r8
	push	r9
	push	r10
	push	r11
%endmacro

; pop volatile registers
%macro POP_VOLATILE_REG 0
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	rdi
	pop	rsi
	pop	rdx
	pop	rcx
	pop	rax
%endmacro

; void swap(unsigned char *rdi, unsigned char *rsi)
swap:
	PROLOGUE
	PUSH_CALLEE_SAVED
	mov al, [rdi]
	mov cl, [rsi]
	mov [rdi], cl
	mov [rsi], al
	POP_CALLEE_SAVED
	EPILOGUE
	ret


; void init_state(unsigned char *rdi, size_t rsi)
init_state:
	PROLOGUE
	PUSH_CALLEE_SAVED
	xor rcx, rcx
.loop:
	cmp rcx, rsi
	je .end
	mov byte [rdi + rcx], cl
	inc rcx
	jmp .loop
.end:
	POP_CALLEE_SAVED
	EPILOGUE
	ret

; size_t modulo(size_t rdi, size_t rsi)
modulo:
	PROLOGUE
	PUSH_CALLEE_SAVED
	xor rdx, rdx
	mov rax, rdi
	div rsi
	mov rax, rdx
	POP_CALLEE_SAVED
	EPILOGUE
	ret

%define N 256

; void	ksa(char *key[rdi], unsigned char *state[rsi], size_t len[rdx])
; r8 = key, r9 = state, r10 = len, r11 = i, r12 = j, r13 = tmp

ksa:
	PROLOGUE
	PUSH_CALLEE_SAVED

	mov r8, rdi
	mov r9, rsi
	mov r10, rdx
	xor r11, r11
	xor r12, r12

	jmp .loop


.loop:
	cmp r11, N
	je .end

	; j = (j + state[i] + key[i % len]) % N;
	movzx rax, byte [r9 + r11]
	add r12, rax

	mov rdi, r11
	mov rsi, r10
	call modulo

	movzx rax, byte [r8 + rax]
	add r12, rax

	mov rdi, r12
	mov rsi, N
	call modulo
	mov r12, rax

	; swap(&state[i], &state[j]);
	lea rdi, [r9 + r11]
	lea rsi, [r9 + r12]
	call swap

	inc r11
	jmp .loop

.end:
	POP_CALLEE_SAVED
	EPILOGUE
	ret

; void	rc4(unsigned char *state, char *str, size_t len)
; r8 = state, r9 = str, r10 = len, r11 = i, r12 = j, r13 = n, r14 = seed
rc4:
	PROLOGUE
	PUSH_CALLEE_SAVED

	xor r11, r11
	xor r12, r12
	xor r13, r13
	xor r14, r14

	mov r8, rdi
	mov r9, rsi
	mov r10, rdx

	jmp .loop

.loop:
	cmp r13, r10
	jae .end

	; i = (i + 1) % N;
	add r11, 1
	mov rdi, r11
	mov rsi, N
	call modulo
	mov r11, rax

	; j = (j + state[i]) % N;
	movzx rax, byte[r8 + r11]
	add r12, rax
	mov rdi, r12
	mov rsi, N
	call modulo
	mov r12, rax

	; swap(&state[i], &state[j]);
	lea rdi, [r8 + r11]
	lea rsi, [r8 + r12]
	call swap

	; seed = state[(state[i] + state[j]) % N];
	movzx rax, byte[r8 + r11]
	mov r14, rax
	movzx rax, byte[r8 + r12]
	add r14, rax
	mov rdi, r14
	mov rsi, N
	call modulo
	movzx rax, byte[r8 + rax]
	mov r14, rax

	; str[n] ^= seed; n++;
	xor byte [r9 + r13], r14b
	inc r13
	jmp .loop

.end:
	POP_CALLEE_SAVED
	EPILOGUE
	ret

