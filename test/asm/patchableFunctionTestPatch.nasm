bits 64
default rel
section .text

add rcx, rdx
mov rax, rcx
jmp [$+6]
dq 0x9090909090909090