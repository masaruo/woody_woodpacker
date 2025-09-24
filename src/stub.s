BITS 64
default rel

%include "./src/rc4.s"

; define seciton for offsets
%define executable_addr 0
%define executable_size 8
%define original_entry_point 16
%define stub_vaddr 24
%define key_offset 32
%define STUB_SIZE (end_of_stub - _start)

global _start

section .bss
    state: resb 256 ; memory for RC4 State-Box

section .text

_start:
    push rbp
    mov rbp, rsp

    ; === DEBUG: Print "START" to see if we get here ===
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_start]
    mov rdx, 6
    syscall
    ; ================================================

    lea r12, [rel _start]               ; runtime address of the stub
    lea r9, [rel _start + STUB_SIZE]    ; r9 points to payload

    ; === DEBUG: Now test payload access ===
    mov rax, [r9 + stub_vaddr]        ; stub's virtual addr
    sub r12, rax                      ; ASLR's base_addr = runtime address - virtual addr
    ; ======================================

    ; === DEBUG: Print "MIDDLE" ===
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_middle]
    mov rdx, 7
    syscall
    ; ============================

    ; === NOW ADD BACK THE DECRYPTION ===
prepare_decrypt:
    ; === DEBUG: Test payload data access ===
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_prepare]
    mov rdx, 8
    syscall

    ; Test each payload access individually
    mov r11, [r9 + executable_addr]     ; vaddr of executable section

    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_size]
    mov rdx, 5
    syscall

    mov rcx, [r9 + executable_size]

    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_add]
    mov rdx, 4
    syscall

    add r11, r12                        ; runtime addr of executable section
    ; ===================================================

decrypt:
    ; === DEBUG: Skip RC4 for now ===
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_init]
    mov rdx, 5
    syscall
    ; ===============================
    ; =====================================

goto_OEP:
    ; === DEBUG: Now test OEP access ===
    mov r10, [r9 + original_entry_point]  ; OEP vaddr
    add r10, r12                           ; actual OEP = vaddr + base_addr
    ; ==================================

    ; === DEBUG: Print before jump ===
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel debug_end]
    mov rdx, 4
    syscall
    ; ===============================

    ; === DEBUG: Now try the actual jump to OEP ===
    leave           ; restore stack frame
    and rsp, -16    ; stack alignment
    jmp r10         ; jump to OEP - THIS IS WHERE IT PROBABLY SEGFAULTS
    ; ============================================

debug_start: db "START", 10
debug_middle: db "MIDDLE", 10
debug_end: db "END", 10
debug_zero: db "ZERO", 10
debug_big: db "BIG", 10
debug_init: db "INIT", 10
debug_ksa: db "KSA", 10
debug_rc4: db "RC4", 10
debug_prepare: db "PREPARE", 10
debug_size: db "SIZE", 10
debug_add: db "ADD", 10

end_of_stub:
