; Multiboot-заголовок
section .multiboot
align 4
    dd 0x1BADB002              ; Magic
    dd 0x00000003              ; Flags
    dd -(0x1BADB002 + 0x03)    ; Checksum

section .text
global start
extern kmain

start:
    call kmain
    jmp $