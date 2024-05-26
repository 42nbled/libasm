section .text
global ft_strcmp

ft_strcmp:
    ; test    rsi, rsi
    ; je      _strcmp_ret_zero
    ; test    rdi, rdi
    ; je      _strcmp_ret_zero
_strcmp_body:
    mov     al, [rdi]
    mov     bl, [rsi]
    cmp     al, bl
    jne     _strcmp_ret
    test    al, al
    je      _strcmp_ret_zero
    inc     rdi
    inc     rsi
    jmp     _strcmp_body
_strcmp_ret_zero:
    mov   rax, 0
    ret
_strcmp_ret:
    sub     al, bl
    movsx   rax, al
    ret
