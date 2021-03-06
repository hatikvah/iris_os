#include "string.h"
#include "type.h"
#include "console.h"
#include "debug.h"

/*WARNING:in the CASE of 's',if use strcpy() with increasing of buf,the output shows nothing!*/

char const tr_str[16]="0123456789abcdef";  //the keyword 'const' is a trouble!!!

static char* vsprintk(char* buf, const char* format,char* arg){
//the arguement arg has the format char* pointing to stack, in order to read the later arguement by byte.
  uint8_t flag=1;
  char* p;
  uint32_t x;
  int32_t len=0;
  while(*format!='\0'){
    switch(*format){
    
    case '%':
            flag=0;
            break;
    case 's':
            if(flag==0){
              flag=1;
              p=*(char**)arg;
              arg=arg+sizeof(char*);
              strcat(buf,p);
            }
            break;
    case 'c':
            if(flag==0){
              flag=1;
              buf[strlen(buf)+1]='\0';
              buf[strlen(buf)]=*arg;
              arg=arg+4; //char format uses 4bytes in stack althought it used 1byte in memory.
            }
            break;
    case 'u':
            if(flag==0){
              flag=1;
              len=strlen(buf);
              x=*((uint32_t*)arg);
              uint32_t an=0x0000000f;
              buf[len++]='0';
              buf[len++]='x';
              for(int i=8;i>0;i--){
                buf[len++]=tr_str[an&(x>>(i*4)-4)];
              }
              buf[len]='\0';
              arg=arg+sizeof(uint32_t);
            }
            break;
    default:
            break;
    }
    
    format++;
    
  }
    return buf;
}

void printk(const char* format,...){
  char buf[64];//buffer
  char* arg=(char*)((char *)(&format)+sizeof(char*));
  console_write(vsprintk(buf,format,arg));
  buf[0]='\0';
}












