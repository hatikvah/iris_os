#include "type.h"

#ifndef STRING_H_
#define STRING_H_

void* memcpy(void* dst,const void* src,uint32_t len);

void* memset(void* dst, char c, uint32_t len);

char* strcpy(char* dst, const char* src);

int strlen(const char* src);

char* strcat(char* dst,const char* src);

#endif
