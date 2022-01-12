#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <stdio.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// format string and put on the stdout
int printf(const char *fmt, ...) {
  static char tmp[256];
  int i;
  va_list args;
  va_start(args, fmt);
  i = vsprintf(tmp, fmt, args);
  va_end(args);
  pu(tmp);
  return i;
}

// ap is a pointer to the fmt...  format string and store in the buff


int vsprintf(char *out, const char *fmt, va_list args) {
  char *p;
  static char tmp[256];
  for(p = out; *fmt; fmt++) {
    if(*fmt != '%') {
      *p++ = *fmt;
      continue;
    }
    fmt++;
    switch (*fmt) {
      case 'd':
        intos(tmp, (int)va_arg(args, int));
        strcat(p, tmp);
        p += strlen(tmp);
        break;

      case 'c':
        *p++ = (char)va_arg(args, int);
        break;
      case 's':
        strcpy(tmp, (char *)va_arg(args, char*));
        strcat(p, tmp);
        p += strlen(tmp);
        break;
      case 'x':
        
        break;

      default:
        break;
    }
  }
  *p = 0;
  return (int)(p - out);
}

// format string and store in the buff
int sprintf(char *out, const char *fmt, ...) {
  int i;
  va_list args;
  va_start(args, fmt);
  i = vsprintf(out, fmt, args);
  va_end(args);
  return i;
}

// similar to sprintf, but limit the buff in byte n 
int snprintf(char *out, size_t n, const char *fmt, ...) {
  int i;
  va_list args;
  va_start(args, fmt);
  i = vsnprintf(out, n, fmt, args);
  va_end(args);
  return i;
}

// similar to vsprintf, but limit the buff in byte n 
int vsnprintf(char *out, size_t n, const char *fmt, va_list args) {
  char *p;
  static char tmp[256];
  for(p = out; *fmt; fmt++) {
    if((int)(p - out) >= n) break;
    if(*fmt != '%') {
      *p++ = *fmt;
      continue;
    }
    fmt++;
    switch (*fmt) {
      case 'd':
        intos(tmp, (int)va_arg(args, int));
        strcat(p, tmp);
        p += strlen(tmp);
        break;

      case 'c':
        *p++ = (char)va_arg(args, int);
        break;
      case 's':
        strcpy(tmp, (char *)va_arg(args, char*));
        strcat(p, tmp);
        p += strlen(tmp);
        break;
      case 'x':
        
        break;

      default:
        break;
    }
  }
  *p = 0;
  return (int)(p - out);
}

// int to string 
char* intos(char *dst, int n) {
  int a[32], i = 0;
  char *tmp = dst;
  if(n == 0) {
    *dst++ = 0 + '0';
  }
  for(; n; n /= 10) {
    a[i++] = n%10;
  }
  for(; i > 0; ) {
    *dst++ = a[--i] + '0';
  }
  *dst = 0;
  return tmp;
}
#endif
