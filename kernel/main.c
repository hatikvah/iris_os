#include "console.h"
#include "string.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

void kmain(){
init_gdt();
init_idt();
init_timer(152);
console_clean();

__asm__ volatile("sti");
}
