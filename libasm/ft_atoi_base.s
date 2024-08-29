section .text
global ft_atoi_base

_ret_zero_clear:
    pop     rax
    pop     rax
_ret_zero:
    mov     rax, 0
    ret
ft_atoi_base:
    test    rsi, rsi
    je      _ret_zero
    mov     al, byte [rsi]
    test    al, al
    je      _ret_zero
    mov     al, byte [rsi + 1]
    test    al, al
    je      _ret_zero
_double_character_check:
    mov     rax, 0    ; i = 0
_double_character_check_loop_one:
    mov     cl, byte [rsi + rax]    ; cl = base[i]
    test    cl, cl    ; ret 1 si [dl != '\0']
    je      _valid_character_check
    mov     rbx, rax    ; y = i + 1
    inc     rbx
_double_character_check_loop_two:
    mov     dl, byte [rsi + rbx]    ; dl = base[y]
    test    dl, dl    ; ret debut loop 1 si [dl != '\0']
    je      _continue_loop_one
    cmp     cl, dl    ; ret 0 si cl = dl
    je     _ret_zero
    inc     rbx    ; y++
    jmp     _double_character_check_loop_two    ; ret debut loop 2
_continue_loop_one:
    ; i++
    inc     rax
    jmp     _double_character_check_loop_one
_valid_character_check:
    mov     rax, 0
_valid_character_check_loop:
    mov     bl, byte [rsi + rax]
    test    bl, bl
    je      _skip_white_space_loop
    cmp     bl, '+'
    je     _ret_zero
    cmp     bl, '-'
    je     _ret_zero
    cmp     bl, 9
    je     _ret_zero
    cmp     bl, 10
    je     _ret_zero
    cmp     bl, 11
    je     _ret_zero
    cmp     bl, 12
    je     _ret_zero
    cmp     bl, 13
    je     _ret_zero
    cmp     bl, 32
    je     _ret_zero
    inc     rax
    jmp     _valid_character_check_loop
_skip_white_space:
    inc     rdi
_skip_white_space_loop:
    mov     al, byte [rdi]
    test    al, al
    je      _determine_signe  ; End of string, return
    cmp     al, 9             ; Tab
    je      _skip_white_space
    cmp     al, 10            ; Newline
    je      _skip_white_space
    cmp     al, 11            ; Vertical tab
    je      _skip_white_space
    cmp     al, 12            ; Form feed
    je      _skip_white_space
    cmp     al, 13            ; Carriage return
    je      _skip_white_space
    cmp     al, 32            ; Space
    je      _skip_white_space
_determine_signe:
    mov     rax, 1
_determine_signe_loop:
    mov     bl, byte [rdi]
    test    bl, bl
    je      _base_size
    cmp     bl, '+'
    je     _determine_signe_loop_insight
    cmp     bl, '-'
    je     _determine_signe_loop_minus
    jmp     _base_size
_determine_signe_loop_minus:
    neg     rax
_determine_signe_loop_insight:
    inc     rdi
    jmp     _determine_signe_loop
_base_size:
    mov     rbx, 0
_base_size_loop:
    mov     cl, byte [rsi + rbx]
    test    cl, cl
    je      _ft_atoi_base_loop_init
    inc     rbx
    jmp     _base_size_loop
_ft_atoi_base_loop_init:
    push    rax                   ; push signe
    push    rbx                   ; push size
    mov     rax, 0                ; result
_ft_atoi_base_loop:
    mov     cl, byte [rdi]        ; str[0]
    test    cl, cl
    je      _ret_one
    mov     rbx, 0                ; i
_ft_atoi_base_loop_two:
    mov     dl, byte [rsi + rbx]  ; base[i]
    test    dl, dl
    je      _ret_zero_clear
_ft_atoi_base_cmp:
    cmp     cl, dl
    jne     _ft_atoi_base_after_cmp
    pop     rdx                   ; pop size
    imul    rax, rdx
    add     rax, rbx
    push    rdx                   ; push size
    jmp     _ft_atoi_base_loop_two_end
_ft_atoi_base_after_cmp:
    inc     rbx
    jmp     _ft_atoi_base_loop_two
_ft_atoi_base_loop_two_end:
    inc     rdi
    jmp     _ft_atoi_base_loop
_ret_one:
    pop     rbx
    pop     rcx
    imul    rax, rcx
    ret

