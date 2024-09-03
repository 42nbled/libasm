section .text
global ft_strcpy

; rdi = char *dst
; rsi = const char *src
ft_strcpy:
    mov     rdx, rdi
    test    rsi, rsi
    jne     _strcpy_body
    mov     rax, 0
    ret
_strcpy_body:
    mov     al, [rsi]
    mov     [rdi], al
    cmp     al, 0
    je      _strcpy_ret
    inc     rdi
    inc     rsi
    jmp     _strcpy_body
_strcpy_ret:
    mov     rax, rdx
    ret
