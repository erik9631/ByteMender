bits 64
default rel
section .text

randomOperations:
    add rcx, 100
    add rdx, 100
    imul rcx, rdx
    mov rax, rcx
    mov rdx, 0
    mov rcx, 2
    idiv rcx
    ret