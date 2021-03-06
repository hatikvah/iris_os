;this asm code is to handle traps and interruptions
;from idt hardware then pushes regs and handles traps
;and interruptions to their processing code. 

;/* warning: the stack need to be considered especially
;   when changing from user to kernel. in line 76 or so
;*/

extern trap_handler;
extern irq_handler;

global ld_idt
ld_idt:
  mov eax,[esp+4]
  lidt [eax]
  cli
  ret

%macro NOERR_TRAP 1
global trap%1
trap%1:
  cli
  push  0
  push  %1
  jmp alltraps
%endmacro

%macro WITHERR_TRAP 1
global trap%1
trap%1:
  cli
  ;push dword 0
  push  %1
  jmp alltraps
%endmacro

NOERR_TRAP 0
NOERR_TRAP 1 
NOERR_TRAP 2
NOERR_TRAP 3
NOERR_TRAP 4
NOERR_TRAP 5
NOERR_TRAP 6
NOERR_TRAP 7
WITHERR_TRAP 8
NOERR_TRAP 9
WITHERR_TRAP 10
WITHERR_TRAP 11
WITHERR_TRAP 12
WITHERR_TRAP 13
WITHERR_TRAP 14
NOERR_TRAP 15
NOERR_TRAP 16
WITHERR_TRAP 17
NOERR_TRAP 18
NOERR_TRAP 19

NOERR_TRAP 20
NOERR_TRAP 21
NOERR_TRAP 22
NOERR_TRAP 23
NOERR_TRAP 24
NOERR_TRAP 25 
NOERR_TRAP 26
NOERR_TRAP 27 
NOERR_TRAP 28
NOERR_TRAP 29 
NOERR_TRAP 30
NOERR_TRAP 31


alltraps:
  mov ax,ds
  push eax
  mov ax,es
  push eax
  mov ax,fs
  push eax
  mov ax,gs
  push eax
  pusha

  
  
  mov ax,0x10
  mov ds,ax
  mov es,ax
  mov fs,ax
  mov gs,ax
  mov ss,ax ;
  mov eax,esp
  push eax   ; the addr of trapframe struct
             ; and is the arg passed to C code as well
  call trap_handler;
  add esp,4;   

  popa;
  pop ebx;
  mov gs,bx
  pop ebx;
  mov fs,bx
  pop ebx
  mov es,bx
  pop ebx
  mov ds,bx
  
  add esp,8 ;manually clear the errcode and trapno in stack
  iret

%macro IRQ 1
global irq%1
irq%1:
cli
push dword 0
push dword (%1+32)
jmp allirq
%endmacro

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

allirq:
mov ax,ds
  push eax
  mov ax,es
  push eax
  mov ax,fs
  push eax
  mov ax,gs
  push eax
  pusha

  mov ax,0x10
  mov ds,ax
  mov es,ax
  mov fs,ax
  mov gs,ax
  mov ss,ax ;
  mov eax,esp
  push eax   ; the addr of trapframe struct
             ; and is the arg passed to C code as well
  call irq_handler;
  add esp,4;   

  popa;
  pop ebx;
  mov gs,bx
  pop ebx;
  mov fs,bx
  pop ebx
  mov es,bx
  pop ebx
  mov ds,bx
  
  add esp,8 ;manually clear the errcode and trapno in stack
  iret


  































