#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>
#include <am.h>
#include <userx86.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

void pu(char *args) {
  char *c = args;
  for(; *c; c++) {
    putch(*c);
  }
  putch('\n');
}

size_t strlen(const char *s) {
  size_t len = 0;
  const char *c = s;
  for( ; *c; c++) len++;
  return len; 
}

char *strcpy(char *dst, const char *src) {
  char *tmp = dst;
  while((*dst++ = *src++) != 0) 
    ;
  *dst = 0;
  return tmp;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;
  for(i = 0; i < n && src[i] != '\0'; i++)
    dst[i] = src[i];
  for(; i <= n; i++)
    dst[i] = '\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t dst_len = strlen(dst);
  size_t i = 0;
  for(; *src; src++, i++)
    dst[dst_len + i] = *src;
  dst[dst_len + i] = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 && *s1 == *s2)
    s1++, s2++;
  if(*s1 == *s2)
    return 0;
  return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;
  for(i = 0; i < n; ++i) {
    if(s1[i] != s2[i])
      return (unsigned char)s1[i] - (unsigned char)s2[i];
  }
  return 0;
}

void *memset(void *s, int c, size_t n) {
  if(n%4 == 0 && (int)s%4 == 0) {
    c &= 0xFF;
    stosl(s, c << 24 | c << 16| c << 8 | c, n / 4);
  } else {
    stosb(s, c, n);
  }
  return s;
}

// 根据官方manual的解释
// memmove需要考虑dst与src分别指向的内存段重叠的情况
void *memmove(void *dst, const void *src, size_t n) {
  char *d;
  const char *s;
  d = dst;
  s = src;
  if(s < d && s + n > d) {
    s += n;
    d += n;
    while(n-- > 0) 
      *d-- = *s--;
  } else {
    while(n-- > 0) 
      *d++ = *s++;
  }

  return dst;
}

// 完全可以用memcpy代替的说
void *memcpy(void *out, const void *in, size_t n) {
  return memmove(out, in, n);
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *d1, *d2;
  d1 = s1;
  d2 = s2;
  while(n > 0 && *d1 == *d2) 
    n--, d1++, d2++;
  if(n == 0) {
    return 0;
  }
  return *d1 - *d2;
}

#endif
