section .text
global ft_atoi_base

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
    ; i = 0
    mov     rax, 0
_double_character_check_loop_one:
    ; al = base[i]
    mov     al, byte [rsi + rax]
    ; ret 1 si [bl != '\0']
    test    al, al
    je      _ret_one
    ; y = i + 1
    mov     rbx, rax
    inc     rbx
_double_character_check_loop_two:
    ; bl = base[y]
    mov     bl, byte [rsi + rbx]
    ; ret debut loop 1 si [bl != '\0']
    test    bl, bl
    je      _continue_loop_one
    ; ret 0 si al = bl
    cmp     al, bl
    je     _ret_zero
    ; y++
    inc     rbx
    ; ret debut loop 2
    jmp     _double_character_check_loop_two
_continue_loop_one:
    ; i++
    inc     rax
    jmp     _double_character_check_loop_one
_ret_one:
    mov     rax, 1
    ret
