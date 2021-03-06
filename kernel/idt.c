#include "idt.h"
#include "type.h"
#include "debug.h"
#include "x86.h"

void trap0();
void trap1();
void trap2();
void trap3();
void trap4();
void trap5();
void trap6();
void trap7();
void trap8();
void trap9();
void trap10();
void trap11();
void trap12();
void trap13();
void trap14();
void trap15();
void trap16();
void trap17();
void trap18();
void trap19();
void trap20();
void trap21();
void trap22();
void trap23();
void trap24();
void trap25();
void trap26();
void trap27();
void trap28();
void trap29();
void trap30();
void trap31();

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

phandler phandler_list[256];
struct idt_info idt_info_struct;
struct idt_entry  idt_entry_list[256];

void irq_handler(struct trapframe* t){
  if(t->trapno>=0x28){
    outb(0xa0,0x20);
  }
  outb(0x20,0x20);
  if(phandler_list[t->trapno]!=NULL){
    //printk("%s,%u,%s","eip",t->eip,"\n");
    phandler_list[t->trapno](t);
  }
  else{
    printk("%s,%u,%s","Unhandled irq ",t->trapno," .\n");
    printk("%s,%u,%s","eip",t->eip,"\n");
    printk("%s,%u,%s","cs",t->cs,"\n");
  }
}
void trap_handler(struct trapframe* t){
 
  if(phandler_list[t->trapno]!=NULL){
    phandler_list[t->trapno](t);
  }
  else{
    printk("%s,%u,%s","Unhandled ",t->trapno,".\n");
    printk("%s,%u,%s","errcode",t->errcode,"\n");
    printk("%s,%u,%s","eip",t->eip,"\n");
    printk("%s,%u,%s","cs",t->cs,"\n");

  }
}
void int_with_errcode_handler(struct trapframe* t){
  printk("%s,%u,%s","Here is int ",t->trapno," handler,hault!");
  __asm__ volatile("hlt");
}
void handle_trap(phandler ptr,uint32_t no){
  phandler_list[no]=ptr;
}

static void make_idt_entry(uint32_t no,uint32_t offset,uint8_t select,uint16_t pr){
  idt_entry_list[no].off_low=offset&0xffff;
  idt_entry_list[no].selector=select;
  idt_entry_list[no].always0=0;
  idt_entry_list[no].p=pr;
  idt_entry_list[no].off_high=(offset>>16)&0xffff;
}

void delay(){
}
void init_8259(){
  outb(0x20,0x11);
  outb(0xa0,0x11);
  outb(0x21,0x20);
  outb(0xa1,0x28);
  outb(0x21,0x04);
  outb(0xa1,0x02);
  outb(0x21,0x01);
  outb(0xa1,0x01);
  outb(0x21,0xfe); //all intr on master
  outb(0xa1,0xff); //all intr on slave
}

void init_idt(){
  idt_info_struct.idt_limit=sizeof(struct idt_entry)*256-1;
  idt_info_struct.idt_base=(uint32_t)(&idt_entry_list);
  for(int i=0;i<256;i++){
    phandler_list[i]=NULL;
  }
  
  make_idt_entry(0,(uint32_t)trap0,0x08,0x8E);
  make_idt_entry(1,(uint32_t)trap1,0x08,0x8E);
  make_idt_entry(2,(uint32_t)trap2,0x08,0x8E);
  make_idt_entry(3,(uint32_t)trap3,0x08,0x8E);
  make_idt_entry(4,(uint32_t)trap4,0x08,0x8E);
  make_idt_entry(5,(uint32_t)trap5,0x08,0x8E);
  make_idt_entry(6,(uint32_t)trap6,0x08,0x8E);
  make_idt_entry(7,(uint32_t)trap7,0x08,0x8E);
  make_idt_entry(8,(uint32_t)trap8,0x08,0x8E);
  make_idt_entry(9,(uint32_t)trap9,0x08,0x8E);
  make_idt_entry(10,(uint32_t)trap10,0x08,0x8E);
  make_idt_entry(11,(uint32_t)trap11,0x08,0x8E);
  make_idt_entry(12,(uint32_t)trap12,0x08,0x8E);
  make_idt_entry(13,(uint32_t)trap13,0x08,0x8E);
  make_idt_entry(14,(uint32_t)trap14,0x08,0x8E);
  make_idt_entry(15,(uint32_t)trap15,0x08,0x8E);
  make_idt_entry(16,(uint32_t)trap16,0x08,0x8E);
  make_idt_entry(17,(uint32_t)trap17,0x08,0x8E);
  make_idt_entry(18,(uint32_t)trap18,0x08,0x8E);
  make_idt_entry(19,(uint32_t)trap19,0x08,0x8E);
  make_idt_entry(20,(uint32_t)trap20,0x08,0x8E);
  make_idt_entry(21,(uint32_t)trap21,0x08,0x8E);
  make_idt_entry(22,(uint32_t)trap22,0x08,0x8E);
  make_idt_entry(23,(uint32_t)trap23,0x08,0x8E);
  make_idt_entry(24,(uint32_t)trap24,0x08,0x8E);
  make_idt_entry(25,(uint32_t)trap25,0x08,0x8E);
  make_idt_entry(26,(uint32_t)trap26,0x08,0x8E);
  make_idt_entry(27,(uint32_t)trap27,0x08,0x8E);
  make_idt_entry(28,(uint32_t)trap28,0x08,0x8E);
  make_idt_entry(29,(uint32_t)trap29,0x08,0x8E);
  make_idt_entry(30,(uint32_t)trap30,0x08,0x8E);
  make_idt_entry(31,(uint32_t)trap31,0x08,0x8E);

  make_idt_entry(32,(uint32_t)irq0,0x08,0x8E);
  make_idt_entry(33,(uint32_t)irq1,0x08,0x8E);
  make_idt_entry(34,(uint32_t)irq2,0x08,0x8E);
  make_idt_entry(35,(uint32_t)irq3,0x08,0x8E);
  make_idt_entry(36,(uint32_t)irq4,0x08,0x8E);
  make_idt_entry(37,(uint32_t)irq5,0x08,0x8E);
  make_idt_entry(38,(uint32_t)irq6,0x08,0x8E);
  make_idt_entry(39,(uint32_t)irq7,0x08,0x8E);
  make_idt_entry(40,(uint32_t)irq8,0x08,0x8E);
  make_idt_entry(41,(uint32_t)irq9,0x08,0x8E);
  make_idt_entry(42,(uint32_t)irq10,0x08,0x8E);
  make_idt_entry(43,(uint32_t)irq11,0x08,0x8E);
  make_idt_entry(44,(uint32_t)irq12,0x08,0x8E);
  make_idt_entry(45,(uint32_t)irq13,0x08,0x8E);
  make_idt_entry(46,(uint32_t)irq14,0x08,0x8E);
  make_idt_entry(47,(uint32_t)irq15,0x08,0x8E);

  handle_trap(int_with_errcode_handler,13);
  ld_idt((uint32_t)(&idt_info_struct));
  
  init_8259();
}


