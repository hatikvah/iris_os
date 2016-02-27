#include "gdt.h"
#include "type.h"
#include "debug.h"

struct gdt_entry gEntry_list[5];
struct gdt_info gInfo;

static void make_entry(uint32_t no,uint32_t base,uint32_t limit,uint8_t type,uint8_t gran){
  gEntry_list[no].limit_low=(limit&(0xffff));
  gEntry_list[no].base_low=(base&(0x0000ffff));
  gEntry_list[no].base_mid=((base>>16)&0xff);
  gEntry_list[no]._type=type;
  gEntry_list[no]._gran=((limit>>16)&0x0f);
  gEntry_list[no]._gran|=(gran & 0xf0);
  gEntry_list[no].base_high=((base>>24)&0x000000ff);
}
void init_gdt(){
  gInfo.gdt_len=sizeof(struct gdt_entry)*5-1;
  gInfo.gdt_base=(uint32_t)(&gEntry_list);
  
  make_entry(0,0,0,0,0);
  make_entry(1,0,0xffffffff,0x9a,0xcf); //kernel code
  make_entry(2,0,0xffffffff,0x92,0xcf); //kernel data
  make_entry(3,0,0xffffffff,0xfa,0xcf); //user code
  make_entry(4,0,0xffffffff,0xf2,0xcf); //user data
  //printk("%s","after making gdt entries\n");
  gdt_flush((uint32_t)(&gInfo));
  //printk("%s","get flushed\n");
}
