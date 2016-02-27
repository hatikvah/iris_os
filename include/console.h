#include "type.h"

#ifndef CONSOLE_H_
#define CONSOLE_H_

//clear all context on console
void console_clean();

//print string on console
void console_write(int8_t* cstr);

void console_put_char(int8_t c);

#endif
