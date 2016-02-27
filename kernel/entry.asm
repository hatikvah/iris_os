extern kmain

global gdt_flush
global _start
;global _kstacktop
;stack resb 2048
;_kstacktop:

global _sys_stack_
section .bss
resb 8192
_sys_stack_:

section .text

gdt_flush:
mov eax,[esp+4]    ;have a question here about +4?

lgdt [eax]

mov ax,0x10
mov ds,ax
mov es,ax
mov ss,ax
mov gs,ax

jmp 0x08:flush
flush:
ret

_start:
mov esp,_sys_stack_
;mov esp,_kstacktop

call kmain
xor eax,eax
xor ebx,ebx
en:jmp en
hlt







