global stub_start
global stub_end

section .text
%define text_segment_vaddr      0
%define text_segment_size       8
%define original_entry_point    16
%define key_addr                24
%define PAGE_SIZE               0x1000

stub_start:
    ; --- Step 1: Calculate the ASLR base address ---
    call get_rip
get_rip:
    pop rbp                 ; rbp now holds the RUNTIME address of 'get_rip' label
    sub rbp, get_rip        ; rbp now holds the ASLR base address (the random offset)

    ; --- Step 2: Find the payload information ---
    lea rsi, [rel payload_info]

    ; --- Step 3: Make the text segment writable and executable (THE CORRECT WAY) ---
    ; Calculate the real runtime address of the text segment
    mov rdi, [rsi + text_segment_vaddr] ; Load base vaddr from payload_info
    add rdi, rbp                        ; Add ASLR offset

    ; Calculate the size needed for mprotect
    ; First, calculate the offset from the page start
    mov r8, rdi             ; Copy the real address to r8
    and r8, PAGE_SIZE - 1   ; r8 = real_addr % PAGE_SIZE (offset within the page)
    ; Now, calculate the total size needed for protection
    mov rdx, [rsi + text_segment_size]
    add rdx, r8             ; len = original_size + offset_from_page_start

    ; Align the start address down to the nearest page boundary
    and rdi, ~(PAGE_SIZE - 1) ; addr = addr - (addr % PAGE_SIZE)

    ; Now, call mprotect with the page-aligned address and corrected size
    ; --- Syscall Preparation ---
    push rbp                ; PRESERVE our precious ASLR offset from syscall
    mov rax, 10             ; syscall: mprotect
    ; RDI already holds the aligned address (Arg 1)
    mov rsi, rdx            ; Move corrected size into RSI (Arg 2)
    mov rdx, 0x7            ; PROT_READ | PROT_WRITE | PROT_EXEC (Arg 3)
    syscall
    pop rbp                 ; RESTORE our ASLR offset

    ; --- Step 4: Decrypt the text segment ---
    lea rsi, [rel payload_info]
    mov rcx, [rsi + text_segment_size]
    mov rbx, [rsi + text_segment_vaddr]
    add rbx, rbp

decrypt_loop:
    xor byte [rbx], 0xff
    inc rbx
    dec rcx
    jnz decrypt_loop

    ; --- Final Step: Jump to the original entry point ---
    mov rbx, [rsi + original_entry_point]
    add rbx, rbp
    jmp rbx

stub_end:

payload_info:

